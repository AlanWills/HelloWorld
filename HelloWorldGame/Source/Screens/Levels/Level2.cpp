#include "stdafx.h"

#include "Screens/Levels/Level2.h"
#include "Screens/Screen.h"
#include "Events/EventTriggerer.h"
#include "Input/KeyboardActivator.h"
#include "Rendering/SpriteRenderer.h"
#include "Physics/RectangleCollider.h"
#include "Physics/PlayerMoveable.h"
#include "Screens/HelloWorldMainMenuScreen.h"

using namespace CelesteEngine::Input;
using namespace CelesteEngine::Physics;


namespace HW
{
  using namespace Physics;

  REGISTER_SCREEN_CREATOR(Level2, "LevelScreen")

  //------------------------------------------------------------------------------------------------
  Level2::Level2(const Handle<Screen>& screen, const std::string& name) :
    Inherited(screen, name)
  {
  }

  //------------------------------------------------------------------------------------------------
  void Level2::create()
  {
    Level2 level(Screen::allocate());

    const glm::vec2& viewportDimensions = level.getViewportDimensions();

    const Handle<GameObject>& levelActivationGrouper = level.createGameObject(kGUI, glm::vec2(), "LevelActivationGrouper");
    KeyboardActivator::create(levelActivationGrouper, GLFW_KEY_DOWN, GLFW_KEY_UP, kToggle);

    // Create background
    {
      const Handle<GameObject>& background = level.createGameObject(kGUI, glm::vec3(viewportDimensions * 0.5f, -0.1f), "Background", levelActivationGrouper);
      SpriteRenderer::create(background, Path("Sprites", "BinaryBackground.jpg"), viewportDimensions);
    }

    // Create floor
    glm::vec2 floorSize = glm::vec2(viewportDimensions.x, viewportDimensions.y * 0.25f);
    {
      const Handle<GameObject>& floorObject = level.createGameObject(kGUI, glm::vec3(floorSize * 0.5f, 0), "Floor", levelActivationGrouper);
      SpriteRenderer::create(floorObject, Path("Sprites", "UI", "Rectangle.png"), floorSize);
    }

    // Create player
    glm::vec2 playerSize = glm::vec2(100, 100);
    {
      const Handle<GameObject>& player = level.createPlayer(playerSize, glm::vec3(0, floorSize.y + playerSize.y * 0.5f, 0));
      player->setParent(levelActivationGrouper);
    }

    {
      const Handle<GameObject>& leftHandObstacle = level.createGameObject(kGUI, glm::vec2(-2, viewportDimensions.y * 0.5f), "LeftHandObstacle", levelActivationGrouper);
      RectangleCollider::create(leftHandObstacle, glm::vec2(4, viewportDimensions.y));
    }

    // Create draggable
    glm::vec2 draggableSize = glm::vec2(50, 50);
    {
      const Handle<GameObject>& draggableObject = level.createGameObject(kGUI, glm::vec2(700, floorSize.y + draggableSize.y * 0.5f), "Draggable", levelActivationGrouper);
      SpriteRenderer::create(draggableObject, Path("Sprites", "UI", "Rectangle.png"), draggableSize);
      draggableObject->addComponent<PlayerMoveable>();
    }

    // Create switch for door
    glm::vec2 switchSize = glm::vec2(100, 20);
    {
      const Handle<GameObject>& switchObject = level.createGameObject(kGUI, glm::vec2(400, floorSize.y - switchSize.y * 0.5f), "Switch", levelActivationGrouper);
      SpriteRenderer::create(switchObject, Path("Sprites", "UI", "Rectangle.png"), draggableSize, glm::vec4(1, 0, 0, 1));
      RectangleCollider::create(switchObject, switchSize);
    }

    // Create door
    glm::vec2 doorSize = glm::vec2(viewportDimensions.x * 0.1f, viewportDimensions.y - floorSize.y);
    {
      const Handle<GameObject>& doorObject = level.createGameObject(kGUI, viewportDimensions - doorSize * 0.5f, "Door", levelActivationGrouper);
      SpriteRenderer::create(doorObject, Path("Sprites", "MetalDoor.png"), doorSize);
      RectangleCollider::create(doorObject, doorSize, glm::vec2(0, doorSize.y * 0.5f));
    }

    // Create exit
    {
      const Handle<GameObject>& exitObject = level.createGameObject(kGUI, glm::vec2(viewportDimensions.x + playerSize.x * 0.5f, floorSize.y + playerSize.y * 0.5f), "Exit", levelActivationGrouper);
      const Handle<EventTriggerer>& eventTriggerer = EventTriggerer::create(exitObject, EventTriggerer::kOnce,
        [](const Handle<GameObject>& gameObject) -> bool
        {
          return gameObject->getOwnerScreen()->findGameObjectWithName("Player")->getTransform()->getTranslation().x >= gameObject->getTransform()->getTranslation().x;
        },
        [](const Handle<GameObject>& gameObject) -> void
        {
          gameObject->getOwnerScreen()->die();
          HelloWorldMainMenuScreen::create();
        });
    }

    // Create terminal
    {
      level.createTerminalUI();
    }
  }
}
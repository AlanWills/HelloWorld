#include "stdafx.h"

#include "Screens/Levels/Level1.h"
#include "Screens/Levels/Level2.h"
#include "Rendering/SpriteRenderer.h"
#include "Rendering/TextRenderer.h"
#include "Events/EventTriggerer.h"
#include "Input/KeyboardActivator.h"
#include "Input/KeyboardVisibilityScript.h"
#include "Physics/RectangleCollider.h"
#include "Physics/RigidBody2D.h"
#include "Physics/PhysicsUtils.h"
#include "UI/NewCodeDialog.h"

using namespace CelesteEngine::Input;
using namespace CelesteEngine::Physics;


namespace HW
{
  using namespace Physics;

  REGISTER_SCREEN_CREATOR(Level1, "LevelScreen")

  //------------------------------------------------------------------------------------------------
  Level1::Level1(const Handle<Screen>& screen, const std::string& name) :
    Inherited(screen, name)
  {
  }

  //------------------------------------------------------------------------------------------------
  void Level1::create()
  {
    Level1 level1(Screen::allocate());
    const glm::vec2& viewportDimensions = level1.getViewportDimensions();

    const Handle<GameObject>& levelActivationGrouper = level1.createGameObject(kWorld, glm::vec2(), "LevelActivationGrouper");
    KeyboardActivator::create(levelActivationGrouper, GLFW_KEY_DOWN, GLFW_KEY_UP, kToggle);

    // Create background
    {
      //const Handle<GameObject>& background = level1.createGameObject(kWorld, glm::vec3(0, 0, -0.1f), "Background", levelActivationGrouper);
      //SpriteRenderer::create(background, Path("Sprites", "BinaryBackground.jpg"), viewportDimensions);
    }

    // Create floor
    glm::vec2 floorSize = glm::vec2(viewportDimensions.x, viewportDimensions.y * 0.25f);
    {
      const Handle<GameObject>& floorObject = level1.createGameObject(kWorld, glm::vec3(floorSize * 0.5f, -0.01f), "Floor", levelActivationGrouper);
      SpriteRenderer::create(floorObject, Path("Sprites", "UI", "Rectangle.png"), floorSize);
    }

    // Create player
    glm::vec2 playerSize = glm::vec2(100, 100);
    {
      const Handle<GameObject>& player = level1.createPlayer(playerSize, glm::vec3(0, 0, -0.01f));
      player->setParent(levelActivationGrouper);
    }

    {
      const Handle<GameObject>& leftHandObstacle = level1.createGameObject(kGUI, glm::vec2(-2, viewportDimensions.y * 0.5f), "LeftHandObstacle", levelActivationGrouper);
      RectangleCollider::create(leftHandObstacle, glm::vec2(4, viewportDimensions.y));
    }

    // Create door
    glm::vec2 doorSize = glm::vec2(viewportDimensions.x * 0.1f, viewportDimensions.y - floorSize.y);
    {
      const Handle<GameObject>& doorObject = level1.createGameObject(kWorld, glm::vec3(viewportDimensions - doorSize * 0.5f, 0), "Door", levelActivationGrouper);
      SpriteRenderer::create(doorObject, Path("Sprites", "MetalDoor.png"), doorSize);
      RectangleCollider::create(doorObject, doorSize);
    }

    // Create exit
    {
      const Handle<GameObject>& exitObject = level1.createGameObject(kWorld, glm::vec2(viewportDimensions.x + playerSize.x * 0.5f, floorSize.y + playerSize.y * 0.5f), "Exit", levelActivationGrouper);
      const Handle<EventTriggerer>& eventTriggerer = EventTriggerer::create(exitObject, EventTriggerer::kOnce,
        [](const Handle<GameObject>& gameObject) -> bool
        {
          return gameObject->getOwnerScreen()->findGameObjectWithName("Player")->getTransform()->getTranslation().x >= gameObject->getTransform()->getTranslation().x;
        },
        [](const Handle<GameObject>& gameObject) -> void
        {
          gameObject->getOwnerScreen()->die();
          clearSimulatedBodies();

          Level2::create();
        });
    }

    // Create terminal
    {
      level1.createTerminalUI();
    }
  }
}
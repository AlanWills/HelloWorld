#include "stdafx.h"

#include "Screens/Levels/Level2.h"
#include "Screens/Screen.h"
#include "Events/EventTriggerer.h"
#include "Input/KeyboardActivator.h"
#include "Rendering/SpriteRenderer.h"
#include "Physics/RectangleCollider.h"
#include "Physics/PlayerMoveable.h"
#include "Screens/HelloWorldMainMenuScreen.h"
#include "Physics/DoorSwitch.h"
#include "Animation/Animators/MoveToPositionAnimator.h"
#include "Physics/PhysicsUtils.h"

using namespace CelesteEngine::Input;
using namespace CelesteEngine::Physics;
using namespace CelesteEngine::Animators;


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

    const Handle<GameObject>& levelActivationGrouper = level.createGameObject(kWorld, glm::vec2(), "LevelActivationGrouper");
    KeyboardActivator::create(levelActivationGrouper, GLFW_KEY_DOWN, GLFW_KEY_UP, kToggle);

    // Create background
    {
      const Handle<GameObject>& background = level.createGameObject(kWorld, glm::vec3(viewportDimensions * 0.5f, -0.1f), "Background", levelActivationGrouper);
      SpriteRenderer::create(background, Path("Sprites", "BinaryBackground.jpg"), viewportDimensions);
    }

    // Create floor
    glm::vec2 floorSize = glm::vec2(viewportDimensions.x, viewportDimensions.y * 0.25f);
    {
      const Handle<GameObject>& floorObject = level.createGameObject(kWorld, glm::vec3(floorSize * 0.5f, 0), "Floor", levelActivationGrouper);
      SpriteRenderer::create(floorObject, Path("Sprites", "UI", "Rectangle.png"), floorSize);
      RectangleCollider::create(floorObject, floorSize);
    }

    // Create player
    glm::vec2 playerSize = glm::vec2(100, 100);
    {
      const Handle<GameObject>& player = level.createPlayer(playerSize, glm::vec3(0, floorSize.y + playerSize.y * 0.5f, 0));
      player->setParent(levelActivationGrouper);
    }

    {
      const Handle<GameObject>& leftHandObstacle = level.createGameObject(kWorld, glm::vec2(-2, viewportDimensions.y * 0.5f), "LeftHandObstacle", levelActivationGrouper);
      RectangleCollider::create(leftHandObstacle, glm::vec2(4, viewportDimensions.y));
    }

    // Create draggable
    glm::vec2 draggableSize = glm::vec2(50, 50);
    const Handle<GameObject>& draggableObject = level.createGameObject(kWorld, glm::vec2(700, floorSize.y + draggableSize.y * 0.5f), "Draggable", levelActivationGrouper);
    SpriteRenderer::create(draggableObject, Path("Sprites", "UI", "Rectangle.png"), draggableSize);
    const Handle<RectangleCollider>& collider = RectangleCollider::create(draggableObject, draggableSize, kTrigger);
    draggableObject->addComponent<PlayerMoveable>();
    addSimulatedBody(collider, Handle<RigidBody2D>());

    // Create door
    glm::vec2 doorSize = glm::vec2(viewportDimensions.x * 0.1f, viewportDimensions.y - floorSize.y);
    const Handle<GameObject>& doorObject = level.createGameObject(kWorld, viewportDimensions - doorSize * 0.5f, "Door", levelActivationGrouper);
    SpriteRenderer::create(doorObject, Path("Sprites", "MetalDoor.png"), doorSize);
    RectangleCollider::create(doorObject, doorSize);
    const Handle<MoveToPositionAnimator>& animator = MoveToPositionAnimator::create(doorObject, doorObject->getTransform()->getTranslation(), 1);
    animator->setActive(false);

    // Create switch for door
    glm::vec2 switchSize = glm::vec2(100, 20);
    {
      const Handle<GameObject>& switchObject = level.createGameObject(kWorld, glm::vec3(400, floorSize.y - switchSize.y * 0.5f, 0.01f), "Switch", levelActivationGrouper);
      SpriteRenderer::create(switchObject, Path("Sprites", "UI", "Rectangle.png"), switchSize, glm::vec4(1, 0, 0, 1));
      const Handle<RectangleCollider>& collider = RectangleCollider::create(switchObject, switchSize, kTrigger, glm::vec2(0, switchSize.y + 1));
      const Handle<DoorSwitch>& switchScript = switchObject->addComponent<DoorSwitch>();
      switchScript->setDoor(doorObject);
      switchScript->setDraggable(draggableObject);
      switchScript->setShutPosition(doorObject->getTransform()->getTranslation());
      switchScript->setOpenPosition(doorObject->getTransform()->getTranslation() + glm::vec3(0, doorSize.y * 0.5f, 0));
      addSimulatedBody(collider, Handle<RigidBody2D>());
    }

    // Create exit
    {
      const Handle<GameObject>& exitObject = level.createGameObject(kWorld, glm::vec2(viewportDimensions.x + playerSize.x * 0.5f, floorSize.y + playerSize.y * 0.5f), "Exit", levelActivationGrouper);
      const Handle<EventTriggerer>& eventTriggerer = EventTriggerer::create(exitObject, EventTriggerer::kOnce,
        [](const Handle<GameObject>& gameObject) -> bool
        {
          return gameObject->getOwnerScreen()->findGameObjectWithName("Player")->getTransform()->getTranslation().x >= gameObject->getTransform()->getTranslation().x;
        },
        [](const Handle<GameObject>& gameObject) -> void
        {
          gameObject->getOwnerScreen()->die();
          clearSimulatedBodies();
          HelloWorldMainMenuScreen::create();
        });
    }

    // Create terminal
    {
      level.createTerminalUI();
    }
  }
}
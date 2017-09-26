#include "stdafx.h"

#include "Screens/Levels/Level1.h"
#include "Screens/HelloWorldMainMenuScreen.h"
#include "Physics/PlayerObstacle.h"
#include "Rendering/SpriteRenderer.h"
#include "Events/EventTriggerer.h"


namespace HW
{
  using namespace Physics;

  //------------------------------------------------------------------------------------------------
  Level1::Level1(const Handle<Screen>& screen) :
    Inherited(screen)
  {
  }

  //------------------------------------------------------------------------------------------------
  void Level1::create()
  {
    const Handle<Screen>& gameplayScreen = Screen::allocate();

    Level1 level1(gameplayScreen);
    const glm::vec2& viewportDimensions = level1.getViewportDimensions();

    const Handle<GameObject>& levelRoot = level1.createGameObject(kGUI, glm::vec2(), "LevelRoot");

    // Create background
    {
      const Handle<GameObject>& background = level1.createGameObject(kGUI, glm::vec3(viewportDimensions * 0.5f, -0.1f), "Background", levelRoot);
      SpriteRenderer::create(background, Path("Sprites", "BinaryBackground.jpg"), viewportDimensions);
    }

    // Create floor
    glm::vec2 floorSize = glm::vec2(viewportDimensions.x, viewportDimensions.y * 0.25f);
    {
      const Handle<GameObject>& floorObject = level1.createGameObject(kGUI, glm::vec3(floorSize * 0.5f, 0), "Floor", levelRoot);
      SpriteRenderer::create(floorObject, Path("Sprites", "UI", "Rectangle.png"), floorSize);
    }

    // Create player
    glm::vec2 playerSize = glm::vec2(100, 100);
    {
      const Handle<GameObject>& player = level1.createPlayer(
        playerSize, glm::vec3(viewportDimensions.x * 0.25f, floorSize.y + playerSize.y * 0.5f, 0));
      player->setTransformParent(levelRoot);
    }

    {
      const Handle<GameObject>& leftHandObstacle = level1.createGameObject(kGUI, glm::vec2(-2, viewportDimensions.y * 0.5f), "LeftHandObstacle", levelRoot);
      const Handle<PlayerObstacle>& obstacle = leftHandObstacle->addComponent<PlayerObstacle>();
      obstacle->setDimensions(glm::vec2(4, viewportDimensions.y));
    }

    // Create door
    glm::vec2 doorSize = glm::vec2(viewportDimensions.x * 0.1f, viewportDimensions.y - floorSize.y);
    {
      const Handle<GameObject>& doorObject = level1.createGameObject(kGUI, glm::vec3(viewportDimensions - doorSize * 0.5f, 0), "Door", levelRoot);
      SpriteRenderer::create(doorObject, Path("Sprites", "MetalDoor.png"), doorSize);
      doorObject->addComponent<PlayerObstacle>();
    }

    // Create exit
    {
      const Handle<GameObject>& exitObject = level1.createGameObject(kGUI, glm::vec2(viewportDimensions.x + playerSize.x * 0.5f, floorSize.y + playerSize.y * 0.5f), "Exit", levelRoot);
      const Handle<EventTriggerer>& eventTriggerer = exitObject->addComponent<EventTriggerer>();
      eventTriggerer->setCondition([](const Handle<GameObject>& gameObject) -> bool
      {
        return gameObject->getOwnerScreen()->findGameObjectWithName("Player")->getTransform()->getTranslation().x >= gameObject->getTransform()->getTranslation().x;
      });
      eventTriggerer->getEvent().subscribe([](const Handle<GameObject>& gameObject) -> void
      {
        gameObject->getOwnerScreen()->die();
        HelloWorldMainMenuScreen::create();
      });
    }

    // Create terminal
    {
      level1.createTerminalUI();
    }
  }
}
#include "stdafx.h"

#include "Screens/Levels/Level1.h"
#include "Screens/TerminalScreen.h"
#include "Controllers/PlayerController.h"
#include "Rendering/SpriteRenderer.h"


namespace HW
{
  //------------------------------------------------------------------------------------------------
  Level1::Level1(const Handle<Screen>& screen) :
    Inherited(screen, "Level1")
  {
  }

  //------------------------------------------------------------------------------------------------
  void Level1::create()
  {
    const Handle<Screen>& gameplayScreen = Screen::allocate();

    Level1 level1(gameplayScreen);
    const glm::vec2& viewportDimensions = level1.getViewportDimensions();

    // Create floor
    glm::vec2 floorSize = glm::vec2(viewportDimensions.x, viewportDimensions.y * 0.25f);
    {
      const Handle<GameObject>& floorObject = level1.createGameObject(kGUI, glm::vec3(floorSize * 0.5f, 0), "Floor");

      SpriteRenderer::create(
        floorObject,
        Path("Sprites", "UI", "Rectangle.png"),
        floorSize);
    }

    // Create door
    glm::vec2 doorSize = glm::vec2(viewportDimensions.x * 0.1f, viewportDimensions.y - floorSize.y);
    {
      const Handle<GameObject>& doorObject = level1.createGameObject(kGUI, glm::vec3(viewportDimensions - doorSize * 0.5f, 0), "Door");

      SpriteRenderer::create(
        doorObject,
        Path("Sprites", "MetalDoor.png"),
        doorSize);
    }

    // Create terminal
    glm::vec2 terminalSize = glm::vec2(90, 90);
    {
      level1.createTerminal(terminalSize, glm::vec3(viewportDimensions.x * 0.5f, floorSize.y + terminalSize.y * 0.5f, 0));
    }

    // Create player
    glm::vec2 playerSize = glm::vec2(100, 100);
    {
      const Handle<GameObject>& player = level1.createPlayer(
        playerSize, glm::vec3(viewportDimensions.x * 0.25f, floorSize.y + playerSize.y * 0.5f, 0.1f));

      const Handle<PlayerController>& controller = player->findComponent<PlayerController>();
      controller->setMinPosition(playerSize.x * 0.5f);
      controller->setMaxPosition(viewportDimensions.x * 0.95f - (doorSize.x + playerSize.x) * 0.5f);
      controller->setNextLevelPosition(viewportDimensions.x + playerSize.x * 0.5f);
    }
  }
}
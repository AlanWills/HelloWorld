#include "stdafx.h"

#include "Screens/LevelScreen.h"
#include "Physics/RectangleCollider.h"
#include "Input/KeyboardRigidBody2DController.h"
#include "Rendering/SpriteRenderer.h"
#include "Controllers/PlayerController.h"
#include "ComputerInteractionUI/ComputerInteractionUI.h"


using namespace CelesteEngine::Physics;
using namespace CelesteEngine::Input;

namespace HW
{
  //------------------------------------------------------------------------------------------------
  LevelScreen::LevelScreen(const Handle<Screen>& screen, const std::string& name) :
    Inherited(screen, name)
  {
  }

  //------------------------------------------------------------------------------------------------
  Handle<GameObject> LevelScreen::createPlayer(const glm::vec2& size, const glm::vec3& translation)
  {
    const Handle<GameObject>& player = createGameObject(kGUI, translation, "Player");
    SpriteRenderer::create(
      player,
      Path("Sprites", "UI", "Rectangle.png"),
      size,
      glm::vec4(0, 0, 1, 1));

    const Handle<RectangleCollider>& playerCollider = player->addComponent<RectangleCollider>();
    playerCollider->setDimensions(player->findComponent<Renderer>()->getDimensions());

    const Handle<KeyboardRigidBody2DController>& playerMovement = player->addComponent<KeyboardRigidBody2DController>();
    playerMovement->setIncreaseXLinearVelocityKey(GLFW_KEY_D);
    playerMovement->setDecreaseXLinearVelocityKey(GLFW_KEY_A);
    playerMovement->setLinearVelocityDelta(10, 0);
    playerMovement->setIncrementMode(KeyboardRigidBody2DController::kToggle);

    player->addComponent<PlayerController>();

    return player;
  }

  //------------------------------------------------------------------------------------------------
  Handle<GameObject> LevelScreen::createTerminal(const glm::vec2& size, const glm::vec3& translation)
  {
    const Handle<GameObject>& terminal = createGameObject(kGUI, translation, "Terminal");
    SpriteRenderer::create(
      terminal,
      Path("Sprites", "ComputerTerminal.png"),
      size);

    const Handle<RectangleCollider>& terminalCollider = terminal->addComponent<RectangleCollider>();
    terminalCollider->setDimensions(terminal->findComponent<Renderer>()->getDimensions());

    terminal->addComponent<HWUI::ComputerInteractionUI>();

    return terminal;
  }
}
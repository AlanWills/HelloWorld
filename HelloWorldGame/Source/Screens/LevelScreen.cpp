#include "stdafx.h"

#include "Screens/LevelScreen.h"
#include "Physics/RectangleCollider.h"
#include "Input/KeyboardRigidBody2DController.h"
#include "Rendering/SpriteRenderer.h"
#include "Controllers/PlayerController.h"
#include "Rendering/TextRenderer.h"
#include "UI/TextBox.h"
#include "Input/TerminalActivationHandler.h"


using namespace CelesteEngine::Physics;
using namespace CelesteEngine::Input;
using namespace CelesteEngine::UI;

namespace HW
{
  using namespace HW::Input;

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

    player->addComponent<RigidBody2D>();

    const Handle<KeyboardRigidBody2DController>& playerMovement = player->addComponent<KeyboardRigidBody2DController>();
    playerMovement->setIncreaseXLinearVelocityKey(GLFW_KEY_D);
    playerMovement->setDecreaseXLinearVelocityKey(GLFW_KEY_A);
    playerMovement->setLinearVelocityDelta(10, 0);
    playerMovement->setIncrementMode(KeyboardRigidBody2DController::kToggle);

    player->addComponent<PlayerController>();

    return player;
  }

  //------------------------------------------------------------------------------------------------
  Handle<GameObject> LevelScreen::createTerminalUI()
  {
    const glm::vec2& viewportDimensions = getViewportDimensions();

    const Handle<GameObject>& grouper = createGameObject(kGUI, glm::vec3(viewportDimensions.x * 0.8, viewportDimensions.y * 0.5f, 0.1f), "TerminalGrouper");
    TerminalActivationHandler::create(grouper, GLFW_KEY_UP, GLFW_KEY_DOWN);

    // Create background
    {
      const Handle<GameObject>& background = createGameObject(kGUI, glm::vec2(0.1f), "TerminalBackground");
      background->getTransform()->setParent(grouper->getTransform());
      SpriteRenderer::create(background, Path("Sprites", "UI", "Rectangle.png"), glm::vec2(400, 400), glm::vec4(0.1f, 0.1f, 0.1f, 1));
    }

    // Create input text box
    {
      const Handle<GameObject>& terminalTextBox = createGameObject(kGUI, glm::vec3(0, 0, 0.1f), "TerminalTextBox");
      terminalTextBox->getTransform()->setParent(grouper->getTransform());
      TextBox::create(terminalTextBox, "", 24);
    }

    // Create output text
    {
      const Handle<GameObject>& outputText = createGameObject(kGUI, glm::vec2(0, -100), "TerminalOutput");
      outputText->getTransform()->setParent(grouper->getTransform());
      TextRenderer::create(outputText, "", 24);
    }

    return grouper;
  }
}
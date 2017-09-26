#include "stdafx.h"

#include "Screens/LevelScreenCreator.h"
#include "Physics/RectangleCollider.h"
#include "Input/KeyboardRigidBody2DController.h"
#include "Rendering/SpriteRenderer.h"
#include "Rendering/TextRenderer.h"
#include "UI/TextBox.h"
#include "Input/TerminalActivationHandler.h"
#include "Input/TerminalInputHandler.h"


using namespace CelesteEngine::Physics;
using namespace CelesteEngine::Input;
using namespace CelesteEngine::UI;

namespace HW
{
  using namespace HW::Input;

  //------------------------------------------------------------------------------------------------
  LevelScreenCreator::LevelScreenCreator(const Handle<Screen>& screen, const std::string& name) :
    Inherited(screen, name)
  {
  }

  //------------------------------------------------------------------------------------------------
  Handle<GameObject> LevelScreenCreator::createPlayer(const glm::vec2& size, const glm::vec3& translation)
  {
    const Handle<GameObject>& player = createGameObject(kGUI, translation, "Player");
    SpriteRenderer::create(player, Path("Sprites", "UI", "Rectangle.png"), size, glm::vec4(0, 0, 1, 1));

    const Handle<RectangleCollider>& playerCollider = player->addComponent<RectangleCollider>();
    playerCollider->setDimensions(player->findComponent<Renderer>()->getDimensions());

    player->addComponent<RigidBody2D>();

    const Handle<KeyboardRigidBody2DController>& playerMovement = player->addComponent<KeyboardRigidBody2DController>();
    playerMovement->setIncreaseXLinearVelocityKey(GLFW_KEY_D);
    playerMovement->setDecreaseXLinearVelocityKey(GLFW_KEY_A);
    playerMovement->setLinearVelocityDelta(10, 0);
    playerMovement->setIncrementMode(KeyboardRigidBody2DController::kToggle);

    return player;
  }

  //------------------------------------------------------------------------------------------------
  Handle<GameObject> LevelScreenCreator::createTerminalUI()
  {
    const glm::vec2& viewportDimensions = getViewportDimensions();

    const Handle<GameObject>& grouper = createGameObject(kGUI, glm::vec3(viewportDimensions * 0.5f, 0.1f), "TerminalGrouper");
    TerminalActivationHandler::create(grouper, GLFW_KEY_UP, GLFW_KEY_DOWN);

    // Create black background for whole screen
    {
      const Handle<GameObject>& blackBackground = createGameObject(kGUI, glm::vec2(), "BlackBackground", grouper);
      SpriteRenderer::create(blackBackground, Path("Sprites", "UI", "Rectangle.png"), glm::vec2(viewportDimensions.x, viewportDimensions.y), glm::vec4(0, 0, 0, 0.6f));
      blackBackground->setActive(false);
      blackBackground->setShouldRender(false);
    }

    // Create background
    {
      const Handle<GameObject>& background = createGameObject(kGUI, glm::vec3(0 , 0, 0.1f), "TerminalBackground", grouper);
      SpriteRenderer::create(background, Path("Sprites", "TerminalBackground.png"), viewportDimensions * 0.6f);
      background->setActive(false);
      background->setShouldRender(false);
    }

    // Create input text box
    {
      const Handle<GameObject>& terminalTextBox = createGameObject(kGUI, glm::vec3(-viewportDimensions.x * 0.3f, viewportDimensions.y * 0.3f, 0.15f), "TerminalTextBox", grouper);
      TextBox::create(terminalTextBox, "> ", 24, Horizontal::kLeft, Vertical::kTop, glm::vec4(0, 1, 0, 1));
      terminalTextBox->setActive(false);
      terminalTextBox->setShouldRender(false);
      terminalTextBox->addComponent<TerminalInputHandler>();
    }

    return grouper;
  }
}
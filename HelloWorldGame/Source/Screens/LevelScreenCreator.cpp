#include "stdafx.h"

#include "Screens/LevelScreenCreator.h"
#include "Rendering/SpriteRenderer.h"
#include "Rendering/TextRenderer.h"
#include "Input/KeyboardActivator.h"
#include "Input/KeyboardVisibilityScript.h"
#include "Input/KeyboardMovementScript.h"
#include "Input/TerminalInputHandler.h"
#include "Physics/RectangleCollider.h"
#include "Physics/PhysicsUtils.h"
#include "Physics/RigidBody2D.h"


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
    const Handle<GameObject>& player = createGameObject(kWorld, translation, "Player");
    SpriteRenderer::create(player, Path("Sprites", "UI", "Rectangle.png"), size, glm::vec4(1, 1, 1, 1));

    const Handle<RectangleCollider>& playerCollider = player->addComponent<RectangleCollider>();
    playerCollider->setDimensions(player->findComponent<Renderer>()->getDimensions());

    const Handle<RigidBody2D>& rigidBody = player->addComponent<RigidBody2D>();
    rigidBody->setMaxLinearVelocity(glm::vec2(1, FLT_MAX));
    rigidBody->setMinLinearVelocity(glm::vec2(-1, -FLT_MAX));

    KeyboardMovementScript::create(player, GLFW_KEY_A, GLFW_KEY_D, -1, -1, 1);
    
    addSimulatedBody(playerCollider, rigidBody);

    return player;
  }

  //------------------------------------------------------------------------------------------------
  Handle<GameObject> LevelScreenCreator::createTerminalUI()
  {
    const glm::vec2& viewportDimensions = getViewportDimensions();

    const Handle<GameObject>& visibilityGrouper = createGameObject(kGUI, glm::vec3(viewportDimensions * 0.5f, 0.1f), "TerminalVisibilityGrouper");
    KeyboardVisibilityScript::create(visibilityGrouper, GLFW_KEY_UP, GLFW_KEY_DOWN, kToggle);

    const Handle<GameObject>& activationGrouper = createGameObject(kGUI, glm::vec2(), "TerminalActivationGrouper", visibilityGrouper);

    // Create black background for whole screen
    {
      const Handle<GameObject>& blackBackground = createGameObject(kGUI, glm::vec2(), "BlackBackground", activationGrouper);
      SpriteRenderer::create(blackBackground, Path("Sprites", "UI", "Rectangle.png"), glm::vec2(viewportDimensions.x, viewportDimensions.y), glm::vec4(0, 0, 0, 0.6f));
    }

    // Create background for terminal
    const glm::vec2& terminalSize = viewportDimensions * 0.6f;
    {
      const Handle<GameObject>& background = createGameObject(kGUI, glm::vec3(0, 0, 0.1f), "TerminalBackground", activationGrouper);
      SpriteRenderer::create(background, Path("Sprites", "TerminalBackground.png"), terminalSize);
    }

    // Create input text box
    {
      glm::vec2 margin(20, 15);
      const Handle<GameObject>& terminalTextBox = createGameObject(kGUI, glm::vec3(-viewportDimensions.x * 0.3f + margin.x, viewportDimensions.y * 0.3f - margin.y, 0.15f), "TerminalTextBox", activationGrouper);
      TextRenderer::create(terminalTextBox, "> ", 24, Horizontal::kLeft, Vertical::kTop, glm::vec4(0, 1, 0, 1));
      terminalTextBox->addComponent<TerminalInputHandler>();
    }

    visibilityGrouper->setShouldRender(false);
    activationGrouper->setActive(false);
    // Create after setting active to false to make sure it is still active
    KeyboardActivator::create(activationGrouper, GLFW_KEY_UP, GLFW_KEY_DOWN, kToggle);

    return visibilityGrouper;
  }
}
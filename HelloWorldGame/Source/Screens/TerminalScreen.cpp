#include "stdafx.h"

#include "Screens/TerminalScreen.h"
#include "Screens/ScreenUtils.h"
#include "Rendering/TextRenderer.h"
#include "UI/TextBox.h"
#include "UI/ToolTip.h"
#include "UI/Button.h"
#include "UI/StackPanel.h"
#include "Physics/RectangleCollider.h"


using namespace CelesteEngine::UI;
using namespace CelesteEngine::Physics;

namespace HW
{
  //------------------------------------------------------------------------------------------------
  TerminalScreen::TerminalScreen(const Handle<Screen>& screen) :
    Inherited(screen, "Terminal")
  {
  }

  //------------------------------------------------------------------------------------------------
  void TerminalScreen::create()
  {
    const Handle<Screen>& terminalScreen = Screen::allocate();

    TerminalScreen terminal(terminalScreen);
    const glm::vec2& viewportDimensions = terminal.getViewportDimensions();

    // Create terminal
    {
      const Handle<GameObject>& terminalTextBox = terminal.createGameObject(kGUI, glm::vec3(10, viewportDimensions.y - 10, 0), "TerminalTextBox");
      TextBox::create(terminalTextBox, "", 24);
    }

    // Create output text
    {
      const Handle<GameObject>& outputText = terminal.createGameObject(kGUI, glm::vec3(viewportDimensions.x * 0.5f, viewportDimensions.y, 0), "Output");
      TextRenderer::create(outputText, "", 24);
    }

    {
      const Handle<GameObject>& runCodeButton = terminal.createGameObject(kGUI, glm::vec3(), "Run Code Button");
      Button::create(runCodeButton, "Run Code", [](const Handle<GameObject>& gameObject) -> void { });

      const Handle<GameObject>& quitButton = terminal.createGameObject(kGUI, glm::vec3(), "Quit Button");
      Button::create(quitButton, "Quit",
        std::bind(&deactivateOwnerScreen, std::placeholders::_1),
        [](const Handle<GameObject>& gameObject) -> void { activateScreen("Level1"); });

      const Handle<GameObject>& terminalButtonStackPanelObject = terminal.createGameObject(kGUI, glm::vec3(viewportDimensions.x * 0.5f, viewportDimensions.y * 0.1f, 0), "Button Stack Panel");
      StackPanel::create(terminalButtonStackPanelObject, Horizontal::kCentre, runCodeButton, quitButton);
    }

    deactivateScreen(terminalScreen);
  }
}
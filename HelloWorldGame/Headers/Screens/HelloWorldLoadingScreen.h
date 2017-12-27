#pragma once

#include "Screens/LevelScreenCreator.h"
#include "ObjectFX/LimitedLifeTime.h"
#include "GraphicalFX/TypingTextEffect.h"
#include "UI/ProgressBar.h"
#include "Loading/LevelLoader.h"
#include "Code/PlayerScriptCommands.h"


namespace HW
{

class HelloWorldLoadingScreen : public CelesteEngine::ScreenCreator
{
  DECLARE_SCREEN_CREATOR(HelloWorldLoadingScreen)

  public:
    template <class T>
    static void create();

  private:
    typedef CelesteEngine::ScreenCreator Inherited;
};

//------------------------------------------------------------------------------------------------
template <class T>
void HelloWorldLoadingScreen::create()
{
  STATIC_ASSERT((std::is_base_of<LevelScreenCreator, T>::value), "Inputted type must derive from LevelScreenCreator");

  const Handle<Screen>& screen = Screen::allocate();
  HelloWorldLoadingScreen loadingScreen(screen);
  const glm::vec2& viewportDimensions = loadingScreen.getViewportDimensions();

  // Create object which will trigger the transition
  {
    const Handle<GameObject>& transitioner = loadingScreen.createGameObject(kGUI, viewportDimensions * 0.5f, "Transitioner");
    LimitedLifeTime::create(transitioner, 3, [](EventArgs& e, const Handle<GameObject>& gameObject) -> void
    {
      gameObject->getOwnerScreen()->die();
      T::create();
    });
  }

  // Create some UI to keep the user occupied
  {
    const Handle<GameObject>& typingText = loadingScreen.createGameObject(kGUI, viewportDimensions * 0.5f, "TypingText");
    UI::TextBox::create(typingText, "", 24, Horizontal::kCentre, Vertical::kCentre, glm::vec4(0, 1, 0, 1));
    TypingTextEffect::create(typingText, std::vector<std::string>
    {
      "Booting Runtime",
      "Simulating Physics",
      "Populating World"
    },
    0.03f, 0.0f);
  }

  // Create the progress bar
  {
    const Handle<GameObject>& progressBar = loadingScreen.createGameObject(kGUI, glm::vec2(viewportDimensions.x * 0.5f, viewportDimensions.y * 0.25f), "ProgressBar");
    SpriteRenderer::create(progressBar, Path("Sprites", "UI", "ProgressBar.png"), glm::vec4(0, 1, 0, 1));
    ProgressBar::create(progressBar, 0, 3);
    progressBar->addComponent<LevelLoader>();
  }

  // Load the players available script commands
  Code::PlayerScriptCommands::instance().loadAsync();
}

}
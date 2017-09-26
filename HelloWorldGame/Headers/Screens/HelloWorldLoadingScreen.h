#pragma once

#include "Screens/LevelScreenCreator.h"
#include "ObjectFX/LimitedLifeTime.h"
#include "GraphicalFX/TypingTextEffect.h"


namespace HW
{

class HelloWorldLoadingScreen : public CelesteEngine::ScreenCreator
{
  public:
    HelloWorldLoadingScreen(const HelloWorldLoadingScreen&) = delete;
    HelloWorldLoadingScreen& operator=(const HelloWorldLoadingScreen&) = delete;

    template <class T>
    static void create();

  protected:
    HelloWorldLoadingScreen(const Handle<Screen>& screen);

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
    LimitedLifeTime::create(transitioner, 3, [](const Handle<GameObject>& gameObject) -> void
    {
      gameObject->getOwnerScreen()->die();
      T::create();
    });
  }

  // Create some UI to keep the user occupied
  {
    const Handle<GameObject>& typingText = loadingScreen.createGameObject(kGUI, viewportDimensions * 0.5f, "TypingText");
    TextRenderer::create(typingText, "", 24, Horizontal::kCentre, Vertical::kCentre, glm::vec4(0, 1, 0, 1));
    TypingTextEffect::create(typingText, std::vector<std::string>
    {
      "Booting Runtime",
      "Simulating Physics",
      "Populating World"
    });
  }
}

}
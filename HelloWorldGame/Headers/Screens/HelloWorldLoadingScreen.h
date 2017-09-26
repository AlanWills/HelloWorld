#pragma once

#include "Screens/LevelScreenCreator.h"


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
  STATIC_ASSERT((std::is_base_of<LevelScreenCreator, T>()));

  const Handle<Screen>& screen = Screen::allocate();
  HelloWorldLoadingScreen loadingScreen(screen);
  const glm::vec2& viewportDimensions = loadingScreen.getViewportDimensions();
}

}
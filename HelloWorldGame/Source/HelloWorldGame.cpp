#include "stdafx.h"

#include "HelloWorldGame.h"
#include "Screens/HelloWorldSplashScreen.h"
#include "Audio/AudioSource.h"


namespace HW
{
  //------------------------------------------------------------------------------------------------
  void HelloWorldGame::onInitialize()
  {
    Inherited::onInitialize();

    const Handle<Screen>& persistent = Screen::allocate();
    persistent->setName("Persistent");

    const Handle<GameObject>& audio = persistent->allocateGameObject(kGUI);
    const Handle<AudioSource>& audioSource = AudioSource::create(audio, Path("StartupMusic.wav"));
    //audioSource->play();

    HelloWorldSplashScreen::create();
  }
}
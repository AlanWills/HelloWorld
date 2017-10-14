#include "stdafx.h"

#include "HelloWorldGame.h"
#include "Screens/HelloWorldSplashScreen.h"
#include "Audio/AudioSource.h"
#include "Settings/Settings.h"


namespace HW
{
  //------------------------------------------------------------------------------------------------
  void HelloWorldGame::onInitialize()
  {
    Inherited::onInitialize();

    Settings::Settings settings;
    settings.load(Path("Settings", "Settings.xml"));
    getAudioManager()->setMasterVolume(settings.getSetting("MasterVolume", 1.0f));
    getAudioManager()->setMusicVolume(settings.getSetting("MusicVolume", 1.0f));
    getAudioManager()->setSFXVolume(settings.getSetting("SFXVolume", 1.0f));

    const Handle<Screen>& persistent = Screen::allocate();
    persistent->setName("Persistent");

    const Handle<GameObject>& audio = persistent->allocateGameObject(kGUI);
    const Handle<AudioSource>& audioSource = AudioSource::create(audio, Path("StartupMusic.wav"), kMusic, true);
    audioSource->play();

    HelloWorldSplashScreen::create();
  }
}
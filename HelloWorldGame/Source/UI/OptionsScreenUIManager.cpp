#include "stdafx.h"

#include "UI/OptionsScreenUIManager.h"
#include "Objects/GameObject.h"
#include "Screens/Screen.h"
#include "UI/Slider.h"
#include "UI/Button.h"
#include "Rendering/TextRenderer.h"
#include "Audio/AudioManager.h"
#include "Settings/Settings.h"
#include "Resources/ResourceManager.h"

using namespace CelesteEngine::UI;
using namespace CelesteEngine::Rendering;
using namespace CelesteEngine::Audio;


namespace HW
{
  REGISTER_SCRIPT(OptionsScreenUIManager, 1);

  //------------------------------------------------------------------------------------------------
  OptionsScreenUIManager::OptionsScreenUIManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  OptionsScreenUIManager::~OptionsScreenUIManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  void OptionsScreenUIManager::onSetGameObject(const Handle<GameObject>& gameObject)
  {
    Inherited::onSetGameObject(gameObject);

    const Handle<Screen>& screen = gameObject->getOwnerScreen();
    if (screen.is_null())
    {
      ASSERT_FAIL();
      return;
    }

    initializeMasterVolumeSlider(screen);
    initializeMusicVolumeSlider(screen);
    initializeSFXVolumeSlider(screen);
    initializeCloseButton(screen);
  }

  //------------------------------------------------------------------------------------------------
  void OptionsScreenUIManager::initializeMasterVolumeSlider(const Handle<Screen>& screen)
  {
    const Handle<Slider>& slider = screen->findGameObjectWithName("MasterVolumeSlider")->findComponent<Slider>();
    slider->subscribeValueChangedCallback([](EventArgs& e, const Handle<GameObject>& go, float newValue) -> void
    {
      const Handle<GameObject>& sliderLabel = go->findChildGameObject("MasterVolumeValueText");
      sliderLabel->findComponent<TextRenderer>()->setLine(0, std::to_string(static_cast<int>(newValue * 100.0f)));
      getAudioManager()->setMasterVolume(newValue);
    });
    slider->setCurrentValue(getAudioManager()->getMasterVolume());

    // Invoke the event to update any UI just in case it's not triggered already by setting the current value
    slider->getValueChangedEvent().invoke(slider->getGameObject(), slider->getCurrentValue());
  }

  //------------------------------------------------------------------------------------------------
  void OptionsScreenUIManager::initializeMusicVolumeSlider(const Handle<Screen>& screen)
  {
    const Handle<Slider>& slider = screen->findGameObjectWithName("MusicVolumeSlider")->findComponent<Slider>();
    slider->subscribeValueChangedCallback([](EventArgs& e, const Handle<GameObject>& go, float newValue) -> void
    {
      const Handle<GameObject>& sliderLabel = go->findChildGameObject("MusicVolumeValueText");
      sliderLabel->findComponent<TextRenderer>()->setLine(0, std::to_string(static_cast<int>(newValue * 100.0f)));
      getAudioManager()->setMusicVolume(newValue);
    });
    slider->setCurrentValue(getAudioManager()->getMusicVolume());

    // Invoke the event to update any UI just in case it's not triggered already by setting the current value
    slider->getValueChangedEvent().invoke(slider->getGameObject(), slider->getCurrentValue());
  }

  //------------------------------------------------------------------------------------------------
  void OptionsScreenUIManager::initializeSFXVolumeSlider(const Handle<Screen>& screen)
  {
    const Handle<Slider>& slider = screen->findGameObjectWithName("SFXVolumeSlider")->findComponent<Slider>();
    slider->subscribeValueChangedCallback([](EventArgs& e, const Handle<GameObject>& go, float newValue) -> void
    {
      const Handle<GameObject>& sliderLabel = go->findChildGameObject("SFXVolumeValueText");
      sliderLabel->findComponent<TextRenderer>()->setLine(0, std::to_string(static_cast<int>(newValue * 100.0f)));
      getAudioManager()->setSFXVolume(newValue);
    });
    slider->setCurrentValue(getAudioManager()->getSFXVolume());

    // Invoke the event to update any UI just in case it's not triggered already by setting the current value
    slider->getValueChangedEvent().invoke(slider->getGameObject(), slider->getCurrentValue());
  }

  //------------------------------------------------------------------------------------------------
  void OptionsScreenUIManager::initializeCloseButton(const Handle<Screen>& screen)
  {
    const Handle<Button>& button = screen->findGameObjectWithName("CloseButton")->findComponent<Button>();
    button->subscribeLeftClickCallback([](EventArgs& e, const Handle<GameObject>& gameObject) -> void
    {
      // Save changes
      Settings settings;
      settings.setSetting("MasterVolume", getAudioManager()->getMasterVolume());
      settings.setSetting("MusicVolume", getAudioManager()->getMusicVolume());
      settings.setSetting("SFXVolume", getAudioManager()->getSFXVolume());
      settings.save(Path(getResourceManager()->getDataDirectoryPath(), "Settings", "Settings.xml"));
    });
  }
}
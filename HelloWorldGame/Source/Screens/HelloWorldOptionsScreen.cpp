#include "stdafx.h"

#include "Screens/HelloWorldOptionsScreen.h"
#include "Screens/HelloWorldMainMenuScreen.h"
#include "UI/StackPanel.h"
#include "Events/EventTriggerer.h"
#include "Input/InputManager.h"
#include "Rendering/TextRenderer.h"
#include "UI/Button.h"
#include "Settings/Settings.h"
#include "Audio/AudioManager.h"
#include "Resources/ResourceManager.h"

using namespace CelesteEngine::UI;
using namespace CelesteEngine::Audio;


namespace HW
{
  REGISTER_SCREEN_CREATOR(HelloWorldOptionsScreen, "OptionsScreen")

  //------------------------------------------------------------------------------------------------
  HelloWorldOptionsScreen::HelloWorldOptionsScreen(const Handle<Screen>& screen, const std::string& name) :
    Inherited(screen, name)
  {
  }

  //------------------------------------------------------------------------------------------------
  void HelloWorldOptionsScreen::create()
  {
    HelloWorldOptionsScreen options(Screen::allocate());
    const glm::vec2& viewportDimensions = options.getViewportDimensions();

    const Handle<GameObject>& titleObject = options.createGameObject(
      kGUI, glm::vec2(viewportDimensions.x * 0.5f, viewportDimensions.y * 0.8f), "TitleObject");
    TextRenderer::create(titleObject, "Options", 30);

    // Create master volume slider
    const Handle<GameObject>& masterVolume = options.createMasterVolumeSlider(
      glm::vec2(), Path("Sprites", "UI", "Rectangle.png"), "MasterVolumeSlider", glm::vec2(400, 30), "Master Volume");

    const Handle<GameObject>& musicVolume = options.createMusicVolumeSlider(
      glm::vec2(), Path("Sprites", "UI", "Rectangle.png"), "MusicVolumeSlider", glm::vec2(400, 30), "Music Volume");

    const Handle<GameObject>& sfxVolume = options.createSFXVolumeSlider(
      glm::vec2(), Path("Sprites", "UI", "Rectangle.png"), "SFXVolumeSlider", glm::vec2(400, 30), "SFX Volume");

    const Handle<GameObject>& stackPanel = options.createGameObject(kGUI, viewportDimensions * 0.5f, "VolumeStackPanel");
    UI::StackPanel::create(stackPanel, Vertical::kCentre, 50, masterVolume, musicVolume, sfxVolume);

    const Handle<GameObject>& closeButton = options.createGameObject(kGUI, glm::vec2(0, -200), "CloseButton", sfxVolume);
    Button::create(closeButton, "Close", [](EventArgs& e, const Handle<GameObject>& gameObject) -> void
    {
      // Save changes
      Settings settings;
      settings.setSetting("MasterVolume", getAudioManager()->getMasterVolume());
      settings.setSetting("MusicVolume", getAudioManager()->getMusicVolume());
      settings.setSetting("SFXVolume", getAudioManager()->getSFXVolume());
      settings.save(Path(getResourceManager()->getDataDirectoryPath(), "Settings", "Settings.xml"));

      gameObject->getOwnerScreen()->die();
      HelloWorldMainMenuScreen::create();
    });
  }
}
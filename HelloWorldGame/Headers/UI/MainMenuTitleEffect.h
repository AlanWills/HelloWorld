#pragma once

#include "Objects/Script.h"
#include "UI/TextBox.h"
#include "Audio/AudioSource.h"
#include "Maths/RandomGenerator.h"


namespace HW
{

class MainMenuTitleEffect : public CelesteEngine::Script
{
  DECLARE_SCRIPT(MainMenuTitleEffect)

  protected:
    void onSetGameObject(const Handle<GameObject>& gameObject) override;
    void onUpdate(GLfloat elapsedGameTime) override;
    void onDeath() override;

  private:
    typedef CelesteEngine::Script Inherited;

    Handle<UI::TextBox> m_textBox;

    const std::vector<Path> m_keyPressSoundPaths;
    std::vector<Handle<Audio::AudioSource>> m_keyPressAudio;
    float m_currentTimer;
    float m_nextTimer;

    static std::string m_text;
    static RandomGenerator m_generator;
};

}
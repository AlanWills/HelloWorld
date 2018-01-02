#pragma once

#include "Objects/Script.h"
#include "UI/TextBox.h"
#include "Audio/AudioSource.h"
#include "Maths/RandomGenerator.h"


namespace HW
{

class TypingTextEffect : public CelesteEngine::Script
{
  DECLARE_SCRIPT(TypingTextEffect)

  public:
    float getDelay() const { return m_delay; }
    void setDelay(float averageTypeSpeed) { m_delay = averageTypeSpeed; }

    float getTypeSpeedVariation() const { return m_typeSpeedVariation; }
    void setTypeSpeedVariation(float typeSpeedVariation) { m_typeSpeedVariation = typeSpeedVariation; }

    const std::vector<std::string>& getText() const { return m_text; }
    void setText(const std::vector<std::string>& text) { m_text = text; }
    void setText(const std::string& text) 
    { 
      m_text.clear(); 
      m_text.push_back(text); 
    }

    //------------------------------------------------------------------------------------------------
    static Handle<TypingTextEffect> create(
      const Handle<GameObject>& gameObject, 
      const std::vector<std::string>& text,
      float delay,
      float typeSpeedVariation);

    static Handle<TypingTextEffect> create(
      const Handle<GameObject>& gameObject, 
      const std::string& text,
      float delay,
      float typeSpeedVariation)
    {
      return create(gameObject, std::vector<std::string> { text }, delay, typeSpeedVariation);
    }

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
    float m_delay;
    float m_typeSpeedVariation;

    std::vector<std::string> m_text;
    size_t m_currentLine;

    static RandomGenerator m_generator;
};

}
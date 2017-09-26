#include "stdafx.h"

#include "GraphicalFX/TypingTextEffect.h"
#include "Objects/GameObject.h"
#include "Resources/ResourceManager.h"

using namespace CelesteEngine;
using namespace CelesteEngine::UI;
using namespace CelesteEngine::Audio;


namespace HW
{
  RandomGenerator TypingTextEffect::m_generator = RandomGenerator();

  REGISTER_SCRIPT(TypingTextEffect, 1)

  //------------------------------------------------------------------------------------------------
  TypingTextEffect::TypingTextEffect() :
    m_textBox(),
    m_currentTimer(0),
    m_nextTimer(0),
    m_text(),
    m_currentLine(0),
    m_keyPressSoundPaths { Path("KeyPresses", "KeyPress1.wav"), Path("KeyPresses", "KeyPress2.wav"), Path("KeyPresses", "KeyPress3.wav") },
    m_keyPressAudio()
  {
    m_keyPressAudio.reserve(m_keyPressSoundPaths.size());
  }

  //------------------------------------------------------------------------------------------------
  TypingTextEffect::~TypingTextEffect()
  {
  }

  //------------------------------------------------------------------------------------------------
  void TypingTextEffect::onSetGameObject(const Handle<GameObject>& gameObject)
  {
    Inherited::onSetGameObject(gameObject);

    m_nextTimer = m_generator.generate(0.1f, 0.5f);
    m_textBox = gameObject->findComponent<TextBox>();

    for (const Path& path : m_keyPressSoundPaths)
    {
      m_keyPressAudio.push_back(AudioSource::create(gameObject, path));
    }
  }

  //------------------------------------------------------------------------------------------------
  void TypingTextEffect::onUpdate(GLfloat elapsedGameTime)
  {
    Inherited::onUpdate(elapsedGameTime);

    if (m_textBox.is_null() || m_text.empty())
    {
      ASSERT_FAIL();
      return;
    }

    m_currentTimer += elapsedGameTime;
    if (m_currentTimer >= m_nextTimer)
    {
      size_t index = m_textBox->getTextRenderer()->getLineLength(0);
      m_currentTimer = 0;
      m_nextTimer = (index == m_text[m_currentLine].size() - 1) ? 2 : m_generator.generate(0.1f, 0.5f);  // Creates pause after final letter

      if (index == m_text.size())
      {
        // Reset with new line of text
        m_currentLine = m_generator.generate(0, m_text.size() - 1);
        m_textBox->getTextRenderer()->resetLines(m_text[m_currentLine]);
        m_textBox->setLetterIndex(0);
      }
      else
      {
        m_textBox->getTextRenderer()->addLetter(0, index, m_text[m_currentLine][index]);
        m_textBox->setLetterIndex(index + 1);
        
        if (!m_keyPressAudio.empty())
        {
          m_keyPressAudio[m_generator.generate(0, m_keyPressAudio.size() - 1)]->play();
        }
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void TypingTextEffect::onDeath()
  {
    Inherited::onDeath();

    m_textBox.reset();
    m_currentTimer = 0;
    m_nextTimer = 0;
    m_text.clear();
    m_currentLine = 0;
    m_keyPressAudio.clear();
  }

  //------------------------------------------------------------------------------------------------
  Handle<TypingTextEffect> TypingTextEffect::create(const Handle<GameObject>& gameObject, const std::vector<std::string>& text)
  {
    if (gameObject.is_null())
    {
      ASSERT_FAIL();
      return;
    }

    const Handle<TypingTextEffect>& typingTextEffect = gameObject->addComponent<TypingTextEffect>();
    typingTextEffect->setText(text);

    return typingTextEffect;
  }
}
#include "stdafx.h"

#include "UI/MainMenuTitleEffect.h"
#include "Objects/GameObject.h"
#include "Resources/ResourceManager.h"

using namespace CelesteEngine;
using namespace CelesteEngine::UI;
using namespace CelesteEngine::Audio;


namespace HW
{
  std::string MainMenuTitleEffect::m_text = "Hello World";
  RandomGenerator MainMenuTitleEffect::m_generator = RandomGenerator();

  REGISTER_SCRIPT(MainMenuTitleEffect, 1)

  //------------------------------------------------------------------------------------------------
  MainMenuTitleEffect::MainMenuTitleEffect() :
    m_textBox(),
    m_currentTimer(0),
    m_nextTimer(0),
    m_keyPressSoundPaths { Path("KeyPresses", "KeyPress1.wav"), Path("KeyPresses", "KeyPress2.wav"), Path("KeyPresses", "KeyPress3.wav") },
    m_keyPressAudio()
  {
    m_keyPressAudio.reserve(m_keyPressSoundPaths.size());
  }

  //------------------------------------------------------------------------------------------------
  MainMenuTitleEffect::~MainMenuTitleEffect()
  {
  }

  //------------------------------------------------------------------------------------------------
  void MainMenuTitleEffect::onSetGameObject(const Handle<GameObject>& gameObject)
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
  void MainMenuTitleEffect::onUpdate(GLfloat elapsedGameTime)
  {
    Inherited::onUpdate(elapsedGameTime);

    if (m_textBox.is_null())
    {
      ASSERT_FAIL();
      return;
    }

    m_currentTimer += elapsedGameTime;
    if (m_currentTimer >= m_nextTimer)
    {
      m_currentTimer = 0;
      m_nextTimer = m_generator.generate(0.1f, 0.5f);

      size_t index = m_textBox->getTextRenderer()->getLineLength(0);
      if (index == m_text.size())
      {
        m_textBox->getTextRenderer()->resetLines();
        m_textBox->setLetterIndex(0);
      }
      else
      {
        m_textBox->getTextRenderer()->addLetter(0, index, m_text[index]);
        m_textBox->setLetterIndex(index + 1);
        
        if (index == m_text.size() - 1)
        {
          // Extend time for whole title
          m_nextTimer = 2;
        }

        if (!m_keyPressAudio.empty())
        {
          m_keyPressAudio[m_generator.generate(0, m_keyPressAudio.size() - 1)]->play();
        }
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void MainMenuTitleEffect::onDeath()
  {
    Inherited::onDeath();

    m_textBox.reset();
    m_keyPressAudio.clear();
  }
}
#include "stdafx.h"

#include "UI/MainMenuTitleEffect.h"
#include "Objects/GameObject.h"
#include "Maths/RandomGenerator.h"

using namespace CelesteEngine;
using namespace CelesteEngine::UI;


namespace HW
{
  std::string MainMenuTitleEffect::m_text = "Hello World";

  REGISTER_SCRIPT(MainMenuTitleEffect, 1)

  //------------------------------------------------------------------------------------------------
  MainMenuTitleEffect::MainMenuTitleEffect() :
    m_textBox(),
    m_currentTimer(0),
    m_nextTimer(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  MainMenuTitleEffect::~MainMenuTitleEffect()
  {
  }

  //------------------------------------------------------------------------------------------------
  void MainMenuTitleEffect::onSetGameObject(const Handle<GameObject>& gameObject)
  {
    Inherited::onSetGameObject(gameObject);

    m_textBox = gameObject->findComponent<TextBox>();
    m_nextTimer = RandomGenerator().generate(0.5f, 2);
  }

  //------------------------------------------------------------------------------------------------
  void MainMenuTitleEffect::onUpdate(GLfloat elapsedGameTime)
  {
    Inherited::onUpdate(elapsedGameTime);

    m_currentTimer += elapsedGameTime;
    if (m_currentTimer >= m_nextTimer)
    {
      m_currentTimer = 0;
      m_nextTimer = RandomGenerator().generate(0.25f, 1);

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
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void MainMenuTitleEffect::onDeath()
  {
    Inherited::onDeath();

    m_textBox.reset();
  }
}
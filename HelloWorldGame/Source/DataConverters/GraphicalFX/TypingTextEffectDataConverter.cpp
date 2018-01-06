#include "stdafx.h"

#include "DataConverters/GraphicalFX/TypingTextEffectDataConverter.h"


namespace HW
{
  REGISTER_COMPONENT_DATA_CONVERTER(TypingTextEffectDataConverter);

  //------------------------------------------------------------------------------------------------
  TypingTextEffectDataConverter::TypingTextEffectDataConverter() :
    m_text(AttributeName("text"), "", kRequired),
    m_delay(AttributeName("delay"), 0.3f),
    m_typeSpeedVariation(AttributeName("variation"), 0.2f)
  {
    addAttribute(&m_text);
    addAttribute(&m_delay);
    addAttribute(&m_typeSpeedVariation);
  }

  //------------------------------------------------------------------------------------------------
  void TypingTextEffectDataConverter::doSetValues(const Handle<TypingTextEffect>& typingTextEffect) const
  {
    typingTextEffect->setText(getText());
    typingTextEffect->setDelay(getDelay());
    typingTextEffect->setTypeSpeedVariation(getTypeSpeedVariation());
  }
}
#pragma once

#include "DataConverters/Objects/ComponentDataConverter.h"
#include "XML/Attributes/StringAttribute.h"
#include "XML/Attributes/FloatAttribute.h"
#include "GraphicalFX/TypingTextEffect.h"


namespace HW
{

class TypingTextEffectDataConverter : public CelesteEngine::ComponentDataConverter
{
  DECLARE_COMPONENTDATA_CONVERTER(TypingTextEffect)

  public:
    TypingTextEffectDataConverter();

    const std::string& getText() const { return m_text.getValue(); }
    const std::string& getTextXMLName() const { return m_text.getAttributeName(); }

    float getDelay() const { return m_delay.getValue(); }
    const std::string& getDelayXMLName() const { return m_delay.getAttributeName(); }

    float getTypeSpeedVariation() const { return m_typeSpeedVariation.getValue(); }
    const std::string& getTypeSpeedVariationXMLName() const { return m_typeSpeedVariation.getAttributeName(); }

  private:
    typedef CelesteEngine::ComponentDataConverter Inherited;

    StringAttribute m_text;
    FloatAttribute m_delay;
    FloatAttribute m_typeSpeedVariation;
};

}
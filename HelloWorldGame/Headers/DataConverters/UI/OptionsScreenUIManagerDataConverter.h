#pragma once

#include "DataConverters/Objects/ComponentDataConverter.h"
#include "UI/OptionsScreenUIManager.h"


namespace HW
{

class OptionsScreenUIManagerDataConverter : public CelesteEngine::ComponentDataConverter<OptionsScreenUIManager>
{
  DECLARE_COMPONENT_DATA_CONVERTER(OptionsScreenUIManagerDataConverter, OptionsScreenUIManager, "OptionsScreenUIManager")
};

}
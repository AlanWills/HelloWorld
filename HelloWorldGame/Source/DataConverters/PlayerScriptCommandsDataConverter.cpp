#include "stdafx.h"

#include "DataConverters/PlayerScriptCommandsDataConverter.h"
#include "Resources/Data.h"


namespace HW
{
  namespace DataConverters
  {
    //------------------------------------------------------------------------------------------------
    PlayerScriptCommandsDataConverter::PlayerScriptCommandsDataConverter(const ConstHandle<Data>& dataFile) :
      Inherited(dataFile)
    {
    }

    //------------------------------------------------------------------------------------------------
    PlayerScriptCommandsDataConverter::PlayerScriptCommandsDataConverter(const XMLElement* element) :
      Inherited(element)
    {
    }

    //------------------------------------------------------------------------------------------------
    void PlayerScriptCommandsDataConverter::load(const tinyxml2::XMLElement* element)
    {
      if (element == nullptr)
      {
        ASSERT_FAIL();
        return;
      }

      // Iterate through all elements under the root and add their tag name to the commands list
      // Do not worry about duplicates - they will be sorted out when the player script commands are set using these names

    }
  }
}
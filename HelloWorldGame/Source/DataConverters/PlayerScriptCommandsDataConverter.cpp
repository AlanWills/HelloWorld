#include "stdafx.h"

#include "DataConverters/PlayerScriptCommandsDataConverter.h"
#include "Resources/Data.h"
#include "Code/ScriptCommandsRegistry.h"
#include "Resources/ResourceManager.h"


namespace HW
{
  using namespace Code;

  namespace DataConverters
  {
    //------------------------------------------------------------------------------------------------
    PlayerScriptCommandsDataConverter::PlayerScriptCommandsDataConverter(const Path& dataFilePath) :
      PlayerScriptCommandsDataConverter(getResourceManager()->load<Data>(dataFilePath).as_const())
    {
    }

    //------------------------------------------------------------------------------------------------
    PlayerScriptCommandsDataConverter::PlayerScriptCommandsDataConverter(const ConstHandle<Data>& dataFile) :
      Inherited(dataFile)
    {
      if (dataFile.is_null())
      {
        ASSERT_FAIL();
        return;
      }

      load(dataFile->getDocumentRoot());
    }

    //------------------------------------------------------------------------------------------------
    PlayerScriptCommandsDataConverter::PlayerScriptCommandsDataConverter(const XMLElement* element) :
      Inherited(element)
    {
      load(element);
    }

    //------------------------------------------------------------------------------------------------
    void PlayerScriptCommandsDataConverter::load(const tinyxml2::XMLElement* element)
    {
      if (element == nullptr)
      {
        ASSERT_FAIL();
        return;
      }

      // Iterate through all elements under the root and add their text and function pointer to the commands map
      for (const XMLElement* commandElement : children(element, "Command"))
      {
        const std::string& name = commandElement->GetText();
        if (m_commands.find(name) != m_commands.end())
        {
          continue;
        }

        if (!ScriptCommandsRegistry::hasCommand(name))
        {
          ASSERT_FAIL();
          continue;
        }

        // Add name and function to the map
        m_commands.emplace(name, ScriptCommandsRegistry::getCommand(name));
      }
    }
  }
}
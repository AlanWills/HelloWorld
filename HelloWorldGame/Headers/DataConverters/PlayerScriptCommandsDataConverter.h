#pragma once

#include "DataConverters/DataConverter.h"
#include "Code/ScriptCommandDefs.h"
#include "Memory/ConstHandle.h"


namespace CelesteEngine
{
  class Data;
}

namespace HW
{
  namespace DataConverters
  {
    class PlayerScriptCommandsDataConverter : CelesteEngine::DataConverter
    {
      public:
        PlayerScriptCommandsDataConverter(const Path& dataFilePath);
        PlayerScriptCommandsDataConverter(const CelesteEngine::ConstHandle<CelesteEngine::Data>& dataFile);
        PlayerScriptCommandsDataConverter(const tinyxml2::XMLElement* element);

        const Code::ScriptCommands& getCommands() const { return m_commands; }

      private:
        typedef CelesteEngine::DataConverter Inherited;

        void load(const tinyxml2::XMLElement* element);

        Code::ScriptCommands m_commands;
    };
  }
}
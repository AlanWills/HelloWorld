#pragma once

#include "DataConverters/DataConverter.h"
#include "Code/ScriptCommandDefs.h"


namespace HW
{
  namespace DataConverters
  {
    class PlayerScriptCommandsDataConverter : CelesteEngine::DataConverter
    {
      public:
        PlayerScriptCommandsDataConverter(const CelesteEngine::ConstHandle<CelesteEngine::Data>& dataFile);
        PlayerScriptCommandsDataConverter(const tinyxml2::XMLElement* element);

        const std::vector<Code::ScriptCommand>& getCommands() const { return m_commands; }

      private:
        typedef CelesteEngine::DataConverter Inherited;

        void load(const tinyxml2::XMLElement* element);

        std::vector<Code::ScriptCommand> m_commands;
    };
  }
}
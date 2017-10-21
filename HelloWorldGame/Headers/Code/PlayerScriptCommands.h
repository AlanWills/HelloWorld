#pragma once

#include "ScriptCommandDefs.h"


namespace HW
{
  namespace Code
  {
    class PlayerScriptCommands
    {
      public:
        static PlayerScriptCommands& instance()
        {
          static PlayerScriptCommands instance;
          return instance;
        }

        void load();
        void loadAsync();

        void addCommand(const std::string& name, const ScriptCommand& command) { m_commands.insert_or_assign(name, command); }
        bool hasCommand(const std::string& name) const { return m_commands.find(name) != m_commands.end(); }
        void invokeCommand(const std::string& name, const ArgList& args) const;

      private:
        PlayerScriptCommands();
        PlayerScriptCommands(const PlayerScriptCommands&) = delete;

        void operator=(const PlayerScriptCommands&) = delete;

        ScriptCommands m_commands;
    };
  }
}
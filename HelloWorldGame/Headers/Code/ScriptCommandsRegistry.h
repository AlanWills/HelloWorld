#pragma once

#include "ScriptCommandDefs.h"


namespace HW
{
  namespace Code
  {
    class ScriptCommandsRegistry
    {
      public:
        ScriptCommandsRegistry() = delete;
        ScriptCommandsRegistry(const ScriptCommandsRegistry&) = delete;
        ~ScriptCommandsRegistry() = delete;

        void operator=(const ScriptCommandsRegistry&) = delete;

        static bool hasCommand(const std::string& name) { return m_commands.find(name) != m_commands.end(); }

        /// I got errors when returning a reference, so try generate a copy for now
        /// Could be that we need to rethink the storage here
        static ScriptCommand getCommand(const std::string& name) { return hasCommand(name) ? m_commands.at(name) : nullptr; }

        static void listObjects() { }

      private:
        static ScriptCommands m_commands;
    };
  }
}
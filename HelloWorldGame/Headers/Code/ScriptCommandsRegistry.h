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

      private:
        static ScriptCommands m_commands;
    };
  }
}
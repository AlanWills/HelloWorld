#include "stdafx.h"

#include "Code/ScriptCommandsRegistry.h"


namespace HW
{
  namespace Code
  {
    // Initialize static registry of function lookups here
    ScriptCommands ScriptCommandsRegistry::m_commands = ScriptCommands
    {
      { "listObjects", std::bind(&ScriptCommandsRegistry::listObjects) }
    };
  }
}
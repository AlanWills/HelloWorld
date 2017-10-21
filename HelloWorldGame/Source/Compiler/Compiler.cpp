#include "stdafx.h"

#include "Compiler/Compiler.h"
#include "Objects/GameObject.h"
#include "Screens/ScreenManager.h"
#include "Screens/Levels/Level1.h"
#include "Code/PlayerScriptCommands.h"


using namespace CelesteEngine;

namespace HW
{
  using namespace Code;

  namespace Compiler
  {
    //------------------------------------------------------------------------------------------------
    void run(const std::string& code)
    {
      if (code.substr(0, 11) == "killObject(")
      {
        std::string& name = code.substr(11, code.size() - 12);
        if (PlayerScriptCommands::instance().hasCommand("killObject"))
        {
          PlayerScriptCommands::instance().invokeCommand("killObject", ArgList { { "name", static_cast<void*>(&name) } });
        }
        else
        {
          ASSERT_FAIL();
        }
      }
      else
      {
        ASSERT_FAIL();
      }
    }
  }
}
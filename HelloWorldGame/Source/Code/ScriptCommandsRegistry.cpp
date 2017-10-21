#include "stdafx.h"

#include "Code/ScriptCommandsRegistry.h"
#include "Objects/GameObject.h"
#include "Screens/ScreenManager.h"


namespace HW
{
  namespace Code
  {
    // Initialize static registry of function lookups here
    ScriptCommands ScriptCommandsRegistry::m_commands = ScriptCommands
    {
      { "listObjects", std::bind(&ScriptCommandsRegistry::listObjects, std::placeholders::_1) },
      { "killObject", std::bind(&ScriptCommandsRegistry::killObject, std::placeholders::_1) }
    };

    //------------------------------------------------------------------------------------------------
    void ScriptCommandsRegistry::killObject(const ArgList& args)
    {
      if (args.find("name") == args.end())
      {
        ASSERT_FAIL();
        return;
      }

      std::string* name = static_cast<std::string*>(args.at("name"));

      const Handle<GameObject>& gameObject = getScreenManager()->findScreen("LevelScreen")->findGameObjectWithName(*name);
      if (!gameObject.is_null())
      {
        gameObject->die();
      }
    }
  }
}
#include "stdafx.h"

#include "Compiler/Compiler.h"
#include "Objects/GameObject.h"
#include "Screens/ScreenManager.h"
#include "Screens/Levels/Level1.h"


using namespace CelesteEngine;

namespace HW
{
  namespace Compiler
  {
    //------------------------------------------------------------------------------------------------
    void run(const std::string& code, std::vector<std::string>& output)
    {
      std::string subStr = code.substr(2);

      if (subStr == "listObjects()")
      {
        std::vector<Handle<GameObject>> namedObjects;
        getScreenManager()->findScreen("LevelScreen")->findGameObjects([](const GameObject* gameObject) -> bool
        {
          return gameObject->getName() != 0;
        }, namedObjects);

        for (const Handle<GameObject>& gameObject : namedObjects)
        {
          output.push_back(deinternString(gameObject->getName()));
        }
      }
      else if (subStr.substr(0, 11) == "killObject(")
      {
        const std::string& name = subStr.substr(11, subStr.size() - 12);
        const Handle<GameObject>& gameObject = getScreenManager()->findScreen("LevelScreen")->findGameObjectWithName(name);
        if (!gameObject.is_null())
        {
          gameObject->die();
        }
        else
        {
          output.push_back(name + " does not exist");
        }
      }
      else
      {
        output.push_back("Unrecognized command");
      }
    }
  }
}
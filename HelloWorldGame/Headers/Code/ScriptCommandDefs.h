#pragma once

#include <unordered_map>
#include <functional>


namespace HW
{
  namespace Code
  {
    typedef std::unordered_map<std::string, void*> ArgList;
    typedef std::function<void(const ArgList&)> ScriptCommand;
    typedef std::unordered_map<std::string, ScriptCommand> ScriptCommands;
  }
}
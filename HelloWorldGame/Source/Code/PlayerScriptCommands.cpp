#include "stdafx.h"

#include "Code/PlayerScriptCommands.h"
#include "DataConverters/PlayerScriptCommandsDataConverter.h"

#include <future>


namespace HW
{
  namespace Code
  {
    //------------------------------------------------------------------------------------------------
    PlayerScriptCommands::PlayerScriptCommands() :
      m_commands()
    {
    }

    //------------------------------------------------------------------------------------------------
    void PlayerScriptCommands::load()
    {
      m_commands = std::move(DataConverters::PlayerScriptCommandsDataConverter(Path("Player", "PlayerScriptCommands.xml")).getCommands());
    }

    //------------------------------------------------------------------------------------------------
    void PlayerScriptCommands::loadAsync()
    {
      std::async(std::launch::async, [this]() -> void
      {
        load();
      });
    }

    //------------------------------------------------------------------------------------------------
    void PlayerScriptCommands::invokeCommand(const std::string& name, const ArgList& args) const
    {
      if (hasCommand(name))
      {
        m_commands.at(name)(args);
      }
    }
  }
}
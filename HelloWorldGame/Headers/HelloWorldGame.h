#pragma once

#include "Game/Game.h"


namespace HW
{

class HelloWorldGame : public Game
{
  public:
    HelloWorldGame() { }

  protected:
    void onInitialize() override;

  private:
    typedef Game Inherited;
};

}
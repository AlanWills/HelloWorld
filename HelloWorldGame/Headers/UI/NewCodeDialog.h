#pragma once

#include "Memory/Handle.h"
#include "Objects/GameObject.h"

#include <string>

using namespace CelesteEngine;


namespace HW
{
  class LevelScreenCreator;

  namespace UI
  {
    namespace NewCodeDialog
    {
      void show(const LevelScreenCreator& screenCreator);
    }
  }
}
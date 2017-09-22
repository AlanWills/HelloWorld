#pragma once

#include "Objects/Script.h"


namespace CelesteEngine
{
  namespace UI
  {
    class TextBox;
  }
}

namespace HW
{
  namespace Input
  {
    class TerminalInputHandler : public CelesteEngine::Script
    {
      DECLARE_SCRIPT(TerminalInputHandler)

      public:
        void setActive(bool isActive) override;

      protected:
        void onSetGameObject(const Handle<GameObject>& gameObject) override;
        void onDeath() override;

      private:
        typedef CelesteEngine::Script Inherited;

        void onKeyDown(int key);

        Handle<CelesteEngine::UI::TextBox> m_terminalTextBox;
        StringId m_eventName;
    };
  }
}
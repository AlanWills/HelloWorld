#pragma once

#include "Objects/Script.h"


namespace CelesteEngine
{
  namespace UI
  {
    class TextBox;
  }

  namespace Rendering
  {
    class TextRenderer;
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

        Handle<CelesteEngine::UI::TextBox> m_terminalTextBox;
        Handle<CelesteEngine::Rendering::TextRenderer> m_terminalOutput;
    };
  }
}
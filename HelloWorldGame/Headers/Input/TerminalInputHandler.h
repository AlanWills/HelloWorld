#pragma once

#include "Objects/Script.h"
#include "Rendering/TextRenderer.h"
#include "Events/Event.h"


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
        const Handle<Rendering::TextRenderer>& getTextRenderer() { return m_textRenderer; }
        ConstHandle<Rendering::TextRenderer> getTextRenderer() const { return m_textRenderer.as_const(); }

        void setActive(bool isActive) override;
        void setLetterIndex(size_t newIndex);

      protected:
        void onInitialize() override;
        void onSetGameObject(const Handle<GameObject>& gameObject) override;
        void onDeath() override;

      private:
        typedef CelesteEngine::Script Inherited;

        void onTextInputtedCallback(EventArgs& e, char character);
        void onKeyPressedCallback(EventArgs& e, int keyPressed);

        Handle<Rendering::TextRenderer> m_textRenderer;
        Handle<GameObject> m_caret;
        StringId m_textInputtedEventHandle;
        StringId m_keyDownEventHandle;

        size_t m_letterIndex;
    };
  }
}
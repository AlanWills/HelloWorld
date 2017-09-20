#pragma once

#include "Objects/Script.h"


namespace HW
{
  namespace Input
  {
    class TerminalActivationHandler : public Script
    {
      DECLARE_SCRIPT(TerminalActivationHandler)

      public:
        int getActivationKey() const { return m_activationKey; }
        void setActivationKey(int activationKey) { m_activationKey = activationKey; }

        int getDeactivationKey() const { return m_deactivationKey; }
        void setDeactivationKey(int deactivationKey) { m_deactivationKey = deactivationKey; }

        //------------------------------------------------------------------------------------------------
        static Handle<TerminalActivationHandler> create(const Handle<GameObject>& gameObject, int activationKey, int deactivationKey);

      protected:
        void onHandleInput() override;
        void onDeath() override;

      private:
        typedef Script Inherited;

        int m_activationKey;
        int m_deactivationKey;
    };
  }
}
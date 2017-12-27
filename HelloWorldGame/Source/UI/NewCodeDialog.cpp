#include "stdafx.h"

#include "UI/NewCodeDialog.h"
#include "UI/Button.h"
#include "Animation/Animators/ChangeScaleAnimator.h"
#include "Animation/Animators/MoveToPositionAnimator.h"
#include "Screens/ScreenManager.h"

using namespace CelesteEngine::Animators;
using namespace CelesteEngine::UI;


namespace HW
{
  namespace UI
  {
    REGISTER_SCREEN_CREATOR(NewCodeDialog, "NewCodeDialog")

    //------------------------------------------------------------------------------------------------
    NewCodeDialog::NewCodeDialog(const Handle<Screen>& screen, const std::string& name) :
      Inherited(screen, name)
    {
    }

    //------------------------------------------------------------------------------------------------
    void NewCodeDialog::showModal(const std::string& text)
    {
      // Hacky - improve this somehow
      getScreenManager()->findScreen("LevelScreen")->setActive(false);

      NewCodeDialog dialog(Screen::allocate(), "NewCodeDialog");
      const glm::vec2& viewportDimensions = dialog.getViewportDimensions();

      const glm::vec2& dialogSize = viewportDimensions * 0.4f;
      const Handle<GameObject>& dialogGrouper = dialog.createGameObject(kGUI, glm::vec3(viewportDimensions * 0.5f, 0.2f), "DialogGrouper");
      dialogGrouper->getTransform()->setScale(glm::vec3(0, 0, 1));
      SpriteRenderer::create(dialogGrouper, Path("Sprites", "UI", "Rectangle.png"), dialogSize, glm::vec4(0, 0, 0, 1));
      const Handle<ChangeScaleAnimator>& dialogAnimator = dialogGrouper->addComponent<ChangeScaleAnimator>();
      dialogAnimator->setTime(0.75f);
      dialogAnimator->setTargetScale(glm::vec3(1, 1, 1));

      const Handle<GameObject>& title = dialog.createGameObject(kGUI, glm::vec3(0, 0, 0.01f), "DialogTitle", dialogGrouper);
      TextRenderer::create(title, "New Code!", 30, Horizontal::kCentre, Vertical::kTop);
      const Handle<MoveToPositionAnimator>& titleAnimator = title->addComponent<MoveToPositionAnimator>();
      titleAnimator->setTime(0.75f);
      titleAnimator->setTargetPosition(glm::vec3(0, dialogSize.y * 0.5f - 10, 0.01f));

      const Handle<GameObject>& textObject = dialog.createGameObject(kGUI, glm::vec3(0, 0, 0.01f), "DialogText", dialogGrouper);
      TextRenderer::create(textObject, text, 22, Horizontal::kCentre, Vertical::kCentre);

      const Handle<GameObject>& closeButton = dialog.createGameObject(kGUI, glm::vec3(0, 0, 0.01f), "DialogText", dialogGrouper);
      Button::create(closeButton, "Close", [](EventArgs& e, const Handle<GameObject>& gameObject) -> void
      {
        gameObject->getOwnerScreen()->die();
        getScreenManager()->findScreen("LevelScreen")->setActive(true);
      });
      const glm::vec2& dimensions = closeButton->findComponent<SpriteRenderer>()->getDimensions();
      const Handle<MoveToPositionAnimator>& closeButtonAnimator = closeButton->addComponent<MoveToPositionAnimator>();
      closeButtonAnimator->setTime(0.75f);
      closeButtonAnimator->setTargetPosition(glm::vec3(dialogSize.x * 0.5f - dimensions.x * 0.75f, dimensions.y * 0.75f - dialogSize.y * 0.5f, 0.01f));
    }
  }
}
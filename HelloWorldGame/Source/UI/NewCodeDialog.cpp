#include "stdafx.h"

#include "UI/NewCodeDialog.h"


namespace HW
{
  namespace UI
  {
    namespace NewCodeDialog
    {
      //------------------------------------------------------------------------------------------------
      void show()
      {
        // Create new screen and deactivate current screen
        // Show dialog modally
        // Use screen creator
        // Move headers from Level1 which we don't need any more




        const glm::vec2& dialogSize = viewportDimensions * 0.6f;
        const Handle<GameObject>& dialogGrouper = level1.createGameObject(kGUI, glm::vec3(viewportDimensions * 0.5f, 0.2f), "DialogGrouper");
        dialogGrouper->getTransform()->setScale(glm::vec3(0, 0, 1));
        SpriteRenderer::create(dialogGrouper, Path("Sprites", "UI", "Rectangle.png"), dialogSize, glm::vec4(0, 0, 0, 1));
        const Handle<ChangeScaleAnimator>& dialogAnimator = dialogGrouper->addComponent<ChangeScaleAnimator>();
        dialogAnimator->setTime(0.75f);
        dialogAnimator->setTargetScale(glm::vec3(1, 1, 1));

        const Handle<GameObject>& title = level1.createGameObject(kGUI, glm::vec3(0, 0, 0.01f), "DialogTitle", dialogGrouper);
        TextRenderer::create(title, "New Code!", 30, Horizontal::kCentre, Vertical::kTop);
        const Handle<MoveToPositionAnimator>& titleAnimator = title->addComponent<MoveToPositionAnimator>();
        titleAnimator->setTime(0.75f);
        titleAnimator->setTargetPosition(glm::vec3(0, dialogSize.y * 0.5f - 10, 0.01f));

        const Handle<GameObject>& text = level1.createGameObject(kGUI, glm::vec3(0, 0, 0.01f), "DialogText", dialogGrouper);
        TextRenderer::create(text, "Use listObjects() to find the names of all the objects in the scene", 22, Horizontal::kCentre, Vertical::kCentre);

        const Handle<GameObject>& closeButton = level1.createGameObject(kGUI, glm::vec3(0, 0, 0.01f), "DialogText", dialogGrouper);
        Button::create(closeButton, "Close", [](const Handle<GameObject>& gameObject) -> void
        {
          gameObject->getParent()->setActive(false);
          gameObject->getParent()->setShouldRender(false);
        });
        const glm::vec2& dimensions = closeButton->findComponent<SpriteRenderer>()->getDimensions();
        const Handle<MoveToPositionAnimator>& closeButtonAnimator = closeButton->addComponent<MoveToPositionAnimator>();
        closeButtonAnimator->setTime(0.75f);
        closeButtonAnimator->setTargetPosition(glm::vec3(dialogSize.x * 0.5f - dimensions.x * 0.75f, dimensions.y * 0.75f - dialogSize.y * 0.5f, 0.01f));
      }
    }
  }
}
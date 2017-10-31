#include "stdafx.h"

#include "Screens/Levels/Level3.h"
#include "Screens/Screen.h"
#include "Animation/Animation.h"


namespace HW
{
  using namespace Physics;

  REGISTER_SCREEN_CREATOR(Level3, "LevelScreen")

  //------------------------------------------------------------------------------------------------
  Level3::Level3(const Handle<Screen>& screen, const std::string& name) :
    Inherited(screen, name)
  {
  }

  //------------------------------------------------------------------------------------------------
  void Level3::create()
  {
    Level3 level(Screen::allocate());

    const glm::vec2& viewportDimensions = level.getViewportDimensions();

    const Handle<GameObject>& mineIdle = level.createGameObject(kWorld, viewportDimensions * 0.5f, "MineIdle");
    mineIdle->getTransform()->setScale(5, 5);
    mineIdle->addComponent<SpriteRenderer>();
    const Handle<Animation>& idleAnimation = Animation::create(mineIdle, "MineIdle", Animation::kLooping, Path("Animations", "MineIdle.xml"));
    idleAnimation->restart();
    idleAnimation->resume();

    const Handle<GameObject>& mineExplosion = level.createGameObject(kWorld, viewportDimensions * 0.5f, "MineIdle");
    mineExplosion->getTransform()->translate(100, 0);
    mineExplosion->getTransform()->setScale(5, 5);
    mineExplosion->addComponent<SpriteRenderer>();
    const Handle<Animation>& explosionAnimation = Animation::create(mineExplosion, "MineExplosion", Animation::kLooping, Path("Animations", "MineExplosion.xml"));
    explosionAnimation->restart();
    explosionAnimation->resume();
  }
}
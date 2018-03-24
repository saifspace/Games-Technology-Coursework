#include <stdlib.h>
#include "GameUtil.h"
#include "Asteroid.h"
#include "BoundingShape.h"
#include "BoundingSphere.h"
#include "Animation.h"
#include "AnimationManager.h"
#include <algorithm>

using namespace std;

Asteroid::Asteroid(void) : GameObject("Asteroid")
{
	mAngle = rand() % 360;
	mRotation = rand() % 90;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;
	mVelocity.x = 10.0 * cos(DEG2RAD*mAngle);
	mVelocity.y = 10.0 * sin(DEG2RAD*mAngle);
	mVelocity.z = 0.0;
}

Asteroid::Asteroid(char const * const type_name) : GameObject(type_name)
{
	mAngle = rand() % 360;
	mRotation = rand() % 90;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;
	mVelocity.x = 10.0 * cos(DEG2RAD*mAngle);
	mVelocity.y = 10.0 * sin(DEG2RAD*mAngle);
	mVelocity.z = 0.0;
}

Asteroid::~Asteroid(void)
{
}

bool Asteroid::CollisionTest(shared_ptr<GameObject> o)
{
	if (GetType() == o->GetType()) return false;
	if (o->GetType() == GameObjectType("Asteroid") || o->GetType() == GameObjectType("MiniAsteroid")) return false;
	if (o->GetType() == GameObjectType("BulletPowerUp")) return false;
	if (o->GetType() == GameObjectType("ShieldPowerUp")) return false;
	if (o->GetType() == GameObjectType("AlienShip")) return false;
	if (o->GetType() == GameObjectType("EnemyBullet")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Asteroid::OnCollision(const GameObjectList& objects)
{
	bool powerBullet = objects.front().get()->GetType() == GameObjectType("PowerBullet");

	mWorld->FlagForRemoval(GetThisPtr());
	
	if (GetThisPtr()->GetType() == GameObjectType("Asteroid") && powerBullet == false) {
		CreateMiniAsteroids();
	}
	
}

void Asteroid::CreateMiniAsteroids() {
	for (int i = 0; i < 2; i++) {

		Animation *anim_ptr = AnimationManager::GetInstance().GetAnimationByName("asteroid1");
		shared_ptr<Sprite> asteroid_sprite
			= make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
		asteroid_sprite->SetLoopAnimation(true);
		shared_ptr<GameObject> nAsteroid = make_shared<Asteroid>("MiniAsteroid");
		nAsteroid->SetPosition(GetThisPtr()->GetPosition());
		nAsteroid->SetScale(0.1f);
		nAsteroid->SetBoundingShape(make_shared<BoundingSphere>(nAsteroid->GetThisPtr(), 5.0f));
		nAsteroid->SetSprite(asteroid_sprite);
		mWorld->AddObject(nAsteroid);
	}

}

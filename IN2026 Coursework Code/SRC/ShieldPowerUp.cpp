#include "ShieldPowerUp.h"
#include "GameUtil.h"
#include "BoundingShape.h"
#include "BoundingSphere.h"

ShieldPowerUp::ShieldPowerUp(void) : GameObject("ShieldPowerUp") {
	mAngle = rand() % 360;
	mRotation = rand() % 90;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;
	mVelocity.x = 10.0 * cos(DEG2RAD*mAngle);
	mVelocity.y = 10.0 * sin(DEG2RAD*mAngle);
	mVelocity.z = 0.0;
}

ShieldPowerUp::~ShieldPowerUp(void) {}

bool ShieldPowerUp::CollisionTest(shared_ptr<GameObject> o) {

	if (GetType() == o->GetType()) return false;
	if (o->GetType() == GameObjectType("Asteroid")) return false;
	if (o->GetType() == GameObjectType("MiniAsteroid")) return false;
	if (o->GetType() == GameObjectType("Bullet")) return false;
	if (o->GetType() == GameObjectType("PowerBullet")) return false;
	if (o->GetType() == GameObjectType("BulletPowerUp")) return false;
	if (o->GetType() == GameObjectType("AlienShip")) return false;
	if (o->GetType() == GameObjectType("EnemyBullet")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());

}

void ShieldPowerUp::OnCollision(const GameObjectList& objects) {
	mWorld->FlagForRemoval(GetThisPtr());
}
#include <stdlib.h>
#include "GameUtil.h"
#include "BulletPowerup.h"
#include "BoundingShape.h"
#include "BoundingSphere.h"

BulletPowerUp::BulletPowerUp(void) : GameObject("BulletPowerUp") {
	mAngle = rand() % 360;
	mRotation = rand() % 90;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	//mPosition.z = 0.0;
	mVelocity.x = 10.0 * cos(DEG2RAD*mAngle);
	mVelocity.y = 10.0 * sin(DEG2RAD*mAngle);
	mVelocity.z = 0.0;
}

BulletPowerUp::~BulletPowerUp(void){}

bool BulletPowerUp::CollisionTest(shared_ptr<GameObject> o) {
	
	if (GetType() == o->GetType()) return false;
	if (o->GetType() == GameObjectType("Asteroid")) return false;
	if (o->GetType() == GameObjectType("MiniAsteroid")) return false;
	if (o->GetType() == GameObjectType("Bullet")) return false;
	if (o->GetType() == GameObjectType("PowerBullet")) return false;
	if (o->GetType() == GameObjectType("ShieldPowerUp")) return false;
	if (o->GetType() == GameObjectType("AlienShip")) return false;
	if (o->GetType() == GameObjectType("EnemyBullet")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());

}

void BulletPowerUp::OnCollision(const GameObjectList& objects) {
	mWorld->FlagForRemoval(GetThisPtr());
}

void BulletPowerUp::Render(void) {
		// Disable lighting for solid colour lines
		glDisable(GL_LIGHTING);
		// Start drawing lines
		glBegin(GL_LINE_LOOP);
		// Set colour to grey
		glColor3f(0.6, 0, 0);
		// Add vertices to draw an octagon
		glVertex3f(-7, -7, 0.0);
		glVertex3f(-10, 0, 0.0);
		glVertex3f(-7, 7, 0.0);
		glVertex3f(0, 10, 0.0);
		glVertex3f(7, 7, 0.0);
		glVertex3f(10, 0, 0.0);
		glVertex3f(7, -7, 0.0);
		glVertex3f(0, -10, 0.0);
		// Finish drawing lines
		glEnd();
		// Enable lighting
		glEnable(GL_LIGHTING);
}

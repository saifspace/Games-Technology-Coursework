#include <stdlib.h>
#include "GameUtil.h"
#include "Asteroid.h"
#include "BoundingShape.h"
#include "BoundingSphere.h"

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
	if (o->GetType() == GameObjectType("Asteroid") || o->GetType() == GameObjectType("miniAsteroid")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Asteroid::OnCollision(const GameObjectList& objects)
{
	mWorld->FlagForRemoval(GetThisPtr());

	if (GetThisPtr()->GetType() == GameObjectType("Asteroid")) {
		shared_ptr<Shape> nAsteroid_shape = make_shared<Shape>("asteroid.shape");
		shared_ptr<GameObject> nAsteroid = make_shared<Asteroid>("miniAsteroid");
		nAsteroid->SetShape(nAsteroid_shape);
		nAsteroid->SetPosition(GetThisPtr()->GetPosition());
		nAsteroid->SetScale(GetThisPtr()->GetScale() / 1);
		nAsteroid->SetBoundingShape(make_shared<BoundingSphere>(nAsteroid->GetThisPtr(), 5.0f));
		mWorld->AddObject(nAsteroid);
	}
	
}

#ifndef __BULLETPOWERUP_H__
#define __BULLETPOWERUP_H__

#include "GameObject.h"

class BulletPowerUp : public GameObject {

public:
	BulletPowerUp(void);
	~BulletPowerUp();

	bool CollisionTest(shared_ptr<GameObject> o);
	bool OnCollision(const GameObjectList& objects);

};
#endif
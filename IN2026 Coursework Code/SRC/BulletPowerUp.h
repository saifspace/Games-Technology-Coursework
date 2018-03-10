#ifndef __BULLETPOWERUP_H__
#define __BULLETPOWERUP_H__

#include "GameObject.h"

class BulletPowerUp : public GameObject {

public:
	BulletPowerUp(void);
	~BulletPowerUp(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

	void Render(void);

};
#endif
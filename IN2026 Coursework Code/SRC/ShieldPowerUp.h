#ifndef __SHIELDPOWERUP_H__
#define __SHIELDPOWERUP_H__

#include "GameObject.h"

class ShieldPowerUp : public GameObject {

public:
	ShieldPowerUp(void);
	~ShieldPowerUp(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

	void Render(void);

};
#endif
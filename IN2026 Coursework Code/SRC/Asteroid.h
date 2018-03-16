#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "GameObject.h"
#include "ScoreKeeper.h"

class Asteroid : public GameObject
{
public:
	Asteroid();
	Asteroid(char const * const type_name);
	~Asteroid(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

	void CreateMiniAsteroids();
};

#endif

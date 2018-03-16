#ifndef __BULLET_H__
#define __BULLET_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "PowerBulletCollisionListener.h"

class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(char const * const type_name, GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r, int ttl);
	Bullet(const Bullet& b);
	virtual ~Bullet(void);

	virtual void Update(int t);

	void SetTimeToLive(int ttl) { mTimeToLive = ttl; }
	int GetTimeToLive(void) { return mTimeToLive; }

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

	void AddListener(shared_ptr<PowerBulletCollisionListener> listener)
	{
		mListeners.push_back(listener);
	}

	void FirePowerBulletCollided()
	{
		// Send message to all listeners
		for (PowerBulletCollisionListenerList::iterator lit = mListeners.begin(); lit != mListeners.end(); ++lit) {
			(*lit)->OnPowerBulletCollision();
		}
	}

private:
	typedef std::list< shared_ptr<PowerBulletCollisionListener> > PowerBulletCollisionListenerList;
	PowerBulletCollisionListenerList mListeners;

protected:
	int mTimeToLive;
};

#endif
#ifndef __ALIENSHIP_H__
#define __ALIENSHIP_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "Shape.h"
#include "OuterBoundingShapeListener.h"

class AlienShip : public GameObject
{
public:
	AlienShip();
	AlienShip(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r);
	AlienShip(const AlienShip& s);
	virtual ~AlienShip(void);

	virtual void Update(int t);
	virtual void Render(void);

	virtual void Thrust(float t);
	virtual void Rotate(float r);
	virtual void Shoot(void);
	virtual void StopShip();
	virtual void MoveShip();

	void SetAlienShipShape(shared_ptr<Shape> AlienShip_shape) { mAlienShipShape = AlienShip_shape; }
	void SetThrusterShape(shared_ptr<Shape> thruster_shape) { mThrusterShape = thruster_shape; }
	void SetBulletShape(shared_ptr<Shape> bullet_shape) { mBulletShape = bullet_shape; }

	void SetOuterBoundingShape(shared_ptr<BoundingShape> bs) { mOuterBoundingShape = bs; }
	
	void AddListener(shared_ptr<OuterBoundingShapeListener> listener)
	{
		mListeners.push_back(listener);
	}
	void FireDetected(GameObjectType obj)
	{
		// Send message to all listeners
		for (OuterBoundingShapeListenerList::iterator lit = mListeners.begin(); lit != mListeners.end(); ++lit) {
			(*lit)->OnOuterBoundDetection(obj);
		}
	}


	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList &objects);

private:
	float mThrust;
	typedef std::list< shared_ptr<OuterBoundingShapeListener>> OuterBoundingShapeListenerList;
	OuterBoundingShapeListenerList mListeners;

	shared_ptr<Shape> mAlienShipShape;
	shared_ptr<Shape> mThrusterShape;
	shared_ptr<Shape> mBulletShape;
	shared_ptr<BoundingShape> mOuterBoundingShape;
};
#endif
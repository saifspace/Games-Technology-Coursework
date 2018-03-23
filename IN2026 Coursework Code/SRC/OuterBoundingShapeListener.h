#ifndef __OUTERBOUNDINGSHAPELISTENER_H__
#define __OUTERBOUNDINGSHAPELISTENER_H__

class OuterBoundingShapeListener
{
public:
	virtual void OnOuterBoundDetection(GameObjectType obj) = 0;
};

#endif

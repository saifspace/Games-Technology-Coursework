#ifndef __ASTEROIDS_H__
#define __ASTEROIDS_H__

#include "GameUtil.h"
#include "GameSession.h"
#include "IKeyboardListener.h"
#include "IGameWorldListener.h"
#include "IScoreListener.h" 
#include "ScoreKeeper.h"
#include "Player.h"
#include "IPlayerListener.h"
#include "PowerBulletCollisionListener.h"
#include "OuterBoundingShapeListener.h"
#include "AlienShip.h"

class GameObject;
class Spaceship;
class GUILabel;

class Asteroids : public GameSession, public IKeyboardListener, public IGameWorldListener, public IScoreListener, public IPlayerListener, public PowerBulletCollisionListener, public OuterBoundingShapeListener
{
public:
	Asteroids(int argc, char *argv[]);
	virtual ~Asteroids(void);

	virtual void Start(void);
	virtual void Stop(void);

	// Declaration of IKeyboardListener interface ////////////////////////////////

	void OnKeyPressed(uchar key, int x, int y);
	void OnKeyReleased(uchar key, int x, int y);
	void OnSpecialKeyPressed(int key, int x, int y);
	void OnSpecialKeyReleased(int key, int x, int y);

	// Declaration of IScoreListener interface //////////////////////////////////

	void OnScoreChanged(int score);

	// Declaration of the IPlayerLister interface //////////////////////////////

	void OnPlayerKilled(int lives_left);

	// Declaration of IGameWorldListener interface //////////////////////////////

	void OnWorldUpdated(GameWorld* world) {}
	void OnObjectAdded(GameWorld* world, shared_ptr<GameObject> object);
	void OnObjectRemoved(GameWorld* world, shared_ptr<GameObject> object);

	// Override the default implementation of ITimerListener ////////////////////
	void OnTimer(int value);

	// Declaration of PowerBulletCollisionListener interface
	void OnPowerBulletCollision();
	void OnOuterBoundDetection(GameObjectType obj);

private:
	shared_ptr<Spaceship> mSpaceship;
	shared_ptr<GUILabel> mScoreLabel;
	shared_ptr<GUILabel> mLivesLabel;
	shared_ptr<GUILabel> mGameOverLabel;

	shared_ptr<AlienShip> mAlienShip;

	uint mLevel;
	uint mAsteroidCount;
	uint mMiniAsteroidCount = 0;

	void ResetSpaceship();
	shared_ptr<GameObject> CreateSpaceship();
	void CreateGUI();
	void CreateAsteroids(const uint num_asteroids);
	shared_ptr<GameObject> CreateExplosion();
	void CreateBulletPowerUps(const uint num_powerUps);
	shared_ptr<AlienShip> CreateAlienShip();
	
	const static uint SHOW_GAME_OVER = 0;
	const static uint START_NEXT_LEVEL = 1;
	const static uint CREATE_NEW_PLAYER = 2;

	const static uint SHIELD_TIME_OUT = 3;
	const static uint THRUST_TIME_OUT = 4;
	const static uint ROTATE_ALIEN_SHIP = 5;
	const static uint MOVE_ALIEN_SHIP = 6;

	ScoreKeeper mScoreKeeper;
	Player mPlayer;
	shared_ptr<Asteroids> thisPtr;
};

#endif
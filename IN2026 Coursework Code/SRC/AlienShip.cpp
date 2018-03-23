#include "GameUtil.h"
#include "GameWorld.h"
#include "Bullet.h"
#include "AlienShip.h"
#include "BoundingSphere.h"


AlienShip::AlienShip()
	: GameObject("AlienShip"), mThrust(0)
{
}

AlienShip::AlienShip(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("AlienShip", p, v, a, h, r), mThrust(0)
{
}

AlienShip::AlienShip(const AlienShip& s)
	: GameObject(s), mThrust(0)
{
}

AlienShip::~AlienShip(void)
{
}

void AlienShip::Update(int t)
{
	// Call parent update function
	GameObject::Update(t);
}

void AlienShip::Render(void)
{
	// Disable lighting to get solid lines
	glDisable(GL_LIGHTING);
	// Set pen colour to very light grey
	glColor3f(0.8, 0.8, 0.8);
	// Start drawing closed shape
	glBegin(GL_LINE_LOOP);
	// Add vertices of ship's body
	glVertex3f(-3, -2, 0);
	glVertex3f(4, 0, 0);
	glVertex3f(-3, 2, 0);
	// Finish drawing closed shape
	glEnd();

	if (mThrust > 0) {
		glBegin(GL_LINE_STRIP);
		glColor3f(0.8, 0.4, 0.1);
		glVertex3f(-2, -1, 0);
		glVertex3f(-4, 0, 0);
		glVertex3f(-2, 1, 0);
		glEnd();
	}

	// Enable lighting
	glEnable(GL_LIGHTING);
	// Call base class to render debug graphics if required
	GameObject::Render();
}

void AlienShip::Thrust(float t)
{
	mThrust = t;
	// Increase acceleration in the direction of ship
	mAcceleration.x = mThrust*cos(DEG2RAD*mAngle);
	mAcceleration.y = mThrust*sin(DEG2RAD*mAngle);
}

void AlienShip::Rotate(float r)
{
	mRotation = r;
}

void AlienShip::Shoot(void)
{
	// Check the world exists
	if (!mWorld) return;

	GLVector3f spaceship_heading(cos(DEG2RAD*mAngle), sin(DEG2RAD*mAngle), 0);
	spaceship_heading.normalize();

	GLVector3f bullet_position = mPosition + (spaceship_heading * 4);

	float bullet_speed = 30;

	GLVector3f bullet_velocity = mVelocity + spaceship_heading * bullet_speed;

	shared_ptr<GameObject> bullet(new Bullet("EnemyBullet",bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 2000));
	bullet->SetBoundingShape(make_shared<BoundingSphere>(bullet->GetThisPtr(), 2.0f));
	bullet->SetShape(mBulletShape);

	mWorld->AddObject(bullet);
}

void AlienShip::StopShip() {
	mVelocity.x = 0;
	mVelocity.y = 0;
}

void AlienShip::MoveShip() {
	mVelocity.x = 10*cos(DEG2RAD*mAngle);
	mVelocity.y = 10*sin(DEG2RAD*mAngle);
}

bool AlienShip::CollisionTest(shared_ptr<GameObject> o)
{
	//if (o->GetType() != GameObjectType("Asteroid")) return false;

	if (o->GetType() == GameObjectType("Asteroid") || o->GetType() == GameObjectType("MiniAsteroid")) {
		return false;
	}

	if (o->GetType() == GameObjectType("Spaceship")) {
		bool collision = mOuterBoundingShape->CollisionTest(o->GetBoundingShape());
		if (collision == true) {
			FireDetected(o->GetType());
		}
	}
	
	if (o->GetType() == GameObjectType("Bullet")) {
		bool collision = mOuterBoundingShape->CollisionTest(o->GetBoundingShape());
		if (collision == true) {
			FireDetected(o->GetType());
		}
	}

	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void AlienShip::OnCollision(const GameObjectList &objects)
{
		//mWorld->FlagForRemoval(GetThisPtr());
}
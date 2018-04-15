#ifndef PLAYER_H
#define PLAYER_H

#include "Framework\Debug\Console.h"
#include "Framework\Debug\DebugDraw.h"

#include "Framework\Utility\Utility.h"

#include "Framework\Entities\Entity.h"

#define PlayerWidth 32
#define PlayerHeight 32

#define PlayerXAccel 75.f
#define PlayerMaxXVel 100.f
#define PlayerXDecel 75.f

#define PlayerYAccel 100.f
#define PlayerMaxYVel 100.f

#define PlayerJumpVel 200.f
#define PlayerJumpFrameLimit 0.1f

struct PhysStats
{
	PhysStats();
	PhysStats(float xaccel, float maxxvel, float xdecel, float yaccel, float maxyvel, float jumpvel, float jumplimit);
	float _XAccel, _MaxXVel, _XDecel, _YAccel, _MaxYVel, _JumpVel, _JumpTimeLimit;
};

class Player : public Entity
{
public:

	Player();
	~Player();

	void Input(float dt);
	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	AABBMask GetMask();

	void Land();

	PhysStats _PhysStats;

private:

	float _JumpFrames = 0.f;

};

#endif
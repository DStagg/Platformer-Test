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

class Player : public Entity
{
public:

	Player();
	~Player();

	void Input(float dt);
	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	AABBMask GetMask();

private:

};

#endif
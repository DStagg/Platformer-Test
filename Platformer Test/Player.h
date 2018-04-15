#ifndef PLAYER_H
#define PLAYER_H

#include "Framework\Debug\Console.h"
#include "Framework\Debug\DebugDraw.h"

#include "Framework\Utility\Utility.h"

#include "Framework\Entities\Entity.h"

#define PlayerWidth 32
#define PlayerHeight 32

class Player : public Entity
{
public:

	Player();
	~Player();

	void Input();
	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	AABBMask GetMask();

private:

};

#endif
#ifndef ENTITY_H
#define ENTITY_H

#include "../Data/Shapes.h"
#include "../Data/Pair.h"
#include "SFML\Graphics.hpp"
#include "../Data/Collision.h"

class Entity
{
public:

	Entity();
	~Entity();

	virtual void Input() = 0;
	virtual void UpdatePos(float dt);
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow* rw) = 0;

	bool _Alive = true;

	Point	_Position = Point(0, 0);
	Vec	_Velocity = Vec(0.f, 0.f);
	PairInt	_Size = PairInt(0, 0);

	float _Facing = 0.f;

	int _HP = 100;

};

#endif
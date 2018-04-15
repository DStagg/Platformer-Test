#include "Entity.h"

Entity::Entity()
{

};
Entity::~Entity()
{

};

void Entity::UpdatePos(float dt)
{
	_Position += _Velocity * dt;
};

void Entity::Update(float dt)
{
	UpdatePos(dt);
};
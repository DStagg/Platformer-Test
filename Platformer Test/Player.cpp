#include "Player.h"

Player::Player()
{
	_Size = PairInt(32, 32);
};

Player::~Player()
{

};

void Player::Input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		_Velocity._Y = -100.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		_Velocity._Y = 100.f;
	else
		_Velocity._Y = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		_Velocity._X = -100.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		_Velocity._X = 100.f;
	else
		_Velocity._X = 0.f;
};

void Player::Update(float dt) 
{
	Entity::Update(dt);

};

void Player::Draw(sf::RenderWindow* rw)
{
	//	Draw main body
	DebugDrawAABB(GetMask()._Mask, rw);
};

AABBMask Player::GetMask()
{
	return AABBMask(AABB(_Position.GetX(), _Position.GetY(), PlayerWidth, PlayerHeight));
};
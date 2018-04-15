#include "Player.h"

Player::Player()
{
	_Size = PairInt(32, 32);
};

Player::~Player()
{

};

void Player::Input(float dt)
{
	//	Alt. mode of acceleration: vector2f curSpeed = a * targetSpeed + (1-a) * curSpeed;

	//	Move Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		_Velocity._X -= PlayerXAccel * dt;
		if (Absolute(_Velocity._X) > PlayerMaxXVel)
			_Velocity._X = -PlayerMaxXVel;
	}
	//	Move Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		_Velocity._X += PlayerXAccel * dt;
		if (Absolute(_Velocity._X) > PlayerMaxXVel)
			_Velocity._X = PlayerMaxXVel;
	}
	//	Slow to a stop
	else if (_Velocity._X != 0.f)
	{
		if (Absolute(_Velocity._X) < PlayerXDecel * dt)
			_Velocity._X = 0.f;
		else
			_Velocity._X -= Sign(_Velocity._X) * PlayerXDecel * dt;
	}

	//	Jump
	if (_JumpFrames < PlayerJumpFrameLimit)
		_JumpFrames += dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && (_JumpFrames <= PlayerJumpFrameLimit))
	{
		_Velocity._Y = -PlayerJumpVel;
		_JumpFrames = PlayerJumpFrameLimit + 0.1f;
	}

	//	Fall
	if (_Velocity._Y > PlayerMaxYVel)
		_Velocity._Y = PlayerMaxYVel;
	else
		_Velocity._Y += PlayerYAccel * dt;
	
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

void Player::Land()
{
	_JumpFrames = 0.f;
};
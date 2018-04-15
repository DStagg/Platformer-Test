#include "Player.h"

PhysStats::PhysStats()
{
	_XAccel = PlayerXAccel;
	_MaxXVel = PlayerMaxXVel;
	_XDecel = PlayerXDecel;
	_YAccel = PlayerYAccel;
	_MaxYVel = PlayerMaxYVel;
	_JumpVel = PlayerJumpVel;
	_JumpTimeLimit = PlayerJumpFrameLimit;
};

PhysStats::PhysStats(float xaccel, float maxxvel, float xdecel, float yaccel, float maxyvel, float jumpvel, float jumplimit)
{
	_XAccel = xaccel;
	_MaxXVel = maxxvel;
	_XDecel = xdecel;
	_YAccel = yaccel;
	_MaxYVel = maxyvel;
	_JumpVel = jumpvel;
	_JumpTimeLimit = jumplimit;
};

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
		_Velocity._X -= _PhysStats._MaxXVel * dt;
		if (Absolute(_Velocity._X) > _PhysStats._MaxXVel)
			_Velocity._X = -_PhysStats._MaxXVel;
	}
	//	Move Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		_Velocity._X += _PhysStats._MaxXVel * dt;
		if (Absolute(_Velocity._X) > _PhysStats._MaxXVel)
			_Velocity._X = _PhysStats._MaxXVel;
	}
	//	Slow to a stop
	else if (_Velocity._X != 0.f)
	{
		if (Absolute(_Velocity._X) < _PhysStats._XDecel * dt)
			_Velocity._X = 0.f;
		else
			_Velocity._X -= Sign(_Velocity._X) * _PhysStats._XDecel * dt;
	}

	//	Jump
	if (_JumpFrames < _PhysStats._JumpTimeLimit)
		_JumpFrames += dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && (_JumpFrames <= _PhysStats._JumpTimeLimit))
	{
		_Velocity._Y = -_PhysStats._JumpVel;
		_JumpFrames = _PhysStats._JumpTimeLimit + 0.1f;
	}

	//	Fall
	if (_Velocity._Y > _PhysStats._MaxYVel)
		_Velocity._Y = _PhysStats._MaxYVel;
	else
		_Velocity._Y += _PhysStats._YAccel * dt;
	
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
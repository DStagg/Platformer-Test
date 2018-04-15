#include "Level.h"

/////

Tile::Tile(int strx, int stry, bool s)
{
	_SpriteX = strx;
	_SpriteY = stry;
	_Solid = s;
};

/////

Impulse::Impulse(Entity* e, float time, Vec accel)
{
	_Target = e;
	_TimeRemaining = time;
	_TimeLength = time;
	_Accel = accel;
};

/////

Level::Level()
{
	_Player._Position.Set(200, 200);
};

Level::~Level()
{

};

void Level::GenerateBox(int w, int h)
{
	if (w < 3) w = 3;
	if (h < 3) h = 3;

	_Tiles.Resize(w, h);
	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
		{
			if ((x == 0) || (x == w - 1)) _Tiles.SetCell(x, y, Tile(0, 0, true));
			else if ((y == 0) || (y == h - 1)) _Tiles.SetCell(x, y, Tile(0, 0, true));
			else _Tiles.SetCell(x, y, Tile(0,1,false));
		}
};

void Level::GenerateFancyBox(int w, int h)
{
	if (w < 3) w = 3;
	if (h < 3) h = 3;

	_Tiles.Resize(w, h);
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			if (x == 0) _Tiles.SetCell(x, y, Tile(2,1,true));			//	L
			else if (x == w - 1) _Tiles.SetCell(x, y, Tile(3,1,true));	//	R
			else if (y == 0) _Tiles.SetCell(x, y, Tile(4,0,true));		//	T
			else if (y == h - 1) _Tiles.SetCell(x, y, Tile(5,0,true));	//	B
			else _Tiles.SetCell(x, y, Tile(6,1,false));					//	Mid
		}
	}
	_Tiles.SetCell(0, 0, Tile(2,0,true));			//	TL
	_Tiles.SetCell(w - 1, 0, Tile(3,0,true));		//	TR
	_Tiles.SetCell(0, h - 1, Tile(4,1,true));		//	BL
	_Tiles.SetCell(w - 1, h - 1, Tile(5,1,true));	//	BR
	
	_PlayerStartPos = PairInt((int)(_TileWidth * 1.5f) , (int)(_TileHeight * 1.5f));

	//	(2, 0) (4, 0) (3, 0)
	//	(2, 1) (6, 1) (3, 1)
	//	(4, 1) (5, 0) (5, 1)
		
};

Grid<Tile>& Level::GetGrid()
{
	return _Tiles;
};
Grid<PairInt> Level::BuildSpriteCoordGrid()
{
	Grid<PairInt> results(GetGrid().GetWidth(), GetGrid().GetHeight());

	for (int x = 0; x < GetGrid().GetWidth(); x++)
		for (int y = 0; y < GetGrid().GetHeight(); y++)
			results.SetCell(x, y, PairInt(GetGrid().GetCell(x,y)._SpriteX, GetGrid().GetCell(x, y)._SpriteY));
	
	return results;
};

bool Level::IsSolid(int x, int y)
{
	if ((x < 0) || (y < 0) || (x >= _Tiles.GetWidth()) || (y >= _Tiles.GetHeight())) return false;
	return _Tiles.GetCell(x, y)._Solid;
};

int Level::CalcCol(float x)
{
	return ((int)x - ( (int)x % _TileWidth)) / _TileWidth;
};

int Level::CalcRow(float y)
{
	return ((int)y - ((int)y % _TileHeight)) / _TileHeight;
};

CollisionResults Level::WallCollision(AABBMask mask)
{
	int lCol = CalcCol((float)mask._Mask._X);
	int rCol = CalcCol((float)mask._Mask.Right());
	int tRow = CalcCol((float)mask._Mask._Y);
	int bRow = CalcRow((float)mask._Mask.Bottom());

	for (int x = lCol; x <= rCol; x++)
		for (int y = tRow; y <= bRow; y++)
		{
			if (IsSolid(x, y))
			{
				AABBMask temp(AABB(x * _TileWidth, y * _TileHeight, _TileWidth, _TileHeight));
				CollisionResults res = mask.Collide(temp);
				if (!res._Collided)	Log("WallCollision(AABB) discrepancy: mask check not returning true.");
				return res;
			}
		}

	return CollisionResults(false, Vec());
};

CollisionResults Level::WallCollision(CircleMask mask)
{
	int lCol = CalcCol((mask._Mask._X - mask._Mask._Radius) + 1.f);
	int rCol = CalcCol((mask._Mask._X + mask._Mask._Radius) - 1.f);
	int tRow = CalcCol((mask._Mask._Y - mask._Mask._Radius) + 1.f);
	int bRow = CalcRow((mask._Mask._Y + mask._Mask._Radius) - 1.f);

	for (int x = lCol; x <= rCol; x++)
		for (int y = tRow; y <= bRow; y++)
		{
			if (IsSolid(x, y))
			{
				AABBMask box(AABB(x * _TileWidth, y * _TileHeight, _TileWidth, _TileHeight));
				CollisionResults res = mask.Collide(box);
				if (res._Collided)
					return res;
			}
		}

	return CollisionResults(false, Vec());
};

CollisionResults Level::WallCollisionX(AABBMask mask, float xvel, float dt)
{
	return CollisionResults(false, Vec());
};

CollisionResults Level::WallCollisionY(AABBMask mask, float yvel, float dt)
{
	return CollisionResults(false, Vec());
};

void Level::Update(float dt)
{
	//	Input
	_Player.Input(dt);

	//	Impulses
	for (int i = 0; i < (int)_Impulses.size(); i++)
	{
		_Impulses[i]._Target->_Velocity += _Impulses[i]._Accel;
		_Impulses[i]._TimeRemaining -= dt;
		if (_Impulses[i]._TimeRemaining <= 0.f)
		{
			_Impulses.erase(_Impulses.begin() + i);
			i--;
		}
	}
	
	//	TODO: work out why the player is being accelerated off of the side of walls
	//	Collide
	if (_Player._Velocity._X != 0.f)
	{
		int nearX = CalcCol(_Player._Velocity._X < 0.f ? (float)_Player.GetMask()._Mask.Left() : (float)_Player.GetMask()._Mask.Right());
		int farX = CalcCol(_Player._Velocity._X < 0.f ? (float)_Player.GetMask()._Mask.Left() + (_Player._Velocity._X * dt) - 1 : (float)_Player.GetMask()._Mask.Right() + (_Player._Velocity._X * dt) + 1);
		int topY = CalcRow((float)_Player.GetMask()._Mask.Top());
		int bottomY = CalcRow((float)_Player.GetMask()._Mask.Bottom());

		bool colX = false;

		for (int x = nearX; x != farX + Sign(_Player._Velocity._X); x += Sign(_Player._Velocity._X))
		{
			if (colX)
				break;

			for (int y = topY; y <= bottomY; y++)
			{
				if (GetGrid().GetCell(x, y)._Solid)
				{
					_Player._Position.SetX(_Player._Velocity._X < 0.f ?
						(x + 1) * _TileWidth :
						(x * _TileWidth) - _Player.GetMask()._Mask._Width);

					colX = true;
					break;
				}
			}
		}

		if (colX)
			_Player._Velocity._X = 0.f;
		else
			_Player.UpdatePos(dt);
	}

	if (_Player._Velocity._Y != 0.f)
	{
		int nearY = CalcRow(_Player._Velocity._Y < 0.f ? (float)_Player.GetMask()._Mask.Top() : (float)_Player.GetMask()._Mask.Bottom());
		int farY = CalcRow(_Player._Velocity._Y < 0.f ? (float)_Player.GetMask()._Mask.Top() + (_Player._Velocity._Y * dt) - 1 : (float)_Player.GetMask()._Mask.Bottom() + (_Player._Velocity._Y * dt) + 1);
		int leftX = CalcCol((float)_Player.GetMask()._Mask.Left());
		int rightX = CalcCol((float)_Player.GetMask()._Mask.Right());

		bool colY = false;

		for (int y = nearY; y != farY + Sign(_Player._Velocity._Y); y += Sign(_Player._Velocity._Y))
		{
			if (colY)
				break;

			for (int x = leftX; x <= rightX; x++)
			{
				if (GetGrid().GetCell(x, y)._Solid)
				{
					_Player._Position.SetY(_Player._Velocity._Y < 0.f ?
						(y + 1) * _TileHeight :
						(y * _TileHeight) - _Player.GetMask()._Mask._Height);
					colY = true;
					break;
				}
			}
		}

		if (colY)
			_Player._Velocity._Y = 0.f;
		else
			_Player.UpdatePos(dt);
	}
	/*
	CollisionResults pres = WallCollision(_Player.GetMask());
	if (pres._Collided)
	{
		_Player._Velocity = Vec(0.f, 0.f);
		_Player._Position += pres._Overlap;
	}
	*/
	//	Update Position/etc.
//	_Player.Update(dt);

	//	Resolve/Cull

};

void Level::Draw(sf::RenderWindow* rw)
{
	_Player.Draw(rw);
};

Player& Level::GetPlayer()
{
	return _Player;
};

void Level::Load(std::string file)
{
	BinaryFile input(file, BinaryFile::IOMode::IO_In);

	if (!input.IsOpen())
		return GenerateFancyBox(10, 10);
	Log("Level opened: " + file + ".");
	int width = input.Read<int>();
	Log("Width: " + IntToString(width));
	int height = input.Read<int>();
	Log("Height: " + IntToString(height));

	GetGrid().Resize(width, height);

	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
		{
			int sprx = input.Read<int>();
			int spry = input.Read<int>();
			bool sol = input.Read<bool>();

			GetGrid().SetCell(x, y, Tile(sprx, spry, sol));
			Log("Cell [" + IntToString(x) + "," + IntToString(y) + "]: " + IntToString(sprx) + "," + IntToString(spry) + " & " + (sol ? "solid." : "passable."));
		}

	int px = input.Read<int>();
	int py = input.Read<int>();
	Log("Player starts at (" + IntToString(px) + "," + IntToString(py) + ")");
	_Player._Position.Set(px, py);
	_PlayerStartPos = PairInt(px, py);
	/*
	_Enemies.clear();
	int numEnemy = input.Read<int>();
	Log(IntToString(numEnemy) + " enemies.");
	for (int i = 0; i < numEnemy; i++)
	{
		int ex = input.Read<int>();
		int ey = input.Read<int>();
		float evx = input.Read<float>();
		float evy = input.Read<float>();
		Log("Enemy " + IntToString(i) + " at (" + IntToString(ex) + "," + IntToString(ey) + ") moves [" + FloatToString(evx) + "," + FloatToString(evy) + "].");
		Enemy e;
		e._Position.Set(ex, ey);
		e._Velocity = Vec(evx, evy);

		_Enemies.push_back(e);
	}

	_Pickups.clear();
	int numPickups = input.Read<int>();
	Log(IntToString(numPickups) + " pickups.");
	for (int i = 0; i < numPickups; i++)
	{
		int pux = input.Read<int>();
		int puy = input.Read<int>();
		Log("Pickup " + IntToString(i) + " at (" + IntToString(pux) + "," + IntToString(puy) + ").");
		Pickup p;
		p._Position.Set(pux, puy);

		_Pickups.push_back(p);
	}
	*/
	Log("Level loaded.");
	input.Close();
};

void Level::Save(std::string file)
{
	BinaryFile output(file, BinaryFile::IOMode::IO_Out, true);

	if (!output.IsOpen())
		return;

	output.Write<int>(GetGrid().GetWidth());
	output.Write<int>(GetGrid().GetHeight());

	for (int x = 0; x < GetGrid().GetWidth(); x++)
		for (int y = 0; y < GetGrid().GetHeight(); y++)
		{
			output.Write<int>(GetGrid().GetCell(x, y)._SpriteX);
			output.Write<int>(GetGrid().GetCell(x, y)._SpriteY);
			output.Write<bool>(GetGrid().GetCell(x, y)._Solid);
		}

	output.Write<int>(_PlayerStartPos._A);
	output.Write<int>(_PlayerStartPos._B);
	/*
	output.Write<int>((int)_Enemies.size());
	for (int i = 0; i < (int)_Enemies.size(); i++)
	{
		output.Write<int>(_Enemies[i]._Position.GetX());
		output.Write<int>(_Enemies[i]._Position.GetY());
		output.Write<float>(_Enemies[i]._Velocity._X);
		output.Write<float>(_Enemies[i]._Velocity._Y);
	}

	output.Write<int>((int)_Pickups.size());
	for (int i = 0; i < (int)_Pickups.size(); i++)
	{
		output.Write<int>(_Pickups[i]._Position.GetX());
		output.Write<int>(_Pickups[i]._Position.GetY());
	}
	*/
	output.Close();
};

void Level::SetPlayerStart(int x, int y)
{
	_PlayerStartPos.Set(x, y);
};

PairInt Level::GetPlayerStart()
{
	return _PlayerStartPos;
};
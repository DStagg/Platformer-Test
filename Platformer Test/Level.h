#ifndef LEVEL_H
#define LEVEL_H

#include "Framework\Data\Grid.h"
#include <map>

#include "Player.h"

#include "Framework\IO\BinaryFile.h"

#include "Framework\Data\Collision.h"
#include "Framework\Debug\DebugDraw.h"

#include "Framework\Utility\Random.h"

struct Tile
{
	Tile(int sprx = 0, int spry = 0, bool solid = false);
	int _SpriteX, _SpriteY;
	bool _Solid;
};

struct Impulse
{
	Impulse(Entity* e = 0, float time = 0.f, Vec accel = Vec());
	Entity* _Target;
	float _TimeLength, _TimeRemaining;
	Vec _Accel;
};

class Level
{
public:

	Level();
	~Level();

	void GenerateBox(int w, int h);
	void GenerateFancyBox(int w, int h);

	Grid<Tile>& GetGrid();
	Grid<PairInt> BuildSpriteCoordGrid();

	bool IsSolid(int x, int y);
	int CalcCol(float x);
	int CalcRow(float y);
	//	TODO: Change WallCollision tests to take into account velocity and dt?
	//	TODO: May also help to get wall collision working better by checkng each axis one at a time, etc.
	CollisionResults WallCollision(AABBMask mask);
	CollisionResults WallCollision(CircleMask mask);
	CollisionResults WallCollisionX(AABBMask mask, float xvel, float dt);
	CollisionResults WallCollisionY(AABBMask mask, float yvel, float dt);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	Player& GetPlayer();

	void Load(std::string file);
	void Save(std::string file);

	void SetPlayerStart(int x, int y);
	PairInt GetPlayerStart();

private:

	Grid<Tile> _Tiles;

	int _TileWidth = 32;
	int _TileHeight = 32;

	Player _Player;
	PairInt _PlayerStartPos;

	std::vector<Impulse> _Impulses;
};

/*	Level Save Format
	int Width
	int Height
	Tiles: X by Y:
		int SpriteX
		int SpriteY
		bool Solid
	int PlayerStartX
	int PlayerStartY
	int NumberOfEnemies
	Enemies: by int id:
		int StartX
		int StartY
		float StartXVel
		float StartYVel
	int NumberOfPickups
	Pickups: by int id:
		int PositionX
		int PositionY
*/
#endif
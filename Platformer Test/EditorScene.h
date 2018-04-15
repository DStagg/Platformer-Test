#ifndef EDITOR_SCENE_H
#define EDITOR_SCENE_H

#include "Framework\SFMLScene.h"

#include "Framework\Data\Grid.h"
#include "Framework\Data\CompositeTex.h"

#include "Framework\IO\ImageManager.h"

#include "Level.h"

#include "Framework\Debug\Console.h"

#include "Framework\IO\MouseInput.h"

class EditorScene : public SFMLScene
{
public:

	enum EditMode {
		PlayerStartMode = 0,
		GridSizeMode,
		TileSpriteMode,
		TileSolidMode,
		AddEnemyMode,
		EnemyMoveMode,
		AddPickupMode
	};

	EditorScene(sf::RenderWindow* rw);
	~EditorScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	void RefreshTiles();

	sf::View _CameraView;

	ImageManager _ImgMan;

	sf::Font _Font;
	CompositeTex _CompositeTex;
	CompositeBuilder _CompositeBuilder;

	int _Mode = 0;
	int _TileX = 0;
	int _TileY = 0;
	int _EnemyDrag = -1;

	int _CameraPanX;
	int _CameraPanY;

	bool _ShowLog = false;

	Level _Level;

	SFMLMouseInput _MouseInput;
};

#endif
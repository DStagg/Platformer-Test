#include "EditorScene.h"

EditorScene::EditorScene(sf::RenderWindow* rw) : SFMLScene(rw)
{
	
};
EditorScene::~EditorScene()
{

};

void EditorScene::Begin()
{
	_CameraView = _Window->getDefaultView();

	_ImgMan.SetDirectory("Resources");
	_ImgMan.LoadTextureFromFile("Tilesheet", "Tilesheet.png");

	sf::Image img = _ImgMan.GetTexturePntr("Tilesheet")->copyToImage();
	_CompositeBuilder = CompositeBuilder(img, PairInt(32, 32));

	_Font.loadFromFile("Resources\\Roboto-Regular.ttf");

	_Level.Load("Level.sav");

	Console::C()->Init(_Font, 16, 20);

	_MouseInput.Init(_Window);

	RefreshTiles();
};
void EditorScene::End()
{
	Console::C()->DumpLog("EditorLog.txt");
};
void EditorScene::Pause()
{

};
void EditorScene::Resume()
{

};
void EditorScene::Update(float dt)
{
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			GetManager()->Quit();
		else if (Event.type == sf::Event::MouseMoved)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
				_CameraView.move((float)_CameraPanX - Event.mouseMove.x, (float)_CameraPanY - Event.mouseMove.y);

			_CameraPanX = Event.mouseMove.x;
			_CameraPanY = Event.mouseMove.y;
		}
		else if (Event.type == sf::Event::MouseButtonPressed)
		{
			PairInt mpos = _MouseInput.GetWorldPos();
			int mx = mpos._A;
			int my = mpos._B;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				mx = mx - (mx % 16);
				my = my - (my % 16);
			}

			if (Event.mouseButton.button == sf::Mouse::Button::Left)
			{
				if (_Mode == EditMode::PlayerStartMode)
					_Level.SetPlayerStart(mx, my);
				else if (_Mode == EditMode::TileSpriteMode)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))		//	Select Tile
					{
						int maxx = (_ImgMan.GetTexturePntr("Tilesheet")->getSize().x / 32) - 1;
						int maxy = (_ImgMan.GetTexturePntr("Tilesheet")->getSize().y / 32) - 1;
						_TileX = Min(maxx, Max(0, (mx - (mx % 32)) / 32));
						_TileY = Min(maxy, Max(0, (my - (my % 32)) / 32));
					}
					else														//	Paint Tile
					{
						int col = _Level.CalcCol((float)mx);
						int row = _Level.CalcRow((float)my);

						_Level.GetGrid().SetCell(col, row, Tile(_TileX, _TileY, _Level.GetGrid().GetCell(col, row)._Solid));

						RefreshTiles();
					}
				}
				else if (_Mode == EditMode::TileSolidMode)
				{
					int col = _Level.CalcCol((float)mx);
					int row = _Level.CalcCol((float)my);

					_Level.GetGrid().SetCell(col, row, Tile(_Level.GetGrid().GetCell(col, row)._SpriteX, _Level.GetGrid().GetCell(col, row)._SpriteY, !_Level.GetGrid().GetCell(col, row)._Solid));
				}
				else if (_Mode == EditMode::AddEnemyMode)
				{
					
				}
				else if (_Mode == EditMode::EnemyMoveMode)
				{
					
				}
				else if (_Mode == EditMode::AddPickupMode)
				{
					
				}
			}
			else if (Event.mouseButton.button == sf::Mouse::Right)
			{
				if (_Mode == EditMode::AddEnemyMode)
				{
					
				}
				else if (_Mode == EditMode::AddPickupMode)
				{
					
				}
				else if (_Mode == EditMode::EnemyMoveMode)
				{
				
				}
			}
		}
		else if (Event.type == sf::Event::KeyPressed)
			switch (Event.key.code)
			{
			case sf::Keyboard::Escape:
				GetManager()->Quit();
				break;
			case sf::Keyboard::F1:
				_ShowLog = !_ShowLog;
				break;
			case sf::Keyboard::S:
				_Level.Save("Level.sav");
				break;
			case sf::Keyboard::L:
				_Level.Load("Level.sav");
				RefreshTiles();
				break;
			case sf::Keyboard::Num1:
				_Mode = EditMode::PlayerStartMode;
				break;
			case sf::Keyboard::Num2:
				_Mode = EditMode::GridSizeMode;
				break;
			case sf::Keyboard::Num3:
				_Mode = EditMode::TileSpriteMode;
				break;
			case sf::Keyboard::Num4:
				_Mode = EditMode::TileSolidMode;
				break;
			case sf::Keyboard::Num5:
				_Mode = EditMode::AddEnemyMode;
				break;
			case sf::Keyboard::Num6:
				_Mode = EditMode::EnemyMoveMode;
				break;
			case sf::Keyboard::Num7:
				_Mode = EditMode::AddPickupMode;
				break;
			case sf::Keyboard::Return:
				_CameraView = _Window->getDefaultView();
				break;
			case sf::Keyboard::Left:
				if (_Mode == EditMode::GridSizeMode)
				{
					_Level.GetGrid().Resize(Max(3, _Level.GetGrid().GetWidth() - 1), _Level.GetGrid().GetHeight());
					RefreshTiles();
				}
				break;
			case sf::Keyboard::Right:
				if (_Mode == EditMode::GridSizeMode)
				{
					_Level.GetGrid().Resize(Min(100, _Level.GetGrid().GetWidth() + 1), _Level.GetGrid().GetHeight());
					RefreshTiles();
				}
				break;
			case sf::Keyboard::Up:
				if (_Mode == EditMode::GridSizeMode)
				{
					_Level.GetGrid().Resize(_Level.GetGrid().GetWidth(), Max(3, _Level.GetGrid().GetHeight() - 1));
					RefreshTiles();
				}
				break;
			case sf::Keyboard::Down:
				if (_Mode == EditMode::GridSizeMode)
				{
					_Level.GetGrid().Resize(_Level.GetGrid().GetWidth(), Min(100, _Level.GetGrid().GetHeight() + 1));
					RefreshTiles();
				}
				break;
			default:
				break;
			}
	}
};
void EditorScene::DrawScreen()
{
	_Window->setView(_CameraView);

	_Window->draw(_CompositeTex.BuildSprite());

	//	Draw the collision map
	if (_Mode == EditMode::TileSolidMode)
	{
		//	HACK: optimise by only drawing on-screen area
		for (int x = 0; x < _Level.GetGrid().GetWidth(); x++)
			for (int y = 0; y < _Level.GetGrid().GetHeight(); y++)
			{
				if (_Level.GetGrid().GetCell(x, y)._Solid)
				{
					sf::RectangleShape rect;
					rect.setPosition((float)x * 32.f, (float)y * 32.f);
					rect.setSize(sf::Vector2f(32.f, 32.f));
					rect.setFillColor(sf::Color(255, 0, 0, 155));
					rect.setOutlineColor(sf::Color::Blue);
					rect.setOutlineThickness(1.f);
					_Window->draw(rect);
				}
			}
	}

	//	Draw the starting position of the player
	sf::CircleShape playerCirc;
	playerCirc.setFillColor(sf::Color::Transparent);
	playerCirc.setOutlineColor(sf::Color::Blue);
	playerCirc.setOutlineThickness(1.f);
	playerCirc.setRadius(16.f);
	playerCirc.setOrigin(16.f, 16.f);
	playerCirc.setPosition((float)_Level.GetPlayerStart()._A, (float)_Level.GetPlayerStart()._B);
	_Window->draw(playerCirc);
	////////////////////////////////////////////

	//	GUI
	_Window->setView(_Window->getDefaultView());

	sf::RectangleShape backBar;
	backBar.setFillColor(sf::Color(155, 155, 155));
	backBar.setSize(sf::Vector2f((float)_Window->getSize().x, 100.f));
	backBar.setPosition(0.f, _Window->getSize().y - 100.f);
	_Window->draw(backBar);

	sf::Text modeText;
	if (_Mode == EditMode::PlayerStartMode) modeText.setString("Player Start Pos:");
	else if (_Mode == EditMode::GridSizeMode) modeText.setString("Grid Size:");
	else if (_Mode == EditMode::TileSpriteMode) modeText.setString("Tile Sprite:");
	else if (_Mode == EditMode::TileSolidMode) modeText.setString("Tile Solid:");
	else if (_Mode == EditMode::AddEnemyMode) modeText.setString("Add Enemy:");
	else if (_Mode == EditMode::EnemyMoveMode) modeText.setString("Enemy Movement:");
	else if (_Mode == EditMode::AddPickupMode) modeText.setString("Add Pickup:");
	modeText.setFont(_Font);
	modeText.setFillColor(sf::Color::White);
	modeText.setPosition(5.f, _Window->getSize().y - (15.f + modeText.getLocalBounds().height));
	_Window->draw(modeText);

	sf::Text rightText;
	if (_Mode == EditMode::PlayerStartMode) rightText.setString("[" + IntToString(_Level.GetPlayerStart()._A) + "," + IntToString(_Level.GetPlayerStart()._B) + "]");
	else if (_Mode == EditMode::GridSizeMode) rightText.setString("[" + IntToString(_Level.GetGrid().GetWidth()) + "," + IntToString(_Level.GetGrid().GetHeight()) + "]");
	else if (_Mode == EditMode::TileSpriteMode) rightText.setString("Hold Ctrl to show tilesheet.");
	else if (_Mode == EditMode::TileSolidMode) rightText.setString("L-Click to toggle.");
	else if (_Mode == EditMode::AddEnemyMode) rightText.setString("");
	else if (_Mode == EditMode::EnemyMoveMode) rightText.setString("");
	else if (_Mode == EditMode::AddPickupMode) rightText.setString("");
	rightText.setFont(_Font);
	rightText.setFillColor(sf::Color::White);
	rightText.setPosition(_Window->getSize().x - (5.f + rightText.getLocalBounds().width), _Window->getSize().y - (15.f + modeText.getLocalBounds().height));
	_Window->draw(rightText);

	if (_Mode == EditMode::TileSpriteMode)
	{
		sf::Sprite tileSelection;
		tileSelection.setPosition((_Window->getSize().x - 32.f) / 2.f, _Window->getSize().y - 37.f);
		tileSelection.setTexture(*_ImgMan.GetTexturePntr("Tilesheet"));
		tileSelection.setTextureRect(sf::IntRect(_TileX * 32, _TileY * 32, 32, 32));
		_Window->draw(tileSelection);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			sf::Sprite tileSheet;
			tileSheet.setTexture(*_ImgMan.GetTexturePntr("Tilesheet"));
			tileSheet.setPosition(0.f, 0.f);
			_Window->draw(tileSheet);

			sf::RectangleShape tileRect;
			tileRect.setPosition((float)_TileX * 32, (float)_TileY * 32);
			tileRect.setSize(sf::Vector2f(32.f, 32.f));
			tileRect.setFillColor(sf::Color::Transparent);
			tileRect.setOutlineColor(sf::Color::Red);
			tileRect.setOutlineThickness(1.f);
			_Window->draw(tileRect);
		}
	}

	if (_ShowLog)
		Console::C()->Draw(_Window);

	_Window->setView(_CameraView);
};

void EditorScene::RefreshTiles()
{
	_CompositeBuilder.BuildCompositeTex(_Level.BuildSpriteCoordGrid(), &_CompositeTex);
};
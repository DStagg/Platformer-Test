#include "MainScene.h"

MainScene::MainScene(sf::RenderWindow* rw) : SFMLScene(rw)
{
	
};
MainScene::~MainScene()
{

};

void MainScene::Begin()
{
	_CameraView = _Window->getDefaultView();

	_DrawLog = false;

	_ImgMan.SetDirectory("Resources");
	_ImgMan.LoadTextureFromFile("Tilesheet", "Tilesheet.png");

	sf::Image img = _ImgMan.GetTexturePntr("Tilesheet")->copyToImage();
	
	CompositeBuilder builder(img,PairInt(32,32));

	_Level.Load("Level.sav");

	builder.BuildCompositeTex(_Level.BuildSpriteCoordGrid(), &_CompositeTex);

	_Font.loadFromFile("Resources\\Roboto-Regular.ttf");

	Console::C()->Init(_Font, ConsoleTextSize, ConsoleLineLimit);

	_MouseInput.Init(_Window);

};
void MainScene::End()
{
	Console::C()->DumpLog("Testlog");
};
void MainScene::Pause()
{

};
void MainScene::Resume()
{

};
void MainScene::Update(float dt)
{
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			GetManager()->Quit();
		else if (Event.type == sf::Event::KeyPressed)
			switch (Event.key.code) 
			{
			case sf::Keyboard::Escape:
				GetManager()->Quit();
			case sf::Keyboard::F1:
				_DrawLog = !_DrawLog;
				break;
			case sf::Keyboard::Left:
				_EditMode -= 1;
				if (_EditMode < 0) _EditMode = 0;
				break;
			case sf::Keyboard::Right:
				_EditMode += 1;
				if (_EditMode > PhysEditMode::JUMPTIME) _EditMode = PhysEditMode::JUMPTIME;
				break;
			case sf::Keyboard::Up:
				if (_EditMode == PhysEditMode::XACCEL) _Level.GetPlayer()._PhysStats._XAccel += 25.f;
				else if (_EditMode == PhysEditMode::XMAX) _Level.GetPlayer()._PhysStats._MaxXVel += 25.f;
				else if (_EditMode == PhysEditMode::XDECEL) _Level.GetPlayer()._PhysStats._XDecel += 25.f;
				else if (_EditMode == PhysEditMode::GRAVITY) _Level.GetPlayer()._PhysStats._YAccel += 25.f;
				else if (_EditMode == PhysEditMode::YMAX) _Level.GetPlayer()._PhysStats._MaxYVel += 25.f;
				else if (_EditMode == PhysEditMode::JUMPVEL) _Level.GetPlayer()._PhysStats._JumpVel += 25.f;
				else _Level.GetPlayer()._PhysStats._JumpTimeLimit += 0.05f;
				break;
			case sf::Keyboard::Down:
				if (_EditMode == PhysEditMode::XACCEL) _Level.GetPlayer()._PhysStats._XAccel -= 25.f;
				else if (_EditMode == PhysEditMode::XMAX) _Level.GetPlayer()._PhysStats._MaxXVel -= 25.f;
				else if (_EditMode == PhysEditMode::XDECEL) _Level.GetPlayer()._PhysStats._XDecel -= 25.f;
				else if (_EditMode == PhysEditMode::GRAVITY) _Level.GetPlayer()._PhysStats._YAccel -= 25.f;
				else if (_EditMode == PhysEditMode::YMAX) _Level.GetPlayer()._PhysStats._MaxYVel -= 25.f;
				else if (_EditMode == PhysEditMode::JUMPVEL) _Level.GetPlayer()._PhysStats._JumpVel -= 25.f;
				else _Level.GetPlayer()._PhysStats._JumpTimeLimit -= 0.05f;
				break;
			default:
				break;
			}
	}

	_Level.Update(dt);

	Console::C()->Clear();
	Log("Player Physics: ");
	Log("X: Vel: " + FloatToString(_Level.GetPlayer()._Velocity._X) + " | Accel: " + FloatToString(_Level.GetPlayer()._PhysStats._XAccel) + " | Max: " + FloatToString(_Level.GetPlayer()._PhysStats._MaxXVel) + " | Dec: " + FloatToString(_Level.GetPlayer()._PhysStats._XDecel));
	Log("Y: Vel: " + FloatToString(_Level.GetPlayer()._Velocity._Y) + " | Gravity: " + FloatToString(_Level.GetPlayer()._PhysStats._YAccel) + " | Max: " + FloatToString(_Level.GetPlayer()._PhysStats._MaxYVel));
	Log("Jump: Vel: " + FloatToString(_Level.GetPlayer()._PhysStats._JumpVel) + " | Delay: " + FloatToString(_Level.GetPlayer()._PhysStats._JumpTimeLimit));
	std::string phys_mode = "";
	if (_EditMode == PhysEditMode::XACCEL) phys_mode = "X Acceleration";
	else if (_EditMode == PhysEditMode::XMAX) phys_mode = "X Max. Vel.";
	else if (_EditMode == PhysEditMode::XDECEL) phys_mode = "X Deceleration";
	else if (_EditMode == PhysEditMode::GRAVITY) phys_mode = "Gravity";
	else if (_EditMode == PhysEditMode::YMAX) phys_mode = "Y Max. Vel.";
	else if (_EditMode == PhysEditMode::JUMPVEL) phys_mode = "Jump Vel.";
	else phys_mode = "Jump Grace Time";
	Log("---");
	Log("Editing: " + phys_mode);
	//	Asymptotic Averaging
	//	Ratio can be anything  - just make sure it equals 1.f. Lower followFactor = faster zoom.
	float followFactor = 0.99f;
	_CameraView.setCenter((_CameraView.getCenter().x * followFactor) + (_Level.GetPlayer()._Position.GetX() * (1.f - followFactor)), (_CameraView.getCenter().y * followFactor) + (_Level.GetPlayer()._Position.GetY() * (1.f - followFactor)) );
};
void MainScene::DrawScreen()
{
	_Window->setView(_CameraView);

	sf::Sprite temp = _CompositeTex.BuildSprite();
	_Window->draw(temp);

	_Level.Draw(_Window);

	_Window->setView(_Window->getDefaultView());	

	if (_DrawLog)
		Console::C()->Draw(_Window);

	_Window->setView(_CameraView);
};

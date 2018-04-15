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
			default:
				break;
			}
	}

	_Level.Update(dt);

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

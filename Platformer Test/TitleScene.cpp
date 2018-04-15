#include "TitleScene.h"

TitleScene::TitleScene(sf::RenderWindow* rw) : SFMLScene(rw)
{
	
};

TitleScene::~TitleScene()
{

};

void TitleScene::Begin()
{
	_Font.loadFromFile("Resources\\Roboto-Regular.ttf");

	_MenuList.Format(_Font, _Window->getSize().x / 2.f, _Window->getSize().y / 2.f, SFMLMenuList::Orientation::Center);
	_MenuList.SetBuffers(10.f, 10.f);
	std::vector<std::string> choices;
	choices.push_back("Play Level");
	choices.push_back("Edit Level");
	choices.push_back("Quit");
	_MenuList.Populate(choices);
};

void TitleScene::End()
{

};

void TitleScene::Pause()
{

};

void TitleScene::Resume()
{

};

void TitleScene::Update(float dt)
{
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			GetManager()->Quit();
		else if (Event.type == sf::Event::KeyPressed)
		{
			if (Event.key.code == sf::Keyboard::Key::Escape)
				GetManager()->Quit();
			else if (Event.key.code == sf::Keyboard::Key::Return)
			{
				if (_MenuList.GetChoice() == 0)
					GetManager()->PushScene(new MainScene(_Window), new FadeTransition(_Window, 1.f));
				else if (_MenuList.GetChoice() == 1)
					GetManager()->PushScene(new EditorScene(_Window), new FadeTransition(_Window, 1.f));
				else
					GetManager()->Quit();
			}
			else if (Event.key.code == sf::Keyboard::Up)
				_MenuList.DecChoice();
			else if (Event.key.code == sf::Keyboard::Down)
				_MenuList.IncChoice();
		}
	}
};

void TitleScene::DrawScreen()
{
	/*
	sf::Text winMsg;
	winMsg.setString("Title Screen");
	winMsg.setFont(_Font);
	winMsg.setFillColor(sf::Color::White);
	winMsg.setPosition((_Window->getSize().x - winMsg.getGlobalBounds().width) / 2.f, (_Window->getSize().y - winMsg.getGlobalBounds().height) / 2.f);
	_Window->draw(winMsg);

	winMsg.setString("Press Enter to begin, or Esc to quit.");
	winMsg.setPosition((_Window->getSize().x - winMsg.getGlobalBounds().width) / 2.f, ((_Window->getSize().y - winMsg.getGlobalBounds().height) / 2.f) + 100.f);
	_Window->draw(winMsg);
	*/
	_MenuList.Draw(_Window);
};
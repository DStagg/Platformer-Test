#include "Framework/SFMLScene.h"
#include "TitleScene.h"
#include "MainScene.h"

int main()
{
	int FramesPerSecond = 60;
	float deltaT = 0.f;
	sf::Clock UpdateClock;

	sf::RenderWindow _Window;
	_Window.create(sf::VideoMode(640, 640), "SFML Window");

	SceneManager SCM;
	SCM.PushScene(new TitleScene(&_Window));

	UpdateClock.restart();
	while (SCM.GetActiveScenePntr() != 0)
	{
		if (SCM.GetTransitionPntr() != 0)
			SCM.GetTransitionPntr()->Update(UpdateClock.restart().asSeconds());
		else
			SCM.GetActiveScenePntr()->Update(UpdateClock.restart().asSeconds());
		_Window.clear();
		if (SCM.GetTransitionPntr() != 0)
			SCM.GetTransitionPntr()->DrawScreen();
		else
			SCM.GetActiveScenePntr()->DrawScreen();
		_Window.display();
		SCM.CullScenes();
	}

	return 0;
};
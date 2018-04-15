#include "SceneTransitions.h"

FadeTransition::FadeTransition(sf::RenderWindow* rw, float time) : SFMLSceneTransition(rw)
{
	_TransitionTime = time;
};

void FadeTransition::Update(float dt)
{
	_ElapsedTime += dt;

	if (_ElapsedTime >= _TransitionTime)
		_ManagerPntr->CompleteTransition();
};

void FadeTransition::DrawScreen()
{
	if (this->_Window == 0)
		return;

	if (_ElapsedTime < _TransitionTime / 2.f)
	{
		if (_Scene1 != 0)
			_Scene1->DrawScreen();
		sf::RectangleShape cover;
		cover.setSize(sf::Vector2f((float)_Window->getSize().x, (float)_Window->getSize().y));
		cover.setPosition(0.f, 0.f);
		cover.setFillColor(sf::Color(0, 0, 0, (sf::Uint8)(_ElapsedTime / (_TransitionTime / 2.f)) * 255));
		_Window->draw(cover);
	}
	else
	{
		if (_Scene2 != 0)
			_Scene2->DrawScreen();
		sf::RectangleShape cover;
		cover.setSize(sf::Vector2f((float)_Window->getSize().x, (float)_Window->getSize().y));
		cover.setPosition(0.f, 0.f);
		float timeOverHalf = _ElapsedTime - (_TransitionTime / 2.f);
		float fadeInProp = timeOverHalf / (_TransitionTime / 2.f);
		int alphaValue = 255 - (int)(fadeInProp * 255);
		cover.setFillColor(sf::Color(0, 0, 0, alphaValue));
		_Window->draw(cover);
	}	
};

DelayTransition::DelayTransition(sf::RenderWindow* rw, float time) : SFMLSceneTransition(rw)
{
	_TransitionTime = time;
}

void DelayTransition::Update(float dt)
{
	_ElapsedTime += dt;

	if (_ElapsedTime >= _TransitionTime)
		_ManagerPntr->CompleteTransition();
};

void DelayTransition::DrawScreen()
{
	if (_Scene1 != 0)
		_Scene1->DrawScreen();
};
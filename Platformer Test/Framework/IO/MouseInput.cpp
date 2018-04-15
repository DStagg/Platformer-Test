#include "MouseInput.h"

SFMLMouseInput::SFMLMouseInput(sf::RenderWindow* rw)
{
	Init(rw);
};

void SFMLMouseInput::Init(sf::RenderWindow* rw)
{
	_Window = rw;
};

PairInt SFMLMouseInput::GetScreenPos()
{
	return PairInt(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
};

PairInt SFMLMouseInput::GetWindowPos()
{
	if (_Window == 0)
		return GetScreenPos();
	return PairInt(sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y);
};

PairInt SFMLMouseInput::GetWorldPos()
{
	PairInt results = GetWindowPos();
	if (_Window != 0)
	{
		results._A += (int)_Window->getView().getCenter().x - (int)(_Window->getView().getSize().x / 2.f);
		results._B += (int)_Window->getView().getCenter().y - (int)(_Window->getView().getSize().y / 2.f);
	}
	return results;
};
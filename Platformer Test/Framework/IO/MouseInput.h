#ifndef MOUSE_INPUT_H
#define MOUSE_INPUT_H

#include "SFML\Graphics.hpp"
#include "..\Data\Pair.h"

class MouseInput
{
public:

	virtual PairInt GetScreenPos() = 0;
	virtual PairInt GetWindowPos() = 0;
	virtual PairInt GetWorldPos() = 0;
};

class SFMLMouseInput
{
public:

	SFMLMouseInput(sf::RenderWindow* rw = 0);

	void Init(sf::RenderWindow* rw);

	PairInt GetScreenPos();
	PairInt GetWindowPos();
	PairInt GetWorldPos();

private:

	sf::RenderWindow* _Window;
};


#endif
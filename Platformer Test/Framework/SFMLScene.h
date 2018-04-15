#ifndef SFML_SCENE_H
#define SFML_SCENE_H

#include "Scenes\Scene.h"
#include "SFML\Graphics.hpp"

class SFMLScene : public Scene
{
public:

	SFMLScene(sf::RenderWindow* rw);

	virtual void Begin() = 0;
	virtual void End() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Update(float dt) = 0;
	virtual void DrawScreen() = 0;

protected:

	sf::RenderWindow* _Window = 0;
};

class SFMLSceneTransition : public SceneTransition
{
public:

	SFMLSceneTransition(sf::RenderWindow* rw);

	virtual void Update(float dt) = 0;
	virtual void DrawScreen() = 0;

	sf::RenderWindow* _Window = 0;
};

#endif
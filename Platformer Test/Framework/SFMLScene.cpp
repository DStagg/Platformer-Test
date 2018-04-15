#include "SFMLScene.h"

SFMLScene::SFMLScene(sf::RenderWindow* rw) : Scene()
{
	_Window = rw;
};

SFMLSceneTransition::SFMLSceneTransition(sf::RenderWindow* rw) : SceneTransition()
{
	_Window = rw;
};
#ifndef SCENE_TRANSITION_H
#define SCENE_TRANSITION_H

#include "Framework\SFMLScene.h"

class FadeTransition : public SFMLSceneTransition
{
public:

	FadeTransition(sf::RenderWindow* rw, float time);

	void Update(float dt);
	void DrawScreen();

private:

	float _TransitionTime;
	float _ElapsedTime = 0.f;
};

class DelayTransition : public SFMLSceneTransition
{
public:

	DelayTransition(sf::RenderWindow* rw, float time);

	void Update(float dt);
	void DrawScreen();

private:

	float _TransitionTime;
	float _ElapsedTime = 0.f;
};

#endif
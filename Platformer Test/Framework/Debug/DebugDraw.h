#ifndef DEBUG_DRAW_H
#define DEBUG_DRAW_H

#include "..\Data\Collision.h"
#include <SFML\Graphics.hpp>

void DebugDrawMask(AABBMask mask, sf::RenderWindow* rw, sf::Color col = sf::Color::White);
void DebugDrawMask(CircleMask mask, sf::RenderWindow* rw, sf::Color col = sf::Color::White);
void DebugDrawAABB(AABB box, sf::RenderWindow* rw, sf::Color col = sf::Color::White);
void DebugDrawCirc(Circle circ, sf::RenderWindow* rw, sf::Color col = sf::Color::White);

#endif
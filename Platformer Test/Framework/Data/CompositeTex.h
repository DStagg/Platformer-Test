#ifndef COMPOSITE_TEX_H
#define COMPOSITE_TEX_H

#include "SFML\Graphics.hpp"
#include "Grid.h"
#include "Pair.h"

//	CompositeTex holds an internal texture representing the entire composite image (such as a tiled map)
//	This can then generate a sprite representing a specific section
class CompositeTex
{
public:

	CompositeTex();
	~CompositeTex();
 
	sf::Sprite BuildSprite();
	sf::Sprite BuildSprite(PairInt topLeft, PairInt size);
	
	sf::Texture* GetTexPntr();

private:

	sf::Texture _Texture;
};

/*	CompositeBuilder generates a CompositeTex from:
1. a 2-d grid of values;
2. a tilesheet; and
3. a pair of tile dimensions.
Preload it with the generic data in the constructor (tilesheet, tile dimensions) for rapid generation of multiple composites.
Feed in the data specific to the desire composite (value grid) in the BuildCompositeTex() function.
*/
class CompositeBuilder
{
public:

	CompositeBuilder();
	CompositeBuilder(sf::Image tilesheet, PairInt tile_size);
	~CompositeBuilder();

	void BuildCompositeTex(Grid<PairInt> grid, CompositeTex* comp);

private:

	sf::Image	_TileSheet;
	PairInt		_TileSize;
};

//	Usage Example: preload a CompositeBuilder with a specific terrain's tilesheet and tile sizes, then generate new maps
//		as individual CompositeTexs.

//	NOTE: is the use of CompositeTex necessary? Could we not just build ordinary sf::Textures and then have a subsection function?

#endif
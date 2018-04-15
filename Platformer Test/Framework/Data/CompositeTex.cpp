#include "CompositeTex.h"

//	CompositeText
CompositeTex::CompositeTex()
{

};
CompositeTex::~CompositeTex()
{

};

sf::Sprite CompositeTex::BuildSprite()
{
	return BuildSprite(PairInt(0, 0), PairInt(_Texture.getSize().x, _Texture.getSize().y));
}

sf::Sprite CompositeTex::BuildSprite(PairInt topLeft, PairInt size)
{
	sf::Sprite tempspr(_Texture);

	tempspr.setTextureRect(sf::IntRect(topLeft._A, topLeft._B, size._A, size._B));

	return tempspr;
};

sf::Texture* CompositeTex::GetTexPntr()
{
	return &_Texture;
};
/////////////////

//	CompositeBuilder
CompositeBuilder::CompositeBuilder()
{

};
CompositeBuilder::CompositeBuilder(sf::Image tilesheet, PairInt tile_size)
{
	_TileSheet = tilesheet;
	_TileSize = tile_size;
};
CompositeBuilder::~CompositeBuilder()
{

};

void CompositeBuilder::BuildCompositeTex(Grid<PairInt> grid, CompositeTex* comp)
{
	//	Sanity check for all of the data (3 x generic, 2 x specific)
	if ((_TileSheet.getSize().x == 0) && (_TileSheet.getSize().y == 0))
		return;
	if ((_TileSize._A <= 0) || (_TileSize._B <= 0))
		return;
	if (comp == 0)
		return;
	if ((grid.GetWidth() == 0) || (grid.GetHeight() == 0))
		return;

	//	Build the blank texture of the correct dimensions
	comp->GetTexPntr()->create((unsigned int)(grid.GetWidth() * _TileSize._A), (unsigned int)(grid.GetHeight() * _TileSize._B));
	
	//	Create a temporary blank image of the correct dimensions
	sf::Image tempimg;
	tempimg.create((unsigned int)(grid.GetWidth() * _TileSize._A), (unsigned int)(grid.GetHeight() * _TileSize._B));

	//	Loop through each cell
	for (int x = 0; x < grid.GetWidth(); x++)
		for (int y = 0; y < grid.GetHeight(); y++)
		{
			//	Pull the cell value from grid, translate it into tilesheet coordinates using _Dictionary, copy from _TileSheet		
			tempimg.copy(_TileSheet, x * _TileSize._A, y * _TileSize._B, sf::IntRect(
				grid.GetCell(x,y)._A * _TileSize._A,
				grid.GetCell(x,y)._B * _TileSize._B,
				_TileSize._A , 
				_TileSize._B)
			);
		}

	//	Load the created composite image into the CompositeTex's internal texture
	comp->GetTexPntr()->loadFromImage(tempimg);
};
////////////////////


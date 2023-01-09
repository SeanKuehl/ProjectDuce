#pragma once
#include "AllegroHelper.h"
#include <string>
#include <vector>
#include "Tile.h"


class GridManager
{

private:
	int gridStartX;
	int gridStartY;
	int dimension;	//is the grid 10*10 etc.
	int tileWidth;
	int tileHieght;
	int xOffset = 5;	//horizontal space between tiles
	int yOffset = 5;	//vertical space between tiles
	std::vector<Tile> tileGrid;


public:
	GridManager(int startX, int startY, int squareDimension);

	void CreateGrid();

	void Render();

	void Destroy();

};


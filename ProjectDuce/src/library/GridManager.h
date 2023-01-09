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

	std::vector<int> GetSoldierCoords(int row, int column);

	std::vector<int> GetSoldierCoordsFromMouse(int x, int y);

	int GetTileWidth();

	int GetTileHieght();
	
	int GetXOffset();

	int GetYOffset();

	

	void Render();

	void Destroy();

};


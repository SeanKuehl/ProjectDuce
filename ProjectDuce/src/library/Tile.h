#pragma once
#include "AllegroHelper.h"
#include <string>
#include <vector>


class Tile
{
protected:
	std::string imageName = "assets/images/tile.png";	//from ProjectDuce project folder
	ALLEGRO_BITMAP* image;
	int xPosition;	//pos is top left of image
	int yPosition;
	int width;
	int hieght;
	int gridX;
	int gridY;


public:
	Tile(int x, int y, int gridX, int gridY);

	int GetTileWidth();

	int GetTileHieght();

	std::vector<int> GetXYCoords();

	std::vector<int> GetGridCoords();

	std::vector<int> GetSoldierCoords();

	bool Contains(int x, int y);

	void Render();

	void Destroy();

};


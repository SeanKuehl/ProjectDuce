#include "Tile.h"


Tile::Tile(int x, int y, int passedGridX, int passedGridY) {

	image = CreateImage(imageName);	//image name includes file extension
	xPosition = x;
	yPosition = y;
	gridX = passedGridX;
	gridY = passedGridY;
	hieght = al_get_bitmap_height(image);
	width = al_get_bitmap_width(image);
}

std::vector<int> Tile::GetGridCoords() {
	std::vector<int> coords = { gridX, gridY };
	return coords;
}


int Tile::GetTileWidth() {
	return width;
}

int Tile::GetTileHieght() {
	return hieght;
}


std::vector<int> Tile::GetSoldierCoords() {
	//get coords for soldier's top left coords
	//currently soldier image is 40*40 pixels and tile image is 30*30,
	//so that's where the 5 comes from (10/2 so soldier is centered on tile)
	int x = xPosition + 5;
	int y = yPosition + 5;
	std::vector<int> newVec;
	newVec.push_back(x);
	newVec.push_back(y);
	return newVec;
}

bool Tile::Contains(int x, int y) {
	if (x >= xPosition && x <= (xPosition + width)) {
		if (y >= yPosition && y <= (yPosition + hieght)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

std::vector<int> Tile::GetXYCoords() {
	std::vector<int> coords = { xPosition, yPosition, width, hieght };
	return coords;
}

void Tile::Render() {

	

	al_draw_bitmap(image, xPosition, yPosition, 0);

}

void Tile::Destroy() {
	al_destroy_bitmap(image);
}
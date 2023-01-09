#include "Tile.h"


Tile::Tile(int x, int y) {

	image = CreateImage(imageName);	//image name includes file extension
	xPosition = x;
	yPosition = y;
	hieght = al_get_bitmap_height(image);
	width = al_get_bitmap_width(image);
}

int Tile::GetTileWidth() {
	return width;
}

int Tile::GetTileHieght() {
	return hieght;
}


void Tile::Render() {

	

	al_draw_bitmap(image, xPosition, yPosition, 0);

}

void Tile::Destroy() {
	al_destroy_bitmap(image);
}
#include "Tile.h"

/*! Create a new tile with xy and grid coords
*   \param x the x coordinate at which to create the tile
*   \param y the y coordinate at which to creeate the tile
*   \param passedGridX the grid x coordinate of the tile
*   \param passedGridY the grid y coordinate of the tile 
*/
Tile::Tile(int x, int y, int passedGridX, int passedGridY) {

	image = CreateImage(imageName);	//image name includes file extension
	xPosition = x;
	yPosition = y;
	gridX = passedGridX;
	gridY = passedGridY;
	hieght = al_get_bitmap_height(image);
	width = al_get_bitmap_width(image);
}

/*! return the tile's grid coordinates in a vector<int>
*/
std::vector<int> Tile::GetGridCoords() {
	std::vector<int> coords = { gridX, gridY };
	return coords;
}

/*! return the int width of the tile
*/
int Tile::GetTileWidth() {
	return width;
}

/*! return the int hieght of the tile
*/
int Tile::GetTileHieght() {
	return hieght;
}

/*! return the coordinates at which to draw a soldier
*   on the tile
*/
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

/*! determine wheather or not the tile contains
*   the xy coords within it. Return true if it does
*   and false if it does not.
*   \param x the x coord to check falls within tile
*   \param y the y coord to check falls within tile
*/
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

/*! Return the tile's xy coords. Leftmost x(xPosition),
*   topmost y(yPosition), with and hieght
*/
std::vector<int> Tile::GetXYCoords() {
	std::vector<int> coords = { xPosition, yPosition, width, hieght };
	return coords;
}

/*! render the tile  to the screen
*/
void Tile::Render() {

	

	al_draw_bitmap(image, xPosition, yPosition, 0);

}

/*! destroy the tile
*/
void Tile::Destroy() {
	al_destroy_bitmap(image);
}
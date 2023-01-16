#include "GridManager.h"



/*! Given starting xy coords, and the dimension(s) of a grid,
*   create a new grid manager.
*   \param startX the starting x coordinate of the grid
*   \param startY the starting y coordinate of the grid
*   \param squareDimension the dimension of the grid(dimension is 10, grid is 10*10 for example)
*/
GridManager::GridManager(int startX, int startY, int squareDimension) {
	gridStartX = startX;
	gridStartY = startY;
	dimension = squareDimension;
	Tile temp = Tile(0, 0, 0, 0);
	tileWidth = temp.GetTileWidth();
	tileHieght = temp.GetTileHieght();
}

/*! Create Tile objects to create a grid
*/
void GridManager::CreateGrid() {
	int activeX = gridStartX;
	int activeY = gridStartY;
	for (int i = 0; i < dimension; i++) {
		for (int k = 0; k < dimension; k++) {
			tileGrid.push_back(Tile(activeX, activeY, i, k));
			activeX += tileWidth + xOffset;
		}
		activeY += tileHieght + yOffset;
		activeX = gridStartX;
	}

}

/*! Return the int with of the tiles
*/
int GridManager::GetTileWidth() {
	return tileWidth;
}

/*! Return the hieght(int) of the tiles
*/
int GridManager::GetTileHieght() {
	return tileHieght;
}

/*! Return the int x offset of where to draw soldiers and bullets
*   for tiles
*/
int GridManager::GetXOffset() {
	return xOffset;
}

/*! Return the int y offset of where to draw soldiers and bullets
*   for tiles
*/
int GridManager::GetYOffset() {
	return yOffset;
}

/*! Given mouse click coords of a tile, get the coords
*   to draw a soldier at. Return {-1, -1} if no tile clicked on
*   and tile's soldier draw coords if one clicked on.
*   Return as vector<int>
*   \param x x click coords of mouse
*   \param y y click coords of mouse
*/
std::vector<int> GridManager::GetSoldierCoordsFromMouse(int x, int y) {
	for (int i = 0; i < tileGrid.size(); i++) {
		if (tileGrid.at(i).Contains(x, y)) {
			return tileGrid.at(i).GetSoldierCoords();
		}
	
	}
	std::vector<int> placeHolder = { -1,-1 };
	return placeHolder;
}

/*! Given the row and column of a tile, get the
*   coords needed to draw a soldier/bullet on that tile.
*   Return as a vector<int>
*   \param row the row of the tile to get the soldier coords of
*   \param column the column of the tile to get the soldier coords of
*/
std::vector<int> GridManager::GetSoldierCoords(int row, int column) {

	int placement = ((row - 1) * dimension) + (column-1);
	std::vector<int> toReturn = tileGrid.at(placement).GetSoldierCoords();
	return toReturn;
}

/*! Given the x and y coords of a tile,
*   get it's grid coords. Return vector<int> of coords
*   \param x the x coords of the tile to get grid coords from
*   \param y the y coords of the tile to get grid coords from
*/
std::vector<int> GridManager::GetGridCoords(int x, int y) {
	std::vector<int> coords;
	for (int i = 0; i < tileGrid.size(); i++) {
		if (tileGrid.at(i).Contains(x, y)) {
			//get it's grid pos
			coords = tileGrid.at(i).GetGridCoords();
		}
	}
	return coords;
}

/*! Given the grid coords of a tile,
*   get the xy coords of a tile. Returning as vector<int>
*   \param x the grid x coord of a tile
*   \param y the grid y coord of a tile
*/
std::vector<int> GridManager::GetTileCoordsFromGridCoords(int x, int y) {
	//x and y are already adjusted to work with the grid, so no need for -1
	int placement = ((x) * dimension) + (y);
	std::vector<int> toReturn = tileGrid.at(placement).GetXYCoords();
	return toReturn;
}

/*! return the int dimension of the grid
*/
int GridManager::GetDimension() {
	return dimension;
}

/*! Render all tiles in manager's tileGrid
*/
void GridManager::Render() {
	for (int i = 0; i < tileGrid.size(); i++) {
		tileGrid.at(i).Render();
	}
}


/*! Destroy all tiles in manager's tileGrid
*/
void GridManager::Destroy() {
	for (int i = 0; i < tileGrid.size(); i++) {
		tileGrid.at(i).Destroy();
	}
}
#include "GridManager.h"




GridManager::GridManager(int startX, int startY, int squareDimension) {
	gridStartX = startX;
	gridStartY = startY;
	dimension = squareDimension;
	Tile temp = Tile(0, 0, 0, 0);
	tileWidth = temp.GetTileWidth();
	tileHieght = temp.GetTileHieght();
}


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

int GridManager::GetTileWidth() {
	return tileWidth;
}

int GridManager::GetTileHieght() {
	return tileHieght;
}

int GridManager::GetXOffset() {
	return xOffset;
}

int GridManager::GetYOffset() {
	return yOffset;
}

std::vector<int> GridManager::GetSoldierCoordsFromMouse(int x, int y) {
	for (int i = 0; i < tileGrid.size(); i++) {
		if (tileGrid.at(i).Contains(x, y)) {
			return tileGrid.at(i).GetSoldierCoords();
		}
	
	}
	std::vector<int> placeHolder = { -1,-1 };
	return placeHolder;
}

std::vector<int> GridManager::GetSoldierCoords(int row, int column) {

	int placement = ((row - 1) * dimension) + (column-1);
	std::vector<int> toReturn = tileGrid.at(placement).GetSoldierCoords();
	return toReturn;
}

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

std::vector<int> GridManager::GetTileCoordsFromGridCoords(int x, int y) {
	//x and y are already adjusted to work with the grid, so no need for -1
	int placement = ((x) * dimension) + (y);
	std::vector<int> toReturn = tileGrid.at(placement).GetXYCoords();
	return toReturn;
}

int GridManager::GetDimension() {
	return dimension;
}


void GridManager::Render() {
	for (int i = 0; i < tileGrid.size(); i++) {
		tileGrid.at(i).Render();
	}
}



void GridManager::Destroy() {
	for (int i = 0; i < tileGrid.size(); i++) {
		tileGrid.at(i).Destroy();
	}
}
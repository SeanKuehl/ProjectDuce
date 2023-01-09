#include "GridManager.h"




GridManager::GridManager(int startX, int startY, int squareDimension) {
	gridStartX = startX;
	gridStartY = startY;
	dimension = squareDimension;
	Tile temp = Tile(0, 0);
	tileWidth = temp.GetTileWidth();
	tileHieght = temp.GetTileHieght();
}


void GridManager::CreateGrid() {
	int activeX = gridStartX;
	int activeY = gridStartY;
	for (int i = 0; i < dimension; i++) {
		for (int k = 0; k < dimension; k++) {
			tileGrid.push_back(Tile(activeX, activeY));
			activeX += tileWidth + xOffset;
		}
		activeY += tileHieght + yOffset;
		activeX = gridStartX;
	}

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
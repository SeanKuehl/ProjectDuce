#include "BuildingManager.h"

/*! create a BuildingManager object
*/
BuildingManager::BuildingManager() {

}

/*! Given xy coords, allegiance and grid row and column
*   create a new Base building and add it to the buildingList
*   for management by the object.
*   \param coords the x and y coords of the base
*   \param passedAllegiance the side(player 1 or 2) the building belongs to
*   \param row the row of the grid where the building is placed(if grid is 10*10, row is 1-10)
*   \param column the column of the grid where the building is placed(if grid is 10*10, row is 1-10)
*/
void BuildingManager::CreateBase(std::vector<int> coords, int passedAllegiance, int row, int column) {
	printf("%d, %d\n", row, column);
	if (passedAllegiance == PLAYER_ONE) {
		buildingList.push_back(Building((buildingImageDirectory + playerOneBaseImage), coords, passedAllegiance, row, column));
	}
	else {
		buildingList.push_back(Building((buildingImageDirectory + playerTwoBaseImage), coords, passedAllegiance, row, column));
	}
	
}

/*! Set the Building Manager's internal player turn variable
*   to prevent things getting out of sync
*/
void BuildingManager::SetPlayerTurn(int passedTurn) {
	playerTurn = passedTurn;
}

/*! Given the x and y coords of a mouse's left click,
*   check if the right allegiance of building was clicked
*   on to trigger an event. If a building was clicked on, 
*   return a vector<int> of building's grid coords for help 
*   placing created soldier. Otherwise return a vector<int> 
*   containing {-1,-1} to indicate no building was clicked on.
*   \param x the x coord of the mouse's left click
*   \param y the y coord of the mouse's left click
*/
std::vector<int> BuildingManager::HandleLeftClick(int x, int y) {
	//return grid coords to create soldier at
    
    for (int i = 0; i < buildingList.size(); i++) {
        if (buildingList.at(i).GetAllegiance() == playerTurn) {
            if (buildingList.at(i).ClickedOn(x, y)) {
                //create soldier, return bases current coords for reference
				return buildingList.at(i).GetGridCoords();
            }
        }
        else {
            //do nothing, it's not their turn
        }
    }

	std::vector<int> empty = { -1, -1 };
	return empty;

   

}

/*! Check wheather a building of the right allegiance was hit by a bullet
*   given allegiance, gridX and gridY. If a building was bit deal damage to it,
*   if this damage kills it return a game over event by returning true.
*   If the hit doesn't kill it or there is no building hit, return false.
*   \param allegiance the player who fired the short from one of thier soldiers
*   \param gridX the gridx coord of where the bullet hit
*   \param gridY the gridy coord of where the bullet hit
*/
bool BuildingManager::GetBuildingHit(int allegiance, int gridX, int gridY) {

	//allegiance is who fired the shot, so only hurt the opposite of allegiance
	for (int i = 0; i < buildingList.size(); i++) {
		if (buildingList.at(i).GetAllegiance() != allegiance) {
			printf("allegiance checks out\n");
			std::vector<int> buildingCoords = buildingList.at(i).GetGridCoords();
			
			//-1's for building coords because they are not adjusted for actual use with the grid/list
			if (gridX == (buildingCoords.at(0)-1) && gridY == (buildingCoords.at(1)-1)) {

				//the building was hit
				bool gameOver = buildingList.at(i).TakeHit();
				
				//check if building killed, if so, for now bases are only building
				//so trigger game over event
				if (gameOver) {
					return true;	//a base was destroyed and the game is over
				}

			}
		}
	}

	return false;

}

/*! Render all buildings in this object's buildingList
*/
void BuildingManager::Render() {
	for (int i = 0; i < buildingList.size(); i++) {
		buildingList.at(i).Render();
	}
}

/*! Destroy all building in this object's buildingList
*/
void BuildingManager::Destroy() {
	for (int i = 0; i < buildingList.size(); i++) {
		buildingList.at(i).Destroy();
	}
}
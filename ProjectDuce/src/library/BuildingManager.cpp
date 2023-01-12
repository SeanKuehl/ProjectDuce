#include "BuildingManager.h"


BuildingManager::BuildingManager() {

}


void BuildingManager::CreateBase(std::vector<int> coords, int passedAllegiance, int row, int column) {
	printf("%d, %d\n", row, column);
	if (passedAllegiance == PLAYER_ONE) {
		buildingList.push_back(Building((buildingImageDirectory + playerOneBaseImage), coords, passedAllegiance, row, column));
	}
	else {
		buildingList.push_back(Building((buildingImageDirectory + playerTwoBaseImage), coords, passedAllegiance, row, column));
	}
	
}

void BuildingManager::SetPlayerTurn(int passedTurn) {
	playerTurn = passedTurn;
}


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


void BuildingManager::Render() {
	for (int i = 0; i < buildingList.size(); i++) {
		buildingList.at(i).Render();
	}
}

void BuildingManager::Destroy() {
	for (int i = 0; i < buildingList.size(); i++) {
		buildingList.at(i).Destroy();
	}
}
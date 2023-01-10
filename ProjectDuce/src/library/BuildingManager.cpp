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
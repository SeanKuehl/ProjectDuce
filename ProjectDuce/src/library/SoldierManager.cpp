#include "SoldierManager.h"
#include "Bullet.h"

SoldierManager::SoldierManager(int passedTileWidth, int passedTileHieght, int passedXOffset, int passedYOffset) {
    tileWidth = passedTileWidth;
    tileHieght = passedTileHieght;
    xOffset = passedXOffset;
    yOffset = passedYOffset;
}


void SoldierManager::CreateSoldier(int passedAllegiance, std::vector<int> coords) {
	if (passedAllegiance == PLAYER_ONE) {
		playerOneUnits.push_back(Soldier(passedAllegiance, coords.at(0), coords.at(1)));
	}
	else {
		playerTwoUnits.push_back(Soldier(passedAllegiance, coords.at(0), coords.at(1)));
	}
}

void SoldierManager::SetPlayerTurn(int passedTurn) {
    playerTurn = passedTurn;
}

void SoldierManager::HandleLeftClick(int x, int y, std::vector<int> moveCoords) {
    std::vector<int> tileMeasures = { tileWidth, tileHieght, xOffset, yOffset };

    if (playerTurn == PLAYER_ONE) {
        //check if player one units were clicked on
        for (int i = 0; i < playerOneUnits.size(); i++) {
            if (playerOneUnits.at(i).ClickedOn(x, y)) {
                playerOneUnits.at(i).ToggleSelected();
            }
            else {
                if (playerOneUnits.at(i).GetSelected() == true && playerOneUnits.at(i).GetActionTaken() == false) {
                    //move to that position
                    playerOneUnits.at(i).Move(moveCoords.at(0), moveCoords.at(1), tileMeasures);
                    playerOneUnits.at(i).ToggleSelected();  //deselect
                    playerOneUnits.at(i).SetActionTaken(true);
                }
            }
        }
    }



    if (playerTurn == PLAYER_TWO) {
        //check if player two units were clicked on
        for (int i = 0; i < playerTwoUnits.size(); i++) {
            if (playerTwoUnits.at(i).ClickedOn(x, y)) {
                playerTwoUnits.at(i).ToggleSelected();
            }
            else {
                if (playerTwoUnits.at(i).GetSelected() == true && playerTwoUnits.at(i).GetActionTaken() == false) {
                    //move to that position

                    playerTwoUnits.at(i).Move(moveCoords.at(0), moveCoords.at(1), tileMeasures);
                    playerTwoUnits.at(i).ToggleSelected();  //deselect
                    playerTwoUnits.at(i).SetActionTaken(true);
                }
            }
        }
    }




}

bool SoldierManager::InRange(std::vector<int> moveCoords, int x, int y) {
    int tileSizeX = tileWidth + xOffset;
    int tileSizeY = tileHieght + yOffset;
    int range = 3;

    int xDist = abs(x - moveCoords.at(0));
    int yDist = abs(y - moveCoords.at(1));

    if (xDist > (range * tileSizeX)) {
        //out of range
        return false;
    }

    if (yDist > (range * tileSizeY)) {
        //out of range
        return false;
    }

    return true;

}


Bullet SoldierManager::HandleRightClick(int x, int y, std::vector<int> moveCoords) {

    if (playerTurn == PLAYER_ONE) {
        for (int i = 0; i < playerOneUnits.size(); i++) {
            if (playerOneUnits.at(i).GetSelected() == true && playerOneUnits.at(i).GetActionTaken() == false) {
                if (InRange(moveCoords, playerOneUnits.at(i).GetTopLeftX(), playerOneUnits.at(i).GetTopLeftY())) {
                    playerOneUnits.at(i).SetActionTaken(true);
                    return Bullet("bullet.png", playerOneUnits.at(i).GetAllegiance(), playerOneUnits.at(i).GetTopLeftX(), playerOneUnits.at(i).GetTopLeftY(), moveCoords.at(0), moveCoords.at(1));
                }
                else {
                    //don't shoot
                    return Bullet();
                }

            }
        }
    }

    if (playerTurn == PLAYER_TWO) {
        for (int i = 0; i < playerTwoUnits.size(); i++) {
            if (playerTwoUnits.at(i).GetSelected() == true && playerTwoUnits.at(i).GetActionTaken() == false) {
                if (InRange(moveCoords, playerTwoUnits.at(i).GetTopLeftX(), playerTwoUnits.at(i).GetTopLeftY())) {
                    playerTwoUnits.at(i).SetActionTaken(true);
                    return Bullet("bullet.png", playerTwoUnits.at(i).GetAllegiance(), playerTwoUnits.at(i).GetTopLeftX(), playerTwoUnits.at(i).GetTopLeftY(), moveCoords.at(0), moveCoords.at(1));
                }
                else {
                    return Bullet();
                }

            }
        }
    }


    return Bullet();



}



std::vector<int> SoldierManager::GetSoldierGridCoords(std::vector<int> gridCoords, int dimension) {
    //check if grid coords at -1, -1 as this is the null case
    std::vector<int> newCoords = { -1,-1 };
    if (gridCoords.at(0) == -1) {
        //it's the null case, don't do anything
    }
    else {
        //try to create a soldier one column to the right, or one column to the left of the coords
        if ((gridCoords.at(1) - 1) > 0) {
            //create soldier there
            
            newCoords = { gridCoords.at(0), gridCoords.at(1) - 1 };
        }
        else if ((gridCoords.at(1) + 1) < dimension){
            //create soldier there
            newCoords = { gridCoords.at(0), gridCoords.at(1) + 1 };
        }
        
    }
    return newCoords;
}

void SoldierManager::EndTurn() {
    for (int i = 0; i < playerOneUnits.size(); i++) {
        playerOneUnits.at(i).SetActionTaken(false);
    }

    for (int i = 0; i < playerTwoUnits.size(); i++) {
        playerTwoUnits.at(i).SetActionTaken(false);
    }
}


void SoldierManager::Render() {
    std::vector<int> tileMeasures = { tileWidth, tileHieght, xOffset, yOffset };
    

    for (int i = 0; i < playerOneUnits.size(); i++) {
        playerOneUnits.at(i).Render(tileMeasures);
    }

    for (int i = 0; i < playerTwoUnits.size(); i++) {
        playerTwoUnits.at(i).Render(tileMeasures);
    }

}

void SoldierManager::Destroy() {
    for (int i = 0; i < playerOneUnits.size(); i++) {
        playerOneUnits.at(i).Destroy();
    }

    for (int i = 0; i < playerTwoUnits.size(); i++) {
        playerTwoUnits.at(i).Destroy();
    }
}
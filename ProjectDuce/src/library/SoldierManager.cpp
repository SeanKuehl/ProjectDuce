#include "SoldierManager.h"
#include "Bullet.h"

SoldierManager::SoldierManager() {

}


void SoldierManager::CreateSoldier(int passedAllegiance, int x, int y) {
	if (passedAllegiance == PLAYER_ONE) {
		playerOneUnits.push_back(Soldier(passedAllegiance, x, y));
	}
	else {
		playerTwoUnits.push_back(Soldier(passedAllegiance, x, y));
	}
}

void SoldierManager::SetPlayerTurn(int passedTurn) {
    playerTurn = passedTurn;
}

void SoldierManager::HandleLeftClick(int x, int y) {

    if (playerTurn == PLAYER_ONE) {
        //check if player one units were clicked on
        for (int i = 0; i < playerOneUnits.size(); i++) {
            if (playerOneUnits.at(i).ClickedOn(x, y)) {
                playerOneUnits.at(i).ToggleSelected();
            }
            else {
                if (playerOneUnits.at(i).GetSelected() == true) {
                    //move to that position
                    playerOneUnits.at(i).Move(x, y);
                    playerOneUnits.at(i).ToggleSelected();  //deselect
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
                if (playerTwoUnits.at(i).GetSelected() == true) {
                    //move to that position
                    playerTwoUnits.at(i).Move(x, y);
                    playerTwoUnits.at(i).ToggleSelected();  //deselect
                }
            }
        }
    }
    


    
}


Bullet SoldierManager::HandleRightClick(int x, int y) {

    if (playerTurn == PLAYER_ONE) {
        for (int i = 0; i < playerOneUnits.size(); i++) {
            if (playerOneUnits.at(i).GetSelected() == true) {

                return Bullet("bullet.png", playerOneUnits.at(i).GetAllegiance(), playerOneUnits.at(i).GetCenterX(), playerOneUnits.at(i).GetCenterY(), x, y);
            }
        }
    }
    
    if (playerTurn == PLAYER_TWO) {
        for (int i = 0; i < playerTwoUnits.size(); i++) {
            if (playerTwoUnits.at(i).GetSelected() == true) {
                return Bullet("bullet.png", playerTwoUnits.at(i).GetAllegiance(), playerTwoUnits.at(i).GetCenterX(), playerTwoUnits.at(i).GetCenterY(), x, y);
            }
        }
    }
    

    return Bullet();


    
}



void SoldierManager::Render() {

    for (int i = 0; i < playerOneUnits.size(); i++) {
        playerOneUnits.at(i).Render();
    }

    for (int i = 0; i < playerTwoUnits.size(); i++) {
        playerTwoUnits.at(i).Render();
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
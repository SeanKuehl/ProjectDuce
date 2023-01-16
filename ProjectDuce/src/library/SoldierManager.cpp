#include "SoldierManager.h"
#include "Bullet.h"


/*! Given tileMeasures create a new soldier manager object
*   \params passedTileWidth the width of the game grid tiles
*   \params passedTileHieght the hieght of the game grid tiles
*   \params passedXOffset the x coord of the offset from the tile to draw soldiers/bullets
*   \params passedYOffset the y coord of the offset from the tile to draw soldiers/bullets
*/
SoldierManager::SoldierManager(int passedTileWidth, int passedTileHieght, int passedXOffset, int passedYOffset) {
    tileWidth = passedTileWidth;
    tileHieght = passedTileHieght;
    xOffset = passedXOffset;
    yOffset = passedYOffset;
}

/*! Given an allegiance and grid coordinates,
*   create a new soldier and add to manager list
*   for management.
*   \param passedAllegiance the player the soldier belongs to
*   \param coords the row and column of the grid where the soldier will be placed
*/
void SoldierManager::CreateSoldier(int passedAllegiance, std::vector<int> coords) {
	if (passedAllegiance == PLAYER_ONE) {
		playerOneUnits.push_back(Soldier(passedAllegiance, coords.at(0), coords.at(1)));
	}
	else {
		playerTwoUnits.push_back(Soldier(passedAllegiance, coords.at(0), coords.at(1)));
	}
}

/*! Set the internal playerTurn value
*   \param passedTurn the value to set the internal playerTurn to
*/
void SoldierManager::SetPlayerTurn(int passedTurn) {
    playerTurn = passedTurn;
}

/*! Handle a left click event by checking wheather any soldier's were clicked
*   on and weather or not any need to be moved, trigger a move event message
*   across the network. Return information needed for soldier move or {-1}
*   if no move event triggered.
*   \param x x coordinate of mouse left click
*   \param y y coordinate of mouse left click
*   \param moveCoords if the soldier does need to move, the coordinates to move to
*/
std::vector<int> SoldierManager::HandleLeftClick(int x, int y, std::vector<int> moveCoords) {
    std::vector<int> tileMeasures = { tileWidth, tileHieght, xOffset, yOffset };
    std::vector<int> moveInformation = { -1 };


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
                    moveInformation = { i, moveCoords.at(0), moveCoords.at(1) };
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
                    moveInformation = { i, moveCoords.at(0), moveCoords.at(1) };
                }
            }
        }
    }

    return moveInformation;


}

/*! Used by SoldierManager in NetworkManager, this function
*   takes a soldier at a certain index in the manager's lists and 
*   moves it to specified xy coordinates
*   \param index the index in the manager's list the soldier to move is
*   \param moveCoords the x and y coordinates of where to move the soldier to
*/
void SoldierManager::NetworkMove(int index, std::vector<int> moveCoords) {
    std::vector<int> tileMeasures = { tileWidth, tileHieght, xOffset, yOffset };

    if (playerTurn == PLAYER_ONE) {
        playerOneUnits.at(index).Move(moveCoords.at(0), moveCoords.at(1), tileMeasures);
    }
    else if (playerTurn == PLAYER_TWO) {
        playerTwoUnits.at(index).Move(moveCoords.at(0), moveCoords.at(1), tileMeasures);
    }

}

/*! Given destination coordinates and a current position,
*   determines wheather the bullet attempting to be shot 
*   will be within the 3 tile range limit. Return true if 
*   within range and false if not.
*   \param moveCoords destination to check if within range
*   \param x x coordinate of current shooting soldier position
*   \param y y coordinate of current shooting soldier position
*/
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

/*! Handle a mouse right click event. If a soldier
*   is selected when there is a right click, try to
*   fire a bullet if destination is within 3 tile range.
*   Return a valid Bullet object if there is a valid shot
*   and one with the isNull attribute set to true if not.
*   \params x the x coord of the mouse at right click
*   \params y the y coord of the mouse at right click
*   \params moveCoords potential destination of the bullet
*/
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

/*! Get if a soldier was hit. If not return {-2, -2},
*   else if a soldier is hit then return {-1, -1}.
*   If a soldier is killed return { allegiance, index }
*   \param allegiance the player owner of the soldier that first the shot, opposite of who'll it'll hit
*   \param tileCoords the coordinates of the tile that was hit by the bullet
*/
std::vector<int> SoldierManager::GetSoldierHit(int allegiance, std::vector<int> tileCoords) {
    //allegiance is of the person firing the shot, so only check the enemies of that allegiance for hits
    //tile coords is xPos, yPos, width, hieght of tile
    std::vector<int> toReturn = { -2, -2 }; //this is the no hit case
    if (allegiance == PLAYER_ONE) {
        //check player two troops
        
        for (int i = 0; i < playerTwoUnits.size(); i++) {
            
            int x = playerTwoUnits.at(i).GetTopLeftX();
            int y = playerTwoUnits.at(i).GetTopLeftY();

            if (x > tileCoords.at(0) && x < (tileCoords.at(0) + tileCoords.at(2))) {
                if (y > tileCoords.at(1) && y < (tileCoords.at(1) + tileCoords.at(3))) {
                    //this soldier was hit, decrease it's health and kill it if needed
                    bool dead = playerTwoUnits.at(i).TakeHit();
                    toReturn = { -1, -1 };  //this is the hit case
                    if (dead) {
                        //remove soldier from play and send event to other player to synchronize
                        //a "K", kill event needing allegiance of soldier to kill, i of their spot in soldier list
                        toReturn = { PLAYER_TWO, i };
                        Soldier temp = playerTwoUnits.at(i);
                        playerTwoUnits.erase(playerTwoUnits.begin() + i);
                        temp.Destroy();
                    }

                }
            }

        }


    }
    else if (allegiance == PLAYER_TWO) {
        //check player one troops
        
        for (int i = 0; i < playerOneUnits.size(); i++) {
            
            int x = playerOneUnits.at(i).GetTopLeftX();
            int y = playerOneUnits.at(i).GetTopLeftY();
           

            if (x > tileCoords.at(0) && x < (tileCoords.at(0) + tileCoords.at(2))) {
                if (y > tileCoords.at(1) && y < (tileCoords.at(1) + tileCoords.at(3))) {
                    
                    //this soldier was hit, decrease it's health and kill it if needed
                    bool dead = playerOneUnits.at(i).TakeHit();
                    
                    toReturn = { -1, -1 };  //this is the hit case
                    if (dead) {
                        //remove soldier from play and send event to other player to synchronize
                        //a "K", kill event needing allegiance of soldier to kill, i of their spot in soldier list
                        toReturn = { PLAYER_TWO, i };
                        Soldier temp = playerOneUnits.at(i);
                        playerOneUnits.erase(playerOneUnits.begin() + i);
                        temp.Destroy();
                        
                    }

                }
            }

        }
    }

    return toReturn;

}

/*! remove a soldier from the manager's lists and the game
*   \param allegiance allegiance of the soldier to erase
*   \param index the position in the manager list of the soldier to erase
*/
void SoldierManager::RemoveSoldier(int allegiance, int index) {
    printf("got here, %d, %d\n", playerOneUnits.size(), playerTwoUnits.size());
    if (allegiance == PLAYER_ONE) {
        
        Soldier temp = playerOneUnits.at(index);
        playerOneUnits.erase(playerOneUnits.begin() + index);
        temp.Destroy();
    }
    else if (allegiance == PLAYER_TWO) {
        Soldier temp = playerTwoUnits.at(index);
        playerTwoUnits.erase(playerTwoUnits.begin() + index);
        temp.Destroy();
    }

}


/*! Get the grid coordinates where we will create a new soldier.
*   This is used when a soldier is created at a base.
*   \param gridCoords the coordinates of the base creating the soldier
*   \param dimension the dimension of the game grid
*/
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

/*! Refresh the actionTaken attribute of all soldiers
*   in advance of next turn
*/
void SoldierManager::EndTurn() {
    for (int i = 0; i < playerOneUnits.size(); i++) {
        playerOneUnits.at(i).SetActionTaken(false);
    }

    for (int i = 0; i < playerTwoUnits.size(); i++) {
        playerTwoUnits.at(i).SetActionTaken(false);
    }
}

/*! Render all soldiers in manager list
*/
void SoldierManager::Render() {
    std::vector<int> tileMeasures = { tileWidth, tileHieght, xOffset, yOffset };
    

    for (int i = 0; i < playerOneUnits.size(); i++) {
        playerOneUnits.at(i).Render(tileMeasures);
    }

    for (int i = 0; i < playerTwoUnits.size(); i++) {
        playerTwoUnits.at(i).Render(tileMeasures);
    }

}

/*! Destroy all soldiers in manager list
*/
void SoldierManager::Destroy() {
    for (int i = 0; i < playerOneUnits.size(); i++) {
        playerOneUnits.at(i).Destroy();
    }

    for (int i = 0; i < playerTwoUnits.size(); i++) {
        playerTwoUnits.at(i).Destroy();
    }
}


#pragma once
#define PLAYER_ONE 1
#define PLAYER_TWO 2
#include <vector>
#include <string>
#include "Soldier.h"
#include "Bullet.h"

class SoldierManager
{
private:
	std::vector<Soldier> playerOneUnits;
	std::vector<Soldier> playerTwoUnits;
	int playerTurn;
	int tileWidth, tileHieght, xOffset, yOffset;



public: 
	SoldierManager(int passedTileWidth, int passedTileHieght, int passedXOffset, int passedYOffset);

	void CreateSoldier(int passedAllegiance, std::vector<int> coords);

	void SetPlayerTurn(int passedTurn);

	void HandleLeftClick(int x, int y, std::vector<int> moveCoords);

	Bullet HandleRightClick(int x, int y);

	void Render();

	void Destroy();

};


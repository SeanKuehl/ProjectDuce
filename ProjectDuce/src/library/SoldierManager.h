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

	std::vector<int> GetSoldierGridCoords(std::vector<int> gridCoords, int dimension);

	void SetPlayerTurn(int passedTurn);

	void RemoveSoldier(int allegiance, int index);

	std::vector<int> GetSoldierHit(int allegiance, std::vector<int> tileCoords);

	void NetworkMove(int index, std::vector<int> moveCoords);

	std::vector<int> HandleLeftClick(int x, int y, std::vector<int> moveCoords);

	Bullet HandleRightClick(int x, int y, std::vector<int> moveCoords);

	bool InRange(std::vector<int> moveCoords, int x, int y);

	void EndTurn();

	void Render();

	void Destroy();

};


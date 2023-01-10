#pragma once
#define PLAYER_ONE 1
#define PLAYER_TWO 2
#include "AllegroHelper.h"
#include "Building.h"
#include <string>
#include <vector>


class BuildingManager
{
private:
	std::string buildingImageDirectory = "assets/images/";
	std::string playerOneBaseImage = "redBase.png";
	std::string playerTwoBaseImage = "blueBase.png";
	std::vector<Building> buildingList;
	int playerTurn = PLAYER_ONE;
	


public:
	BuildingManager();

	void CreateBase(std::vector<int> coords, int passedAllegiance, int gridRow, int gridColumn);

	void SetPlayerTurn(int passedTurn);

	std::vector<int> HandleLeftClick(int x, int y);

	

	void Render();

	void Destroy();

};


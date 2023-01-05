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



public: 
	SoldierManager();

	void CreateSoldier(std::string imageName, int passedAllegiance, int x, int y);

	void HandleLeftClick(int x, int y);

	Bullet HandleRightClick(int x, int y);

	void Render();

	void Destroy();

};


#pragma once
#include "Entity.h"
#include <vector>

class Bullet : public Entity
{
private:
	int allegiance;	//the bullet will only hit/hurt enemies
	bool isNull = false;
	int partialDestX;
	int partialDestY;
	bool partialSet = false;
	

public:
	Bullet(std::string imageName, int passedAllegiance, int x, int y, int targetX, int targetY);

	Bullet();

	bool GetIsNull();

	bool InRange(int x, int y, std::vector<int> tileMeasures);

	void Render(std::vector<int> tileMeasures);

	void Move(int x, int y, std::vector<int> tileMeasures);

	bool ReachedDestination();


};


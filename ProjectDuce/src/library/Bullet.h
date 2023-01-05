#pragma once
#include "Entity.h"

class Bullet : public Entity
{
private:
	int allegiance;	//the bullet will only hit/hurt enemies
	bool isNull = false;

public:
	Bullet(std::string imageName, int passedAllegiance, int x, int y, int targetX, int targetY);

	Bullet();

	bool GetIsNull();

	

	bool ReachedDestination();


};


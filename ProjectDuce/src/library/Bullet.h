#pragma once
#include "Entity.h"

class Bullet : public Entity
{
private:
	int allegiance;	//the bullet will only hit/hurt enemies


public:
	Bullet(std::string imageName, int passedAllegiance, int x, int y) {
		image = CreateImage(imageDirectory + imageName);
		allegiance = passedAllegiance;
		xPosition = x;
		yPosition = y;
		hieght = al_get_bitmap_height(image);
		width = al_get_bitmap_width(image);
	}


};


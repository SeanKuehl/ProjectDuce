#include "Bullet.h"



Bullet::Bullet(std::string imageName, int passedAllegiance, int x, int y, int targetX, int targetY) {
	image = CreateImage(imageDirectory + imageName);
	allegiance = passedAllegiance;
	xPosition = x;
	yPosition = y;
	destX = targetX;
	destY = targetY;
	hieght = al_get_bitmap_height(image);
	width = al_get_bitmap_width(image);


}


Bullet::Bullet() {
	//this is the null constructor
	isNull = true;
}

bool Bullet::GetIsNull() {
	return isNull;
}


bool Bullet::ReachedDestination() {
	if (xPosition == destX && yPosition == destY) {
		return true;
	}
	else {
		return false;
	}
}
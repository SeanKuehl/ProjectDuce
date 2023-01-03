#include "Entity.h"


Entity::Entity() {

}

Entity::Entity(std::string imageName, int x, int y) {

	image = CreateImage(imageDirectory + imageName);	//image name includes file extension
	xPosition = x;
	yPosition = y;
	hieght = al_get_bitmap_height(image);
	width = al_get_bitmap_width(image);
}


void Entity::Move(int x, int y) {

	destX = x;
	destY = y;

	if (xPosition < x) {
		xPosition += speed;
		if (xPosition > x) {
			xPosition = x;
		}
	}
	else if (xPosition > x) {
		xPosition -= speed;
		if (xPosition < x) {
			xPosition = x;
		}
	}



	if (yPosition < y) {
		yPosition += speed;
		if (yPosition > y) {
			yPosition = y;
		}
	}
	else if (yPosition > y) {
		yPosition -= speed;
		if (yPosition < y) {
			yPosition = y;
		}
	}
}


void Entity::Render() {
	
	Move(destX, destY);

	al_draw_bitmap(image, xPosition, yPosition, 0);
	
}

void Entity::Destroy() {
	al_destroy_bitmap(image);
}
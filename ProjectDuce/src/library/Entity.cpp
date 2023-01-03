#include "Entity.h"



Entity::Entity(std::string imageName) {

	image = CreateImage(imageDirectory + imageName);	//image name includes file extension
}

void Entity::Render(int x, int y) {
	al_draw_bitmap(image, x, y, 0);
	xPosition = x;
	yPosition = y;
}

void Entity::Destroy() {
	al_destroy_bitmap(image);
}
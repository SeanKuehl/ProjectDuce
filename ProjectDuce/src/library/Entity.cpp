#include "Entity.h"

/*! Create empty Entity object
*/
Entity::Entity() {

}

/*! Given an image and xy coords, create an entity object
*   \param imageName the path to the entity's image
*   \param x the x coord of where to place entity
*   \param y the y coord of where to place entity
*/
Entity::Entity(std::string imageName, int x, int y) {

	image = CreateImage(imageDirectory + imageName);	//image name includes file extension
	xPosition = x;
	yPosition = y;
	hieght = al_get_bitmap_height(image);
	width = al_get_bitmap_width(image);
}

/*! Given the xy coords of a position, 
*   move towards that position.
*   \param x the x coord of destination position
*   \param y the y coord of destination position
*/
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

/*! Move the entity and then render this object
*   at the position.
*/
void Entity::Render() {
	
	Move(destX, destY);

	al_draw_bitmap(image, xPosition, yPosition, 0);
	
}

/*! destroy this object's image
*/
void Entity::Destroy() {
	al_destroy_bitmap(image);
}
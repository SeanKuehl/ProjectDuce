#include "Bullet.h"


/*! Create a new bullet object given an image, allegiance, xy and target coords.
*   \param imageName this is the path the bullet's image
*   \param passedAllegiance this is the allegiance of the bullet
*   \param x this is the x coord of the bullet
*   \param y this is the y coord of the bullet
*   \param targetX x coord of the tile where the bullet is moving towards
*   \param targetY y coord of the tile where the bullet is moving towards
*/
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

/*! Create a null bullet for the special case where a
*   bullet object must be created but is only a placeholder
*/
Bullet::Bullet() {
	//this is the null constructor
	isNull = true;
}

/*! Given the dimensions of the tiles of the grid,
*   move the bullet towards it's destination and 
*   render it.
*   \param tileMeasures a vector<int> like { tileWidth, tileHieght, xOffset, yOffset }
*/
void Bullet::Render(std::vector<int> tileMeasures) {
	Move(destX, destY, tileMeasures);

	al_draw_bitmap(image, xPosition, yPosition, 0);

}

/*! return a vector<int> containing the x and y
*   coordinates of the top left of the image
*/
std::vector<int> Bullet::GetXAndYPosition() {
	std::vector<int> coords = { xPosition, yPosition };
	return coords;
}

/*! Given x, y and tileMeasures, determine
*   wheather or not an attempted shoot from a soldier
*   is within the 3 tile range. If it is, return true
*   and if not return false.
*   \param x the x coordinate of the tile the bullet is being shot at
*   \param y the y coordinate of the tile the bullet is being shot at
*   \param tileMeasures a vector<int> like { tileWidth, tileHieght, xOffset, yOffset }
*/
bool Bullet::InRange(int x, int y, std::vector<int> tileMeasures) {
	//do the range check
	int tileXSize = tileMeasures.at(0) + tileMeasures.at(2);
	int tileYSize = tileMeasures.at(1) + tileMeasures.at(3);
	int range = 3;
	int xDist = abs(xPosition - x);
	int yDist = abs(yPosition - y);
	if ((xDist - xDist / (range * tileXSize)) > 0) {
		//out of range, cancel it
		destX = xPosition;
		destY = yPosition;
		return false;
	}

	if ((yDist - yDist / (range * tileYSize)) > 0) {
		//out of range, cancel it
		destX = xPosition;
		destY = yPosition;
		return false;
	}

	return true;
}


/*! Given the x and y of a location to move toward and the measures
*   of the tile grid, move toward that destination until it's reached.
*   \param x the x of the tile to move toward
*   \param y the y of the tile to move toward
*   \param tileMeasures a vector<int> like { tileWidth, tileHieght, xOffset, yOffset }
*/
void Bullet::Move(int x, int y, std::vector<int> tileMeasures) {
	//tileMeasures: tileWidth, tileHieght, xOffset, yOffset
	destX = x;
	destY = y;

	
		if ((partialDestX != destX || partialDestY != destY) && partialSet == false) {
			//calculate new partialdest and move soldier towards it
			if (partialDestX > destX) {
				partialDestX = xPosition - tileMeasures.at(0) - tileMeasures.at(2);
				partialDestY = yPosition;
			}
			else if (partialDestX < destX) {
				partialDestX = xPosition + tileMeasures.at(0) + tileMeasures.at(2);
				partialDestY = yPosition;
			}

			if (partialDestY < destY) {
				partialDestX = xPosition;
				partialDestY = yPosition + tileMeasures.at(1) + tileMeasures.at(3);
			}
			else if (partialDestY > destY) {
				partialDestX = xPosition;
				partialDestY = yPosition - tileMeasures.at(1) - tileMeasures.at(3);
			}

			partialSet = true;
		}

		if (xPosition > partialDestX) {
			xPosition -= speed;
			if (xPosition < partialDestX) {
				xPosition = partialDestX;
			}
		}
		else if (xPosition < partialDestX) {
			xPosition += speed;
			if (xPosition > partialDestX) {
				xPosition = partialDestX;
			}
		}

		if (yPosition > partialDestY) {
			yPosition -= speed;
			if (yPosition < partialDestY) {
				yPosition = partialDestY;
			}
		}
		else if (yPosition < partialDestY) {
			yPosition += speed;
			if (yPosition > partialDestY) {
				yPosition = partialDestY;
			}
		}

		if (xPosition == partialDestX && yPosition == partialDestY) {
			partialSet = false;
		}
	
	



	
}

/*! Return the bullet object's isNull property
*/
bool Bullet::GetIsNull() {
	return isNull;
}

/*! Check wheather or not the bullet has reached the target/destination
*   set when it was created. Return true if so or false if not.
*/
bool Bullet::ReachedDestination() {
	
	if (xPosition == destX && yPosition == destY) {
		return true;
	}
	else {
		return false;
	}
	
	
}
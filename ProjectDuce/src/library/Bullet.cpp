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

void Bullet::Render(std::vector<int> tileMeasures) {
	Move(destX, destY, tileMeasures);

	al_draw_bitmap(image, xPosition, yPosition, 0);

}

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
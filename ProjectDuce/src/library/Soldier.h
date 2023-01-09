#pragma once
#define PLAYER_ONE 1
#define PLAYER_TWO 2
#include "AllegroHelper.h"
#include "Entity.h"
#include <string>
#include <vector>
#include <stdio.h>

class Soldier : public Entity
{

private:
	int allegiance;	//which player this unit belongs to
	bool selected = false;	//whether user clicked on this unit or not
	std::string redSoldierImage = "soldier.png";
	std::string blueSoldierImage = "EnemySoldier.png";
	int partialDestX;
	int partialDestY;
	bool partialSet = false;
	bool actionTaken = false;


public:
	Soldier(int passedAllegiance, int x, int y) {
		if (passedAllegiance == PLAYER_ONE) {
			image = CreateImage(imageDirectory + redSoldierImage);
		}
		else if (passedAllegiance == PLAYER_TWO) {
			image = CreateImage(imageDirectory + blueSoldierImage);
		}
		
		allegiance = passedAllegiance;
		xPosition = x;
		yPosition = y;
		destX = x;
		destY = y;
		partialDestX = x;
		partialDestY = y;
		hieght = al_get_bitmap_height(image);
		width = al_get_bitmap_width(image);
	}

	void ToggleSelected() {
		selected = !selected;
	}

	bool GetSelected() {
		return selected;
	}

	bool ClickedOn(int mouseX, int mouseY) {
		//if mouseX > xPosition(leftmost point) and mouseX < (xPosition + width)(rightmost point)
		//and if mouseY > yPosition(topmost point) and mouseY < (yPosition + hieght)(bottommost point)
		//then we've been clicked on

		bool clickedOn = false;

		//printf("%d, %d\n", mouseX, mouseY);
		//printf("%d, %d, %d, %d\n", xPosition, yPosition, width, hieght);

		if (mouseX > xPosition && mouseX < (xPosition + width)) {
			if (mouseY > yPosition && mouseY < (yPosition + hieght)) {
				clickedOn = true;
				
			}
		}

		return clickedOn;

	}


	void Move(int x, int y, std::vector<int> tileMeasures) {
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


	void Render(std::vector<int> tileMeasures) {

		Move(destX, destY, tileMeasures);

		al_draw_bitmap(image, xPosition, yPosition, 0);

	}

	void SetActionTaken(bool passedTaken) {
		actionTaken = passedTaken;
	}

	bool GetActionTaken() {
		return actionTaken;
	}

	int GetAllegiance() {
		return allegiance;
	}

	int GetCenterX() {
		return (xPosition + (width / 2));
	}

	int GetCenterY() {
		return (yPosition + (hieght / 2));
	}

	int GetTopLeftX() {
		return xPosition;
	}

	int GetTopLeftY() {
		return yPosition;
	}

};


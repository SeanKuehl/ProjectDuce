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
	int health = 3;


public:
	/*! Given an allegiance and xy coords, create
	*   a new soldier.
	*   \param passedAllegiance the player the new soldier will belong to
	*   \param x the x coordinates the soldier will be placed at
	*   \param y the y coordinates the soldier will be placed at
	*/
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

	/*! inverse the internal selected variable.
	*   If it's true, set to false. If set to false,
	*   set to true.
	*/
	void ToggleSelected() {
		selected = !selected;
	}

	/*! return the internal selected(boolean) variable
	*/
	bool GetSelected() {
		return selected;
	}

	/*! Reduce the soldier's health by 1,
	*   if this reduces health to 0 then return true
	*   that the soldier died or false that
	*   they did not.
	*/
	bool TakeHit() {
		health -= 1;
		if (health == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	/*! Given coordinates of mouse click, determine
	*   wheather or not this soldier was clicked on.
	*   Returning false if not clicked on and true 
	*   if clicked on.
	*   \param mouseX the x coordinates of the mouse click
	*   \param mouseY the y coordinates of the mouse click
	*/
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

	/*! Given the xy coords of a destination and the tile measurements,
	*   move the soldier towards the destination.
	*   \param x the x coordinate to move towards
	*   \param y the y coordinate to move towards
	*   \param tileMeasures a vector<int> with {tileWidth, tileHieght, xOffset, yOffset}
	*/
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

	/*! Move towards destination if not there and render
	*   at position.
	*   \param tileMeasures a vector<int> with {tileWidth, tileHieght, xOffset, yOffset}
	*/
	void Render(std::vector<int> tileMeasures) {

		Move(destX, destY, tileMeasures);

		al_draw_bitmap(image, xPosition, yPosition, 0);

	}

	/*! Set the internal actionTaken boolean variable
	*   \param passedTaken the new boolean value to set actionTaken to
	*/
	void SetActionTaken(bool passedTaken) {
		actionTaken = passedTaken;
	}

	/*! return the internal boolean value actionTaken
	*/
	bool GetActionTaken() {
		return actionTaken;
	}

	/*! return the internal integer allegiance value
	*/
	int GetAllegiance() {
		return allegiance;
	}

	/*! return the integer x coordinate that maps
	*   to the very center of the soldier's image
	*/
	int GetCenterX() {
		return (xPosition + (width / 2));
	}

	/*! return the integer y coordinate that maps
	*   to the very center of the soldier's image
	*/
	int GetCenterY() {
		return (yPosition + (hieght / 2));
	}

	/*! return the x value of the leftmost part of the
	*   soldier's image(topleft coord)
	*/
	int GetTopLeftX() {
		return xPosition;
	}

	/*! return the y value of the topmost part of the
	*   soldier's image(topleft coord)
	*/
	int GetTopLeftY() {
		return yPosition;
	}

};


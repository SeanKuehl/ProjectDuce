#pragma once
#include "AllegroHelper.h"
#include "Entity.h"
#include <string>
#include <stdio.h>

class Soldier : public Entity
{

private:
	int allegiance;	//which player this unit belongs to
	bool selected = false;	//whether user clicked on this unit or not


public:
	Soldier(std::string imageName, int passedAllegiance, int x, int y) {
		image = CreateImage(imageDirectory + imageName);
		allegiance = passedAllegiance;
		xPosition = x;
		yPosition = y;
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

	int GetAllegiance() {
		return allegiance;
	}

	int GetCenterX() {
		return (xPosition + (width / 2));
	}

	int GetCenterY() {
		return (yPosition + (hieght / 2));
	}


};


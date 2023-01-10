#include "Building.h"


Building::Building(std::string imageName, std::vector<int> coords, int passedAllegiance, int passedGridRow, int passedGridColumn) {
	image = CreateImage(imageName);	//image name includes file extension
	
	topLeftX = coords.at(0);
	topLeftY = coords.at(1);

	gridX = passedGridRow;
	gridY = passedGridColumn;
	printf("%d, %d\n", gridX, gridY);
	
	hieght = al_get_bitmap_height(image);
	width = al_get_bitmap_width(image);

	allegiance = passedAllegiance;
}

std::vector<int> Building::GetGridCoords() {
	std::vector<int> myCoords = { gridX, gridY };
	return myCoords;
}

bool Building::ClickedOn(int mouseX, int mouseY) {
	//if mouseX > xPosition(leftmost point) and mouseX < (xPosition + width)(rightmost point)
	//and if mouseY > yPosition(topmost point) and mouseY < (yPosition + hieght)(bottommost point)
	//then we've been clicked on

	bool clickedOn = false;

	//printf("%d, %d\n", mouseX, mouseY);
	//printf("%d, %d, %d, %d\n", xPosition, yPosition, width, hieght);

	if (mouseX > topLeftX && mouseX < (topLeftX + width)) {
		if (mouseY > topLeftY && mouseY < (topLeftY + hieght)) {
			clickedOn = true;

		}
	}

	return clickedOn;

}

int Building::GetAllegiance() {
	return allegiance;
}

void Building::Render() {

	

	al_draw_bitmap(image, topLeftX, topLeftY, 0);

}

void Building::Destroy() {
	al_destroy_bitmap(image);
}
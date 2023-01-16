#include "Building.h"

/*! Create a building object with image, girc and xy coords
*   and allegiance.
*   \param imageName this is the path to the image to load for the building
*   \param coords these are the top y coord and leftmost x coord of building
*   \param passedAllegiance the side(player 1 or 2) that the building belongs to
*   \param passedGridRow the row of the game grid the building belongs to(if grid 10*10, row is 1-10)
*   \param passedGridColumn the column of the game grid the building belongs to(if grid 10*10, row is 1-10)
*/
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

/*! Handle the building being hit by an enemy bullet
*   and taking damage. Return false if building health still
*   above 0 after hit or true if it is now 0 and the building is destroyed.
*/
bool Building::TakeHit() {
	health -= 1;
	printf("%d\n", health);
	if (health == 0) {
		return true;
	}
	else {
		return false;
	}
}

/*! Return a vector<int> with the buildings grid row, and grid column
*/
std::vector<int> Building::GetGridCoords() {
	std::vector<int> myCoords = { gridX, gridY };
	return myCoords;
}

/*! Given the x and y coordinates of where the mouse clicked,
*   determine wheather or not this building was clicked on. 
*   Return false if not clicked on and true if clicked on.
*   \param mouseX the x coordinate of where the mouse clicked
*   \param mouseY the y coordinate of where the mouse clicked
*/
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

/*! return the int(1 or 2) allegiance value of the building
*/
int Building::GetAllegiance() {
	return allegiance;
}

/*! Render the building's bitmap image at the current x and y coords
*/
void Building::Render() {

	

	al_draw_bitmap(image, topLeftX, topLeftY, 0);

}

/*! Free the resources of the building's image object
*/
void Building::Destroy() {
	al_destroy_bitmap(image);
}
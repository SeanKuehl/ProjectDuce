#include "Building.h"


Building::Building(std::string imageName, std::vector<int> coords) {
	image = CreateImage(imageName);	//image name includes file extension
	
	topLeftX = coords.at(0);
	topLeftY = coords.at(1);
	
	hieght = al_get_bitmap_height(image);
	width = al_get_bitmap_width(image);
}



void Building::Render() {

	

	al_draw_bitmap(image, topLeftX, topLeftY, 0);

}

void Building::Destroy() {
	al_destroy_bitmap(image);
}
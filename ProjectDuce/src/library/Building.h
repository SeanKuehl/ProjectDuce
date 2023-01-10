#pragma once
#include "AllegroHelper.h"
#include <string>
#include <vector>

class Building
{
private:
	
	int topLeftX;
	int topLeftY;
	int width;
	int hieght;
	int allegiance;
	ALLEGRO_BITMAP* image;


public:
	Building(std::string imageName, std::vector<int> coords);

	void Render();

	void Destroy();

};


#pragma once
#include "AllegroHelper.h"
#include <string>


class Entity
{
	
private:
	std::string imageDirectory = "assets/images/";	//from ProjectDuce project folder
	ALLEGRO_BITMAP* image;
	int xPosition;
	int yPosition;


public:
	Entity(std::string imageName);

	void Render(int x, int y);

	void Destroy();


};


#pragma once
#include "AllegroHelper.h"
#include <string>


class Entity
{
	

protected:	//protected so children can access them
	std::string imageDirectory = "assets/images/";	//from ProjectDuce project folder
	ALLEGRO_BITMAP* image;
	int xPosition;	//pos is top left of image
	int yPosition;
	int width;
	int hieght;
	int destX;	//destination x
	int destY;
	int speed = 5;

public:
	Entity();

	Entity(std::string imageName, int x, int y);

	void Move(int x, int y);

	void Render();

	void Destroy();


};


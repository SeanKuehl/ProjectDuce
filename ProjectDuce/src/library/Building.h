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
	int gridX;
	int gridY;
	ALLEGRO_BITMAP* image;


public:
	Building(std::string imageName, std::vector<int> coords, int passedAllegiance, int gridRow, int gridColumn);

	bool ClickedOn(int mouseX, int mouseY);

	int GetAllegiance();

	std::vector<int> GetGridCoords();

	void Render();

	void Destroy();

};


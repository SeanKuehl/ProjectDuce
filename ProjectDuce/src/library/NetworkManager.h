#pragma once
#include "SoldierManager.h"
#include "GridManager.h"
#include "BuildingManager.h"
#include <string>
#include <vector>
#include <stdio.h>

class NetworkManager
{

public:
	NetworkManager() {

	}

	std::vector<int> InterperetNetworkMessage(std::string message, SoldierManager& man, GridManager& gman, BuildingManager& bman) {
		
		std::vector<std::string> messageTokens;
		std::string thisToken = "";

		for (int i = 0; i < message.size(); i++) {
			if (message.at(i) == 'X') {
				messageTokens.push_back(thisToken);
				thisToken = "";
			}
			else {
				thisToken += message.at(i);
			}
		}


		if (messageTokens.at(0) == "C") {
			//create soldier
			int allegiance = std::stoi(messageTokens.at(1));
			std::vector<int> coords = { std::stoi(messageTokens.at(2)), std::stoi(messageTokens.at(3)) };
			man.CreateSoldier(allegiance, gman.GetSoldierCoords(coords.at(0), coords.at(1)));

		}
		else if (messageTokens.at(0) == "M") {
			//move a soldier
			int index = std::stoi(messageTokens.at(1));
			std::vector<int> coords = { std::stoi(messageTokens.at(2)), std::stoi(messageTokens.at(3)) };
			man.NetworkMove(index, coords);
		}
		else if (messageTokens.at(0) == "H") {
			//someone fired a bullet that hit a square
			//check if it hit a soldier or a base
			int allegiance = std::stoi(messageTokens.at(1));
			std::vector<int> coords = { std::stoi(messageTokens.at(2)), std::stoi(messageTokens.at(3)) };
			printf("right before grid\n");
			std::vector<int> xyCoords = gman.GetTileCoordsFromGridCoords(coords.at(0), coords.at(1));
			printf("right before soldier hit\n");
			std::vector<int> hitEvent = man.GetSoldierHit(allegiance, xyCoords);
			printf("worked to here\n");
			

			if (hitEvent.at(0) == -2) {
				printf("worked in here\n");
				//no hit, check buildings
				coords = { std::stoi(messageTokens.at(2)), std::stoi(messageTokens.at(3)) };
				bool gameOver = bman.GetBuildingHit(allegiance, coords.at(0), coords.at(1));
				
				if (gameOver) {
					return { -1 };
				}

			}
			else if (hitEvent.at(0) == -1){
				printf("worked in -1\n");
				//a soldier was hit, no need to check buildings
			}
			else {
				printf("worked in here with -2\n");
				//a soldier was killed, send the kill event across the network
				return hitEvent;
			}

			
		}
		else if (messageTokens.at(0) == "K") {
			int allegiance = std::stoi(messageTokens.at(1));
			int index = std::stoi(messageTokens.at(2));
			printf("got all the way to remove\n");
			man.RemoveSoldier(allegiance, index);
		}
		return { -3 };
	}
	

};


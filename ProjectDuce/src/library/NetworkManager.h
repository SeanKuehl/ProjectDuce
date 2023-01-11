#pragma once
#include "SoldierManager.h"
#include "GridManager.h"
#include <string>
#include <vector>
#include <stdio.h>

class NetworkManager
{

public:
	NetworkManager() {

	}

	void InterperetNetworkMessage(std::string message, SoldierManager& man, GridManager& gman) {
		printf("got here\n");
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

	}
	

};


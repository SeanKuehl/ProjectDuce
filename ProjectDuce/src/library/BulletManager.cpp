#include "BulletManager.h"



BulletManager::BulletManager(int passedTileWidth, int passedTileHieght, int passedXOffset, int passedYOffset) {
	tileWidth = passedTileWidth;
	tileHieght = passedTileHieght;
	xOffset = passedXOffset;
	yOffset = passedYOffset;
}

void BulletManager::CreateBullet(std::string imageName, int passedAllegiance, int x, int y, int targetX, int targetY) {
	activeBulletList.push_back(Bullet(imageName, passedAllegiance, x, y, targetX, targetY));
}

void BulletManager::AddBullet(Bullet b) {
	activeBulletList.push_back(b);
}

std::vector<int> BulletManager::Render() {
	std::vector<int> toPass = { tileWidth, tileHieght, xOffset, yOffset };
	std::vector<int> toReturn = { -1, -1 };

	for (int i = 0; i < activeBulletList.size(); i++) {
		activeBulletList.at(i).Render(toPass);
		if (activeBulletList.at(i).ReachedDestination() == true) {
			//it hit a square, get it's x and y so we can figure out where
			toReturn = activeBulletList.at(i).GetXAndYPosition();
			Bullet temp = activeBulletList.at(i);	
			activeBulletList.erase(activeBulletList.begin() + i);
			temp.Destroy();
		}
	}
	return toReturn;
}

void BulletManager::Destroy() {
	for (int i = 0; i < activeBulletList.size(); i++) {
		activeBulletList.at(i).Destroy();
	}
}
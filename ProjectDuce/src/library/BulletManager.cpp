#include "BulletManager.h"



BulletManager::BulletManager() {

}

void BulletManager::CreateBullet(std::string imageName, int passedAllegiance, int x, int y, int targetX, int targetY) {
	activeBulletList.push_back(Bullet(imageName, passedAllegiance, x, y, targetX, targetY));
}

void BulletManager::AddBullet(Bullet b) {
	activeBulletList.push_back(b);
}

void BulletManager::Render() {
	for (int i = 0; i < activeBulletList.size(); i++) {
		activeBulletList.at(i).Render();
		if (activeBulletList.at(i).ReachedDestination() == true) {
			Bullet temp = activeBulletList.at(i);	
			activeBulletList.erase(activeBulletList.begin() + i);
			temp.Destroy();
		}
	}
}

void BulletManager::Destroy() {
	for (int i = 0; i < activeBulletList.size(); i++) {
		activeBulletList.at(i).Destroy();
	}
}
#pragma once
#include "Bullet.h"
#include <vector>
#include <string>

class BulletManager
{

private:
	std::vector<Bullet> activeBulletList;

public:
	BulletManager();

	void CreateBullet(std::string imageName, int passedAllegiance, int x, int y, int targetX, int targetY);

	void AddBullet(Bullet b);

	void Render();

	void Destroy();

};


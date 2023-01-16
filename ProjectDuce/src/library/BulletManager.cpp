#include "BulletManager.h"


/*! Create a bullet manager object given
*   tile width, tile hieght, x offset and y offset.
*   \param passedTileWidth the width of the grid tiles
*   \param passedTileHieght the hieght of the grid tiles
*   \param passedXOffset the x offset from tile coords for drawing soldiers or bullets at
*   \param passedYOffset the y offset from the tile coords for drawing soldiers or bullets at
*/
BulletManager::BulletManager(int passedTileWidth, int passedTileHieght, int passedXOffset, int passedYOffset) {
	tileWidth = passedTileWidth;
	tileHieght = passedTileHieght;
	xOffset = passedXOffset;
	yOffset = passedYOffset;
}

/*! Given an image, allegiance, xy coords and target/destination coords
*   add a new bullet object to the Bullet Manager object's activeBulletList
*   for management
*   \param imageName the path to the bullet image
*   \param passedAllegiance the allegiance to assign to the bullet
*   \param x the x coord to create the bullet at
*   \param y the y coord to create the bullet at
*   \param targetX the x coord to shoot the bullet at
*   \param targetY the y coord to shoot the bullet at
*/
void BulletManager::CreateBullet(std::string imageName, int passedAllegiance, int x, int y, int targetX, int targetY) {
	activeBulletList.push_back(Bullet(imageName, passedAllegiance, x, y, targetX, targetY));
}

/*! Given a bullet object, add it to the manager's
*   active bullet list
*   \param b the bullet to add to the list
*/
void BulletManager::AddBullet(Bullet b) {
	activeBulletList.push_back(b);
}

/*! Render all bullets in list, check if any have reached
*   their destinations and if so, destroy that bullet and 
*   return a vector<int> of the bullet's x and y pos for a hit event
*   otherwise return a vector<int> of {-1, -1} to indicate no hit event
*/
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

/*! Destroy every bullet in the manager's list
*/
void BulletManager::Destroy() {
	for (int i = 0; i < activeBulletList.size(); i++) {
		activeBulletList.at(i).Destroy();
	}
}
#include <stdlib.h>
#include "Collidable.h"

void Collidable::applyCollision(std::shared_ptr<Collidable> collideObj) {
	if (!this->collisionBox->detectCollision(collideObj->getCollisionBox())) return;

	std::shared_ptr<CollisionInfo> collisionInfo = std::make_shared<CollisionInfo>();

	collisionInfo->collideObjVelocityVector = collideObj->getVelocityVector();
	collisionInfo->collideObjCategory = collideObj->getCategory();

	collisionInfo->collisionType = CollisionManager::GetInstance()->getCollisionInteractive(this->getCategory(), collideObj->getCategory());
	
	float x_dir, y_dir, deltaX, deltaY;
	x_dir = ((this->x_location - collideObj->getLocationX()) > 0 ? -1 : 1);
	y_dir = ((this->y_location - collideObj->getLocationY()) > 0 ? -1 : 1);
	deltaX = this->x_location + x_dir * this->collisionBox->getWidth()/2 - (collideObj->getLocationX() - x_dir * collideObj->getCollisionBox()->getWidth()/2);
	deltaY = this->y_location + y_dir * this->collisionBox->getHeight()/2 - (collideObj->getLocationY() - y_dir * collideObj->getCollisionBox()->getHeight()/2);

	collisionInfo->collideDirection = (
			std::abs(deltaX) > std::abs(deltaY) ?
				(deltaY < 0 ? CollideDirection::TOP : (deltaY > 0 ? CollideDirection::BOTTOM : y_dir > 0 ? CollideDirection::BOTTOM : CollideDirection::TOP)) :		// 2 dong nay: Do khi va cham, tai frame sau thi this da bi block
				(deltaX < 0 ? CollideDirection::LEFT : (deltaX > 0 ? CollideDirection::RIGHT : x_dir > 0 ? CollideDirection::RIGHT : CollideDirection:: LEFT))		// Va do do', deltaX hoac deltaY = 0 -> thuat toan detect sai huong.
		);

	switch (collisionInfo->collideDirection) {
		case CollideDirection::TOP:
		case CollideDirection::BOTTOM:
			collisionInfo->blockCoordinate = collideObj->getLocationY() - y_dir * collideObj->getCollisionBox()->getHeight() / 2;
			break;
		case CollideDirection::LEFT:
		case CollideDirection::RIGHT:
			collisionInfo->blockCoordinate = collideObj->getLocationX() - x_dir * collideObj->getCollisionBox()->getWidth() / 2;
			break;
		default:
			break;
	}

	this->list_CollisionInfo.push_back(collisionInfo);
}

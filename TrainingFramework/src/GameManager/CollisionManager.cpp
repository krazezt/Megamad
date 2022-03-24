#include "CollisionManager.h"

CollisionManager::CollisionManager() {}
CollisionManager::~CollisionManager() {}

void CollisionManager::init() {
	// Init all collision interactives here
	
	addCollisionInteractive(Category::PLAYER, Category::TERRAIN, Collision::BLOCK);
};

Collision CollisionManager::getCollisionInteractive(Category category1, Category category2) {
	for (auto ci : list_collisionInteractive) {
		if (ci->checkCategory(category1, category2)) {
			return ci->getCollisionType();
		}
	}
};

void CollisionManager::addCollisionInteractive(Category category1, Category category2, Collision interactive) {
	std::shared_ptr<CollisionInteractive> tmp_interactive;
	tmp_interactive->init(category1, category2, interactive);

	list_collisionInteractive.push_back(tmp_interactive);
};
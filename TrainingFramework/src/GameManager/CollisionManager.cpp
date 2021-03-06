#include "CollisionManager.h"

CollisionManager::CollisionManager() {}
CollisionManager::~CollisionManager() {}

void CollisionManager::init() {
	// Init all collision interactives
	
	addCollisionInteractive(Category::PLAYER, Category::TERRAIN, Collision::BLOCK);
	addCollisionInteractive(Category::PLAYER, Category::TRIGGERER, Collision::BLOCK);
	addCollisionInteractive(Category::PLAYER, Category::ENEMY_BULLET, Collision::OVERLAP);
	addCollisionInteractive(Category::PLAYER, Category::ENEMY, Collision::OVERLAP);
	
	addCollisionInteractive(Category::TRIGGER_BLOCK, Category::PLAYER, Collision::OVERLAP);
	addCollisionInteractive(Category::TRIGGER_BLOCK, Category::TERRAIN, Collision::OVERLAP);
	addCollisionInteractive(Category::TRIGGER_BLOCK, Category::TRIGGERER, Collision::OVERLAP);

	addCollisionInteractive(Category::NUMBER_BLOCK, Category::PLAYER, Collision::OVERLAP);
};

Collision CollisionManager::getCollisionInteractive(Category category1, Category category2) {
	for (auto ci : list_collisionInteractive) {
		if (ci->checkCategory(category1, category2)) {
			return ci->getCollisionType();
		}
	}

	return Collision::IGNORED;
};

void CollisionManager::addCollisionInteractive(Category category1, Category category2, Collision interactive) {
	std::shared_ptr<CollisionInteractive> tmp_interactive = std::make_shared<CollisionInteractive>();
	tmp_interactive->init(category1, category2, interactive);

	list_collisionInteractive.push_back(tmp_interactive);
};
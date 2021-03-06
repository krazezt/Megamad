#include "Enemy1.h"
#include "EnemyBullet1.h"
#include "GameStates/GSPlaySurvive.h"

Enemy1::Enemy1() {
	this->category = Category::ENEMY;
}

Enemy1::~Enemy1() {}

void Enemy1::init(float x_location, float y_location) {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Enemy1.tga");

	width = Globals::screenWidth / 12.8f;
	height = Globals::screenWidth / 12.8f;
	movingRight = true;
	bulletLoading = true;
	m_totalTime = 0.0f;

	animation = std::make_shared<SpriteAnimation>(model, shader, texture, 15, 1, 0, 0.1f);
	animation->SetSize(width, height);

	this->initCollisionBox(this->x_location, this->y_location, width, height);
	this->velocityVector = Vector2(Globals::screenWidth / 12, 0.0f);
	this->blockState.reset();

	this->setLocation(x_location, y_location);
}

void Enemy1::initCollisionBox(float x_location, float y_location, float width, float height) {
	collisionBox = std::make_shared<CollisionBox2D>();
	collisionBox->init(this->x_location, this->y_location, width, height);
}

void Enemy1::update(float deltaTime) {
	if (x_location - width <= 0 || x_location + width >= Globals::screenWidth) {
		movingRight = !movingRight;
		this->animation->SetRotation(Vector3(0.0f, PI * (movingRight ? 0 : 1), 0.0f));
	}
	m_totalTime += deltaTime;
	if (
			((((int)(m_totalTime / 0.1f)) % 15) >= 10) &&
			(bulletLoading == false)
		) {
		bulletLoading = true;
		std::shared_ptr<EnemyBullet1> newBullet = std::make_shared<EnemyBullet1>();
		newBullet->init(this->x_location, this->y_location + 80);
		GSPlaySurvive::addSpawnedActor(newBullet);
	}
	else if (
			((((int)(m_totalTime / 0.1f)) % 15) < 10) &&
			(bulletLoading == true)
		) {
		bulletLoading = false;
	}

	this->setLocation(x_location + this->velocityVector.x * deltaTime * (movingRight ? 1 : -1), y_location);

	this->animation->Update(deltaTime);
	this->collisionBox->update(deltaTime);
}

void Enemy1::draw() {
	this->animation->Draw();
	this->collisionBox->draw();
}
#include "HostileEntity.h"

HostileEntity::HostileEntity(Map* map, std::vector<Entity*>* entities, Player* player) : MobileEntity(map, entities) {
	speed = 0.5f;
	this->player = player;

	//set sprite for rendering
	spriteSheet.loadFromFile("res/enemy.png");
	sprite.setTexture(spriteSheet);

	//construct animations
	animation = new Animation[4];
	animationCount = 4;
	for (int i = 0; i < animationCount; i++) {
		animation[i].length = 4;
		animation[i].frames.push_back(sf::IntRect(0,  (32 * i) + 64, 32, 32));
		animation[i].frames.push_back(sf::IntRect(32, (32 * i) + 64, 32, 32));
		animation[i].frames.push_back(sf::IntRect(0,  (32 * i) + 64, 32, 32));
		animation[i].frames.push_back(sf::IntRect(64, (32 * i) + 64, 32, 32));
	}

	currentAnimation = animation;
	sprite.setTextureRect(currentAnimation->frames.at(0));

	//set entity's starting location
	x = 500.0f;
	y = 500.0f;

	//set collision bounds of the entity
	collisionBounds.left = 4;
	collisionBounds.top = 8;
	collisionBounds.width = 24;
	collisionBounds.height = 24;
}

HostileEntity::~HostileEntity() {

}

void HostileEntity::tick() {

	float xMove = 0.0f, yMove = 0.0f;

	dormant = true;
	//if the distance between the entity and the player is less than 150 pixels, start moving towards the player

	if (std::abs(player->getX() - x) < 200 && std::abs(player->getY() - y) < 200) {
		FloatPoint moveRatio = getLengthRatio(player->getX(), player->getY(), x, y);

		xMove = moveRatio.x * speed;
		yMove = moveRatio.y * speed;

		//move the entity
		moveX(xMove);
		moveY(yMove);

		//set the current animation for the direction of movement
		if		(moveRatio.y > 0.0f)   currentAnimation = &animation[0];
		else if (moveRatio.y < 0.0f)   currentAnimation = &animation[1];
		if		(moveRatio.x < -0.85f) currentAnimation = &animation[3];
		else if (moveRatio.x > 0.85f)  currentAnimation = &animation[2];

		//cycle animation, and if the entity isn't moving set the currentFrame to idle
		if (cycleClock.getElapsedTime().asMilliseconds() >= animationCycleSpeed) {
			if (xMove != 0.0f || yMove != 0.0f) {
				cycleClock.restart();
				currentFrame++;
				if (currentFrame >= currentAnimation->length) currentFrame = 0;
			} else currentFrame = 0; //the first frame in the vector doubles as the stagnant frame
		}
	}
}

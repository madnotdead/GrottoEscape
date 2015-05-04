#pragma once
#include "AnimatedSprite.h"
class FireMonster :
	public AnimatedSprite
{
public:
	FireMonster(sf::Vector2f position, std::vector<tmx::MapLayer> collisionObjects);
	~FireMonster();
	void Update(sf::Time dt);
	void HandleCollision();

private:
	sf::Texture texture;
	Animation *currentAnimation;
	std::vector<tmx::MapObject> collisionObjects;
	std::map<Animation, std::string> animations;
	float jumpTime;
	float jumpRate;
	bool onGround;
	sf::Vector2f velocity;
};


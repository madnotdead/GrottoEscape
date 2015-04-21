#pragma once
#include "AnimatedSprite.h"
#include "stdafx.h"
class Slime : public AnimatedSprite
{
private:
	bool onGround;
	sf::Vector2f playerVelocity;
	sf::Texture normalTexture;
	sf::Texture invertedTexture;
	Animation walkingLeft;
	Animation walkingRight;
	Animation *currentAnimation;
	bool facingRight;
	float speed;
	std::vector<tmx::MapLayer> layers;
	//std::vector<tmx::MapObject> collisionObjects;
public:
	Slime(std::vector<tmx::MapLayer> _layers);
	~Slime();
	void HandleCollision();
	void Update(sf::Time dt);
	void GetLayers();
	std::vector<tmx::MapObject> collisionObjects;
};


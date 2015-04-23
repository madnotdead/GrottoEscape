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
	bool isActive;
	std::string name;
	std::vector<sf::Vector2f> points;
	sf::Vector2f currentPoint;
	//std::vector<tmx::MapObject> collisionObjects;
public:
	Slime(std::vector<tmx::MapLayer> _layers, std::string name);
	~Slime();
	void HandleCollision();
	void Update(sf::Time dt);
	void GetLayers();
	std::vector<tmx::MapObject> collisionObjects;
	void SetActive(bool active);
	bool getActive();
	sf::FloatRect getAdjustedGlobalBounds();
};


#pragma once
#include "AnimatedSprite.h"
#include "Bullet.h"
class FireMonster :
	public AnimatedSprite
{
public:
	FireMonster(sf::Vector2f position, std::vector<tmx::MapLayer> collisionObjects);
	~FireMonster();
	void Update(sf::Time dt);
	void HandleCollision();
	void TakeDamage();
	void SetActive(bool active);
	bool IsActive();
	void SpitFire();
	std::vector<Bullet*> spits;
private:
	sf::Texture texture;
	Animation *currentAnimation;
	std::vector<tmx::MapObject> collisionObjects;
	std::map<Animation, std::string> animations;
	float jumpTime;
	float jumpRate;
	bool onGround;
	sf::Vector2f velocity;
	int hit;
	bool active;
	Bullet* spit;
	float spitRate = 2.5f;
	float spiteTime;

};


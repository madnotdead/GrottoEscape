#pragma once
#include "Animation.h"
#include "stdafx.h"
class Bullet :public AnimatedSprite
{
private:
	float bulletSpeed;
	bool active;
	bool facingRigth;
	float bulletTime;
	float bulletlifeTime;
	bool CheckCollision();
	bool collided;
public:
	Bullet(std::vector<tmx::MapObject> _collisionObjects);
	~Bullet();
	sf::Texture texture;
	sf::Texture inv_texture;
	Animation normalAnimation;
	Animation invAnimation;
	Animation *currentAnimation;
	Animation explotionAnimation;
	void Update(sf::Time dt);
	void SetBulletSpeed(float speed);
	bool isActive();
	void SetActive(bool active);
	void SetInitialPosition(sf::Vector2f pos,bool direction);
	std::vector<tmx::MapObject> collisionObjects;
};


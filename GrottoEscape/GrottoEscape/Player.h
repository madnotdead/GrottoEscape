#pragma once
#include "AnimatedSprite.h"
#include "Bullet.h"
#include "stdafx.h"
#include <SFML\Audio.hpp>

enum PlayerState{
	ALIVE,
	DEAD,
	SUCCEDED
};


class Player :
	public AnimatedSprite
{
public:
	Player(sf::RenderWindow *wnd, std::vector<tmx::MapLayer> _layers, ImageManager &imageManager);
	~Player();
	void Update(sf::Time dt);
	void HandleCollision();
	void GetLayers();
	void Jump(float deltaTime);
	void DrawBullets();
	std::vector<Bullet*> bullets;
	void Hit(int damage);
	void HandleItemCollision(Item *mItem);
	int GetHealth();
	void ApplyGravity();
	bool Succeded();
	bool Dead();
	bool isActive();
	void SetActive(bool active);
private:
	Animation succededAnimation;
	Animation walkingAnimationRight;
	Animation walkingAnimationLeft;
	Animation idleAnimationLeft;
	Animation idleAnimationRight;
	Animation jumpLeftAnimation;
	Animation jumpRightAnimation;
	Animation deadAnimation;
	Animation shootLeftAnimation;
	Animation shootRightAnimation;
	Animation winAnimation;
	Animation hitAnimation;
	Animation* currentAnimation;
	float speed;
	bool noKeyWasPressed;
	bool facingRight;
	sf::RenderWindow *window;
	sf::Texture texture;
	sf::Texture textureInverted;
	sf::Texture damageTexture;
	std::vector<tmx::MapLayer> layers;
	sf::Vector2f playerVelocity;
	std::vector<tmx::MapObject> collisionObjects;
	bool onGround;
	bool isJumping;
	float yPosition;
	float xPosition;
	float jumpRate;
	float jumpTime;
	sf::Vector2f shootSpawn;
	void Shoot();
	float shootRate;
	float shootTime;
	bool isDead;
	bool hited;
	float timeSinceLastHit;
	sf::SoundBuffer *shootBuffer;
	sf::Sound *shootSound;
	sf::SoundBuffer *jumpBuffer;
	sf::Sound *jumpSound;
	sf::SoundBuffer *pickUpBuffer;
	sf::Sound *pickUpSound;
	sf::SoundBuffer *winBuffer;
	sf::Sound *winSound;
	sf::SoundBuffer *deathBuffer;
	sf::Sound *deathSound;
	sf::SoundBuffer *hurtBuffer;
	sf::Sound *hurtSound;
	sf::Vector2f initialPosition;
	int health = 3;
	int doubleJump;
	int runs;
	bool win;
	float winRate;
	float winCount;
	PlayerState currentState;
	bool active = true;
};



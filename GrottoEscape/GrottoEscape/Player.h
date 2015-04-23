#pragma once
#include "AnimatedSprite.h"
#include "Bullet.h"
class Player :
	public AnimatedSprite
{
public:
	Player(sf::RenderWindow *wnd, std::vector<tmx::MapLayer> _layers);
	~Player();
	void Loop(sf::Time dt);
	void HandleCollision();
	void GetLayers();
	void Jump(float deltaTime);
	void DrawBullets();
	std::vector<Bullet*> bullets;
	void Hit();
private:
	Animation walkingAnimationUp;
	Animation walkingAnimationRight;
	Animation walkingAnimationLeft;
	Animation walkingAnimationDown;
	Animation idleAnimationLeft;
	Animation idleAnimationRight;
	Animation jumpLeftAnimation;
	Animation jumpRightAnimation;
	Animation deadAnimation;
	Animation shootLeftAnimation;
	Animation shootRightAnimation;
	Animation* currentAnimation;
	float speed;
	bool noKeyWasPressed;
	bool facingRight;
	sf::RenderWindow *window;
	sf::Texture texture;
	sf::Texture textureInverted;
	std::vector<tmx::MapLayer> layers;
	sf::Vector2f playerVelocity;
	std::vector<tmx::MapObject> collisionObjects;
	bool onGround;
	float inAir;
	bool isJumping;
	bool canJump;
	void UpdateJump();
	bool jumpKeyPressed;
	bool jumpInProgress;
	bool ascending;
	float maxJumpHeigth;
	float floorHeigth;
	float mass;
	float jumpF;
	float yPosition;
	float xPosition;
	float jumpRate;
	float jumpTime;
	sf::Vector2f shootSpawn;
	void Shoot();
	float shootRate;
	float shootTime;
	bool isDead;
	float timeFromLastHit;
	//float speed;
	//tmx::MapLayer collisionLayer;
};


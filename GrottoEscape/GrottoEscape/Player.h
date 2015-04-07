#pragma once
#include "AnimatedSprite.h"
class Player :
	public AnimatedSprite
{
public:
	Player(sf::RenderWindow *wnd, std::vector<tmx::MapLayer> _layers);
	~Player();
	void Loop(sf::Time dt);
	void HandleCollision();
private:
	Animation walkingAnimationUp;
	Animation walkingAnimationRight;
	Animation walkingAnimationLeft;
	Animation walkingAnimationDown;
	Animation idleAnimationLeft;
	Animation idleAnimationRight;
	Animation* currentAnimation;
	float speed;
	bool noKeyWasPressed;
	bool facingRight;
	sf::RenderWindow *window;
	sf::Texture texture;
	sf::Texture textureInverted;
	std::vector<tmx::MapLayer> layers;
	sf::Vector2f playerVelocity;
	bool onGround;
	bool inAir;
};


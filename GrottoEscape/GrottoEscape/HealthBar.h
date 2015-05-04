#pragma once
#include "AnimatedSprite.h"

enum HealthType{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	FULL
};

class HealthBar :
	public AnimatedSprite
{
public:
	HealthBar(sf::Vector2f position);
	~HealthBar();
	void Update(sf::Time dt);
	void SetHealthState(int healthPlayere);
	void SetActive(bool active);
	bool IsActive();
private:
	Animation currentAnimation;
	Animation fullHealthAnimation;
	Animation fiveAnimation;
	Animation fourAnimation;
	Animation threeAnimation;
	Animation twoAnimation;
	Animation oneAnimation;
	Animation zeroAnimation;
	sf::Texture texture;
	HealthType type;
	bool active;
};



#pragma once
#include "AnimatedSprite.h"
class Item :
	public AnimatedSprite
{
private:
	Animation *currentAnimation;
public:
	Item();
	~Item();

	void Update(sf::Time dt);
};


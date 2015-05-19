#include "stdafx.h"
#include "HealthBar.h"


HealthBar::HealthBar(sf::Vector2f position)
{
	setPosition(position);

	if (!texture.loadFromFile("img/meter.png"))
	{
		std::cout <<"Couldn't load meter.png" << std::endl;
	}

	oneAnimation.setSpriteSheet(texture);
	oneAnimation.addFrame(sf::IntRect(0, 0, 28, 7));

	twoAnimation.setSpriteSheet(texture);
	twoAnimation.addFrame(sf::IntRect(0, 7, 28, 7));

	threeAnimation.setSpriteSheet(texture);
	threeAnimation.addFrame(sf::IntRect(0, 14, 28, 7));

	fourAnimation.setSpriteSheet(texture);
	fourAnimation.addFrame(sf::IntRect(0, 21, 28, 7));

	fiveAnimation.setSpriteSheet(texture);
	fiveAnimation.addFrame(sf::IntRect(0, 28, 28, 7));

	fullHealthAnimation.setSpriteSheet(texture);
	fullHealthAnimation.addFrame(sf::IntRect(0, 35, 28, 7));

	zeroAnimation.setSpriteSheet(texture);
	zeroAnimation.addFrame(sf::IntRect(0, 42, 28, 7));

	currentAnimation = fullHealthAnimation;
	type = HealthType::FULL;
	active = true;
}


HealthBar::~HealthBar()
{
}

void HealthBar::Update(sf::Time dt)
{
	if (!IsActive())
		return;
	switch (type)
	{
	case ZERO:
		currentAnimation = zeroAnimation;
		break;
	case ONE:
		currentAnimation = oneAnimation;
		break;
	case TWO:
		currentAnimation = twoAnimation;
		break;
	case THREE:
		currentAnimation = threeAnimation;
		break;
	case FOUR:
		currentAnimation = fourAnimation;
		break;
	case FIVE:
		currentAnimation = fiveAnimation;
		break;
	case FULL:
		currentAnimation = fullHealthAnimation;
		break;
	default:
		break;
	}

	play(currentAnimation);

	update(dt);
}

void HealthBar::SetHealthState(int healthType)
{
	type = (HealthType)healthType;
}

void HealthBar::SetActive(bool active)
{
	this->active = active;
}

bool HealthBar::IsActive()
{
	return active;
}
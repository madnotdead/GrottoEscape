#include "stdafx.h"
#include "Item.h"


Item::Item(sf::Vector2f position, ItemType type)
{
	setPosition(position);

	if (!texture.loadFromFile("img/items.png"))
	{
		std::cout << "Failed to load player spritesheet: player_2.png!" << std::endl;
		//return 1;
	}

	currentAnimation = new Animation();
	currentAnimation->setSpriteSheet(texture);

	switch (type)
	{
	case POWER_UP:
		currentAnimation->addFrame(sf::IntRect(0, 48, 16, 16));
		break;
	case OBJECTIVE:
		currentAnimation->addFrame(sf::IntRect(16, 48, 16, 16));
		break;
	case SPAWN:
		currentAnimation->addFrame(sf::IntRect(32, 48, 16, 16));
		break;
	case COLLECTABLE:
		currentAnimation->addFrame(sf::IntRect(0, 16, 16, 16));
		currentAnimation->addFrame(sf::IntRect(16, 16, 16, 16));
		currentAnimation->addFrame(sf::IntRect(32, 16, 16, 16));
		currentAnimation->addFrame(sf::IntRect(48, 16, 16, 16));
		break;
	case FINAL:
		currentAnimation->addFrame(sf::IntRect(0
			, 0, 16, 16));
		currentAnimation->addFrame(sf::IntRect(16, 0, 16, 16));
		currentAnimation->addFrame(sf::IntRect(32, 0, 16, 16));

		break;
	default:
		break;
	}
}


Item::~Item()
{
}

void Item::SetActive(bool active)
{
	this->active = active;
}

bool Item::IsActive()
{
	return active;
}

void Item::Update(sf::Time dt)
{
	play(*currentAnimation);

	update(dt);
}
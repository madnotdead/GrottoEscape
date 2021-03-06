#include "stdafx.h"
#include "Item.h"

Item::Item(sf::Vector2f _position, ItemType _type)
{
	setPosition(_position);

	if (!texture.loadFromFile("img/items.png"))
	{
		std::cout << "Failed to load player spritesheet: player_2.png!" << std::endl;
		//return 1;
	}
	active = true;
	currentAnimation = new Animation();
	currentAnimation->setSpriteSheet(texture);
	type = _type;
	switch (type)
	{
	case POWER_UP:
		currentAnimation->addFrame(sf::IntRect(0, 48, 16, 16));
		break;
	case HEALTH:
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
		currentAnimation->addFrame(sf::IntRect(0, 0, 16, 16));
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
	if (!IsActive())
		return;

	play(*currentAnimation);

	update(dt);
}

ItemType Item::GetType()
{
	return type;
}

bool Item::Collected()
{
	return !IsActive();
}
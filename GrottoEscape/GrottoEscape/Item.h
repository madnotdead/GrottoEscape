#pragma once
#include "AnimatedSprite.h"
#include "stdafx.h"

enum ItemType
{
	POWER_UP,
	HEALTH,
	SPAWN,
	COLLECTABLE,
	FINAL
};

class Item :
	public AnimatedSprite
{
private:
	Animation *currentAnimation;
	sf::Texture texture;
	bool active;
	ItemType type;
public:
	Item(sf::Vector2f position, ItemType type);
	~Item();
	bool IsActive();
	void SetActive(bool active);
	void Update(sf::Time dt);
	ItemType GetType();
	bool Collected();
};


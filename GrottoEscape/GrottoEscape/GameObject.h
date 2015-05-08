#pragma once
#include "AnimatedSprite.h"
class GameObject :
	public AnimatedSprite
{
public:
	GameObject();
	~GameObject();
	virtual void Update() = 0;
	virtual void HandleCollision() =0;
	bool IsActive(){ return isActive; }
	void SetActive(bool _active){ isActive = _active; }
private:
	bool isActive = true;
	Animation *currentAnimation;
	sf::Texture texture;
};


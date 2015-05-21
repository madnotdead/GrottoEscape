#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(std::vector<tmx::MapObject> _collisionObjects, ImageManager &imageManager) :AnimatedSprite(sf::seconds(0.2f), true, false)
{
	texture = imageManager.GetImage("items.png");

	// set up the animations for all four directions (set spritesheet and push frames)
	normalAnimation.setSpriteSheet(texture);
	normalAnimation.addFrame(sf::IntRect(0, 32, 16, 16));
	normalAnimation.addFrame(sf::IntRect(16, 32, 16, 16));
	normalAnimation.addFrame(sf::IntRect(32, 32, 16, 16));

	explotionAnimation.setSpriteSheet(texture);
	explotionAnimation.addFrame(sf::IntRect(48, 32, 16, 16));

	active = false;
	bulletTime = 3.0f;
	bulletSpeed = 120.0f;
	bulletlifeTime = 0;
	collisionObjects = _collisionObjects;

	currentAnimation = &normalAnimation;
}


Bullet::~Bullet()
{
}

void Bullet::Update(sf::Time dt)
{
	if (!isActive())
		return;


	bulletlifeTime += dt.asSeconds();

	if (bulletlifeTime > bulletTime)
	{
		SetActive(false);
		bulletlifeTime = 0;
	}
		
	
	if (!collided){

		float xPosition;
		currentAnimation = &normalAnimation;
		if (facingRigth)
		{			
			setScale(1, 1);
			xPosition = getPosition().x + bulletSpeed * dt.asSeconds();
		}
		else
		{
			xPosition = getPosition().x - bulletSpeed * dt.asSeconds();
			setScale(-1, 1);
		}

		setPosition(xPosition, getPosition().y);
	}


	play(*currentAnimation);

	update(dt);

	collided = CheckCollision();
}

void Bullet::SetBulletSpeed(float speed)
{
	bulletSpeed = speed;
}

void Bullet::SetActive(bool active)
{
	this->active = active;
}

bool Bullet::isActive()
{
	return active;
}

void Bullet::SetInitialPosition(sf::Vector2f pos,bool direction)
{
	setPosition(pos);
	facingRigth = direction;
}

bool Bullet::CheckCollision()
{
	sf::FloatRect collisionRect;

	if (collisionObjects.size() > 0)
	{
		for (auto object = collisionObjects.begin(); object != collisionObjects.end(); ++object)
		{
			if (object->GetAABB().intersects(getGlobalBounds(),collisionRect))
			{
				if (collisionRect.width > 3 && collisionRect.height > 3)
				{
					currentAnimation = &explotionAnimation;
					bulletlifeTime += 0.3f;
					return true;
				}
			}
				
		}
	}

	return false;
}
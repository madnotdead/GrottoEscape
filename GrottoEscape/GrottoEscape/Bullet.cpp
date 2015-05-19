#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(std::vector<tmx::MapObject> _collisionObjects) :AnimatedSprite(sf::seconds(0.2f), true, false)
{

	if (!texture.loadFromFile("img/items.png"))
	{
		std::cout << "Failed to load player spritesheet: items.png!" << std::endl;
		//return 1;
	}
	else
		std::cout << "items.png loaded!" << std::endl;

	sf::Texture textureInverted;
	if (!inv_texture.loadFromFile("img/items_i.png"))
	{
		std::cout << "items_i.png loaded!" << std::endl;
		//return 1;
	}

	// set up the animations for all four directions (set spritesheet and push frames)
	normalAnimation.setSpriteSheet(texture);
	normalAnimation.addFrame(sf::IntRect(0, 32, 16, 16));
	normalAnimation.addFrame(sf::IntRect(16, 32, 16, 16));
	normalAnimation.addFrame(sf::IntRect(32, 32, 16, 16));
	//normalAnimation.addFrame(sf::IntRect(48, 32, 16, 16));
	// set up the animations for all four directions (set spritesheet and push frames)
	invAnimation.setSpriteSheet(inv_texture);
	invAnimation.addFrame(sf::IntRect(48, 32, 16, 16));
	invAnimation.addFrame(sf::IntRect(32, 32, 16, 16));
	invAnimation.addFrame(sf::IntRect(16, 32, 16, 16));

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
		std::cout << "bulletlifetime: " << bulletlifeTime << std::endl;
		SetActive(false);
		bulletlifeTime = 0;
	}
		
	
	if (!collided){

		float xPosition;

		if (facingRigth)
		{
			currentAnimation = &normalAnimation;
			xPosition = getPosition().x + bulletSpeed * dt.asSeconds();
		}
		else
		{
			xPosition = getPosition().x - bulletSpeed * dt.asSeconds();
			currentAnimation = &invAnimation;
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
	collisionRect.height = getGlobalBounds().height - 2;
	collisionRect.width = getGlobalBounds().width - 2;
	collisionRect.left = getGlobalBounds().left +2;
	collisionRect.top= getGlobalBounds().top + 2;

	if (collisionObjects.size() > 0)
	{
		for (auto object = collisionObjects.begin(); object != collisionObjects.end(); ++object)
		{
			if (object->GetAABB().intersects(collisionRect))
			{
				currentAnimation = &explotionAnimation;
				bulletlifeTime += 0.3f;
				return true;
			}
				
		}
	}

	return false;
}
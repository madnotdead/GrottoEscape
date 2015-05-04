#include "stdafx.h"
#include "FireMonster.h"


FireMonster::FireMonster(sf::Vector2f position, std::vector<tmx::MapLayer> collisionObjects) :AnimatedSprite(sf::seconds(0.16f), true, false)
{
	if (!texture.loadFromFile("img/enemies.png"))
	{
		std::cout << "Couldn't load firemoster texture!" << std::endl;
		return;
	}

	for (size_t i = 0; i < collisionObjects.size(); i++)
	{
		if (collisionObjects.at(i).name == "Collision")
		{
			this->collisionObjects = collisionObjects.at(i).objects;
			break;
		}
	}
	
	currentAnimation = new Animation();
	currentAnimation->setSpriteSheet(texture);
	currentAnimation->addFrame(sf::IntRect(0,16,16,16));
	currentAnimation->addFrame(sf::IntRect(16, 16, 16, 16));
	currentAnimation->addFrame(sf::IntRect(32, 16, 16, 16));
	currentAnimation->addFrame(sf::IntRect(48, 16, 16, 16));
	setScale(sf::Vector2f(-1, 1));
	jumpRate = 3.0f;
	jumpTime = 0;
	setPosition(position);

}


FireMonster::~FireMonster()
{
}

void FireMonster::Update(sf::Time dt)
{
	
	jumpTime += dt.asSeconds();

	if (jumpTime >= jumpRate)
	{
		jumpTime = 0;
		jumpRate = Utils::GetRandomIntValue(3, 7);

		velocity.y = -275;
	}

	if (!onGround || velocity.y < 0)//Sino esta en el piso aplico gravedad
		velocity.y += 20;
	else
		velocity.y = 0;
	
	move(velocity * dt.asSeconds());
	update(dt);
	play(*currentAnimation);
	HandleCollision();
}

void FireMonster::HandleCollision()
{
	sf::Rect<float> area;
	onGround = false;
	if (collisionObjects.size() > 0)
	{
		for (auto object = collisionObjects.begin(); object != collisionObjects.end(); ++object)
		{
			if (object->GetAABB().intersects(getGlobalBounds(), area))
			{
				if (area.width > area.height)
				{
					if (!area.contains({ area.left, getPosition().y }))
					{
						setPosition({ getPosition().x, getPosition().y - area.height });
						//std::cout << "Down side crash" << std::endl;
						onGround = true;
					}
					else
					{
						// Up side crash
						setPosition({ getPosition().x, getPosition().y + area.height });
						std::cout << "Up side crash" << std::endl;
					}
				}
				else if (area.width < area.height)
				{
					if (area.contains({ getPosition().x + getGlobalBounds().width - 1.f, area.top + 1.f }))
					{
						//Right side crash
						setPosition({ getPosition().x - area.width, getPosition().y });
						std::cout << "Right side crash" << std::endl;
					}
					else
					{
						//Left side crash
						setPosition({ getPosition().x + area.width, getPosition().y });
						std::cout << "Left side crash" << std::endl;
					}
				}
			}
		}
	}
}
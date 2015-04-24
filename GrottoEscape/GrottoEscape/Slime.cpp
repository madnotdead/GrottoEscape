#include "stdafx.h"
#include "Slime.h"


Slime::Slime(std::vector<tmx::MapLayer> _layers, std::string name) :AnimatedSprite(sf::seconds(0.2f), true, false)

{
	if (!normalTexture.loadFromFile("img/enemies.png"))
	{
		std::cout << "failed to load: enemies.png!" << std::endl;
		//return 1;
	}
	else
		std::cout << "items.png loaded!" << std::endl;

	//sf::Texture textureInverted;
	if (!invertedTexture.loadFromFile("img/enemies2.png"))
	{
		std::cout << "failed to load: enemies.png!" << std::endl;
		//return 1;
	}

	walkingRight.setSpriteSheet(normalTexture);
	walkingRight.addFrame(sf::IntRect(0, 0, 16, 16));
	walkingRight.addFrame(sf::IntRect(16, 0, 16, 16));
	walkingRight.addFrame(sf::IntRect(32, 0, 16, 16));

	walkingLeft.setSpriteSheet(invertedTexture);
	walkingLeft.addFrame(sf::IntRect(48, 0, 16, 16));
	walkingLeft.addFrame(sf::IntRect(32, 0, 16, 16));
	walkingLeft.addFrame(sf::IntRect(16, 0, 16, 16));
	
	facingRight = false;

	setPosition(sf::Vector2f(300, 250));
	layers = _layers;
	speed = 50.0f;

	this->name = name;

	GetLayers();

	setPosition(points.at(0));

	SetActive(true);
}


Slime::~Slime()
{
}

void Slime::Update(sf::Time dt)
{
	if (!getActive())
		return;

	float xPosition;

	if (facingRight)
	{
		currentPoint = points.at(1);
		currentAnimation = &walkingRight;
		xPosition = getPosition().x + speed * dt.asSeconds();
	}
	else
	{
		currentPoint = points.at(0);
		xPosition = getPosition().x - speed * dt.asSeconds();
		currentAnimation = &walkingLeft;
	}

	if (currentPoint.x ==  roundf(getPosition().x))
		facingRight = !facingRight;

	if (!onGround || playerVelocity.y < 0)//Sino esta en el piso aplico gravedad
		playerVelocity.y += 20;
	else
		playerVelocity.y = 0;

	float yPosition = getPosition().y + playerVelocity.y  * dt.asSeconds();

	setPosition(xPosition, yPosition);
	
	play(*currentAnimation);

	update(dt);

	HandleCollision();
	//collided = CheckCollision();
}

void Slime::HandleCollision()
{
	sf::Rect<float> area;
	onGround = false;
	if (collisionObjects.size() > 0)
	{
		for (auto object = collisionObjects.begin(); object != collisionObjects.end(); ++object)
		{
			if (object->GetAABB().intersects(getGlobalBounds(), area))
			{
				if (object->GetPropertyString("IsLava") == "true")
				{
					SetActive(false);
					return;
				}

				if (area.width > area.height)
				{
					if (!area.contains({ area.left, getPosition().y }))
					{
						// Down side crash
						onGround = true;
						playerVelocity.y = 0;
						setPosition({ getPosition().x, getPosition().y - area.height });
						//std::cout << "Down side crash" << std::endl;
					}
					else
					{
						onGround = false;
						playerVelocity.y = 0;
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
						facingRight = false;
					}
					else
					{
						//Left side crash
						setPosition({ getPosition().x + area.width, getPosition().y });
						std::cout << "Left side crash" << std::endl;
						facingRight = true;
					}
				}
			}
		}
	}
}

void Slime::GetLayers()
{
	if (layers.size() > 0)
	{
		for (auto layer = layers.begin(); layer != layers.end(); ++layer)
		{
			if (layer->name == "Collision")
				collisionObjects = layer->objects;

			if (layer->name == "Waypoints")
			{
				for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
				{
					if (object->GetName() == name)
					{
						points.push_back(object->GetPosition());
					}
				}
			}
		}
	}
}

void Slime::SetActive(bool active)
{
	this->isActive = active;
}

bool Slime::getActive()
{
	return this->isActive;
}

sf::FloatRect Slime::getAdjustedGlobalBounds()
{
	return sf::FloatRect(getGlobalBounds().left + 4, getGlobalBounds().top + 4, getGlobalBounds().width - 4, getGlobalBounds().height - 4);
}
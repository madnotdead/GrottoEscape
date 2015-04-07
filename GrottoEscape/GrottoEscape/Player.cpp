#include "stdafx.h"
#include "Player.h"


Player::Player(sf::RenderWindow *wnd, std::vector<tmx::MapLayer> _layers ) :AnimatedSprite(sf::seconds(0.2), true, false)
{
	window = wnd;
	layers = _layers;
	// load texture (spritesheet)
	//sf::Texture texture;
	if (!texture.loadFromFile("img/player_2.png"))
	{
		std::cout << "Failed to load player spritesheet: player_2.png!" << std::endl;
		//return 1;
	}

	//sf::Texture textureInverted;
	if (!textureInverted.loadFromFile("img/player_2_i.png"))
	{
		std::cout << "Failed to load player spritesheet: player_2_i.png!" << std::endl;
		//return 1;
	}
	
	// set up the animations for all four directions (set spritesheet and push frames)

	
	idleAnimationRight.setSpriteSheet(texture);
	idleAnimationRight.addFrame(sf::IntRect(16, 16, 16, 16));

	
	idleAnimationLeft.setSpriteSheet(textureInverted);
	idleAnimationLeft.addFrame(sf::IntRect(32, 16, 16, 16));

	
	walkingAnimationDown.setSpriteSheet(texture);
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));

	walkingAnimationLeft.setSpriteSheet(textureInverted);
	walkingAnimationLeft.addFrame(sf::IntRect(48, 0, 16, 16));
	walkingAnimationLeft.addFrame(sf::IntRect(32, 0, 16, 16));
	walkingAnimationLeft.addFrame(sf::IntRect(16, 0, 16, 16));
		
	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationRight.addFrame(sf::IntRect(0, 0, 16, 16));
	walkingAnimationRight.addFrame(sf::IntRect(16, 0, 16, 16));
	walkingAnimationRight.addFrame(sf::IntRect(32, 0, 16, 16));
		
	walkingAnimationUp.setSpriteSheet(texture);
	walkingAnimationUp.addFrame(sf::IntRect(0, 16, 16, 16));
	//walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
	//walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	//walkingAnimationUp.addFrame(sf::IntRect(0, 96, 32, 32));

	currentAnimation = &idleAnimationRight;

	// set up AnimatedSprite
	setPosition(sf::Vector2f(50,250));

	speed = 80.f;
	noKeyWasPressed = true;
	facingRight = true;

	// Create a sf::Vector2f for player velocity and add to the y variable value gravity
	playerVelocity.x = 0;
	playerVelocity.y = 200;
}


Player::~Player()
{
}

void Player::Loop(sf::Time dt)
{
	float maxInAir = 0.8f;
	float gravity = 500;
	// if a key was pressed set the correct animation and move correctly
	sf::Vector2f movement(0.f, 0.f);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	//{
	//	currentAnimation = &walkingAnimationUp;
	//	movement.y -= speed;
	//	noKeyWasPressed = false;
	//}
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		currentAnimation = &walkingAnimationDown;
		movement.y += speed;
		noKeyWasPressed = false;
	}*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		currentAnimation = &walkingAnimationLeft;
		movement.x -= speed;
		noKeyWasPressed = false;
		facingRight = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		currentAnimation = &walkingAnimationRight;
		movement.x += speed;
		noKeyWasPressed = false;
		facingRight = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (onGround || inAir < maxInAir))
	{
		movement.y = -gravity;
		inAir += dt.asSeconds();
	}
	else
	{
		movement.y = gravity;
		inAir = maxInAir;
	}

	
	play(*currentAnimation);
	move(movement * dt.asSeconds());

	// if no key was pressed stop the animation
	if (noKeyWasPressed)
	{
		stop();

		if (facingRight)
			currentAnimation = &idleAnimationRight;
		else
			currentAnimation = &idleAnimationLeft;
	}
	noKeyWasPressed = true;

	// update AnimatedSprite
	update(dt);

	HandleCollision();
	
}

void Player::HandleCollision()
{
	sf::Rect<float> area;
	onGround = false;

	if (layers.size() > 0)
	{
		for (auto layer = layers.begin(); layer != layers.end(); ++layer)
		{
			if (layer->name == "Coll")
			{
				for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
				{			
						if (object->GetAABB().intersects(getGlobalBounds(), area))
						{
							if (area.width > area.height)
							{
								if (area.contains({ area.left, getPosition().y }))
								{
									// Up side crash
									setPosition({ getPosition().x, getPosition().y + area.height });
									std::cout << "Up side crash" << std::endl;
								}
								else
								{
									// Down side crash
									onGround = true;
									inAir = 0.f;
									setPosition({ getPosition().x, getPosition().y - area.height });
									std::cout << "Down side crash" << std::endl;
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
	}
}
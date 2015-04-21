#include "stdafx.h"
#include "Player.h"


Player::Player(sf::RenderWindow *wnd, std::vector<tmx::MapLayer> _layers ) :AnimatedSprite(sf::seconds(0.2f), true, false)
{
	window = wnd;
	layers = _layers;
	onGround = false;
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

	jumpLeftAnimation.setSpriteSheet(textureInverted);
	jumpLeftAnimation.addFrame(sf::IntRect(48, 16, 16, 16));
	
	jumpRightAnimation.setSpriteSheet(texture);
	jumpRightAnimation.addFrame(sf::IntRect(0, 16, 16, 16));

	walkingAnimationLeft.setSpriteSheet(textureInverted);
	walkingAnimationLeft.addFrame(sf::IntRect(48, 0, 16, 16));
	walkingAnimationLeft.addFrame(sf::IntRect(32, 0, 16, 16));
	walkingAnimationLeft.addFrame(sf::IntRect(16, 0, 16, 16));

	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationRight.addFrame(sf::IntRect(0, 0, 16, 16));
	walkingAnimationRight.addFrame(sf::IntRect(16, 0, 16, 16));
	walkingAnimationRight.addFrame(sf::IntRect(32, 0, 16, 16));
		
	deadAnimation.setSpriteSheet(texture);
	deadAnimation.addFrame(sf::IntRect(48, 16, 16, 16));

	shootLeftAnimation.setSpriteSheet(textureInverted);
	shootLeftAnimation.addFrame(sf::IntRect(0, 0, 16, 16));

	shootRightAnimation.setSpriteSheet(texture);
	shootRightAnimation.addFrame(sf::IntRect(48, 0, 16, 16));

	currentAnimation = &idleAnimationRight;

	// set up AnimatedSprite
	setPosition(sf::Vector2f(400,300));

	speed = 80.f;
	noKeyWasPressed = true;
	facingRight = true;

	// Create a sf::Vector2f for player velocity and add to the y variable value gravity
	playerVelocity = sf::Vector2f(0, 0);
	GetLayers();

	jumpF = 400;
	mass = 75;

	jumpRate = 0.6f;
	shootRate = 0.5f;
	for (size_t i = 0; i < 10; i++)
	{
		bullets.push_back(new Bullet(collisionObjects));
	}
}


Player::~Player()
{
	delete currentAnimation;

	for (size_t i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}

}

void Player::Loop(sf::Time dt)
{
	float maxInAir = 0.3f;
	float gravity = 20;
	// if a key was pressed set the correct animation and move correctly
	sf::Vector2f movement(0.f, 0.f);
	


	float velX = 0.0f;
	playerVelocity.x = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (onGround)
			currentAnimation = &walkingAnimationLeft;

		movement.x -= speed;
		velX = -80.0f;
		noKeyWasPressed = false;
		facingRight = false;
		playerVelocity.x = -80;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (onGround)
		currentAnimation = &walkingAnimationRight;

		movement.x = speed;
		noKeyWasPressed = false;
		facingRight = true;
		velX = 80.0f;
		playerVelocity.x = 80;
	}

	if (facingRight)
		shootSpawn = sf::Vector2f(getPosition().x + 8, getPosition().y);
	else
		shootSpawn = sf::Vector2f(getPosition().x - 8 , getPosition().y);

	shootTime += dt.asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && shootTime > shootRate)
	{
		if (facingRight)
			currentAnimation = &shootRightAnimation;
		else
			currentAnimation = &shootLeftAnimation;

		Shoot();
		std::cout << "ShootSpawn: "<< shootSpawn.x << "," << shootSpawn.y << std::endl;
		shootTime = 0.0f;

		noKeyWasPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		setPosition(sf::Vector2f(450, 300));


	/////////////////////////////////////////////////////////DEBUG
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	//	currentAnimation = &deadAnimation;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	//	currentAnimation = &shootLeftAnimation;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	//	currentAnimation = &shootRightAnimation;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	//	currentAnimation = &jumpLeftAnimation;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	//	currentAnimation = &jumpRightAnimation;
	/////////////////////////////////////////////////////////DEBUG
	float velY = 200.0f;

	//std::cout << "inAir < maxInAir: " << (inAir < maxInAir) << std::endl;
	float currentFloorHeigth = 0;
	
	jumpTime += dt.asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround && jumpTime >= jumpRate)
	{
		//movement.y -= gravity;
		//inAir += dt.asSeconds();
		std::cout << "jumpTime: " << jumpTime << std::endl;
		jumpTime = 0.0f;

		onGround = false;
		velY = -200.0f;
		isJumping = true;
		//currentFloorHeigth = getPosition().y + 16;
		noKeyWasPressed = false;
		playerVelocity.y = -275;
	}  
	else
	{
		if (!onGround || playerVelocity.y < 0)//Sino esta en el piso aplico gravedad
			playerVelocity.y += gravity;
		else
			playerVelocity.y = 0;
	}
	

	if (isJumping)
	{
		if (facingRight)
			currentAnimation = &jumpRightAnimation;
		else
			currentAnimation = &jumpLeftAnimation;
	}
		
	float yPosition = getPosition().y + velY * dt.asSeconds() + 4.9f * (dt.asSeconds() * 2);
	float xPosition = getPosition().x + velX * dt.asSeconds();
	

	play(*currentAnimation);

	move(playerVelocity * dt.asSeconds());

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

	for (size_t i = 0; i < 10; i++)
	{
		bullets[i]->Update(dt);
	}
}

void Player::GetLayers()
{
	if (layers.size() > 0)
	{
		for (auto layer = layers.begin(); layer != layers.end(); ++layer)
		{
			if (layer->name == "Collision")
				 collisionObjects = layer->objects;

			if (layer->name == "Player"){
				for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
				{
					//setPosition(object->GetPosition());
				}
			}

		}
	}
}

void Player::HandleCollision()
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
						// Down side crash
						onGround = true;
						isJumping = false;
						inAir = 0.f;
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

void Player::Jump(float deltaTime)
{
	speed -= 9.8 * deltaTime;

	move(0, -speed);
}

void Player::Shoot()
{
	for (size_t i = 0; i < 10; i++)
	{
		if (bullets[i]->isActive())
			continue;

		bullets[i]->SetActive(true);
		bullets[i]->SetInitialPosition(shootSpawn,facingRight);
		break;
	}
}

void Player::DrawBullets()
{
	//for (size_t i = 0; i < 10; i++)
	//{
	//	window->draw(bullets[i]->draw);

	//}
	
}
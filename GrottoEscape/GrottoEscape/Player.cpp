#include "stdafx.h"
#include "Player.h"


Player::Player(sf::RenderWindow *wnd, std::vector<tmx::MapLayer> _layers ) :AnimatedSprite(sf::seconds(0.2f), true, false)
{
	window = wnd;
	layers = _layers;
	onGround = false;

	// load texture (spritesheet)
	if (!texture.loadFromFile("img/player_2.png"))
	{
		std::cout << "Failed to load player spritesheet: player_2.png!" << std::endl;
	}

	//sf::Texture textureInverted;
	if (!textureInverted.loadFromFile("img/player_2_i.png"))
	{
		std::cout << "Failed to load player spritesheet: player_2_i.png!" << std::endl;
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

	winAnimation.setSpriteSheet(texture);
	winAnimation.addFrame(sf::IntRect(32, 16, 16, 16));

	currentAnimation = &idleAnimationRight;

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

	jumpBuffer = new sf::SoundBuffer;

	if (!jumpBuffer->loadFromFile("audio/jump.wav"))
	{
		delete jumpBuffer;
		jumpBuffer = 0;
	}

	jumpSound = new sf::Sound(*jumpBuffer);
	jumpSound->setVolume(50.0f);


	shootBuffer= new sf::SoundBuffer;
	if (!shootBuffer->loadFromFile("audio/laser.wav"))
	{
		delete shootBuffer;
		shootBuffer = 0;
	}

	shootSound = new sf::Sound(*shootBuffer);
	shootSound->setVolume(50.0f);

	pickUpBuffer= new sf::SoundBuffer;
	if (!pickUpBuffer->loadFromFile("audio/pickup.wav"))
	{
		delete pickUpBuffer;
		pickUpBuffer = 0;
	}

	pickUpSound = new sf::Sound(*pickUpBuffer);
	pickUpSound->setVolume(50.0f);

	winBuffer = new sf::SoundBuffer;
	if (!winBuffer->loadFromFile("audio/success.wav"))
	{
		delete winBuffer;
		winBuffer = 0;
	}

	winSound= new sf::Sound(*winBuffer);
	winSound->setVolume(100.0f);

	winRate = 0.5f;
	currentState = PlayerState::ALIVE; 
}

Player::~Player()
{
	//delete currentAnimation;

	for (size_t i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}

}

void Player::Update(sf::Time dt)
{
	//Auxiliar variables to store position
	sf::Vector2f newPostion(0, 0);
	
	sf::Vector2f movement(0.f, 0.f);

	switch (currentState)
	{
	case PlayerState::ALIVE:

		playerVelocity.x = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (onGround)
				currentAnimation = &walkingAnimationLeft;

			movement.x -= speed;
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
			playerVelocity.x = 80;
		}

		if (facingRight)
			shootSpawn = sf::Vector2f(getPosition().x + 8, getPosition().y);
		else
			shootSpawn = sf::Vector2f(getPosition().x - 8, getPosition().y);

		shootTime += dt.asSeconds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && shootTime > shootRate)
		{
			if (facingRight)
				currentAnimation = &shootRightAnimation;
			else
				currentAnimation = &shootLeftAnimation;

			Shoot();
			shootSound->play();
			std::cout << "ShootSpawn: " << shootSpawn.x << "," << shootSpawn.y << std::endl;
			shootTime = 0.0f;

			noKeyWasPressed = false;
		}

		jumpTime += dt.asSeconds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround && jumpTime >= jumpRate)
		{
			jumpTime = 0.0f;
			onGround = false;
			isJumping = true;
			noKeyWasPressed = false;
			playerVelocity.y = -275;
			jumpSound->play();
		}

		if (isJumping)
		{
			if (facingRight)
				currentAnimation = &jumpRightAnimation;
			else
				currentAnimation = &jumpLeftAnimation;
		}

		//To avoid player from being hit constantly
		if (timeSinceLastHit > 0)
			timeSinceLastHit -= dt.asSeconds();

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
		
		break;
	case PlayerState::SUCCEDED:
		
		currentAnimation = &winAnimation;

		//Little celebration 
		winCount += dt.asSeconds();
		if (winCount > winRate)
		{
			playerVelocity.y = -100;
			winCount = 0;
		}

		playerVelocity.x = 0;

		break;
	case PlayerState::DEAD:
		
		//ApplyGravity();
		currentAnimation = &deadAnimation;
		health = 0;

		break;
	default:
		break;
	}
	
	//Modify velocity using gravity
	ApplyGravity();
		
	newPostion.y = getPosition().y + playerVelocity.y * dt.asSeconds() + 4.9f * (dt.asSeconds() * 2);
	newPostion.x = getPosition().x + playerVelocity.x * dt.asSeconds();
	//move(playerVelocity * dt.asSeconds());
	setPosition(newPostion);
	
	play(*currentAnimation);
	// update AnimatedSprite
	update(dt);

	HandleCollision();	

	//updateBullets
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
					initialPosition = object->GetPosition();
					setPosition(initialPosition);
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
				if (object->GetPropertyString("IsLava") == "true")
				{
					currentState = PlayerState::DEAD;
					isDead = true;
					health = 0;
				}
					

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

void Player::Hit(int damage)
{

	if (timeSinceLastHit <= 0 && !isDead)
	{
		timeSinceLastHit = 2;
		playerVelocity.y = -300;
		health -= damage;
	}
	

	if (health <= 0)
	{
		isDead = true;
		currentState = PlayerState::DEAD;
	}
		
	//std::cout << "playerVelocity.x: " << playerVelocity.x << std::endl;

}

void Player::HandleItemCollision(Item *mItem)
{

	if (!mItem->IsActive())
		return;	
	bool final = false;
	switch (mItem->GetType())
	{
	case POWER_UP:
		std::cout << "Power up item collected." << std::endl;
		break;
	case OBJECTIVE:
		std::cout << "Objective collected." << std::endl;
		break;
	case SPAWN:
		std::cout << "Spawn item collected." << std::endl;
		break;
	case COLLECTABLE:
		std::cout << "collectable item collected." << std::endl;
		break;
	case FINAL:
		//std::cout << "Final item collected." << std::endl;
		mItem->SetActive(false);
		currentState = PlayerState::SUCCEDED;
		final = true;
		win = true;
		winSound->play();
		break;
	default:
		break;
	}

	if (!final)
	{
		mItem->SetActive(false);
		pickUpSound->play();
	}
		
}

int Player::GetHealth()
{
	return health;
}

void Player::ApplyGravity()
{
	if (!onGround || playerVelocity.y < 0)//Sino esta en el piso aplico gravedad
		playerVelocity.y += 20;
	else
		playerVelocity.y = 0;
}
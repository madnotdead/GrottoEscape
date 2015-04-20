#include "stdafx.h"
#include "Player.h"


Player::Player(sf::RenderWindow *wnd, std::vector<tmx::MapLayer> _layers ) :AnimatedSprite(sf::seconds(0.2f), true, false)
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
	setPosition(sf::Vector2f(50,272));

	speed = 80.f;
	noKeyWasPressed = true;
	facingRight = true;

	// Create a sf::Vector2f for player velocity and add to the y variable value gravity
	//playerVelocity.x = 0;
	//playerVelocity.y = 200;

	GetLayers();

	jumpF = 400;
	mass = 75;
}


Player::~Player()
{
}

void Player::Loop(sf::Time dt)
{
	float maxInAir = 0.4f;
	float gravity = 100;
	// if a key was pressed set the correct animation and move correctly
	sf::Vector2f movement(0.f, 0.f); 
	float velY = 80.0f;
	float velX = 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (onGround)
			currentAnimation = &walkingAnimationLeft;
		else
			currentAnimation = facingRight ? &jumpRightAnimation : &jumpRightAnimation;

		movement.x -= speed;
		velX = -80.0f;
		noKeyWasPressed = false;
		facingRight = false;
		playerVelocity.x -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (onGround)
			currentAnimation = &walkingAnimationRight;
		else
			currentAnimation = facingRight ? &jumpRightAnimation : &jumpRightAnimation;
		movement.x += speed;
		noKeyWasPressed = false;
		facingRight = true;
		velX = 80.0f;
		playerVelocity.x += speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		setPosition(sf::Vector2f(50, 250));


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
	//velY = 100.0f;

	//std::cout << "inAir < maxInAir: " << (inAir < maxInAir) << std::endl;
	float currentFloorHeigth = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&( onGround || inAir < maxInAir))
	{
		
		inAir += dt.asSeconds();
		/*movement.y -= gravity;
		if (facingRight)
			currentAnimation = &jumpRightAnimation;
		else
			currentAnimation = &jumpLeftAnimation;*/
		movement.y = -100;
		//isJumping = true;
		//currentFloorHeigth = getPosition().y + 16;
		onGround = false;
	}
	else
	{
		movement.y = 100;
		inAir = maxInAir;
	}

/*	if (isJumping)
	{
		if (getPosition().y <= currentFloorHeigth + 20)
			velY = 2.0f;
	}
	*/	
		
	//float yPosition = getPosition().y + velY * dt.asSeconds();// +4.9f * (dt.asSeconds() * 2);
	//std::cout << "velY: " << velY << " - " << "yPosition: " << yPosition << std::endl;
	//float xPosition = getPosition().x + velX * dt.asSeconds();

	//setPosition(xPosition, yPosition);
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping)
	{
		isJumping = true;
		speed = jumpF / mass;
	}

	if (isJumping){
	
		Jump(dt.asSeconds());

		if (onGround)
			isJumping = false;
	}
*/


//	movement.y += movement.y + gravity;

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

void Player::GetLayers()
{
	if (layers.size() > 0)
	{
		for (auto layer = layers.begin(); layer != layers.end(); ++layer)
		{
			if (!(layer->name == "Coll"))
				continue;

			collisionObjects = layer->objects;
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
						inAir = 0.f;
						setPosition({ getPosition().x, getPosition().y - area.height });
						//std::cout << "Down side crash" << std::endl;
					}
					else
					{
						onGround = false;

						// Up side crash
						setPosition({ getPosition().x, getPosition().y + area.height });
						//std::cout << "Up side crash" << std::endl;
					}
				}
				else if (area.width < area.height)
				{
					if (area.contains({ getPosition().x + getGlobalBounds().width - 1.f, area.top + 1.f }))
					{
						//Right side crash
						onGround = false;
						setPosition({ getPosition().x - area.width, getPosition().y });
						std::cout << "Right side crash" << std::endl;
					}
					else
					{
						onGround = false;
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
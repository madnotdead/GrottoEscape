//////////////////////////////////////////////////////////////////////////
//
// File: CollisionDetection.cpp
//
// Desc: Functions that performs collision detection.
//
// Author: Bertoa Nicolas - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cfloat>

#include "CollisionDetection.h"

namespace Game
{
	Rectangle::Rectangle(const sf::Vector2f& position, const uint32_t width, const uint32_t height)
		: mPosition(position)
		, mWidth(width)
		, mHeight(height)
	{
	
	}

	// Check collision between bullets and ship and returns the number of collisions.
	// Also it deactivate (by reposition) the bullets that collided.
	uint8_t BulletsShipCollision(const uint8_t numberOfBullets, sf::Vector2f * const bulletPositions, const uint32_t bulletWidth,
		const uint32_t bulletHeight, sf::Vector2f * const shipPosition, const uint32_t shipWidth, const uint32_t shipHeight)
	{
		assert(bulletPositions && "BulletsShipCollision: NULL pointer");
		assert(shipPosition && "BulletsShipCollision: NULL pointer");
		
		uint8_t numberOfCollisions = 0;
		const float shipUpLeftX = shipPosition->x;
		const float shipUpLeftY = shipPosition->y;
		const float shipUpRightX = shipUpLeftX + shipWidth;
		const float shipDownLeftY = shipUpLeftY + shipHeight;
		const float calculation1 = shipUpLeftX - bulletWidth;
		const float calculation2 = shipUpLeftY - bulletHeight;
		float bulletX = 0.0f;
		float bulletY = 0.0f;
		for(uint8_t i = 0; i < numberOfBullets; ++i)
		{
			bulletX = bulletPositions[i].x;
			bulletY = bulletPositions[i].y;
			
			// If there was a collision, we reposition the bullet and increment the count of collisions
			if(calculation1 < bulletX && calculation2 < bulletY && bulletX < shipUpRightX && bulletY < shipDownLeftY)
			{
				bulletPositions[i].x = FLT_MAX;
				bulletPositions[i].y = FLT_MAX;

				numberOfCollisions++;
			}
		}

		return numberOfCollisions;
	}

	// Check if two rectangles are overlapped or not.
	bool CheckRectanglesCollision(const Rectangle& rectangle1, const Rectangle& rectangle2)
	{
		const float rectangle2UpLeftX = rectangle2.mPosition.x;
		const float rectangle2UpLeftY = rectangle2.mPosition.y;
		const float rectangle2UpRightX = rectangle2UpLeftX + rectangle2.mWidth;
		const float rectangle2DownLeftY = rectangle2UpLeftY + rectangle2.mHeight;
		const float calculation1 = rectangle2UpLeftX - rectangle1.mWidth;
		const float calculation2 = rectangle2UpLeftY - rectangle1.mHeight;

		return calculation1 < rectangle1.mPosition.x && calculation2 < rectangle1.mPosition.y && 
			rectangle1.mPosition.x < rectangle2UpRightX && rectangle1.mPosition.y < rectangle2DownLeftY;
	}
}
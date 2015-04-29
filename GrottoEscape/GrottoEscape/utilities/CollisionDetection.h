//////////////////////////////////////////////////////////////////////////
//
// File: CollisionDetection.h
//
// Desc: Functions that performs collision detection.
//
// Author: Bertoa Nicolas - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "../utilities/Types.h"

#include <SFML/System/Vector2.hpp>

namespace CollisionDetection
{
	class Rectangle
	{
	public:
		Rectangle(const sf::Vector2f& position, const uint32_t width, const uint32_t height);

	public:
		sf::Vector2f mPosition;
		uint32_t mWidth;
		uint32_t mHeight;
	};

	// Check if two rectangles are overlapped or not.
	bool CheckRectanglesCollision(const Rectangle& rectangle1, const Rectangle& rectangle2);
}

#endif // COLLISION_DETECTION_H
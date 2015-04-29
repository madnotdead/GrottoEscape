#include <cassert>
#include "../utilities/Types.h"

#include "ImageManager.h"

namespace Manager
{
	sf::Texture* ImageManager::load(const std::string& strId) 
	{
		sf::Texture *image = new sf::Texture;
		if(!image->loadFromFile(strId)) 
		{
			delete image;
			image = 0;
		}

		return image;
	}
}

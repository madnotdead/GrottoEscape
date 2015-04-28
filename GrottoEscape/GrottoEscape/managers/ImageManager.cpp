#include <cassert>
#include "../utilities/Types.h"

#include "ImageManager.h"

namespace Game
{
	sf::Texture* ImageManager::load(const std::string& strId) 
	{
		sf::Texture *image = new sf::Texture;
		if(!image->LoadFromFile(strId)) 
		{
			delete image;
			image = 0;
		}

		return image;
	}
}

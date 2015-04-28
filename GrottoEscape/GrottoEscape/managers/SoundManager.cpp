#include "SoundManager.h"

#include <cassert>

#include "../utilities/Types.h"

namespace Game
{
	sf::SoundBuffer* SoundManager::load(const std::string& strId) 
	{
		sf::SoundBuffer *soundBuffer = new sf::SoundBuffer;
		if(!soundBuffer->LoadFromFile(strId)) 
		{
			delete soundBuffer;
			soundBuffer = 0;
		}

		return soundBuffer;
	}
}

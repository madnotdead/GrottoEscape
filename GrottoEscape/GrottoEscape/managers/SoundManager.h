#ifndef GAME_SOUND_MANAGER_H
#define GAME_SOUND_MANAGER_H

#include <string>

#include <SFML/Audio/SoundBuffer.hpp>

#include "ResourceManager.h"

namespace Manager
{
	class SoundManager : public ResourceManager<sf::SoundBuffer> 
	{
	protected:
		sf::SoundBuffer* load(const std::string& strId);
	};
}

#endif // GAME_SOUND_MANAGER_H

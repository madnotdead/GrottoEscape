#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}


sf::SoundBuffer* SoundManager::load(const std::string& strId)
{
	sf::SoundBuffer *soundBuffer = new sf::SoundBuffer;
	if (!soundBuffer->loadFromFile(strId))
	{
		delete soundBuffer;
		soundBuffer = 0;
	}

	return soundBuffer;
}
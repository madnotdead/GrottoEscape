#pragma once
class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	sf::SoundBuffer* load(const std::string& strId);
};


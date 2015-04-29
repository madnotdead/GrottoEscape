#pragma once
class GameManager
{

private:
	Manager::ImageManager mImageManager;
	Manager::SoundManager mSoundManager;
public:
	GameManager();
	~GameManager();
	inline Manager::ImageManager& GetImageManager();
	inline Manager::SoundManager& GetSoundManager();


	Manager::ImageManager& GameManager::GetImageManager()
	{
		return mImageManager;
	}

	Manager::SoundManager& GameManager::GetSoundManager()
	{
		return mSoundManager;
	}
};


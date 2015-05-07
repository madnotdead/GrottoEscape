#pragma once
#include "stdafx.h"
#include <tmx\MapLayer.h>
#include <tmx\MapLoader.h>
#include "AnimatedSprite.h"
#include "Item.h"
#include "Slime.h"
#include "ImageManager.h"
#include "tmx\MapLayer.h"
#include "FireMonster.h"
#include "HealthBar.h"
#include "Player.h"

enum GameStates{
	INTRO,
	PLAYING,
	PAUSED
};
class Game
{

private:
	sf::RenderWindow *wnd;
	static const sf::Time	TimePerFrame;
	std::vector<Item*> items; 
	std::vector<Slime*> slimes;
	std::vector<tmx::MapLayer> layers;
	std::vector<FireMonster*> fireMonsters;
	HealthBar* hBar;
	Player* mPlayer;
	tmx::MapLoader* map;
	GameStates currentState;
	GameStates oldState;
	sf::SoundBuffer *mainThemeBuffer;
	sf::Sound *main;
	sf::SoundBuffer *pauseBuffer;
	sf::Sound *pauseSound;
	sf::Texture introTexture;
	sf::Sprite introImage; //placeholder for intro screen
	sf::View view;
public:

	float getFPS(const sf::Time& time);
	Game(int width, int height);
	void MainLoop();
	void Init();
	void HandleInput();
	void Draw();
	void HandleCollision();

	~Game();
	void GenerateItems(std::vector<tmx::MapLayer> layers);
	ImageManager imageManager;
};


#pragma once
#include "stdafx.h"
#include <tmx\MapLayer.h>
#include "AnimatedSprite.h"
#include "Item.h"
#include "Slime.h"
#include "ImageManager.h"
#include "tmx\MapLayer.h"
class Game
{

private:
	sf::RenderWindow *wnd;
	static const sf::Time	TimePerFrame;
	std::vector<Item*> items; 
	std::vector<Slime*> slimes;
	std::vector<tmx::MapLayer> layers;
public:

	float getFPS(const sf::Time& time);
	Game(int width, int height);
	void MainLoop();
	void Init();
	void HandleInput();
	~Game();
	void GenerateItems(std::vector<tmx::MapLayer> layers);
	ImageManager imageManager;
};


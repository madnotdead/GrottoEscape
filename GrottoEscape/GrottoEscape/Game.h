#pragma once
#include "stdafx.h"
#include <tmx\MapLayer.h>
#include "AnimatedSprite.h"
#include "Item.h"
class Game
{

private:
	sf::RenderWindow *wnd;
	static const sf::Time	TimePerFrame;
	std::vector<Item*> items; 
public:

	float getFPS(const sf::Time& time);
	Game(int width, int height);
	void MainLoop();
	void Init();
	void HandleInput();
	~Game();
	void GenerateItems(std::vector<tmx::MapLayer> layers);
};


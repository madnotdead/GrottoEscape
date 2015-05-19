#pragma once
#include "GameState.h"
#include "GameManager.h"
#include "stdafx.h"
class GameStatePlay :
	public GameState
{
private:

	sf::View view;
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
public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
	GameStatePlay(GameManager* game);

	float getFPS(const sf::Time& time);
	//Game(int width, int height);
	//void MainLoop();
	//void Init();
	//void HandleInput();
	void Draw();
	void HandleCollision();

	//~GameStatePlay();
	void GenerateItems(std::vector<tmx::MapLayer> layers);
};


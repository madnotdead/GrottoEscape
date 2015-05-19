#pragma once
#include "GameState.h"
class GameStateIntro : public GameState
{
private:

	sf::View view;

public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	GameStateIntro(GameManager* game);
};


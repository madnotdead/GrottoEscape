#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <stack>
#include <SFML/Graphics.hpp>

class GameState;

class GameManager
{
public:

	std::stack<GameState*> states;

	sf::RenderWindow window;

	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();

	void gameLoop();

	GameManager();
	~GameManager();
};

#endif /* GAMEMANAGER_HPP */
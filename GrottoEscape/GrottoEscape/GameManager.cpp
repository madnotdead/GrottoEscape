#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "GameManager.h"
#include "GameState.h"

void GameManager::pushState(GameState* state)
{
	this->states.push(state);

	return;
}

void GameManager::popState()
{
	delete this->states.top();
	this->states.pop();

	return;
}

void GameManager::changeState(GameState* state)
{
	if (!this->states.empty())
		popState();
	pushState(state);

	return;
}

GameState* GameManager::peekState()
{
	if (this->states.empty()) return nullptr;
	return this->states.top();
}

void GameManager::gameLoop()
{
	sf::Clock clock;

	while (this->window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (peekState() == nullptr) continue;
		peekState()->handleInput();
		peekState()->update(dt);
		this->window.clear(sf::Color::Black);
		peekState()->draw(dt);
		this->window.display();
	}
}

GameManager::GameManager()
{
	this->window.create(sf::VideoMode(800, 600), "Grotto Escape");
	this->window.setFramerateLimit(60);
}

GameManager::~GameManager()
{
	while (!this->states.empty()) popState();
}
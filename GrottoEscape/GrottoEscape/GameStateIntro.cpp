#include "stdafx.h"
#include "GameStateIntro.h"


#include <SFML/Graphics.hpp>

#include "GameState.h"
//#include "game_state_editor.hpp"
#include "GameStateIntro.h"
#include "GameStatePlay.h"
GameStateIntro::GameStateIntro(GameManager* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
}

void GameStateIntro::draw(const float dt)
{
	this->game->window.setView(this->view);

	this->game->window.clear(sf::Color::Cyan);
	//this->game->window.draw(this->game->background);

	return;
}

void GameStateIntro::update(const float dt)
{
}

void GameStateIntro::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
		{
			game->window.close();
			break;
		}
			/* Resize the window */
		case sf::Event::Resized:
		{
			this->view.setSize(event.size.width, event.size.height);
			/*this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0)));
			this->game->background.setScale(
				float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
				float(event.size.height) / float(this->game->background.getTexture()->getSize().y));*/
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape) this->game->window.close();
			break;

			if (event.key.code == sf::Keyboard::Space)
				this->game->pushState(new GameStatePlay(this->game));
		}
		default: break;
		}
	}

	return;
}


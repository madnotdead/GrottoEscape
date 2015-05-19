#include "stdafx.h"
#include "GameStatePlay.h"

GameStatePlay::GameStatePlay(GameManager* game)
{
	this->game = game;
	//sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	//this->view.setSize(pos);
	//pos *= 0.5f;
	//this->view.setCenter(pos);

	currentState = GameStates::INTRO;

	pauseBuffer = new sf::SoundBuffer;
	if (!pauseBuffer->loadFromFile("audio/pause.wav"))
	{
		delete pauseBuffer;
		pauseBuffer = 0;
	}

	pauseSound = new sf::Sound(*pauseBuffer);
	pauseSound->setVolume(100.0f);

	//sf::Clock FPSClock;
	map = new tmx::MapLoader("maps/");
	map->Load("map_test.tmx");
	//sf::Clock frameClock;
	//sf::Time frameTime;
	//Player* mPlayer = new Player(wnd,ml.GetLayers());
	//mPlayer = new Player(wnd, ml.GetLayers());
	//sf::View view;
	view.reset(sf::FloatRect(0, 0, 800 / 2, 600 / 2));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	sf::Vector2f viewPosition(800 / 2, 600 / 2);
	view.zoom(0.6f);

	//sf::Clock clock;
	//sf::Time timeSinceLastUpdate = sf::Time::Zero;


	//sf::SoundBuffer *mainThemeBuffer;
	mainThemeBuffer = new sf::SoundBuffer();

	if (!mainThemeBuffer->loadFromFile("audio/main.wav"))
	{
		std::cout << "Failed to load mainTheme.wav" << std::endl;
		delete mainThemeBuffer;
		mainThemeBuffer = 0;
	}

	main = new sf::Sound(*mainThemeBuffer);
	main->setLoop(true);
	main->setVolume(75.0f);
	//main->play();

	layers = map->GetLayers();

	hBar = new HealthBar(view.getCenter());
}


void GameStatePlay::draw(const float dt)
{
	this->game->window.setView(this->view);

	this->game->window.clear(sf::Color::Cyan);
	//this->game->window.draw(this->game->background);

	return;
}

void GameStatePlay::update(const float dt)
{
}

void GameStatePlay::handleInput()
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
		}
		default: break;
		}
	}

	return;
}

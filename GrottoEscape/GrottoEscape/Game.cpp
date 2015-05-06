#include "stdafx.h"
#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game(int width, int height) 
{
	wnd = new sf::RenderWindow(sf::VideoMode(width, height), "Grotto Escape");
	//wnd->setVerticalSyncEnabled(true);
	wnd->setFramerateLimit(60);
	currentState = GameStates::INTRO;

	pauseBuffer = new sf::SoundBuffer;
	if (!pauseBuffer->loadFromFile("audio/pause.wav"))
	{
		delete pauseBuffer;
		pauseBuffer = 0;
	}

	pauseSound = new sf::Sound(*pauseBuffer);
	pauseSound->setVolume(100.0f);

	if (!introTexture.loadFromFile("img/intro.png"))
	{
		std::cout << "Couldnt load intro.png" << std::endl;
	}
	
	introImage.setTexture(introTexture);
	introImage.setPosition(0, 0);
}

Game::~Game()
{
}

void Game::HandleInput()
{
	sf::Event evento;

	while (wnd->pollEvent(evento))
	{
		switch (evento.type)
		{
			case sf::Event::EventType::Closed://Evento para capturar el cierre de la ventana
			{
				wnd->close();//Cierro la ventana
			}
			break;

			case sf::Event::KeyPressed:
				{

					if (evento.key.code == sf::Keyboard::Space)
					{
						if (currentState == GameStates::INTRO)
						{
							currentState = GameStates::PLAYING;
							GenerateItems(layers);
							main->play();
						}
							
					}

					if (evento.key.code == sf::Keyboard::Escape)
					{
						currentState = GameStates::INTRO;
						main->stop();
					}
						

					if (evento.key.code == sf::Keyboard::R)
					{
						if (currentState == GameStates::PLAYING)
						{
							GenerateItems(layers);
							main->stop();
							main->play();
						}					
					}
					
					if (evento.key.code == sf::Keyboard::P)
					{
						main->pause();
						pauseSound->play();
					
						if (oldState != currentState)
							oldState = currentState;

						if (currentState == GameStates::PLAYING)
							currentState = GameStates::PAUSED;
						else
						{
							currentState = GameStates::PLAYING;
							main->play();
						}
					}

				}
				break;

		default:	
			break;
		}

	}
}

float Game::getFPS(const sf::Time& time) {
	return (1000000.0f / time.asMicroseconds());
}

void Game::MainLoop()
{

	sf::Clock FPSClock;
	map = new tmx::MapLoader("maps/");
	map->Load("map_test.tmx");
	sf::Clock frameClock;
	sf::Time frameTime;
	//Player* mPlayer = new Player(wnd,ml.GetLayers());
	//mPlayer = new Player(wnd, ml.GetLayers());
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 800/2, 600/2));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	sf::Vector2f viewPosition(800 / 2, 600 / 2);
	view.zoom(0.6f);

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;	


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



	

	while(wnd->isOpen())
	{


		if (currentState == GameStates::PLAYING)
		{

			sf::Time elapsedTime = clock.restart();
			timeSinceLastUpdate += elapsedTime;
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;

				//Update logic
				mPlayer->Update(TimePerFrame);

				hBar->Update(TimePerFrame);

				for (size_t i = 0; i < slimes.size(); i++)
					slimes.at(i)->Update(TimePerFrame);

				for (size_t i = 0; i < items.size(); i++)
					items.at(i)->Update(TimePerFrame);

				for (size_t i = 0; i < fireMonsters.size(); i++)
					fireMonsters.at(i)->Update(TimePerFrame);

			}
	
			//Collision Detection

			HandleCollision();

			hBar->SetHealthState(mPlayer->GetHealth());



			if (mPlayer->getPosition().x > 120 && mPlayer->getPosition().x < 1160)
				view.setCenter(mPlayer->getPosition().x, mPlayer->getPosition().y - 50);
			else
			{
				if (mPlayer->getPosition().x < 1160)
					view.setCenter(120, mPlayer->getPosition().y - 50);
				else
					view.setCenter(1160, mPlayer->getPosition().y - 50);
			}

			hBar->setPosition(view.getCenter().x - 105, view.getCenter().y - 75);

		

			if (mPlayer->Succeded() || mPlayer->Dead())
				main->stop();
		}
		else
		{
			timeSinceLastUpdate = sf::Time::Zero;
			clock.restart();
		}
			
		wnd->setView(view);
		HandleInput();
		
		Draw();

	}
}

void Game::GenerateItems(std::vector<tmx::MapLayer> layers)
{
	int itemType;
	if (layers.size() <= 0)
		return;

	std::cout << "Generating level..." << std::endl;

	items.clear();
	slimes.clear();
	fireMonsters.clear();
	hBar->SetActive(true);
	
	if (mPlayer)
		delete mPlayer;

	for (auto layer = layers.begin(); layer != layers.end(); ++layer)
	{
		for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
		{
			if (layer->name == "Items")
			{
				if (!object->Visible())
					continue;
				
				itemType = atoi(object->GetPropertyString("ItemType").c_str());
				items.push_back(new Item(object->GetPosition(),(ItemType)itemType));
			}

			if (layer->name == "Enemies")
			{
				if (object->GetType() == "S")
					slimes.push_back(new Slime(layers, object->GetName()));

				if (object->GetType() == "F")
					fireMonsters.push_back(new FireMonster(object->GetPosition(), layers));
			}

			if (layer->name == "Player")
			{
				mPlayer = new Player(wnd, layers);
			}
		}
	}
}

void Game::Draw()
{
	//Draw in screen
	wnd->clear();

	if (currentState != GameStates::INTRO)
	{
		//Draw tiles
		wnd->draw(*map);

		//Draw player
		wnd->draw(*mPlayer);

		if (hBar->IsActive())
			wnd->draw(*hBar);

		for (size_t i = 0; i < fireMonsters.size(); i++)
		{
			wnd->draw(*fireMonsters.at(i));
		}

		//Draw active slimes
		for (size_t i = 0; i < slimes.size(); i++)
		{
			if (slimes.at(i)->getActive())
				wnd->draw(*slimes.at(i));
		}

		//Draw active bullets
		for (size_t i = 0; i < mPlayer->bullets.size(); i++)
		{
			if (mPlayer->bullets.at(i)->isActive())
				wnd->draw(*mPlayer->bullets.at(i));
		}

		//Draw active items
		for (size_t i = 0; i < items.size(); i++)
		{
			if (items.at(i)->IsActive())
				wnd->draw(*items.at(i));
		}
	}
	else
		wnd->draw(introImage);

	wnd->display();
}

void Game::HandleCollision()
{
	for (size_t i = 0; i < fireMonsters.size(); i++)
	{
		if (fireMonsters.at(i)->getGlobalBounds().intersects(mPlayer->getGlobalBounds()))
			mPlayer->Hit(2);
	}

	sf::FloatRect itemAreaCollision;
	for (size_t i = 0; i < items.size(); i++)
	{
		if (mPlayer->getGlobalBounds().intersects(items.at(i)->getGlobalBounds(), itemAreaCollision))
		{
			if (items.at(i)->Collected())
				continue;

			if (itemAreaCollision.width > 10)
				mPlayer->HandleItemCollision(items.at(i));
		}
	}


	for (size_t i = 0; i < slimes.size(); i++)
	{
		if (!slimes.at(i)->getActive())
			continue;

		if (mPlayer->getGlobalBounds().intersects(slimes.at(i)->getGlobalBounds()))
			mPlayer->Hit(1);
	}

	for (size_t i = 0; i < mPlayer->bullets.size(); i++)
	{
		if (!mPlayer->bullets.at(i)->isActive())
			continue;

		sf::FloatRect areaCollision;

		for (size_t j = 0; j < slimes.size(); j++)
		{
			if (mPlayer->bullets.at(i)->getGlobalBounds().intersects(slimes.at(j)->getGlobalBounds(), areaCollision) && slimes.at(j)->getActive())
			{
				//hack to avoid bullet collision with sprites's transparent area
				if (areaCollision.width >= 10)
				{
					slimes.at(j)->Die();
					mPlayer->bullets.at(i)->SetActive(false);
				}
			}
		}
	}

}
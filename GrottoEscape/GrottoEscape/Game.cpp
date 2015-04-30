#include "stdafx.h"
#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game(int width, int height) 
{
	wnd = new sf::RenderWindow(sf::VideoMode(width, height), "Grotto Escape");
	//wnd->setVerticalSyncEnabled(true);
	wnd->setFramerateLimit(60);
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
		case sf::Event::EventType::MouseButtonPressed://Evento para capturar el click del mouse
		{
			//sf::Vector2i pos = sf::Mouse::getPosition(//Obtengo la posicion del mouse en la ventana al momento del click

			//if (tablero.hayFichaElegida())//Compruebo si existe una ficha elegida, si existe se realiza el movimiento
			//	tablero.hacerMovimiento(pos.x, pos.y);//Realizo el movimiento de la ficha seleccionada
			//else
			//	tablero.elegirFicha(pos.x, pos.y);//Elijo la ficha donde se realizo el click
		}
			break;

		case sf::Event::EventType::Closed://Evento para capturar el cierre de la ventana
		{
			wnd->close();//Cierro la ventana
		}
			break;

		case sf::Event::KeyPressed:
			{
				if (evento.key.code == sf::Keyboard::R)
				{
					GenerateItems(layers);
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
	tmx::MapLoader ml("maps/");
	ml.Load("map_test.tmx");
	sf::Clock frameClock;
	sf::Time frameTime;
	Player* mPlayer = new Player(wnd,ml.GetLayers());
	Slime* mSlime1 = new Slime(ml.GetLayers(),"Slime1");
	Slime* mSlime2 = new Slime(ml.GetLayers(), "Slime2");
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 800/2, 600/2));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	sf::Vector2f viewPosition(800 / 2, 600 / 2);
	view.zoom(0.6f);

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;	


	sf::SoundBuffer *mainThemeBuffer;
	mainThemeBuffer = new sf::SoundBuffer();

	if (!mainThemeBuffer->loadFromFile("audio/main.wav"))
	{
		std::cout << "Failed to load mainTheme.wav" << std::endl;
		delete mainThemeBuffer;
		mainThemeBuffer = 0;
	}

	sf::Sound *main = new sf::Sound(*mainThemeBuffer);
	main->setLoop(true);
	main->setVolume(100.0f);
	//main->play();
	imageManager.AddResourceDirectoy("img/");
	layers = ml.GetLayers();
	GenerateItems(layers);

	while(wnd->isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			//Update logic
			mPlayer->Update(TimePerFrame);

			for (size_t i = 0; i < slimes.size(); i++)
				slimes.at(i)->Update(TimePerFrame);
			
			for (size_t i = 0; i < items.size(); i++)
				items.at(i)->Update(TimePerFrame);

			//Collision Detection
			for (size_t i = 0; i < items.size(); i++)
			{
				if (mPlayer->getGlobalBounds().intersects(items.at(i)->getGlobalBounds()))
				{
					if (!items.at(i)->IsActive())
						continue;

					mPlayer->HandleItemCollision(items.at(i));
				}
			}
			

			for (size_t i = 0; i < slimes.size(); i++)
			{
				if (!slimes.at(i)->getActive())
					continue;

				if (mPlayer->getGlobalBounds().intersects(slimes.at(i)->getGlobalBounds()))
					mPlayer->Hit();
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
							slimes.at(j)->SetActive(false);
							mPlayer->bullets.at(i)->SetActive(false);
						}
					}
				}
			}

			
		}

		HandleInput();

		if (mPlayer->getPosition().x > 120 && mPlayer->getPosition().x < 1160)
			view.setCenter(mPlayer->getPosition().x, mPlayer->getPosition().y - 50);
		else
		{
			if (mPlayer->getPosition().x < 1160)
				view.setCenter(120, mPlayer->getPosition().y - 50);
			else
				view.setCenter(1160, mPlayer->getPosition().y - 50);
		}
			
		//1160
		wnd->setView(view);

		//Draw in screen
		wnd->clear();
		
		//Draw tiles
		wnd->draw(ml);
		
		//Draw player
		wnd->draw(*mPlayer);
		
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

		wnd->display();
	}
}


void Game::GenerateItems(std::vector<tmx::MapLayer> layers)
{
	int itemType;
	if (layers.size() <= 0)
		return;
	
	items.clear();
	slimes.clear();

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
			}
			//if (layer->name == "Player")
			//{
			//	//Create Enemies
			//}

			//if (layer->name == "Waypoints")
			//{
			//	//Asigno los waypoints a los enemigos
			//}
		}
	}
}


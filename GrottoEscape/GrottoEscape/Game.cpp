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
	while(wnd->isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			mPlayer->Loop(TimePerFrame);
			mSlime1->Update(TimePerFrame);
			mSlime2->Update(TimePerFrame);


			if (mPlayer->getGlobalBounds().intersects(mSlime1->getGlobalBounds()))
				mPlayer->Hit();

			if (mPlayer->getGlobalBounds().intersects(mSlime2->getGlobalBounds()))
				mPlayer->Hit();

			for (size_t i = 0; i < mPlayer->bullets.size(); i++)
			{
				if (!mPlayer->bullets.at(i)->isActive())
					continue;


				if (mPlayer->bullets.at(i)->getGlobalBounds().intersects(mSlime1->getGlobalBounds()))
				{
					mSlime1->SetActive(false);
					mPlayer->bullets.at(i)->SetActive(false);
				}


				if (mPlayer->bullets.at(i)->getGlobalBounds().intersects(mSlime2->getGlobalBounds()))
				{
					mSlime2->SetActive(false);
					mPlayer->bullets.at(i)->SetActive(false);
				}

			}
		}


		//if (mPlayer->getPosition().x > 50 ){
			//viewPosition.x = mPlayer->getPosition().x + 100;
			//viewPosition.y = mPlayer->getPosition().y - 50;
		//}
		//else
		//{
		//	viewPosition.x = mPlayer->getPosition().x;
		//	viewPosition.y = mPlayer->getPosition().y ;
		//}
		//	

		//else
		//	viewPosition.x = mPlayer->getPosition().x;

		//	viewPosition.y = mPlayer->getPosition().y;
		//}

		

		view.setCenter(mPlayer->getPosition().x, mPlayer->getPosition().y - 50);
		wnd->setView(view);
		wnd->clear();
		wnd->draw(ml);
		wnd->draw(*mPlayer);
		
		if (mSlime1->getActive())
			wnd->draw(*mSlime1);

		if (mSlime2->getActive())
			wnd->draw(*mSlime2);



		for (size_t i = 0; i < mPlayer->bullets.size(); i++)
		{
			if (mPlayer->bullets.at(i)->isActive())
				wnd->draw(*mPlayer->bullets.at(i));
		}

		

		wnd->display();
	}
}

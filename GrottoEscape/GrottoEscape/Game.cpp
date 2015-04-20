#include "stdafx.h"
#include "Game.h"


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

	sf::View view;
	view.reset(sf::FloatRect(0, 0, 800/2, 600/2));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	sf::Vector2f viewPosition(800 / 2, 600 / 2);
	//view.zoom(0.8f);
	while(wnd->isOpen())
	{
		frameTime = frameClock.restart();
		
		mPlayer->Loop(frameTime);

		//if (mPlayer->getPosition().x + 10 < 400)
		//	viewPosition.x = mPlayer->getPosition().x + 100;
		//else
			//viewPosition.x = mPlayer->getPosition().x;

		//	viewPosition.y = mPlayer->getPosition().y;
		//}
		//	
		//else
		//	viewPosition.x = 800 / 2;

		//view.setCenter(viewPosition);
		//wnd->setView(view);
		wnd->clear();
		wnd->draw(ml);
		wnd->draw(*mPlayer);
		wnd->display();

		//float fps = getFPS(FPSClock.restart());

		//std::cout << getFPS(FPSClock.restart()) << std::endl;
	}
}
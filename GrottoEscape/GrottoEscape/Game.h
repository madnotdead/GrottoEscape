#pragma once
class Game
{

private:
	sf::RenderWindow *wnd;
public:
	Game(int width, int height);
	void MainLoop();
	void Init();
	void HandleInput();
	~Game();
};


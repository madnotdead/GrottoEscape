#pragma once
class Game
{

private:
	sf::RenderWindow *wnd;
public:

	float getFPS(const sf::Time& time);
	Game(int width, int height);
	void MainLoop();
	void Init();
	void HandleInput();
	~Game();
};


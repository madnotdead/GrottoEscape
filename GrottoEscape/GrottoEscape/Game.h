#pragma once
class Game
{

private:
	sf::RenderWindow *wnd;
	static const sf::Time	TimePerFrame;
public:

	float getFPS(const sf::Time& time);
	Game(int width, int height);
	void MainLoop();
	void Init();
	void HandleInput();
	~Game();
};


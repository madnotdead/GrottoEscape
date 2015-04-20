#pragma once
class Game
{

private:
	sf::RenderWindow *wnd;
public:
	static const sf::Time	TimePerFrame;
	float getFPS(const sf::Time& time);
	Game(int width, int height);
	void MainLoop();
	void Init();
	void HandleInput();
	void Draw();
	~Game();
};


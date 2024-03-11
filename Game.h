#pragma once
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

class Game
{
private:
	RenderWindow window;
	vector<Button> buttons;
	RectangleShape screen;
	Texture screenT;
	RectangleShape frame;
	Texture frameT;
	int wolfPos = 0; //0 left up 1 left down 2 right up 3 right down
	void processEvents();
	void render();
	void update();
public:
	Game();
	void run();
};


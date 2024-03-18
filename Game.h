#pragma once
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
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

	vector<RectangleShape> eggs;
	Texture eggT;

	bool chickens[4][6]{ 0 };

	int mistakes = 0;
	int wolfPos = 0; //0 left up 1 left down 2 right up 3 right down

	const Time TimePerFrame = seconds(1.f / 10.f);
	thread th;
	int static value;

	Text score;
	Font scoreF;
	int spawnCount = 0;

	int level = 1;
	int speed = 10;
	int spawnRate = 5;
	int caughtEggs = 0;
	int coordsEggs[4][6]{ {} };

	void processEvents();
	void render();
	void update();

	void static incrementer();
	void createRandomEgg();
	void showInfoEggs();
	void moveEggs();
	void reset();
public:
	Game();
	~Game();
	void run();
};


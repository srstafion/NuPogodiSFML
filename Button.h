#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Button
{
private:
	CircleShape button;
	bool status = false;
public:
	Button(Vector2f startPos);
	void changeStatus();
	bool getStatus();
	Vector2f getPosition();
	CircleShape& getShape();
};


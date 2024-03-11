#include "Button.h"

Button::Button(Vector2f startPos)
{
	button.setRadius(30);
	button.setFillColor(Color::Blue);
	button.setPosition(startPos);
}

void Button::changeStatus()
{
	status = !status;
	if(status) button.setFillColor(Color(0,0,0,150));
	else button.setFillColor(Color::Blue);
}

bool Button::getStatus()
{
	return status;
}

Vector2f Button::getPosition()
{
	return button.getPosition();
}

CircleShape& Button::getShape()
{
	return button;
}

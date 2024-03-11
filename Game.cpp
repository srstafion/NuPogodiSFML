#include "Game.h"
#include <iostream>

void Game::processEvents()
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
        if (event.type == Event::MouseButtonPressed
            || event.type == Event::MouseButtonReleased 
            && event.mouseButton.button == Mouse::Left) {
            Vector2i mousePos = Mouse::getPosition(window);
            int count = 0;
            for (auto& i : buttons) {
                if (i.getShape().getGlobalBounds().contains(float(mousePos.x), float(mousePos.y))) {
                    i.changeStatus();
                    wolfPos = count;
                }
                count++;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            buttons[0].changeStatus();
            wolfPos = 0;
            cout << wolfPos;
        }
        else if (Keyboard::isKeyPressed(Keyboard::C)) {
            buttons[1].changeStatus();
            wolfPos = 1;
            cout << wolfPos;
        }
        else if (Keyboard::isKeyPressed(Keyboard::K)) {
            buttons[2].changeStatus();
            wolfPos = 2;
            cout << wolfPos;
        }
        else if (Keyboard::isKeyPressed(Keyboard::M)) {
            buttons[3].changeStatus();
            wolfPos = 3;
            cout << wolfPos;
        }
    }
}

void Game::render()
{
    window.clear();
    window.draw(frame);
    window.draw(screen);
    for (auto i : buttons) {
        window.draw(i.getShape());
    }
    window.display();
}

void Game::update()
{
    switch (wolfPos) {
    case 0:
        screenT.loadFromFile("./Textures/LU.png");
        screen.setTexture(&screenT);
        break;
    case 1:
        screenT.loadFromFile("./Textures/LD.png");
        screen.setTexture(&screenT);
        break;
    case 2:
        screenT.loadFromFile("./Textures/RU.png");
        screen.setTexture(&screenT);
        break;
    case 3:
        screenT.loadFromFile("./Textures/RD.png");
        screen.setTexture(&screenT);
        break;
    }
}

Game::Game()
    :window(VideoMode(1200, 690), "Nu Pogodi!")
{
    screen.setSize(Vector2f(650, 420));
    screenT.loadFromFile("./Textures/LU.png");
    screen.setTexture(&screenT);
    screen.setPosition(275, 130);
    frame.setSize(Vector2f(1200, 690));
    frameT.loadFromFile("./Textures/frame.png");
    frame.setTexture(&frameT);
    buttons.push_back(Button(Vector2f(90, 440)));
    buttons.push_back(Button(Vector2f(90, 560)));
    buttons.push_back(Button(Vector2f(1045, 440)));
    buttons.push_back(Button(Vector2f(1045, 560)));
}

void Game::run()
{
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

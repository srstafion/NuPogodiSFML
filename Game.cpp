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
    for (int i = 0, count = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            if (chickens[i][j] == true) window.draw(eggs[count]);
        }
        count++;
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
    if (value % spawnRate == 0) {
        spawnCount++;
        moveEggs();
        if (spawnCount >= spawnRate) {
            spawnCount = 0;
            createRandomEgg();
        }
        showInfoEggs();
    }
}

void Game::incrementer()
{
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(100));
        value++;
    }
}

Game::Game()
    :window(VideoMode(1200, 690), "Nu Pogodi!"),
    th(incrementer)
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

    eggT.loadFromFile("./Textures/egg.png");
    int posEggs[24][3] = { { 330, 265, 20 },
                           { 370, 275, 80 },
                           { 400, 300, 140 },
                           { 420, 325, 180 },
                           { 440, 350, 220 },
                           { 450, 510, 200 },

                           { 330, 365, 20 },
                           { 370, 375, 80 },
                           { 400, 400, 140 },
                           { 420, 425, 180 },
                           { 440, 450, 220 },
                           { 450, 510, 200 }, 

                           { 870, 293, 200 },
                           { 854, 290, 140 },
                           { 820, 288, 80 },
                           { 780, 302, 20 },
                           { 745, 345, -40 },
                           { 765, 510, 200 },

                           { 870, 393, 200 },
                           { 854, 390, 140 },
                           { 820, 388, 80 },
                           { 780, 402, 20 },
                           { 745, 445, -40 },
                           { 765, 510, 200 } };
    for (int i = 0; i < 25; i++) {
        RectangleShape shape;
        shape.setSize(Vector2f(26, 19));
        shape.setTexture(&eggT);
        shape.setPosition(Vector2f(posEggs[i][0], posEggs[i][1]));
        shape.rotate(posEggs[i][2]);
        eggs.push_back(shape);
    }
}

Game::~Game()
{
    th.join();
}

void Game::showInfoEggs()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            cout << chickens[i][j] << " ";
        }
        cout << " : ";
    }
    cout << endl;
}

void Game::createRandomEgg()
{
    chickens[rand() % 4][0] = true;
}

void Game::moveEggs()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 6; j > 0; j--) {
            swap(chickens[i][j], chickens[i][j - 1]);
        }
    }
}

void Game::run()
{
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

int Game::value = 0;

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
        }
        else if (Keyboard::isKeyPressed(Keyboard::C)) {
            buttons[1].changeStatus();
            wolfPos = 1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::K)) {
            buttons[2].changeStatus();
            wolfPos = 2;
        }
        else if (Keyboard::isKeyPressed(Keyboard::M)) {
            buttons[3].changeStatus();
            wolfPos = 3;
        }
    }
}

void Game::render()
{
    window.clear();
    window.draw(frame);
    window.draw(screen);

    for (auto el : buttons) {
        window.draw(el.getShape());
    }

    for (int i = 0, count = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            if (chickens[i][j]) {
                window.draw(eggs[count]);
            }
            count++;
        }
    }
    window.draw(score);
    window.display();
}

void Game::update()
{
    score.setString(to_string(caughtEggs));
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
    if (value >= speed) {
        spawnCount++;
        moveEggs();
        if (spawnCount >= spawnRate) {
            spawnCount = 0;
            createRandomEgg();
        }
        value = 0;
        /*showInfoEggs();*/
        if ((caughtEggs % (10 * level)) == 0 && caughtEggs > 0) {
            if (spawnRate > 1) {
                spawnRate--;
                level++;
                cout << spawnRate << " : " << level << endl;
            }
        }
        if ((caughtEggs % (20 * level)) == 0 && caughtEggs > 0) {
            if (speed > 4) speed--;
        }
        if (mistakes == 3) {
            window.close();
        }
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
    : window(sf::VideoMode(1200, 690), "Nu Pogodi!"),
    th(incrementer)
{
    scoreF.loadFromFile("Segment7Standard.otf");
    score.setFont(scoreF);
    score.setPosition(650, 140);
    score.setCharacterSize(70);
    score.setFillColor(Color::Black);

    frameT.loadFromFile("./Textures/frame.png");
    frame.setSize(sf::Vector2f(1200, 690));
    frame.setTexture(&frameT);

    screenT.loadFromFile("./Textures/lu.png");
    screen.setSize(sf::Vector2f(637, 410));
    screen.setPosition(sf::Vector2f(280, 138));
    screen.setTexture(&screenT);

    sf::Vector2f pos1(95, 440);
    sf::Vector2f pos2(95, 565);
    sf::Vector2f pos3(1045, 440);
    sf::Vector2f pos4(1045, 565);

    buttons.push_back(Button(pos1));
    buttons.push_back(Button(pos2));
    buttons.push_back(Button(pos3));
    buttons.push_back(Button(pos4));

    eggT.loadFromFile("./Textures/egg.png");

    int posEggs[24][3] = { {330, 265, 20},
                            {370, 275, 80},
                            {400, 300, 140},
                            {420, 325, 180},
                            {440, 350, 220},
                            {450, 510, 200}, // Óïàëî

                            {330, 365, 20},
                            {370, 375, 80},
                            {400, 400, 140},
                            {420, 425, 180},
                            {440, 450, 220},
                            {450, 510, 200}, // Óïàëî

                            {870, 293, 200},
                            {854, 290, 140},
                            {820, 288, 80},
                            {780, 302, 20},
                            {745, 345, -40},
                            {765, 510, 200}, // Óïàëî

                            {870, 393, 200},
                            {854, 390, 140},
                            {820, 388, 80},
                            {780, 402, 20},
                            {745, 445, -40},
                            {765, 510, 200}, // Óïàëî
    };

    for (int i = 0; i < 24; i++) {
        sf::RectangleShape shape;

        shape.setSize(sf::Vector2f(26, 19));
        shape.setTexture(&eggT);
        shape.setPosition(sf::Vector2f(posEggs[i][0], posEggs[i][1]));
        shape.rotate(posEggs[i][2]);

        eggs.push_back(shape);
    }
}

void Game::reset()
{
    level = 1;
    speed = 10;
    spawnRate = 5;
    spawnCount = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            chickens[i][j] == 0;
        }
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
        for (int j = 5; j > 0; j--) {
            swap(chickens[i][j], chickens[i][j - 1]);
            if (j == 5 && chickens[i][j]) {
                if (wolfPos == i && chickens[i][j] == 1) {
                    chickens[i][j] = 0;
                    caughtEggs++;
                }
                else if (wolfPos != i) {
                    mistakes++;
                    reset();
                    cout << spawnRate << " : " << level << endl;
                }
            }
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

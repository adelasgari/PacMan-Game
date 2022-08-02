#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>
#include <string>
#include "ghost.cpp"
#include <functional>
#include <fstream>
using namespace sf;
bool winCheck(int map[22][19])
{
    int tedadeNoghteBaghimande = 0;
    for (size_t i = 0; i < 22; i++)
    {
        for (size_t j = 0; j < 19; j++)
        {
            if (map[i][j] == 0)
            {
                tedadeNoghteBaghimande++;
            }
        }
    }
    if (tedadeNoghteBaghimande == 0)
    {
        return true;
    }
    else
        return false;
}
void setmap(int map[22][19])
{
    for (size_t i = 0; i < 22; i++)
    {
        for (size_t j = 0; j < 19; j++)
        {
            map[i][j] = 0;
        }
    }
    for (size_t i = 0; i < 19; i++)
    {
        map[0][i] = 2;
    }
    for (size_t i = 0; i < 22; i++)
    {
        map[i][0] = 2;
    }
    for (size_t i = 0; i < 19; i++)
    {
        map[21][i] = 2;
    }
    for (size_t i = 0; i < 22; i++)
    {
        map[i][18] = 2;
    }

    map[1][9] = 2;
    map[2][2] = map[2][3] = map[2][5] = map[2][6] = map[2][7] = map[2][9] = map[2][11] = map[2][12] = map[2][13] = map[2][15] = map[2][16] = 2;
    map[3][2] = map[3][3] = map[3][5] = map[3][6] = map[3][7] = map[3][9] = map[3][11] = map[3][12] = map[3][13] = map[3][15] = map[3][16] = 2;

    map[5][2] = map[5][3] = map[5][5] = map[5][7] = map[5][8] = map[5][9] = map[5][10] = map[5][11] = map[5][13] = map[5][15] = map[5][16] = 2;
    map[6][5] = map[6][9] = map[6][13] = 2;
    map[7][1] = map[7][2] = map[7][3] = map[7][5] = map[7][6] = map[7][7] = map[7][9] = map[7][11] = map[7][12] = map[7][13] = map[7][15] = map[7][16] = map[7][17] = 2;
    map[8][1] = map[8][2] = map[8][3] = map[8][5] = map[8][13] = map[8][15] = map[8][16] = map[8][17] = 2;
    map[9][1] = map[9][2] = map[9][3] = map[9][5] = map[9][7] = map[9][8] = map[9][10] = map[9][11] = map[9][13] = map[9][15] = map[9][16] = map[9][17] = 2;
    // door of ghosts palce
    map[9][9] = 5;

    map[10][0] = map[10][1] = map[10][2] = map[10][3] = map[10][8] = map[10][9] = map[10][10] = map[10][15] = map[10][16] = map[10][17] = map[10][18] = 3;
    map[10][7] = map[10][11] = 2;
    map[11][1] = map[11][2] = map[11][3] = map[11][5] = map[11][7] = map[11][8] = map[11][9] = map[11][10] = map[11][11] = map[11][13] = map[11][15] = map[11][16] = map[11][17] = 2;
    map[12][1] = map[12][2] = map[12][3] = map[12][5] = map[12][13] = map[12][15] = map[12][16] = map[12][17] = 2;
    map[13][1] = map[13][2] = map[13][3] = map[13][5] = map[13][7] = map[13][8] = map[13][9] = map[13][10] = map[13][11] = map[13][13] = map[13][15] = map[13][16] = map[13][17] = 2;
    map[14][9] = 2;
    map[15][2] = map[15][3] = map[15][5] = map[15][6] = map[15][7] = map[15][9] = map[15][11] = map[15][12] = map[15][13] = map[15][15] = map[15][16] = 2;
    map[16][3] = map[16][15] = 2;
    map[17][1] = map[17][3] = map[17][5] = map[17][7] = map[17][8] = map[17][9] = map[17][10] = map[17][11] = map[17][13] = map[17][15] = map[17][17] = 2;
    map[18][5] = map[18][9] = map[18][13] = 2;
    map[19][2] = map[19][3] = map[19][2] = map[19][4] = map[19][5] = map[19][6] = map[19][7] = map[19][9] = map[19][11] = map[19][12] = map[19][13] = map[19][14] = map[19][15] = map[19][16] = 2;
    // pacman place
    map[12][9] = 3;

    // power points
    map[14][1] = 1;
    map[1][1] = 1;
    map[3][17] = 1;
    map[20][17] = 1;
}
void drawmap(RenderWindow &b, int map[22][19])
{
    float x = 20;
    float y = 200;
    for (size_t i = 0; i < 22; i++)
    {
        for (size_t j = 0; j < 19; j++)
        {
            if (map[i][j] == 0)
            {
                CircleShape c(1);
                c.setFillColor(Color::Yellow);
                c.setPosition(Vector2f(x, y));
                b.draw(c);
            }
            else if (map[i][j] == 1)
            {
                CircleShape c(5);
                c.setFillColor(Color::White);
                c.setPosition(Vector2f(x, y));
                b.draw(c);
            }
            else if (map[i][j] == 2)
            {
                // RectangleShape r(Vector2f(10, 10));
                // r.setPosition(Vector2f(x, y));
                // b.draw(r);
            }

            x += 25;
        }
        y += 24.9;
        x = 20;
    }
}

int main()
{
    srand(time(0));
    RenderWindow b(VideoMode(500, 800), "emam ali");

    Image icon;
    icon.loadFromFile("pacpac.png");
    b.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    RectangleShape doshman(Vector2f(40, 40));
    doshman.setPosition(Vector2f(200, 0));

    Vector2i andaze(33, 33);

    Texture t;
    t.loadFromFile("pacman.png");

    Sprite s(t);
    s.setTextureRect(IntRect(0, 0, andaze.x, andaze.y));
    s.setScale(Vector2f(0.8, 0.8));

    int CountOfLifes = 3;

    float x = 245;
    float y = 487;

    int normalizeX = 0;
    int normalizeY = 0;

    Event event;
    Time zamaneseparishode;

    Clock clock;

    float zamaneanimation = 0.2;
    int tedadFrame = 3;

    float sorat = 1;

    Texture worldmap;
    worldmap.loadFromFile("map.png");
    Sprite worldsprite;
    worldsprite.setTexture(worldmap);
    worldsprite.setPosition(Vector2f(20, 200));
    worldsprite.setScale(Vector2f(1.025, 1.065));

    int map[22][19];
    setmap(map);

    Font font;
    font.loadFromFile("times.ttf");

    Text matneEmtiaz;
    matneEmtiaz.setString("Emtiaz : 0");
    matneEmtiaz.setFont(font);
    matneEmtiaz.setPosition(Vector2f(20, 160));
    // matneEmtiaz.scale(Vector2f(0.8, 0.8));
    matneEmtiaz.setFillColor(Color::Yellow);
    matneEmtiaz.setCharacterSize(28);
    matneEmtiaz.setOutlineColor(Color::Magenta);
    matneEmtiaz.setOutlineThickness(2);

    int emtiaz = 0;
    int emtiazeHarNoghte = 10;
    int emtiazeHarNoghteBozorg = 50;
    int forsatebazi = 2;

    int jahatePacMan = 3;

    Texture scareGhostTexture;
    scareGhostTexture.loadFromFile("scaredghost.png");
    Texture redGhostTexture;
    redGhostTexture.loadFromFile("redghost.png");
    Ghost redGhost(245, 375, redGhostTexture, scareGhostTexture, 1, 1, 1);
    int ghostStep = 1;

    Texture cyanGhostTexture;
    cyanGhostTexture.loadFromFile("cyanghost.png");
    Ghost cyanGhost(200, 435, cyanGhostTexture, scareGhostTexture, 1, 1, 1);

    Texture orangeGhostTexture;
    orangeGhostTexture.loadFromFile("orangeghost.png");
    Ghost orangeGhost(228, 435, orangeGhostTexture, scareGhostTexture, 1, 1, 1);

    Texture pinkGhostTexture;
    pinkGhostTexture.loadFromFile("pinkghost.png");
    Ghost pinkGhost(235, 435, pinkGhostTexture, scareGhostTexture, 1, 1, 1);

    Texture food;
    food.loadFromFile("foods.png");
    Sprite foodsprite;
    foodsprite.setTexture(food);

    int countOfEats = 0;

    float secondsfromFoodShow = 0;
    bool showFood = false;

    float ghostsScareTime = 0;
    bool isGhostsScare = false;
    float timeToChangeColorOfScaredGhost = 0;

    float lossTime = 0;
    bool playerLoss = false;

    Texture life1;
    life1.loadFromFile("pacman.png");
    Texture life2;
    life2.loadFromFile("pacman.png");

    Sprite lifes1;
    lifes1.setTexture(life1);
    lifes1.setPosition(Vector2f(50, 750));
    lifes1.setTextureRect(IntRect(63, 0, 33, 33));
    Sprite lifes2;
    lifes2.setTexture(life2);
    lifes2.setPosition(Vector2f(95, 750));
    lifes2.setTextureRect(IntRect(63, 0, 33, 33));

    ifstream inputfile("HighScore.txt", ios::in);
    Text highScore;
    highScore.setFont(font);
    int highScoreFromFile = 0;
    inputfile >> highScoreFromFile;
    highScore.setString("High Score: " + std::to_string(highScoreFromFile));
    highScore.setPosition(Vector2f(230, 160));
    highScore.setFillColor(Color::Yellow);
    highScore.setCharacterSize(28);
    highScore.setOutlineColor(Color::Magenta);
    highScore.setOutlineThickness(2);

    Text gameover;
    gameover.setFont(font);
    gameover.setString("Game Over!");
    gameover.setPosition(Vector2f(160, 400));
    gameover.setFillColor(Color::Yellow);
    gameover.setCharacterSize(35);
    gameover.setOutlineColor(Color::Magenta);
    gameover.setOutlineThickness(2);

    Text Win;
    Win.setFont(font);
    Win.setString("You Win!");
    Win.setPosition(Vector2f(160, 400));
    Win.setFillColor(Color::Yellow);
    Win.setCharacterSize(35);
    Win.setOutlineColor(Color::Magenta);
    Win.setOutlineThickness(2);

    bool isGameOver = false;
    bool isWin = false;

    while (b.isOpen())
    {
        Time deltatime = clock.restart();
        zamaneseparishode += deltatime;
        float zamanbarhasbesanieh = zamaneseparishode.asSeconds();

        int frame = static_cast<int>((zamanbarhasbesanieh / zamaneanimation) * tedadFrame) % tedadFrame;
        s.setTextureRect(IntRect(frame * andaze.x, 0, andaze.x, andaze.y));

        while (b.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::EventType::KeyPressed:

                if (event.key.code == Keyboard::Key::Right || event.key.code == Keyboard::Key::D)
                {
                    if (map[(int)ceil((y - 200) / 24.9)][(int)ceil((x - 20 + (10 * sorat)) / 25)] != 2)
                    {
                        jahatePacMan = 1;
                        // std::cout << "X: " + std::to_string((int)ceil((x - 20 + (5 * sorat)) / 25)) + " ,Y: " + std::to_string((int)ceil((y - 200) / 24.9)) << std::endl;
                    }
                }
                else if (event.key.code == Keyboard::Key::Left || event.key.code == Keyboard::Key::A)
                {
                    if (map[(int)ceil((y - 200) / 24.9)][(int)ceil((x - 20 - (10 * sorat)) / 25)] != 2)
                    {
                        jahatePacMan = 3;
                        // std::cout << "X: " + std::to_string((int)ceil((x - 20 - (5 * sorat)) / 25)) + " ,Y: " + std::to_string((int)ceil((y - 200) / 24.9)) << std::endl;
                    }
                }
                else if (event.key.code == Keyboard::Key::Up || event.key.code == Keyboard::Key::W)
                {
                    if (map[(int)ceil((y - 200 - (10 * sorat)) / 24.9)][(int)ceil((x - 20) / 25)] != 2)
                    {
                        jahatePacMan = 4;
                        // std::cout << "X: " + std::to_string(ceil((x - 20) / 25)) + " ,Y: " + std::to_string((int)ceil((y - 200 - (5 * sorat)) / 25)) << std::endl;
                    }
                }
                else if (event.key.code == Keyboard::Key::Down || event.key.code == Keyboard::Key::S)
                {
                    if (map[(int)ceil((y - 200 + (10 * sorat)) / 24.9)][(int)ceil((x - 20) / 25)] != 2 && map[(int)ceil((y - 200 + (10 * sorat)) / 24.9)][(int)ceil((x - 20) / 25)] != 5)
                    {
                        jahatePacMan = 2;
                        // std::cout << "X: " + std::to_string(ceil((x - 20) / 25)) + " ,Y: " + std::to_string((int)ceil((y - 200 + (5 * sorat)) / 25)) << std::endl;
                    }
                }
                else if (event.key.code == Keyboard::Key::Escape)
                {
                    b.close();
                }
                break;
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (isWin || isGameOver)
            {
                if (emtiaz > highScoreFromFile)
                {
                    ofstream output("HighScore.txt", ios::out);
                    output << emtiaz;
                    output.close();
                    highScore.setString("High Score: " + std::to_string(emtiaz));
                }

                isGameOver = false;
                isWin = false;
                emtiaz = 0;
                CountOfLifes = 3;

                redGhost.setStatus(1);
                redGhost.setPosition(245, 375);

                cyanGhost.setStatus(1);
                cyanGhost.setPosition(200, 435);

                pinkGhost.setStatus(1);
                pinkGhost.setPosition(235, 435);

                orangeGhost.setStatus(1);
                orangeGhost.setPosition(228, 435);

                s.setPosition(Vector2f(245, 487));
                setmap(map);

                jahatePacMan = 3;
            }
        }
        if (isWin)
        {
            b.clear(Color::Black);
            b.draw(Win);
            b.display();
        }
        else if (!isGameOver)
        {

            if (!playerLoss)
            {

                if (jahatePacMan == 1)
                {
                    if (map[(int)ceil((y - 200) / 24.9)][(int)ceil((x - 20 + (5 * sorat)) / 25)] != 2)
                    {
                        x += (0.12 * sorat);
                    }
                }
                else if (jahatePacMan == 3)
                {
                    if (map[(int)ceil((y - 200) / 24.9)][(int)ceil((x - 20 - (5 * sorat)) / 25)] != 2)
                    {
                        x -= (0.12 * sorat);
                    }
                }
                else if (jahatePacMan == 2)
                {
                    if (map[(int)ceil((y - 200 + (5 * sorat)) / 24.9)][(int)ceil((x - 20) / 25)] != 2 && map[(int)ceil((y - 200 + (5 * sorat)) / 24.9)][(int)ceil((x - 20) / 25)] != 5)
                    {
                        y += (0.12 * sorat);
                    }
                }
                else if (jahatePacMan == 4)
                {
                    if (map[(int)ceil((y - 200 - (5 * sorat)) / 24.9)][(int)ceil((x - 20) / 25)] != 2)
                    {
                        y -= (0.12 * sorat);
                    }
                }
                if (map[(int)ceil((y - 200) / 24.9)][(int)ceil((x - 20) / 25)] == 0)
                {
                    countOfEats++;
                    map[(int)ceil((y - 200) / 24.9)][(int)ceil((x - 20) / 25)] = 3;
                    emtiaz += emtiazeHarNoghte;

                    isWin = winCheck(map);
                }
            }
            if (map[(int)ceil((y - 200) / 24.9)][(int)ceil((x - 20) / 25)] == 1)
            {
                emtiaz += emtiazeHarNoghteBozorg;
                map[(int)ceil((y - 200) / 24.9)][(int)ceil((x - 20) / 25)] = 3;
                isGhostsScare = true;
                redGhost.ShoroeTars();
                cyanGhost.ShoroeTars();
                pinkGhost.ShoroeTars();
                orangeGhost.ShoroeTars();
                ghostsScareTime += deltatime.asSeconds();
            }
            if (isGhostsScare && ghostsScareTime != 0)
            {
                if (ghostsScareTime <= 6.0)
                {
                    ghostsScareTime += deltatime.asSeconds();
                    if (ghostsScareTime <= 6.0 && ghostsScareTime >= 5.0)
                    {
                        timeToChangeColorOfScaredGhost += deltatime.asSeconds();
                        if (redGhost.getStatus() == 3)
                        {
                            if (!(timeToChangeColorOfScaredGhost <= 0.1 && timeToChangeColorOfScaredGhost >= 0))
                            {
                                redGhost.setStatus(4);
                                cyanGhost.setStatus(4);
                                pinkGhost.setStatus(4);
                                orangeGhost.setStatus(4);
                            }
                        }
                        else if (redGhost.getStatus() == 4)
                        {
                            if (!(timeToChangeColorOfScaredGhost <= 0.2 && timeToChangeColorOfScaredGhost >= 0.1))
                            {
                                redGhost.setStatus(3);
                                cyanGhost.setStatus(3);
                                pinkGhost.setStatus(3);
                                orangeGhost.setStatus(3);
                                timeToChangeColorOfScaredGhost = 0;
                            }
                        }
                    }
                }

                else
                {
                    ghostsScareTime = 0;
                    isGhostsScare = false;
                    timeToChangeColorOfScaredGhost = 0;

                    redGhost.setStatus(1);
                    cyanGhost.setStatus(1);
                    pinkGhost.setStatus(1);
                    orangeGhost.setStatus(1);
                }
            }

            if ((countOfEats == 70 || countOfEats == 140) && !showFood)
            {
                showFood = true;
                secondsfromFoodShow += 0.1;
                int randx = rand() % 17 + 1;
                int randy = rand() % 21 + 1;
                while (map[randy][randx] == 2)
                {
                    randx = rand() % 17 + 1;
                    randy = rand() % 21 + 1;
                }
                randx = randx * 25 + 20;
                randy = randy * 24.9 + 200;
                cout << randx << " ** " << randy << endl;
                foodsprite.setPosition(Vector2f(randx, randy));
                if (countOfEats == 70)
                {
                    foodsprite.setTextureRect(IntRect(0, 0, 16, 17));
                }
                else if (countOfEats == 140)
                {
                    foodsprite.setTextureRect(IntRect(16, 0, 16, 17));
                }
            }

            if (s.getGlobalBounds().intersects(foodsprite.getGlobalBounds()) && showFood)
            {
                if (countOfEats >= 70 && countOfEats < 140)
                    emtiaz += 100;
                else
                    emtiaz += 300;

                showFood = false;
            }

            if (!playerLoss && s.getGlobalBounds().intersects(redGhost.getGlobalBounds()) || s.getGlobalBounds().intersects(cyanGhost.getGlobalBounds()) || s.getGlobalBounds().intersects(pinkGhost.getGlobalBounds()) || s.getGlobalBounds().intersects(orangeGhost.getGlobalBounds()))
            {
                if (isGhostsScare)
                {
                    emtiaz += 200;
                    if (s.getGlobalBounds().intersects(redGhost.getGlobalBounds()))
                    {
                        redGhost.setStatus(1);
                        // redGhost.setPosition(245, 375);
                        redGhost.returnHome(map);
                    }
                    else if (s.getGlobalBounds().intersects(cyanGhost.getGlobalBounds()))
                    {
                        cyanGhost.setStatus(1);
                        // cyanGhost.setPosition(200, 435);
                        cyanGhost.returnHome(map);
                    }
                    else if (s.getGlobalBounds().intersects(pinkGhost.getGlobalBounds()))
                    {
                        pinkGhost.setStatus(1);
                        // pinkGhost.setPosition(235, 435);
                        pinkGhost.returnHome(map);
                    }
                    else if (s.getGlobalBounds().intersects(orangeGhost.getGlobalBounds()))
                    {
                        orangeGhost.setStatus(1);
                        // orangeGhost.setPosition(228, 435);
                        orangeGhost.returnHome(map);
                    }
                }
                else
                {
                    if (CountOfLifes == 0)
                    {
                        isGameOver = true;
                    }

                    CountOfLifes--;
                    emtiaz -= 20;
                    playerLoss = true;
                    lossTime = 0;
                    lossTime += deltatime.asSeconds();
                    x = 245;
                    y = 487;
                    s.setPosition(Vector2f(x, y));

                    redGhost.setPosition(245, 375);
                    redGhost.taeineJahat(map, 1);
                    cyanGhost.setPosition(200, 435);
                    cyanGhost.taeineJahat(map, 1);

                    orangeGhost.setPosition(228, 435);
                    orangeGhost.taeineJahat(map, 1);
                    pinkGhost.setPosition(235, 435);
                    pinkGhost.taeineJahat(map, 1);
                }
            }
            if ((int)ceil((x - 20) / 25) == 0 && (int)ceil((y - 200) / 24.9) == 10 && jahatePacMan == 3)
            {
                x = 20 + 18 * 25;
            }
            if ((int)ceil((x - 20) / 25) == 18 && (int)ceil((y - 200) / 24.9) == 10 && jahatePacMan == 1)
            {
                x = 20;
            }
            if (!playerLoss)
            {
                ghostStep = (ghostStep + 1) % 2;
                redGhost.taeineJahat(map, ghostStep);
                cyanGhost.taeineJahat(map, ghostStep);
                orangeGhost.taeineJahat(map, ghostStep);
                pinkGhost.taeineJahat(map, ghostStep);
                s.setPosition(Vector2f(x, y));
            }
            else if (lossTime <= 2.0 && playerLoss)
            {
                lossTime += deltatime.asSeconds();
            }
            else
            {
                lossTime = 0;
                playerLoss = false;
            }

            matneEmtiaz.setString("Emtiaz :" + std::to_string(emtiaz));

            b.clear(Color::Black);

            b.draw(worldsprite);
            if (CountOfLifes == 1)
            {
                b.draw(lifes1);
            }

            if (CountOfLifes == 2)
            {
                b.draw(lifes1);

                b.draw(lifes2);
            }

            drawmap(b, map);
            b.draw(matneEmtiaz);
            b.draw(doshman);
            b.draw(s);
            b.draw(redGhost);
            b.draw(cyanGhost);
            b.draw(orangeGhost);
            b.draw(pinkGhost);
            b.draw(highScore);
            if (showFood && secondsfromFoodShow != 0)
            {
                secondsfromFoodShow += deltatime.asSeconds();

                if (secondsfromFoodShow <= 10.0)
                {
                    b.draw(foodsprite);
                }
                else
                {
                    secondsfromFoodShow = 0;
                    showFood = false;
                }
            }
            b.display();
        }
        else if (isGameOver)
        {

            b.clear(Color::Black);
            b.draw(gameover);
            b.display();
        }
    }
}
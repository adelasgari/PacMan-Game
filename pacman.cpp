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
//این تابع برنده شدن در بازی را بررسی می کند
bool winCheck(int map[22][19])
{

    for (size_t i = 0; i < 22; i++) //تعداد سطرهای نقشه بازی 22 می باشد
    {
        for (size_t j = 0; j < 19; j++) //نعداد ستون های نقشه بازی 19 می باشد
        {
            if (map[i][j] == 0) //در نقشه بازی شماره 0 به معنی خوراکی عادی است
            {
                return false;
            }
        }
    }
    return true;
}
//این تابع نقشه بازی را بر اساس عکس نقشه پر میکند
void setmap(int map[22][19])
{
    for (size_t i = 0; i < 22; i++)
    {
        for (size_t j = 0; j < 19; j++)
        {
            map[i][j] = 0; //ابتدا تمام خانه های ماتریس با خوراکی های عادی پر می شود
        }
    }
    for (size_t i = 0; i < 19; i++)
    {
        map[0][i] = 2; //سطر اول را باد یوار پر میکند.(دیوار بالا)
    }
    for (size_t i = 0; i < 22; i++)
    {
        map[i][0] = 2; //ستون اول را با دیوار پر میکنیم(دیوتر سمت چپ)
    }
    for (size_t i = 0; i < 19; i++)
    {
        map[21][i] = 2; //  (سطر آخر را با دیوار پر میکنیم(دیوار پایین
    }
    for (size_t i = 0; i < 22; i++)
    {
        map[i][18] = 2; //(ستون اخر را با دیوار پر میکنیم(ستون سمت راستا
    }

    map[1][9] = 2; // دیوار کشیده ایم
    map[2][2] = map[2][3] = map[2][5] = map[2][6] = map[2][7] = map[2][9] = map[2][11] = map[2][12] = map[2][13] = map[2][15] = map[2][16] = 2;
    map[3][2] = map[3][3] = map[3][5] = map[3][6] = map[3][7] = map[3][9] = map[3][11] = map[3][12] = map[3][13] = map[3][15] = map[3][16] = 2;

    map[5][2] = map[5][3] = map[5][5] = map[5][7] = map[5][8] = map[5][9] = map[5][10] = map[5][11] = map[5][13] = map[5][15] = map[5][16] = 2;
    map[6][5] = map[6][9] = map[6][13] = 2;
    map[7][1] = map[7][2] = map[7][3] = map[7][5] = map[7][6] = map[7][7] = map[7][9] = map[7][11] = map[7][12] = map[7][13] = map[7][15] = map[7][16] = map[7][17] = 2;
    map[8][1] = map[8][2] = map[8][3] = map[8][5] = map[8][13] = map[8][15] = map[8][16] = map[8][17] = 2;
    map[9][1] = map[9][2] = map[9][3] = map[9][5] = map[9][7] = map[9][8] = map[9][10] = map[9][11] = map[9][13] = map[9][15] = map[9][16] = map[9][17] = 2;
    // درب ختنه روح ها
    map[9][9] = 5;
    //خانه های پوچ
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
    // موقعیت اولیه پک من
    map[12][9] = 3;

    // خوراکی های قدرتی
    map[14][1] = 1;
    map[1][1] = 1;
    map[3][17] = 1;
    map[20][17] = 1;
}
// تابع برای ترسیم نقشه
void drawmap(RenderWindow &b, int map[22][19])
{
    float x = 20;  // مختصات xنقشه
    float y = 200; //مختصات y نقشه
    for (size_t i = 0; i < 22; i++)
    {
        for (size_t j = 0; j < 19; j++)
        {
            if (map[i][j] == 0)
            {
                CircleShape c(2);              //ترسیم دایره به شعاع 2
                c.setFillColor(Color::Yellow); //تعیین رنگ دایره
                c.setPosition(Vector2f(x, y)); //مختصات گوشه دایره
                b.draw(c);
            }
            else if (map[i][j] == 1)
            {

                CircleShape c(5); //تعیین اندازه دایره دیوار
                c.setFillColor(Color::White);
                c.setPosition(Vector2f(x, y));
                b.draw(c);
            }
            else if (map[i][j] == 2)
            {
                //کد های بخش ترسیم دیوار
                // RectangleShape r(Vector2f(10, 10));
                // r.setPosition(Vector2f(x, y));
                // b.draw(r);
            }

            x += 25; //فاصله دو ستون 25 است
        }
        y += 24.9; //فاصله دو سطر 24.9 است
        x = 20;    //مختصات ط اولین خانه 20 میباشد
    }
}

int main()
{
    srand(time(0));                                                          //باعث ایجاد اعداد تصادفی میشود
    RenderWindow MainWindow(VideoMode(500, 800), "Adel Asgari 40012358027"); //ابعاد پنجره 500 در 800 میباشد
    // MainWindow.setFramerateLimit(60);//حد اکثر تعداد فریم 60 میباشد
    Image icon;
    icon.loadFromFile("Images/pacpac.png"); //با رگذاری ایکون پروژه
    MainWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Texture logo;
    logo.loadFromFile("Images/logo.png"); //بارگذاری بنر بازی
    RectangleShape banner(Vector2f(500, 150));
    banner.setPosition(Vector2f(0, 0));
    banner.setTexture(&logo);

    Vector2i andaze(33, 33); //اندازه کاراکتر پک من

    Texture pacmanTexture;
    pacmanTexture.loadFromFile("Images/pacman.png"); //بارگذاری عکس پک من

    Sprite PacMan(pacmanTexture);
    PacMan.setTextureRect(IntRect(0, 0, andaze.x, andaze.y));
    PacMan.setScale(Vector2f(0.8, 0.8));

    int CountOfLifes = 3; //تعداد جانهای بارگذاری شده

    float x = 245; //مختصات x پک من
    float y = 487; //مختصات y پک من

    int normalizeX = 0;
    int normalizeY = 0;

    Event event;            //رویداد های صفحه کلید و موس را دریافت میکند
    Time zamaneseparishode; //زمان سپری شده

    Clock clock; //برای اندازه گیری زمان

    float zamaneanimation = 0.2; //مدت زمتن اجرای انیمیشن پک من
    int tedadFrame = 3;          //تعدتد عکس هتی تشکیل دهنده انیمیشن پک من

    float sorat = 1; //ضریب سرعت پک من

    Texture worldmap;
    worldmap.loadFromFile("Images/map.png"); //بارگذاری عکس نقشه با زی
    Sprite worldsprite;
    worldsprite.setTexture(worldmap);
    worldsprite.setPosition(Vector2f(20, 200));
    worldsprite.setScale(Vector2f(1.025, 1.065)); //تغییر مقیاس نقشه بازی

    int map[22][19]; //تعیین نقشه بازی
    setmap(map);     //پر کردن نقشه بازی

    Font font;
    font.loadFromFile("Fonts/times.ttf"); //بارگذاری فونت بازی

    Text matneEmtiaz; //متن امتیاز بازی
    matneEmtiaz.setString("Emtiaz : 0");
    matneEmtiaz.setFont(font);
    matneEmtiaz.setPosition(Vector2f(20, 160));
    // matneEmtiaz.scale(Vector2f(0.8, 0.8));
    matneEmtiaz.setFillColor(Color::Yellow);
    matneEmtiaz.setCharacterSize(28); //اندازه متن
    matneEmtiaz.setOutlineColor(Color::Magenta);
    matneEmtiaz.setOutlineThickness(2);

    int emtiaz = 20;                 //امتیاز اولیه بازی
    int emtiazeHarNoghte = 10;       //امتیاز هر خوراک عادی
    int emtiazeHarNoghteBozorg = 50; //امتیاز هر خوراک قدرتی
    int forsatebazi = 2;

    int jahatePacMan = 3; //جهت اولیه پک-من

    Texture scareGhostTexture;
    scareGhostTexture.loadFromFile("Images/scaredghost.png"); //بارگزاری روح ترسیده
    Texture redGhostTexture;
    redGhostTexture.loadFromFile("Images/redghost.png"); //بارگزاری روح قرمز
    Ghost redGhost(245, 375, redGhostTexture, scareGhostTexture, 1, 1, 1);

    int ghostStep = 1; //مشخص کننده گام حرکت ارواح

    Texture cyanGhostTexture;
    cyanGhostTexture.loadFromFile("Images/cyanghost.png"); //بارگزاری روح فیروزه ای
    Ghost cyanGhost(200, 435, cyanGhostTexture, scareGhostTexture, 1, 1, 1);

    Texture orangeGhostTexture;
    orangeGhostTexture.loadFromFile("Images/orangeghost.png"); //بارگزاری روح نارنجی
    Ghost orangeGhost(228, 435, orangeGhostTexture, scareGhostTexture, 1, 1, 1);

    Texture pinkGhostTexture;
    pinkGhostTexture.loadFromFile("Images/pinkghost.png"); //بارگزاری روح صورتی
    Ghost pinkGhost(235, 435, pinkGhostTexture, scareGhostTexture, 1, 1, 1);

    Texture food;
    food.loadFromFile("Images/foods.png"); //بارگزاری غذا
    Sprite foodsprite;
    foodsprite.setTexture(food);

    int countOfEats = 0; //تعداد غذاهای خورده شده

    float secondsfromFoodShow = 0; //تعداد ثانیه های گذشته از نمایش غذا
    bool showFood = false;         // آیا غذا نمایش داده شده است؟

    float ghostsScareTime = 0;                //چقدر از زمان ترس ارواح گذشته است
    bool isGhostsScare = false;               //آیا روح ها در حالت ترس قرار دارند
    float timeToChangeColorOfScaredGhost = 0; //مدت زمانی که ارواح ترسیده چشمک می زنند

    float lossTime = 0;      //مدت زمانی ک پس از باخت پک من و ارواح ثابت می مانند و حرکتی نمی کنند
    bool playerLoss = false; //آیا بازیکن باخته است؟

    Texture life;
    life.loadFromFile("Images/pacman.png"); //بارگزاری عکس پک من برای نمایش جان ها

    Sprite lifes1;
    lifes1.setTexture(life);
    lifes1.setPosition(Vector2f(50, 750));
    lifes1.setTextureRect(IntRect(63, 0, 33, 33));
    Sprite lifes2;
    lifes2.setTexture(life);
    lifes2.setPosition(Vector2f(95, 750));
    lifes2.setTextureRect(IntRect(63, 0, 33, 33));

    ifstream inputfile("Data/HighScore.txt", ios::in); //خواندن بیشترین امتیاز از فایل
    int highScoreFromFile = 0;
    inputfile >> highScoreFromFile;

    Text highScore;
    highScore.setFont(font);
    highScore.setString("High Score: " + std::to_string(highScoreFromFile)); //نمایش بیشترین امنیاز درون متن
    highScore.setPosition(Vector2f(230, 160));
    highScore.setFillColor(Color::Yellow);
    highScore.setCharacterSize(28);
    highScore.setOutlineColor(Color::Magenta);
    highScore.setOutlineThickness(2);

    Text gameover; //متن نمایش داده شده در زمان باخت
    gameover.setFont(font);
    gameover.setString("Game Over!");
    gameover.setPosition(Vector2f(160, 400));
    gameover.setFillColor(Color::Yellow);
    gameover.setCharacterSize(35);
    gameover.setOutlineColor(Color::Magenta);
    gameover.setOutlineThickness(2);

    Text Win; //زمان نمایش داده شده در زمان برد
    Win.setFont(font);
    Win.setString("You Win!");
    Win.setPosition(Vector2f(160, 400));
    Win.setFillColor(Color::Yellow);
    Win.setCharacterSize(35);
    Win.setOutlineColor(Color::Magenta);
    Win.setOutlineThickness(2);

    bool isGameOver = false; //آیا پک من باخته است؟
    bool isWin = false;      //آیا پک من برده است؟

    Text myName;
    myName.setFont(font);
    myName.setString("Adel Asgari 40012358027");
    myName.setPosition(Vector2f(150, 750));
    myName.setFillColor(Color::White);
    myName.setCharacterSize(30);
    myName.setOutlineColor(Color::Magenta);
    myName.setOutlineThickness(2);

    while (MainWindow.isOpen()) //حلقه اصلی بازی
    {
        Time deltatime = clock.restart();                          //مدت زمان اجرای هر بار حلقه
        zamaneseparishode += deltatime;                            //کل زمان سپری شده را نگهداری می کنیم
        float zamanbarhasbesanieh = zamaneseparishode.asSeconds(); //زمان سپری شده را بر حسب ثانیه نگهداری می کنیم

        int frame = static_cast<int>((zamanbarhasbesanieh / zamaneanimation) * tedadFrame) % tedadFrame; //مشخص کردن شماره فریمی از پک من ک باید نمایش داده شود
        PacMan.setTextureRect(IntRect(frame * andaze.x, 0, andaze.x, andaze.y));                         //تعیین برشی از بافت پک من که باید تمایش داده شود

        while (MainWindow.pollEvent(event)) //آیا رویدادی رخ داده است؟
        {
            switch (event.type) //نوع رویداد رخ داده چیست
            {
            case Event::EventType::KeyPressed: //اگر رویداد رخ داده فشردن کلید کیبرد باشد

                if (event.key.code == Keyboard::Key::Right || event.key.code == Keyboard::Key::D) //اگر کلید راست یا D فشرده شد.
                {
                    if (map[(int)ceil((y - 200) / 24.9)][(int)ceil((x - 20 + (10 * sorat)) / 25)] != 2) //اگر سمت راست دیواری نبود
                    {
                        jahatePacMan = 1; //پک من به سمت راست حرکت می کند
                        // std::cout << "X: " + std::to_string((int)ceil((x - 20 + (5 * sorat)) / 25)) + " ,Y: " + std::to_string((int)ceil((y - 200) / 24.9)) << std::endl;
                    }
                }
                else if (event.key.code == Keyboard::Key::Left || event.key.code == Keyboard::Key::A)
                {
                    if (map[(int)ceil((y - 200) / 24.9)][(int)ceil((x - 20 - (10 * sorat)) / 25)] != 2)
                    {
                        jahatePacMan = 3; //پک من به سمت چپ حرکت می کند
                        // std::cout << "X: " + std::to_string((int)ceil((x - 20 - (5 * sorat)) / 25)) + " ,Y: " + std::to_string((int)ceil((y - 200) / 24.9)) << std::endl;
                    }
                }
                else if (event.key.code == Keyboard::Key::Up || event.key.code == Keyboard::Key::W)
                {
                    if (map[(int)ceil((y - 200 - (10 * sorat)) / 24.9)][(int)ceil((x - 20) / 25)] != 2)
                    {
                        jahatePacMan = 4; //پک من به سمت بالا حرکت می کند
                        // std::cout << "X: " + std::to_string(ceil((x - 20) / 25)) + " ,Y: " + std::to_string((int)ceil((y - 200 - (5 * sorat)) / 25)) << std::endl;
                    }
                }
                else if (event.key.code == Keyboard::Key::Down || event.key.code == Keyboard::Key::S)
                {
                    if (map[(int)ceil((y - 200 + (10 * sorat)) / 24.9)][(int)ceil((x - 20) / 25)] != 2 && map[(int)ceil((y - 200 + (10 * sorat)) / 24.9)][(int)ceil((x - 20) / 25)] != 5)
                    {
                        jahatePacMan = 2; //پک من به سمت پایین حرکت می کند
                        // std::cout << "X: " + std::to_string(ceil((x - 20) / 25)) + " ,Y: " + std::to_string((int)ceil((y - 200 + (5 * sorat)) / 25)) << std::endl;
                    }
                }
                else if (event.key.code == Keyboard::Key::Escape) //اگر کلید esc فشرده شده
                {
                    MainWindow.close(); //پنجره بسته شود.
                }
                break;

            case Event::EventType::Closed: //اگر روی علامت ضربدر گوشه پنجره کلیک کردیم
                MainWindow.close();
                break;
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //اگر کلیک چپ موس فشرده شد
        {
            if (isWin || isGameOver) //اگر برده یا باخته ایم و بازی تمام شده است.اکنون باید بازی ریست شود
            {
                if (emtiaz > highScoreFromFile) //اگر بیشترین امتیاز جدید یافته ایم
                {
                    ofstream output("Data/HighScore.txt", ios::out);
                    output << emtiaz; //بیشترین امتیاز جدید را روی فایل می نویسیم
                    output.close();
                    highScore.setString("High Score: " + std::to_string(emtiaz)); //نمایش متن بیشترین امتیاز
                }
                //تعیین کلیه مقادیر به وضعیت اولیه
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

                PacMan.setPosition(Vector2f(245, 487));
                setmap(map);

                jahatePacMan = 3;
            }
        }
        if (isWin)
        {
            MainWindow.clear(Color::Black);
            MainWindow.draw(Win);
            MainWindow.display();
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
                    // if (deltatime.asSeconds() != 0.0)
                    // {
                    //     sleep(microseconds(1 / deltatime.asMicroseconds()));
                    // }
                }
            }
            if (map[(int)ceil((y - 200) / 24.9)][(int)ceil((x - 20) / 25)] == 1)
            {
                if (deltatime.asSeconds() != 0.0)
                {
                    sleep(microseconds(3 / deltatime.asMicroseconds()));
                }
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
                int randy = rand() % 20 + 1;
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

            if (PacMan.getGlobalBounds().intersects(foodsprite.getGlobalBounds()) && showFood)
            {
                if (countOfEats >= 70 && countOfEats < 140)
                    emtiaz += 100;
                else
                    emtiaz += 300;

                showFood = false;
            }

            if (!playerLoss && PacMan.getGlobalBounds().intersects(redGhost.getGlobalBounds()) || PacMan.getGlobalBounds().intersects(cyanGhost.getGlobalBounds()) || PacMan.getGlobalBounds().intersects(pinkGhost.getGlobalBounds()) || PacMan.getGlobalBounds().intersects(orangeGhost.getGlobalBounds()))
            {
                if (isGhostsScare)
                {
                    emtiaz += 200;
                    if (PacMan.getGlobalBounds().intersects(redGhost.getGlobalBounds()))
                    {
                        redGhost.setStatus(1);
                        // redGhost.setPosition(245, 375);
                        redGhost.boroBe(map);
                    }
                    else if (PacMan.getGlobalBounds().intersects(cyanGhost.getGlobalBounds()))
                    {
                        cyanGhost.setStatus(1);
                        // cyanGhost.setPosition(200, 435);
                        cyanGhost.boroBe(map);
                    }
                    else if (PacMan.getGlobalBounds().intersects(pinkGhost.getGlobalBounds()))
                    {
                        pinkGhost.setStatus(1);
                        // pinkGhost.setPosition(235, 435);
                        pinkGhost.boroBe(map);
                    }
                    else if (PacMan.getGlobalBounds().intersects(orangeGhost.getGlobalBounds()))
                    {
                        orangeGhost.setStatus(1);
                        // orangeGhost.setPosition(228, 435);
                        orangeGhost.boroBe(map);
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
                    PacMan.setPosition(Vector2f(x, y));

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
                PacMan.setPosition(Vector2f(x, y));
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

            MainWindow.clear(Color::Black);

            MainWindow.draw(worldsprite);
            if (CountOfLifes == 1)
            {
                MainWindow.draw(lifes1);
            }

            if (CountOfLifes == 2)
            {
                MainWindow.draw(lifes1);

                MainWindow.draw(lifes2);
            }

            drawmap(MainWindow, map);
            MainWindow.draw(matneEmtiaz);
            MainWindow.draw(banner);
            MainWindow.draw(PacMan);
            MainWindow.draw(redGhost);
            MainWindow.draw(cyanGhost);
            MainWindow.draw(orangeGhost);
            MainWindow.draw(pinkGhost);
            MainWindow.draw(highScore);
            MainWindow.draw(myName);
            if (showFood && secondsfromFoodShow != 0)
            {
                secondsfromFoodShow += deltatime.asSeconds();

                if (secondsfromFoodShow <= 10.0)
                {
                    MainWindow.draw(foodsprite);
                }
                else
                {
                    secondsfromFoodShow = 0;
                    showFood = false;
                }
            }
            MainWindow.display();
        }
        else if (isGameOver)
        {

            MainWindow.clear(Color::Black);
            MainWindow.draw(gameover);
            MainWindow.display();
        }
    }
}
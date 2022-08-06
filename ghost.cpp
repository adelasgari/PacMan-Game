#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
using namespace sf;
using namespace std;
class Ghost : public Drawable //ارث بری از این کلاس باعث می شود بتوانیم شکل روح را ترسیم کنیم
{
private:
    float x; //مختصات روح
    float y;

    sf::Sprite mSprite; //تصویر روح معمولی
    sf::Sprite sSprite; //تصویر روح ترسیده
    float sorat;

    int jahateHarekat; //جهت حرکت روح
    Color color;
    int status; //وضعیت روح که عددی بین 1-5 می باشد

public:
    Ghost(float x, float y, const sf::Texture &playerTexture, const sf::Texture &ScaredTexture, int jahateHarekat, float sorat, int status);
    ~Ghost();
    void taeineJahat(int map[22][19], int);                //مسیر یابی و حرکت روح
    int masirhayeMojaver(int map[22][19]);                 //یافتن مسیرهای باز اطراف روح
    int masireShansi(int map[22][19]);                     //تصمیم گیری برای حرکت
    virtual void draw(RenderTarget &, RenderStates) const; //ترسیم اسپرایت روح
    void ShoroeTars();                                     //پس از خوردن خوراک قدرتی فراخوانی می شود
    void setStatus(int status);                            //تنظیم وضعیت روح
    int getStatus();                                       //دریافت وضعیت روح
    void setPosition(float x, float y);                    //تغییر مختصات
    FloatRect getGlobalBounds();                           //دریافت مستطیل محاط روح
    void boroBe(int map[22][19]);                          //مسیریابی
    int Taaghib(int map[22][19], float, float);
    Vector2f masafat(float, float);
};
Vector2f Ghost::masafat(float pacmanX, float pacmanY)
{
    float distX = x - pacmanX;
    float distY = y - pacmanY;
    return Vector2f(distX, distY);
}
int Ghost::Taaghib(int map[22][19], float pacmanX, float pacmanY)
{
    int tas = 0;
    int count = masirhayeMojaver(map);                        //یافتن مسیرهای باز برای روح عدد 1 یعنی مسیر بالا باز است-2 یعنی  سمت چپ باز است 4 پایین و 8 راست
    if (count == 1 || count == 2 || count == 4 || count == 8) //اگر فقط یک راه داریم!!!
    {
        return jahateHarekat;
    }
    else if (count == 3) //اگر مسیر بالا و چپ باز باشد و به راست میرویم باید مسیر بالا انتخاب شود چون نمیتوان برگشت. درغیراینصورت به سمت چپ می رویم
    {

        if (jahateHarekat == 1) //اگر به سمت راست در حال حرکت هستیم
        {
            return 4;
        }
        else
            return 3;
    }
    else if (count == 5) //اگر مسیر بالا و پایین باز باشد
    {
        if (jahateHarekat == 4)
        {
            return 4;
        }
        else
            return 2;
    }
    else if (count == 9) //اگر مسیر بالا و راست باز باشد
    {
        if (jahateHarekat == 2)
        {
            return 1;
        }
        else
            return 4;
    }
    else if (count == 6) //اگر مسیر چپ و پایین باز باشد
    {
        if (jahateHarekat == 1)
        {
            return 2;
        }
        else
            return 3;
    }
    else if (count == 10) //اگر مسیر راست و چپ باز باشد
    {
        if (jahateHarekat == 1)
        {
            return 1;
        }
        else
            return 3;
    }
    else if (count == 12) //اگر مسیر راست و پایین باز باشد
    {
        if (jahateHarekat == 4)
        {
            return 1;
        }
        else
            return 2;
    }
    //سه راهی ها را محاسبه می کنیم
    else if (count == 7) //اگر مسیر های بالا - چپ-پایین باز باشد
    {
        Vector2f dist = masafat(pacmanX, pacmanY);
        if (dist.x == 0 && dist.y > 0)
            return 4;
        else if (dist.x == 0 && dist.y < 0)
            return 2;
        else if (dist.x > 0 && dist.y == 0)
        {
            return 3;
        }
        else if (dist.x < 0 && dist.y == 0)
        {
            tas = rand() % 2;
            if (tas == 0)
            {
                return 4;
            }
            else
                return 2;
        }
        else if (dist.x < 0 && dist.y < 0)
        {
            return 2;
        }
        else if (dist.x > 0 && dist.y < 0)
        {
            tas = rand() % 2;
            if (tas == 0)
            {
                return 3;
            }
            else
                return 2;
        }
        else if (dist.x < 0 && dist.y > 0)
        {
            return 4;
        }
        else if (dist.x > 0 && dist.y > 0)
        {
            tas = rand() % 2;
            if (tas == 0)
            {
                return 4;
            }
            else
                return 3;
        }
    }
    else if (count == 11) //اگر مسیرهای چپ-بالا-راست باز باشد
    {
        Vector2f dist = masafat(pacmanX, pacmanY);
        if (dist.x == 0 && dist.y > 0)
        {
            return 4;
        }
        else if (dist.x == 0 && dist.y < 0)
        {
            tas = rand() % 2;
            if (tas == 0)
            {
                return 1;
            }
            else
                return 3;
        }
        else if (dist.x > 0 && dist.y == 0)
        {
            return 3;
        }
        else if (dist.x < 0 && dist.y == 0)
        {
            return 1;
        }
        else if (dist.x < 0 && dist.y < 0)
        {
            return 1;
        }
        else if (dist.x > 0 && dist.y < 0)
        {
            return 2;
        }
        else if (dist.x < 0 && dist.y > 0)
        {
            tas = rand() % 2;
            if (tas == 0)
            {
                return 1;
            }
            else
                return 4;
        }
        else if (dist.x > 0 && dist.y > 0)
        {
            tas = rand() % 2;
            if (tas == 0)
            {
                return 4;
            }
            else
                return 3;
        }
    }
    else if (count == 13) //اگر مسیرهای بالا-راست -پایین باز باشد
    {
        Vector2f dist = masafat(pacmanX, pacmanY);
        if (dist.x == 0 && dist.y > 0)
        {
            return 4;
        }
        else if (dist.x == 0 && dist.y < 0)
        {
            return 2;
        }
        else if (dist.x > 0 && dist.y == 0)
        {
            tas = rand() % 2;
            if (tas == 0)
            {
                return 4;
            }
            else
                return 2;
        }
        else if (dist.x < 0 && dist.y == 0)
        {
            return 1;
        }
        else if (dist.x < 0 && dist.y < 0)
        {
            tas = rand() % 2;
            if (tas == 0)
            {
                return 1;
            }
            else
                return 2;
        }
        else if (dist.x > 0 && dist.y < 0)
        {
            return 2;
        }
        else if (dist.x < 0 && dist.y > 0)
        {
            tas = rand() % 2;
            if (tas == 0)
            {
                return 1;
            }
            else
                return 4;
        }
        else if (dist.x > 0 && dist.y > 0)
        {
            return 4;
        }
    }
    else if (count == 14) //اگر مسیرهای راست-پایین-چپ باز باشد
    {
        Vector2f dist = masafat(pacmanX, pacmanY);
        if (dist.x == 0 && dist.y > 0)
        {
            return 4;
        }
        else if (dist.x == 0 && dist.y < 0)
        {
            return 2;
        }
        else if (dist.x > 0 && dist.y == 0)
        {
            return 3;
        }
        else if (dist.x < 0 && dist.y == 0)
        {
            return 1;
        }
        else if (dist.x < 0 && dist.y < 0)
        {
            tas = rand() % 2;
            if (tas == 0)
            {
                return 1;
            }
            else
                return 2;
        }
        else if (dist.x > 0 && dist.y < 0)
        {
            tas = rand() % 2;
            if (tas == 0)
            {
                return 3;
            }
            else
                return 2;
        }
        else if (dist.x < 0 && dist.y > 0)
        {

            tas = rand() % 2;
            if (tas == 0)
            {
                return 1;
            }
            else
                return 4;
        }
        else if (dist.x > 0 && dist.y > 0)
        {
            tas = rand() % 2;
            if (tas == 0)
            {
                return 1;
            }
            else
                return 3;
        }
    }
    else if (count == 15) //اگر سر چهار راه باشیم
    {
        Vector2f dist = masafat(pacmanX, pacmanY);
        if (dist.x == 0 && dist.y > 0)
        {
            return 4;
        }
        else if (dist.x == 0 && dist.y < 0)
        {
            return 2;
        }
        else if (dist.x > 0 && dist.y == 0)
        {
            return 3;
        }
        else if (dist.x < 0 && dist.y == 0)
        {
            return 1;
        }
        else if (dist.x < 0 && dist.y < 0)
        {
            tas = rand() % 2;
            if (tas == 0)
            {
                return 1;
            }
            else
                return 2;
        }
        else if (dist.x > 0 && dist.y < 0)
        {
            tas = rand() % 2;
            if (tas == 0)
            {
                return 3;
            }
            else
                return 2;
        }
        else if (dist.x < 0 && dist.y > 0)
        {

            tas = rand() % 2;
            if (tas == 0)
            {
                return 1;
            }
            else
                return 4;
        }
        else if (dist.x > 0 && dist.y > 0)
        {
            tas = rand() % 2;
            if (tas == 0)
            {
                return 1;
            }
            else
                return 3;
        }
    }
}
void Ghost::boroBe(int map[22][19])
{
    sorat = 0.1;
    float xDist = x - 9 * 25 + 20;
    float yDist = y - 9 * 24.9 + 200;
    float dist = sqrt((xDist * xDist) + (yDist * yDist));

    if ((int)ceil((y - 200) * 24.9) < 11 && (int)ceil((x - 20) * 25) < 9)
    {
        x += xDist * sorat;
        y += yDist * sorat;
    }
    else if ((int)ceil((y - 200) * 24.9) > 11 && (int)ceil((x - 20) * 25) < 9)
    {
        x += xDist * sorat;
        y -= yDist * sorat;
    }
    else if ((int)ceil((y - 200) * 24.9) < 11 && (int)ceil((x - 20) * 25) >= 9)
    {
        x -= xDist * sorat;
        y += yDist * sorat;
    }
    else if ((int)ceil((y - 200) * 24.9) >= 11 && (int)ceil((x - 20) * 25) >= 9)
    {
        x -= xDist * sorat;
        y -= yDist * sorat;
    }

    // float absoluteX = ceil((x - 20) / 25);
    // float absoluteY = ceil((y - 200) / 25);
    // if (absoluteX <= 9 && absoluteY <= 11)
    // {
    //     while (absoluteX != 4 && absoluteY != 4)
    //     {
    //         if (absoluteX < 4)
    //         {
    //             if (map[(int)absoluteY][(int)(absoluteX + .1 * sorat)] != 2)
    //                 absoluteX += 0.1 * sorat;
    //         }
    //         else if (absoluteX > 4)
    //         {
    //             if (map[(int)absoluteY][(int)(absoluteX + .1 * sorat)] != 2)

    //                 absoluteX -= 0.1 * sorat;
    //         }
    //         x = absoluteX * 25 + 20;
    //         if (absoluteY < 4)
    //         {
    //             if (map[(int)(absoluteY + .1 * sorat)][(int)(absoluteX)] != 2)
    //                 absoluteY += 0.1;
    //         }
    //         else if (absoluteX > 4)
    //         {
    //             if (map[(int)(absoluteY + .1 * sorat)][(int)(absoluteX)] != 2)

    //                 absoluteX -= 0.1 * sorat;
    //         }
    //         y = absoluteY * 24.9 + 200;
    //         setPosition(x, y);
    //     }
    // }
    // else if (x <= 9 && y > 11)
    // {
    //     while (absoluteX != 2 && absoluteY != 18)
    //     {
    //         if (absoluteX < 2)
    //         {
    //             if (map[(int)absoluteY][(int)(absoluteX + .1 * sorat)] != 2)
    //                 absoluteX += 0.1 * sorat;
    //         }
    //         else if (absoluteX > 2)
    //         {
    //             if (map[(int)absoluteY][(int)(absoluteX + .1 * sorat)] != 2)

    //                 absoluteX -= 0.1 * sorat;
    //         }
    //         x = absoluteX * 25 + 20;
    //         if (absoluteY < 18)
    //         {
    //             if (map[(int)(absoluteY + .1 * sorat)][(int)(absoluteX)] != 2)
    //                 absoluteY += 0.1;
    //         }
    //         else if (absoluteX > 18)
    //         {
    //             if (map[(int)(absoluteY + .1 * sorat)][(int)(absoluteX)] != 2)

    //                 absoluteX -= 0.1 * sorat;
    //         }
    //         y = absoluteY * 24.9 + 200;
    //         setPosition(x, y);
    //     }
    // }
    // else if (x >= 9 && y <= 11)
    // {

    //     while (absoluteX != 14 && absoluteY != 4)
    //     {
    //         if (absoluteX < 14)
    //         {
    //             if (map[(int)absoluteY][(int)(absoluteX + .1 * sorat)] != 2)
    //                 absoluteX += 0.1 * sorat;
    //         }
    //         else if (absoluteX > 14)
    //         {
    //             if (map[(int)absoluteY][(int)(absoluteX + .1 * sorat)] != 2)

    //                 absoluteX -= 0.1 * sorat;
    //         }
    //         x = absoluteX * 25 + 20;
    //         if (absoluteY < 4)
    //         {
    //             if (map[(int)(absoluteY + .1 * sorat)][(int)(absoluteX)] != 2)
    //                 absoluteY += 0.1 * sorat;
    //         }
    //         else if (absoluteX > 4)
    //         {
    //             if (map[(int)(absoluteY + .1 * sorat)][(int)(absoluteX)] != 2)

    //                 absoluteX -= 0.1 * sorat;
    //         }
    //         y = absoluteY * 24.9 + 200;
    //         setPosition(x, y);
    //     }
    // }
    // else if (x >= 9 && y > 11)
    // {
    //     while (absoluteX != 2 && absoluteY != 18)
    //     {
    //         if (absoluteX < 16)
    //         {
    //             if (map[(int)absoluteY][(int)(absoluteX + .1 * sorat)] != 2)
    //                 absoluteX += 0.1 * sorat;
    //         }
    //         else if (absoluteX > 16)
    //         {
    //             if (map[(int)absoluteY][(int)(absoluteX + .1 * sorat)] != 2)

    //                 absoluteX -= 0.1 * sorat;
    //         }
    //         x = absoluteX * 25 + 20;
    //         if (absoluteY < 18)
    //         {
    //             if (map[(int)(absoluteY + .1 * sorat)][(int)(absoluteX)] != 2)
    //                 absoluteY += 0.1;
    //         }
    //         else if (absoluteX > 18)
    //         {
    //             if (map[(int)(absoluteY + .1 * sorat)][(int)(absoluteX)] != 2)

    //                 absoluteX -= 0.1 * sorat;
    //         }
    //         y = absoluteY * 24.9 + 200;
    //         setPosition(x, y);
    //     }
    // }
}
FloatRect Ghost::getGlobalBounds() //دریافت مستطیل محاط به روح جهت محاسبه برخورد با پک-من
{
    if (status == 3 || status == 4) //اگر وضعیت ترسیده باشد در حال نمایش حالت ترسیده روح هستیم و از ssprite استفاده می کنیم
        return sSprite.getGlobalBounds();
    else
        return mSprite.getGlobalBounds();
}
void Ghost::setPosition(float x, float y) //تنظیم موقعیت روح
{
    this->x = x;
    this->y = y;
}

int Ghost::getStatus()
{
    return status;
}
void Ghost::setStatus(int status)
{
    this->status = status;
}
void Ghost::ShoroeTars() //زمانی که پک-من خوراک قدرتی می خورد این تابع را صدا میزینم تا وضعیت به ترس تغییر کند
{
    status = 3;             //وضعیت ترس
    if (jahateHarekat == 1) //جهت حرکت1=راست ، 2=پایین،3=چپ و4=بالا
    {
        jahateHarekat = 3;
    }
    else if (jahateHarekat == 2)
    {
        jahateHarekat = 4;
    }
    else if (jahateHarekat == 3)
    {
        jahateHarekat = 1;
    }
    else if (jahateHarekat == 4)
    {
        jahateHarekat = 2;
    }
}
void Ghost::draw(sf::RenderTarget &target, sf::RenderStates states) const //ترسیم روح بر روی صفحه
{
    if (status == 3 || status == 4) //اگر روح ترسیده باشد حالت ترسیده ترسیم می شود
    {
        target.draw(sSprite, states);
    }
    else
        target.draw(mSprite, states);
}
Ghost::Ghost(float x, float y, const Texture &playerTexture, const sf::Texture &ScaredTexture, int jahateHarekat = 1, float sorat = 1, int status = 1)
{
    this->x = x;
    this->y = y;
    this->jahateHarekat = jahateHarekat;
    this->sorat = sorat;
    this->status = status;
    mSprite.setTexture(playerTexture);
    sSprite.setTexture(ScaredTexture);
}

Ghost::~Ghost()
{
}
void Ghost::taeineJahat(int map[22][19], int gameHarekat) //حرکت روح
{
    if ((int)ceil((x - 20) / 25) == 0 && (int)ceil((y - 200) / 24.9) == 10 && jahateHarekat == 3) //تونل جاویی سمت چپ
    {
        x = 20 + 18 * 25;
    }
    if ((int)ceil((x - 20) / 25) == 18 && (int)ceil((y - 200) / 24.9) == 10 && jahateHarekat == 1) //تونل جادویی سمت راست
    {
        x = 20;
    }

    if (jahateHarekat == 1) //اگر به راست حرکت می کردیم
    {
        if (map[(int)ceil((y - 200) / 24.9)][(int)ceil((x - 20 + (10 * sorat)) / 25)] != 2) //اگر در مسیرحرکت دیوار نباشد
        {
            x += (0.1 * sorat); //جابجا می شویم

            jahateHarekat = masireShansi(map); //محاسبه امکان انتخاب مسیر بعدی در تقاطع ها
        }
        else
        {
            jahateHarekat = masireShansi(map);
        }
    }
    else if (jahateHarekat == 2) //اگر به پایین حرکت می کردیم
    {
        //اگر سمت پایین ما دیوار یا درب ورود خانه ارواح نباشد می توانیم وارد شویم
        if (map[(int)ceil((y - 200 + (10 * sorat)) / 24.9)][(int)ceil((x - 20) / 25)] != 2 && map[(int)ceil((y - 200 + (10 * sorat)) / 24.9)][(int)ceil((x - 20) / 25)] != 5)
        {
            y += (0.1 * sorat);

            jahateHarekat = masireShansi(map); //محاسبه امکان انتخاب مسیر بعدی در تقاطع ها

            // y += (0.1 * sorat);
        }
        else
            jahateHarekat = masireShansi(map);
    }
    else if (jahateHarekat == 3) //اگر به چپ حرکت می کردیم
    {
        if (map[(int)ceil((y - 200) / 24.9)][(int)ceil((x - 20 - (10 * sorat)) / 25)] != 2) //اگر در مسیرحرکت دیوار نباشد
        {
            x -= (0.1 * sorat);

            jahateHarekat = masireShansi(map); //محاسبه امکان انتخاب مسیر بعدی در تقاطع ها
        }
        else
            jahateHarekat = masireShansi(map);
    }
    else if (jahateHarekat == 4)
    {
        if (map[(int)ceil((y - 200 - (10 * sorat)) / 24.9)][(int)ceil((x - 20) / 25)] != 2) //اگر در مسیرحرکت دیوار نباشد
        {
            y -= (0.1 * sorat);

            jahateHarekat = masireShansi(map); //محاسبه امکان انتخاب مسیر بعدی در تقاطع ها
        }
        else
            jahateHarekat = masireShansi(map);
    }
    if (status == 3) // اگر روح ترسیده باشد و رنگش آبی باشد
    {
        sSprite.setPosition(x, y); //تعیین موقعیت مکانی روح
        //گام حرکت مشخص می کند کدام برش از روح نمایش داده شود. در نتیجه روح حالت راه رفتن پیدا می کند
        if (gameHarekat == 0)
        {
            sSprite.setTextureRect(IntRect(0, 0, 38, 33)); //برش 33*38 پیکسلی از عکس روح ترسیده آبی(حالتی ک روح 3 پا دارد)
        }
        else
        {
            sSprite.setTextureRect(IntRect(38, 0, 38, 33)); //برش 33*38 پیکسلی از عکس روح ترسیده آبی(حالتی ک روح4 پا دارد)
        }
    }
    else if (status == 4) // اگر روح ترسیده باشد و رنگش سفید باشد
    {
        sSprite.setPosition(x, y); //تعیین موقعیت مکانی روح
        //گام حرکت مشخص می کند کدام برش از روح نمایش داده شود. در نتیجه روح حالت راه رفتن پیدا می کند
        if (gameHarekat == 0)
        {
            sSprite.setTextureRect(IntRect(76, 0, 38, 33)); //برش 33*38 پیکسلی از عکس روح ترسیده سفید(حالتی ک روح 3 پا دارد)
        }
        else
        {
            sSprite.setTextureRect(IntRect(114, 0, 38, 33)); //برش 33*38 پیکسلی از عکس روح ترسیده سفید(حالتی ک روح4 پا دارد)
        }
    }
    else
    {
        mSprite.setPosition(x, y);
        if (jahateHarekat == 1) //اگر به سمت راست می رویم روح باید عکسی داشته باشد که چشمانش به راست نگاه می کند
        {
            if (gameHarekat == 0)
            {
                mSprite.setTextureRect(IntRect(0, 0, 38, 33));
            }
            else
            {
                mSprite.setTextureRect(IntRect(38, 0, 38, 33));
            }
        }
        else if (jahateHarekat == 2) //اگر به سمت پایین می رویم روح باید عکسی داشته باشد که چشمانش به پایین نگاه می کند
        {
            if (gameHarekat == 0)
            {
                mSprite.setTextureRect(IntRect(76, 0, 38, 33));
            }
            else
            {
                mSprite.setTextureRect(IntRect(114, 0, 38, 33));
            }
        }
        else if (jahateHarekat == 3) //اگر به سمت چپ می رویم روح باید عکسی داشته باشد که چشمانش به چپ نگاه می کند
        {
            if (gameHarekat == 0)
            {
                mSprite.setTextureRect(IntRect(228, 0, 38, 33));
            }
            else
            {
                mSprite.setTextureRect(IntRect(266, 0, 38, 33));
            }
        }
        else if (jahateHarekat == 4) //اگر به سمت بالا می رویم روح باید عکسی داشته باشد که چشمانش به بالا نگاه می کند
        {
            if (gameHarekat == 0)
            {
                mSprite.setTextureRect(IntRect(152, 0, 38, 33));
            }
            else
            {
                mSprite.setTextureRect(IntRect(190, 0, 38, 33));
            }
        }
    }
    // cout << x << "*************" << y << "-------------" << masirhayeMojaver(map) << "++++++++" << jahateHarekat << endl;
}

int Ghost::masireShansi(int map[22][19]) //انتخاب مسیر بعدی حرکت روح
{
    srand(time(0));
    int count = masirhayeMojaver(map);                        //یافتن مسیرهای باز برای روح عدد 1 یعنی مسیر بالا باز است-2 یعنی  سمت چپ باز است 4 پایین و 8 راست
    int tas = 0;                                              //حرکت تصادفی بعدی را در خود دارد
    if (count == 1 || count == 2 || count == 4 || count == 8) //اگر فقط یک راه داریم!!!
    {
        return jahateHarekat;
    }
    else if (count == 3) //اگر مسیر بالا و چپ باز باشد و به راست میرویم باید مسیر بالا انتخاب شود چون نمیتوان برگشت. درغیراینصورت به سمت چپ می رویم
    {
        if (jahateHarekat == 1) //اگر به سمت راست در حال حرکت هستیم
        {
            return 4;
        }
        else
            return 3;
    }
    else if (count == 5) //اگر مسیر بالا و پایین باز باشد
    {
        if (jahateHarekat == 4)
        {
            return 4;
        }
        else
            return 2;
    }
    else if (count == 9) //اگر مسیر بالا و راست باز باشد
    {
        if (jahateHarekat == 2)
        {
            return 1;
        }
        else
            return 4;
    }
    else if (count == 6) //اگر مسیر چپ و پایین باز باشد
    {
        if (jahateHarekat == 1)
        {
            return 2;
        }
        else
            return 3;
    }
    else if (count == 10) //اگر مسیر راست و چپ باز باشد
    {
        if (jahateHarekat == 1)
        {
            return 1;
        }
        else
            return 3;
    }
    else if (count == 12) //اگر مسیر راست و پایین باز باشد
    {
        if (jahateHarekat == 4)
        {
            return 1;
        }
        else
            return 2;
    }
    //سه راهی ها را محاسبه می کنیم
    else if (count == 7) //اگر مسیر های بالا - چپ-پایین باز باشد
    {
        tas = (rand() % 2) + 1; //یک عدد تصادفی می سازیم که1 یا 2 است
        if (jahateHarekat == 1) //اگر به راست میرویم به تاس نگاه می کنیم اگر یک باشد بالا می رویم و اگر 2 باشد به پایین میرویم
        {
            if (tas == 1)
            {
                return 4;
            }
            else
                return 2;
        }
        else if (jahateHarekat == 4)
        {
            if (tas == 1)
            {
                return 4;
            }
            else
                return 3;
        }
        else if (jahateHarekat == 2)
        {
            if (tas == 1)
            {
                return 2;
            }
            else
                return 3;
        }
    }
    else if (count == 11) //اگر مسیرهای چپ-بالا-راست باز باشد
    {
        tas = (rand() % 2) + 1;
        if (jahateHarekat == 1)
        {
            if (tas == 1)
            {
                return 4;
            }
            else
                return 1;
        }
        else if (jahateHarekat == 2)
        {
            if (tas == 1)
            {
                return 1;
            }
            else
                return 3;
        }
        else if (jahateHarekat == 3)
        {
            if (tas == 1)
            {
                return 4;
            }
            else
                return 3;
        }
    }
    else if (count == 13) //اگر مسیرهای بالا-راست -پایین باز باشد
    {
        tas = (rand() % 2) + 1;
        if (jahateHarekat == 2)
        {
            if (tas == 1)
            {
                return 1;
            }
            else
                return 2;
        }
        else if (jahateHarekat == 4)
        {
            if (tas == 1)
            {
                return 4;
            }
            else
                return 1;
        }
        else if (jahateHarekat == 3)
        {
            if (tas == 1)
            {
                return 2;
            }
            else
                return 4;
        }
    }
    else if (count == 14) //اگر مسیرهای راست-پایین-چپ باز باشد
    {
        tas = (rand() % 2) + 1;
        if (jahateHarekat == 1)
        {
            if (tas == 1)
            {
                return 1;
            }
            else
                return 2;
        }
        else if (jahateHarekat == 4)
        {
            if (tas == 1)
            {
                return 1;
            }
            else
                return 3;
        }
        else if (jahateHarekat == 3)
        {
            if (tas == 1)
            {
                return 2;
            }
            else
                return 3;
        }
    }
    else if (count == 15) //اگر سر چهار راه باشیم
    {
        tas = (rand() % 3) + 1;
        if (jahateHarekat == 1)
        {
            if (tas == 1)
            {
                return 4;
            }
            else if (tas == 2)
            {
                return 1;
            }
            else
                return 2;
        }
        else if (jahateHarekat == 4)
        {
            if (tas == 1)
            {
                return 3;
            }
            else if (tas == 2)
            {
                return 1;
            }
            else
                return 4;
        }
        else if (jahateHarekat == 3)
        {
            if (tas == 1)
            {
                return 4;
            }
            else if (tas == 2)
            {
                return 3;
            }
            else
                return 2;
        }
        else if (jahateHarekat == 2)
        {
            if (tas == 1)
            {
                return 3;
            }
            else if (tas == 2)
            {
                return 2;
            }
            else
                return 1;
        }
    }
}
//یافتن مسیرهای باز برای روح در چهار جهت اصلی
//اگر به بالا راه داشته باشیم 1،چپ 2،پایین 4وراست 8 را جمع کرده می فرستیم
//از روی این مجموع جهاتی که باز است و می توان حرکت کرد را می یابیم
int Ghost::masirhayeMojaver(int map[22][19]) //
{
    int count = 0;
    if (map[(int)(ceil((y - 200) / 24.9) - 1)][(int)ceil((x - 20) / 25)] != 2) //اگر سمت بالا راه داریم
    {
        count += 1;
    }
    if (map[(int)(ceil((y - 200) / 24.9))][(int)(ceil((x - 20) / 25) - 1)] != 2) //اگرسمت چپ راه داریم
    {
        count += 2;
    }
    //اگر سمت پایین راه داریم
    if (map[(int)(ceil((y - 200) / 24.9) + 1)][(int)ceil((x - 20) / 25)] != 2 && map[(int)(ceil((y - 200) / 24.9) + 1)][(int)ceil((x - 20) / 25)] != 5)
    {
        count += 4;
    }
    if (map[(int)(ceil((y - 200) / 24.9))][(int)(ceil((x - 20) / 25) + 1)] != 2) //اگر سمت راست راه داریم
    {
        count += 8;
    }
    return count;
}
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
class Ghost : public Drawable
{
private:
    float x;
    float y;

    sf::Sprite mSprite;

    float sorat;

    int jahateHarekat;
    Color color;
    int status;

public:
    Ghost(float x, float y, const sf::Texture &playerTexture, int jahateHarekat, float sorat, int status);
    ~Ghost();
    void taeineJahat(int map[22][19], int, bool);
    int masirhayeMojaver(int map[22][19]);
    int masireShansi(int map[22][19]);
    virtual void draw(RenderTarget &, RenderStates) const;
    void ShoroeTars();
};
void Ghost::ShoroeTars()
{
    if (jahateHarekat == 1)
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
void Ghost::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
Ghost::Ghost(float x, float y, const Texture &playerTexture, int jahateHarekat = 1, float sorat = 1, int status = 1)
{
    this->x = x;
    this->y = y;
    this->jahateHarekat = jahateHarekat;
    this->sorat = sorat;
    this->status = status;
    mSprite.setTexture(playerTexture);
}

Ghost::~Ghost()
{
}
void Ghost::taeineJahat(int map[22][19], int gameHarekat, bool isGhostsScare)
{
    if ((int)ceil((x - 20) / 25) == 0 && (int)ceil((y - 200) / 24.9) == 10 && jahateHarekat == 3)
    {
        x = 20 + 18 * 25;
    }
    if ((int)ceil((x - 20) / 25) == 18 && (int)ceil((y - 200) / 24.9) == 10 && jahateHarekat == 1)
    {
        x = 20;
    }

    if (jahateHarekat == 1)
    {
        if (map[(int)ceil((y - 200) / 24.9)][(int)ceil((x - 20 + (10 * sorat)) / 25)] != 2)
        {
            x += (0.1 * sorat);

            jahateHarekat = masireShansi(map);
        }
        else
        {
            jahateHarekat = masireShansi(map);
        }
    }
    else if (jahateHarekat == 2)
    {
        if (map[(int)ceil((y - 200 + (10 * sorat)) / 24.9)][(int)ceil((x - 20) / 25)] != 2 && map[(int)ceil((y - 200 + (10 * sorat)) / 24.9)][(int)ceil((x - 20) / 25)] != 5)
        {
            y += (0.1 * sorat);

            jahateHarekat = masireShansi(map);

            y += (0.1 * sorat);
        }
        else
            jahateHarekat = masireShansi(map);
    }
    else if (jahateHarekat == 3)
    {
        if (map[(int)ceil((y - 200) / 24.9)][(int)ceil((x - 20 - (10 * sorat)) / 25)] != 2)
        {
            x -= (0.1 * sorat);

            jahateHarekat = masireShansi(map);
        }
        else
            jahateHarekat = masireShansi(map);
    }
    else if (jahateHarekat == 4)
    {
        if (map[(int)ceil((y - 200 - (10 * sorat)) / 24.9)][(int)ceil((x - 20) / 25)] != 2)
        {
            y -= (0.1 * sorat);

            jahateHarekat = masireShansi(map);
        }
        else
            jahateHarekat = masireShansi(map);
    }
    mSprite.setPosition(x, y);
    if (isGhostsScare)
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
    else
    {
        if (jahateHarekat == 1)
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
        else if (jahateHarekat == 2)
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
        else if (jahateHarekat == 3)
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
        else if (jahateHarekat == 4)
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

int Ghost::masireShansi(int map[22][19])
{
    srand(time(0));
    int count = masirhayeMojaver(map);
    int tas = 0;
    if (count == 1 || count == 2 || count == 4 || count == 8)
    {
        return jahateHarekat;
    }
    else if (count == 3)
    {
        if (jahateHarekat == 1)
        {
            return 4;
        }
        else
            return 3;
    }
    else if (count == 5)
    {
        if (jahateHarekat == 4)
        {
            return 4;
        }
        else
            return 2;
    }
    else if (count == 9)
    {
        if (jahateHarekat == 2)
        {
            return 1;
        }
        else
            return 4;
    }
    else if (count == 6)
    {
        if (jahateHarekat == 1)
        {
            return 2;
        }
        else
            return 3;
    }
    else if (count == 10)
    {
        if (jahateHarekat == 1)
        {
            return 1;
        }
        else
            return 3;
    }
    else if (count == 12)
    {
        if (jahateHarekat == 4)
        {
            return 1;
        }
        else
            return 2;
    }
    else if (count == 7)
    {
        tas = (rand() % 2) + 1;
        if (jahateHarekat == 1)
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
    else if (count == 11)
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
    else if (count == 13)
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
    else if (count == 14)
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
    else if (count == 15)
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

int Ghost::masirhayeMojaver(int map[22][19])
{
    int count = 0;
    if (map[(int)(ceil((y - 200) / 24.9) - 1)][(int)ceil((x - 20) / 25)] != 2)
    {
        count += 1;
    }
    if (map[(int)(ceil((y - 200) / 24.9))][(int)(ceil((x - 20) / 25) - 1)] != 2)
    {
        count += 2;
    }
    if (map[(int)(ceil((y - 200) / 24.9) + 1)][(int)ceil((x - 20) / 25)] != 2 && map[(int)(ceil((y - 200) / 24.9) + 1)][(int)ceil((x - 20) / 25)] != 5)
    {
        count += 4;
    }
    if (map[(int)(ceil((y - 200) / 24.9))][(int)(ceil((x - 20) / 25) + 1)] != 2)
    {
        count += 8;
    }
    return count;
}
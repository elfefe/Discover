#ifndef VILLAGE_H
#define VILLAGE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Village
{
    public:
        Village();
        virtual ~Village();

        void Maison();

    sf::Sprite herbe;

    protected:

    private:
    sf::Texture herbe_Texture;
    string herbe_Path = "texture/sol/herbe.png";
};

#endif // VILLAGE_H

#include "Village.h"

Village::Village()
{
    //ctor
}

Village::~Village()
{
    //dtor
}

void Village::Maison()
{
    herbe_Texture.loadFromFile(herbe_Path);
    herbe_Texture.setRepeated(true);
    herbe.setTextureRect(sf::IntRect(0,0,1000,800));
    herbe.setTexture(herbe_Texture);
}

#ifdef SFML_STATIC
#endif // SFML_STATIC

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

sf::View camera;

sf::Texture gazon_Texture;
sf::Sprite gazon;

sf::Texture trees_Texture;
sf::Sprite trees;

sf::Texture indepassable_Texture;
sf::Sprite indepassable;

sf::Texture player_Texture;
sf::Sprite player;

int player_Move(float player_Speed, float sec, float anim_Time);
int func_Gazon();
int func_Trees();
int func_Indepassable();
int func_Player();
int func_Collisions();

int sprite_x = 1000;
int sprite_y = 800;
int tile = 64;
int rand_trees;
int rand_X;
int rand_Y;
float s;//Vitesse du personnage
float a = 0.3;//Vitesse de l'animation du personnage
string gazon_Path = "texture/sol/gazon.png";
string tileset_Path = "texture/tileset.png";
string arbre_Path = "texture/arbre.png";
string indepassable_Path = "texture/sol/indepassable.png";
string player_Path = "texture/player_n.png";
bool run;

int main()
{
    sf::Clock clock;
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(sprite_x, sprite_y), "DISCOVER");
    camera.reset(sf::FloatRect(0,0,sprite_x,sprite_y));
    app.setFramerateLimit(35);
    int size_x = app.getSize().x;
    int size_y = app.getSize().y;
    srand (time(0));
    rand_trees = rand() % 1000 + 0;
    func_Player();
    player.setPosition(sf::Vector2f(size_x / 2.1,size_y / 2.1));
	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }
        sf::Time elapsed = clock.getElapsedTime();
        float sec = elapsed.asSeconds();
        if(sec > a*2){
            clock.restart();
        }
        if(!run)
        {
            s = 2.1;
        }else{
            s = 4;
        }
        player_Move(s,sec, a);
        camera.setCenter(player.getPosition().x, player.getPosition().y);
        func_Collisions();
        // Charge le décor
        func_Gazon();
        func_Trees();
        trees.setScale(sf::Vector2f(2, 2));
        func_Indepassable();
        // Clear screen
        app.clear();
        // Draw the sprite// Sol
        app.draw(gazon);

        app.draw(player);

        trees.setPosition(sf::Vector2f(100, 100));
        app.draw(trees);
        func_Collisions();
        trees.setPosition(sf::Vector2f(200, 400));
        app.draw(trees);
        func_Collisions();
        trees.setPosition(sf::Vector2f(600, 300));
        app.draw(trees);
        func_Collisions();

        app.setView(camera);
        // Update the window
        app.display();
    }
    return 0;
}
// Interraction clavier
int player_Move(float player_Speed, float sec, float anim_Time)
{
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space))&&(run))
    {
        run = false;
        cout<<"0"<<endl;
    }else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space))&&(!run))
    {
        run = true;
        cout<<"1"<<endl;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        player.move(0,-player_Speed);
       if(sec < anim_Time){
            player.setTextureRect(sf::IntRect(35,148,31,51));
       }else if(sec >= anim_Time){
            player.setTextureRect(sf::IntRect(100,148,31,55));
        }else{
            player.setTextureRect(sf::IntRect(0,150,31,51));
        }
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        player.move(0,player_Speed);
       if(sec < anim_Time){
            player.setTextureRect(sf::IntRect(35,0,31,51));
       }else if(sec >= anim_Time){
            player.setTextureRect(sf::IntRect(100,0,35,51));
        }else{
            player.setTextureRect(sf::IntRect(0,0,31,51));
        }
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.move(-player_Speed,0);
       if(sec < anim_Time){
            player.setTextureRect(sf::IntRect(35,52,34,48));
       }else if(sec >= anim_Time){
            player.setTextureRect(sf::IntRect(102,52,34,48));
        }else{
            player.setTextureRect(sf::IntRect(0,51,34,49));
        }
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.move(player_Speed,0);
       if(sec < anim_Time){
            player.setTextureRect(sf::IntRect(35,100,34,48));
       }else if(sec >= anim_Time){
            player.setTextureRect(sf::IntRect(105,100,34,48));
        }else{
            player.setTextureRect(sf::IntRect(0,100,34,48));

        }
    }else{
        player.setTextureRect(sf::IntRect(0,0,33,51));
    }
    return 0;
}
int func_Collisions()
{
    if(player.getPosition().x <= 0) {
        player.setPosition(0, player.getPosition().y);
    }
    if(player.getPosition().y <= 0){
        player.setPosition(player.getPosition(). x, 0);
    }
    if(player.getPosition().x <= sprite_x/2)
    {
        camera.setCenter(sprite_x / 2, camera.getCenter().y);
    }
    if(player.getPosition().y <= sprite_y / 2)
    {
        camera.setCenter(camera.getCenter().x, sprite_y / 2);
    }
    if((player.getPosition().x <= trees.getPosition().x+96) && (player.getPosition().x >= trees.getPosition().x)&&(player.getPosition().y <= trees.getPosition().y+131) && (player.getPosition().y >= trees.getPosition().y))
    {
        if((player.getPosition().x <= trees.getPosition().x+60)&&(player.getPosition().x >= trees.getPosition().x+50))
        {
            player.setPosition(trees.getPosition().x+60, player.getPosition().y);
        }
        if((player.getPosition().x >= trees.getPosition().x+20)&&(player.getPosition().x <= trees.getPosition().x+30))
        {
            player.setPosition(trees.getPosition().x+20, player.getPosition().y);
        }
        if((player.getPosition().y<= trees.getPosition().y+100)&&(player.getPosition().y >= trees.getPosition().y+90))
        {
            player.setPosition(player.getPosition().x , trees.getPosition().y+80);
        }
        if((player.getPosition().y >= trees.getPosition().y+130)&&(player.getPosition().y <= trees.getPosition().y+140))
        {
            player.setPosition(player.getPosition().x, trees.getPosition().y+130);
        }
    }
    return 0;
}
int func_Gazon()
{
    gazon_Texture.loadFromFile(gazon_Path);
    gazon_Texture.setRepeated(true);
    if((player.getPosition().x >= 0)||(player.getPosition().y >= 0)){
        gazon.setTextureRect(sf::IntRect(0,0,tile+camera.getCenter().x+sprite_x,tile+camera.getCenter().y+sprite_y));
    }else{
        gazon.setTextureRect(sf::IntRect(0,0,tile,tile));
    }
    gazon.setTexture(gazon_Texture);
    return 0;
}
int func_Trees()
{
    trees_Texture.loadFromFile(arbre_Path);

    trees.setTextureRect(sf::IntRect(0,0,90,125));
    trees.setTexture(trees_Texture);
    return 0;
}
int func_Indepassable()
{
    indepassable_Texture.loadFromFile(indepassable_Path);
    indepassable_Texture.setRepeated(true);
    indepassable.setTextureRect(sf::IntRect(0,0,sprite_x,192));
    indepassable.setTexture(indepassable_Texture);
    return 0;
}
int func_Player()
{
    player_Texture.loadFromFile(player_Path);
    player.setTextureRect(sf::IntRect(0,0,35,51));
    player.setTexture(player_Texture);
    return 0;
}

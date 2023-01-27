#include <iostream>
#include "Mario.h"
#include "Tile.h"
#include <vector>
#include <SFML/Graphics.hpp>

int main() {
    sf::Clock Clock;

    int windowWidth = 1024;

    int windowHeight = 896;

    bool restart = false;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Super Mario World");

    Mario mario;

    Entity entity;

    sf::Texture texture;
    texture.loadFromFile("Resources/Tilesheet.png");

    sf::Texture enemyset;
    enemyset.loadFromFile("Resources/enemies_sprites.png");

    entity.LoadFromFile("Levels/1-1.wd", sf::Color(26, 128, 182, 255), mario, entity, texture, enemyset);

    sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));
    unsigned view_x = 0;

    //Main Loop:
    while (window.isOpen())
    {
        sf::Event Event;

        float deltaTime = Clock.restart().asSeconds();

        //Event Loop:
        while (window.pollEvent(Event))
        {
            {
                if (Event.type == sf::Event::Closed)
                    // Someone closed the window- bye
                    window.close();
            }
        }
        if (mario.getPosition().x >= windowWidth / 2)
        {
            view_x = mario.getPosition().x - windowWidth / 2;
        }
        view.reset(sf::FloatRect(view_x, 0, windowWidth, windowHeight));
        mario.vision.setPosition(view_x, 0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            restart = true;
        }

        window.setView(view);
        mario.update(deltaTime, entity.Sprite_v);
        window.clear(sf::Color(26, 128, 182, 255));
        entity.DrawToScreen(window, mario, deltaTime, entity.Sprite_v);
        window.display();
    }
}
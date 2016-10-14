//
//  main.cpp
//  t01
//
//  Created by Cordry, Julien on 30/09/2016.
//  Copyright © 2016 Cordry, Julien. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    sf::CircleShape shape(500.f);
    shape.setFillColor(sf::Color::Yellow);
    
    //Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("./Assets/image.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    
    //Create a graphical text to display
    /*sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return EXIT_FAILURE;
    }*/
    
    //Load a music to play
    /*sf::Music music;
    if (!music.openFromFile("music.ogg")) {
        return EXIT_FAILURE;
    }*/
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        
        window.draw(shape);
        window.draw(sprite);
        
        window.display();
    }
    
    return EXIT_SUCCESS;
}
 
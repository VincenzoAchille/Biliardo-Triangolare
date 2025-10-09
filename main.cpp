//camelCase
#include "ball.hpp"
#include "Methods.cpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

int main()
{   
    float center[2]{100, 450};
    float alfa{}; //è l'angolo delle rette
    auto controllo = controlAngle(alfa, 0 , 1.67);
    float r1{200.};
    float r2{100.};
    float l{1000.};

    
    //parte di SFML
    sf::Vertex upperBound[] = //preso da Chat
    {
        sf::Vertex(sf::Vector2f(center[0], center[1] + r1), sf::Color::White),
        sf::Vertex(sf::Vector2f(center[0] + l, center[1] + r2), sf::Color::White)
    };
    sf::Vertex lowerBound[] = //preso da Chat
    {
        sf::Vertex(sf::Vector2f(center[0], center[1] - r1), sf::Color::White),
        sf::Vertex(sf::Vector2f(center[0] + l, center[1] - r2), sf::Color::White)
    };


    sf::RenderWindow window(sf::VideoMode(1600, 900), "Triangular Billiards"); //aggiustare l'inizializzazione
    sf::CircleShape shape1(25.f);
    shape1.setPosition(center[0],center[1]);
    shape1.setFillColor(sf::Color::Cyan);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(upperBound, 2, sf::Lines); //preso da Chat
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();
    }

    return 0;
}
        

    

#ifndef METHODS_CPP
#define METHODS_CPP
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "ball.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

inline bool controlAngle(float angle, float a, float b){
    if(a < angle < b){
        return 0;
        std::cout << "angolo fuori dal range" << '\n';
        exit(1);
    }else{
        return 1;
    }
}

inline int sgn(float x) {
return (x > 0) - (x < 0);
}

inline void pause(){
    int a;
    std::cin >> a;
    exit(1);
}

inline void Dynamics(ball b1, float m, float center[2], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, float t){
    
    sf::CircleShape shape1(10.f);
    shape1.setPosition(center[0] + b1.getX(),center[1] - b1.getY()); //da rivedere l'inizializzazione
    shape1.setFillColor(sf::Color::Cyan);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //std::cout << a1.positionY(i, m) << ", " << a1.getX() << '\n';
        shape1.setPosition(center[0] + b1.positionX(t), center[1]- b1.positionY(t, m)); // non chiarissimo cosa faccia l'equazione di Giacomini, forse conta gia y0
        window.clear();
        window.draw(upperBound, 2, sf::Lines); //preso da Chat
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();
        t++;
    }


}
#endif
#include "ball.hpp"
#include "Methods.cpp"
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
void ball::dynamicsInizialization(){

}
void endingDynamics(){
     while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        shape1.setPosition(center[0] + positionX(t), center[1]- positionY(t)); 
        window.clear();
        window.draw(upperBound, 2, sf::Lines); //preso da Chat
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();

        if(std::abs((shape1.getPosition()).x -center[0] - impact[0]) < 12. && (std::abs((-shape1.getPosition()).y +center[1] -impact[1]) < 12.)){
            std::cout << "la pallina ha urtato!" << '\n';
            std::cout << "direzione pre update: " << Direction << '\n';
            updateDirection();
            std::cout << "direzione post update: " << Direction << '\n';
            ball help(x,y,m);
            help.collision(direction); 
            postCollisionM(direction, i );

            x = help.getX();
            y = help.getY();
            break;
            
            
        }else{
            t++;
        }}
}

void ball::Dynamics(float center[], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, int &t, sf::CircleShape &shape1,bool selected) {

    if(selected == 0){ 
       endingDynamics(center, upperBound, lowerBound, window,t,shape1);
    }
    else{
       collidingDynamics(center, upperBound, lowerBound, window,t,shape1);
    }

}
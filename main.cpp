//camelCase

#include "ball.hpp"
#include "Methods.cpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

// osservazione: potrei creare un sistema con delle variabili generali r1,r2,l e poi tramite il polimorfismo dividerlo in 2 classi ball e grafica
int main()
{   
    float center[2]{300, 450};
    const float pi = 3.141592653589793;
    float r1{200};
    float r2{100};
    float l{1000};
    float y0{-100};
    float vx{2};
    float vy{3};
    float theta0{-0.7};
    float m = std::tan(theta0);
    float v{5};

    rangeValidity(y0, -r1,r1);
    rangeValidity(theta0, -pi/2,pi/2);
    ball::setr1(r1);  
    ball::setr2(r2);
    ball::setl(l);

    //parte di SFML (setting)
    sf::Vertex upperBound[] 
    {
        sf::Vertex(sf::Vector2f(center[0], center[1] - ball::getr1()), sf::Color::White),
        sf::Vertex(sf::Vector2f(center[0] + ball::getl(), center[1] - ball::getr2()), sf::Color::White)
    };
    sf::Vertex lowerBound[] = //preso da Chat
    {
        sf::Vertex(sf::Vector2f(center[0], center[1] + ball::getr1()), sf::Color::Red),
        sf::Vertex(sf::Vector2f(center[0] + ball::getl(), center[1] + ball::getr2()), sf::Color::Red)
    };
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Biliardo Triangolare"); 

    //inizializzazione ball e shape
    ball b1(0, y0, m);
    sf::CircleShape shape1(10.f);
    shape1.setPosition(center[0],center[1] - y0);
    shape1.setFillColor(sf::Color::Cyan);
    
    //parte dinamica
    
    float t{0};
    float h{0};
    float T{0};

for(int i{0}; i >= 0; i++){

    bool selectedMotion = b1.selector(); 

    //dynamics starting
    if(selectedMotion == 0){ 
       b1.endingDynamics(center, upperBound, lowerBound, window,t,shape1,h,T,v);
    }
    else{
        b1.collidingDynamics(center, upperBound, lowerBound, window,t,shape1,h,T,v);
    }
    std::cout << "valore di controllo = " << i << '\n';
    i++;
    if(i > 15){
        myPause();
    }
}











    
}


        

    

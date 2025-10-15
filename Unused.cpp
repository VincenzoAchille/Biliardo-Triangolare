#include "ball.hpp"
#include "Methods.cpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

float ball::newM(int direction, bool updown){float alfa = angleRespectNormal();
    float theta = std::atan(m);
    float A;
    /*if(m*Direction > 0){
        updown = 1;
    }else{
        updown = 0;
    }*/
    if (m < 0) {
        theta += M_PI;
        if(theta < 0)
        {
        std::cout << "calcolo angolo sbagliato" << '\n';}
          // Ora tra π/2 e 3π/2
    }
    if(direction > 0){
        if(updown == 1){
            A = 2*alfa + theta;
        }else{
            A = -2*alfa +theta;
        }
    } else{
        if(updown == 1){
            A = -2*alfa + theta;
        }else{
            A = 2*alfa +theta;
        }

    }
    if (A < 0) A += 2 * pi;
    return std::tan(A);
    
    
};
int main(){
    float center[2]{300, 450};
    //float alfa{2}; //è l'angolo delle rette
    const float pi = 3.141592653589793;
    ball::setr1(200);  //mettere dei controlli sui range di r1,r2,l devono dipendere dalle dimensioni della finestra
    ball::setr2(100);
    ball::setl(1000);
    float y0{0.};
    float vx{2};
    float vy{3};
    float theta{0.7};
    float m = std::tan(theta);
    int t{0};
    int direction{0};
    bool updown{0};
    sf::Vertex upperBound[] = //preso da Chat
    {
        sf::Vertex(sf::Vector2f(center[0], center[1] - ball::getr1()), sf::Color::White),
        sf::Vertex(sf::Vector2f(center[0] + ball::getl(), center[1] - ball::getr2()), sf::Color::White)
    };
    sf::Vertex lowerBound[] = //preso da Chat
    {
        sf::Vertex(sf::Vector2f(center[0], center[1] + ball::getr1()), sf::Color::Red),
        sf::Vertex(sf::Vector2f(center[0] + ball::getl(), center[1] + ball::getr2()), sf::Color::Red)
    };
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Triangular Billiards"); //aggiustare l'inizializzazione

    ball b1(0, y0, m);
    sf::CircleShape shape1(10.f);
    shape1.setPosition(center[0]+500,center[1] - y0);
    shape1.setFillColor(sf::Color::Cyan);
    std::cout << "parametri all'inizio di un while" " x=" << b1.getX() << " y=" << b1.getY() << " m=" << b1.getM() << " direction= " << b1.getDirection() << '\n';
    ball bParameters = b1; //mi serve il copy constuctor
    bool a = b1.selector(1,b1.getDirection()); 
    bParameters.collision();  
    shape1.setPosition(center[0] + b1.getX(),center[1] - b1.getY()); 
    shape1.setFillColor(sf::Color::Cyan);
    float impact[2] = {bParameters.getX(), bParameters.getY()};

    int h;
    int T = t;
    if(b1.getDirection() < 0){t = 0;}


    while (window.isOpen())
    {   
        if(b1.getDirection() > 0){
        h = t;
    }else{
        h = T -t;
    }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
         float newX = b1.positionX(h);
        float newY = b1.positionY(h);
        shape1.setPosition(center[0] + newX, center[1] - newY); 
        
        
        window.clear();
        window.draw(upperBound, 2, sf::Lines);
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();
        
        if(std::abs((shape1.getPosition()).x -center[0] - impact[0]) < 12. && (std::abs((-shape1.getPosition()).y +center[1] -impact[1]) < 12.)){
            while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            float a = b1.newM(direction, updown);
            std::cout << "il nuovo coefficiente è: " << a << '\n';
        }
    }

        }else{
            t++;
        }
    }}

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
    float center[2]{100, 450};
    float alfa{2}; //è l'angolo delle rette
    const float pi = 3.141592653589793;
    ball::setr1(200);  //mettere dei controlli sui range di r1,r2,l devono dipendere dalle dimensioni della finestra
    ball::setr2(50);
    ball::setl(1200);
    float y0{-100};
    float vx{2};
    float vy{3};
    float theta{1};
    float m = std::tan(theta);

    if(-ball::getr2() < ball::getl()*m + y0 &&  ball::getl()*m + y0 < ball::getr2()){
        std::cout << "no urti !" << '\n';
    }
    //parte di SFML (setting)
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

    //inizializzazione ball e shape
    ball b1(0, y0, m);
    sf::CircleShape shape1(10.f);
    shape1.setPosition(center[0],center[1] - y0);
    shape1.setFillColor(sf::Color::Cyan);
    
    //parte dinamica
    
    int t{0};
    int i{0};

while(i >= 0){
    std::cout << "x,y inizio segmento all'inizio di un ciclo while: " << b1.getX() << ", " << b1.getY() << '\n';
    //bool updown = sgn(b1.getY()); //c'è un bell'errore sui tipi
    ball bParameters = b1; //mi serve il copy constuctor
    bool a = b1.selector(1,bParameters.direction(b1)); //1 se verso dx 0 se verso sx
    bParameters.collision(a);
    
    //std::cout << "end: " << bParameters.getX() << ", " << bParameters.getY() << ", " << bParameters.direction(b1) << ", " << b1.selector(1,bParameters.direction(b1)) << '\n';
    
    std::cout << "x,y inizio segmento prima del controllo di collision:" << b1.getX() << ", " << b1.getY() << '\n';
    //dynamics starting
    if(a == 0){ 
       std::cout << "la pallina sta per fuggire!" << '\n';
       //la pallina evolve dinamicamente, e poi il programma si ferma
       b1.endingDynamics(center, upperBound, lowerBound, window,t,shape1,bParameters,bParameters.direction(b1));
    }
    else{
        //std::cout << "la pallina sta per urtare!" << '\n';
        //evolve: l'equazioni sono uguali sia per il primo che per il secondo
        //so gia che impatta. Quindi le coordinate dell'impatto saranno date aggiornando l'oggetto con collision.
        b1.collidingDynamics(center, upperBound, lowerBound, window,t,shape1,bParameters,bParameters.direction(b1), i);
        //se coincidono break, aggiorna ball e riparte il ciclo (devo implementare un aggiornamento di m)
    }
    std::cout << "valore di controllo = " << i << '\n';
    i++;
    if(i > 10){
        pause();
    }
}











    
}
    
    //secondo urto

        

    

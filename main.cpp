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
    // float alfa{}; //è l'angolo delle rette
    // auto controllo = controlAngle(alfa, 0 , 1.67);

    ball::setr1(300);  //mettere dei controlli sui range di r1,r2,l devono dipendere dalle dimensioni della finestra
    ball::setr2(100);
    ball::setl(800);
    float y0{-200};
    float vx{2};
    float vy{3};
    float theta{1.2};
    float m = std::tan(theta);
    //float xu = (y0 - ball::getr1())/(0.5 * (ball::getr2() -ball::getr1()) -m); //da implementare per angoli negativi
    //float yu = m*xu + y0;
    //ball test(0.,y0,vy,vx,0);
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

    //inizializzazione ball con shape
    ball b1(0, y0,vx,vy,0.);
    //a1.firstCollision(theta, y0);   //inizializzo i parametri per l'eq di Giacomini
    sf::CircleShape shape1(10.f);
    shape1.setPosition(center[0],center[1] - y0);
    shape1.setFillColor(sf::Color::Cyan);
    
    //parte dinamica
    //inizializzazione selection
    int t{0};
    //bool updown = sgn(b1.getY()); //c'è un bell'errore sui tipi
    ball bParameters = b1; //mi serve il copy constuctor
    bParameters.collision(m);
    float dir = bParameters.getX() - b1.getX();
    std::cout << b1.getX() << ", " << bParameters.getX() << '\n';
    bool direction;
    if(sgn(dir) < 0){
        direction = 0;
    }else{
        direction = 1;
    }
    bool a = b1.selector(m, 1, direction); //c'è qualcosa che non va con selector
    //std::cout << b1.getX() << ", " << b1.getY() << ", " << m*(-b1.getX())+b1.getY() << ", " << ball::getr1() << "," <<   '\n';


    if(a == 0){ 
       std::cout << "la pallina sta per fuggire!" << '\n';
       //la pallina evolve dinamicamente, e poi il programma si ferma
       Dynamics(b1,m,center, upperBound, lowerBound, window,t);
       pause();
    }
    else{
        float m1 = m; 
        std::cout << "la pallina sta per urtare!" << '\n';
        //evolve: l'equazioni sono uguali sia per il primo che per il secondo
        //so gia che impatta. Quindi le coordinate dell'impatto saranno date aggiornando l'oggetto con collision.

        float impact[2] = {bParameters.getX(), bParameters.getY()}; // attenzione: devo passare by reference?
        //una prima versione mi calcola solo l'impatto
        //un altra aggiorna la ball
        //ad ogni iterazione controlla se x,y position coincidono con collision -> se lo voglio fare con Dynamics è più complesso
        while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //std::cout << a1.positionY(i, m) << ", " << a1.getX() << '\n';
        shape1.setPosition(center[0] + b1.positionX(3*t), center[1]- b1.positionY(3*t, m)); // non chiarissimo cosa faccia l'equazione di Giacomini, forse conta gia y0
        window.clear();
        window.draw(upperBound, 2, sf::Lines); //preso da Chat
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();
        bool K = std::abs((shape1.getPosition()).x -center[0] - impact[0] )< 5.;
        bool H = std::abs((shape1.getPosition()).y +center[1] -impact[1]) < 5.;
        std::cout << -(shape1.getPosition()).y + center[1] << ", " << impact[1] << "," << H << ", "<<std::abs(-(shape1.getPosition()).y +center[1] -impact[1]) <<  '\n';
        //scrivere la condizione in modo più semplice -> posso usare gli abs
        //osservazione: se il programma funziona basta avere la condizione sulle x e non anche sulle y. E'un controllo ulteriore ma perdo potenza di calcolo. Cosa vuole Giacomo?
        if(std::abs((shape1.getPosition()).x -center[0] - impact[0]) < 5. && (std::abs((-shape1.getPosition()).y +center[1] -impact[1]) < 5.)){
            std::cout << "la pallina ha urtato!" << '\n';
            break;
            
        }else{
            t++;
        }
        
    }
        //se coincidono break, aggiorna ball e riparte il ciclo (devo implementare un aggiornamento di m)
    }











    /*while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //std::cout << a1.positionY(i, m) << ", " << a1.getX() << '\n';
        shape1.setPosition(center[0] + b1.positionX(i), center[1]- b1.positionY(i, m)); // non chiarissimo cosa faccia l'equazione di Giacomini, forse conta gia y0
        window.clear();
        window.draw(upperBound, 2, sf::Lines); //preso da Chat
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();
        i++;
    }*/
}
    
    //secondo urto

        

    

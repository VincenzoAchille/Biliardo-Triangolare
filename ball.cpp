#include "ball.hpp"
#include "Methods.cpp"
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

float ball::l = 1.; //metto 1 per non far esplodere A
float ball::r1 = 0.5;
float ball::r2 = 1.;
float ball::mGiac = l/(r2-r1);

ball::ball(float _x, float _y, float _m){
    x = _x;
    y = _y;
    m = _m;
};

bool ball::direction(ball iniziale){
    float dir = x - iniziale.getX();
    if(sgn(dir) < 0){
        return 0; //verso sx
    }else{
        return 1; //verso dx
    }
    
}
void ball::postFirstCollisionM(){

}

void ball::postCollisionM(bool direction, int i){
    /*float B = postCollisionAngle();
    std::cout << "postCollisionAngle=" << B << '\n';
    int a;
    if(direction == 0){a = -1;}
    else{a=1;}
    std::cout << "direction sign=" << a << '\n';
    float m2 = mGiac * (-sgn(y));
    float m3 = (m2 + B)/(1-m2*B); //si possono invertire i segni e si ottiene un altra retta: Attenzione!
    std::cout << "new m=" << m3 << '\n';*/
    int t;
if (i % 2 == 0) {
    t = 1;   // se i è pari
} else {
    t = -1;  // se i è dispari
}
    float m3 = - 1.3*m;
    this->m = m3;
}

float ball::postCollisionAngle(){ //non ho implementato il +,-
    float m2 = mGiac * (-(y > 0) + (y < 0));  //da problemi se y == 0
    return std::abs((m2-m)/(1+m*m2)) * sgn(m2); //vera se mGiac > 0
 
}


void ball::nCollision(bool direction){      //le nCollision mi updatano i valori dell'urto
    if(sgn(y) >= 0){
        std::cout << "chiamata 1parte nCollision" << '\n';
        float xu = x;
        x = (-r1-y+m*x)/(m+(r2-r1)/l);
        y = m*(x-xu) + y;
        std::cout << "valori fine segmento:" << x << ", " << y << '\n';
    }
    else if(sgn(y) < 0){
        std::cout << "chiamata 2parte nCollision" << '\n';
        float xu = x;
        x = (r1-y+m*x)/(m-(r2-r1)/l);
        y = m*(x-xu) + y;
        std::cout << "valori fine segmento:" << x << ", " << y << '\n';
    }

}
void ball::firstCollision(){  //tiene conto se l'urto è sopra o sotto
       //questa versione vale se la prima inizializzazione di ball è a x=0, y = y0;
        if(m >= 0.){                           
            x = (y - r1)/((r2-r1)/l -m);
            y = m*x + y;
        }
        else if(m < 0.){
            x = (y + r1)/((r1-r2)/l -m);
            y = m*x + y;
    
        }
    }

void ball::collision(bool direction){
    if(std::abs(x) < 1e-2){
        firstCollision();
        std::cout << "firstCollision" << '\n';
    }else{
        nCollision(direction);
        std::cout << "nCollision" << '\n';
    }
}



    bool ball::selector(bool updown, bool direction) {  //funzione da Chat
    std::cout << "\n=== Entrata in selector ===\n";
    std::cout << "x=" << x << " y=" << y << " m=" << m << direction << '\n';

    float M;

    if (std::abs(x) < 1e-2) {
    
        std::cout << "→ Caso FirstImpact (x=" << x << " < 1e-2)\n";
    } else {
        //postCollisionM(direction);
        std::cout << "→ Caso nImpact (x=" << x << " >= 1e-2)\n";
    }

    //std::cout << "Valori attuali: M=" << m << " l=" << l << " r1=" << r1 << " r2=" << r2 << '\n';

    // --- ramo per updown == 1 ---
    if (updown == 1) {
        //std::cout << "→ Entrato in ramo updown == 1\n";

        if ((m * (l - x) + y > -r2 && m * (l - x) + y < r2) && direction) {
            //std::cout << "trigger dx (updown==1)\n";
            return 0;
        }
        if ((m * (-x) + y > -r1 && m * (-x) + y < r1) && !direction) {
            //std::cout << "trigger sx (updown==1)\n";
            return 0;
        }
        /*if (M * (-x) + y < -r1 && !direction) {
            std::cout << "⚠ errore: palla non rimbalza (sx)\n";
            return 0;
        }
        if (M * (l - x) + y < -r2 && direction) {
            std::cout << "⚠ errore: palla non rimbalza (dx)\n";
            return 0;
        }*/

        std::cout << "selector: return 1" << '\n';
        return 1;
    }

    // --- ramo per updown == 0 ---
    if (updown == 0) {
        //std::cout << "→ Entrato in ramo updown == 0\n";

        if ((m * (l - x) + y > -r2 && m * (l - x) + y < r2) && direction) {
            //std::cout << "trigger dx (updown==0)\n";
            return 0;
        }

        if ((m * (-x) + y > -r1 && m * (-x) + y < r1) && !direction) {
            //std::cout << "trigger sx (updown==0)\n";
            return 0;
        }

        /*if ((M * (-x) + y > r1) && direction) {
            std::cout << "⚠ errore: palla non rimbalza (dx, updown==0)\n";
            return 0;
        }

        if ((M * (l - x) + y > r2) && !direction) {
            std::cout << "⚠ errore: palla non rimbalza (sx, updown==0)\n";
            return 0;
        }*/    //valgono solo in nImpact

        std::cout << "selector: return 1\n";
        return 1;
    }

    // fallback di sicurezza
    //std::cout << "⚠ Caso inatteso: updown=" << updown << '\n';
    return 0;
}

void ball::endingDynamics(float center[], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, int &t, sf::CircleShape &shape1, ball &bParameters, bool direction){
    std::cout << "endingDynamics" << '\n';
    shape1.setPosition(center[0] + x,center[1] - y); //da rivedere l'inizializzazione
    shape1.setFillColor(sf::Color::Cyan);
    float impact[2] = {bParameters.getX(), bParameters.getY()};
    std::cout << "x,y fine segmento all'inizio di endingDynamics" << impact[0] << ", " << impact[1] << '\n';

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //std::cout << a1.positionY(i, m) << ", " << a1.getX() << '\n';
        shape1.setPosition(center[0] + positionX(3*t), center[1]- positionY(3*t)); // non chiarissimo cosa faccia l'equazione di Giacomini, forse conta gia y0
        window.clear();
        window.draw(upperBound, 2, sf::Lines); //preso da Chat
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();
        //sotto non ci vorrebbe impact perchè le coordinate di impatto non sono quelle di bParameters
        if(std::abs((shape1.getPosition()).x -center[0] - impact[0]) < 5. && (std::abs((-shape1.getPosition()).y +center[1] -impact[1]) < 5.)){
            std::cout << "la pallina è scappata!" << '\n';
            while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

        }else{
            t++;
        }
    }
}
void ball::collidingDynamics(float center[], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, int &t, sf::CircleShape &shape1, ball &bParameters, bool direction, int i)
{std::cout << "collidyingDynamics" << '\n';
    float impact[2] = {bParameters.getX(), bParameters.getY()}; // attenzione: devo passare by reference?
        //una prima versione mi calcola solo l'impatto
        //un altra aggiorna la ball
        //ad ogni iterazione controlla se x,y position coincidono con collision -> se lo voglio fare con Dynamics è più complesso
        shape1.setPosition(center[0] + x,center[1] - y);
        std::cout << "x,y fine segmento all'inizio di collidingDynamics" << impact[0] << ", " << impact[1] << '\n';
        while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        shape1.setPosition(center[0] + positionX(3*t), center[1]- positionY(3*t)); 
        window.clear();
        window.draw(upperBound, 2, sf::Lines); //preso da Chat
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();

        //osservazione: se il programma funziona basta avere la condizione sulle x e non anche sulle y. E'un controllo ulteriore ma perdo potenza di calcolo. Cosa vuole Giacomo?
        //std::cout << std::abs((shape1.getPosition()).x -center[0] - impact[0]) << ", " << std::abs((-shape1.getPosition()).y +center[1] -impact[1]) << '\n';
        if(std::abs((shape1.getPosition()).x -center[0] - impact[0]) < 5. && (std::abs((-shape1.getPosition()).y +center[1] -impact[1]) < 5.)){
            std::cout << "la pallina ha urtato!" << '\n';
            //b1 = bParameters;
            //std::cout << "mPostUrto=" << m <<  ", " << y <<'\n'; //c'è un problema nel calcolo del punto d'urto
            collision(direction); //quando chiamo collision ho ancora x del firstImpact
            postCollisionM(direction, i );//quando chiamo questo ho ancora i punti di impatto iniziali e sto sempre nel firstImpact
            //m=30;
            //std::cout << "x,y fine segmento alla fine di collidingDynamics" << impact[0] << ", " << impact[1] << '\n';
            

            break;
            
            
        }else{
            t++;
        }
        
    }

}



#include "ball.hpp"
#include "Methods.cpp"
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

float ball::l = 1.; //metto 1 per non far esplodere A
float ball::r1 = 0.5;
float ball::r2 = 1.;
float ball::mGiac = std::abs(l/(r2-r1));

ball::ball(float _x, float _y, float _m, int _direction){
    x = _x;
    y = _y;
    m = _m;
    Direction = _direction;
};

ball::ball(float _x, float _y, float _m){
    x = _x;
    y = _y;
    m = _m;
};

float ball::alfaMax(){
    return std::abs(atan(std::abs(1/mGiac)));
}

void ball::updateDirection(){   //quando chiamo update direction normal deve essere gia stata updata
    std::cout <<"l'angolo rispetto alla normale è: " << angleRespectNormal() << ", l'angolo limite è: " << alfaMax() << '\n';
    if(normal() < 0){
        if(angleRespectNormal() < alfaMax()){
            Direction = -1;
        }
        if(angleRespectNormal() > alfaMax()){
            Direction = 1;
        }

    }
    if(normal() > 0){
        if(angleRespectNormal() < alfaMax()){
            Direction = -1;
        }
        if(angleRespectNormal() > alfaMax()){
            Direction = 1;
        }

    }
}
/*bool ball::direction(ball iniziale){ //questo metodo di direction funziona a posteriori non mi consente di ricavare la direzione a priori
    float dir = x - iniziale.getX();
    if(sgn(dir) < 0){
        return 0; //verso sx
    }else{
        return 1; //verso dx
    }
    
}*/

float ball::normal(){
    bool updown;
    if(m*Direction > 0){
        updown = 1;
    }else{
        updown = 0;
    }
    std::cout << "updown da normal: " << updown << '\n';
    if(updown == 1){
        return std::abs(mGiac);

    }else{
        return -std::abs(mGiac);

    }
}

void ball::postCollisionM(bool direction, int i){ //vuole m pre urto, e coordinate pre urto

    
   std::cout << "Entrato in postCollisionM\n";
    std::cout << "Coordinate pre-urto: x=" << x << " y=" << y << " m=" << m << "\n";
    float N = normal();
    m = (2*N + m*N*N - m)/(1 + 2 *m*N - N*N);
    std::cout << "coeff angolare post-urto: " << m << '\n';

    
    /*float B = postCollisionAngle();
    std::cout << "postCollisionAngle=" << B << '\n';
    int a;
    if(direction == 0){a = -1;}
    else{a=1;}
    std::cout << "direction sign=" << a << '\n';
    float m2 = mGiac * (-sgn(y));
    float m3 = (m2 + B)/(1-m2*B); //si possono invertire i segni e si ottiene un altra retta: Attenzione!
    std::cout << "new m=" << m3 << '\n';*/
    /*int t;
if (i % 2 == 0) {
    t = 1;   // se i è pari
} else {
    t = -1;  // se i è dispari
}
    float m3 = - 1.3*m;*/
}

float ball::angleRespectNormal(){ //non ho implementato il +,-

    float N = normal(); //coefficiente angolare della normale
    //m è l'm pre-urto
    float M  = std::abs(m);
    return std::atan(std::abs((M-N)/(1+M*N)));
 
}


void ball::nCollision(){      //vuole le coordinate  pre urto
    std::cout << "segno della normale" << sgn(normal()) << '\n';
    if(normal() >= 0){  
        std::cout << "enter in Normal > 0" << '\n';                      //vedere come cambia dopo l'aggiunta di direction
        double xu = x;  
        x = (r1-y+m*x)/(m-(r2-r1)/l);
        y = m*(x-xu) + y;
        std::cout << "valori fine segmento:" << x << ", " << y << '\n';
    }
    else if(normal() < 0){
        std::cout << "enter in Normal < 0" << '\n';  
        double xu = x;
        x = (-r1-y+m*x)/(m+(r2-r1)/l);
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

void ball::collision(){
    if(std::abs(x) < 1e-2){
        firstCollision();
        std::cout << "firstCollision" << '\n';
    }else{
        nCollision();
        std::cout << "nCollision" << '\n';
    }
}





    bool ball::selector(bool updown, bool direction) {  //funzione da Chat
    std::cout << "\n=== Entrata in selector ===\n";
    std::cout << "x=" << x << " y=" << y << " m=" << m << "direction= " << Direction << '\n';

    float M;

    if (std::abs(x) < 1e-2) {
    
        //std::cout << "→ Caso FirstImpact (x=" << x << " < 1e-2)\n";
    } else {
        //postCollisionM(direction);
        //std::cout << "→ Caso nImpact (x=" << x << " >= 1e-2)\n";
    }

    //std::cout << "Valori attuali: M=" << m << " l=" << l << " r1=" << r1 << " r2=" << r2 << '\n';

    // --- ramo per updown == 1 ---
    if (updown == 1) {
        //std::cout << "→ Entrato in ramo updown == 1\n";

        if ((m * (l - x) + y > -r2 && m * (l - x) + y < r2) && invert(Direction)) {
            //std::cout << "trigger dx (updown==1)\n";
            return 0;
        }
        if ((m * (-x) + y > -r1 && m * (-x) + y < r1) && !invert(Direction)) {
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

        //std::cout << "selector: return 1" << '\n';
        return 1;
    }

    // --- ramo per updown == 0 ---
    if (updown == 0) {
        //std::cout << "→ Entrato in ramo updown == 0\n";

        if ((m * (l - x) + y > -r2 && m * (l - x) + y < r2) && invert(Direction)) {
            //std::cout << "trigger dx (updown==0)\n";
            return 0;
        }

        if ((m * (-x) + y > -r1 && m * (-x) + y < r1) && !invert(Direction)) {
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

void ball::timeEvolving(float center[], sf::Vertex upperBound[],sf::Vertex lowerBound[],sf::RenderWindow &window, int &t,sf::CircleShape &shape1){
    if(Direction > 0)
{
 shape1.setPosition(center[0] + positionX(Direction*t), center[1]- positionY(Direction*t)); 
        window.clear();
        window.draw(upperBound, 2, sf::Lines); //preso da Chat
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();
}else if(Direction < 0){
        const int T = t;
        std::cout << T << '\n';
        shape1.setPosition(center[0] + positionX(T-t), center[1]- positionY(T-t)); // non chiarissimo cosa faccia l'equazione di Giacomini, forse conta gia y0
        window.clear();
        window.draw(upperBound, 2, sf::Lines); //preso da Chat
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();
}
}

void ball::endingDynamics(float center[], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, int &t, sf::CircleShape &shape1, ball &bParameters, bool direction){
    std::cout << "endingDynamics" << '\n';
    shape1.setPosition(center[0] + x,center[1] - y); //da rivedere l'inizializzazione
    shape1.setFillColor(sf::Color::Cyan);
    float impact[2] = {bParameters.getX(), bParameters.getY()};
    std::cout << "x,y fine segmento all'inizio di endingDynamics" << impact[0] << ", " << impact[1] << '\n';

    int h;
    int T = t;
    if(Direction < 0){t = 0;}


    while (window.isOpen())
    {   
        if(Direction > 0){
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
        
        
        
        //std::cout << a1.positionY(i, m) << ", " << a1.getX() << '\n';
        float scale = 1.0f / std::sqrt(1 + m*m);
        float effective_t = h * scale;
        shape1.setPosition(center[0] + positionX(effective_t), center[1]- positionY(effective_t)); 
        window.clear();
        window.draw(upperBound, 2, sf::Lines); //preso da Chat
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();
        
        //sotto non ci vorrebbe impact perchè le coordinate di impatto non sono quelle di bParameters
        if(std::abs((shape1.getPosition()).x -center[0] - impact[0]) < 12. && (std::abs((-shape1.getPosition()).y +center[1] -impact[1]) < 12.)){
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
    }}


void ball::collidingDynamics(float center[], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, int &t, sf::CircleShape &shape1, ball &bParameters, bool direction, int i)
{std::cout << "collidingDynamics" << '\n';
    std::cout << "parametri all'inizio di collidingDynamics: x= " << x << "y=" << y << "direction=" <<  Direction << '\n';
    float impact[2] = {bParameters.getX(), bParameters.getY()}; // attenzione: devo passare by reference?
        //una prima versione mi calcola solo l'impatto
        //un altra aggiorna la ball
        //ad ogni iterazione controlla se x,y position coincidono con collision -> se lo voglio fare con Dynamics è più complesso
        shape1.setPosition(center[0] + x,center[1] - y);
        std::cout << "posizioni grafiche inizio collidingDynamics x= " << shape1.getPosition().x << ", y= " << shape1.getPosition().y << '\n';
         int h;
        int T = t;
        if(Direction < 0){t = 0;}

        while (window.isOpen())
    {   
        if(Direction > 0){
            h = t;
        }else{
            h = T-t;
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        double scale = 1.0f / std::sqrt(1 + m*m);
        double effective_t = h;
        //std::cout << "evoluzionePosizioni: x= " << shape1.getPosition().x << ", y= " << shape1.getPosition().y << "effective_t= " << effective_t<<'\n';
        //std::cout << "incrementi: x= " << positionX(effective_t) << ", y= " << positionY(effective_t) << "scala= " << scale << '\n';
        shape1.setPosition(center[0] + positionX(effective_t), center[1]- positionY(effective_t)); 
        window.clear();
        window.draw(upperBound, 2, sf::Lines); //preso da Chat
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();

        //osservazione: se il programma funziona basta avere la condizione sulle x e non anche sulle y. E'un controllo ulteriore ma perdo potenza di calcolo. Cosa vuole Giacomo?
        if(std::abs((shape1.getPosition()).x -center[0] - impact[0]) < 12. && (std::abs((-shape1.getPosition()).y +center[1] -impact[1]) < 12.)){
            std::cout << "la pallina ha urtato!" << '\n';
            //b1 = bParameters;
            //std::cout << "mPostUrto=" << m <<  ", " << y <<'\n'; //c'è un problema nel calcolo del punto d'urto
            std::cout << "direzione pre update: " << Direction << '\n';
            ball helpXY(x,y,m);
            ball helpDir(x,y,m);
            ball helpM(x,y,m);
            helpM.postCollisionM(Direction, i );
            helpDir.updateDirection();
            helpXY.collision();
            std::cout << "direzione post update: " << Direction << '\n';
            //std::cout << "1)m dopo help" << m << '\n';
            collision();  
            //std::cout << "2)m dopo help.collsion" << m << '\n';
            //std::cout << "3)m dopo postCollisionM" << m << '\n';
            x = helpXY.getX();
            y = helpXY.getY();
            m = helpM.getM();
            Direction = helpDir.getDirection();
            //m=30;
            std::cout << "x,y b1 alla fine di collidingDynamics" << x << ", " << y << '\n';
            

            break;
            
            
        }else{
            t++;
        }}
    }
            




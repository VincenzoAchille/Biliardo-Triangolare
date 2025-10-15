#include "ball.hpp"
#include "Methods.cpp"
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

float ball::l = 1.; 
float ball::r1 = 0.5;
float ball::r2 = 1.;
//float ball::mGiac = std::abs(l/(r2-r1));

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
    return std::abs(atan(std::abs(1/mGiac())));
}

void ball::updateDirection(){  
    float angle = angleRespectNormal();

        if(angle < alfaMax()){
            Direction = -1;
        }
        if(angle > alfaMax()){
            Direction = 1;
        }
    
}
bool ball::updown(int direction){
    if(m*direction == 0){
        return 0;
    }
    if(m*direction > 0){
        return 1;
    }else{
        return 0;
    }
}
float ball::normal(int direction, bool updown){
    if(updown == 1){
        return std::abs(mGiac());

    }else{
        return -std::abs(mGiac());

    }
}
float ball::normal(){
    bool a = updown(Direction);
    if(a == 1){
        return std::abs(mGiac());

    }else{
        return -std::abs(mGiac());

    }
}
    void ball::updateM() {
    std::cout << "Entrato in postCollisionM\n";
    std::cout << "m in entrata=" << m << "\n";
    //altro tentativo
    /*float alfa = angleRespectNormal();
    float theta = std::atan(m);
    float A;
    bool updown;
    if(m*Direction > 0){
        updown = 1;
    }else{
        updown = 0;
    }
    if (m < 0) {
        theta += M_PI;
        if(theta < 0)
        {
        std::cout << "calcolo angolo sbagliato" << '\n';}
          // Ora tra π/2 e 3π/2
    }
    if(Direction > 0){
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
    m = std::tan(A);*/
    float N = normal();
    float mAngle = std::tan(angleRespectNormal());
    std::cout << "l'angolo rispettto alla normale è: " << mAngle << '\n';
    int a = 1;
    float newM = -(a*mAngle + N)/(N*a * mAngle - 1);
    if(std::abs(newM - m) < 1e-3){
        std::cout << "triggerati coefficienti uguali" << '\n';
        a = -1;
        newM = -(a*mAngle + N)/(N*a * mAngle - 1);
        m = newM;
    }else{
        std::cout << "triggerati coefficienti diversi " << '\n';
        m = newM;
    }
    std::cout << "m in uscita: " << m << '\n';

    
}


float ball::angleRespectNormal(){ //vuole N0 e m0

    float N = normal();
    float M  = m;
    float b = std::abs(std::atan((M-N)/(1+M*N))); // con questo valore assoulto ottengo sempre l'angolo acuto
    return b;
    //return 180 * b/pi;
 
}

void ball::nCollision(){    
    if(normal() >= 0){                     
        double xu = x;  
        x = (r1-y+m*x)/(m-(r2-r1)/l);
        y = m*(x-xu) + y;
     
    }
    else if(normal() < 0){
        double xu = x;
        x = (-r1-y+m*x)/(m+(r2-r1)/l);
        y = m*(x-xu) + y;
        
    }

}
void ball::firstCollision(){ 
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
        std::cout << "chiamata collision: firstCollision" << '\n';
    }else{
        nCollision();
        std::cout << "chiamata collision: nCollision" << '\n';
    }
}





    bool ball::selector(bool updown, bool direction) { 
    std::cout << "\n=== Entrata in selector ===\n";
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
        return 1;
    }
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

        std::cout << "selector: return 1\n";
        return 1;
    }

    return 0;
}

void ball::timeEvolving(float center[], sf::Vertex upperBound[],sf::Vertex lowerBound[],sf::RenderWindow &window, int &t,sf::CircleShape &shape1){
    if(Direction > 0)
{
 shape1.setPosition(center[0] + positionX(Direction*t), center[1]- positionY(Direction*t)); 
        window.clear();
        window.draw(upperBound, 2, sf::Lines); 
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();
}else if(Direction < 0){
        const int T = t;
        std::cout << T << '\n';
        shape1.setPosition(center[0] + positionX(T-t), center[1]- positionY(T-t));
        window.clear();
        window.draw(upperBound, 2, sf::Lines); 
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();
}
}

void ball::endingDynamics(float center[], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, int &t, sf::CircleShape &shape1, ball &bParameters, bool direction){
    std::cout << "endingDynamics" << '\n';
    shape1.setPosition(center[0] + x,center[1] - y); 
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
        
        float scale = 1.0f / std::sqrt(1 + m*m);
        float effective_t = h; //per il momento senza scale
        shape1.setPosition(center[0] + positionX(effective_t), center[1]- positionY(effective_t)); 
        window.clear();
        window.draw(upperBound, 2, sf::Lines);
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();
        
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
    }}


    void ball::collidingDynamics(float center[], sf::Vertex upperBound[], sf::Vertex lowerBound[], 
                           sf::RenderWindow &window, int &t, sf::CircleShape &shape1, 
                           ball &bParameters, bool direction, int i)
{
    std::cout << "collidingDynamics" << '\n';
    std::cout << "il valore di mGiac è: " << mGiac << '\n';
    std::cout << "parametri all'inizio di collidingDynamics: x= " << x << " y=" << y << " direction=" << Direction << '\n';
    
    float impact[2] = {bParameters.getX(), bParameters.getY()}; 
    shape1.setPosition(center[0] + x, center[1] - y);
    
    int h;
    int T = t;
    if(Direction < 0) { t = 0; }

    while (window.isOpen())
    {   
        if(Direction > 0){
            h = t;
        } else {
            h = T - t;
        }
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        double scale = 1.0f / std::sqrt(1 + m*m);
        double effective_t = h;
        float newX = positionX(effective_t);
        float newY = positionY(effective_t);
        shape1.setPosition(center[0] + newX, center[1] - newY); 
        
        window.clear();
        window.draw(upperBound, 2, sf::Lines); 
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();

        if(std::abs(newX - impact[0]) < 12. && std::abs(newY - impact[1]) < 12.) {
            std::cout << "la pallina ha urtato!" << '\n';
            
            float collisionX = newX;
            float collisionY = newY;
            
            ball helpXY(collisionX, collisionY, m);  // Usa la posizione di collisione
            ball helpDir(collisionX, collisionY, m);
            ball helpM(collisionX, collisionY, m);
            
            helpM.updateM();
            helpDir.updateDirection();

            x = collisionX;  
            y = collisionY;
            m = helpM.getM();
            Direction = helpDir.getDirection();
            
            
            std::cout << "parametri alla fine di collidingDynamics: " << x << ", " << y << ", " << m << ", " << Direction << '\n';
            break;
        } else {
            t++;
        }
    }
}
            




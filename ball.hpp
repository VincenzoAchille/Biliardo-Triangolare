#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


struct collisionBall{
    float x_o;
    float y_o;
    bool collide; //1 collide, 0 no
};

class ball{
    public:
    //costruttori
    ball(float x, float y, float m);
    ball();
    //manca il costruttore copia
    //metodi
    void firstCollision(); //mi genera i primi xu e yu da cui derivo la prima equazione di giacomini
    void nCollision(bool direction);
    void collision(bool direction);
    void collisionParamters();
    bool direction(ball iniziale);
    float positionX(float t) {return t;}
    float positionY(float t) {return m*(t-x) + y;}
    float postnCollisionM();
    void postFirstCollisionM();
    void  postCollisionM(bool direction, int i);
    float postCollisionAngle();
    bool selector(bool a, bool b);

    void endingDynamics(float center[2], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, int &t, sf::CircleShape &shape1, ball &bParameters, bool direction);
    void collidingDynamics(float center[2], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, int &t, sf::CircleShape &shape1, ball &bParameters, bool direction, int i);
    //setters
    static void setr1(float _r1) { r1 = _r1; }
    static void setr2(float _r2) { r2 = _r2; }
    static void setl(float _l) { l = _l; }
    //getters
    static float getr1() { return r1;}
    static float getr2() { return r2; }
    static float getl() { return l;}
    static float getmGiac() {return l/(r2 - r1);}
    float getX() {return x;}
    float getY() {return y;}
    float getM() {return m;}
    
    //operazioni
    //distruttori

    private:
    float x;
    float y;
    float m;

    static float l; //vanno inizializzati come puntatori?
    static float r1;
    static float r2;
    static float mGiac;
};

#endif
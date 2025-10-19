#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class ball{
    public:
    //costruttori
    ball(float x, float y, float m,int direction);
    ball(float x, float y, float m);
    ball();
    //manca il costruttore copia
    ball(const ball& b) : x(b.x), y(b.y), m(b.m), Direction(b.Direction) {}
    //metodi
    void firstUpdateXY(); //mi genera i primi xu e yu da cui derivo la prima equazione di giacomini
    void nUpdateXY();
    void updateXY();
    void updateDirection();
    float positionX(float t) {return t;}
    float positionY(float t) {return m*(t-x) + y;}
    void update(float collisionX, float collisionY);
    void updateM();
    float angleRespectNormal();
    bool selector();
    float normal();
    float alfaMax();
    bool updown();
    void endingDynamics(float center[2], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, float &t, sf::CircleShape &shape1, 
        float &h, float &T, float v);
    void collidingDynamics(float center[2], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, float &t, sf::CircleShape &shape1, 
        float &h, float &T, float v);
    void timeEvolving(float center[2], sf::Vertex upperBound[],sf::Vertex lowerBound[],sf::RenderWindow &window, int &t,sf::CircleShape &shape1);
    bool discard(float center[], float &t, float &h, float &T,
                   float v);
    //setters
    static void setr1(float _r1) { r1 = _r1; }
    static void setr2(float _r2) { r2 = _r2; }
    static void setl(float _l) { l = _l; }
    //getters
    static float getr1() { return r1;}
    static float getr2() { return r2; }
    static float getl() { return l;}
    static float mGiac() {return std::abs(l/(r2 - r1));}
    float getX() {return x;}
    float getY() {return y;}
    float getM() {return m;}
    float getDirection() {return Direction;} //+-1

    
    //operazioni
    ball& operator=(const ball& b);
    //distruttori
    ~ball() {}

    private:
    double x;
    double y;
    double m;
    int Direction {1};

    static float l; //vanno inizializzati come puntatori?
    static float r1;
    static float r2;
    const float pi = 3.14;
};

#endif
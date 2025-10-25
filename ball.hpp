#ifndef BALL_HPP
#define BALL_HPP

#include "Methods.cpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class ball{
    public:
    //costruttori
    ball(float x, float y, float m,int direction);
    ball(float x, float y, float m);
    // ball();
    ball(const ball& b) : m_x(b.m_x), m_y(b.m_y), m_m(b.m_m), m_direction(b.m_direction) {}
    //metodi
    void updateXY();
    void updateDirection();
    float positionX(float t) {return t;}
    float positionY(float t) {return m_m*(t-m_x) + m_y;}
    void update(float collisionX, float collisionY);
    void updateM();
    float angleRespectNormal();
    bool selector();
    float normal();
    float alfaMax() const;
    bool updown();
    int discard(sf::Vector2f center, float &h, float &T);
    void dynamics(sf::Vector2f center, sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, float &t, sf::CircleShape &shape1,
    float &h, float &T, float v);     
    //setters
    static void r1(float _r1) { rangeValidity(_r1,0.,450.);
        m_r1 = _r1; }
    static void r2(float _r2) { rangeValidity(_r2,0.,450.);
        m_r2 = _r2; }
    static void l(float _l) { rangeValidity(_l,0.,1600.);
        m_l = _l; }
    //getters
    static float getr1() { return m_r1;}
    static float getr2() { return m_r2; }
    static float getl() { return m_l;}
    static float mGiac() {return std::abs(m_l/(m_r2 - m_r1));}
    float getX() {return m_x;}
    float getY() {return m_y;}
    float getM() {return m_m;}
    int getDirection() {return m_direction;} //+-1

    
    //operazioni
    ball& operator=(const ball& b);
    //distruttori
    ~ball() {}

    private:
    float m_x;
    float m_y;
    float m_m;
    int m_direction {1};

    static float m_l; 
    static float m_r1;
    static float m_r2;
};

#endif
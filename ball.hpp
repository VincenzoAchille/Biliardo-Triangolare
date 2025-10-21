#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class ball{
    public:
    //costruttori
    ball(float x, float y, float m,int direction);
    ball(float x, float y, float m);
    // ball();
    //manca il costruttore copia
    // ball(const ball& b) : x(b.x), y(b.y), m(b.m), Direction(b.Direction) {}
    //metodi
    void firstUpdateXY(); //mi genera i primi xu e yu da cui derivo la prima equazione di giacomini
    void nUpdateXY();
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
    void endingDynamics(float center[2], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, float &t, sf::CircleShape &shape1, 
        float &h, float &T, float v);
    void collidingDynamics(float center[2], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, float &t, sf::CircleShape &shape1, 
        float &h, float &T, float v);
    void timeEvolving(float center[2], sf::Vertex upperBound[],sf::Vertex lowerBound[],sf::RenderWindow &window, int &t,sf::CircleShape &shape1);
    int discard(float center[], float &t, float &h, float &T, sf::CircleShape &shape1,
                   float v);
    void dynamics(float center[], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, float &t, sf::CircleShape &shape1,
    float &h, float &T, float v);     
    //setters
    static void r1(float _r1) { m_r1 = _r1; }
    static void setr2(float _r2) { m_r2 = _r2; }
    static void setl(float _l) { m_l = _l; }
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

    static float m_l; //vanno inizializzati come puntatori?
    static float m_r1;
    static float m_r2;
};

#endif
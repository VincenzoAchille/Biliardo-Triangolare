#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <iostream>

//se avessi una classe globale che include ball potrei fare dei controlli migliori (avrei accesso a center e a windows)
inline void rangeValidity(float value, float min, float max) { //[] estremi compresi
    if (value >= min && value <= max) { 
        return; 
    }
    //std::cout << min << ", " << max;
    throw std::out_of_range("Value out of range");  
}

inline int sgn(float x) {
return x > 0 ? 1:-1;  
  // return (x > 0) - (x < 0);
}

class ball {
 public:
  // costruttori
  ball(float x, float y, float m, int direction);
  ball(float x, float y, float m);
  // ball();
  ball(const ball &b)
      : m_x(b.m_x), m_y(b.m_y), m_m(b.m_m), m_direction(b.m_direction) {}
  // metodi
  void updateXY();
  void updateDirection();
  float positionX(float t) const { return t; } 
  float positionY(float t) const { return m_m * (t - m_x) + m_y; }
  void update(float collisionX, float collisionY);
  void updateM();
  float angleRespectNormal();
  bool selector();
  float normal() const;
  float alfaMax() const;
  //int updown();
  int dynamics(sf::Vector2f center, float &h, float &T);
  void dynamicsAnimated(sf::Vector2f center, sf::Vertex upperBound[],
                sf::Vertex lowerBound[], sf::RenderWindow &window, float &t,
                sf::CircleShape &shape1, float &h, float &T, float v);
  // setters
  static void r1(float _r1) {
    rangeValidity(_r1, 0., 450.);
    m_r1 = _r1;
  }
  static void r2(float _r2) {
    rangeValidity(_r2, 0., 450.);
    m_r2 = _r2;
  }
  static void l(float _l) { //questo è un limite grafico
    rangeValidity(_l, 0.,1200);
    m_l = _l;
  }
  /*
  static void center(sf::Vector2f _center){
    m_center = _center;

  }
  static void window(sf::Vector2f _window){
    m_window = _window;

  }*/
  // getters
  static float getr1() { return m_r1; }
  static float getr2() { return m_r2; }
  static float getl() { return m_l; }
  static float mGiac() { return std::abs(m_l / (m_r2 - m_r1)); }
  //static sf::Vector2f getCenter() {return m_center;}
  //static sf::Vector2f getWindow() {return m_window;}
  float getX() const { return m_x; }
  float getY() const{ return m_y; }
  float getM() const { return m_m; }
  int getDirection() const { return m_direction; }  //+-1

  // operazioni
  ball &operator=(const ball &b);
  // distruttori
  ~ball() {}

 private:
  float m_x;
  float m_y;
  float m_m;
  int m_direction{1};
  float m_radius{10.f};

  static float m_l;
  static float m_r1;
  static float m_r2;
  //static sf::Vector2f m_center;
  //static sf::Vector2f m_window;
};

#endif
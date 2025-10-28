#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <limits>

//se avessi una classe globale che include ball potrei fare dei controlli migliori (avrei accesso a center e a windows)
template <typename T>
inline void rangeValidity(T value, T min, T max) { //[] estremi compresi
    if (value >= min && value <= max) { 
        return; 
    }
    throw std::out_of_range("Value out of range");  
}

inline int sgn(float x) {
return x >= 0 ? 1:-1;  
}

class ball {
 public:
  // costruttori
  template<typename A>
  ball(float _x, float _y, float _m, A _direction) { //non ho capito benissimo cosa fa
    if constexpr (!std::is_same_v<A, int>) {
        throw std::invalid_argument("Direction must be int type");
    }
    float maxY = std::max(m_r1, m_r2);
    const float floatTolerance = 0.1f; //non usata
    rangeValidity(_x, -m_errorTolerance, m_l+ + m_errorTolerance);
    rangeValidity(_y, -(maxY + m_errorTolerance), maxY + m_errorTolerance);
    
    if (_direction != 1 && _direction != -1) {
        throw std::out_of_range("Value out of range");
    }

  m_x = _x;
  m_y = _y;
  m_m = _m;
  m_direction = _direction;
}
  ball(float _x, float _y, float _m) : ball(_x, _y, _m, 1) {}
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
  void dynamics(sf::Vector2f center,
                            sf::RenderWindow &window,
                            float &t, float &h,
                            float &T);
  void dynamicsAnimated(sf::Vector2f center, sf::Vertex upperBound[],
                sf::Vertex lowerBound[], sf::RenderWindow &window, float &t,
                sf::CircleShape &shape1, float &h, float &T, float v);
  // setters
  static void r1(float _r1) {
    rangeValidity(_r1, 0.f, static_cast<float>(m_window.y)-m_center.y);
    m_r1 = _r1;
  }
  static void r2(float _r2) {
    rangeValidity(_r2, 0.f,static_cast<float>(m_window.y)-m_center.y);
    m_r2 = _r2;
  }
  static void l(float _l) {  
    rangeValidity(_l, 0.f,static_cast<float>(m_window.x)-m_center.x);
    m_l = _l;
  }
  
  static void center(sf::Vector2f _center){
    rangeValidity(_center.x,0.f, static_cast<float>(m_window.x));
    rangeValidity(_center.y,0.f, static_cast<float>(m_window.y));

    m_center = _center;

  }
  static void window(sf::Vector2i _window){
    rangeValidity(_window.x,0, 1920);
    rangeValidity(_window.y,0, 1080);
    m_window = _window;

  }
  // getters
  static float getr1() { return m_r1; }
  static float getr2() { return m_r2; }
  static float getl() { return m_l; }
  static float getErrorTolerance() {return m_errorTolerance;}
  static float mGiac() { return std::abs(m_l / (m_r2 - m_r1)); }
  static sf::Vector2f getCenter() {return m_center;}
  static sf::Vector2i getWindow() {return m_window;}
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
  
  static float m_errorTolerance;
  static float m_l;
  static float m_r1;
  static float m_r2;
  static sf::Vector2f m_center;
  static sf::Vector2i m_window;
};

#endif
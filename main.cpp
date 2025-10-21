// camelCase

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

#include "Methods.cpp"
#include "ball.hpp"

int main() {
    constexpr float M_PI_F = static_cast<float> (M_PI);
  float center[2]{300, 450};
  float r1{200};
  float r2{100};
  float l{1000};
  float y0{50};
  float theta0{static_cast<float>(0.6)};
  float m = std::tan(theta0);
  float v{2};

  rangeValidity(y0, -r1, r1);
  rangeValidity(theta0, -M_PI_F / 2, M_PI_F / 2);
  ball::r1(r1);
  ball::setr2(r2);
  ball::setl(l);

  // parte di SFML (setting)
  sf::Vertex upperBound[]{
      sf::Vertex(sf::Vector2f(center[0], center[1] - ball::getr1()),
                 sf::Color::White),
      sf::Vertex(
          sf::Vector2f(center[0] + ball::getl(), center[1] - ball::getr2()),
          sf::Color::White)};
  sf::Vertex lowerBound[] =  // preso da Chat
      {sf::Vertex(sf::Vector2f(center[0], center[1] + ball::getr1()),
                  sf::Color::Red),
       sf::Vertex(
           sf::Vector2f(center[0] + ball::getl(), center[1] + ball::getr2()),
           sf::Color::Red)};
  sf::RenderWindow window(sf::VideoMode(1600, 900), "Biliardo Triangolare");

  // inizializzazione ball e shape
  ball b1(0, y0, m);
  sf::CircleShape shape1(10.f);
  shape1.setPosition(center[0], center[1] - y0);
  shape1.setFillColor(sf::Color::Cyan);

  // parte dinamica

  float t{0};
  float h{0};
  float T{0};
  int finalDirection = b1.discard(center, t, h, T, shape1, v);
  std::cout << "finalDirection" << finalDirection << '\n';
  for (int i{0}; i >= 0; i++) {
    // bool selectedMotion = b1.selector();

    // dynamics starting

    /*if(selectedMotion == 0){
       b1.endingDynamics(center, upperBound, lowerBound, window,t,shape1,h,T,v);
    }
    else{
        b1.collidingDynamics(center, upperBound, lowerBound,
    window,t,shape1,h,T,v);
    }*/
    b1.dynamics(center, upperBound, lowerBound, window, t, shape1, h, T, v);
    // std::cout << "valore di controllo = " << i << '\n';
    if (i > 30) {
      myPause();
    }
  }
}

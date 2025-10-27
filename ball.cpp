#include "ball.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <cmath>

float ball::m_l = 1.f;
float ball::m_r1 = 1.f;
float ball::m_r2 = 1.f;
//sf::Vector2f center (300,450);
//sf::Vector2f window (1600,900);

ball::ball(float _x, float _y, float _m, int _direction) {
  // rangeValidity(_x);
  float maxY = std::max(m_r1, m_r2);
  rangeValidity(_x,0.,900.);
  rangeValidity(_y, -maxY, maxY);
  if (_direction != 1 && _direction != -1) {
    throw std::out_of_range("Value out of range");  
  }

  m_x = _x;
  m_y = _y;
  m_m = _m;
  m_direction = _direction;
}

ball::ball(float _x, float _y, float _m) : ball(_x,_y,_m,1){}

ball &ball::operator=(const ball &b) {
  m_x = b.m_x;
  m_y = b.m_y;
  m_m = b.m_m;
  m_direction = b.m_direction;
  return *this;
}

float ball::alfaMax() const {
  return static_cast<float>(std::abs(atan(1 / mGiac())));
}

void ball::updateDirection() {
  float angle = angleRespectNormal();

  if (alfaMax() - angle > 0.) {
    m_direction = -m_direction;
  }
  /*if (alfaMax() - angle < 0.) { c'è un warning
    m_direction = m_direction;
  }*/
}

/*int ball::updown() {  // strano che cambiando il verso delle normali non
  cambi,
                       // cosi come se ho <0 o ==0. bo
  float controlValue = m_m * static_cast<float>(m_direction);
    if (controlValue < 0) {
      return -1;
    }
    else if (controlValue > 0) {
      return 1;
    } else {
    std::cout << "errore nel calcolo della normale" << '\n';
    return 0;
  }}
    */

float ball::normal() const{
  float controlValue = m_m * static_cast<float>(m_direction);
  int normalDirection;
  if (controlValue < 0) {
    normalDirection = -1;
  } else if (controlValue > 0) {
    normalDirection = 1;
  } else {
    std::cout << "errore nel calcolo della normale" << '\n';
    return 0;
  }

  if (normalDirection > 0) {
    return std::abs(mGiac());

  } else {
    return -std::abs(mGiac());
  }
}
void ball::updateM() {
  float N = normal();
  float mAngle = static_cast<float>(std::tan(angleRespectNormal()));
  // int a = 1;
  float newM = -(mAngle + N) / (N * mAngle - 1);
  if (std::abs(newM - m_m) < 1e-3) {
    // a = -1;
    newM = -(-mAngle + N) / (N * -mAngle - 1);
    m_m = newM;
  } else {
    m_m = newM;
  }
}

float ball::angleRespectNormal() {
  float N = normal();
  float M = m_m;
  float b = std::abs(std::atan((M - N) / (1 + M * N)));
  return b;
}

void ball::updateXY() {
  float A = normal();
  std::cout << "normal in updateXY: " << A << '\n';
  if (A >= 0) {
    float xu = m_x;
    m_x = (m_r1 - m_y + m_m * m_x) / (m_m - (m_r2 - m_r1) / m_l);
    m_y = m_m * (m_x - xu) + m_y;

  } else if (A < 0) {
    float xu = m_x;
    m_x = (-m_r1 - m_y + m_m * m_x) / (m_m + (m_r2 - m_r1) / m_l);
    m_y = m_m * (m_x - xu) + m_y;
  }
}
bool ball::selector() {
  {
    if ((m_m * (m_l - m_x) + m_y  > -m_r2 && m_m * (m_l - m_x) + m_y  < m_r2) &&
        m_direction > 0) {
      return 0;
    }
    if ((m_m * (-m_x) + m_y -2* m_radius * std::sqrt(2)/std::sqrt(1+m_m*m_m)> -m_r1 && 
    m_m * (-m_x) + m_y -2* m_radius * std::sqrt(2)/std::sqrt(1+m_m*m_m) < m_r1) &&
        m_direction < 0) {
          std::cout << "il controllo è di:" << m_m * (-m_x) + m_y +2* m_radius * std::sqrt(2)/std::sqrt(1+m_m*m_m) << "il vecchio controllo: " <<
           m_m * (-m_x) + m_y << "m_r1 = " << m_r1  << '\n';
      return 0;
    }
    return 1;
  }

  return 0;
}

void ball::update(float collisionX, float collisionY) {
  ball helpDir(m_x, m_y, m_m, m_direction);
  ball helpM(m_x, m_y, m_m, m_direction);
  helpM.updateM();
  helpDir.updateDirection();
  m_x = collisionX;
  m_y = collisionY;
  m_m = helpM.getM();
  m_direction = helpDir.getDirection();
}
void ball::dynamicsAnimated(sf::Vector2f center, sf::Vertex upperBound[],
                    sf::Vertex lowerBound[], sf::RenderWindow &window, float &t,
                    sf::CircleShape &shape1, float &h, float &T, float v) {
  for (int i{0}; i >= 0; i++) {
    //std::cout << "pre selector" << '\n';
    bool selectedMotion = this->selector();
    std::cout << "il moto selezionato è: " << selectedMotion << '\n';
    //std::cout << "post selector" << '\n';
    float radius = shape1.getRadius() / 2;
   /*float extra;
    if (normal() > 0) {
      extra = 0;
    } else {
      extra = radius;
    }*/
    sf::Vector2f impact;
    if (selectedMotion == 1) {
      ball toUpdate(m_x, m_y, m_m, m_direction);
      toUpdate.updateXY();
      impact.x = toUpdate.getX();
      impact.y = toUpdate.getY();
    } else {
      if (m_direction > 0) {
        impact.x = positionX(m_l);
        impact.y = positionY(m_l);
      } else {
        impact.x = positionX(0);
        impact.y = positionY(0);
      }
    }
    if (m_direction < 0) {
      T = h;
      t = 0;
    }

    while (window.isOpen()) {
      if (m_direction > 0) {
        h = t;
      } else {
        h = T - t;
      }
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
      }

      float scale = 1.0f / std::sqrt(1 + m_m * m_m);
      float effective_t = h * v;
      shape1.setPosition(center.x + positionX(effective_t),
                         center.y - positionY(effective_t));
      float newX = positionX(effective_t);
      float newY = positionY(effective_t);
      window.clear();
      window.draw(upperBound, 2, sf::Lines);
      window.draw(lowerBound, 2, sf::Lines);
      window.draw(shape1);
      window.display();
      //std::cout << "valori impatto: X= " << newX - impact.x << "Y= " << newY - impact.y << '\n';
      bool isCollision = std::abs(newX - impact.x ) <  5. &&
                         std::abs(newY - impact.y) < 5.;

      if (isCollision) {
        //std::cout << "il moto precedentemente selezionato è: " << selectedMotion << '\n';
        if (selectedMotion == 1) {
          update(newX, newY);
          break;
        } else if (selectedMotion == 0) {
          while (window.isOpen()) {
            sf::Event event2;
            while (window.pollEvent(event2)) {
              if (event2.type == sf::Event::Closed) {
                window.close();
                return;
              }

              if (event2.type == sf::Event::KeyPressed) {
                if (event2.key.code == sf::Keyboard::Escape) {
                  window.close();
                  return;
                }
              }
            }
            window.clear();
            window.draw(upperBound, 2, sf::Lines);
            window.draw(lowerBound, 2, sf::Lines);
            window.draw(shape1);
            window.display();
          }
        }
      }

      else {
        t = t + scale;
      }
    }
  }
}

int ball::dynamics(sf::Vector2f center, float &h,
                  float &T) {  // ho tolto tutto ciò che riguardava il radius
                               // sembra non usare t
  float i{0};
  ball b1Temp(m_x, m_y, m_m, m_direction);
  bool selectedMotion = selector();
  while (selectedMotion == 1) {
    selectedMotion = this->selector();

    ball toUpdate(m_x, m_y, m_m, m_direction);
    toUpdate.updateXY();
    sf::Vector2f impact;  // forse non è il massimo, da chiedere
    if (selectedMotion == 1) {
      impact.x = toUpdate.getX();
      impact.y = toUpdate.getY();
    } else {
      if (m_direction < 0) {
        impact.x = positionX(0);
        impact.y = positionY(0);
      } else {
        impact.x = positionX(m_l);
        impact.y = positionY(m_l);
      }
    }

    if (m_direction < 0) {
      T = h;
      i = 0;
    }

    while (i >= 0) {
      if (m_direction > 0) {
        h = i;
      } else {
        h = T - i;
      }
      float scale = static_cast<float>(1. / std::sqrt(1 + m_m * m_m));
      float effective_t = h;
      float newX = positionX(effective_t);
      float newY = positionY(effective_t);

      if (std::abs(newX - impact.x) < 10. && std::abs(newY - impact.y) < 10.) {
        float collisionX = newX;
        float collisionY = newY;
        update(collisionX, collisionY);

        break;
      } else if (std::abs(newX - impact.x - center.x) < 10. &&
                 std::abs(newY + impact.y - center.y) < 10.) {
        break;

      } else {
        i = i + scale;
      }
    }
  }
  int newDirection = m_direction;
  *this = b1Temp;
  return newDirection;
}

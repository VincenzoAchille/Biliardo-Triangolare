#include "ball.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include "Methods.cpp"
#include <algorithm>

float ball::m_l = 1.;
float ball::m_r1 = 1.;
float ball::m_r2 = 1.;

ball::ball(float _x, float _y, float _m, int _direction) {
  //rangeValidity(_x);
  float maxY = std::max(m_r1,m_r2);
  std::cout << "il valore è:" << _y << '\n';
  std::cout << "il massimo è: " << maxY << '\n';

  rangeValidity(_y, -maxY, maxY);
  //rangeValidity(_m);
  //rangeValidity(_direction);

  m_x = _x;
  m_y = _y;
  m_m = _m;
  m_direction = _direction;
}

ball::ball(float _x, float _y, float _m) {
  m_x = _x;
  m_y = _y;
  m_m = _m;
}

ball &ball::operator=(const ball &b) {
  m_x = b.m_x;
  m_y = b.m_y;
  m_m = b.m_m;
  m_direction = b.m_direction;
  return *this;
}

float ball::alfaMax() const {
     return static_cast<float>(std::abs(atan(1 / mGiac()))); }

void ball::updateDirection() {
  float angle = angleRespectNormal();
  std::cout << "in updateDirection: " << angle << ", " << alfaMax()
            << " , la differenza è: " << std::abs(angle - alfaMax()) << '\n';

  if (alfaMax() - angle > 0.) {
    m_direction = -m_direction;
  }
  /*if (alfaMax() - angle < 0.) { c'è un warning
    m_direction = m_direction;
  }*/
}

bool ball::updown() {  // strano che cambiando il verso delle normali non cambi,
                       // cosi come se ho <0 o ==0. bo
  float controlValue = m_m * static_cast<float>(m_direction);
  if (m_r1 - m_r2 > 1e-1) {
    if (controlValue < 0) {
      return 0;
    }
    if (controlValue > 0) {
      return 1;
    } else {
      return 0;
    }
   }
   else{
    std::cout << "errore nel calcolo della normale" << '\n';
    return 0;
   }
}

float ball::normal() {
  bool a = updown();
  if (a == 1) {
    return std::abs(mGiac());

  } else {
    return -std::abs(mGiac());
  }
}
void ball::updateM() {
  float N = normal();
  float mAngle = static_cast<float>(std::tan(angleRespectNormal()));
  //int a = 1;
  float newM = -( mAngle + N) / (N * mAngle - 1);
  if (std::abs(newM - m_m) < 1e-3) {
    //a = -1;
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
  if (normal() >= 0) {
    float  xu = m_x;
    m_x = (m_r1 - m_y + m_m * m_x) / (m_m - (m_r2 - m_r1) / m_l);
    m_y = m_m * (m_x - xu) + m_y;

  } else if (normal() < 0) {
    float  xu = m_x;
    m_x = (-m_r1 - m_y + m_m * m_x) / (m_m + (m_r2 - m_r1) / m_l);
    m_y = m_m * (m_x - xu) + m_y;
  }
}
/*void ball::firstUpdateXY() {
  if (m_m >= 0.) {
    m_x = (m_y - m_r1) / ((m_r2 - m_r1) / m_l - m_m);
    m_y = m_m * m_x + m_y;
  } else if (m_m < 0.) {
    m_x = (m_y + m_r1) / ((m_r1 - m_r2) / m_l -m_m);
    m_y = m_m * m_x + m_y;
  }
}*/


bool ball::selector() {
  {
    if ((m_m * (m_l - m_x) + m_y > -m_r2 && m_m * (m_l - m_x) + m_y < m_r2) && invert(m_direction)) {
      return 0;
    }
    if ((m_m * (-m_x) + m_y > -m_r1 && m_m * (-m_x) + m_y < m_r1) && !invert(m_direction)) {
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
void ball::dynamics(sf::Vector2f center, sf::Vertex upperBound[],
                    sf::Vertex lowerBound[], sf::RenderWindow &window, float &t,
                    sf::CircleShape &shape1, float &h, float &T, float v) {
  for(int i{0}; i >= 0; i++){
  std::cout << "pre selector" << '\n';
  bool selectedMotion = this->selector();
  std::cout << "post selector" << '\n';
  float radius = shape1.getRadius() / 2;
  /*float extra;
  if (updown() == 1) {
    extra = 0;
  } else {
    extra = 2 * radius;
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
  std::cout << "calcolati gli impatti" << '\n';
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
    shape1.setPosition(center.x + positionX(effective_t) - radius,
                       center.y - positionY(effective_t) - radius);
    float newX = positionX(effective_t);
    float newY = positionY(effective_t);
    window.clear();
    window.draw(upperBound, 2, sf::Lines);
    window.draw(lowerBound, 2, sf::Lines);
    window.draw(shape1);
    window.display();
    bool isCollision = std::abs(newX - impact.x) < radius + 2 &&
                       std::abs(newY - impact.y) < radius + 2;

    if (isCollision) {
      if (selectedMotion == 1) {
        update(newX, newY);
        break;
      }else if (selectedMotion == 0){
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
      }}
      
    

    else{
      t = t + scale;
    }
  
}
                    }
                  }


int ball::discard(sf::Vector2f center, float &h, float &T) {  // ho tolto tutto ciò che riguardava il radius
                                                                        //sembra non usare t
  float i{0};
  ball b1Temp(m_x, m_y, m_m, m_direction);
  bool selectedMotion = selector();
  while (selectedMotion == 1) {
    selectedMotion = this->selector();

    ball toUpdate(m_x, m_y, m_m, m_direction);
    toUpdate.updateXY();
    sf::Vector2f impact; //forse non è il massimo, da chiedere
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
      float scale = static_cast<float> (1. / std::sqrt(1 + m_m * m_m));
      float effective_t = h;
      float newX = positionX(effective_t);
      float newY = positionY(effective_t);

      if (std::abs(newX - impact.x) < 10. &&
          std::abs(newY - impact.y) < 10.) {
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

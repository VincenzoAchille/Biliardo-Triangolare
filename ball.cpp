#include "ball.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
float ball::m_l = 1.f;
float ball::m_r1 = 1.f;
float ball::m_r2 = 1.f;
sf::Vector2f ball::m_center(300, 450);
sf::Vector2i ball::m_window(1600, 900);
float ball::m_errorTolerance = 5.f;
float ball::m_radius = 10.f;

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

void ball::updateDirection() {  // dubbio se tenere il secondo if
  std::cout << "angleRespectNormal: " << angleRespectNormal() << '\n';
  float angle = angleRespectNormal();

  if (alfaMax() - angle > 0.) {
    m_direction = -m_direction;
  }
  /*if (alfaMax() - angle < 0.) { c'è un warning
    m_direction = m_direction;
  }*/
}

float ball::normal() const {
  float controlValue = m_m * static_cast<float>(m_direction);
  int normalDirection;

  if (m_r1 >= m_r2) {
    if (controlValue < 0) {
      normalDirection = -1;
    } else if (controlValue > 0) {
      normalDirection = 1;
    } else if (controlValue == 0 && m_direction == 1) {
      normalDirection = static_cast<int>(sgn(m_y));

    } else if (controlValue == 0 && m_direction == -1) {
      normalDirection = 1;  //è indifferente: termina il moto

    } else {
      return 0;
    }
  } else {
    if (controlValue < 0) {
      normalDirection = 1;
    } else if (controlValue > 0) {
      normalDirection = -1;
    } else if (controlValue == 0 && m_direction == 1) {
      normalDirection = 1;  //è indifferente

    } else if (controlValue == 0 && m_direction == 1) {
      normalDirection = static_cast<int>(sgn(m_y));
    } else {
      return 0;
    }
  }
  //
  if (normalDirection > 0) {
    return std::abs(mGiac());

  } else {
    return -std::abs(mGiac());
  }
}

void ball::updateM() {
  float newM;
  if (std::abs(m_r1 - m_r2) < 1e-6) {
    m_m = -m_m;

  } else {
    float N = normal();
    float mAngle = static_cast<float>(std::tan(angleRespectNormal()));
    newM = -(mAngle + N) / (N * mAngle - 1);
    if (std::abs(newM - m_m) < 1e-3) {
      newM = -(-mAngle + N) /
             (N * -mAngle - 1);  // forse questa condizione può essere eliminata
      m_m = newM;
    } else {
      m_m = newM;
    }
  }
}
// den == 0
float ball::angleRespectNormal() const{
  if (std::abs(m_r1 - m_r2) < 1e-6) {
    float b = std::abs(std::atan(1 / m_m));
    return b;

  } else {
    float N = normal();
    float M = m_m;
    float b;
    if (1 + M * N == 0) {
      std::cout << "errore: 1+M*N == 0" << '\n';
      b = 0.f;
    } else {
      b = std::abs(std::atan((M - N) / (1 + M * N)));
    }
    return b;
  }
}

// ha senso mettere una guardia sul denominatore? tanto non si verifica mai
void ball::updateXY() {
  float A = normal();

  if (A >= 0) {
    float xu = m_x;
    m_x = (m_r1 * sgn(m_r1 - m_r2) - m_y + m_m * m_x) /
          (m_m + 1 / normal());  // std::abs(m_r2 - m_r1) / m_l
    m_y = m_m * (m_x - xu) + m_y;

  } else if (A < 0) {
    float xu = m_x;
    m_x = (-m_r1 * sgn(m_r1 - m_r2) - m_y + m_m * m_x) / (m_m + 1 / normal());
    m_y = m_m * (m_x - xu) + m_y;
  }
}
bool ball::selector()const {
  {
    if ((m_m * (m_l - m_x) + m_y > -m_r2 && m_m * (m_l - m_x) + m_y < m_r2) &&
        m_direction > 0) {
      return 0;
    }
    if ((m_m * (-m_x) + m_y > -m_r1 && m_m * (-m_x) + m_y < m_r1) &&
        m_direction < 0) {
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
                            sf::Vertex lowerBound[], sf::RenderWindow &window,
                            float &t, sf::CircleShape &shape1, float &h,
                            float &T, float v) {
  for (int i{0}; i >= 0; i++) {
    bool selectedMotion = this->selector();

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
    sf::CircleShape Impact (5.f);
    Impact.setFillColor(sf::Color::Red);
    Impact.setPosition(center.x+ impact.x,center.y-impact.y);
    sf::CircleShape Pilot(5.f);
    Pilot.setFillColor(sf::Color::Yellow);
    
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
      float effective_t = h*v;
      float angle = std::abs(std::atan(m_m));
      shape1.setPosition(center.x + positionX(effective_t),
                         center.y - positionY(effective_t));

      float newX = positionX(effective_t);
      float newY = positionY(effective_t);
      Pilot.setPosition(center.x + positionX(effective_t)+ static_cast<float>(m_direction) * m_radius *
                               std::cos(angle),center.y - positionY(effective_t)-(static_cast<float>(sgn(normal() * (m_r1 - m_r2))) *
                               m_radius * std::sin(angle)));

      window.clear();
      window.draw(upperBound, 2, sf::Lines);
      window.draw(lowerBound, 2, sf::Lines);
      window.draw(shape1);
      window.draw(Impact);
      window.draw(Pilot);

      window.display();
      bool isCollision =
          std::abs((newX + static_cast<float>(m_direction) * m_radius *
                               std::cos(angle)) -
                   impact.x) < m_errorTolerance &&
          std::abs((newY + static_cast<float>(sgn(normal() * (m_r1 - m_r2))) *
                               m_radius * std::sin(angle)) -
                   impact.y) < m_errorTolerance;

      float yFinalCollision;
      float xFinalCollision;
      if (m_direction > 0) {
        yFinalCollision = m_m * (m_l - m_x) + m_y;
        xFinalCollision = m_l;
      } else {
        yFinalCollision = -m_m * m_x + m_y;
        xFinalCollision = 0.f;
      }
      bool finalCollision;
      if (m_direction > 0) {
        finalCollision = std::abs(newX - m_l) < m_errorTolerance &&
                         std::abs(newY - yFinalCollision) < m_errorTolerance;
      } else {
        finalCollision = std::abs(newX - 0.) < m_errorTolerance &&
                         std::abs(newY - yFinalCollision) < m_errorTolerance;
      }

      if (selectedMotion == 1 && isCollision) {
        update(newX, newY);
        break;
      } else if (selectedMotion == 0 && finalCollision) {
        ball bTemp(xFinalCollision, yFinalCollision, m_m, m_direction);
        *this = bTemp;
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

      else {
        t = t + scale;
      }
    }
  }
}

void ball::dynamics(float &h, float &T) {
  for (int i{0}; i >= 0; i++) {
    float j = 0.f;

    bool selectedMotion = this->selector();
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
      j = 0;
    }
    float scale = 1.0f / std::sqrt(1 + m_m * m_m);
    while (j >= 0) {
      if (m_direction > 0) {
        h = j;
      } else {
        h = T - j;
      }

      float angle = std::abs(std::atan(m_m));
      float newX = positionX(h);
      float newY = positionY(h);
      bool isCollision = std::abs((newX + static_cast<float>(m_direction) *
                                              m_radius * std::cos(angle)) -
                                  impact.x) < m_errorTolerance &&
                         std::abs((newY + sgn(normal() * (m_r1 - m_r2)) *
                                              m_radius * std::sin(angle)) -
                                  impact.y) < m_errorTolerance;

      float xFinalCollision;
      float yFinalCollision;
      if (m_direction > 0) {
        yFinalCollision = m_m * (m_l - m_x) + m_y;
        xFinalCollision = m_l;
      } else {
        yFinalCollision = -m_m * m_x + m_y;
        xFinalCollision = 0.0f;
      }
      bool finalCollision;
      if (m_direction > 0) {
        finalCollision = std::abs(newX - m_l) < m_errorTolerance &&
                         std::abs(newY - yFinalCollision) < m_errorTolerance;
      } else {
        finalCollision = std::abs(newX - 0.) < m_errorTolerance &&
                         std::abs(newY - yFinalCollision) < m_errorTolerance;
      }
      if (selectedMotion == 1 && isCollision) {
        update(newX, newY);
        break;
      } else if (selectedMotion == 0 && finalCollision) {
        ball bTemp(xFinalCollision, yFinalCollision, m_m, m_direction);
        *this = bTemp;
        return;
      } else {
        j = j + scale;
      }
    }
  }
}

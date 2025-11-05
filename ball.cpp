#include "ball.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

namespace biliard {
float ball::m_l = 1.f;
float ball::m_r1 = 1.f;
float ball::m_r2 = 1.f;
sf::Vector2f ball::m_center(300, 450);
sf::Vector2i ball::m_window(1600, 900);
float ball::m_errorTolerance = 2.f;
float ball::m_radius = 10.f;

ball &ball::operator=(const ball &b) {
  m_x = b.m_x;
  m_y = b.m_y;
  m_m = b.m_m;
  m_direction = b.m_direction;
  return *this;
}

float ball::alfaMax() const {
  return static_cast<float>(std::abs(atan(1 / normalModulus())));
}

void ball::updateDirection() {
  float angle = angleWithNormal();

  if (alfaMax() - angle > 0.) {
    m_direction = -m_direction;
  }
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
      normalDirection = 1;

    } else {
      return 0;
    }
  } else {
    if (controlValue < 0) {
      normalDirection = 1;
    } else if (controlValue > 0) {
      normalDirection = -1;
    } else if (controlValue == 0 && m_direction == 1) {
      normalDirection = 1;

    } else if (controlValue == 0 && m_direction == 1) {
      normalDirection = static_cast<int>(sgn(m_y));
    } else {
      return 0;
    }
  }
  //
  if (normalDirection > 0) {
    return std::abs(normalModulus());

  } else {
    return -std::abs(normalModulus());
  }
}

void ball::updateM() {
  float newM;
  if (std::abs(m_r1 - m_r2) < 1e-8) {
    m_m = -m_m;

  } else {
    float N = normal();
    float mAngle = static_cast<float>(std::tan(angleWithNormal()));
    newM = -(mAngle + N) / (N * mAngle - 1);
    if (std::abs(newM - m_m) < 1e-3) {
      newM = -(-mAngle + N) / (N * -mAngle - 1);
      m_m = newM;
    } else {
      m_m = newM;
    }
  }
}

float ball::angleWithNormal() const {
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

void ball::nextCollisionPosition() {
  float N = normal();
  const float xPrevious = m_x;

  if (N >= 0) {
    m_x = (m_r1 * sgn(m_r1 - m_r2) - m_y + m_m * m_x) / (m_m + 1 / normal());
    m_y = m_m * (m_x - xPrevious) + m_y;

  } else if (N < 0) {
    m_x = (-m_r1 * sgn(m_r1 - m_r2) - m_y + m_m * m_x) / (m_m + 1 / normal());
    m_y = m_m * (m_x - xPrevious) + m_y;
  }
}
bool ball::isColliding() const {
  if ((m_m * (m_l - m_x) + m_y > -m_r2 && m_m * (m_l - m_x) + m_y < m_r2) &&
      m_direction > 0) {
    return false;
  }
  if ((m_m * (-m_x) + m_y > -m_r1 && m_m * (-m_x) + m_y < m_r1) &&
      m_direction < 0) {
    return false;
  }
  return true;
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
void ball::ballDynamicsAnimated(float animationSpeed) {
  float time{0};
  float lastCollisionX{0};
  float positionX{0};
  sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(m_window.x),
                                        static_cast<unsigned int>(m_window.y)),
                          "Biliardo Triangolare");
  window.setFramerateLimit(60);
  sf::CircleShape circleShape(ball::getRadius());
  circleShape.setOrigin(m_radius, m_radius);
  circleShape.setPosition(m_center.x, m_center.y - m_y);
  circleShape.setFillColor(sf::Color::Cyan);
  while (true) {
    const bool collide = isColliding();

    sf::Vector2f impactCoordinates;
    if (collide) {
      ball toUpdate(*this);

      toUpdate.nextCollisionPosition();

      impactCoordinates.x = toUpdate.getX();
      impactCoordinates.y = toUpdate.getY();
    } else {
      if (m_direction > 0) {
        impactCoordinates.x = m_l;
        impactCoordinates.y = positionY(m_l);
      } else {
        impactCoordinates.x = 0.f;
        impactCoordinates.y = positionY(0);
      }
    }
    if (m_direction < 0) {
      lastCollisionX = positionX;
      time = 0;
    }

    while (window.isOpen()) {
      if (m_direction > 0) {
        positionX = time;
      } else {
        positionX = lastCollisionX - time;
      }
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
      }

      const float scale = 1.0f / std::sqrt(1 + m_m * m_m);
      const float effectivePositionX = positionX * animationSpeed;
      const float angle = std::abs(std::atan(m_m));
      circleShape.setPosition(m_center.x + effectivePositionX,
                              m_center.y - positionY(effectivePositionX));

      float newY = positionY(effectivePositionX);
      window.clear();
      window.draw(upperBound());
      window.draw(lowerBound());
      window.draw(circleShape);

      window.display();
      bool isCollision =
          std::abs((effectivePositionX +
                    sgn(m_direction) * m_radius * std::cos(angle)) -
                   impactCoordinates.x) < m_errorTolerance &&
          std::abs((newY + sgn(normal()) * sgn(m_r1 - m_r2) * m_radius *
                               std::sin(angle)) -
                   impactCoordinates.y) < m_errorTolerance;

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
        finalCollision =
            std::abs(effectivePositionX - m_l) < m_errorTolerance &&
            std::abs(newY - yFinalCollision) < m_errorTolerance;
      } else {
        finalCollision = std::abs(effectivePositionX - 0.) < m_errorTolerance &&
                         std::abs(newY - yFinalCollision) < m_errorTolerance;
      }

      if (std::abs(newY - yFinalCollision) > 1e7) {
        ball limitBall(0.f, 0.f, 0.f, 0);

        *this = limitBall;
        return;
      }
      if (collide && isCollision) {
        update(
            impactCoordinates.x - sgn(m_direction) * m_radius * std::cos(angle),
            impactCoordinates.y -
                sgn(normal()) * sgn(m_r1 - m_r2) * m_radius * std::sin(angle));

        break;
      } else if (!collide && finalCollision) {
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
          window.draw(upperBound());
          window.draw(lowerBound());
          window.draw(circleShape);
          window.display();
        }

      }

      else {
        time = time + scale;
      }
    }
  }
}

void ball::ballDynamics() {
  float positionX = 0.f;
  float lastCollisionX = 0.f;

  while (true) {
    float time = 0.f;

    const bool collide = isColliding();
    sf::Vector2f impactCoordinates;
    if (collide) {
      ball toUpdate(*this);
      toUpdate.nextCollisionPosition();

      impactCoordinates.x = toUpdate.getX();
      impactCoordinates.y = toUpdate.getY();
    } else {
      if (m_direction > 0) {
        impactCoordinates.x = m_l;
        impactCoordinates.y = positionY(m_l);
      } else {
        impactCoordinates.x = 0.f;
        impactCoordinates.y = positionY(0.f);
      }
    }
    if (m_direction < 0) {
      lastCollisionX = positionX;
      time = 0;
    }

    while (true) {
      if (m_direction > 0) {
        positionX = time;
      } else {
        positionX = lastCollisionX - time;
      }

      const float angle = std::abs(std::atan(m_m));
      const float newX = positionX;
      const float newY = positionY(newX);
      const float scale = 1.0f / std::sqrt(1 + m_m * m_m);

      bool isCollision = std::abs((newX + static_cast<float>(m_direction) *
                                              m_radius * std::cos(angle)) -
                                  impactCoordinates.x) < m_errorTolerance &&
                         std::abs((newY + sgn(normal()) * sgn(m_r1 - m_r2) *
                                              m_radius * std::sin(angle)) -
                                  impactCoordinates.y) < m_errorTolerance;

      float xFinalCollision;
      float yFinalCollision;
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

      if (std::abs(newY - yFinalCollision) > 1e7) {
        ball limitBall(0.f, 0.f, 0.f, 0);
        *this = limitBall;
        return;
      }

      if (collide && isCollision) {
        update(
            impactCoordinates.x - sgn(m_direction) * m_radius * std::cos(angle),
            impactCoordinates.y -
                sgn(normal()) * sgn(m_r1 - m_r2) * m_radius * std::sin(angle));

        break;
      } else if (!collide && finalCollision) {
        ball bTemp(xFinalCollision, yFinalCollision, m_m, m_direction);

        *this = bTemp;

        return;
      } else {
        time = time + scale;
      }
    }
  }
}

sf::VertexArray ball::upperBound() {
  sf::VertexArray vertexArray(sf::Lines, 2);

  vertexArray[0] =
      sf::Vertex(sf::Vector2f(m_center.x, m_center.y - m_r1), sf::Color::White);

  vertexArray[1] = sf::Vertex(sf::Vector2f(m_center.x + m_l, m_center.y - m_r2),
                              sf::Color::White);

  return vertexArray;
}
sf::VertexArray ball::lowerBound() {
  sf::VertexArray vertexArray(sf::Lines, 2);
  vertexArray[0] =
      sf::Vertex(sf::Vector2f(m_center.x, m_center.y + m_r1), sf::Color::White);

  vertexArray[1] = sf::Vertex(sf::Vector2f(m_center.x + m_l, m_center.y + m_r2),
                              sf::Color::White);

  return vertexArray;
}
}  // namespace biliard
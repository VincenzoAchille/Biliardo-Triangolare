#include "ball.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include "Methods.cpp"

float ball::m_l = 1.;
float ball::m_r1 = 1.;
float ball::m_r2 = 1.;

ball::ball(float _x, float _y, float _m, int _direction) {
  m_x = _x;
  m_y = _y;
  m_m = _m;
  m_direction = _direction;
};

ball::ball(float _x, float _y, float _m) {
  m_x = _x;
  m_y = _y;
  m_m = _m;
};

ball &ball::operator=(const ball &b) {
  m_x = b.m_x;
  m_y = b.m_y;
  m_m = b.m_m;
  m_direction = b.m_direction;
  return *this;
}

float ball::alfaMax() const {
     return std::abs(atan(std::abs(1 / mGiac()))); }

void ball::updateDirection() {
  float angle = angleRespectNormal();
  std::cout << "in updateDirection: " << angle << ", " << alfaMax()
            << " , la differenza è: " << std::abs(angle - alfaMax()) << '\n';

  if (alfaMax() - angle > 0.) {
    m_direction = -m_direction;
  }
  if (alfaMax() - angle < 0.) {
    m_direction = m_direction;
  }
}
bool ball::updown() {  // strano che cambiando il verso delle normali non cambi,
                       // cosi come se ho <0 o ==0. bo
  if (m_r1 - m_r2 > 1e-1) {
    if (m_m * m_direction < 0) {
      return 0;
    }
    if (m_m * m_direction > 0) {
      return 1;
    } else {
      return 0;
    }
  } else if (m_r2 - m_r1 > 1e-1) {
    if (m_m * m_direction < 0) {
      return 1;
    }
    if (m_m * m_direction > 0) {
      return 0;
    } else {
      return 0;
    }
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
  float mAngle = std::tan(angleRespectNormal());
  int a = 1;
  float newM = -(a * mAngle + N) / (N * a * mAngle - 1);
  if (std::abs(newM - m_m) < 1e-3) {
    a = -1;
    newM = -(a * mAngle + N) / (N * a * mAngle - 1);
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

void ball::nUpdateXY() {
  if (normal() >= 0) {
    double xu = m_x;
    m_x = (m_r1 - m_y + m_m * m_x) / (m_m - (m_r2 - m_r1) / m_l);
    m_y = m_m * (m_x - xu) + m_y;

  } else if (normal() < 0) {
    double xu = m_x;
    m_x = (-m_r1 - m_y + m_m * m_x) / (m_m + (m_r2 - m_r1) / m_l);
    m_y = m_m * (m_x - xu) + m_y;
  }
}
void ball::firstUpdateXY() {
  if (m_m >= 0.) {
    m_x = (m_y - m_r1) / ((m_r2 - m_r1) / m_l - m_m);
    m_y = m_m * m_x + m_y;
  } else if (m_m < 0.) {
    m_x = (m_y + m_r1) / ((m_r1 - m_r2) / m_l -m_m);
    m_y = m_m * m_x + m_y;
  }
}

void ball::updateXY() {  // qui mi serve un controllo un filo più forte sul
                         // first
  if (std::abs(m_x) < 1e-2) {
    firstUpdateXY();
  } else {
    nUpdateXY();
  }
}

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
void ball::dynamics(float center[], sf::Vertex upperBound[],
                    sf::Vertex lowerBound[], sf::RenderWindow &window, float &t,
                    sf::CircleShape &shape1, float &h, float &T, float v) {
  std::cout << "pre selector" << '\n';
  bool selectedMotion = this->selector();
  std::cout << "post selector" << '\n';
  float radius = shape1.getRadius() / 2;
  float extra;
  if (updown() == 1) {
    extra = 0;
  } else {
    extra = 2 * radius;
  }
  float impactX;
  float impactY;
  if (selectedMotion == 1) {
    ball toUpdate(m_x, m_y, m_m, m_direction);
    toUpdate.updateXY();
    impactX = toUpdate.getX();
    impactY = toUpdate.getY();
  } else {
    if (m_direction > 0) {
      impactX = positionX(m_l);
      impactY = positionY(m_l);
    } else {
      impactX = positionX(0);
      impactY = positionY(0);
    }
  }
  float impact[2] = {impactX, impactY};
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
    shape1.setPosition(center[0] + positionX(effective_t) - radius,
                       center[1] - positionY(effective_t) - radius);
    float newX = positionX(effective_t);
    float newY = positionY(effective_t);
    window.clear();
    window.draw(upperBound, 2, sf::Lines);
    window.draw(lowerBound, 2, sf::Lines);
    window.draw(shape1);
    window.display();
    bool isCollision = std::abs(newX - impact[0]) < radius + 2 &&
                       std::abs(newY - impact[1]) < radius + 2;
    std::cout << "sono nel ciclo: " << h << '\n';

    if (isCollision) {
      if (selectedMotion == 1) {
        update(newX, newY);
      }
      break;
    } else {
      t = t + scale;
    }
  }
}

/*void ball::endingDynamics(float center[], sf::Vertex upperBound[], sf::Vertex
lowerBound[], sf::RenderWindow &window, float &t, sf::CircleShape &shape1, float
&h, float &T, float v){

    float radius = shape1.getRadius() /2;
    ball toUpdate(x,y,m,Direction);
    toUpdate.updateXY();
    float impactX;
    float impactY;
    float extra;
        if(updown() == 1){
            extra = 0;
        }else{
            extra = 2* radius;
        }
    if(Direction > 0){
    impactX = positionX(l);
    impactY = positionY(l) + extra;

    }else{
    impactX = positionX(0);
    impactY = positionY(0) + extra;
    }

    float impact[2] = {impactX, impactY};
    std::cout << "x,y fine segmento all'inizio di endingDynamics" << impact[0]
<< ", " << impact[1] << '\n';


    if(Direction < 0) {
        T = h;
        t = 0; }


    while (window.isOpen())
    {
        if(Direction > 0){
        h = t;
    }else{
        h = T -t;
    }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float scale = 1.0f / std::sqrt(1 + m*m);
        float effective_t = h*v; //per il momento senza scale
          //std::cout << h << ",  " << T << ",  "<< t << '\n';
          //std::cout << "parametri pre-grafica:" << x << ", " << y << ", " << m
<< ", " << Direction << '\n'; shape1.setPosition(center[0] +
positionX(effective_t) - radius, center[1] - positionY(effective_t) - radius);
        float newX = positionX(effective_t);
        float newY = positionY(effective_t);
          //std::cout << "parametri grafici: " << positionX(effective_t) <<  ",
" << positionY(effective_t) << '\n'; window.clear(); window.draw(upperBound, 2,
sf::Lines); window.draw(lowerBound, 2, sf::Lines); window.draw(shape1);
        window.display();

        if(std::abs((newX - impact[0])) < radius + 2. && (std::abs((newY
-impact[1])) < radius + 2.)){ std::cout << "la pallina è scappata!" << '\n';
            while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

        }else{
            t = t +scale;
        }
    }}


    void ball::collidingDynamics(float center[], sf::Vertex upperBound[],
sf::Vertex lowerBound[], sf::RenderWindow &window, float &t, sf::CircleShape
&shape1, float &h, float &T, float v)
{
    float radius = shape1.getRadius() /2;
    ball toUpdate(x,y,m,Direction);
    toUpdate.updateXY();
    float extra;
        if(updown() == 1){
            extra = 0;
        }else{
            extra = 2* radius;
        }

    float impactX = toUpdate.getX();
    float impactY = toUpdate.getY();


    float impact[2] = {impactX, impactY};

    if(Direction < 0) {
        T = h;
        t = 0; }



    while (window.isOpen())
    {
        if(Direction > 0){
            //std::cout << "chiamata h = t" << '\n';
            h = t;
        } else {
            h = T - t;
            //std::cout << "chiamata h = T - t" << '\n';
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        double scale = 1./ std::sqrt(1 + m*m);
        double effective_t = h*v;
        float newX = positionX(effective_t);
        float newY = positionY(effective_t);
        shape1.setPosition(newX + center[0] - radius, center[1]- newY - radius);

        sf::CircleShape impatto(5.f);
        sf::CircleShape centro(4.f);
        impatto.setFillColor(sf::Color::Green);
        impatto.setPosition(impactX + center[0],center[1]-impactY);
        centro.setFillColor(sf::Color::Red);
        centro.setPosition(newX + center[0], center[1]- newY);
        window.clear();
        window.draw(upperBound, 2, sf::Lines);
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        //window.draw(impatto);
        //window.draw(centro);
        window.display();
        std::cout << newX << ", " << impact[0] << " - - " << newY << ", " <<
impact[1] << '\n'; if(std::abs(newX - impact[0]) < radius + 2. && std::abs(newY
- impact[1]) < radius + 2. ) {std::cout << "-- la pallina ha urtato! --" <<
'\n';

            float collisionX = newX;
            float collisionY = newY;

            update(collisionX, collisionY);

            std::cout << "parametri alla fine di collidingDynamics: " << x << ",
" << y << ", " << m << ", " << Direction << '\n'; break; } else { t = t + scale
;
        }
    }
}
*/
int ball::discard(float center[], float &t, float &h, float &T,
                  sf::CircleShape &shape1,
                  float v) {  // ho tolto tutto ciò che riguardava il radius

  std::cout << "chiamato discard " << '\n';
  int k{0};
  float i{0};
  ball b1Temp(m_x, m_y, m_m, m_direction);
  bool selectedMotion = selector();
  while (selectedMotion == 1) {
    selectedMotion = this->selector();

    ball toUpdate(m_x, m_y, m_m, m_direction);
    toUpdate.updateXY();
    float impactX;
    float impactY;
    if (selectedMotion == 1) {
      impactX = toUpdate.getX();
      impactY = toUpdate.getY();
    } else {
      if (m_direction < 0) {
        impactX = positionX(0);
        impactY = positionY(0);
      } else {
        impactX = positionX(m_l);
        impactY = positionY(m_l);
      }
    }
    float impact[2] = {impactX, impactY};

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
      double scale = 1. / std::sqrt(1 + m_m * m_m);
      double effective_t = h;
      float newX = positionX(effective_t);
      float newY = positionY(effective_t);

      if (std::abs(newX - impact[0]) < 10. &&
          std::abs(newY - impact[1]) < 10.) {
        float collisionX = newX;
        float collisionY = newY;
        update(collisionX, collisionY);

        break;
      } else if (std::abs(newX - impact[0] - center[0]) < 10. &&
                 std::abs(newY + impact[1] - center[1]) < 10.) {
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

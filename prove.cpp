void ball::dynamicsAnimated(sf::Vector2f center, sf::Vertex upperBound[],
                            sf::Vertex lowerBound[], sf::RenderWindow &window,
                            float &t, sf::CircleShape &shape1, float &h,
                            float &T, float v) {
  for (int i{0}; i >= 0; i++) {
    // std::cout << "pre selector" << '\n';
    bool selectedMotion = this->selector();
    // std::cout << "il moto selezionato è: " << selectedMotion << '\n';
    // std::cout << "post selector" << '\n';
    // float radius = shape1.getRadius() / 2;
    // std::cout << "l'extra è:" << extra << '\n';
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
    float scale = 1.0f / std::sqrt(1 + m_m * m_m);
    sf::CircleShape pilot(5.f);
    pilot.setOrigin(5.f, 5.f);
    pilot.setFillColor(sf::Color::Yellow);
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
      sf::CircleShape Impact(5.f);
      Impact.setFillColor(sf::Color::Red);
      Impact.setPosition(center.x + impact.x, center.y - impact.y);
      float effective_t = h * v;
      float angle = std::abs(std::atan(m_m));
      shape1.setPosition(center.x + positionX(effective_t),
                         center.y - positionY(effective_t));
      pilot.setPosition(center.x + positionX(effective_t) +
                            m_direction * m_radius * std::cos(angle),
                        center.y - positionY(effective_t) -
                            sgn(normal())*sgn(m_r1-m_r2) * m_radius * std::sin(angle));

      float newX = positionX(effective_t);
      float newY = positionY(effective_t);

      window.clear();
      window.draw(upperBound, 2, sf::Lines);
      window.draw(lowerBound, 2, sf::Lines);
      window.draw(shape1);
      window.draw(pilot);
      window.draw(Impact);

      window.display();
      bool isCollision =
          std::abs((newX + m_direction * m_radius * std::cos(angle)) -
                   impact.x) < m_errorTolerance &&
          std::abs((newY + sgn(normal())*sgn(m_r1-m_r2) * m_radius * std::sin(angle)) -
                   impact.y) < m_errorTolerance;
       //std::cout << "valori impatto, X= " << newX << " impatto= " << impact.x << '\n';
      // << " corr corpo rigido= " << m_direction*m_radius*std::cos(angle) <<
      // "distance:" << std::abs((newX+m_direction*m_radius*std::cos(angle)) -
      // impact.x)<<'\n'; std::cout << "valori impatto, Y= " << newY << "
      // impatto= " << impact.y << " corr corpo rigido= " <<
      // -sgn(normal())*m_radius*std::sin(angle) << "distance: "
      // <<std::abs((newY+sgn(normal())*m_radius*std::sin(angle)) - impact.y) <<
      // '\n' << '\n';

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
            std::abs(newX - m_l) < m_errorTolerance && std::abs(newY - yFinalCollision) < m_errorTolerance;
      } else {
        finalCollision =
            std::abs(newX - 0.) < m_errorTolerance && std::abs(newY - yFinalCollision) < m_errorTolerance;
      }
      //std::cout << "controllo urto finaleY: finalCollision " << yFinalCollision << " Y= " << newY << "distance: " << std::abs(newY - yFinalCollision) << "bool: " << finalCollision << '\n';
      //std::cout << "controllo urto finaleX: finalCollision " << 0. << " Y= " << newX << "distance: " << std::abs(newX) << '\n' << '\n';
      //std::cout <<"moto selezionato: " << selectedMotion << '\n';
      if (selectedMotion == 1 && isCollision) {
        //std::cout << "urto contro parete" << '\n' << '\n';
        update(newX, newY);
        break;
      } else if (selectedMotion == 0 && finalCollision) {
        std::cout << "urto finale" << '\n' << '\n';
        ball bTemp (xFinalCollision,yFinalCollision,m_m,m_direction);
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
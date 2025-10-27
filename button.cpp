#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(){
    float radius = 100.f;
    sf::CircleShape mainCircle (radius);
    sf::CircleShape radiusCircle (10.f);
    sf::Vector2f center(500. ,500.);
    mainCircle.setFillColor(sf::Color::Red);
    radiusCircle.setFillColor(sf::Color::Green);
    mainCircle.setOrigin(radius,radius);
    radiusCircle.setPosition(radius,radius);
    //voglio che setPosition mi setti il centro.
    //radiusCircle.setPosition()
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Circle test");
    int t{0};
    while(window.isOpen()){
        sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
      }
        mainCircle.setPosition(t,t/2);
        window.clear();
        window.draw(mainCircle);
        window.draw(radiusCircle);
        window.display();
        t++;
    }
}

//m_radius == radius

 /*if (isCollision) {
        std::cout << "impatto avvenuto" << '\n';
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
      }*/

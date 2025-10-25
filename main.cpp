#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include "ball.hpp"

int main() {
  //constexpr float M_PI_F = static_cast<float> (M_PI);
  sf::Vector2f center(300, 450);
  float r1{0.};
  float r2{0.};
  float l{0.};
  float y0{0.};
  float theta0{0.};
  float v{4};
  std::cout << "inserisci i parametri per la forma del biliardo:" << '\n';
  std::cout << "r1 = ";
  std::cin >> r1;
  std::cout << "r2 = ";
  std::cin >> r2;
  std::cout << "l = ";
  std::cin >> l;
  ball::r1(r1);
  ball::r2(r2);
  ball::l(l);
  // parte di SFML (setting)
  sf::Vertex upperBound[]{
      sf::Vertex(sf::Vector2f(center.x, center.y - ball::getr1()),
                 sf::Color::White),
      sf::Vertex(
          sf::Vector2f(center.x + ball::getl(), center.y - ball::getr2()),
          sf::Color::White)};
  sf::Vertex lowerBound[] = 
      {sf::Vertex(sf::Vector2f(center.x, center.y + ball::getr1()),
                  sf::Color::Red),
       sf::Vertex(
           sf::Vector2f(center.x + ball::getl(), center.y + ball::getr2()),
           sf::Color::Red)};

  std::cout << "selezionare il tipo di simulazione. " << '\n' << "per un lancio singolo premere 1" << '\n' << "per N lanci premere 2" << '\n';
  int input;
  std::cin >> input;

  if(input == 1){
  std::cout << "Inserire i parametri della pallina:" << '\n';
  std::cout << "y0 = ";
  std::cin >> y0;
  std::cout << "theta0 = ";
  std::cin >> theta0;
  rangeValidity(theta0, -static_cast<float>(M_PI/2), static_cast<float>(M_PI/2));
  sf::RenderWindow window(sf::VideoMode(1600, 900), "Biliardo Triangolare");
  float m = std::tan(static_cast<float>(theta0));
  ball b1(0, y0, m);
  sf::CircleShape shape1(10.f);
  shape1.setPosition(center.x, center.y - y0);
  shape1.setFillColor(sf::Color::Cyan);
  float t{0};
  float h{0};
  float T{0};
  // int finalDirection = b1.discard(center, h, T);
  //std::cout << "finalDirection = " << finalDirection << '\n';
  b1.dynamics(center, upperBound, lowerBound, window, t, shape1, h, T, v);
  
  }else if(input == 2){
  int N{0};
  float mean1{0.};
  float mean2{0.};
  float std1{0.};
  float std2{0.};
  std::cout << "Inserire il numero di tentativi:" << '\n';
  std::cin >> N;
  std::cout << "Inserire i parametri delle distribuzioni:" << '\n';
  std::cout << "Angolo iniziale:" << '\n';
  std::cout << "Media:" << '\n';
  std::cin >> mean1;
  std::cout << "Deviazione Standard:" << '\n';
  std::cin >> std1;
  std::cout << "Altezza iniziale:" << '\n';
  std::cout << "Media:" << '\n';
  std::cin >> mean2;
  std::cout << "Deviazione Standard:" << '\n';
  std::cin >> std2;
  
  }else{
    std::cout << "errore nel tipo di simulazione scelta. Riprovare: " << '\n' << "per un lancio singolo premere 1" << '\n' << "per N lanci premere 2" << '\n';
    std::cin >> input;
  }


  

  }


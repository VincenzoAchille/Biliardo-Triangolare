#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include "statisticsRoot.hpp"
#include "ball.hpp"


int main() {
  sf::Vector2f center(300, 450);
  float r1{200};
  float r2{100};
  float l{800};
  float y0{0.f};
  float theta0{0.7f};
  float v{1};
  /*std::cout << "inserisci i parametri per la forma del biliardo:" << '\n';
  std::cout << "r1 = ";
  std::cin >> r1;
  std::cout << "r2 = ";
  std::cin >> r2;
  std::cout << "l = ";
  std::cin >> l;*/
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
  sf::Vertex lowerBound[] = {
      sf::Vertex(sf::Vector2f(center.x, center.y + ball::getr1()),
                 sf::Color::Red),
      sf::Vertex(
          sf::Vector2f(center.x + ball::getl(), center.y + ball::getr2()),
          sf::Color::Red)};

  std::cout << "selezionare il tipo di simulazione. " << '\n'
            << "per un lancio singolo premere 1" << '\n'
            << "per N lanci premere 2" << '\n';
  int input;
  std::cin >> input;

  if (input == 1) {
    /*std::cout << "Inserire i parametri della pallina:" << '\n';
    std::cout << "y0 = ";
    std::cin >> y0;
    std::cout << "theta0 = ";
    std::cin >> theta0;
    rangeValidity(theta0, -static_cast<float>(M_PI / 2),
                  static_cast<float>(M_PI / 2));*/
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Biliardo Triangolare");
    rangeValidity(theta0, -static_cast<float>(M_PI/2),static_cast<float>(M_PI/2));
    float m = std::tan(theta0);
    ball b1(0, y0, m);
    sf::CircleShape shape1(ball::getRadius());
    shape1.setOrigin(10.f, 10.f);
    shape1.setPosition(center.x, center.y - y0);
    shape1.setFillColor(sf::Color::Cyan);
    float t{0};
    float h{0};
    float T{0};
    b1.dynamicsAnimated(upperBound ,lowerBound, t,h,T,
                        v);
    

  } else if (input == 2) {
    int N{100000};
    bool isDiscarted = true;
    float meanY0{0.};
    float meanTheta0{0.};
    float stdY0{10.};
    float stdTheta0{0.2f};
    /*std::cout << "Inserire il numero di tentativi:" << '\n';
    std::cin >> N;
    std::cout << "Vuoi scartare le palline che rimbalzano verso sinistra? Se "
                 "sì, premere 1 altrimenti 0"
              << '\n';
    std::cin >> isDiscarted;
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
    if (isDiscarted == 0) {
    } else {
    }*/
    std::array<double,8> statisticalParamters = statistics(N,meanY0,stdY0,meanTheta0,stdTheta0,isDiscarted);
    std::cout << "i parametri richiesti sono:" << '\n';
    std::array<std::string, 4> words = {" mean = ", " rms = ", " skewness = ", " kurtosis = "};
    for(size_t i{0}; i < 4;i++){
      std::string histName = "yf";
      std::cout << histName << words[i] << statisticalParamters[i]<< '\n';
    }
    std::cout << '\n'; 
    for(size_t i{0}; i < 4;i++){
      std::string histName = "thetaf";
      std::cout << histName << words[i] << statisticalParamters[i+4] << '\n';
    }


  } else {
    std::cout << "errore nel tipo di simulazione scelta. Riprovare: " << '\n'
              << "per un lancio singolo premere 1" << '\n'
              << "per N lanci premere 2" << '\n';
    std::cin >> input;
  }
}

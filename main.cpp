#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

#include "ball.hpp"
#include "statisticsRoot.hpp"

int main() {
  float r1{200};
  float r2{100};
  float l{1000};
  float y0{0.f};        
  float theta0{0.f};  
  const float animationSpeed{5};
  biliard::ball::radius(10.f);
  std::cout << "inserisci i parametri per la forma del biliardo:" << '\n';
  std::cout << "r1 = ";
  std::cin >> r1;
  std::cout << "r2 = ";
  std::cin >> r2;
  std::cout << "l = ";
  std::cin >> l;
  biliard::ball::r1(r1);
  biliard::ball::r2(r2);
  biliard::ball::l(l);
  std::cout << "selezionare il tipo di simulazione. " << '\n'
            << "per un lancio singolo premere 1" << '\n'
            << "per N lanci premere 2" << '\n';
  int selectedFunctionality;
  std::cin >> selectedFunctionality;

  if (selectedFunctionality == 1) {
    std::cout << "Inserire i parametri della pallina:" << '\n';
    std::cout << "y0 = ";
    std::cin >> y0;
    std::cout << "theta0 = ";
    std::cin >> theta0;
    biliard::rangeValidity(theta0, -static_cast<float>(M_PI / 2),
                  static_cast<float>(M_PI / 2));
    biliard::rangeValidity(theta0, -static_cast<float>(M_PI / 2),
                  static_cast<float>(M_PI / 2));
    const float m = std::tan(theta0);
    biliard::ball animatedBall(0, y0, m);
    animatedBall.ballDynamicsAnimated(animationSpeed);
    if (animatedBall.getDirection() == 0) {
      std::cout << "errore: moto verticale" << '\n';
      return 0;
    }
    std::cout << "yf = " << animatedBall.getY()
              << "theta0 = " << std::atan(animatedBall.getM()) << '\n';

  } else if (selectedFunctionality == 2) {
    int N{50};
    bool isDiscarted = false;
    float meanY0{0.f};
    float meanTheta0{0.f};
    float stdY0{1.f};
    float stdTheta0{1.f};
    std::cout << "Inserire il numero di tentativi:" << '\n';
    std::cin >> N;
    std::cout << "Vuoi scartare le palline che rimbalzano verso sinistra? Se "
                 "sì, premere 1 altrimenti 0"
              << '\n';
    std::cin >> isDiscarted;
    std::cout << "Inserire i parametri delle distribuzioni:" << '\n' << '\n';
    std::cout << "Angolo iniziale:" << '\n';
    std::cout << "Media:" << '\n';
    std::cin >> meanY0;
    std::cout << "Deviazione Standard:" << '\n' << '\n';
    std::cin >> stdY0;
    std::cout << "Altezza iniziale:" << '\n';
    std::cout << "Media:" << '\n';
    std::cin >> meanTheta0;
    std::cout << "Deviazione Standard:" << '\n';
    std::cin >> stdTheta0;
    if (isDiscarted == 0) {
    } else {
    }
    std::array<double, 9> statisticalParameters = biliard::statistics(
        N, meanY0, stdY0, meanTheta0, stdTheta0, isDiscarted);
    std::cout << "i parametri richiesti sono:" << '\n';
    std::array<std::string, 4> words = {
        " media = ", " rms = ", " asimmetria = ", " curtosi = "};
    for (size_t i{0}; i < 4; i++) {
      std::string histName = "yf";
      std::cout << histName << words[i] << statisticalParameters[i] << '\n';
    }
    std::cout << '\n';
    for (size_t i{0}; i < 4; i++) {
      std::string histName = "thetaf";
      std::cout << histName << words[i] << statisticalParameters[i + 4] << '\n'
                << '\n';
    }
    std::cout << "sono stati trovati " << statisticalParameters[8]
              << " moti verticali" << '\n';

  } else {
    std::cout << "errore nel tipo di simulazione scelta.\n";
    return 1;
  }
}

#ifndef METHODS_CPP
#define METHODS_CPP
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

inline void rangeValidity(float value, float a, float b) { //da capire come trattare la conversione agli estremi 
  float A = static_cast<float>(a);
  float B = static_cast<float>(b);
  if (A > value || value > B) {
    std::cout << "Errore: valorre fuori dal range" << '\n';
    exit(1);
  }
}

inline int sgn(float x) {
return x > 0 ? 1:-1;  
  // return (x > 0) - (x < 0);
}

inline void myPause() {
  int a;
  std::cin >> a;
  exit(1);
}

inline bool invert(int a) {
  if (a > 0) {
    return 1;
  } else {
    return 0;
  }
}

inline int bti(bool a) {
  if (a == 1) {
    return 1;
  } else {
    return -1;
  }
}

#endif
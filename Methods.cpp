#ifndef METHODS_CPP
#define METHODS_CPP
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

inline void rangeValidity(float value, float min, float max) {
    if (value >= min && value <= max) { 
        return; 
    }
    std::cout << min << ", " << max;
    throw std::out_of_range("Value out of range");  
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
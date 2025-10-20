#ifndef METHODS_CPP
#define METHODS_CPP
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "ball.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
const float pi = 3.141592653589793;

inline bool rangeValidity(float value, float a, float b){
    if(a > value || value > b){
        std::cout << "Errore: valorre fuori dal range" << '\n';
        exit(1);
}
}

inline int sgn(float x) {
return (x > 0) - (x < 0);
}

inline void myPause(){
    int a;
    std::cin >> a;
    exit(1);
}

inline bool invert(int a){
    if(a > 0){
        return 1;
    }else{
        return 0;
    }
}

inline int bti(bool a){
    if(a == 1){
        return 1;
    }else{
        return -1;
    }
}


#endif
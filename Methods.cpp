#ifndef METHODS_CPP
#define METHODS_CPP
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "ball.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

inline bool controlAngle(float angle, float a, float b){
    if(a < angle < b){
        return 0;
        std::cout << "angolo fuori dal range" << '\n';
        exit(1);
    }else{
        return 1;
    }
}

inline int sgn(float x) {
return (x > 0) - (x < 0);
}

inline void pause(){
    int a;
    std::cin >> a;
    exit(1);
}


#endif
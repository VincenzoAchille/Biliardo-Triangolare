#include <iostream>
#include <cstdlib>

bool controlAngle(float angle, float a, float b){
    if(a < angle < b){
        return 0;
        std::cout << "angolo fuori dal range" << '\n';
        exit(1);
    }else{
        return 1;
    }
}
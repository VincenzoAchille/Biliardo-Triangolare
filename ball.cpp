#include "ball.hpp"



ball::ball(float _x, float _y, float _vx, float _vy){
    x = _x;
    y = _y;
    vx = _vx;
    vy = _vy;
};

ball::ball(float _x, float _y) : ball(_x,_y,0.,0.) {};
//ball::ball(float _vx, float _vy) : ball(0.,0.,_vx,_vy) {};
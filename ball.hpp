#ifndef BALL_HPP
#define BALL_HPP

class ball{
    public:
    ball();
    ball(float x, float y);
    //ball(float vx, float vy);
    ball(float x, float y, float vx, float vy);

    private:
    float x;
    float y;
    float vx;
    float vy;
};

#endif
#include "doctest.h"

//verifiche primo urto, fare tutte le casistiche
//verifiche cambi di urto
//verifiche altri urti
//fare un test che mostra che i rimbalzi vanno sempre dentro il biliardo#include "body.hpp"
#include <cmath>
#include "Methods.cpp"
#include "ball.hpp"
#include <numbers>

TEST_CASE("First Impact") {

    float epsilon{1e-7};
    float y0[5] = {300, 100, 0, -100, -300};
    float pi = 3.141592653589793;
    float Theta0[5] ={pi/2, pi/4, 0, -pi/4, -pi/2};
    int i{0};
    int j{0};
    ball b1(0., y0[i],0.,0.,0);
    bool direction = 1;
    SUBCASE("General"){
        CHECK(b1.selector(std::tan(Theta0[j])) == 0);

    }
}
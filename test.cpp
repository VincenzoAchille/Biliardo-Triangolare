#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

//verifiche primo urto, fare tutte le casistiche
//verifiche cambi di urto
//verifiche altri urti
//fare un test che mostra che i rimbalzi vanno sempre dentro il biliardo#include "body.hpp"
#include <cmath>
#include "Methods.cpp"
#include "ball.hpp"
#include <numbers>

TEST_CASE("Controllo Funzioni") {

    float epsilon{1e-7};
    //float y0[5] = {300, 100, 0, -100, -300};
    float pi = 3.141592653589793;
    float Theta[8] ={pi/6, pi/3, 2*pi/3, 5*pi/6, -pi/6, -pi/3, -2*pi/3, -5*pi/6 };

    float ValoriControlloNewM[8] = {0.,0.,0.,0.,0.,0.,0.,0.};
    float ValoriControlloAngleWithNormal[8] = {(pi-12)/(2*(pi+3)),0.,0.,0.,0.,0.,0.,0.};
    bool ValoriControlloUpdown[8] = {1,1,1,1,0,0,0,0};
    float ValoriControlloNormal[8] = {2.,2.,2.,2.,-2.,-2.,-2.,-2.};
    
    int Direction;
    /*SUBCASE("updown"){
        for (int i = 0; i < 8; i++){
        CAPTURE(i); 
        CAPTURE(Theta[i]);
        evaluate(Theta[i],Direction,updown);
        ball b(500.,0.,std::tan(Theta[i]),Direction);
        CHECK(b.updown(Direction) == ValoriControlloUpdown[i]);
    }}
    SUBCASE("normal"){
        ball b(0.,0.,0.,1);
        float N = b.getmGiac();
        std::cout << "il coefficiente della normale è: " << N << '\n';

        for (int i = 0; i < 8; i++){
        CAPTURE(i);
        evaluate(Theta[i],Direction,updown);
        ball b(500.,0.,std::tan(Theta[i]),Direction);
        
        std::cout << "i parametri di interesse sono: " << "Direction= " << Direction << "e updown= " << updown << '\n';
        CAPTURE(b.normal());
        CHECK(b.normal() - ValoriControlloNormal[i] < 1e-2);
    }}*/
    /*SUBCASE("angleWithNormal"){
        for (int i = 0; i < 8; i++){
        evaluate(Theta[i],Direction);
        ball b(500.,0.,std::tan(Theta[i]),Direction);
        std::cout << "l'angolo è " << b.angleRespectNormal() << '\n';
        //CHECK(b.angleRespectNormal() - std::abs(ValoriControlloAngleWithNormal[i]) < 1e-2);
}}*/
    SUBCASE("newM"){
        for (int i = 0; i < 8; i++){
        evaluate(Theta[i],Direction);
        ball b(500.,0.,std::tan(Theta[i]),Direction);
        b.updateM();
        CHECK(b.getM() - ValoriControlloNewM[i] < 1e-2);
    }
}
}

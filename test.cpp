#include <SFML/System/Vector2.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

// verifiche primo urto, fare tutte le casistiche
// verifiche cambi di urto
// verifiche altri urti
// fare un test che mostra che i rimbalzi vanno sempre dentro il
// biliardo#include "body.hpp"
#include <cmath>
#include <numbers>
#include<limits>

#include "ball.hpp"

TEST_CASE("Controllo Setters") {
   sf::Vector2f _center (300.f, 450.f);
   sf::Vector2f _window (1600.f,900.f);
    SUBCASE("setCenter") {
    float valoriR1noThrow[6] = {0.f,0.1f,100.f,300.f,449.9f,450.f};
    float valoriR1Throw[4] = {-100, 450.1f, 1000., std::numeric_limits<float>::infinity()};
    for (int i{0}; i < 6; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriR1noThrow[i]);
     CHECK_NOTHROW(test.r1(valoriR1noThrow[i]));
    }
    for (int i{0}; i < 4; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriR1Throw[i]);
     CHECK_THROWS(test.r1(valoriR1Throw[i]));
    }
  
  }
   SUBCASE("setWindow") {
    float valoriR1noThrow[6] = {0.f,0.1f,100.f,300.f,449.9f,450.f};
    float valoriR1Throw[4] = {-100, 450.1f, 1000., std::numeric_limits<float>::infinity()};
    for (int i{0}; i < 6; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriR1noThrow[i]);
     CHECK_NOTHROW(test.r1(valoriR1noThrow[i]));
    }
    for (int i{0}; i < 4; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriR1Throw[i]);
     CHECK_THROWS(test.r1(valoriR1Throw[i]));
    }
  
  }
   ball::center(_center);
   ball::window(_window);
   SUBCASE("setr1") {
    float valoriR1noThrow[6] = {0.f,0.1f,100.f,300.f,449.9f,450.f};
    float valoriR1Throw[4] = {-100, 450.1f, 1000., std::numeric_limits<float>::infinity()};
    for (int i{0}; i < 6; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriR1noThrow[i]);
     CHECK_NOTHROW(test.r1(valoriR1noThrow[i]));
    }
    for (int i{0}; i < 4; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriR1Throw[i]);
     CHECK_THROWS(test.r1(valoriR1Throw[i]));
    }
  
  }
  SUBCASE("setr2") {
    float valoriR2noThrow[6] = {0.f,0.1f,100.f,300.f,449.9f,450.f};
    float valoriR2Throw[4] = {-100, -0.1f, 450.1f, 1000.}; //sarebbe da mettere infinito?
    for (int i{0}; i < 6; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriR2noThrow[i]);
     CHECK_NOTHROW(test.r2(valoriR2noThrow[i]));
    }
    for (int i{0}; i < 4; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriR2Throw[i]);
     CHECK_THROWS(test.r2(valoriR2Throw[i]));
    }

  }
  SUBCASE("setl") {
    float valoriLnoThrow[6] = {0.f,0.1f,100.f,800.f,1199.9f,1200.f};
    float valoriLThrow[4] ={-100, -0.1f, 1200.1f, 3000.f};
    for (int i{0}; i < 6; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriLnoThrow[i]);
     CHECK_NOTHROW(test.l(valoriLnoThrow[i]));
    }
    for (int i{0}; i < 4; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriLThrow[i]);
     CHECK_THROWS(test.l(valoriLThrow[i]));
    }

  }
}
  TEST_CASE("Controllo Costruttore"){
  SUBCASE("controllo X") {
    //controlli x //c'è qualcosa nella logica che non funziona mi sembra che vengano ripetuti più volte
    float valoriXnoThrow[6] = {0.f,0.1f,100.f,800.f,899.9f,900.f};
    float valoriXThrow[4] ={-100, -0.1f, 900.1f, 3000.f};
    for (int i{0}; i < 6; i++) {
     CAPTURE(valoriXnoThrow[i]);
     CHECK_NOTHROW(ball(valoriXnoThrow[i],0.,0.,1));
    }
    for (int i{0}; i < 4; i++) {
     CAPTURE(valoriXThrow[i]);
     CHECK_THROWS(ball(valoriXThrow[i],0.,0.,1));
    }
}
    SUBCASE("controllo Y"){
    ball::r1(200);
    ball::r2(100);
    float valoriYnoThrow[6] = {-200.f,-199.9f,0.f,100.f,199.9f,200.f};
    float valoriYThrow[4] ={-600, -200.1f, 200.1f, 1000.f};
    for (int i{0}; i < 6; i++) {
     CAPTURE(valoriYnoThrow[i]);
     CHECK_NOTHROW(ball(0.,valoriYnoThrow[i],0.,1));
    }
   for (int i{0}; i < 4; i++) {
     CAPTURE(valoriYThrow[i]);
     CHECK_THROWS(ball(0.,valoriYThrow[i],0.,1));
    }}

    SUBCASE("controllo direction"){
    int valoriDirectionnoThrow[2] = {1,-1};
    int valoriDirectionThrowInt[3] = {2,0,-4};
    float valoriDirectionThrow[6] {0.f,0.99f,1.01f,-0.99f,-1.01f, 3.f};
    for (int i{0}; i < 2; i++) {
     CAPTURE(valoriDirectionnoThrow[i]);
     CHECK_NOTHROW(ball(0.,0.,0.,valoriDirectionnoThrow[i]));
    }
    for (int i{0}; i < 6; i++) {
     CAPTURE(valoriDirectionThrow[i]);
     CHECK_THROWS(ball(0.,0.,0.,valoriDirectionThrow[i]));
    }
     for (int i{0}; i < 3; i++) {
     CAPTURE(valoriDirectionThrowInt[i]);
     CHECK_THROWS(ball(0.,0.,0.,valoriDirectionThrowInt[i]));
    }
    }
}
 /* TEST_CASE("Controllo Urti"){
  SUBCASE("controllo dynamics == dynamicsAnimated") {
    //controlli x //c'è qualcosa nella logica che non funziona mi sembra che vengano ripetuti più volte
    float valoriXnoThrow[6] = {0.f,0.1f,100.f,800.f,899.9f,900.f};
    float valoriXThrow[4] ={-100, -0.1f, 900.1f, 3000.f};
    for (int i{0}; i < 6; i++) {
     CAPTURE(valoriXnoThrow[i]);
     CHECK_NOTHROW(ball(valoriXnoThrow[i],0.,0.,1));
    }
    for (int i{0}; i < 4; i++) {
     CAPTURE(valoriXThrow[i]);
     CHECK_THROWS(ball(valoriXThrow[i],0.,0.,1));
    }
}
    
    SUBCASE("urti funzionanti") {
    //controlli x //c'è qualcosa nella logica che non funziona mi sembra che vengano ripetuti più volte
    float valoriXnoThrow[6] = {0.f,0.1f,100.f,800.f,899.9f,900.f};
    float valoriXThrow[4] ={-100, -0.1f, 900.1f, 3000.f};
    for (int i{0}; i < 6; i++) {
     CAPTURE(valoriXnoThrow[i]);
     CHECK_NOTHROW(ball(valoriXnoThrow[i],0.,0.,1));
    }
    for (int i{0}; i < 4; i++) {
     CAPTURE(valoriXThrow[i]);
     CHECK_THROWS(ball(valoriXThrow[i],0.,0.,1));
    }
}
}*/



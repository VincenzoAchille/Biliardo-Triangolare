#include <SFML/System/Vector2.hpp>
#include <stdexcept>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cmath>
#include "ball.hpp"

TEST_CASE("Controllo Setters General" * doctest::skip()) {
   
   SUBCASE("setWindow") { //da capire se è il più efficiente //cosa succede se per sbaglio ci metto un float o un double?
    int valoriWindowXNoThrow[5] = {0,1,1600,1919,1920};
    int valoriWindowXThrow[4] = {-100, -1, 1921,2300};
    int valoriWindowYNoThrow[5] = {0,1,900,1079,1080};
    int valoriWindowYThrow[4] = {-100, -1, 1081,1400};
    for (int i{0}; i < 5; i++) {
     sf::Vector2i test(valoriWindowXNoThrow[i],900);
     CAPTURE(valoriWindowXNoThrow[i]);
     CHECK_NOTHROW(ball::window(test));
    }
    for (int i{0}; i < 5; i++) {
     sf::Vector2i test(1600,valoriWindowYNoThrow[i]);
     CAPTURE(valoriWindowYNoThrow[i]);
     CHECK_NOTHROW(ball::window(test));
    }
    for (int i{0}; i < 4; i++) {
     sf::Vector2i test(valoriWindowXThrow[i],900);
     CAPTURE(valoriWindowXThrow[i]);
     CHECK_THROWS_AS(ball::window(test),std::out_of_range);}
    for (int i{0}; i < 4; i++) {
     sf::Vector2i test(1600,valoriWindowYThrow[i]);
     CAPTURE(valoriWindowYThrow[i]);
     CHECK_THROWS_AS(ball::window(test),std::out_of_range);}
    
    }
   SUBCASE("setCenter") { 
    sf::Vector2i dimension (1600,900);
    ball::window(dimension);
    float valoriCenterXNoThrow[7] = {0.f,0.01f,0.1f,300.f,1599.9f,1599.99f,1600.f};
    float valoriCenterXThrow[6] = {-100.f, -0.1f,-0.01f, 1600.01f,1600.1f,2000.f};
    float valoriCenterYNoThrow[7] = {0.f,0.01f,0.1f,450.f,899.9f,899.99f,900.f};
    float valoriCenterYThrow[6] = {-100.f, -0.1f,-0.01f, 900.01f,900.1f,1200.f};
    for (int i{0}; i < 7; i++) {
     sf::Vector2f test(valoriCenterXNoThrow[i],900);
     CAPTURE(valoriCenterXNoThrow[i]);
     CHECK_NOTHROW(ball::center(test));
    }
    for (int i{0}; i < 7; i++) {
     sf::Vector2f test(1600,valoriCenterYNoThrow[i]);
     CAPTURE(valoriCenterYNoThrow[i]);
     CHECK_NOTHROW(ball::center(test));
    }
    for (int i{0}; i < 6; i++) {
     sf::Vector2f test(valoriCenterXThrow[i],900);
     CAPTURE(valoriCenterXThrow[i]);
     CHECK_THROWS_AS(ball::center(test),std::out_of_range);}
    for (int i{0}; i < 6; i++) {
     sf::Vector2f test(1600,valoriCenterYThrow[i]);
     CAPTURE(valoriCenterYThrow[i]);
     CHECK_THROWS_AS(ball::center(test),std::out_of_range);}
    
    }
  
  }
   TEST_CASE("Controllo Setters Biliard" * doctest::skip()) {
   sf::Vector2i dimensionWindow (1600,900);
    ball::window(dimensionWindow);
   sf::Vector2f dimensionCenter (300.f,450.f);
    ball::center(dimensionCenter);
   SUBCASE("setr1") {
    float valoriR1noThrow[8] = {0.f,0.01f,0.1f,100.f,300.f,449.9f,449.99f,450.f};
    float valoriR1Throw[6] = {-100.f,-0.1f,-0.01f, 450.01f,450.1f, 1000.f};
    for (int i{0}; i < 8; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriR1noThrow[i]);
     CHECK_NOTHROW(test.r1(valoriR1noThrow[i]));
    }
    for (int i{0}; i < 6; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriR1Throw[i]);
     CHECK_THROWS(test.r1(valoriR1Throw[i]));
    }
  
  }
  SUBCASE("setr2") {
    float valoriR2noThrow[8] = {0.f,0.01f,0.1f,100.f,300.f,449.9f,449.99f,450.f};
    float valoriR2Throw[6] = {-100.f,-0.1f,-0.01f, 450.01f,450.1f, 1000.f}; //sarebbe da mettere infinito?
    for (int i{0}; i < 8; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriR2noThrow[i]);
     CHECK_NOTHROW(test.r2(valoriR2noThrow[i]));
    }
    for (int i{0}; i < 6; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriR2Throw[i]);
     CHECK_THROWS(test.r2(valoriR2Throw[i]));
    }

  }
  SUBCASE("setl") {
    float valoriLnoThrow[8] = {0.f,0.01f,0.1f, 100.f,1200.f,1299.9f,1299.99f,1300.f};
    float valoriLThrow[6] ={-100, -0.1f, -0.01f,1300.01f,1300.1f, 3000.f};
    for (int i{0}; i < 8; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriLnoThrow[i]);
     CHECK_NOTHROW(test.l(valoriLnoThrow[i]));
    }
    for (int i{0}; i < 6; i++) {
     ball test(0., 0., 0., 1);
     CAPTURE(valoriLThrow[i]);
     CHECK_THROWS(test.l(valoriLThrow[i]));
    }

  }
}
  TEST_CASE("Controllo Costruttore"){ //si può migliorare un pochino mettendo l dentro a mano
    sf::Vector2i dimensionWindow (1600,900);
    ball::window(dimensionWindow);
   sf::Vector2f dimensionCenter (300.f,450.f);
    ball::center(dimensionCenter);
    ball::l(1200.f);
    ball::r1(200.f); //per semplicità r1 > r2
    ball::r2(100.f);
  SUBCASE("controllo X") {
    float T = ball::getErrorTolerance();
    float valoriXnoThrow[8] = {0.f-T,0.01f-T,0.1f-T,100.f,1199.9f+T,1199.99f+T,1200.f+T};
    float valoriXThrow[6] ={-100, -0.1f-T,-0.01f-T,1200.01f+T, 1200.1f+T, 3000.f};
    for (int i{0}; i < 8; i++) {
     CAPTURE(valoriXnoThrow[i]);
     CHECK_NOTHROW(ball(valoriXnoThrow[i],0.,0.,1));
    }
    for (int i{0}; i < 6; i++) {
     CAPTURE(valoriXThrow[i]);
     CHECK_THROWS(ball(valoriXThrow[i],0.,0.,1));
    }
}
    SUBCASE("controllo Y"){
    float T = ball::getErrorTolerance();
    float valoriYnoThrow[8] = {-200-T,-199.9f-T,-199.99f-T,0.f,199.9f+T,199.99f+T,200.f+T};
    float valoriYThrow[6] ={-400.f, -200.1f-T,-200.01f-T,200.01f+T, 200.1f+T, 500.f};
    for (int i{0}; i < 8; i++) {
     CAPTURE(valoriYnoThrow[i]);
     CHECK_NOTHROW(ball(0.,valoriYnoThrow[i],0.,1));
    }
   for (int i{0}; i < 6; i++) {
     CAPTURE(valoriYThrow[i]);
     CHECK_THROWS(ball(0.,valoriYThrow[i],0.,1));
    }}

    SUBCASE("controllo direction"){
    int valoriDirectionnoThrow[2] = {1,-1};
    int valoriDirectionThrowInt[3] = {2,0,-4};
    float valoriDirectionThrowFloat[6] {0.f,0.99f,1.01f,-0.99f,-1.01f, 3.f};
    for (int i{0}; i < 2; i++) {
     CAPTURE(valoriDirectionnoThrow[i]);
     CHECK_NOTHROW(ball(0.,0.,0.,valoriDirectionnoThrow[i]));
    }
    for (int i{0}; i < 6; i++) {
     CAPTURE(valoriDirectionThrowFloat[i]);
     CHECK_THROWS_AS(ball(0.,0.,0.,valoriDirectionThrowFloat[i]),std::invalid_argument);
    }
     for (int i{0}; i < 3; i++) {
     CAPTURE(valoriDirectionThrowInt[i]);
     CHECK_THROWS_AS(ball(0.,0.,0.,valoriDirectionThrowInt[i]),std::out_of_range);
    }
    }
}
   TEST_CASE("Controllo Urti"){
    sf::Vector2i dimensionWindow (1600,900);
    ball::window(dimensionWindow);
    sf::Vector2f dimensionCenter (300.f,450.f);
    ball::center(dimensionCenter);
    ball::l(1200);
    int t{0};
    int T{0};
    int h{0};
    sf::RenderWindow window(sf::VideoMode(ball::getWindow().x, ball::getWindow().y), "Biliardo Triangolare");
   /*SUBCASE("controllo dynamics == dynamicsAnimated") {
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
}*/
    
    SUBCASE("urti funzionanti(r1 > r2)") {
    ball::r1(200);
    ball::r2(100);
    float y0[] = {};
    float theta0[] = {};
    float finalX[] = {};
    float finalY[] = {};
    float finalM[] = {};
    int finalDirection[] = {};
    float t{0.f};
    float h{0.f};
    float T{0.f};
    for (int i{0}; i < 6; i++) {
    ball test(0.,y0[i],std::tan(theta0[i]));
     test.dynamics(ball::getCenter(),window,t,h,T);
     CHECK(std::abs(test.getX()- finalX[i]) < 5.);
     CHECK(std::abs(test.getY()- finalY[i]) < 5.);
     CHECK(std::abs(test.getM()- finalM[i]) < 5.);
     CHECK(test.getDirection() == finalDirection[i]);
    }
    
}
   SUBCASE("urti funzionanti(r2 > r1)") {
    ball::r1(100);
    ball::r2(200);
    float y0[1] = {1.};
    float theta0[3] = {1,2,3};
    float finalX[] = {};
    float finalY[] = {};
    float finalM[] = {};
    float finalDirection[] = {};
    float t{0.f};
    float h{0.f};
    float T{0.f};
    for (int i{0}; i < 6; i++) {
     ball test(0.,y0[i],std::tan(theta0[i]));
     test.dynamics(ball::getCenter(),window,t,h,T);
     CHECK(std::abs(test.getX()- finalX[i]) < 5.);
     CHECK(std::abs(test.getY()- finalY[i]) < 5.);
     CHECK(std::abs(test.getM()- finalM[i]) < 5.);
     CHECK(test.getDirection() == finalDirection[i]);
   
}}  SUBCASE("urti funzionanti(r1 == r2)") {
    ball::r1(200);
    ball::r2(100);
    float y0[] = {};
    float theta0[] = {};
    float finalX[] = {};
    float finalY[] = {};
    float finalM[] = {};
    float finalDirection[] = {};
    float t{0.f};
    float h{0.f};
    float T{0.f};
    for (int i{0}; i < 6; i++) {
     ball test(0.,y0[i],std::tan(theta0[i]));
     test.dynamics(ball::getCenter(),window,t,h,T);
     CHECK(std::abs(test.getX()- finalX[i]) < 5.);
     CHECK(std::abs(test.getY()- finalY[i]) < 5.);
     CHECK(std::abs(test.getM()- finalM[i]) < 5.);
     CHECK(test.getDirection() == finalDirection[i]);
}
}}



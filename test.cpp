#include <SFML/System/Vector2.hpp>
//#include <stdexcept>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cmath>

#include "ball.hpp"
#include "doctest.h"

namespace biliard {
TEST_CASE("Controllo Setters General") {
  SUBCASE("setWindow") {
    int valuesWindowXNoThrow[5] = {0, 1, 1600, 1919, 1920};
    int valuesWindowXThrow[4] = {-100, -1, 1921, 2300};
    int valuesWindowYNoThrow[5] = {0, 1, 900, 1079, 1080};
    int valuesWindowYThrow[4] = {-100, -1, 1081, 1400};
    for (int i{0}; i < 5; i++) {
      sf::Vector2i test(valuesWindowXNoThrow[i], 900);
      CAPTURE(valuesWindowXNoThrow[i]);
      CHECK_NOTHROW(ball::window(test));
    }
    for (int i{0}; i < 5; i++) {
      sf::Vector2i test(1600, valuesWindowYNoThrow[i]);
      CAPTURE(valuesWindowYNoThrow[i]);
      CHECK_NOTHROW(ball::window(test));
    }
    for (int i{0}; i < 4; i++) {
      sf::Vector2i test(valuesWindowXThrow[i], 900);
      CAPTURE(valuesWindowXThrow[i]);
      CHECK_THROWS_AS(ball::window(test), std::out_of_range);
    }
    for (int i{0}; i < 4; i++) {
      sf::Vector2i test(1600, valuesWindowYThrow[i]);
      CAPTURE(valuesWindowYThrow[i]);
      CHECK_THROWS_AS(ball::window(test), std::out_of_range);
    }
  }
  SUBCASE("setCenter") {
    sf::Vector2i windowDimension(1600, 900);
    ball::window(windowDimension);
    float valuesCenterXNoThrow[7] = {0.f,     0.01f,    0.1f,  300.f,
                                     1599.9f, 1599.99f, 1600.f};
    float valuesCenterXThrow[6] = {-100.f,   -0.1f,   -0.01f,
                                   1600.01f, 1600.1f, 2000.f};
    float valuesCenterYNoThrow[7] = {0.f,    0.01f,   0.1f, 450.f,
                                     899.9f, 899.99f, 900.f};
    float valuesCenterYThrow[6] = {-100.f,  -0.1f,  -0.01f,
                                   900.01f, 900.1f, 1200.f};
    for (int i{0}; i < 7; i++) {
      sf::Vector2f test(valuesCenterXNoThrow[i], 900);
      CAPTURE(valuesCenterXNoThrow[i]);
      CHECK_NOTHROW(ball::center(test));
    }
    for (int i{0}; i < 7; i++) {
      sf::Vector2f test(1600, valuesCenterYNoThrow[i]);
      CAPTURE(valuesCenterYNoThrow[i]);
      CHECK_NOTHROW(ball::center(test));
    }
    for (int i{0}; i < 6; i++) {
      sf::Vector2f test(valuesCenterXThrow[i], 900);
      CAPTURE(valuesCenterXThrow[i]);
      CHECK_THROWS_AS(ball::center(test), std::out_of_range);
    }
    for (int i{0}; i < 6; i++) {
      sf::Vector2f test(1600, valuesCenterYThrow[i]);
      CAPTURE(valuesCenterYThrow[i]);
      CHECK_THROWS_AS(ball::center(test), std::out_of_range);
    }
  }
}
TEST_CASE("Controllo Setters Biliard" * doctest::skip()) {
  sf::Vector2i dimensionWindow(1600, 900);
  ball::window(dimensionWindow);
  sf::Vector2f dimensionCenter(300.f, 450.f);
  ball::center(dimensionCenter);
  SUBCASE("setr1") {
    float valuesR1noThrow[8] = {0.f,   0.01f,  0.1f,    100.f,
                                300.f, 449.9f, 449.99f, 450.f};
    float valuesR1Throw[6] = {-100.f, -0.1f, -0.01f, 450.01f, 450.1f, 1000.f};
    for (int i{0}; i < 8; i++) {
      ball test(0., 0., 0., 1);
      CAPTURE(valuesR1noThrow[i]);
      CHECK_NOTHROW(test.r1(valuesR1noThrow[i]));
    }
    for (int i{0}; i < 6; i++) {
      ball test(0., 0., 0., 1);
      CAPTURE(valuesR1Throw[i]);
      CHECK_THROWS(test.r1(valuesR1Throw[i]));
    }
  }
  SUBCASE("setr2") {
    float valuesR2noThrow[8] = {0.f,   0.01f,  0.1f,    100.f,
                                300.f, 449.9f, 449.99f, 450.f};
    float valuesR2Throw[6] = {-100.f, -0.1f, -0.01f, 450.01f, 450.1f, 1000.f};
    for (int i{0}; i < 8; i++) {
      ball test(0., 0., 0., 1);
      CAPTURE(valuesR2noThrow[i]);
      CHECK_NOTHROW(test.r2(valuesR2noThrow[i]));
    }
    for (int i{0}; i < 6; i++) {
      ball test(0., 0., 0., 1);
      CAPTURE(valuesR2Throw[i]);
      CHECK_THROWS(test.r2(valuesR2Throw[i]));
    }
  }
  SUBCASE("setl") {
    float valuesLnoThrow[8] = {0.f,    0.01f,   0.1f,     100.f,
                               1200.f, 1299.9f, 1299.99f, 1300.f};
    float valuesLThrow[6] = {-100, -0.1f, -0.01f, 1300.01f, 1300.1f, 3000.f};
    for (int i{0}; i < 8; i++) {
      ball test(0., 0., 0., 1);
      CAPTURE(valuesLnoThrow[i]);
      CHECK_NOTHROW(test.l(valuesLnoThrow[i]));
    }
    for (int i{0}; i < 6; i++) {
      ball test(0., 0., 0., 1);
      CAPTURE(valuesLThrow[i]);
      CHECK_THROWS(test.l(valuesLThrow[i]));
    }
  }
}
TEST_CASE("Controllo Costruttore" * doctest::skip()) {
  sf::Vector2i dimensionWindow(1600, 900);
  ball::window(dimensionWindow);
  sf::Vector2f dimensionCenter(300.f, 450.f);
  ball::center(dimensionCenter);
  ball::l(1200.f);
  ball::r1(200.f);
  ball::r2(100.f);
  SUBCASE("controllo X") {
    float errorTolerance = ball::getErrorTolerance();
    float valuesXnoThrow[8] = {
        0.f - errorTolerance,     0.01f - errorTolerance,
        0.1f - errorTolerance,    100.f,
        1199.9f + errorTolerance, 1199.99f + errorTolerance,
        1200.f + errorTolerance};
    float valuesXThrow[6] = {-100,
                             -0.1f - errorTolerance,
                             -0.01f - errorTolerance,
                             1200.01f + errorTolerance,
                             1200.1f + errorTolerance,
                             3000.f};
    for (int i{0}; i < 8; i++) {
      CAPTURE(valuesXnoThrow[i]);
      CHECK_NOTHROW(ball(valuesXnoThrow[i], 0., 0., 1));
    }
    for (int i{0}; i < 6; i++) {
      CAPTURE(valuesXThrow[i]);
      CHECK_THROWS(ball(valuesXThrow[i], 0., 0., 1));
    }
  }
  SUBCASE("controllo Y") {
    ball::radius(10.f);
    float valuesYnoThrow[8] = {
        -200 + ball::getRadius(),     -199.9f +ball::getRadius(),
        -199.99f +ball::getRadius(), 0.f,
        199.9f -ball::getRadius(),   199.99f -ball::getRadius(),
        200.f -ball::getRadius()};
    float valuesYThrow[6] = {-400.f,
                             -200.1f + ball::getRadius(),
                             -200.01f + ball::getRadius(),
                             200.01f - ball::getRadius(),
                             200.1f - ball::getRadius(),
                             500.f};
    for (int i{0}; i < 8; i++) {
      CAPTURE(valuesYnoThrow[i]);
      CHECK_NOTHROW(ball(0., valuesYnoThrow[i], 0., 1));
    }
    for (int i{0}; i < 6; i++) {
      CAPTURE(valuesYThrow[i]);
      CHECK_THROWS(ball(0., valuesYThrow[i], 0., 1));
    }
  }

  SUBCASE("controllo direction") {
    int valuesDirectionnoThrow[2] = {1, -1};
    int valuesDirectionThrowInt[3] = {2, 0, -4};
    for (int i{0}; i < 2; i++) {
      CAPTURE(valuesDirectionnoThrow[i]);
      CHECK_NOTHROW(ball(0., 0., 0., valuesDirectionnoThrow[i]));
    }
    for (int i{0}; i < 3; i++) {
      CAPTURE(valuesDirectionThrowInt[i]);
      CHECK_THROWS_AS(ball(0., 0., 0., valuesDirectionThrowInt[i]),
                      std::out_of_range);
    }
  }
}
TEST_CASE("Controllo Urti") {
  sf::Vector2i dimensionWindow(1600, 900);
  ball::window(dimensionWindow);
  sf::Vector2f dimensionCenter(300.f, 450.f);
  ball::center(dimensionCenter);
  ball::l(1000);

  SUBCASE("urti funzionanti(r1 > r2)") {
    ball::r1(200);
    ball::r2(100);
    ball::radius(0.01f);
    float y0[6] = {0.f, 0.f, 100.f, -100.f, 199.9f, -199.9f};
    float theta0[6] = {1.2f, -1.2f, 0.3f, 0.3f, 0.5f, -0.5f};
    float finalY[6] = {-104.6f, 104.6f, 56.6f, -18.9f, 92.8f, -92.88f};
    float finalTheta[6] = {0.42f, -0.42f, 0.69f, -0.49f, 2.49f, -2.49f};
    for (int i{0}; i < 6; i++) {
      ball test(0., y0[i], std::tan(theta0[i]));

      test.ballDynamics();

      CAPTURE(y0[i]);
      CAPTURE(test.getY());
      CAPTURE(finalY[i]);
      CHECK(std::abs(test.getY() - finalY[i]) < 5.);
      CHECK(std::abs(std::atan(test.getM()) - finalTheta[i]) < 5.);
    }
  }
  SUBCASE("urti funzionanti(r2 > r1)") {
    ball::r1(100);
    ball::r2(200);
    ball::radius(0.01f);
    float y0[6] = {0.f, 0.f, 50.f, -50.f, 99.9f, -99.9f};
    float theta0[6] = {1.2f, -1.2f, 0.3f, 0.3f, 0.8f, -0.8f};
    float finalY[6] = {-161.21f, 161.22f, 47.01f, 143.03f, 144.37f, -144.37f};
    float finalTheta[6] = {0.40f, -0.40f, -0.10f, -0.10f, 0.40f, 0.40f};
    for (int i{0}; i < 6; i++) {
      ball test(0., y0[i], std::tan(theta0[i]));
      test.ballDynamics();
      CHECK(std::abs(test.getY() - finalY[i]) < 5.);
      CHECK(std::abs(std::atan(test.getM()) - finalTheta[i]) < 5.);
    }
  }
  SUBCASE("urti funzionanti(r1 == r2)") {
    ball::r1(200);
    ball::r2(200);
    ball::radius(0.01f);
    float y0[6] = {0.f, 0.f, 100.f, -100.f, 199.9f, -199.9f};
    float theta0[6] = {1.2f, -1.2f, 0.3f, 0.3f, 0.5f, -0.5f};
    float finalY[6] = {172.1f, -172.1f, -9.33f, 190.6f, -53.79f, 53.79f};
    float finalTheta[6] = {1.2f, -1.2f, -0.3f, -0.3f, 0.5f, -0.5f};

    for (int i{0}; i < 6; i++) {
      ball test(0.f, y0[i], std::tan(theta0[i]));
      test.ballDynamics();
      CAPTURE(y0[i]);
      CAPTURE(theta0[i]);
      CAPTURE(test.getY());
      CAPTURE(finalY[i]);
      CHECK(std::abs(test.getY() - finalY[i]) < 5.);
      CHECK(std::abs(std::atan(test.getM()) - finalTheta[i]) < 5.);
    }
  }
}
}  // namespace biliard
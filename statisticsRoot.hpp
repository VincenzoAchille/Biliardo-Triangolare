#include <TCanvas.h>
#include <TF1.h>
#include <TH1.h>
#include <TH1F.h>
#include <TRandom.h>

#include <algorithm>
#include <array>

#include "ball.hpp"

namespace biliard {
inline int calculateBins(int N) {
  int bins = static_cast<int>(std::sqrt(N));
  return bins;
}

inline std::array<double, 9> statistics(int N, float meanY0, float stdY0,
                                        float meanTheta0, float stdTheta0,
                                        bool isDiscarded) {
  gRandom->SetSeed(0);
  rangeValidity(meanY0, -ball::getr1(), ball::getr1());
  rangeValidity(meanTheta0, -static_cast<float>(M_PI),
                static_cast<float>(M_PI));
  rangeValidity(stdY0, 0.f);
  rangeValidity(stdTheta0, 0.f);

  float estremi = std::max(ball::getr1(), ball::getr2());
  TH1F yfHist("y finali", "", calculateBins(N), -estremi, estremi);
  TH1F thetafHist("angoli finali", "", calculateBins(N), -M_PI / 2, M_PI / 2);

  int i{0};
  int verticalMotionCounter{0};
  while (i < N) {
    float y0Rand = static_cast<float>(gRandom->Gaus(meanY0, stdY0));
    if ((y0Rand < (-ball::getr1() + ball::getRadius())) ||
        (y0Rand > (ball::getr1() - ball::getRadius()))) {
      continue;
    }
    float theta0Rand = static_cast<float>(gRandom->Gaus(meanTheta0, stdTheta0));
    if ((theta0Rand < -M_PI / 2) || (theta0Rand > M_PI / 2)) {
      continue;
    }
    float m = std::tan(static_cast<float>(theta0Rand));
    ball randomBall(0.f, y0Rand, m);

    randomBall.ballDynamics();

    if (isDiscarded == true) {
      if (randomBall.getDirection() != -1) {
        if (randomBall.getDirection() != 0) {
          yfHist.Fill(randomBall.getY());
          float thetaf = std::atan(randomBall.getM());
          thetafHist.Fill(thetaf);
        } else {
          verticalMotionCounter++;
        }
      }
    } else {
      if (randomBall.getDirection() != 0) {
        yfHist.Fill(randomBall.getY());
        float thetaf = std::atan(randomBall.getM());
        thetafHist.Fill(thetaf);
      } else {
        verticalMotionCounter++;
      }
    }

    i++;
  }

  TCanvas canvas("canvas", "Both Distributions", 1000, 600);
  canvas.Divide(2, 1);

  canvas.cd(1);
  yfHist.SetLineColor(kBlue);
  yfHist.Draw();

  canvas.cd(2);
  thetafHist.SetLineColor(kRed);
  thetafHist.Draw();

  canvas.SaveAs("distributions.png");

  system("eog --single-window distributions.png");

  double yfMean = yfHist.GetMean();
  double yfRMS = yfHist.GetRMS();
  double yfSkewness = yfHist.GetSkewness();
  double yfKurtosis = yfHist.GetKurtosis();
  //
  double thetafMean = thetafHist.GetMean();
  double thetafRMS = thetafHist.GetRMS();
  double thetafSkewness = thetafHist.GetSkewness();
  double thetafKurtosis = thetafHist.GetKurtosis();
  std::array<double, 9> statisticalParameter = {
      yfMean,
      yfRMS,
      yfSkewness,
      yfKurtosis,
      thetafMean,
      thetafRMS,
      thetafSkewness,
      thetafKurtosis,
      static_cast<float>(verticalMotionCounter)};
  return statisticalParameter;
}
}  // namespace biliard
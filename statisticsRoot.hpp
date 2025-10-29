#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TH1F.h>
#include <TRandom.h>
#include "ball.hpp"
#include <array>
#include <algorithm>
//problema con valori limite
inline int calculateBins(int N) {
     int bins = static_cast<int>(3.0 * sqrt(N));
    return bins;}

inline std::array<double,8> statistics(int N, float meanY0, float stdY0, float meanTheta0, float stdTheta0,bool isDiscarded) {
  rangeValidity(meanY0, -ball::getr1(), ball::getr1());
  rangeValidity(meanTheta0, -static_cast<float>(M_PI), static_cast<float>(M_PI));
  rangeValidity(stdY0,0.f);
  rangeValidity(stdTheta0, 0.f);
  
  float estremi = std::max(ball::getr1(), ball::getr2());
  TH1F yfHist ("y finali", "", calculateBins(N), -estremi, estremi);
  TH1F thetafHist ("angoli finali", "", calculateBins(N), -M_PI/2, M_PI/2);
  //TH1F *y0Hist = new TH1F("angoli iniziali", "", calculateBins(N), -ball::getr1(), ball::getr1());
  float h{0};
  float T{0};
  //gRandom->SetSeed(12345);
  int i{0};
  //std::cout << "r1 è: " << ball::getr1() << '\n';
  while(i < N) {
    float y0Rand = static_cast<float>(gRandom->Gaus(meanY0,stdY0));
    if((y0Rand < -ball::getr1()) || (y0Rand > ball::getr1())){
      std::cout<< "entrato in if y0" << '\n';
      continue;}
    float theta0Rand = static_cast<float>(gRandom->Gaus(meanTheta0, stdTheta0));
    if((theta0Rand < -M_PI/2) || (theta0Rand > M_PI/2)) {

      //std::cout<< "entrato in if theta0" << '\n';
      continue;}
    float m = std::tan(static_cast<float>(theta0Rand));
    std::cout << "valore generato: " << "y0 = " << y0Rand << " theta0 = " << theta0Rand << '\n'; 
    ball randomBall(0.f,y0Rand,m);
    //y0Hist->Fill(y0Rand);
    //std::cout << "randomBall generata correttamente" << '\n';
    randomBall.dynamics(h,T);
    //std::cout << "dynamics eseguita corretamente" << '\n';
    if(isDiscarded == true){
    if(randomBall.getDirection() == 1){
      yfHist.Fill(randomBall.getY());
    float thetaf = std::atan(randomBall.getM());
    thetafHist.Fill(thetaf);

    }}else{
      yfHist.Fill(randomBall.getY());
    float thetaf = std::atan(randomBall.getM());
    thetafHist.Fill(thetaf);
    }
    i++;
    //std::cout <<"numero iterazioni = "<< i << '\n';
   }
   TCanvas *c1 = new TCanvas("c1", "Both Distributions", 1000, 600);
   c1->Divide(2,1);  // Divide il canvas in 2 colonne, 1 riga

   c1->cd(1);        // Seleziona il primo pad
   yfHist.SetLineColor(kBlue);
   yfHist.Draw();

  c1->cd(2);        // Seleziona il secondo pad  
  thetafHist.SetLineColor(kRed);
  thetafHist.Draw();

  c1->SaveAs("distributions.png");   
  
  system("eog --single-window distributions.png");
   //TCanvas *c2 = new TCanvas("c1", "Both Distributions", 1000, 600);
   //y0Hist->Draw();
  // c2->SaveAs("distribuzione_y0.png");
   // system("eog --single-window distribuzione_y0.png");
   double yfMean = yfHist.GetMean();
   double yfRMS = yfHist.GetRMS();
   double yfSkewness = yfHist.GetSkewness();
   double yfKurtosis = yfHist.GetKurtosis();
   //
   double thetafMean = thetafHist.GetMean();
   double thetafRMS = thetafHist.GetRMS();
   double thetafSkewness = thetafHist.GetSkewness();
   double thetafKurtosis = thetafHist.GetKurtosis();
   std::array<double, 8>statisticalParameter = {yfMean,yfRMS,yfSkewness,yfKurtosis,thetafMean,thetafRMS, thetafSkewness,thetafKurtosis}; 
   return statisticalParameter;
}
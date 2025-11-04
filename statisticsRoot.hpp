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
     int bins = static_cast<int>(std::sqrt(N));
    return bins;}

inline std::array<double,8> statistics(int N, float meanY0, float stdY0, float meanTheta0, float stdTheta0,bool isDiscarded) {
  rangeValidity(meanY0, -ball::getr1(), ball::getr1());
  rangeValidity(meanTheta0, -static_cast<float>(M_PI), static_cast<float>(M_PI));
  rangeValidity(stdY0,0.f);
  rangeValidity(stdTheta0, 0.f);
  
  float estremi = std::max(ball::getr1(), ball::getr2());
  TH1F yfHist ("y finali", "", calculateBins(N), -estremi, estremi);
  TH1F thetafHist ("angoli finali", "", calculateBins(N), -M_PI/2, M_PI/2);
  
  int i{0};
  
  while(i < N) {
    float y0Rand = static_cast<float>(gRandom->Gaus(meanY0,stdY0));
    if((y0Rand < -ball::getr1()) || (y0Rand > ball::getr1())){
      
      continue;}
    float theta0Rand = static_cast<float>(gRandom->Gaus(meanTheta0, stdTheta0));
    if((theta0Rand < -M_PI/2) || (theta0Rand > M_PI/2)) {

      
      continue;}
    float m = std::tan(static_cast<float>(theta0Rand));
    ball randomBall(0.f,y0Rand,m);
    std::cout << "inizializzazione completa per la pallina" << i <<'\n';
    std::cout << randomBall.getX() <<", " << randomBall.getY() << ", " << std::atan(randomBall.getM()) << '\n';
    std::cout << "chiamata Dyanamics" << '\n';
    randomBall.ballDynamics();
    std::cout << "terminata Dynamics" << '\n';
    if(isDiscarded == true){
    if(randomBall.getDirection() == 1){
      yfHist.Fill(randomBall.getY());
    float thetaf = std::atan(randomBall.getM());
    thetafHist.Fill(thetaf);

    }}else{
      std::cout << "entrato in non scarto " << '\n';
      yfHist.Fill(randomBall.getY());
    float thetaf = std::atan(randomBall.getM());
    thetafHist.Fill(thetaf);
   
    }
    i++;
   
   
   }
   
   TCanvas c1 ("c1", "Both Distributions", 1000, 600);
   c1.Divide(2,1);  

   c1.cd(1);        
   yfHist.SetLineColor(kBlue);
   yfHist.Draw();

  c1.cd(2);       
  thetafHist.SetLineColor(kRed);
  thetafHist.Draw();

  c1.SaveAs("distributions.png");   
  
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
   std::array<double, 8>statisticalParameter = {yfMean,yfRMS,yfSkewness,yfKurtosis,thetafMean,thetafRMS, thetafSkewness,thetafKurtosis}; 
   return statisticalParameter;
}
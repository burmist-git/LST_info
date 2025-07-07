//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <time.h>

using namespace std;

Double_t exp_dist(Double_t lam, TRandom3 *rnd){
  return -TMath::Log(rnd->Uniform())/lam;
}

Int_t plots_exp_dist(){
  //
  TRandom3 *rnd = new TRandom3(1231231);
  TH1D *h1_lam1 = new TH1D("h1_lam1","h1_lam1",200, 0.001,10.0);
  TH1D *h1_lam2 = new TH1D("h1_lam2","h1_lam2",200, 0.001,10.0);

  
  Double_t lam1 = 3.0;
  Double_t lam2 = 6.0;
  //
  for(Int_t i = 0;i<100000;i++){
    h1_lam1->Fill(exp_dist(lam1, rnd));
    h1_lam2->Fill(exp_dist(lam2, rnd));
  }
  TCanvas *c1 = new TCanvas("c1","c1",10,10,600,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //
  //h1->SetMinimum(0);
  //h1->Draw("errors");
  h1_lam2->Draw();
  h1_lam1->SetLineColor(kRed);
  h1_lam1->Draw("sames");
  return 0;
}

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

Double_t power_law(Double_t *x, Double_t *par){
  Double_t A  = par[0];
  Double_t B  = par[1];
  Double_t val = A/(TMath::Power(x[0],B));
  return val;
}

//
void read_atm(TString atmFileName, TGraph *gr_Alt_km, TGraph *gr_rho_g_cm3, TGraph *gr_thick_g_cm2, TGraph *gr_n_m);  
Double_t beta_vs_p_m( Double_t p_gev, Double_t m_gev);
Double_t theta_vs_n_beta( Double_t n, Double_t beta);
void TH1D_norm( TH1D *h1, Double_t norm);
void load_ring_radius_dist(TH1D *h1);

Int_t plots_power_law_dist(){


  //TString fileN;
  //fileN = "./histSingle.root";
  //TFile *f1 = new TFile(fileN.Data());
  //TH1D *h1_ring_radius = (TH1D*)f1->Get("h1_ring_radius_all");
  TH1D *h1_ring_radius = new TH1D("h1_ring_radius","h1_ring_radius",1000,0,2);
  load_ring_radius_dist(h1_ring_radius);

  
  Double_t sigma_system = 0.02;
  
  Double_t eMin = 6.0;
  Double_t eCut = 11.5;
  Double_t eMax = 100.0;

  TH1D *h1 = new TH1D("h1","h1",10000,eMin,eMax);
  TH1D *h1_theta_w = new TH1D("h1_theta_w","h1_theta_w",1000, 0, 1.5);
  TH1D *h1_theta_s = new TH1D("h1_theta_s","h1_theta_s",1000, 0, 1.5);
  //
  //
  //
  //
  //
  TString atmFileName_winter;
  TString atmFileName_summer;
  atmFileName_winter = "./atmprof8.dat";
  atmFileName_summer = "./atmprof7.dat";
  //
  //
  TGraph *gr_Alt_km_winter = new TGraph();
  TGraph *gr_rho_g_cm3_winter = new TGraph();
  TGraph *gr_thick_g_cm2_winter = new TGraph();
  TGraph *gr_n_m_winter = new TGraph();
  //
  //
  TGraph *gr_Alt_km_summer = new TGraph();
  TGraph *gr_rho_g_cm3_summer = new TGraph();
  TGraph *gr_thick_g_cm2_summer = new TGraph();
  TGraph *gr_n_m_summer = new TGraph();
  //  
  //
  //
  read_atm( atmFileName_winter, gr_Alt_km_winter, gr_rho_g_cm3_winter, gr_thick_g_cm2_winter, gr_n_m_winter);
  read_atm( atmFileName_summer, gr_Alt_km_summer, gr_rho_g_cm3_summer, gr_thick_g_cm2_summer, gr_n_m_summer);  
  //
  //
  //
  //
  TRandom3 *rnd = new TRandom3(123123);
  //for(Int_t i = 0;i<100000000;i++)
  //h1->Fill(TMath::Sqrt(1.0/(rnd->Uniform(1.0/eMax/eMax,1.0/eMin/eMin))));
  for(Int_t i = 0;i<10000000;i++){
    double alpha = 2.7;
    double exponent = 1.0 - alpha;
    double xmin_pow = TMath::Power(eMin, exponent);
    double eCut_pow = TMath::Power(eCut, exponent);
    double xmax_pow = TMath::Power(eMax, exponent);
    double var = TMath::Power(rnd->Uniform() * (xmax_pow - eCut_pow) + eCut_pow, 1.0 / exponent);
    h1->Fill(var);
    Double_t p = var;
    Double_t b = beta_vs_p_m(p,0.1057);
    Double_t n_w = gr_n_m_winter->Eval(2.0);
    Double_t n_s = gr_n_m_summer->Eval(2.0);
    Double_t t_w = theta_vs_n_beta(n_w,b) + rnd->Gaus(0.0,sigma_system);
    Double_t t_s = theta_vs_n_beta(n_s,b) + rnd->Gaus(0.0,sigma_system);
    if(t_w>0.8)
      h1_theta_w->Fill(t_w);
    if(t_s>0.8)
      h1_theta_s->Fill(t_s);
  }
  //
  //
  for(Int_t i = 0;i<13000000;i++){
    double alpha =1.39;
    double exponent = 1.0 - alpha;
    double xmin_pow = TMath::Power(eMin, exponent);
    double eCut_pow = TMath::Power(eCut, exponent);
    double xmax_pow = TMath::Power(eMax, exponent);
    double var = TMath::Power(rnd->Uniform() * (eCut_pow - xmin_pow ) + xmin_pow, 1.0 / exponent);
    h1->Fill(var);
    Double_t p = var;
    Double_t b = beta_vs_p_m(p,0.1057);
    Double_t n_w = gr_n_m_winter->Eval(2.0);
    Double_t n_s = gr_n_m_summer->Eval(2.0);
    Double_t t_w = theta_vs_n_beta(n_w,b) + rnd->Gaus(0.0,sigma_system);
    Double_t t_s = theta_vs_n_beta(n_s,b) + rnd->Gaus(0.0,sigma_system);
    if(t_w>0.8)
      h1_theta_w->Fill(t_w);
    if(t_s>0.8)
      h1_theta_s->Fill(t_s);
  }
  //
  //
  TH1D_norm( h1_theta_w, h1_theta_w->GetBinContent(h1_theta_w->GetMaximumBin())/(h1_ring_radius->GetBinContent(h1_ring_radius->GetMaximumBin())) );
  TH1D_norm( h1_theta_s, h1_theta_s->GetBinContent(h1_theta_s->GetMaximumBin())/(h1_ring_radius->GetBinContent(h1_ring_radius->GetMaximumBin())) );
  //
  //
  //
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,600,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //
  //h1->SetMinimum(0);
  //h1->Draw("errors");
  h1->Draw();
  //
  const Int_t npar = 2;
  Double_t inParameters[npar];
  inParameters[0] = 1.0e+10;
  inParameters[1] = 2.0;
  //
  TF1 *f_power_law = new TF1( "f_power_law", power_law, eMin, eMax, npar);
  f_power_law->SetParameters(inParameters);
  f_power_law->SetParName(0, "A");
  f_power_law->SetParName(1, "B");
  //f_power_law->FixParameter(0,inParameters[0]);
  //f_power_law->FixParameter(1,inParameters[1]);
  h1->Fit("f_power_law","","",eMin, eMax-1000);


  TCanvas *c2 = new TCanvas("c2","c2",10,10,600,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);

  h1_theta_w->SetLineWidth(3.0);
  h1_theta_s->SetLineWidth(3.0);
  h1_theta_w->SetLineColor(kBlack);
  h1_theta_s->SetLineColor(kRed+2);
  h1_ring_radius->SetLineColor(kBlue+2);
  h1_ring_radius->SetLineWidth(3.0);
  
  h1_theta_s->SetMaximum(700000);
  h1_theta_s->Draw();
  h1_theta_w->SetMaximum(700000);
  h1_theta_s->Draw();
  h1_ring_radius->Draw("sames");

  //h1_theta_s->Draw("sames");
  

  //
  return 0;
}


void read_atm(TString atmFileName, TGraph *gr_Alt_km, TGraph *gr_rho_g_cm3, TGraph *gr_thick_g_cm2, TGraph *gr_n_m){
  //
  ifstream fileIn(atmFileName.Data());
  cout<<"atm file : "<<atmFileName<<std::endl;
  //
  Double_t Alt_km, rho_g_cm3, thick_g_cm2, n_m;
  TString mot;
  Int_t counter = 0;
  //
  if (fileIn.is_open()){
    //
    while(fileIn>>mot)
      if(mot == "n-1")
	break;
    //
    while(fileIn>>Alt_km>>rho_g_cm3>>thick_g_cm2>>n_m){
      if(Alt_km<6.0){
      gr_Alt_km->SetPoint(counter,counter,Alt_km);
      gr_rho_g_cm3->SetPoint(counter,Alt_km,rho_g_cm3);
      gr_thick_g_cm2->SetPoint(counter,Alt_km,thick_g_cm2);
      gr_n_m->SetPoint(counter,Alt_km,1.0+n_m);
      counter++;
      }
    }
    fileIn.close();
    //
  }
  else {
    std::cout<<"Unable to open file"<<std::endl;
    assert(0);
  }
}

Double_t beta_vs_p_m( Double_t p_gev, Double_t m_gev){
  return TMath::Sqrt(1.0 - 1.0/(1.0 + p_gev*p_gev/m_gev/m_gev));
}

Double_t theta_vs_n_beta( Double_t n, Double_t beta){
  if(1.0/n/beta<=1.0)
    return TMath::ACos(1.0/n/beta)*180.0/TMath::Pi();
  else
    return 0;
}

void TH1D_norm( TH1D *h1, Double_t norm){
  Double_t val;
  Double_t val_norm;
  for(Int_t i = 1;i<=h1->GetNbinsX();i++){
    val = h1->GetBinContent(i);
    if(norm>0)
      val_norm = val/norm;
    else
      val_norm = 0.0;
    h1->SetBinContent(i,val_norm);
  }
}

void load_ring_radius_dist(TH1D *h1_ring_radius_all__1){
//========= Macro generated from object: h1_ring_radius_all/h1_ring_radius_all
//========= by ROOT version6.28/12
   

   h1_ring_radius_all__1->SetBinContent(401,112365);
   h1_ring_radius_all__1->SetBinContent(402,113192);
   h1_ring_radius_all__1->SetBinContent(403,113896);
   h1_ring_radius_all__1->SetBinContent(404,115141);
   h1_ring_radius_all__1->SetBinContent(405,116698);
   h1_ring_radius_all__1->SetBinContent(406,117887);
   h1_ring_radius_all__1->SetBinContent(407,119043);
   h1_ring_radius_all__1->SetBinContent(408,119641);
   h1_ring_radius_all__1->SetBinContent(409,121643);
   h1_ring_radius_all__1->SetBinContent(410,122038);
   h1_ring_radius_all__1->SetBinContent(411,123705);
   h1_ring_radius_all__1->SetBinContent(412,125771);
   h1_ring_radius_all__1->SetBinContent(413,126298);
   h1_ring_radius_all__1->SetBinContent(414,126823);
   h1_ring_radius_all__1->SetBinContent(415,129320);
   h1_ring_radius_all__1->SetBinContent(416,129660);
   h1_ring_radius_all__1->SetBinContent(417,131152);
   h1_ring_radius_all__1->SetBinContent(418,133238);
   h1_ring_radius_all__1->SetBinContent(419,133466);
   h1_ring_radius_all__1->SetBinContent(420,136545);
   h1_ring_radius_all__1->SetBinContent(421,138280);
   h1_ring_radius_all__1->SetBinContent(422,139403);
   h1_ring_radius_all__1->SetBinContent(423,140542);
   h1_ring_radius_all__1->SetBinContent(424,142688);
   h1_ring_radius_all__1->SetBinContent(425,143208);
   h1_ring_radius_all__1->SetBinContent(426,145521);
   h1_ring_radius_all__1->SetBinContent(427,146823);
   h1_ring_radius_all__1->SetBinContent(428,148328);
   h1_ring_radius_all__1->SetBinContent(429,149470);
   h1_ring_radius_all__1->SetBinContent(430,151082);
   h1_ring_radius_all__1->SetBinContent(431,152761);
   h1_ring_radius_all__1->SetBinContent(432,155548);
   h1_ring_radius_all__1->SetBinContent(433,156619);
   h1_ring_radius_all__1->SetBinContent(434,157342);
   h1_ring_radius_all__1->SetBinContent(435,160012);
   h1_ring_radius_all__1->SetBinContent(436,161276);
   h1_ring_radius_all__1->SetBinContent(437,164538);
   h1_ring_radius_all__1->SetBinContent(438,167807);
   h1_ring_radius_all__1->SetBinContent(439,168040);
   h1_ring_radius_all__1->SetBinContent(440,169627);
   h1_ring_radius_all__1->SetBinContent(441,171573);
   h1_ring_radius_all__1->SetBinContent(442,173713);
   h1_ring_radius_all__1->SetBinContent(443,175131);
   h1_ring_radius_all__1->SetBinContent(444,178283);
   h1_ring_radius_all__1->SetBinContent(445,178697);
   h1_ring_radius_all__1->SetBinContent(446,179284);
   h1_ring_radius_all__1->SetBinContent(447,181070);
   h1_ring_radius_all__1->SetBinContent(448,183681);
   h1_ring_radius_all__1->SetBinContent(449,185898);
   h1_ring_radius_all__1->SetBinContent(450,187337);
   h1_ring_radius_all__1->SetBinContent(451,188759);
   h1_ring_radius_all__1->SetBinContent(452,191049);
   h1_ring_radius_all__1->SetBinContent(453,192911);
   h1_ring_radius_all__1->SetBinContent(454,196156);
   h1_ring_radius_all__1->SetBinContent(455,199228);
   h1_ring_radius_all__1->SetBinContent(456,200854);
   h1_ring_radius_all__1->SetBinContent(457,202582);
   h1_ring_radius_all__1->SetBinContent(458,205720);
   h1_ring_radius_all__1->SetBinContent(459,207374);
   h1_ring_radius_all__1->SetBinContent(460,210136);
   h1_ring_radius_all__1->SetBinContent(461,212190);
   h1_ring_radius_all__1->SetBinContent(462,213725);
   h1_ring_radius_all__1->SetBinContent(463,213694);
   h1_ring_radius_all__1->SetBinContent(464,215220);
   h1_ring_radius_all__1->SetBinContent(465,218028);
   h1_ring_radius_all__1->SetBinContent(466,219605);
   h1_ring_radius_all__1->SetBinContent(467,222212);
   h1_ring_radius_all__1->SetBinContent(468,224602);
   h1_ring_radius_all__1->SetBinContent(469,227012);
   h1_ring_radius_all__1->SetBinContent(470,230497);
   h1_ring_radius_all__1->SetBinContent(471,233713);
   h1_ring_radius_all__1->SetBinContent(472,236417);
   h1_ring_radius_all__1->SetBinContent(473,239468);
   h1_ring_radius_all__1->SetBinContent(474,242155);
   h1_ring_radius_all__1->SetBinContent(475,244455);
   h1_ring_radius_all__1->SetBinContent(476,246401);
   h1_ring_radius_all__1->SetBinContent(477,249082);
   h1_ring_radius_all__1->SetBinContent(478,252353);
   h1_ring_radius_all__1->SetBinContent(479,252805);
   h1_ring_radius_all__1->SetBinContent(480,249725);
   h1_ring_radius_all__1->SetBinContent(481,251694);
   h1_ring_radius_all__1->SetBinContent(482,254269);
   h1_ring_radius_all__1->SetBinContent(483,257121);
   h1_ring_radius_all__1->SetBinContent(484,260051);
   h1_ring_radius_all__1->SetBinContent(485,262334);
   h1_ring_radius_all__1->SetBinContent(486,264280);
   h1_ring_radius_all__1->SetBinContent(487,267219);
   h1_ring_radius_all__1->SetBinContent(488,280166);
   h1_ring_radius_all__1->SetBinContent(489,286930);
   h1_ring_radius_all__1->SetBinContent(490,289820);
   h1_ring_radius_all__1->SetBinContent(491,293782);
   h1_ring_radius_all__1->SetBinContent(492,295979);
   h1_ring_radius_all__1->SetBinContent(493,298284);
   h1_ring_radius_all__1->SetBinContent(494,301169);
   h1_ring_radius_all__1->SetBinContent(495,304539);
   h1_ring_radius_all__1->SetBinContent(496,303835);
   h1_ring_radius_all__1->SetBinContent(497,278620);
   h1_ring_radius_all__1->SetBinContent(498,281367);
   h1_ring_radius_all__1->SetBinContent(499,283840);
   h1_ring_radius_all__1->SetBinContent(500,286319);
   h1_ring_radius_all__1->SetBinContent(501,288904);
   h1_ring_radius_all__1->SetBinContent(502,292567);
   h1_ring_radius_all__1->SetBinContent(503,296456);
   h1_ring_radius_all__1->SetBinContent(504,298231);
   h1_ring_radius_all__1->SetBinContent(505,320302);
   h1_ring_radius_all__1->SetBinContent(506,335898);
   h1_ring_radius_all__1->SetBinContent(507,340523);
   h1_ring_radius_all__1->SetBinContent(508,343049);
   h1_ring_radius_all__1->SetBinContent(509,345940);
   h1_ring_radius_all__1->SetBinContent(510,349508);
   h1_ring_radius_all__1->SetBinContent(511,351223);
   h1_ring_radius_all__1->SetBinContent(512,356282);
   h1_ring_radius_all__1->SetBinContent(513,360798);
   h1_ring_radius_all__1->SetBinContent(514,354810);
   h1_ring_radius_all__1->SetBinContent(515,359652);
   h1_ring_radius_all__1->SetBinContent(516,362904);
   h1_ring_radius_all__1->SetBinContent(517,366136);
   h1_ring_radius_all__1->SetBinContent(518,368062);
   h1_ring_radius_all__1->SetBinContent(519,372334);
   h1_ring_radius_all__1->SetBinContent(520,376358);
   h1_ring_radius_all__1->SetBinContent(521,377572);
   h1_ring_radius_all__1->SetBinContent(522,384510);
   h1_ring_radius_all__1->SetBinContent(523,390723);
   h1_ring_radius_all__1->SetBinContent(524,393471);
   h1_ring_radius_all__1->SetBinContent(525,397714);
   h1_ring_radius_all__1->SetBinContent(526,401239);
   h1_ring_radius_all__1->SetBinContent(527,404469);
   h1_ring_radius_all__1->SetBinContent(528,408554);
   h1_ring_radius_all__1->SetBinContent(529,411935);
   h1_ring_radius_all__1->SetBinContent(530,415636);
   h1_ring_radius_all__1->SetBinContent(531,413138);
   h1_ring_radius_all__1->SetBinContent(532,415985);
   h1_ring_radius_all__1->SetBinContent(533,421561);
   h1_ring_radius_all__1->SetBinContent(534,423404);
   h1_ring_radius_all__1->SetBinContent(535,425663);
   h1_ring_radius_all__1->SetBinContent(536,431377);
   h1_ring_radius_all__1->SetBinContent(537,434890);
   h1_ring_radius_all__1->SetBinContent(538,435750);
   h1_ring_radius_all__1->SetBinContent(539,442050);
   h1_ring_radius_all__1->SetBinContent(540,446964);
   h1_ring_radius_all__1->SetBinContent(541,450652);
   h1_ring_radius_all__1->SetBinContent(542,454555);
   h1_ring_radius_all__1->SetBinContent(543,457999);
   h1_ring_radius_all__1->SetBinContent(544,462175);
   h1_ring_radius_all__1->SetBinContent(545,467237);
   h1_ring_radius_all__1->SetBinContent(546,471189);
   h1_ring_radius_all__1->SetBinContent(547,474101);
   h1_ring_radius_all__1->SetBinContent(548,472393);
   h1_ring_radius_all__1->SetBinContent(549,476246);
   h1_ring_radius_all__1->SetBinContent(550,479187);
   h1_ring_radius_all__1->SetBinContent(551,483816);
   h1_ring_radius_all__1->SetBinContent(552,485030);
   h1_ring_radius_all__1->SetBinContent(553,489304);
   h1_ring_radius_all__1->SetBinContent(554,493980);
   h1_ring_radius_all__1->SetBinContent(555,496548);
   h1_ring_radius_all__1->SetBinContent(556,500774);
   h1_ring_radius_all__1->SetBinContent(557,506553);
   h1_ring_radius_all__1->SetBinContent(558,510803);
   h1_ring_radius_all__1->SetBinContent(559,512804);
   h1_ring_radius_all__1->SetBinContent(560,515074);
   h1_ring_radius_all__1->SetBinContent(561,520176);
   h1_ring_radius_all__1->SetBinContent(562,524140);
   h1_ring_radius_all__1->SetBinContent(563,527547);
   h1_ring_radius_all__1->SetBinContent(564,529321);
   h1_ring_radius_all__1->SetBinContent(565,530063);
   h1_ring_radius_all__1->SetBinContent(566,534310);
   h1_ring_radius_all__1->SetBinContent(567,536264);
   h1_ring_radius_all__1->SetBinContent(568,540893);
   h1_ring_radius_all__1->SetBinContent(569,544222);
   h1_ring_radius_all__1->SetBinContent(570,549853);
   h1_ring_radius_all__1->SetBinContent(571,552488);
   h1_ring_radius_all__1->SetBinContent(572,555482);
   h1_ring_radius_all__1->SetBinContent(573,558263);
   h1_ring_radius_all__1->SetBinContent(574,556109);
   h1_ring_radius_all__1->SetBinContent(575,561056);
   h1_ring_radius_all__1->SetBinContent(576,563701);
   h1_ring_radius_all__1->SetBinContent(577,566367);
   h1_ring_radius_all__1->SetBinContent(578,569829);
   h1_ring_radius_all__1->SetBinContent(579,571970);
   h1_ring_radius_all__1->SetBinContent(580,576280);
   h1_ring_radius_all__1->SetBinContent(581,578112);
   h1_ring_radius_all__1->SetBinContent(582,573783);
   h1_ring_radius_all__1->SetBinContent(583,572729);
   h1_ring_radius_all__1->SetBinContent(584,576248);
   h1_ring_radius_all__1->SetBinContent(585,580351);
   h1_ring_radius_all__1->SetBinContent(586,584962);
   h1_ring_radius_all__1->SetBinContent(587,587479);
   h1_ring_radius_all__1->SetBinContent(588,592264);
   h1_ring_radius_all__1->SetBinContent(589,594170);
   h1_ring_radius_all__1->SetBinContent(590,595163);
   h1_ring_radius_all__1->SetBinContent(591,592128);
   h1_ring_radius_all__1->SetBinContent(592,594476);
   h1_ring_radius_all__1->SetBinContent(593,594942);
   h1_ring_radius_all__1->SetBinContent(594,593176);
   h1_ring_radius_all__1->SetBinContent(595,594157);
   h1_ring_radius_all__1->SetBinContent(596,591467);
   h1_ring_radius_all__1->SetBinContent(597,588103);
   h1_ring_radius_all__1->SetBinContent(598,584571);
   h1_ring_radius_all__1->SetBinContent(599,578618);
   h1_ring_radius_all__1->SetBinContent(600,567989);
   h1_ring_radius_all__1->SetBinContent(601,563038);
   h1_ring_radius_all__1->SetBinContent(602,549797);
   h1_ring_radius_all__1->SetBinContent(603,539213);
   h1_ring_radius_all__1->SetBinContent(604,523441);
   h1_ring_radius_all__1->SetBinContent(605,507641);
   h1_ring_radius_all__1->SetBinContent(606,490315);
   h1_ring_radius_all__1->SetBinContent(607,469126);
   h1_ring_radius_all__1->SetBinContent(608,448914);
   h1_ring_radius_all__1->SetBinContent(609,424085);
   h1_ring_radius_all__1->SetBinContent(610,398027);
   h1_ring_radius_all__1->SetBinContent(611,371270);
   h1_ring_radius_all__1->SetBinContent(612,344403);
   h1_ring_radius_all__1->SetBinContent(613,317147);
   h1_ring_radius_all__1->SetBinContent(614,289058);
   h1_ring_radius_all__1->SetBinContent(615,260791);
   h1_ring_radius_all__1->SetBinContent(616,232872);
   h1_ring_radius_all__1->SetBinContent(617,204536);
   h1_ring_radius_all__1->SetBinContent(618,179658);
   h1_ring_radius_all__1->SetBinContent(619,155884);
   h1_ring_radius_all__1->SetBinContent(620,133495);
   h1_ring_radius_all__1->SetBinContent(621,112644);
   h1_ring_radius_all__1->SetBinContent(622,94307);
   h1_ring_radius_all__1->SetBinContent(623,77399);
   h1_ring_radius_all__1->SetBinContent(624,62915);
   h1_ring_radius_all__1->SetBinContent(625,49157);
   h1_ring_radius_all__1->SetBinContent(626,38825);
   h1_ring_radius_all__1->SetBinContent(627,30783);
   h1_ring_radius_all__1->SetBinContent(628,24288);
   h1_ring_radius_all__1->SetBinContent(629,18698);
   h1_ring_radius_all__1->SetBinContent(630,14689);
   h1_ring_radius_all__1->SetBinContent(631,11580);
   h1_ring_radius_all__1->SetBinContent(632,9250);
   h1_ring_radius_all__1->SetBinContent(633,7379);
   h1_ring_radius_all__1->SetBinContent(634,6002);
   h1_ring_radius_all__1->SetBinContent(635,5074);
   h1_ring_radius_all__1->SetBinContent(636,4396);
   h1_ring_radius_all__1->SetBinContent(637,3743);
   h1_ring_radius_all__1->SetBinContent(638,3392);
   h1_ring_radius_all__1->SetBinContent(639,2889);
   h1_ring_radius_all__1->SetBinContent(640,2603);
   h1_ring_radius_all__1->SetBinContent(641,2433);
   h1_ring_radius_all__1->SetBinContent(642,2163);
   h1_ring_radius_all__1->SetBinContent(643,1890);
   h1_ring_radius_all__1->SetBinContent(644,1701);
   h1_ring_radius_all__1->SetBinContent(645,1650);
   h1_ring_radius_all__1->SetBinContent(646,1646);
   h1_ring_radius_all__1->SetBinContent(647,1534);
   h1_ring_radius_all__1->SetBinContent(648,1502);
   h1_ring_radius_all__1->SetBinContent(649,1372);
   h1_ring_radius_all__1->SetBinContent(650,1352);
   h1_ring_radius_all__1->SetBinContent(651,1240);
   h1_ring_radius_all__1->SetBinContent(652,1148);
   h1_ring_radius_all__1->SetBinContent(653,1105);
   h1_ring_radius_all__1->SetBinContent(654,1117);
   h1_ring_radius_all__1->SetBinContent(655,1059);
   h1_ring_radius_all__1->SetBinContent(656,1036);
   h1_ring_radius_all__1->SetBinContent(657,1055);
   h1_ring_radius_all__1->SetBinContent(658,977);
   h1_ring_radius_all__1->SetBinContent(659,1003);
   h1_ring_radius_all__1->SetBinContent(660,943);
   h1_ring_radius_all__1->SetBinContent(661,960);
   h1_ring_radius_all__1->SetBinContent(662,947);
   h1_ring_radius_all__1->SetBinContent(663,876);
   h1_ring_radius_all__1->SetBinContent(664,890);
   h1_ring_radius_all__1->SetBinContent(665,894);
   h1_ring_radius_all__1->SetBinContent(666,845);
   h1_ring_radius_all__1->SetBinContent(667,812);
   h1_ring_radius_all__1->SetBinContent(668,840);
   h1_ring_radius_all__1->SetBinContent(669,896);
   h1_ring_radius_all__1->SetBinContent(670,823);
   h1_ring_radius_all__1->SetBinContent(671,769);
   h1_ring_radius_all__1->SetBinContent(672,763);
   h1_ring_radius_all__1->SetBinContent(673,757);
   h1_ring_radius_all__1->SetBinContent(674,763);
   h1_ring_radius_all__1->SetBinContent(675,760);
   h1_ring_radius_all__1->SetBinContent(676,714);
   h1_ring_radius_all__1->SetBinContent(677,760);
   h1_ring_radius_all__1->SetBinContent(678,807);
   h1_ring_radius_all__1->SetBinContent(679,732);
   h1_ring_radius_all__1->SetBinContent(680,688);
   h1_ring_radius_all__1->SetBinContent(681,682);
   h1_ring_radius_all__1->SetBinContent(682,712);
   h1_ring_radius_all__1->SetBinContent(683,650);
   h1_ring_radius_all__1->SetBinContent(684,610);
   h1_ring_radius_all__1->SetBinContent(685,688);
   h1_ring_radius_all__1->SetBinContent(686,632);
   h1_ring_radius_all__1->SetBinContent(687,674);
   h1_ring_radius_all__1->SetBinContent(688,590);
   h1_ring_radius_all__1->SetBinContent(689,593);
   h1_ring_radius_all__1->SetBinContent(690,606);
   h1_ring_radius_all__1->SetBinContent(691,551);
   h1_ring_radius_all__1->SetBinContent(692,620);
   h1_ring_radius_all__1->SetBinContent(693,592);
   h1_ring_radius_all__1->SetBinContent(694,617);
   h1_ring_radius_all__1->SetBinContent(695,613);
   h1_ring_radius_all__1->SetBinContent(696,567);
   h1_ring_radius_all__1->SetBinContent(697,560);
   h1_ring_radius_all__1->SetBinContent(698,567);
   h1_ring_radius_all__1->SetBinContent(699,543);
   h1_ring_radius_all__1->SetBinContent(700,548);
   h1_ring_radius_all__1->SetBinContent(701,581);
   h1_ring_radius_all__1->SetBinContent(702,543);
   h1_ring_radius_all__1->SetBinContent(703,552);
   h1_ring_radius_all__1->SetBinContent(704,541);
   h1_ring_radius_all__1->SetBinContent(705,509);
   h1_ring_radius_all__1->SetBinContent(706,534);
   h1_ring_radius_all__1->SetBinContent(707,511);
   h1_ring_radius_all__1->SetBinContent(708,490);
   h1_ring_radius_all__1->SetBinContent(709,503);
   h1_ring_radius_all__1->SetBinContent(710,504);
   h1_ring_radius_all__1->SetBinContent(711,475);
   h1_ring_radius_all__1->SetBinContent(712,495);
   h1_ring_radius_all__1->SetBinContent(713,489);
   h1_ring_radius_all__1->SetBinContent(714,494);
   h1_ring_radius_all__1->SetBinContent(715,479);
   h1_ring_radius_all__1->SetBinContent(716,462);
   h1_ring_radius_all__1->SetBinContent(717,460);
   h1_ring_radius_all__1->SetBinContent(718,417);
   h1_ring_radius_all__1->SetBinContent(719,434);
   h1_ring_radius_all__1->SetBinContent(720,452);
   h1_ring_radius_all__1->SetBinContent(721,438);
   h1_ring_radius_all__1->SetBinContent(722,403);
   h1_ring_radius_all__1->SetBinContent(723,437);
   h1_ring_radius_all__1->SetBinContent(724,448);
   h1_ring_radius_all__1->SetBinContent(725,422);
   h1_ring_radius_all__1->SetBinContent(726,421);
   h1_ring_radius_all__1->SetBinContent(727,410);
   h1_ring_radius_all__1->SetBinContent(728,434);
   h1_ring_radius_all__1->SetBinContent(729,436);
   h1_ring_radius_all__1->SetBinContent(730,423);
   h1_ring_radius_all__1->SetBinContent(731,420);
   h1_ring_radius_all__1->SetBinContent(732,375);
   h1_ring_radius_all__1->SetBinContent(733,427);
   h1_ring_radius_all__1->SetBinContent(734,393);
   h1_ring_radius_all__1->SetBinContent(735,406);
   h1_ring_radius_all__1->SetBinContent(736,380);
   h1_ring_radius_all__1->SetBinContent(737,391);
   h1_ring_radius_all__1->SetBinContent(738,399);
   h1_ring_radius_all__1->SetBinContent(739,382);
   h1_ring_radius_all__1->SetBinContent(740,370);
   h1_ring_radius_all__1->SetBinContent(741,350);
   h1_ring_radius_all__1->SetBinContent(742,322);
   h1_ring_radius_all__1->SetBinContent(743,396);
   h1_ring_radius_all__1->SetBinContent(744,374);
   h1_ring_radius_all__1->SetBinContent(745,338);
   h1_ring_radius_all__1->SetBinContent(746,373);
   h1_ring_radius_all__1->SetBinContent(747,345);
   h1_ring_radius_all__1->SetBinContent(748,358);
   h1_ring_radius_all__1->SetBinContent(749,320);
   h1_ring_radius_all__1->SetBinContent(750,338);
   h1_ring_radius_all__1->SetEntries(7.50818e+07);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h1_ring_radius_all__1->SetLineColor(ci);
   h1_ring_radius_all__1->GetXaxis()->SetLabelFont(42);
   h1_ring_radius_all__1->GetXaxis()->SetTitleOffset(1);
   h1_ring_radius_all__1->GetXaxis()->SetTitleFont(42);
   h1_ring_radius_all__1->GetYaxis()->SetLabelFont(42);
   h1_ring_radius_all__1->GetYaxis()->SetTitleFont(42);
   h1_ring_radius_all__1->GetZaxis()->SetLabelFont(42);
   h1_ring_radius_all__1->GetZaxis()->SetTitleOffset(1);
   h1_ring_radius_all__1->GetZaxis()->SetTitleFont(42);
   //h1_ring_radius_all__1->Draw("");
}

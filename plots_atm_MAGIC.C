//
//atmprof8.dat
//# Atmospheric Model  8 (MAGIC winter)            
//#Col. #1          #2           #3            #4 
//# Alt [km]    rho [g/cm^3] thick [g/cm^2]    n-1
//    0.000     0.12167E-02  0.10526E+04  0.28047E-03
//    1.000     0.10996E-02  0.93687E+03  0.25348E-03
//    2.000     0.99545E-03  0.83221E+03  0.22947E-03
//    3.000     0.90172E-03  0.73744E+03  0.20786E-03
//
//atmprof7.dat
//# Atmospheric Model  7 (MAGIC summer)            
//#Col. #1          #2           #3            #4 
//# Alt [km]    rho [g/cm^3] thick [g/cm^2]    n-1
//    0.000     0.11982E-02  0.10475E+04  0.27622E-03
//    1.000     0.10843E-02  0.93351E+03  0.24996E-03
//    2.000     0.98142E-03  0.83032E+03  0.22624E-03
//    3.000     0.88812E-03  0.73692E+03  0.20473E-03
//

//
void read_atm(TString atmFileName, TGraph *gr_Alt_km, TGraph *gr_rho_g_cm3, TGraph *gr_thick_g_cm2, TGraph *gr_n_m);  
Double_t beta_vs_p_m( Double_t p_gev, Double_t m_gev);
Double_t theta_vs_n_beta( Double_t n, Double_t beta);
//

//
//
Int_t plots_atm_MAGIC(){
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
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);
  //
  TCanvas *c1 = new TCanvas("c1","gr_Alt_km",10,10,600,600);  
  gr_Alt_km_winter->SetLineColor(kBlack);
  gr_Alt_km_winter->SetLineWidth(3.0);
  gr_Alt_km_winter->SetMarkerColor(kBlack);
  gr_Alt_km_winter->SetMarkerStyle(20);
  //gr_Alt_km_winter->Draw("APL");
  //
  gr_Alt_km_summer->SetLineColor(kRed+2);
  gr_Alt_km_summer->SetLineWidth(3.0);
  gr_Alt_km_summer->SetMarkerColor(kRed+2);
  gr_Alt_km_summer->SetMarkerStyle(20);
  //gr_Alt_km_summer->Draw("APL");
  ////////
  TMultiGraph *mg01 = new TMultiGraph();
  mg01->Add(gr_Alt_km_winter);
  mg01->Add(gr_Alt_km_summer);
  mg01->Draw("APL");
  //mg01->GetXaxis()->SetRangeUser(400,1500);
  //mg01->SetMinimum(0.0);
  //mg01->SetMaximum(4.0);
  //mg01->SetMaximum(6.0);
  //mg01->SetMaximum(5.0);
  //
  //mg01->GetXaxis()->SetTitle("time, ns");
  //mg01->GetYaxis()->SetTitle("Amplitude, a.u.");
  ////////
  TCanvas *c2 = new TCanvas("c2","gr_rho_g_cm3",10,10,600,600);
  gr_rho_g_cm3_winter->SetLineColor(kBlack);
  gr_rho_g_cm3_winter->SetLineWidth(3.0);
  gr_rho_g_cm3_winter->SetMarkerColor(kBlack);
  gr_rho_g_cm3_winter->SetMarkerStyle(20);
  //gr_rho_g_cm3_winter->Draw("APL");
  //
  gr_rho_g_cm3_summer->SetLineColor(kRed+2);
  gr_rho_g_cm3_summer->SetLineWidth(3.0);
  gr_rho_g_cm3_summer->SetMarkerColor(kRed+2);
  gr_rho_g_cm3_summer->SetMarkerStyle(20);  
  //
  TMultiGraph *mg02 = new TMultiGraph();
  mg02->Add(gr_rho_g_cm3_winter);
  mg02->Add(gr_rho_g_cm3_summer);
  mg02->Draw("APL");
  //
  TCanvas *c3 = new TCanvas("c3","gr_thick_g_cm2",10,10,600,600);
  gr_thick_g_cm2_winter->SetLineColor(kBlack);
  gr_thick_g_cm2_winter->SetLineWidth(3.0);
  gr_thick_g_cm2_winter->SetMarkerColor(kBlack);
  gr_thick_g_cm2_winter->SetMarkerStyle(20);
  //gr_thick_g_cm2_winter->Draw("APL");
  //
  gr_thick_g_cm2_summer->SetLineColor(kRed+2);
  gr_thick_g_cm2_summer->SetLineWidth(3.0);
  gr_thick_g_cm2_summer->SetMarkerColor(kRed+2);
  gr_thick_g_cm2_summer->SetMarkerStyle(20);  
  //
  TMultiGraph *mg03 = new TMultiGraph();
  mg03->Add(gr_thick_g_cm2_winter);
  mg03->Add(gr_thick_g_cm2_summer);
  mg03->Draw("APL");
  //
  TCanvas *c4 = new TCanvas("c4","gr_n_m",10,10,1700,500);
  c4->Divide(4,1);
  c4->cd(1);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  //
  gr_n_m_winter->SetLineColor(kBlack);
  gr_n_m_winter->SetLineWidth(3.0);
  gr_n_m_winter->SetMarkerColor(kBlack);
  gr_n_m_winter->SetMarkerStyle(20);
  //gr_n_m_winter->Draw("APL");
  //
  gr_n_m_summer->SetLineColor(kRed+2);
  gr_n_m_summer->SetLineWidth(3.0);
  gr_n_m_summer->SetMarkerColor(kRed+2);
  gr_n_m_summer->SetMarkerStyle(20);  
  //
  TMultiGraph *mg04 = new TMultiGraph();
  mg04->Add(gr_n_m_winter);
  mg04->Add(gr_n_m_summer);
  mg04->Draw("APL");
  mg04->GetXaxis()->SetTitle("Altitude, km");
  mg04->GetYaxis()->SetTitle("Air refractive index");
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr_n_m_winter, "Winter", "apl");
  leg->AddEntry(gr_n_m_summer, "Summer", "apl");  
  leg->Draw();    
  //
  c4->cd(2); 
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  TGraph *gr_d = new TGraph();
  gr_d->SetNameTitle("gr_d","gr_d");
  //
  Double_t dtch = (TMath::ACos(1.0/1.0/gr_n_m_winter->Eval(0.0)) -
		   TMath::ACos(1.0/1.0/gr_n_m_summer->Eval(0.0)))*180.0/TMath::Pi();
  gr_d->SetPoint(0, 0.0, dtch);
  //
  dtch = (TMath::ACos(1.0/1.0/gr_n_m_winter->Eval(1.0)) -
	  TMath::ACos(1.0/1.0/gr_n_m_summer->Eval(1.0)))*180.0/TMath::Pi();
  gr_d->SetPoint(1, 1.0, dtch);
  //
  dtch = (TMath::ACos(1.0/1.0/gr_n_m_winter->Eval(2.0)) -
	  TMath::ACos(1.0/1.0/gr_n_m_summer->Eval(2.0)))*180.0/TMath::Pi();
  gr_d->SetPoint(2, 2.0, dtch);
  //
  dtch = (TMath::ACos(1.0/1.0/gr_n_m_winter->Eval(3.0)) -
	  TMath::ACos(1.0/1.0/gr_n_m_summer->Eval(3.0)))*180.0/TMath::Pi();
  gr_d->SetPoint(3, 3.0, dtch);
  //
  dtch = (TMath::ACos(1.0/1.0/gr_n_m_winter->Eval(4.0)) -
	  TMath::ACos(1.0/1.0/gr_n_m_summer->Eval(4.0)))*180.0/TMath::Pi();
  gr_d->SetPoint(4, 4.0, dtch);
  //
  dtch = (TMath::ACos(1.0/1.0/gr_n_m_winter->Eval(5.0)) -
	  TMath::ACos(1.0/1.0/gr_n_m_summer->Eval(5.0)))*180.0/TMath::Pi();
  gr_d->SetPoint(5, 5.0, dtch);
  gr_d->SetLineColor(kBlack);
  gr_d->SetLineWidth(3.0);
  gr_d->SetMarkerColor(kBlack);
  gr_d->SetMarkerStyle(1);
  gr_d->GetXaxis()->SetTitle("Altitude, km");
  gr_d->GetYaxis()->SetTitle("#Delta Cherenkov angle, deg.");

  //
  //
  gr_d->GetXaxis()->SetRangeUser(-1.5, 5.5);
  gr_d->SetTitle("");
  gr_d->SetMinimum(0.0);
  gr_d->SetMaximum(0.012);
  gr_d->Draw("APL");
  //
  TGraph *gr_theta_vs_p_mu_winter = new TGraph();
  TGraph *gr_theta_vs_p_mu_summer = new TGraph();
  TGraph *gr_theta_vs_p_mu_winter_cut = new TGraph();
  TGraph *gr_theta_vs_p_mu_summer_cut = new TGraph();
  for(Int_t i = 0;i<1000;i++){
    Double_t p = 8.0 + (50 - 8.0)/(1000-1)*i;
    Double_t b = beta_vs_p_m(p,0.1057);
    Double_t n_w = gr_n_m_winter->Eval(2.0);
    Double_t n_s = gr_n_m_summer->Eval(2.0);
    Double_t t_w = theta_vs_n_beta(n_w,b);
    Double_t t_s = theta_vs_n_beta(n_s,b);    
    gr_theta_vs_p_mu_winter->SetPoint(i,p,t_w);
    gr_theta_vs_p_mu_summer->SetPoint(i,p,t_s);
  }
  for(Int_t i = 0;i<1000;i++){
    Double_t p = 4.0 + (10 - 4.0)/(1000-1)*i;
    Double_t b = beta_vs_p_m(p,0.1057);
    Double_t n_w = gr_n_m_winter->Eval(2.0);
    Double_t n_s = gr_n_m_summer->Eval(2.0);
    Double_t t_w = theta_vs_n_beta(n_w,b);
    Double_t t_s = theta_vs_n_beta(n_s,b);    
    gr_theta_vs_p_mu_winter_cut->SetPoint(i,p,t_w);
    gr_theta_vs_p_mu_summer_cut->SetPoint(i,p,t_s);
  }
  c4->cd(3);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  //
  gr_theta_vs_p_mu_winter->SetLineColor(kBlack);
  gr_theta_vs_p_mu_winter->SetLineWidth(3.0);
  gr_theta_vs_p_mu_winter->SetMarkerColor(kBlack);
  gr_theta_vs_p_mu_winter->SetMarkerStyle(1);
  //
  gr_theta_vs_p_mu_summer->SetLineColor(kRed+2);
  gr_theta_vs_p_mu_summer->SetLineWidth(3.0);
  gr_theta_vs_p_mu_summer->SetMarkerColor(kRed+2);
  gr_theta_vs_p_mu_summer->SetMarkerStyle(1);  
  //
  TMultiGraph *mg0ws = new TMultiGraph();
  mg0ws->Add(gr_theta_vs_p_mu_winter);
  mg0ws->Add(gr_theta_vs_p_mu_summer);
  mg0ws->Draw("APL");
  mg0ws->GetXaxis()->SetTitle("Muon momentum, GeV/c");
  mg0ws->GetYaxis()->SetTitle("Cherenkov angle, deg.");
  TLegend *leg001 = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg001->AddEntry(gr_theta_vs_p_mu_winter, "Winter", "apl");
  leg001->AddEntry(gr_theta_vs_p_mu_summer, "Summer", "apl");  
  leg001->Draw();    
  //
  //
  c4->cd(4);
  //
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  //
  gr_theta_vs_p_mu_winter_cut->SetLineColor(kBlack);
  gr_theta_vs_p_mu_winter_cut->SetLineWidth(3.0);
  gr_theta_vs_p_mu_winter_cut->SetMarkerColor(kBlack);
  gr_theta_vs_p_mu_winter_cut->SetMarkerStyle(1);
  //
  gr_theta_vs_p_mu_summer_cut->SetLineColor(kRed+2);
  gr_theta_vs_p_mu_summer_cut->SetLineWidth(3.0);
  gr_theta_vs_p_mu_summer_cut->SetMarkerColor(kRed+2);
  gr_theta_vs_p_mu_summer_cut->SetMarkerStyle(1);  

  TMultiGraph *mg1ws = new TMultiGraph();
  mg1ws->Add(gr_theta_vs_p_mu_winter_cut);
  mg1ws->Add(gr_theta_vs_p_mu_summer_cut);
  mg1ws->Draw("APL");
  mg1ws->GetXaxis()->SetTitle("Muon momentum, GeV/c");
  mg1ws->GetYaxis()->SetTitle("Cherenkov angle, deg.");
  TLegend *leg002 = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg002->AddEntry(gr_theta_vs_p_mu_winter_cut, "Winter", "apl");
  leg002->AddEntry(gr_theta_vs_p_mu_summer_cut, "Summer", "apl");  
  leg002->Draw();    
  
  //TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  //leg->AddEntry(gr_n_m_winter, "Winter", "apl");
  //leg->AddEntry(gr_n_m_summer, "Summer", "apl");  
  //leg->Draw("APL");    



  //
  return 0;
}

///////////////////////////////////////////////////////
//atmprof8.dat
//# Atmospheric Model  8 (MAGIC winter)            
//#Col. #1          #2           #3            #4 
//# Alt [km]    rho [g/cm^3] thick [g/cm^2]    n-1
//    0.000     0.12167E-02  0.10526E+04  0.28047E-03
//    1.000     0.10996E-02  0.93687E+03  0.25348E-03
//    2.000     0.99545E-03  0.83221E+03  0.22947E-03
//    3.000     0.90172E-03  0.73744E+03  0.20786E-03
//
//atmprof7.dat
//# Atmospheric Model  7 (MAGIC summer)            
//#Col. #1          #2           #3            #4 
//# Alt [km]    rho [g/cm^3] thick [g/cm^2]    n-1
//    0.000     0.11982E-02  0.10475E+04  0.27622E-03
//    1.000     0.10843E-02  0.93351E+03  0.24996E-03
//    2.000     0.98142E-03  0.83032E+03  0.22624E-03
//    3.000     0.88812E-03  0.73692E+03  0.20473E-03
///////////////////////////////////////////////////////

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

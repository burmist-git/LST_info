void read_mirror_reflectivity_LST(TString atmFileName, TGraph *gr_wl, TGraph *gr_reflectivity, TGraphErrors *gr_err_reflectivity, TGraph *gr_1sigma);
void read_qe_LST(TString fileName, TGraph *gr_qe);
void read_window_transmission_LST(TString fileName, TGraph *gr);
void read_atm_tr(TString fileName, TGraph *gr);
Bool_t if_ok(Double_t var, TRandom3 *rnd, TGraph *gr);
Bool_t if_ok(Double_t var, TRandom3 *rnd, Double_t constdegrad);

Int_t plots_mirror_window_qe_cher_conv_LST(){
  //
  //TString fileName = ;
  //
  TGraph *gr_wl = new TGraph();
  TGraph *gr_reflectivity = new TGraph();
  TGraphErrors *gr_err_reflectivity = new TGraphErrors();
  TGraph *gr_1sigma = new TGraph();
  TGraph *gr_qe = new TGraph();
  TGraph *gr_tr = new TGraph();
  TGraph *gr_atm_tr = new TGraph();
  //
  read_mirror_reflectivity_LST("./lst-sim-config/mirror_reflectivity_LST.dat", gr_wl, gr_reflectivity, gr_err_reflectivity, gr_1sigma);
  read_qe_LST("lst-sim-config/qe_lst1_20200318_highandlow.dat", gr_qe);
  read_window_transmission_LST("lst-sim-config/window_transmission_LST.dat", gr_tr);
  //read_atm_tr("./atm_trans_at_1km_above_LST.dat", gr_atm_tr);
  //read_atm_tr("./atm_trans_at_0.3km_above_LST.dat", gr_atm_tr);
  //read_atm_tr("./atm_trans_at_0.5km_above_LST.dat", gr_atm_tr);
  read_atm_tr("./atm_trans_at_0.7km_above_LST.dat", gr_atm_tr);
  //
  //
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  //
  //TCanvas *c1 = new TCanvas("c1","gr_wl",10,10,600,600);
  //gr_wl->SetLineColor(kBlack);
  //gr_wl->SetLineWidth(3.0);
  //gr_wl->SetMarkerColor(kBlack);
  //gr_wl->SetMarkerStyle(20);
  //gr_wl->Draw("APL");
  //
  TCanvas *c1 = new TCanvas("c1","gr_reflectivity",10,10,600,600);
  gr_reflectivity->SetLineColor(kBlack);
  gr_reflectivity->SetLineWidth(3.0);
  gr_reflectivity->SetMarkerColor(kBlack);
  gr_reflectivity->SetMarkerStyle(20);
  gr_reflectivity->Draw("APL");
  //
  //TCanvas *c3 = new TCanvas("c3","gr_err_reflectivity",10,10,600,600);
  //gr_err_reflectivity->SetLineColor(kBlack);
  //gr_err_reflectivity->SetLineWidth(3.0);
  //gr_err_reflectivity->SetMarkerColor(kBlack);
  //gr_err_reflectivity->SetMarkerStyle(20);
  //gr_err_reflectivity->Draw("APL");
  //
  //TCanvas *c4 = new TCanvas("c4","gr_1sigma",10,10,600,600);
  //gr_1sigma->SetLineColor(kBlack);
  //gr_1sigma->SetLineWidth(3.0);
  //gr_1sigma->SetMarkerColor(kBlack);
  //gr_1sigma->SetMarkerStyle(20);
  //gr_1sigma->Draw("APL");
  //
  TCanvas *c2 = new TCanvas("c2","gr_qe",10,10,600,600);
  gr_qe->SetLineColor(kBlack);
  gr_qe->SetLineWidth(3.0);
  gr_qe->SetMarkerColor(kBlack);
  gr_qe->SetMarkerStyle(20);
  gr_qe->Draw("APL");
  //
  TCanvas *c3 = new TCanvas("c3","gr_qe",10,10,600,600);
  gr_tr->SetLineColor(kBlack);
  gr_tr->SetLineWidth(3.0);
  gr_tr->SetMarkerColor(kBlack);
  gr_tr->SetMarkerStyle(20);
  gr_tr->Draw("APL");
  //
  TCanvas *c5 = new TCanvas("c5","gr_atm_tr",10,10,600,600);
  gr_atm_tr->SetLineColor(kBlack);
  gr_atm_tr->SetLineWidth(3.0);
  gr_atm_tr->SetMarkerColor(kBlack);
  gr_atm_tr->SetMarkerStyle(20);
  gr_atm_tr->Draw("APL");
  //
  //
  //
  //
  Double_t lam_Min = 300.0;
  Double_t lam_Max = 600.0;
  TH1D *h1 = new TH1D("h1","h1",100,lam_Min-10,lam_Max+10);
  TH1D *h1_abs = new TH1D("h1_abs","h1_abs",100,lam_Min-10,lam_Max+10);
  //
  //
  TRandom3 *rnd = new TRandom3(123123);
  Double_t alpha = 2.0;
  Double_t exponent = 1.0 - alpha;
  Double_t xmin_pow = TMath::Power(lam_Min, exponent);
  Double_t xmax_pow = TMath::Power(lam_Max, exponent);
  Double_t var;
  for(Int_t i = 0;i<1000000;i++){
    var = TMath::Power(rnd->Uniform() * (xmax_pow - xmin_pow) + xmin_pow, 1.0 / exponent);
    h1->Fill(var);
    if(if_ok(var, rnd, gr_reflectivity))
      if(if_ok(var, rnd, gr_qe))
	if(if_ok(var, rnd, gr_tr))
	  if(if_ok(var, rnd, 0.784))
	    if(if_ok(var, rnd, 0.9690))
	      if(if_ok(var, rnd, gr_atm_tr))   
		h1_abs->Fill(var);
  }
  //
  cout<<"Eff : "<<h1_abs->Integral()/h1->Integral()<<endl;
  
  //
  TCanvas *c4 = new TCanvas("c4","gr_qe",10,10,600,600);
  h1->SetLineColor(kBlack);
  h1->SetLineWidth(3.0);
  h1->SetMarkerColor(kBlack);
  h1->SetMarkerStyle(20);
  h1->Draw();
  h1_abs->SetLineColor(kRed+2);
  h1_abs->SetLineWidth(3.0);
  h1_abs->SetMarkerColor(kRed+2);
  h1_abs->SetMarkerStyle(20);
  h1_abs->Draw("sames");

  
  //
  return 0;
}

////////////////////////////////////////////////////
//
//
//# Provided by Yusuke Suda to MC team on 2020-04-23 (see Redmine issue 21060),
//# superceding ref_LST_2020-04-21.dat. Includes extended wavelength coverage.
//# Scaled from percentage to absolute values, as expected by sim_telarray. (KB).
//#
//# Col. 1: wavelength [nm] 
//# Col. 2: reflectivity
//# Col. 3: 1sigma (not used by sim_telarray)
//#
// 200.0          0.23457         0.03764
// 200.5          0.24264         0.03701
// .
// .
// .
//1099.0          0.82823         0.01177
//1099.5          0.82833         0.01167
//
//
/////////////////////////////////////////////////

void read_mirror_reflectivity_LST(TString atmFileName, TGraph *gr_wl, TGraph *gr_reflectivity, TGraphErrors *gr_err_reflectivity, TGraph *gr_1sigma){
  //
  ifstream fileIn(atmFileName.Data());
  cout<<"atm file : "<<atmFileName<<std::endl;
  //
  Double_t wl, reflectivity, onesigma;
  //
  TString mot;
  Int_t counter = 0;
  //
  if (fileIn.is_open()){
    //
    while(fileIn>>mot)
      if(mot == "sim_telarray)")
	break;
    fileIn>>mot; // #
    cout<<"mot = "<<mot<<endl;
    //
    while(fileIn>>wl>>reflectivity>>onesigma){
      gr_wl->SetPoint(counter,counter,wl);
      gr_reflectivity->SetPoint(counter,wl,reflectivity);
      gr_1sigma->SetPoint(counter,wl,onesigma);
      gr_err_reflectivity->SetPoint(counter,wl,reflectivity);
      gr_err_reflectivity->SetPointError(counter,0.25,2.0*onesigma);
      counter++;
    }
    fileIn.close();
    //
  }
  else {
    std::cout<<"Unable to open file"<<std::endl;
    assert(0);
  }
}

void read_qe_LST(TString fileName, TGraph *gr_qe){
    //
  ifstream fileIn(fileName.Data());
  cout<<"qe file : "<<fileName<<std::endl;
  //
  Double_t wl, qe;
  //
  TString mot;
  Int_t counter = 0;
  //
  if (fileIn.is_open()){
    //
    for(Int_t j= 0; j<292;j++)
      fileIn>>mot;
    cout<<"mot == "<<mot<<endl;
    //
    while(fileIn>>wl>>qe>>mot>>mot>>mot){
      if(wl<=600){
	gr_qe->SetPoint(counter,wl,qe);
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

void read_window_transmission_LST(TString fileName, TGraph *gr){
    //
  ifstream fileIn(fileName.Data());
  cout<<"window transmission file : "<<fileName<<std::endl;
  //
  Double_t wl, tr;
  //
  TString mot;
  Int_t counter = 0;
  //
  if (fileIn.is_open()){
    //
    while(fileIn>>mot)
      if(mot == "average(No.7-No.10)[%]")
	break;
    cout<<"mot = "<<mot<<endl;
    //
    while(fileIn>>wl>>tr){
	gr->SetPoint(counter,wl,tr);
	counter++;
    }
    fileIn.close();
    //
  }
  else {
    std::cout<<"Unable to open file"<<std::endl;
    assert(0);
  }
}

void read_atm_tr(TString fileName, TGraph *gr){
    //
  ifstream fileIn(fileName.Data());
  cout<<"atm tr file : "<<fileName<<std::endl;
  //
  Double_t wl, tr;
  //
  TString mot;
  Int_t counter = 0;
  //
  if (fileIn.is_open()){
    //
    fileIn>>mot>>mot>>mot>>mot;
    cout<<"mot = "<<mot<<endl;
    //
    while(fileIn>>mot>>wl>>mot>>tr){
	gr->SetPoint(counter,wl,tr);
	counter++;
    }
    fileIn.close();
    //
  }
  else {
    std::cout<<"Unable to open file"<<std::endl;
    assert(0);
  }
}

Bool_t if_ok(Double_t var, TRandom3 *rnd, TGraph *gr){
  if(rnd->Uniform(0,1)<=gr->Eval(var))
    return true;
  return false;
}

Bool_t if_ok(Double_t var, TRandom3 *rnd, Double_t constdegrad){
  if(rnd->Uniform(0,1)<=constdegrad)
    return true;
  return false;
}

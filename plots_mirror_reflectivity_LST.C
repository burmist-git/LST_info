void read_mirror_reflectivity_LST(TString atmFileName, TGraph *gr_wl, TGraph *gr_reflectivity, TGraphErrors *gr_err_reflectivity, TGraph *gr_1sigma);

Int_t plots_mirror_reflectivity_LST(){
  //
  TString fileName = "./lst-sim-config/mirror_reflectivity_LST.dat";
  //
  TGraph *gr_wl = new TGraph();
  TGraph *gr_reflectivity = new TGraph();
  TGraphErrors *gr_err_reflectivity = new TGraphErrors();
  TGraph *gr_1sigma = new TGraph();
  //
  read_mirror_reflectivity_LST(fileName, gr_wl, gr_reflectivity, gr_err_reflectivity, gr_1sigma);
  //
  //
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);
  //
  TCanvas *c1 = new TCanvas("c1","gr_Alt_km",10,10,600,600);
  gr_wl->SetLineColor(kBlack);
  gr_wl->SetLineWidth(3.0);
  gr_wl->SetMarkerColor(kBlack);
  gr_wl->SetMarkerStyle(20);
  gr_wl->Draw("APL");
  //
  TCanvas *c2 = new TCanvas("c2","gr_rho_g_cm3",10,10,600,600);
  gr_reflectivity->SetLineColor(kBlack);
  gr_reflectivity->SetLineWidth(3.0);
  gr_reflectivity->SetMarkerColor(kBlack);
  gr_reflectivity->SetMarkerStyle(20);
  gr_reflectivity->Draw("APL");
  //
  TCanvas *c3 = new TCanvas("c3","c3",10,10,600,600);
  gr_err_reflectivity->SetLineColor(kBlack);
  gr_err_reflectivity->SetLineWidth(3.0);
  gr_err_reflectivity->SetMarkerColor(kBlack);
  gr_err_reflectivity->SetMarkerStyle(20);
  gr_err_reflectivity->Draw("APL");
  //
  TCanvas *c4 = new TCanvas("c4","gr_thick_g_cm2",10,10,600,600);
  gr_1sigma->SetLineColor(kBlack);
  gr_1sigma->SetLineWidth(3.0);
  gr_1sigma->SetMarkerColor(kBlack);
  gr_1sigma->SetMarkerStyle(20);
  gr_1sigma->Draw("APL");
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

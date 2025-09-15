//void read_atm_trans(TString atmFileName, TH2Poly *h2poly);  
void read_atm_trans( TString atmFileName, TH2Poly *h2poly, Int_t nn_km_bin, Double_t *km_bin_center_arr, Int_t n_lambda_bins, Double_t *lam_bin_center_arr);

Int_t plots_atm_trans(){
  //
  TString atmFileName;
  //
  //atmFileName = "./atm_trans_2158_1_3_2_0_0_0.1_0.1.dat";
  atmFileName = "./atm_trans_0_1_10_0_0_0.dat";
  //
  const int nn = 45;
  Double_t H2_H1_arr_km[nn] =
    { 0.000,  0.050,  0.100,  0.200,   0.300,   0.500,  0.700,  1.000,  1.500,  2.000,
      2.500,  3.000,  3.500,  4.000,   4.500,   5.000,  5.500,  6.000,  7.000,  8.000,
      9.000, 10.000, 11.000, 12.000,  13.000,  14.000, 15.000, 16.000, 18.000, 20.000,
     22.000, 24.000, 26.000, 28.000,  30.000,  32.500, 35.000, 37.500, 40.000, 45.000,
     50.000, 60.000, 70.000, 80.000, 100.000};

  Double_t lambda_min  = 199.5;
  Double_t lambda_max  = 999.5;
  Double_t lambda_bin_width = 1.0;
  const Int_t n_lambda_bins = 800;

  
  //cout<<H2_H1_arr[44]<<endl;

  TH2Poly *h2poly = new TH2Poly();
  h2poly->SetNameTitle("h2poly","h2poly");
  
  Int_t n = 5;  
  Double_t* x;
  Double_t* y;

  Double_t lam_bin_center;
  Double_t lam_bin_center_arr[n_lambda_bins-1];
  Double_t lam_bin_L;
  Double_t lam_bin_R;
  Double_t km_bin_center;
  Double_t km_bin_center_arr[nn-1];
  Double_t km_bin_min;
  Double_t km_bin_max;

  x = new Double_t [n];
  y = new Double_t [n];
  for(Int_t i_km = 0;i_km<(nn-1);i_km++){
    //for(Int_t i_km = 0;i_km<1;i_km++){
    km_bin_center = H2_H1_arr_km[i_km] + (H2_H1_arr_km[i_km+1] - H2_H1_arr_km[i_km])/2.0;
    km_bin_min = km_bin_center - (H2_H1_arr_km[i_km+1] - H2_H1_arr_km[i_km])/2.0;
    km_bin_max = km_bin_center + (H2_H1_arr_km[i_km+1] - H2_H1_arr_km[i_km])/2.0;
    if(km_bin_min<0.01)
      km_bin_min = 0.01;
    cout<<i_km<<" "<<km_bin_min<<endl;
    //
    //
    km_bin_center_arr[i_km] = km_bin_center;
    //
    //
    for(Int_t i_lam = 0;i_lam<n_lambda_bins;i_lam++){
      lam_bin_center = lambda_min + lambda_bin_width/2.0 + lambda_bin_width*i_lam;
      lam_bin_L = lam_bin_center - lambda_bin_width/2.0 ;
      lam_bin_R = lam_bin_center + lambda_bin_width/2.0;
      //cout<<i_lam<<" "<<lam_bin_center<<endl;
      //
      //we go clockwise
      //
      //
      if(i_km == 0)
	lam_bin_center_arr[i_lam] = lam_bin_center;
      //
      //
      //
      x[0] = lam_bin_L;
      y[0] = km_bin_min;
      //
      x[1] = lam_bin_L;
      y[1] = km_bin_max;
      //
      x[2] = lam_bin_R;
      y[2] = km_bin_max;
      //
      x[3] = lam_bin_R;
      y[3] = km_bin_min;
      //
      x[4] = lam_bin_L;
      y[4] = km_bin_min;
      //
      h2poly->AddBin(n,x,y);      
    }
  }

  //for(Int_t i = 0;i<10000;i++){
  //h2poly->SetBinContent(i,i+1);
  //}
  
  //
  read_atm_trans( atmFileName, h2poly, nn-1, km_bin_center_arr, n_lambda_bins, lam_bin_center_arr);  
  //
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);
  //
  h2poly->SetMinimum(0.0);
  h2poly->SetMaximum(1.0);
  TCanvas *c1 = new TCanvas("c1","gr_Alt_km",10,10,600,600);

  TH2F *frame = new TH2F("h2","h2", 40, 200, 1000, 40, 0.01, 100.0);
  //frame->SetTitle("Proton rate, Hz");
  //frame->SetTitle(_title.Data());
  //frame->SetTitle(frame_title.Data());
  //frame->GetXaxis()->SetTitle("Theta, deg");
  //frame->GetYaxis()->SetTitle("Energy, GeV");
  //frame->GetXaxis()->CenterTitle();
  //frame->GetYaxis()->CenterTitle();
  //frame->GetYaxis()->SetTitleOffset(1.5);
  frame->SetStats(kFALSE);
  frame->Draw();
  //
  h2poly->Draw("same ZCOLOR");
  //h2poly->Draw();
  //
  return 0;
}

///////////////////////////////////////////////////////////////
//#============================
//#
//# MODTRAN options as follows:
//#
//# Atmospheric model: 1 (Tropical atmosphere)
//# Haze: 10 (DESERT extinction, VIS is wind speed dependent)
//# Season: 0
//# Vulcanic dust: 0
//# Zenith angle:  0.00 deg
//# End altitude: 0.000 km
//# Ground altitude: 0.000 km
//#
//#============================

//# H2= 0.000, H1=    0.050     0.100     0.200     0.300     0.500     0.700     1.000     1.500     2.000     2.500     3.000     3.500     4.000     4.500     5.000     5.500     6.000     7.000     8.000     9.000    10.000    11.000    12.000    13.000    14.000    15.000    16.000    18.000    20.000    22.000    24.000    26.000    28.000    30.000    32.500    35.000    37.500    40.000    45.000    50.000    60.000    70.000    80.000    100.000 
//        200       1.760238  2.515952  3.709572  4.736418  6.564166  8.239561 10.637457  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00  99999.00
// .
// .
// .
//       997       0.002754  0.004510  0.007377  0.009949  0.014454  0.018317  0.023320  0.030150  0.035472  0.039521  0.042751  0.045259  0.047511  0.049716  0.052030  0.054245  0.056253  0.059750  0.062195  0.063686  0.064752  0.065446  0.066033  0.066460  0.066888  0.067262  0.067583  0.068172  0.068814  0.069296  0.069672  0.069833  0.069940  0.070047  0.070101  0.070154  0.070208  0.070262  0.070262  0.070315  0.070315  0.070315  0.070315  0.070315
//       998       0.003305  0.005364  0.008637  0.011516  0.016434  0.020662  0.026087  0.033350  0.039105  0.043430  0.046777  0.049348  0.051662  0.053876  0.056200  0.058530  0.060546  0.064059  0.066514  0.068011  0.068975  0.069725  0.070262  0.070798  0.071174  0.071550  0.071872  0.072463  0.073055  0.073593  0.073916  0.074077  0.074185  0.074293  0.074346  0.074400  0.074454  0.074508  0.074562  0.074562  0.074562  0.074562  0.074562  0.074562
//       999       0.003406  0.005515  0.008889  0.011769  0.016841  0.021121  0.026652  0.034074  0.039781  0.044161  0.047563  0.050189  0.052505  0.054720  0.057100  0.059325  0.061344  0.064859  0.067316  0.068814  0.069779  0.070530  0.071066  0.071603  0.071979  0.072356  0.072678  0.073216  0.073862  0.074400  0.074724  0.074885  0.074993  0.075047  0.075155  0.075155  0.075262  0.075262  0.075370  0.075370  0.075370  0.075370  0.075370  0.075370

void read_atm_trans( TString atmFileName, TH2Poly *h2poly, Int_t nn_km_bin, Double_t *km_bin_center_arr, Int_t n_lambda_bins, Double_t *lam_bin_center_arr){
  //
  ifstream fileIn(atmFileName.Data());
  cout<<"atm file : "<<atmFileName<<std::endl;
  //
  Double_t val;
  TString mot;
  Int_t counter = 0;
  //
  if (fileIn.is_open()){
    //
    while(fileIn>>mot)
      if(mot == "H1=")
	break;
    //
    //
    for(Int_t i = 0;i<nn_km_bin;i++){
      fileIn>>val;
      //cout<<"val "<<val<<endl;
    }
    //
    //
    for(Int_t i_lam = 0;i_lam<n_lambda_bins;i_lam++){
      fileIn>>val;
      //cout<<"lam "<<val<<endl;
      for(Int_t i_km = 0;i_km<nn_km_bin;i_km++){
	fileIn>>val;
	//cout<<"  "<<val<<endl;
	//cout<<km_bin_center_arr[i_km]<<"  "<<val<<endl;
	h2poly->Fill(lam_bin_center_arr[i_lam],km_bin_center_arr[i_km],val);
	if(i_km == 6)
	  cout<<km_bin_center_arr[i_km]<<" "<<lam_bin_center_arr[i_lam]<<" "<<val<<" "<<TMath::Power(10,-val)<<endl;
      }
    }
    
    //
    //
    fileIn.close();
    //
    //
  }
  else {
    std::cout<<"Unable to open file"<<std::endl;
    assert(0);
  }
  //
  //for(Int_t i = 0;i<grtmp->GetN();i++){
  //grtmp->GetPoint(i,x,y);
  //_gr_wf_tmpl->SetPoint(i,x,grtmpstrached->Eval(x));
  //}
}

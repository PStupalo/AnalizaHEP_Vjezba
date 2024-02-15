// Include classes
#include "Analyzer.h"

// Declaring default constructor
Analyzer::Analyzer()
{
}

// Destructor declaration
Analyzer::~Analyzer()
{
}

// Function for the ChiSquareFit
void Analyzer::ChiSquareFit()
{
  c = new TCanvas("c","c",1200,800);
  c->Divide(2);
  gStyle->SetOptFit();

  c->cd(1);

  double F[5]  = {1,2,3,4,5};
  double a[5]  = {9.8,21.2,34.5,39.9,48.5};
  double sigma_F[5] = {0.,0.,0.,0.,0.};
  double sigma_a[5] = {1.0,1.9,3.1,3.9,5.1};
  double sum1=0, sum2=0;
  int i;

  gr = new TGraphErrors(5,F,a,sigma_F,sigma_a);

  gr->SetTitle("Mass of the ball measurement;F [N];a [m/s^{2}]");
  gr->SetMarkerColor(kBlack);
  gr->SetMarkerStyle(21);
  gr->Draw("AP");

  fit_funciton = new TF1("fit_function","x/[0]",0,50.);
  fit_funciton->SetParName(0,"mass");
  fit_funciton->SetParameter(0,0.1);

  gr->Fit(fit_funciton);

  c->cd(2);

  ChiSquare_function = new TF1("Chi-Square Function",
  "TMath::Power(([0]-[1]*x)/([2]),2)+TMath::Power(([3]-[4]*x)/([5]),2)+TMath::Power(([6]-[7]*x)/([8]),2)+TMath::Power(([9]-[10]*x)/([11]),2)+TMath::Power(([12]-[13]*x)/([14]),2)",9.4,11.0);

  for ( int i=0; i < 5*5; i = i+ 3)
  {
    ChiSquare_function->SetParameter(i,a[i/3]);
    ChiSquare_function->SetParameter(i+1,F[i/3]);
    ChiSquare_function->SetParameter(i+2,sigma_a[i/3]);
  }

  for(i=0;i<5;i++)
   {
	    sum1+=F[i]*a[i]/pow(sigma_a[i],2);
      sum2+=pow(F[i],2)/pow(sigma_a[i],2);
   }


  ChiSquare_function->SetTitle("Chi-Square function;mass^{-1} [kg^{-1}];#chi^{2}");

  ChiSquare_function->Draw();

  float oneOverMass_hat = sum1/sum2;

  float sigma_oneOverMass = sqrt(1./sum2);

  cout << endl;
  cout << "===================================================================================================" << endl;
  cout << "Analiticaly calculated parameter from the Chi-Square method: mass = " << 1/oneOverMass_hat << endl;
  cout << "Analiticaly calculated standard deviation from the Chi-Square method: sigma = " << sigma_oneOverMass/TMath::Power(oneOverMass_hat,2) << endl;
  cout << "===================================================================================================" << endl;
  cout << endl;

  float mass_hat;
  float sigma_m, sigma_p;

  mass_hat = ChiSquare_function->GetMinimumX();
  sigma_m = mass_hat - ChiSquare_function->GetX(ChiSquare_function->GetMinimum() + 1.0,mass_hat - 5., mass_hat-0.01);
  sigma_p = ChiSquare_function->GetX(ChiSquare_function->GetMinimum() + 1.0,mass_hat+0.01, mass_hat + 5.) - mass_hat;

  cout << "Control printout" << endl;
  cout << "Theta = " << ChiSquare_function->GetMinimumX() << endl;
  cout << "Theta_up = " << ChiSquare_function->GetX(ChiSquare_function->GetMinimum() + 1.0,mass_hat+0.01, mass_hat + 5.) << endl;
  cout << "Theta_dn = " << ChiSquare_function->GetX(ChiSquare_function->GetMinimum() + 1.0,mass_hat - 5., mass_hat-0.01) << endl;

  cout << endl;
  cout << "===================================================================================================" << endl;
  cout << "Parameter from the maximum of the Chi-Square function: mass = " << 1/mass_hat << endl;
  cout << "Uncertainty from the Chi-Square_max - 1.0: sigma_+ = " << sigma_p/TMath::Power(mass_hat,2) << " sigma_- = " << sigma_m/TMath::Power(mass_hat,2) << endl;
  cout << "===================================================================================================" << endl;
  cout << endl;

  ChiSquare_function->SetMinimum(1.0);

  line_h = new TLine(mass_hat-sigma_m,ChiSquare_function->GetMinimum() + 1.0,mass_hat+sigma_p,ChiSquare_function->GetMinimum() + 1.0);
  line_h->SetLineColor(kBlack);
  line_h->SetLineStyle(kDashed);
  line_h->Draw();

  line_v1 = new TLine(mass_hat-sigma_m,1.0,mass_hat-sigma_m,ChiSquare_function->GetMinimum() + 1.0);
  line_v1->SetLineColor(kBlack);
  line_v1->SetLineStyle(kDashed);
  line_v1->Draw();

  line_v2 = new TLine(mass_hat,1.0,mass_hat,ChiSquare_function->GetMinimum());
  line_v2->SetLineColor(kBlack);
  line_v2->SetLineStyle(kDashed);
  line_v2->Draw();

  line_v3 = new TLine(mass_hat+sigma_p,1.0,mass_hat+sigma_p,ChiSquare_function->GetMinimum() + 1.0);
  line_v3->SetLineColor(kBlack);
  line_v3->SetLineStyle(kDashed);
  line_v3->Draw();

  c->SaveAs("ChiSquareFit.pdf");

  delete c,gr;
}
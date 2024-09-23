#include <Analyzer.h>
Analyzer::Analyzer()
{

}
Analyzer::~Analyzer()
{

}
void Analyzer::MakeFit()
{
    TFile* inputFile = new TFile("/home/public/data/LinearHisto.root");

    TH1F* histogram;
    inputFile->GetObject("histogram", histogram);

    for (int i = 1; i <= histogram->GetNbinsX(); ++i) {
        double binContent = histogram->GetBinContent(i);
        double binError = histogram->GetBinError(i);

        std::cout << "Bin " << i << ", Content = " << binContent << ", Error = " << binError << std::endl;
    }

    auto ChiSquare_function = new TF1("Chi-Square Function",
     "TMath::Power(2807-400.*(x+10.)/(x+2.),2)/2807+ \
     TMath::Power(2459-400.*(3*x+10.)/(x+2.),2)/2459+ \
     TMath::Power(2036-400.*(5*x+10.)/(x+2.),2)/2036+ \
     TMath::Power(1540-400.*(7*x+10.)/(x+2.),2)/2540+ \
     TMath::Power(1158-400.*(9*x+10.)/(x+2.),2)/1158",-1.,0.);
     

    TCanvas* canvas1 = new TCanvas("canvas", "Canvas", 800, 600);
    ChiSquare_function->Draw();
    canvas1->SaveAs("ChiSquare.png");
    double a = ChiSquare_function->GetMinimumX();
    double a_up2 = ChiSquare_function->GetX(ChiSquare_function->GetMinimum() + 4.0, a+0.01, a + 0.6);
    double a_dn2 =  ChiSquare_function->GetX(ChiSquare_function->GetMinimum() + 4.0, a-0.3, a-0.01);
    std::cout<< "a = " <<ChiSquare_function->GetMinimumX()<<std::endl;
    cout << "a_up = " << a_up2 << endl;
    cout << "a_dn = " << a_dn2 << endl;

    TCanvas* canvas2 = new TCanvas("canvas1", "Canvas1", 800, 600);
    auto fit_function = new TF1("linear","1./[0]*10000*([1]*x+5)",0,5);
    fit_function->SetTitle("Chi Square fit on histogram");
    fit_function->SetParameter(0,16.25); //16.25 je normalizacija
    fit_function->SetParameter(1,a);
    fit_function->Draw();
    histogram->Draw("SAME HISTO");
    canvas2->SaveAs("Fit.png");

   
    inputFile->Close();

}
#include "Analyzer.h"
#include <cmath>
Analyzer::Analyzer()
{

}
Analyzer::~Analyzer()
{

}
double Analyzer::BinomialProb(int r, double p, int N)
{
  return TMath::Binomial(N,r)*pow(p,r)*pow((1-p),N-r);
}
pair<double,double> Analyzer::CPinterval(double CL, int N, int m)
{
  double p_up=1.0,p_dn=0,sum_up=0,sum_dn=0,increment=0.001;
  int r;

  while(sum_up<(1-CL)/2.)
  {
     sum_up=0;
     for(r=0;r<=m;r++)
     {
       sum_up+=BinomialProb(r,p_up,N);
     }
     p_up-=increment;
  }

  while(sum_dn<(1-CL)/2.)
  {
     sum_dn=0;
     for(r=m;r<=N;r++)
     {
       sum_dn+=BinomialProb(r,p_dn,N);
     }
     p_dn+=increment;
  }

  if(p_dn-2*increment<0)
  return make_pair(0, p_up+2*increment);
  else if(p_up+2*increment>1)
  return make_pair(p_dn-2*increment, 1);
  else
  return make_pair(p_dn-2*increment, p_up+2*increment);
}
void Analyzer::CPbelt(int N, double CL)
{
  gStyle->SetOptStat(0);
  THStack* hs = new THStack("hs","");
  TH1F* Histo_up = new TH1F("up", "up", 11, 0, 11);
	TH1F* Histo_down = new TH1F("down", "down", 11, 0, 11);
  TCanvas *canvas = new TCanvas("c1","Clopper-Pearson belt",900,700);
  for(int m=0;m<=10;m++)
	{
		Histo_up->SetBinContent(m+1,CPinterval(CL,N,m).second-CPinterval(CL,N,m).first);
		Histo_down->SetBinContent(m+1,CPinterval(CL,N,m).first);
    Histo_up->GetXaxis()->SetBinLabel(m+1,to_string(m).c_str());
    Histo_down->GetXaxis()->SetBinLabel(m+1,to_string(m).c_str());
  }

  Histo_down->SetFillColor(kWhite);
  Histo_down->GetXaxis()->SetTitle("m");
  Histo_up->SetFillColor(kOrange+7);
  hs->Add(Histo_down);
  hs->Add(Histo_up);
  hs->Draw();
  hs->GetXaxis()->SetTitle("m");
  hs->GetYaxis()->SetTitle("p");
  hs->SetTitle("Clopper-Pearson confidence belt");

  //Example for m=6
  TLine *line1=new TLine(6.5,0,6.5,CPinterval(CL,N,6).second);
  TLine *line2=new TLine(0,CPinterval(CL,N,6).first,6.5,CPinterval(CL,N,6).first);
  TLine *line3=new TLine(0,CPinterval(CL,N,6).second,6.5,CPinterval(CL,N,6).second);
	line1->SetLineStyle(kDashed);
	line2->SetLineStyle(kDashed);
	line3->SetLineStyle(kDashed);
  line1->Draw("SAME");
  line2->Draw("SAME");
  line3->Draw("SAME");

  canvas->SaveAs("CPbelt.pdf");
}
void Analyzer::Game()
{
  srand((unsigned)time(0));
  int i,j,h,r,covered=0;
  double p_true;
  for(j=1;j<=1000;j++)
  {
  r=0;
  for(i=1;i<=10;i++)
  {
    h = (rand()%6)+1;
    if(h==6)
    r++;
  }
  if(1./6<=CPinterval(0.6827,10,r).second && 1./6>=CPinterval(0.6827,10,r).first)
  covered++;
  }
  cout<<"Clopper-Pearson coverage:"<<covered*1./1000<<endl;
}
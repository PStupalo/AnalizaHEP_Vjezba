#include <Analyzer.h>
Analyzer::Analyzer()
{

}
Analyzer::~Analyzer()
{

}
void Analyzer::ProoveCLT()
{
  TRandom3 random;
  int PredictedSum=0;

	TH1F * hexp = new TH1F("exp","exp",100, 500., 2000.);

  double SumExp;

	for(int i=0; i<1000000; i++)
	{
		SumExp=0.;

	for (int j=1; j<=50; j++)
	{
    double y = random.Exp(j);
		SumExp+=y;
  }

    hexp->Fill(SumExp);
  }

  TCanvas * c = new TCanvas();
  
  hexp->Draw();

  c->SaveAs("SumDistribution.pdf");
  
  for(int k=1;k<=50;k++)
  PredictedSum+=k;

  std::cout<<"Mean from histogram:"<<hexp->GetMean(1)<<std::endl;
  std::cout<<"Predicted mean:"<<PredictedSum<<std::endl;  

}
#include "Generator.h"

Generator::Generator(){

}

void Generator::GeneratePDF(){
	srand((unsigned)1);
	i = 0;
	canvas = new TCanvas ();
	hist = new TH1F ("GeneratePDF", "GeneratePDF", 48, -3., 9.); //48 binova, u rangu [-3,9]
	while (i < 1E5){ //generiramo 10^5 vrijednosti
		rn1 = -3 + 12 * (float)rand () / RAND_MAX;
		f = (-rn1 * rn1 + 6 * rn1 + 27) / 36.; //-(x+3)(x-9)=-(x^2-6x-27)=-x^2+6x+27
		rn2 = -3 + 12 * (float)rand () /RAND_MAX;
		if (rn2 < f){
			hist -> Fill (rn1);
			i++;
		}
	}
	gPad -> SetLeftMargin (0.20);
	gPad -> SetBottomMargin (0.20);
	canvas -> SetCanvasSize (800, 800);
	canvas -> SetTitle ("GeneratePDF");
	hist->SetFillColor(kRed);
  	hist->SetLineColor(kRed);
	hist -> Draw ("HIST");
	hist -> GetXaxis () -> SetTitle ("Generated value");
	hist -> GetYaxis () -> SetTitle ("Events / 0.25");
	hist -> GetXaxis () -> SetLabelSize (0.03);
	hist -> GetYaxis () -> SetLabelSize (0.03);
	//hist -> SetFillColor (kRed);
	//hist -> SetLineColor (kRed);
	
	canvas -> Print ("zad1.pdf");
	canvas -> Print ("zad1.png");
	canvas -> Print ("zad1.root");

}


#include "Analyzer.h"

Analyzer::Analyzer()
{
    //konstruktor
}

Analyzer::~Analyzer()
{
    //destruktor
}

void Analyzer:: LifetimeFit(){
    //1.zad 
    file = new TFile("/home/public/data/Lifetime/Lifetime.root");
    tree = (TTree*)file->Get("Tree"); //Dohvaća stablo podataka iz ROOT datoteke
    tree->SetBranchAddress("t",&t); //Postavlja vezu između grane koja sadrži vremena poluraspada ("t") i varijable t u koju će se učitavati vrijednosti.

    gStyle->SetOptStat(0); //brisanje statistike na hist (gornji desni kut njacesce)
    HistoLifetime = new TH1F("Lifetime", "Lifetime", 24, 0.0, 10.0);

    exp = new TF1("exp","[0]/[1]*exp(-x/[1])",0.0,10.0); //formula po kojoj fittamo, iz predavanja: 1/tau*exp(-t/tau)
    exp->SetParameter(0,100.);
    exp->SetParameter(1,1.);

    sum =0;
    nentries = tree->GetEntries();
    for (i = 0; i < nentries; i++)
    {
        tree->GetEntry(i);
        HistoLifetime->Fill(t);
        sum += t;
    }

    HistoLifetime->Fit(exp,"L");

    //crtanje platna
    canvas1 = new TCanvas("canvas1","canvas1",600,400);
    HistoLifetime->GetXaxis()->SetTitle("t/s");
    HistoLifetime->GetYaxis()->SetTitle("N");
    HistoLifetime->Draw();
    canvas1->SaveAs("LifetimeFit.pdf");

    std::cout << "Koristeci root: tau = " << exp->GetParameter(1) << "±" << exp->GetParError(1) << endl;


    C=exp->GetParameter(0);
    delete exp;
    
	//2.zad - t=1s
    Likelihood = new TF1("Likelihood","([0]/x)*exp(-1.0/x)",0.1,10); //za t=1
    Likelihood->SetParameter(0,C);

    //novo platno
    canvas2 = new TCanvas("canvas2","canvas2",600,400);
    Likelihood->GetXaxis()->SetTitle("#tau");
    Likelihood->GetYaxis()->SetTitle("L(#tau)");
    Likelihood->SetTitle("Likelihood function for t=1s");
    Likelihood->Draw();
    canvas2->SaveAs("Likelihood.pdf");

    delete Likelihood;

    //3.zad, analiticki tau
    mean=sum/nentries;
    error=mean/sqrt(nentries);
    std::cout<<"Analiticki: tau = "<<mean<<"±"<<error<<endl;

    //4.zad, lnL, racunanje tau, preko minimuma logL
    LogLikelihood = new TF1("LogLikelihood","-2*([0]*log(1./x)-[1]/x)",0.1,5); // mogu uzet C=1, rezultat ostaje isti
    LogLikelihood->SetParameter(0,nentries); //broj dogadaja
    LogLikelihood->SetParameter(1,sum);//suma svih vremena

    //novo platno - crtanje logL funkcije
    canvas3=new TCanvas("canvas1","canvas1",600,400);
    LogLikelihood->GetXaxis()->SetTitle("#tau"); //ovdje nam je tau na x osi
    LogLikelihood->GetYaxis()->SetTitle("-2lnL(#tau)");
    LogLikelihood->SetTitle("Log Likelihood function");
    LogLikelihood->Draw();
    canvas3->SaveAs("LogLikelihood.pdf");

    //sada iz logL funkcije mjerimo parametar tau tako sto minimiziramo gunkciju
    tau_graph=LogLikelihood->GetMinimumX();
    Float_t err_dn=tau_graph-LogLikelihood->GetX(LogLikelihood->GetMinimum(0.1,5)+1,0.1,tau_graph); //-2lnL=lnL_min+1
    Float_t err_up=LogLikelihood->GetX(LogLikelihood->GetMinimum(0.1,5)+1,tau_graph,5)-tau_graph; //-2lnL=lnL_min+1

    std::cout<<"Graficki: tau = "<<tau_graph<<"+"<<err_up<<"-"<<err_dn<<endl;

    delete LogLikelihood;

    delete HistoLifetime, file, tree;

    canvas1->Destructor();
    canvas2->Destructor();
    canvas3->Destructor();






}

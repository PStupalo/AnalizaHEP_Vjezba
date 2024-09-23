#define Analyzer_cxx
#include "Analyzer.h"


void Analyzer::Loop()
{
   histo_signal[0]     = new TH1F("ele_pt_s","ele_pt_s",50,0.,100.);
   histo_background[0] = new TH1F("ele_pt_b","ele_pt_b",50,0.,100.);

   histo_signal[1]     = new TH1F("scl_eta_s","scl_eta_s",60,-3.0,3.0);
   histo_background[1] = new TH1F("scl_eta_b","scl_eta_s",60,-3.0,3.0);

   histo_signal[2]     = new TH1F("ele_hOverE_s","ele_hOverE_s",20,0.,0.2);
   histo_background[2] = new TH1F("ele_hOverE_b","ele_hOverE_b",20,0.,0.2);

   histo_signal[3]     = new TH1F("ele_Chi2_s","ele_Chi2_s",100,0.,10.);
   histo_background[3] = new TH1F("ele_Chi2_b","ele_Chi2_b",100,0.,10.);

   histo_signal[4]     = new TH1F("ele_fbrem_s","ele_fbrem_s",100,0.,1.);
   histo_background[4] = new TH1F("ele_fbrem_b","ele_fbrem_b",100,0.,1.);

   histo_signal[5]     = new TH1F("ele_ep_s","ele_ep_s",100,0.,10.);
   histo_background[5] = new TH1F("ele_ep_b","ele_ep_b",100,0.,10.);

   histo_signal[6]     = new TH1F("ele_epout_s","ele_epout_s",100,0.,10.);
   histo_background[6] = new TH1F("ele_epout_b","ele_epout_b",100,0.,10.);

   histo_signal[7]     = new TH1F("ele_chIso_s","ele_chIso_s",100,0.,2.);
   histo_background[7] = new TH1F("ele_chIso_b","ele_chIso_b",100,0.,2.);

   Init(signal);

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry< nentries;jentry++)
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      histo_signal[0]->Fill(ele_pt);
      histo_signal[1]->Fill(scl_eta);
      histo_signal[2]->Fill(ele_hadronicOverEm);
      histo_signal[3]->Fill(ele_gsfchi2);
      histo_signal[4]->Fill(ele_fbrem);
      histo_signal[5]->Fill(ele_ep);
      histo_signal[6]->Fill(ele_eelepout);
      histo_signal[7]->Fill(ele_pfChargedHadIso);

   }

   Init(background);

   nentries = fChain->GetEntriesFast();

   nbytes = 0, nb = 0;

   for (Long64_t jentry=0; jentry< nentries;jentry++)
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      histo_background[0]->Fill(ele_pt);
      histo_background[1]->Fill(scl_eta);
      histo_background[2]->Fill(ele_hadronicOverEm);
      histo_background[3]->Fill(ele_gsfchi2);
      histo_background[4]->Fill(ele_fbrem);
      histo_background[5]->Fill(ele_ep);
      histo_background[6]->Fill(ele_eelepout);
      histo_background[7]->Fill(ele_pfChargedHadIso);

   }

   c = new TCanvas("c","c",800,1600);
   c->Divide(2,4);

   c->cd(1);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histo_background[0]->SetLineColor(kBlue);
   histo_signal[0]->SetLineColor(kRed);
   histo_signal[0]->SetStats(0);
   histo_signal[0]->Scale(1/histo_signal[0]->Integral());
   histo_background[0]->Scale(1/histo_background[0]->Integral());
   histo_signal[0]->SetTitle("");
   histo_signal[0]->GetXaxis()->SetTitle("electron p_{T}");
   histo_signal[0]->GetYaxis()->SetTitle("Events / 2 GeV");
   histo_signal[0]->GetXaxis()->SetTitleSize(0.07);
   histo_signal[0]->GetYaxis()->SetTitleSize(0.07);
   histo_signal[0]->Draw("HIST");
   histo_background[0]->Draw("HIST SAME");
   if ( histo_background[0]->GetMaximum() > histo_signal[0]->GetMaximum()) histo_signal[0]->SetMaximum(1.3*histo_background[0]->GetMaximum());

   c->cd(2);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histo_background[1]->SetLineColor(kBlue);
   histo_signal[1]->SetLineColor(kRed);
   histo_signal[1]->SetStats(0);
   histo_signal[1]->Scale(1/histo_signal[1]->Integral());
   histo_background[1]->Scale(1/histo_background[1]->Integral());
   histo_signal[1]->SetTitle("");
   histo_signal[1]->GetXaxis()->SetTitle("supercluster #eta");
   histo_signal[1]->GetYaxis()->SetTitle("Events / 0.1");
   histo_signal[1]->GetXaxis()->SetTitleSize(0.07);
   histo_signal[1]->GetYaxis()->SetTitleSize(0.07);
   histo_signal[1]->Draw("HIST");
   histo_background[1]->Draw("HIST SAME");
   if ( histo_background[1]->GetMaximum() > histo_signal[1]->GetMaximum()) histo_signal[1]->SetMaximum(1.3*histo_background[1]->GetMaximum());

   c->cd(3);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histo_background[2]->SetLineColor(kBlue);
   histo_signal[2]->SetLineColor(kRed);
   histo_signal[2]->SetStats(0);
   histo_signal[2]->Scale(1/histo_signal[2]->Integral());
   histo_background[2]->Scale(1/histo_background[2]->Integral());
   histo_signal[2]->SetTitle("");
   histo_signal[2]->GetXaxis()->SetTitle("electron H/E");
   histo_signal[2]->GetYaxis()->SetTitle("Events / 0.01");
   histo_signal[2]->GetXaxis()->SetTitleSize(0.07);
   histo_signal[2]->GetYaxis()->SetTitleSize(0.07);
   histo_signal[2]->Draw("HIST");
   histo_background[2]->Draw("HIST SAME");
   if ( histo_background[2]->GetMaximum() > histo_signal[2]->GetMaximum()) histo_signal[2]->SetMaximum(1.3*histo_background[2]->GetMaximum());

   c->cd(4);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histo_background[3]->SetLineColor(kBlue);
   histo_signal[3]->SetLineColor(kRed);
   histo_signal[3]->SetStats(0);
   histo_signal[3]->Scale(1/histo_signal[3]->Integral());
   histo_background[3]->Scale(1/histo_background[3]->Integral());
   histo_signal[3]->SetTitle("");
   histo_signal[3]->GetXaxis()->SetTitle("electron fit #chi^{2}");
   histo_signal[3]->GetYaxis()->SetTitle("Events / 0.1");
   histo_signal[3]->GetXaxis()->SetTitleSize(0.07);
   histo_signal[3]->GetYaxis()->SetTitleSize(0.07);
   histo_signal[3]->Draw("HIST");
   histo_background[3]->Draw("HIST SAME");
   if ( histo_background[3]->GetMaximum() > histo_signal[3]->GetMaximum()) histo_signal[3]->SetMaximum(1.3*histo_background[3]->GetMaximum());

   c->cd(5);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histo_background[4]->SetLineColor(kBlue);
   histo_signal[4]->SetLineColor(kRed);
   histo_signal[4]->SetStats(0);
   histo_signal[4]->Scale(1/histo_signal[4]->Integral());
   histo_background[4]->Scale(1/histo_background[4]->Integral());
   histo_signal[4]->SetTitle("");
   histo_signal[4]->GetXaxis()->SetTitle("electron f_{brem}");
   histo_signal[4]->GetYaxis()->SetTitle("Events / 0.01");
   histo_signal[4]->GetXaxis()->SetTitleSize(0.07);
   histo_signal[4]->GetYaxis()->SetTitleSize(0.07);
   histo_signal[4]->Draw("HIST");
   histo_background[4]->Draw("HIST SAME");
   if ( histo_background[4]->GetMaximum() > histo_signal[4]->GetMaximum()) histo_signal[4]->SetMaximum(1.3*histo_background[4]->GetMaximum());

   c->cd(6);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histo_background[5]->SetLineColor(kBlue);
   histo_signal[5]->SetLineColor(kRed);
   histo_signal[5]->SetStats(0);
   histo_signal[5]->Scale(1/histo_signal[5]->Integral());
   histo_background[5]->Scale(1/histo_background[5]->Integral());
   histo_signal[5]->SetTitle("");
   histo_signal[5]->GetXaxis()->SetTitle("electron E-p");
   histo_signal[5]->GetYaxis()->SetTitle("Events / 0.1 GeV");
   histo_signal[5]->GetXaxis()->SetTitleSize(0.07);
   histo_signal[5]->GetYaxis()->SetTitleSize(0.07);
   histo_signal[5]->Draw("HIST");
   histo_background[5]->Draw("HIST SAME");
   if ( histo_background[5]->GetMaximum() > histo_signal[5]->GetMaximum()) histo_signal[5]->SetMaximum(1.3*histo_background[5]->GetMaximum());

   c->cd(7);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histo_background[6]->SetLineColor(kBlue);
   histo_signal[6]->SetLineColor(kRed);
   histo_signal[6]->SetStats(0);
   histo_signal[6]->Scale(1/histo_signal[6]->Integral());
   histo_background[6]->Scale(1/histo_background[6]->Integral());
   histo_signal[6]->SetTitle("");
   histo_signal[6]->GetXaxis()->SetTitle("electron E-p_{out}");
   histo_signal[6]->GetYaxis()->SetTitle("Events / 0.1 GeV");
   histo_signal[6]->GetXaxis()->SetTitleSize(0.07);
   histo_signal[6]->GetYaxis()->SetTitleSize(0.07);
   histo_signal[6]->Draw("HIST");
   histo_background[6]->Draw("HIST SAME");
   if ( histo_background[6]->GetMaximum() > histo_signal[6]->GetMaximum()) histo_signal[6]->SetMaximum(1.3*histo_background[6]->GetMaximum());

   c->cd(8);
   gPad->SetLeftMargin(0.2);
   gPad->SetBottomMargin(0.2);
   histo_background[7]->SetLineColor(kBlue);
   histo_signal[7]->SetLineColor(kRed);
   histo_signal[7]->SetStats(0);
   histo_signal[7]->Scale(1/histo_signal[7]->Integral());
   histo_background[7]->Scale(1/histo_background[7]->Integral());
   histo_signal[7]->SetTitle("");
   histo_signal[7]->GetXaxis()->SetTitle("electron charged Iso");
   histo_signal[7]->GetYaxis()->SetTitle("Events / 0.02 GeV");
   histo_signal[7]->GetXaxis()->SetTitleSize(0.07);
   histo_signal[7]->GetYaxis()->SetTitleSize(0.07);
   histo_signal[7]->Draw("HIST");
   histo_background[7]->Draw("HIST SAME");
   if ( histo_background[7]->GetMaximum() > histo_signal[7]->GetMaximum()) histo_signal[7]->SetMaximum(1.3*histo_background[7]->GetMaximum());

   c->SaveAs("ElectronDistributions.pdf");
}

void Analyzer::MVATraining(TString method)
{
   TMVA::Tools::Instance();

   TString outfileName( "TMVA_"+method+".root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                              "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");

   dataloader->AddVariable( "ele_pt","Variable 1", "", 'F' );
   dataloader->AddVariable( "scl_eta","Variable 2", "", 'F' );
   dataloader->AddVariable( "ele_fbrem","Variable 3", "", 'F' );
   dataloader->AddVariable( "ele_eelepout","Variable 4", "", 'F' );

   dataloader->AddVariable( "ele_hadronicOverEm","Variable 5", "", 'F' );
   dataloader->AddVariable( "ele_gsfchi2","Variable 6", "", 'F' );
   dataloader->AddVariable( "ele_pfChargedHadIso","Variable 7", "", 'F' );
   dataloader->AddVariable( "ele_ep","Variable 8", "", 'F' );


   // You can add an arbitrary number of signal or background trees
   dataloader->AddSignalTree    ( signal,     1. );
   dataloader->AddBackgroundTree( background, 1. );

   dataloader->PrepareTrainingAndTestTree( "", "", "nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V" );

   if(method == "GBDT") factory->BookMethod( dataloader, TMVA::Types::kBDT, method,"!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2" );
   if(method == "kMLP") factory->BookMethod( dataloader, TMVA::Types::kMLP, method, "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );


   // Train MVAs using the set of training events
   factory->TrainAllMethods();
   // Evaluate all MVAs using the set of test events
   factory->TestAllMethods();
   // Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();
   // --------------------------------------------------------------
   // Save the output
   outputFile->Close();
   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   delete factory;
   delete dataloader;

}

void Analyzer::PlotMVAScore(TString method)
{
    c = new TCanvas("c","c",900,900);

    if(method == "GBDT")
    {
      TFile* file = new TFile("TMVA_GBDT.root","READ");

      MVAScore_signal = (TH1D*)file->Get("dataset/Method_BDT/GBDT/MVA_GBDT_S");
      MVAScore_background = (TH1D*)file->Get("dataset/Method_BDT/GBDT/MVA_GBDT_B");
      sig_bkg_eff = (TH1F*)file->Get("dataset/Method_BDT/GBDT/MVA_GBDT_effBvsS");
    }

    else if(method == "kMLP")
    {
      TFile* file = new TFile("TMVA_kMLP.root","READ");

      MVAScore_signal = (TH1D*)file->Get("dataset/Method_MLP/kMLP/MVA_kMLP_S");
      MVAScore_background = (TH1D*)file->Get("dataset/Method_MLP/kMLP/MVA_kMLP_B");
      sig_bkg_eff = (TH1F*)file->Get("dataset/Method_MLP/kMLP/MVA_kMLP_effBvsS");
    }

    MVAScore_background->SetLineColor(kBlue);
    MVAScore_signal->SetLineColor(kRed);
    MVAScore_signal->SetLineWidth(3);
    MVAScore_background->SetLineWidth(3);
    MVAScore_signal->SetStats(0);
    MVAScore_signal->Scale(1/MVAScore_signal->Integral());
    MVAScore_background->Scale(1/MVAScore_background->Integral());
    MVAScore_signal->SetTitle(method + " Score");
    MVAScore_signal->GetXaxis()->SetTitle(method);
    MVAScore_signal->GetYaxis()->SetTitle("Events 0.05");
    MVAScore_signal->Draw("HIST");
    MVAScore_background->Draw("HIST SAME");
    if ( MVAScore_background->GetMaximum() > MVAScore_signal->GetMaximum()) MVAScore_signal->SetMaximum(1.3*MVAScore_background->GetMaximum());

    c->SaveAs("MVAScore_"+method+".pdf");

    cout<<"Udio propustenog backgrounda za 90% signala: "<< sig_bkg_eff->Interpolate(0.9)*100<<"%"<<endl;

}
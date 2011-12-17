#include "MergePlots.h"
#include "DrawOptions.h"

#include <TCanvas.h>
#include <TPaveStats.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TF1.h>
#include <TH1D.h>
#include <TLatex.h>
#include <iostream>
#include <vector>
//#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

MergePlots::MergePlots(std::string dirname) : dirname_(dirname) {}
MergePlots::~MergePlots() {}

void MergePlots::addDataSet(std::string dataSet, string dataName )
{
	// Get the draw options for the dataset from the DrawOptions class
	DrawOptions* myOptions = new DrawOptions(dataName);
	
	// Create vector of ROOT files, one entry for each dataset
	TString dsRootFileName = dirname_ + dataSet + ".root";
	cout << "Adding " << dsRootFileName << endl;
	TFile* rootFile = new TFile(dsRootFileName, "read");
	
	//rootFile->Print();
	dataFileVec.push_back(rootFile);
	
	// Add dataset variables to other vectors
	drawOptVec.push_back(myOptions->drawOpt);
	
	colorVec.push_back(myOptions->color);
	linewidthVec.push_back(myOptions->linewidth);
	fillcolorVec.push_back(myOptions->fillcolor); 
	linestyleVec.push_back(myOptions->linestyle);
	dataNameVec.push_back(dataSet);

       
	legendVec.push_back(dataName);
}

void MergePlots::mergeHist(char* histname, string titlex, string titley, bool legend, TString drawOpt )
{
	TCanvas *myCanvas = new TCanvas ("", "");
	
	TLegend myLegend(0.68, 0.62, 0.88, 0.92);

	myLegend.SetBorderSize(0);
	//L[id]->SetFillColor(0);
	//L[id]->SetLineColor(1);
	myLegend.SetLineStyle(0);
	myLegend.SetTextFont(42);
	myLegend.SetFillStyle(0);


	myCanvas->SetLogy();
	//myCanvas->SetGridx();
	//myCanvas->SetGridy();
	
	//gPad->RedrawAxis();


	int it = 0;
	//Double_t maxsize=0;

	for (vector<TFile*>::iterator tfileIt = dataFileVec.begin();tfileIt!=dataFileVec.end();tfileIt++)
	{
		(*tfileIt)->GetListOfKeys()->Print();

		cout << " still alive " << endl;
		if( fillcolorVec[it]!=111 && fillcolorVec[it]!=112  && fillcolorVec[it]!=113 ) 
		{
			((TH1D*)(*tfileIt)->Get(histname))->SetFillColor(fillcolorVec[it]);
			if(legend==true)  myLegend.AddEntry(((TH1D*)(*tfileIt)->Get(histname)),legendVec[it], "F");
		}
		if( fillcolorVec[it]==111  ) 
		{
			((TH1D*)(*tfileIt)->Get(histname))->Sumw2();

			((TH1D*)(*tfileIt)->Get(histname))->SetMarkerStyle(8);
			((TH1D*)(*tfileIt)->Get(histname))->SetMarkerSize(1.4);
			if(legend==true)  myLegend.AddEntry(((TH1D*)(*tfileIt)->Get(histname)),legendVec[it], "lp");
		}
		if(  fillcolorVec[it]==112  ) 
		{
			((TH1D*)(*tfileIt)->Get(histname))->SetLineStyle(2);
			((TH1D*)(*tfileIt)->Get(histname))->SetLineWidth(3);
			((TH1D*)(*tfileIt)->Get(histname))->SetLineColor(2);
			if(legend==true)  myLegend.AddEntry(((TH1D*)(*tfileIt)->Get(histname)),legendVec[it], "lp");
		}
		if(  fillcolorVec[it]==113  ) 
		{
			((TH1D*)(*tfileIt)->Get(histname))->SetLineStyle(2);
			((TH1D*)(*tfileIt)->Get(histname))->SetLineWidth(3);
			((TH1D*)(*tfileIt)->Get(histname))->SetLineColor(4);
			if(legend==true)  myLegend.AddEntry(((TH1D*)(*tfileIt)->Get(histname)),legendVec[it], "lp");
		}

		if(it==0) 
		{
			(*tfileIt)->Get(histname)->Draw();
		}
		else
		{
			((TH1D*)(*tfileIt)->Get(histname))->Draw("sames");
		}
	
		///Adjust stat location

		if(legend ==false)
		{
			gPad->Update();
			TPaveStats *st = (TPaveStats*)((TH1D*)(*tfileIt)->Get(histname))->FindObject("stats");
	
			st->SetTextColor( fillcolorVec[it] );
			
			double y = it*0.18;
			st->SetX1NDC(0.75);
			st->SetX2NDC(0.92);
			st->SetY1NDC( 0.8-y);
			st->SetY2NDC( 0.97-y );
		}

		
		((TH1D*)(*tfileIt)->Get(histname))->GetXaxis()->SetTitle( titlex.c_str() );
		((TH1D*)(*tfileIt)->Get(histname))->GetYaxis()->SetTitle( titley.c_str() );
		

		((TH1D*)(*tfileIt)->Get(histname))->GetXaxis()->SetTitleFont(42);
		((TH1D*)(*tfileIt)->Get(histname))->GetXaxis()->SetTitleSize(0.06);

		((TH1D*)(*tfileIt)->Get(histname))->GetYaxis()->SetTitleFont(42);
		((TH1D*)(*tfileIt)->Get(histname))->GetYaxis()->SetTitleSize(0.06);

		((TH1D*)(*tfileIt)->Get(histname))->GetXaxis()->SetTitleOffset(0.9);
		((TH1D*)(*tfileIt)->Get(histname))->GetYaxis()->SetTitleOffset(1.25);
		

		
		//Float_t labelSize = 0.05;

		//((TH1D*)(*tfileIt)->Get(histname))->GetXaxis()->SetLabelSize( labelSize );
		//((TH1D*)(*tfileIt)->Get(histname))->GetYaxis()->SetLabelSize( labelSize );
		//
		//((TH1D*)(*tfileIt)->Get(histname))->GetXaxis()->SetLabelFont( 42 );
		//
 	//	((TH1D*)(*tfileIt)->Get("NJet"))->GetXaxis()->CenterLabels(kTRUE);
 	//	((TH1D*)(*tfileIt)->Get("NJet"))->SetNdivisions(10);
 	//	((TH1D*)(*tfileIt)->Get("MetMu2"))->GetXaxis()->SetNdivisions(6,4,0, kFALSE);
 	//	((TH1D*)(*tfileIt)->Get("MetMu3"))->GetXaxis()->SetNdivisions(6,4,0, kFALSE);
 
 	//	((TH1D*)(*tfileIt)->Get("Jet1Pt"))->GetXaxis()->SetNdivisions(7,4,0, kFALSE);
 	//	((TH1D*)(*tfileIt)->Get("Jet1Pt2"))->GetXaxis()->SetNdivisions(7,4,0, kFALSE);
 
 	//	((TH1D*)(*tfileIt)->Get("Jet2Pt"))->GetXaxis()->SetNdivisions(6,4,0, kFALSE);
 	//	((TH1D*)(*tfileIt)->Get("MuonPt_2"))->GetXaxis()->SetNdivisions(6,5,0, kFALSE);
 
 	//	((TH1D*)(*tfileIt)->Get("PFElecPt"))->GetXaxis()->SetNdivisions(8,10,0, kFALSE);
 	//	((TH1D*)(*tfileIt)->Get("PFMuonPt"))->GetXaxis()->SetNdivisions(8,10,0, kFALSE);

		
 	//	((TH1D*)(*tfileIt)->Get("NofMuon"))->GetXaxis()->CenterLabels(kTRUE);
 	//	((TH1D*)(*tfileIt)->Get("NofMuon"))->SetNdivisions(10);

		//((TH1D*)(*tfileIt)->Get("WmunuMT"))->GetXaxis()->SetNdivisions(5,10,0, kFALSE);
		//((TH1D*)(*tfileIt)->Get("ZmumuMT"))->GetXaxis()->SetNdivisions(10,10,0, kFALSE);
		//((TH1D*)(*tfileIt)->Get("ZmumuMT_2"))->GetXaxis()->SetNdivisions(5,10,0, kFALSE);


		((TH1D*)(*tfileIt)->Get(histname))->GetYaxis()->SetLabelFont( 42 );

		vector<Float_t> ent;

			for(int i=1; i<((TH1D*)(*tfileIt)->Get(histname))->GetNbinsX(); i++ )
			{
			     ent.push_back( ((TH1D*)(*tfileIt)->Get(histname))->GetBinContent(i) );
		    
			}
				sort(ent.begin(), ent.end());
				reverse(ent.begin(), ent.end());
		

		((TH1D*)(*tfileIt)->Get(histname))->SetMinimum(0.2);
		((TH1D*)(*tfileIt)->Get(histname))->SetMaximum(ent[0]*1500 );
		
		//cout  << ent[0] << "................" <<  endl;
		
		it++;
	}
	
	gPad->RedrawAxis();


	if(legend==true) myLegend.Draw();
	TString filename = histname;
	

	myCanvas->cd()->SetRightMargin(0.04);


	TLatex *text1, *text2;

	text1 = new TLatex(3.570061,23.08044,"CMS Preliminary");
	text1->SetNDC();
	text1->SetTextAlign(13);
	text1->SetX(0.19);
	text1->SetY(0.92);
	//text1->SetLineWidth(2);
	text1->SetTextFont(72);
	text1->SetTextSizePixels(24);// dflt=28
	text1->Draw();

	text2 = new TLatex(3.570061,23.08044,"#intL dt = 4.7 fb^{-1} at #sqrt{s}=7 TeV");
	text2->SetNDC();
	text2->SetTextAlign(13);
	text2->SetX(0.19);
	text2->SetY(0.86);
	//text2->SetLineWidth(2);
	text2->SetTextFont(42);
	text2->SetTextSize(0.040);// dflt=28
	text2->Draw();


	
	gPad->Update();
	
	

	



	
	
	TString outFileName = "output.root";
	
	TFile* rootFile = new TFile(outFileName,"update");
	rootFile->cd();
	
	myCanvas->Write();
	myCanvas->SaveAs(dirname_+ filename+".eps");
	
	//myCanvas->SaveAs("/afs/fnal.gov/files/home/room2/vergili/public_html/ANALYSIS/MET/"+filename+".gif");

}


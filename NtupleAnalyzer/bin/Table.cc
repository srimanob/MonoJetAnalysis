// ROOT includes
#include <TStyle.h>
#include <TROOT.h>

// std includes
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include "TH1D.h"

#include <TString.h>
#include <TFile.h>
#include <math.h>
using namespace std;


const std::string outputDir = "";

int main(int argc, char ** argv)
{

	if ( argc < 3 ) {
		cerr << "Insufficient arguments: [histogram name] [options] [dataset1] [dataset2...]" << endl;
		return 1;
	}


	vector<double>  t, tbin;
	Double_t a1[45], a2[45];

	//cout << argc   <<  "  "  <<  argv[0] <<  "  "  << argv[1]<<  "  "  << endl;

	float selection;
	sscanf ( argv[2], "%f", &selection );

	for(int i=3; i<argc; i++  )
	{
		char file1[200];
		sprintf(file1,"%s.root" , argv[i] );
	
	
		string  histo = argv[1];
		
		TFile f1( file1 );
	
	
		TH1D*  histo1  = (TH1D*)f1.Get( histo.c_str() )->Clone();
		
	
		Int_t nbins1 = histo1->GetNbinsX() +2;
	
	
		double  t1=0.;
	
		for(int j=0; j<nbins1; j++  ){  t1= t1+ histo1->GetBinContent(j); }
	
		t.push_back(t1);

		for(int j=0; j<nbins1; j++  ){  tbin.push_back( histo1->GetBinContent(j) ) ; }
	

		
		if(selection!=6) continue; 
		
		if(i==4)
		{
			for(int k=0; k<45; k++ )
			{
				char his[100];

				sprintf(his,"PDF%d", k);

				TH1D*  histo1  = (TH1D*)f1.Get( his )->Clone();

				Int_t nbins1 = histo1->GetNbinsX() +2;

				Double_t  t1=0.;

				for(int j=0; j<nbins1; j++  ){  t1= t1+ histo1->GetBinContent(j); }

				a1[k]=t1;
			}
		}

		if(i==7)
		{
			
			for(int k=0; k<45; k++ )
			{
				char his[100];

				sprintf(his,"PDF%d", k);

				TH1D*  histo1  = (TH1D*)f1.Get( his )->Clone();

				Int_t nbins1 = histo1->GetNbinsX() +2;

				Double_t  t1=0.;

				for(int j=0; j<nbins1; j++  ){  t1= t1+ histo1->GetBinContent(j); }

				a2[k]=t1;
			}	
		}

	}
	//for cut efficiency
	if(selection==1.)
	{
	       printf( "|  %7.1f  |  %7.1f  |*%7.1f*",     t[1], t[1]-t[0] , (t[1]-t[0])*100./t[1] );		
	       printf( "|  %7.1f  |  %7.1f  |*%7.1f*",     t[3], t[3]-t[2] , (t[3]-t[2])*100./t[3] );
	       printf( "|  %7.1f  |  %7.1f  |*%7.1f*",     t[5], t[5]-t[4] , (t[5]-t[4])*100./t[5] );
	}
	//for data and background
	else if(selection==2.)
	{
	       printf( "| %7.1f | %7.1f | %7.1f | %7.1f | %7.1f | %7.1f | %7.1f |  %7.1f | ",     t[0], t[1], t[2] , t[3], t[4],t[5], t[0]+t[1]+t[2]+t[3]+t[4]+t[5] , t[6] );
	}
	//for data and background
	else if(selection==2.5)
	{
	       printf( "| %7.1f | %7.1f | %7.1f | %7.1f | %7.1f | %7.1f | %7.1f |  %7.1f | %7.1f | %7.1f |",     t[0], t[1], t[2] , t[3], t[4],t[5], t[0]+t[1]+t[2]+t[3]+t[4]+t[5] , t[6] , t[7] , t[8] , t[9] ) ;
	}
	else if(selection==2.6)
	{
	       printf( "|   %7.1f   |",   t[0] );
	}

	//for add
	else if(selection==3.)
	{  

	        printf( "| %6.1f | %6.1f | %6.1f | %6.1f | %6.1f | %6.1f |  %6.1f | %6.1f |  %6.1f |",     t[0], t[1], t[2] , t[3], t[4], t[5] , t[6] , t[7], t[8] );


	}
	//for unparticle
	else if(selection==4.)
	{

	    printf( "| %6.1f | %6.1f | %6.1f | %6.1f | %6.1f | %6.1f |  %6.1f | %6.1f |  %6.1f |   %6.1f | ",     t[0], t[1], t[2] , t[3], t[4], t[5] , t[6] , t[7], t[8], t[9] );


	}

	else if(selection==5.)
	{

	    printf( "| %6.2f | %6.2f | %6.2f |  ",     tbin[2], tbin[3], tbin[2]+tbin[3] );


	}

	else if(selection==6.)
	{
	  
	    
		Double_t  tds=0, tdsp=0 , tdsm=0; 

		//cout <<  "  0"   <<  "  "  << a1[0] <<  "  "  <<  a2[0]  <<    "  "  <<  a2[0]/a1[0]  <<  endl;

		for(size_t i=1; i<42; i+=2 )
		{


			double_t ds  =  (a2[i]/a1[i] -  a2[i+1]/a1[i+1]  ) / 2.; 
			
			Double_t dsp =  a2[i]/a1[i]  -  a2[0]/a1[0] ;

			Double_t dsm =  a2[0]/a1[0]  -  a2[i+1]/a1[i+1];

			tds = tds +  (ds*ds);

			tdsp = tdsp +  (dsp*dsp);
			tdsm = tdsm +  (dsm*dsm);


			//cout <<  "  +" << (i+1)/2  <<  "  "   << a1[i] <<  "  "  <<  a2[i]     <<  "  " <<  a2[i]/a1[i]   <<  "  ..." <<   a2[0]/a1[0] << endl;
			//cout <<  "  -" << (i+1)/2  <<  "  "   << a1[i+1] <<  "  "  <<  a2[i+1]  <<  "  " <<  a2[i+1]/a1[i+1]   <<endl;
			
			//cout <<  "" << i <<  "  " <<  ds <<  "  "<< dsp   <<  "  "  <<  dsm  << endl<< endl;
		
			//cout <<  ds << endl;
		}
		  
		//cout  << " avarage: "  <<  sqrt(tds)  <<  "   +" <<  sqrt(tdsp)  <<  "   -" <<  sqrt(tdsm)   <<  "   -+" <<  (sqrt(tdsm)+  sqrt(tdsp)) /2 <<   endl;
		      
		double  acc = t[4]*100/t[1];
		
		double  jesm = (t[4]- t[3])*100 / t[4];
		double  jesp = (t[5] - t[4])*100 / t[4];
		
		double  pdfm = sqrt(tdsm)*100 / ( t[4]/t[1])  ; 
		double  pdfp = sqrt(tdsp)*100 / ( t[4]/t[1])  ; 
		
		double  totm = sqrt( jesm*jesm + pdfm*pdfm );
		double  totp = sqrt( jesp*jesp + pdfp*pdfp );
		
		
		printf( "| %6.3f | -%6.3f / +%6.3f | -%6.3f / +%6.3f | -%6.3f / +%6.3f |",  acc , jesm, jesp , pdfm ,pdfp  , totm, totp  );      
		
	}
}



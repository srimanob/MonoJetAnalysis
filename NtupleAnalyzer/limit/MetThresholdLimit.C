{
	//Settings:
	gROOT->Reset();
	gROOT->ProcessLine(".L ../bin/tdrStyle.C");
	gROOT->ProcessLine("setTDRStyle()");
	
	TLatex l; l.SetTextSize(0.05);
	TCanvas *c1 = new TCanvas("Expected Limits", "Expected Limits");
	c1->SetGrid();


	
	TFile f1("rootfiles/data_limit.root");
	TH1D*  data = (TH1D*) f1.Get("MetMuThrs1")->Clone();


	TFile f21("rootfiles/ttbar_limit.root");
	TH1D*  ttbar = (TH1D*) f21.Get("MetMuThrs1")->Clone();

	TFile f22("rootfiles/zjets_limit.root");
	TH1D*  zjets = (TH1D*) f22.Get("MetMuThrs1")->Clone();

	TFile f23("rootfiles/tsingle_limit.root");
	TH1D*  tsingle = (TH1D*) f23.Get("MetMuThrs1")->Clone();

	TFile f24("rootfiles/qcd_limit.root");
	TH1D*  qcd  = (TH1D*) f24.Get("MetMuThrs1")->Clone();


	TFile f31("rootfiles/signal_limit_0.root");
	TH1D*  signal0 = (TH1D*) f31.Get("MetMu1")->Clone();

	TFile f32("rootfiles/signal_limit_8.root");
	TH1D*  signal8 = (TH1D*) f32.Get("MetMuThrs1")->Clone();



	///Zinv

	TFile f4("rootfiles/zinv_limit.root");
	TH1D*  zinv = (TH1D*) f4.Get("MetMuThrs1")->Clone();

	TFile f41("rootfiles/AnaZDATA.root");
	TH1D*  zmumuDATA = (TH1D*) f41.Get("MetMuThrs1")->Clone();

	TFile f42("rootfiles/AnaZMC.root");
	TH1D*  zmumuMC    = (TH1D*) f42.Get("MetMuThrs1")->Clone();
	TH1D*  zmumuMCmet = (TH1D*) f42.Get("MetMu1")->Clone();

	TFile f43("rootfiles/AnaZMC_ttbar.root");
	TH1D*  zmumu_ttbar = (TH1D*) f43.Get("MetMuThrs1")->Clone();

	TFile f44("rootfiles/AnaZMC_tsingle.root");
	TH1D*  zmumu_tsingle = (TH1D*) f44.Get("MetMuThrs1")->Clone();


	///Wjets

	TFile f5("rootfiles/wjets_limit.root");
	TH1D*  wjets = (TH1D*) f5.Get("MetMuThrs1")->Clone();

	TFile f51("rootfiles/AnaWDATA.root");
	TH1D*  wmunuDATA = (TH1D*) f51.Get("MetMuThrs1")->Clone();

	TFile f52("rootfiles/AnaWMC.root");
	TH1D*  wmunuMC    = (TH1D*) f52.Get("MetMuThrs1")->Clone();
	TH1D*  wmunuMCmet = (TH1D*) f52.Get("MetMu1")->Clone();

	TFile f53("rootfiles/AnaWMC_ttbar.root");
	TH1D*  wmunu_ttbar = (TH1D*) f53.Get("MetMuThrs1")->Clone();

	TFile f54("rootfiles/AnaWMC_tsingle.root");
	TH1D*  wmunu_tsingle = (TH1D*) f54.Get("MetMuThrs1")->Clone();


	Int_t nbins = data->GetNbinsX()+1 ;

	///------------------- Z Error ----------------------------------------------------------

	double Zerr[40], ZBin[40]; 

	
	double  normZ =   zmumuMCmet->GetEntries() / zmumuMC->GetBinContent(1);

	for(int i=1; i<nbins; i++)
	{

		if(zmumuDATA->GetBinContent(i) == 0 )
			double ZstatData  = 0.0000001; 
		else
			double ZstatData  = 1./ sqrt( zmumuDATA->GetBinContent(i) );	


		if(zmumuMC->GetBinContent(i) == 0 )
			double ZstatMC    = 0.0000001;
		else
			double ZstatMC    = 1./ sqrt( zmumuMC->GetBinContent(i)*normZ );

		if(zmumu_ttbar->GetBinContent(i) == 0 )
			double Zstat_ttbar    = 0.0000001;
		else
			double Zstat_ttbar    = zmumu_ttbar->GetBinContent(i) / zmumuMC->GetBinContent(i) ;

		if(zmumu_tsingle->GetBinContent(i) == 0 )
			double Zstat_tsingle    = 0.0000001;
		else
			double Zstat_tsingle    =zmumu_tsingle->GetBinContent(i) / zmumuMC->GetBinContent(i)  ;


		double  Zacc = 0.03;
		
		Zerr[i] = sqrt( ZstatData*ZstatData + ZstatMC*ZstatMC + Zacc*Zacc + Zstat_ttbar*Zstat_ttbar + Zstat_tsingle*Zstat_tsingle ); 
 		
		ZBin[i] = zinv->GetBinContent(i);  


	}

	///------------------- W Error ----------------------------------------------------------


	double  normW =   wmunuMCmet->GetEntries() / wmunuMC->GetBinContent(1);

	double Werr[40], WBin[40];

	for(int i=1; i<nbins; i++)
	{

		if(wmunuDATA->GetBinContent(i) == 0 )
			double WstatData  = 0.0000001; 
		else
			double WstatData  = 1./ sqrt( wmunuDATA->GetBinContent(i) );	


		if(wmunuMC->GetBinContent(i) == 0 )
			double WstatMC    = 0.0000001;
		else
			double WstatMC    = 1./ sqrt( wmunuMC->GetBinContent(i)*1.579 );


		if(wmunu_ttbar->GetBinContent(i) == 0 )
			double Wstat_ttbar    = 0.0000001;
		else
			double Wstat_ttbar    =  wmunu_ttbar->GetBinContent(i) / wmunuMC->GetBinContent(i);

		if(wmunu_tsingle->GetBinContent(i) == 0 )
			double Wstat_tsingle    = 0.0000001;
		else
			double Wstat_tsingle    =  wmunu_tsingle->GetBinContent(i) / wmunuMC->GetBinContent(i) ;

		
		cout << "W data: " <<  WstatData << " mc:"  <<  WstatMC <<  " ttbar:" << Wstat_ttbar<<  " tsingle:" << Wstat_tsingle<< endl; 

		double Wacc = 0.02;
		
		Werr[i] = sqrt( WstatData*WstatData + WstatMC*WstatMC + Wacc*Wacc  +Wstat_ttbar*Wstat_ttbar + Wstat_tsingle*Wstat_tsingle ); 
 		
		WBin[i] =  wjets->GetBinContent(i);  

		//cout << "data:" << WstatData  <<  " mc:" << WstatMC ;
		//cout << "ttbar:" << wmunu_ttbar->GetBinContent(i)  <<  " tsingle:" <<  wmunu_tsingle->GetBinContent(i)  << endl;



	}

	///--------------Other Bck--------------------------------------------------


	double dataBin[40], mcBin[40], signalBin[40], zjetsBin[40] , ttbarBin[40], tsingleBin[40] , qcdBin[40];


	for(int i=1; i<nbins; i++)
	{

		dataBin[i]     = data->GetBinContent(i);
		
		ttbarBin[i]    = ttbar->GetBinContent(i);
		tsingleBin[i]  = tsingle->GetBinContent(i);
		zjetsBin[i]    = zjets->GetBinContent(i);
		qcdBin[i]      = qcd->GetBinContent(i);
		
		
		mcBin[i]       = zinv->GetBinContent(i) + wjets->GetBinContent(i) + ttbar->GetBinContent(i) +
                         zjets->GetBinContent(i) + tsingle->GetBinContent(i) +  qcd->GetBinContent(i);


		signalBin[i]   = signal8->GetBinContent(i);
	}


	double signalTot=0; 

	for(int i=0; i<nbins; i++)
	{
		signalTot= signalTot + signal0->GetBinContent(i);
	}



	double  lumi = 1146.; 
	double  lumierr = 4.5;  //percentage
	double deneme[40];
	double BckErr[40];
	double METThreshold[40]; 

	for(int i=8; i<nbins-16; i++)
	{

								 
		//deneme = roostats_clm(1092, 66, 0.04847, 0.004847,  1724, 73, 1 ,1 ); 

		BckErr[i] = sqrt(   pow(Zerr[1]*ZBin[i], 2)    +  pow(Werr[1]*WBin[i],2) 
						   +pow( zjetsBin[i], 2) + pow( tsingleBin[i], 2) + pow( ttbarBin[i], 2) + pow( qcdBin[i], 2)    );

	
			//deneme[i] = roostats_cl95(lumi, lumi*lumierr/100. , signalBin[i]/signalTot, signalBin[i]/signalTot/10., mcBin[i],
			//sqrt(pow(BckErr[i],2) + dataBin[i] + pow(mcBin[i]*0.042 ,2) )  , mcBin[i], gauss=false, nuisanceModel=1, "bayesian" , "");
		

			//deneme[i] = roostats_cl95(lumi, lumi*lumierr/100. , signalBin[i]/signalTot, signalBin[i]/signalTot/7.5, mcBin[i],
			//sqrt(pow(BckErr[i],2) + dataBin[i] + mcBin[i]*0.03 )  , mcBin[i], gauss=false, nuisanceModel=1, "bayesian" , "");
		

		cout <<  signalBin[i]  << endl ;
		cout <<  mcBin[i]  << endl ;

		METThreshold[i] = i*25. -25. ;

	
	}

	for(int i=8; i<nbins-16; i++)
	{

        cout << i*25.-25. << " WErr:" << WBin[i]*Werr[i]  <<  "  ZErr: " << ZBin[i]*Zerr[i]  <<  "  bck Err: " <<  sqrt(pow(BckErr[i],2) + dataBin[i] + pow(mcBin[i]*0.042,2) )  <<   "  my limit....................." <<deneme[i] << endl; 

		
	
	}





}

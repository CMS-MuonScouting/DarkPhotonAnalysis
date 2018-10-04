#include <iostream>
#include <TLegend.h>
#include <sstream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include "TH1D.h"
#include "TH2D.h"
#include <THStack.h>
#include "TProfile.h"
#include "TGraph.h"
#include "TFile.h"
#include "TTree.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TFractionFitter.h"
#include <string>
#include <vector>
#include <math.h>
#include <TLatex.h>
#include <TLine.h>
#include <TMarker.h>
#include <TPave.h>
#include <TPaveStats.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <TString.h>
#include "TGraphErrors.h"
#include "TF1.h"


#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>




#include <RooPlot.h>
#include <RooArgSet.h>
#include <RooArgList.h>
#include <RooDataSet.h>
#include <RooDataHist.h>
#include <RooGaussian.h>
#include <RooPolynomial.h>
#include <RooRealVar.h> 
#include <RooFormulaVar.h> 
#include <RooWorkspace.h> 
#include <RooMsgService.h> 


using namespace std;

void makeCardsAndWS(){
  
  //WHICH YEAR
  	TString year="2018";
  //INPUT FILE WITH HISTOGRAMS TO FIT BACKGROUND
  	TFile* file=TFile::Open("/eos/cms/store/group/phys_exotica/darkPhoton/jakob/"+year+"/mergedForCards"+year+".root");

  //PREPARE EXPECTED NUMBER OF SIGNAL EVENTS PER CATEGORY
	//X-SECTION GRAPH
	double m[14] 		= {10,12.5,15,20,30,40,50,60,100,120,140,160,180,200};
	double xSec[14] 	= {131.1,83.82,57.87,31.39,12.75,6.624,4.033,2.796,2.62,0.47,0.2473,0.1585,0.1089,0.07896};//[pb]
	TGraph* xsecgraph 	= new TGraph(14,m,xSec);
	double acceptances[3] 	= {0.18,0.117,0.468}; 
	//LUMINOSITY
	double luminosity = 35000.;//pb-1
	//EFFICIENCY
	double eff = 0.7;// to be updated
	
	//scale
	double eps2scale = 0.0001; // this scales the cross section eps=0.02->0.002 or eps2=10^(-6)

	//*****----->>>>> nSignal = xsecgraph->Eval(mass)*eff*luminosity*acceptances[i]

   //LOOP OVER MASS INDICES AND MAKE THE CARDS/WORKSPACES
	double mass = 10.;
	for(int i=0; i<300; i++){


	  if(i<90. || i>112.) continue;
	  	//get the histograms
	  	TH1D* catA=(TH1D*)file->Get(Form("massforLimit_CatA%d",i));
	  	TH1D* catB=(TH1D*)file->Get(Form("massforLimit_CatB%d",i));
	  	TH1D* catC=(TH1D*)file->Get(Form("massforLimit_CatC%d",i));
	  	double massLow  =  catA->GetXaxis()->GetXmin();
      		double massHigh =  catA->GetXaxis()->GetXmax();
	  

		//compute mass point and define ROOFit variables
	  	mass = mass+(mass*0.01);
		RooRealVar MH    ("MH"       	, "MH"          , mass);	
		RooRealVar resA  ("resA"  	, "RFes. unc. " , mass*0.007);//to be checked
		RooRealVar resB  ("resB"  	, "RFes. unc. " , mass*0.01);//to be checked
		RooRealVar resC  ("resC"  	, "RFes. unc. " , mass*0.014);// to be checked
		RooRealVar m2mu  ("m2mu"  	, "m2mu " 	, massLow		, massHigh);

		//define the signal model
		RooGaussian signalModel_CatA("signalModel_CatA"	, "signalModel_CatA"		, m2mu		      ,MH	,resA);
		RooGaussian signalModel_CatB("signalModel_CatB"	, "signalModel_CatB"		, m2mu		      ,MH	,resB);
		RooGaussian signalModel_CatC("signalModel_CatC"	, "signalModel_CatC"		, m2mu		      ,MH	,resC);
		//cout<<signalModel_CatA.Integral()<<endl;
		//define data_obs, i.e. observed ROOPDF
		RooDataHist data_obs_CatA("data_obs_CatA", "", RooArgList(m2mu), catA);
		RooDataHist data_obs_CatB("data_obs_CatB", "", RooArgList(m2mu), catB);
		RooDataHist data_obs_CatC("data_obs_CatC", "", RooArgList(m2mu), catC);

		//fit and get the background PDF
		TF1 *bkfit = new TF1("bkfit","pol3",massLow,massHigh);
		catA->Fit(bkfit);
		RooRealVar a0a("a0a","a0a",bkfit->GetParameter(0));//,bkfit->GetParameter(0)*0.1,bkfit->GetParameter(0)*2.) ;
      		RooRealVar a1a("a1a","a1a",bkfit->GetParameter(1));//,bkfit->GetParameter(1)*0.1,bkfit->GetParameter(1)*2.);
      		RooRealVar a2a("a2a","a2a",bkfit->GetParameter(2));//,bkfit->GetParameter(2)*0.1,bkfit->GetParameter(2)*2.) ;
      		RooRealVar a3a("a3a","a3a",bkfit->GetParameter(3));//,bkfit->GetParameter(3)*0.1,bkfit->GetParameter(3)*2.) ;
		RooPolynomial bkg_mass_CatA("bkg_mass_CatA","bkg_mass_CatA",m2mu,RooArgList(a0a,a1a,a2a,a3a),0);
		catB->Fit(bkfit);
		RooRealVar a0b("a0b","a0b",bkfit->GetParameter(0));//,bkfit->GetParameter(0)*0.1,bkfit->GetParameter(0)*2.) ;
      		RooRealVar a1b("a1b","a1b",bkfit->GetParameter(1));//,bkfit->GetParameter(1)*0.1,bkfit->GetParameter(1)*2.);
      		RooRealVar a2b("a2b","a2b",bkfit->GetParameter(2));//,bkfit->GetParameter(2)*0.1,bkfit->GetParameter(2)*2.) ;
      		RooRealVar a3b("a3b","a3b",bkfit->GetParameter(3));//,bkfit->GetParameter(3)*0.1,bkfit->GetParameter(3)*2.) ;
		RooPolynomial bkg_mass_CatB("bkg_mass_CatB","bkg_mass_CatB",m2mu,RooArgList(a0b,a1b,a2b,a3b),0);
		catC->Fit(bkfit);
		RooRealVar a0c("a0c","a0c",bkfit->GetParameter(0));//,bkfit->GetParameter(0)*0.1,bkfit->GetParameter(0)*2.) ;
      		RooRealVar a1c("a1c","a1c",bkfit->GetParameter(1));//,bkfit->GetParameter(1)*0.1,bkfit->GetParameter(1)*2.);
      		RooRealVar a2c("a2c","a2c",bkfit->GetParameter(2));//,bkfit->GetParameter(2)*0.1,bkfit->GetParameter(2)*2.) ;
      		RooRealVar a3c("a3c","a3c",bkfit->GetParameter(3));//,bkfit->GetParameter(3)*0.1,bkfit->GetParameter(3)*2.) ;
		RooPolynomial bkg_mass_CatC("bkg_mass_CatC","bkg_mass_CatC",m2mu,RooArgList(a0c,a1c,a2c,a3c),0);
		
		//save into ROO workspace
		RooWorkspace dpworkspace("dpworkspace", "");
      		dpworkspace.import(data_obs_CatA);
		dpworkspace.import(data_obs_CatB);
		dpworkspace.import(data_obs_CatC);
      		dpworkspace.import(signalModel_CatA);
		dpworkspace.import(signalModel_CatB);
		dpworkspace.import(signalModel_CatC);
      		dpworkspace.import(bkg_mass_CatA);
		dpworkspace.import(bkg_mass_CatB);
		dpworkspace.import(bkg_mass_CatC);
      		dpworkspace.writeToFile(Form("dpWorkspace"+year+"_%d.root",i));

		//write the datacard
		char inputShape[200];
      		sprintf(inputShape,"dpCard%d.txt",i);
      		ofstream newcardShape;
      		newcardShape.open(inputShape);
      		newcardShape << Form("imax 3 number of channels\n");
      		newcardShape << Form("jmax * number of background\n");
      		newcardShape << Form("kmax * number of nuisance parameters\n");
		newcardShape << Form("shapes data_obs 		CatA dpWorkspace"+year+"_%d.root dpworkspace:data_obs_CatA	\n",i);
		newcardShape << Form("shapes bkg_mass 		CatA dpWorkspace"+year+"_%d.root dpworkspace:bkg_mass_CatA	\n",i);
		newcardShape << Form("shapes signalModel 	CatA dpWorkspace"+year+"_%d.root dpworkspace:signalModel_CatA	\n",i);
		newcardShape << Form("shapes data_obs 		CatB dpWorkspace"+year+"_%d.root dpworkspace:data_obs_CatB	\n",i);
		newcardShape << Form("shapes bkg_mass 		CatB dpWorkspace"+year+"_%d.root dpworkspace:bkg_mass_CatB	\n",i);
		newcardShape << Form("shapes signalModel 	CatB dpWorkspace"+year+"_%d.root dpworkspace:signalModel_CatB	\n",i);
		newcardShape << Form("shapes data_obs 		CatC dpWorkspace"+year+"_%d.root dpworkspace:data_obs_CatC	\n",i);
		newcardShape << Form("shapes bkg_mass 		CatC dpWorkspace"+year+"_%d.root dpworkspace:bkg_mass_CatC	\n",i);
		newcardShape << Form("shapes signalModel 	CatC dpWorkspace"+year+"_%d.root dpworkspace:signalModel_CatC	\n",i);
      		newcardShape << Form("bin		CatA 	CatB	CatC\n");
      		newcardShape << Form("observation 	-1.0	-1.0	-1.0\n");
      		newcardShape << Form("bin     		CatA		CatA		CatB 		CatB		CatC		CatC	\n");
      		newcardShape << Form("process 		signalModel  	bkg_mass	signalModel  	bkg_mass	signalModel  	bkg_mass\n");
      		newcardShape << Form("process 		0    		1		0		1		0		1   	\n");
      		newcardShape << Form("rate    		%f  		1.0		%f  		1.0		%f  		1	\n",eps2scale*xsecgraph->Eval(mass)*eff*luminosity*acceptances[0],eps2scale*xsecgraph->Eval(mass)*eff*luminosity*acceptances[1],eps2scale*xsecgraph->Eval(mass)*eff*luminosity*acceptances[2]);
		newcardShape.close();
		
	}




}

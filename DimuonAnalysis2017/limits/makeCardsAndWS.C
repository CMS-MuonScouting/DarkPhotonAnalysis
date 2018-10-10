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

void makeCardsAndWStest(){
  

  TH1F* histChi2_A=new TH1F("histChi2_A","histChi2_A",50,0.5,1.5);
  TH1F* histChi2_B=new TH1F("histChi2_B","histChi2_B",50,0.5,1.5);
  TH1F* histChi2_C=new TH1F("histChi2_C","histChi2_C",50,0.5,1.5);


  //WHICH YEAR
  	TString year="2017";
	TString suff="IterV3";
  //INPUT FILE WITH HISTOGRAMS TO FIT BACKGROUND
  	TFile* file=TFile::Open("/eos/cms/store/group/phys_exotica/darkPhoton/jakob/"+year+"/mergedForCards"+year+".root");

  //PREPARE EXPECTED NUMBER OF SIGNAL EVENTS PER CATEGORY
	//X-SECTION GRAPH
	double m[14] 		= {10,12.5,15,20,30,40,50,60,120,140,160,180,200};
	double xSec[14] 	= {131.1,83.82,57.87,31.39,12.75,6.624,4.033,2.796,0.47,0.2473,0.1585,0.1089,0.07896};//[pb]
	TGraph* xsecgraph 	= new TGraph(14,m,xSec);
	double acceptances[3] 	= {0.18,0.117,0.468}; 
	//LUMINOSITY
	double luminosity = 35000.;//pb-1
	//EFFICIENCY
	double me[7] 		= {12.5,15,20,30,50,70,200};
	double effA[7] = {0.29,0.40,0.49,0.60,0.71,0.75,0.80};// to be updated
	double effB[7] = {0.24,0.35,0.48,0.57,0.70,0.76,0.80};
	double effC[7] = {0.26,0.33,0.41,0.50,0.61,0.68,0.80};
	TGraph* effAgraph 	= new TGraph(7,me,effA);
	TGraph* effBgraph 	= new TGraph(7,me,effB);
	TGraph* effCgraph 	= new TGraph(7,me,effC);
	
	effAgraph->SaveAs("effAgraph.root");
	effBgraph->SaveAs("effBgraph.root");
	effCgraph->SaveAs("effCgraph.root");
	xsecgraph->SaveAs("xsecgraph.root");

	
	//scale
	double eps2scale = 5*0.0001; // this scales the cross section eps=0.02->0.0002 or eps2=10^(-8)

	//*****----->>>>> nSignal = xsecgraph->Eval(mass)*eff*luminosity*acceptances[i]

   //LOOP OVER MASS INDICES AND MAKE THE CARDS/WORKSPACES
	double mass = 10.;
	for(int i=0; i<300; i++){

	  
	  
	  	//get the histograms
	  	TH1D* catA=(TH1D*)file->Get(Form("massforLimit_CatA%d",i));
	  	TH1D* catB=(TH1D*)file->Get(Form("massforLimit_CatB%d",i));
	  	TH1D* catC=(TH1D*)file->Get(Form("massforLimit_CatC%d",i));
	  	double massLow  =  catA->GetXaxis()->GetXmin();
      		double massHigh =  catA->GetXaxis()->GetXmax();
	  

		//compute mass point and define ROOFit variables
	  	mass = mass+(mass*0.01);
		//cout<<"Spline: "<<effAgraph->Eval(mass,0,"S")<<endl;
		//cout<<"Graph : "<<effAgraph->Eval(mass)<<endl;
		RooRealVar MH    ("MH"       	, "MH"          , mass);	
		RooRealVar resA  ("resA"  	, "RFes. unc. " , mass*0.01);//to be checked
		RooRealVar resB  ("resB"  	, "RFes. unc. " , mass*0.013);//to be checked
		RooRealVar resC  ("resC"  	, "RFes. unc. " , mass*0.02);// to be checked
		RooRealVar m2mu  ("m2mu"  	, "m2mu " 	, massLow		, massHigh);

		//define the signal model
		RooGaussian signalModel_CatA("signalModel_CatA"	, "signalModel_CatA"		, m2mu		      ,MH	,resA);
		RooGaussian signalModel_CatB("signalModel_CatB"	, "signalModel_CatB"		, m2mu		      ,MH	,resB);
		RooGaussian signalModel_CatC("signalModel_CatC"	, "signalModel_CatC"		, m2mu		      ,MH	,resC);
		RooDataHist data_obs_CatA("data_obs_CatA", "", RooArgList(m2mu), catA);
		RooDataHist data_obs_CatB("data_obs_CatB", "", RooArgList(m2mu), catB);
		RooDataHist data_obs_CatC("data_obs_CatC", "", RooArgList(m2mu), catC);
		RooRealVar bkg_norm("bkg_norm", "",catA->Integral());
		RooRealVar bkg_norm_CatB("bkg_norm_CatB", "",catB->Integral());
		RooRealVar bkg_norm_CatC("bkg_norm_CatC", "",catC->Integral());

		//fit and get the background PDF
		TF1 *bkfit = new TF1("bkfit","pol3",massLow,massHigh);
		catA->Fit(bkfit);
		//TCanvas * catAc = new TCanvas("catAc", "catAc", 500, 500);
		//catA->Draw();
		//catAc->SaveAs(Form("catA%d"+year+".png",i));
		if(i>24. && (i<200. || i>240.)) {histChi2_A->Fill(bkfit->GetChisquare()/bkfit->GetNDF());}
		RooRealVar a0a("a0a","a0a",bkfit->GetParameter(0),(bkfit->GetParameter(0)-bkfit->GetParError(0)*5.),(bkfit->GetParameter(0)+bkfit->GetParError(0)*5.));
		RooRealVar a1a("a1a","a1a",bkfit->GetParameter(1),(bkfit->GetParameter(1)-bkfit->GetParError(1)*5.),(bkfit->GetParameter(1)+bkfit->GetParError(1)*5.));
      		RooRealVar a2a("a2a","a2a",bkfit->GetParameter(2),(bkfit->GetParameter(2)-bkfit->GetParError(2)*5.),(bkfit->GetParameter(2)+bkfit->GetParError(2)*5.));
		RooRealVar a3a("a3a","a3a",bkfit->GetParameter(3),(bkfit->GetParameter(3)-bkfit->GetParError(3)*5.),(bkfit->GetParameter(3)+bkfit->GetParError(3)*5.));
		RooPolynomial bkg_mass_CatA("bkg_mass_CatA","bkg_mass_CatA",m2mu,RooArgList(a0a,a1a,a2a,a3a),0);
		catB->Fit(bkfit);
		//TCanvas * catBc = new TCanvas("catBc", "catBc", 500, 500);
		//catB->Draw();
		//catBc->SaveAs(Form("catB%d"+year+".png",i));
		if(i>24. && (i<200. || i>240.)) {histChi2_B->Fill(bkfit->GetChisquare()/bkfit->GetNDF());}
		RooRealVar a0b("a0b","a0a",bkfit->GetParameter(0),(bkfit->GetParameter(0)-bkfit->GetParError(0)*5.),(bkfit->GetParameter(0)+bkfit->GetParError(0)*5.));
		RooRealVar a1b("a1b","a1b",bkfit->GetParameter(1),(bkfit->GetParameter(1)-bkfit->GetParError(1)*5.),(bkfit->GetParameter(1)+bkfit->GetParError(1)*5.));
		RooRealVar a2b("a2b","a2b",bkfit->GetParameter(2),(bkfit->GetParameter(2)-bkfit->GetParError(2)*5.),(bkfit->GetParameter(2)+bkfit->GetParError(2)*5.));
		RooRealVar a3b("a3b","a3b",bkfit->GetParameter(3),(bkfit->GetParameter(3)-bkfit->GetParError(3)*5.),(bkfit->GetParameter(3)+bkfit->GetParError(3)*5.));
		RooPolynomial bkg_mass_CatB("bkg_mass_CatB","bkg_mass_CatB",m2mu,RooArgList(a0b,a1b,a2b,a3b),0);
		catC->Fit(bkfit);
		//TCanvas * catCc = new TCanvas("catCc", "catCc", 500, 500);
		//catC->Draw();
		//catCc->SaveAs(Form("catC%d"+year+".png",i));
		if(i>24. && (i<200. || i>240.)) {histChi2_C->Fill(bkfit->GetChisquare()/bkfit->GetNDF());}
		RooRealVar a0c("a0c","a0c",bkfit->GetParameter(0),(bkfit->GetParameter(0)-bkfit->GetParError(0)*5.),(bkfit->GetParameter(0)+bkfit->GetParError(0)*5.));
	        RooRealVar a1c("a1c","a1c",bkfit->GetParameter(1),(bkfit->GetParameter(1)-bkfit->GetParError(1)*5.),(bkfit->GetParameter(1)+bkfit->GetParError(1)*5.));
	        RooRealVar a2c("a2c","a2c",bkfit->GetParameter(2),(bkfit->GetParameter(2)-bkfit->GetParError(2)*5.),(bkfit->GetParameter(2)+bkfit->GetParError(2)*5.));
	        RooRealVar a3c("a3c","a3c",bkfit->GetParameter(3),(bkfit->GetParameter(3)-bkfit->GetParError(3)*5.),(bkfit->GetParameter(3)+bkfit->GetParError(3)*5.));
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
      		dpworkspace.writeToFile(Form("dpWorkspace"+year+suff+"_%d.root",i));

		//write the datacard
		char inputShape[200];
      		sprintf(inputShape,"dpCard_"+year+suff+"_%d.txt",i);
      		ofstream newcardShape;
      		newcardShape.open(inputShape);
      		newcardShape << Form("imax 3 number of channels\n");
      		newcardShape << Form("jmax * number of background\n");
      		newcardShape << Form("kmax * number of nuisance parameters\n");
		newcardShape << Form("shapes data_obs	CatA dpWorkspace"+year+suff+"_%d.root dpworkspace:data_obs_CatA\n",i);
		newcardShape << Form("shapes bkg_mass	CatA dpWorkspace"+year+suff+"_%d.root dpworkspace:bkg_mass_CatA\n",i);
		newcardShape << Form("shapes signalModel	CatA dpWorkspace"+year+suff+"_%d.root dpworkspace:signalModel_CatA\n",i);
		newcardShape << Form("shapes data_obs	CatB dpWorkspace"+year+suff+"_%d.root dpworkspace:data_obs_CatB\n",i);
		newcardShape << Form("shapes bkg_mass	CatB dpWorkspace"+year+suff+"_%d.root dpworkspace:bkg_mass_CatB	\n",i);
		newcardShape << Form("shapes signalModel 	CatB dpWorkspace"+year+suff+"_%d.root dpworkspace:signalModel_CatB	\n",i);
		newcardShape << Form("shapes data_obs	CatC dpWorkspace"+year+suff+"_%d.root dpworkspace:data_obs_CatC	\n",i);
		newcardShape << Form("shapes bkg_mass	CatC dpWorkspace"+year+suff+"_%d.root dpworkspace:bkg_mass_CatC	\n",i);
		newcardShape << Form("shapes signalModel 	CatC dpWorkspace"+year+suff+"_%d.root dpworkspace:signalModel_CatC	\n",i);
      		newcardShape << Form("bin		CatA 	CatB	CatC\n");
      		newcardShape << Form("observation 	-1.0	-1.0	-1.0\n");
      		newcardShape << Form("bin     		CatA		CatA		CatB 		CatB		CatC		CatC	\n");
      		newcardShape << Form("process 		signalModel  	bkg_mass	signalModel  	bkg_mass	signalModel  	bkg_mass\n");
      		newcardShape << Form("process 		0    		1		0		1		0		1   	\n");
      		newcardShape << Form("rate    		%f  		%d		%f  		%d		%f  		%d	\n",
				     eps2scale*xsecgraph->Eval(mass,0,"S")*effAgraph->Eval(mass,0,"S")*luminosity*acceptances[0],
		1,
				     eps2scale*xsecgraph->Eval(mass,0,"S")*effBgraph->Eval(mass,0,"S")*luminosity*acceptances[1],
		1,
				     eps2scale*xsecgraph->Eval(mass,0,"S")*effCgraph->Eval(mass,0,"S")*luminosity*acceptances[2],
		1);
		newcardShape << Form("lumi13TeV_2017 lnN 	1.023 	-	1.023	-	1.023	-\n");
		newcardShape << Form("eff_mu_13TeV_2017 lnN	1.015 	-	1.015	-	1.015	-\n");
		newcardShape << Form("bkg_norm_cata rateParam CatA bkg_mass %f\n",catA->Integral());
		newcardShape << Form("bkg_norm_catb rateParam CatB bkg_mass %f\n",catB->Integral());
		newcardShape << Form("bkg_norm_catc rateParam CatC bkg_mass %f\n",catC->Integral());
		newcardShape << Form("resA param %f %f\n",resA.getValV(),resA.getValV()*0.1);
		newcardShape << Form("resB param %f %f\n",resB.getValV(),resB.getValV()*0.1);
		newcardShape << Form("resC param %f %f\n",resC.getValV(),resC.getValV()*0.1);
		newcardShape.close();
		
	}
	histChi2_A->SaveAs("histAchi2_"+year+".root");
	histChi2_B->SaveAs("histBchi2_"+year+".root");
	histChi2_C->SaveAs("histCchi2_"+year+".root");

}

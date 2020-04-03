//#include "sumwgt.h"
#include "TFileCollection.h"
#include "TChain.h"
#include "TFile.h"
#include <TTreeReader.h>
#include "TH1D.h"
#include "TH2D.h"
#include <TTreeReaderValue.h>
#include "TLorentzVector.h"

void trimscoutMakeTheCardsxyz18(string treepath = 
			      // "/eos/cms/store/group/phys_exotica/darkPhoton/jakob/2017/ScoutingCaloMuon/crab_20181106_233051/181106_223103/0000/meregd3344.root"
			      // "/eos/cms/store/group/phys_exotica/darkPhoton/jakob/2017/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_20181123_123249/181123_113300/0000/merged7.root"
			      //  "/eos/cms/store/group/phys_exotica/darkPhoton/jakob/2017/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_20181123_123130/181123_113244/0000/merged4.root"
			      //"/eos/cms/store/group/phys_exotica/darkPhoton/jakob/2017/DarkPhoton/crab_20181202_190451/181202_180503/0000/scout_1.root"
			      //	      "/eos/cms/store/group/phys_exotica/darkPhoton/jakob/2017/DarkPhoton/crab_20181123_123303/181123_113315/0000/scout_1.root"
			      //			      "/eos/cms/store/group/phys_exotica/darkPhoton/jakob/2018/XDYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_20190702_110617/190702_090625/0000/x8x8x8x.root"
				"/eos/cms/store/group/phys_exotica/darkPhoton/jakob/2017/ScoutingRunF/ScoutingCaloMuon/crab_20181212_141737/181212_131744/0000/merge5star.root"
			      //"/eos/cms/store/group/phys_exotica/darkPhoton/jakob/2018/ScoutingCaloMuon/crab_20180905_214655/180905_194708/0000/scout_93.root"
, const char* outfilename = "./scoutData4Muonsx.root", bool isMC=false) {
 
   vector<string> filesToRun;
   vector<bool> isData;
   
   filesToRun.push_back(treepath);isData.push_back(true);
   TFile* outfile = new TFile(outfilename, "RECREATE");
   TTree* outtree = new TTree("tree", "tree");
     

    TH1D* massforLimit_CatxA[300];
    TH1D* massforLimit_CatxB[300];
    TH1D* massforLimit_CatxC[300];
    TH1D* massforLimit_CatyA[300];
    TH1D* massforLimit_CatyB[300];
    TH1D* massforLimit_CatyC[300];
    
    float m=10.;
    for(int j=0; j<300.; j++){
      m = m+(m*0.01); 
      massforLimit_CatxA[j] = new TH1D(Form("massforLimit_CatxA%d",j),Form("massforLimit_CatxA%d",j),100,m-(m*0.01*10.),m+(m*0.01*10.));  massforLimit_CatxA[j]->Sumw2();
      massforLimit_CatxB[j] = new TH1D(Form("massforLimit_CatxB%d",j),Form("massforLimit_CatxB%d",j),100,m-(m*0.012*10.),m+(m*0.012*10.));  massforLimit_CatxB[j]->Sumw2();
      massforLimit_CatxC[j] = new TH1D(Form("massforLimit_CatxC%d",j),Form("massforLimit_CatxC%d",j),100,m-(m*0.015*10.),m+(m*0.015*10.));  massforLimit_CatxC[j]->Sumw2();

      massforLimit_CatyA[j] = new TH1D(Form("massforLimit_CatyA%d",j),Form("massforLimit_CatyA%d",j),100,m-(m*0.01*10.),m+(m*0.01*10.));  massforLimit_CatyA[j]->Sumw2();
      massforLimit_CatyB[j] = new TH1D(Form("massforLimit_CatyB%d",j),Form("massforLimit_CatyB%d",j),100,m-(m*0.012*10.),m+(m*0.012*10.));  massforLimit_CatyB[j]->Sumw2();
      massforLimit_CatyC[j] = new TH1D(Form("massforLimit_CatyC%d",j),Form("massforLimit_CatyC%d",j),100,m-(m*0.015*10.),m+(m*0.015*10.));  massforLimit_CatyC[j]->Sumw2();

      //massforLimitBlind[j] = new TH1D(Form("massforLimitBlind%d",j),Form("massforLimitBlind%d",j),48,m-(m*0.01*6.),m+(m*0.01*6.));  massforLimitBlind[j]->Sumw2();
      //cout<<m<<"  "<<j<<endl;
    }

    // return;

   
    //Float massesLimit[3]={1.300,1.400,1.500,};
    TH2F* BS = new TH2F("BS","BS",50,-1.,1.,50,-1.,1.);
    TH1F* forLimitMassZopt[50];
    TH1F* forLimitMassZoptX[50];
    TH1F* forLimitMassZoptXX[50];
    TH1F* forLimitMassZoptXXX[50];
    for(int k=0;k<50;k++){
     forLimitMassZopt[k] 	= new TH1F(Form("forLimitMassZopt%d",k),Form("forLimitMassZopt%d",k),275,0.1,120.);
     forLimitMassZoptX[k] 	= new TH1F(Form("forLimitMassZoptX%d",k),Form("forLimitMassZoptX%d",k),275,0.1,120.);
     forLimitMassZoptXX[k] 	= new TH1F(Form("forLimitMassZoptXX%d",k),Form("forLimitMassZoptXX%d",k),275,0.1,120.);
     forLimitMassZoptXXX[k] 	= new TH1F(Form("forLimitMassZoptXXX%d",k),Form("forLimitMassZoptXXX%d",k),275,0.1,120.);
    }

    TH1F* forLimitMassZ_1 	= new TH1F("forLimitMassZ_1","forLimitMassZ_1",275,0.1,120.);
    TH1F* forLimitMassZ_2 	= new TH1F("forLimitMassZ_2","forLimitMassZ_2",275,0.1,120.);
    TH1F* forLimitMassZ_3 	= new TH1F("forLimitMassZ_3","forLimitMassZ_3",275,0.1,120.);
    TH1F* forLimitMassZ_4 	= new TH1F("forLimitMassZ_4","forLimitMassZ_4",275,0.1,120.);
    TH1F* forLimitMassZ_5 	= new TH1F("forLimitMassZ_5","forLimitMassZ_5",275,0.1,120.);
    TH1F* forLimitMassZ_6 	= new TH1F("forLimitMassZ_6","forLimitMassZ_6",275,0.1,120.);
    TH1F* forLimitMassZ_7 	= new TH1F("forLimitMassZ_7","forLimitMassZ_7",275,60,160.);

    TH1F* dr	= new TH1F("dr","dr",50,0.0,5.);
    TH1F* dimupt	= new TH1F("dimupt","dimupt",50,0.0,30.);
    TH1F* dimuptF	= new TH1F("dimuptF","dimuptF",50,0.0,30.);

    TH1F* forLimitMassZ4Mu 	= new TH1F("forLimitMassZ4Mu","forLimitMassZ4Mu",275,0.1,120.);
    TH1F* forLimitMassZ4Mu_1 	= new TH1F("forLimitMassZ4Mu_1","forLimitMassZ4Mu_1",275,0.1,120.);
    TH1F* forLimitMassZ4Mu_2 	= new TH1F("forLimitMassZ4Mu_2","forLimitMassZ4Mu_2",275,0.1,120.);
    TH1F* forLimitMassZ4Mu_3 	= new TH1F("forLimitMassZ4Mu_3","forLimitMassZ4Mu_3",275,0.1,120.);
    TH1F* forLimitMassZ4Mu_4 	= new TH1F("forLimitMassZ4Mu_4","forLimitMassZ4Mu_4",275,0.1,120.);
    TH1F* forLimitMassZ4Mu_5 	= new TH1F("forLimitMassZ4Mu_5","forLimitMassZ4Mu_5",275,0.1,120.);
    TH1F* forLimitMassZ4Mu_6 	= new TH1F("forLimitMassZ4Mu_6","forLimitMassZ4Mu_6",275,0.1,120.);
    TH1F* forLimitMassZ4Mu_7 	= new TH1F("forLimitMassZ4Mu_7","forLimitMassZ4Mu_7",275,60,160.);
    

    TH1F* trkIsoZh	= new TH1F("trkIsoZh","trkIsoZh",200,0.0,30.);
    TH1F* trkIsoJh	= new TH1F("trkIsoJh","trkIsoJh",200,0.0,30.);
    TH1F* trkIsoFh	= new TH1F("trkIsoFh","trkIsoFh",200,0.0,30.);
    TH1F* trkIsoF2h	= new TH1F("trkIsoF2h","trkIsoF2h",200,0.0,30.);

    TH1F* trkIsoRelZh	= new TH1F("trkIsoRelZh","trkIsoRelZh",200,0.0,10.);
    TH1F* trkIsoRelJh	= new TH1F("trkIsoRelJh","trkIsoRelJh",200,0.0,10.);
    TH1F* trkIsoRelFh	= new TH1F("trkIsoRelFh","trkIsoRelFh",200,0.0,10.);
    TH1F* trkIsoRelF2h	= new TH1F("trkIsoRelF2h","trkIsoRelF2h",200,0.0,10.);

    TH1F* npHitsZh	= new TH1F("npHitsZh","npHitsZh",10,0.0,10.);
    TH1F* npHitsJh	= new TH1F("npHitsJh","npHitsJh",10,0.0,10.);
    TH1F* npHitsFh	= new TH1F("npHitsFh","npHitsFh",10,0.0,10.);
    TH1F* npHitsF2h	= new TH1F("npHitsF2h","npHitsF2h",10,0.0,10.);

    TH1F* nMuonHitsZh	= new TH1F("nMuonHitsZh","nMuonHitsZh",55,0.0,55.);
    TH1F* nMuonHitsJh	= new TH1F("nMuonHitsJh","nMuonHitsJh",55,0.0,55.);
    TH1F* nMuonHitsFh	= new TH1F("nMuonHitsFh","nMuonHitsFh",55,0.0,55.);
    TH1F* nMuonHitsF2h	= new TH1F("nMuonHitsF2h","nMuonHitsF2h",55,0.0,55.);

    TH1F* chi2Zh	= new TH1F("chi2Zh","chi2Zh",40,0.0,20.);
    TH1F* chi2Jh	= new TH1F("chi2Jh","chi2Jh",40,0.0,20.);
    TH1F* chi2Fh	= new TH1F("chi2Fh","chi2Fh",40,0.0,20.);
    TH1F* chi2F2h	= new TH1F("chi2F2h","chi2F2h",40,0.0,20.);

    TH1F* tklayerZh	= new TH1F("tklayerZh","tklayerZh",18,0.0,18.);
    TH1F* tklayerJh	= new TH1F("tklayerJh","tklayerJh",18,0.0,18.);
    TH1F* tklayerFh	= new TH1F("tklayerFh","tklayerFh",18,0.0,18.);
    TH1F* tklayerF2h	= new TH1F("tklayerF2h","tklayerF2h",18,0.0,18.);

    

    



    TH1F* forResolutionAxMassZ 	= new TH1F("forResolutionAxMassZ","forResolutionAxMassZ",1200,60.,120.);
    TH1F* forResolutionBxMassZ 	= new TH1F("forResolutionBxMassZ","forResolutionBxMassZ",1200,60.,120.);
    TH1F* forResolutionCxMassZ 	= new TH1F("forResolutionCxMassZ","forResolutionCxMassZ",1200,60.,120.);
    TH1F* forResolutionAxMassJPsi = new TH1F("forResolutionAxMassJPsi","forResolutionAxMassJPsi",1400,2.8,3.5);
    TH1F* forResolutionBxMassJPsi = new TH1F("forResolutionBxMassJPsi","forResolutionBxMassJPsi",1400,2.8,3.5);
    TH1F* forResolutionCxMassJPsi = new TH1F("forResolutionCxMassJPsi","forResolutionCxMassJPsi",1400,2.8,3.5);
    
    TH1F* forResolutionAyMassZ = new TH1F("forResolutionAyMassZ","forResolutionAyMassZ",1200,60.,120.);
    TH1F* forResolutionByMassZ = new TH1F("forResolutionByMassZ","forResolutionByMassZ",1200,60.,120.);
    TH1F* forResolutionCyMassZ = new TH1F("forResolutionCyMassZ","forResolutionCyMassZ",1200,60.,120.);
    TH1F* forResolutionAyMassJPsi = new TH1F("forResolutionAyMassJPsi","forResolutionAyMassJPsi",1400,2.8,3.5);
    TH1F* forResolutionByMassJPsi = new TH1F("forResolutionByMassJPsi","forResolutionByMassJPsi",1400,2.8,3.5);
    TH1F* forResolutionCyMassJPsi = new TH1F("forResolutionCyMassJPsi","forResolutionCyMassJPsi",1400,2.8,3.5);

    

   for(unsigned int f=0; f<filesToRun.size(); f++){


     cout<<filesToRun[f]<<endl;
    TChain* chain = new TChain("mmtree/tree");
    chain->Add((TString)filesToRun[f]);
    
    TTreeReader reader(chain);
     
    TTreeReaderValue<double>*                      wgt;
    TTreeReaderValue<double>*                      xsec;
    //TTreeReaderValue<std::vector<int>* >            pdgid   ;
    //TTreeReaderValue<std::vector<int>* >            motherid ;
    
    TTreeReaderValue<std::vector<float> >          mpt      (reader, "muonpt"     );
    TTreeReaderValue<std::vector<float> >          meta     (reader, "muoneta"    );
    TTreeReaderValue<std::vector<float> >          mphi     (reader, "muonphi"    );
    TTreeReaderValue<std::vector<float> >          mcharge  (reader, "muoncharge" );
    TTreeReaderValue<std::vector<char>  >          mid      (reader, "muonid"     );
    //TTreeReaderValue<std::vector<float>  >         mvtxind  (reader, "muonvtxind" );
    TTreeReaderValue<std::vector<float> >          chi2     (reader, "chi2"       );
    TTreeReaderValue<std::vector<float> >          dxy      (reader, "dxy"        );
    TTreeReaderValue<std::vector<float> >          dz       (reader, "dz"         );
    TTreeReaderValue<std::vector<float> >          cpiso    (reader, "cpiso"      );
    TTreeReaderValue<std::vector<float> >          chiso    (reader, "chiso"      );
    TTreeReaderValue<std::vector<float> >          phiso    (reader, "phiso"      );
    TTreeReaderValue<std::vector<float> >          nhiso    (reader, "nhiso"      );
    TTreeReaderValue<std::vector<float> >          puiso    (reader, "puiso"      );
    TTreeReaderValue<std::vector<float> >          tkiso    (reader, "tkiso"      );
    TTreeReaderValue<std::vector<bool> >           l1Result (reader, "l1Result"   );
    TTreeReaderValue<std::vector<unsigned char> >  nmhits   (reader, "nMuonHits"  );
    TTreeReaderValue<std::vector<unsigned char> >  nphits   (reader, "nPixelHits" );
    TTreeReaderValue<std::vector<unsigned char> >  ntklayers(reader, "nTkLayers"  );
    TTreeReaderValue<unsigned char>                hlt      (reader, "trig"       );
    TTreeReaderValue<unsigned>                     nverts   (reader, "nvtx"       );
    cout<<"here4"<<endl;
    TTreeReaderValue<std::vector<float> >          vtxX     (reader, "vtxX"       );
    TTreeReaderValue<std::vector<float> >          vtxY     (reader, "vtxY"       );
    TTreeReaderValue<std::vector<float> >          vtxZ     (reader, "vtxZ"       );
    //TTreeReaderValue<std::vector<float> >          vtxchi2  (reader, "vtxchi2"    );
    cout<<"here5"<<endl;
    TTreeReaderValue<double>                       rho      (reader, "rho"        );
    TTreeReaderValue<unsigned int>                 run      (reader, "run"        );
    TTreeReaderValue<unsigned int>                 lumSec   (reader, "lumSec"     );
  cout<<"here6"<<endl;
  //TTreeReaderValue<std::vector<int> >		   pdgid    (reader, "pdgid" );
  //TTreeReaderValue<std::vector<int> > 	   motherid (reader, "motherid");
     cout<<"here7"<<endl;
    
   if (isMC || !isData[f]) {
        wgt  = new TTreeReaderValue<double>(reader, "wgt" );
        xsec = new TTreeReaderValue<double>(reader, "xsec");
	
    }
	 cout<<"here8"<<endl;
 

    double wgtsum  = 1.0;//isMC ? sumwgt(treepath) : 1.0;
    float  puwgt   = 1.0;
    float  mcwgt   = 1.0;
    float  m1pt    = 0.0;        
    float  m1eta   = 0.0;        
    float  m1phi   = 0.0;        
    float  m1iso   = 0.0;        
    float  m2pt    = 0.0;        
    float  m2eta   = 0.0;        
    float  m2phi   = 0.0;        
    float  m2iso   = 0.0;  
float  m3pt    = 0.0;        
    float  m3eta   = 0.0;        
    float  m3phi   = 0.0;        
    float  m3iso   = 0.0;  
float  m4pt    = 0.0;        
    float  m4eta   = 0.0;        
    float  m4phi   = 0.0;        
    float  m4iso   = 0.0;        
    float  mass    = 0.0;        
    float  mass4   = 0.0;        
    char   m1id    = 0;
    char   m2id    = 0;
    char   m3id    = 0;
    char   m4id    = 0;
    float  m1ch    = 0.; 
    float  m2ch    = 0.;
    float  m3ch    = 0.; 
    float  m4ch    = 0.; 
    vector<bool> l1Bools;
    unsigned nvtx  = 0;
    unsigned Run   = 0;
    unsigned LumSec   = 0;

    if (isMC) {
    outtree->Branch("mcwgt" , &mcwgt , "mcwgt/F" );
    outtree->Branch("puwgt" , &puwgt , "puwgt/F" );
    }
    outtree->Branch("m1pt"  , &m1pt  , "m1pt/F"  );
    outtree->Branch("m1eta" , &m1eta , "m1eta/F" );
    outtree->Branch("m1phi" , &m1phi , "m1phi/F" );
    outtree->Branch("m1iso" , &m1iso , "m1iso/F" );
    outtree->Branch("m1id"  , &m1id  , "m1id/B"  );
    outtree->Branch("m2pt"  , &m2pt  , "m2pt/F"  );
    outtree->Branch("m2eta" , &m2eta , "m2eta/F" );
    outtree->Branch("m2phi" , &m2phi , "m2phi/F" );
    outtree->Branch("m2iso" , &m2iso , "m2iso/F" );
    outtree->Branch("m2id"  , &m2id  , "m2id/B"  );
    outtree->Branch("mass"  , &mass  , "mass/F"  );
    outtree->Branch("nvtx"  , &nvtx  , "nvtx/i"  );
    outtree->Branch("Run"   , &Run   , "Run/i"  );
    outtree->Branch("LumSec", &LumSec, "LumSec/i"  );

    //outtree->Branch("l1Bools"  , &l1Bools , "l1Bools" );
    int p=0;
    while(reader.Next()) {
      if (((*hlt) & 2) == 0) continue; 
      //unsigned int hj = 305388;
      //cout<<(*run)<<endl; 
      bool passIso=false;
      bool passIsoLoose=false;
        double ea = (isMC ? 0.3 : 0.45);
        std::vector<unsigned> goodmuons;
        for (std::size_t i = 0; i < mpt->size(); i++) {
	  //if ((*nmhits)[i] == 0)     continue;
	  if ((*nphits)[i] == 0)     continue;
          if ((*ntklayers)[i] <= 5)  continue;
          if ((*chi2)[i] > 10.)      continue;
            double iso = (*cpiso)[i] + (*nhiso)[i] + (*phiso)[i] - ea*(*rho);
	    //	  if (iso > 10.0) continue;

            goodmuons.push_back(i);
        }

        if (goodmuons.size() < 4) continue;

        unsigned idx1 = goodmuons[0];
        unsigned idx2 = goodmuons[1];
	unsigned idx3 = goodmuons[2];
        unsigned idx4 = goodmuons[3];

	if((*tkiso)[goodmuons[0]]<0.02 && (*tkiso)[goodmuons[1]]<0.02 && (*tkiso)[goodmuons[2]]<0.02 && (*tkiso)[goodmuons[3]]<0.02 ) passIso=true;
	if((*tkiso)[goodmuons[0]]<0.05 && (*tkiso)[goodmuons[1]]<0.05 && (*tkiso)[goodmuons[2]]<0.05 && (*tkiso)[goodmuons[3]]<0.05 ) passIsoLoose=true;
	
        if ((*mpt)[goodmuons[0]] < (*mpt)[goodmuons[1]]) {
            idx1 = goodmuons[1];
            idx2 = goodmuons[0];
	    }
	
        TLorentzVector mm;
	TLorentzVector mmmm;
        TLorentzVector m1;
        TLorentzVector m2;
	TLorentzVector m3;
        TLorentzVector m4;
        m1.SetPtEtaPhiM((*mpt)[idx1], (*meta)[idx1], (*mphi)[idx1], 0.1057);
        m2.SetPtEtaPhiM((*mpt)[idx2], (*meta)[idx2], (*mphi)[idx2], 0.1057);
	m3.SetPtEtaPhiM((*mpt)[idx3], (*meta)[idx3], (*mphi)[idx3], 0.1057);
        m4.SetPtEtaPhiM((*mpt)[idx4], (*meta)[idx4], (*mphi)[idx4], 0.1057);

        mm += m1;
        mm += m2;
	mmmm += m1;
	mmmm += m2;
	mmmm += m3;
	mmmm += m4;

        m1pt   = m1.Pt();
        m1eta  = m1.Eta();
        m1phi  = m1.Phi();
        m1iso  = (*cpiso)[idx1] + (*phiso)[idx1] + (*nhiso)[idx1] - ea*(*rho);
        m1id   = (*mid)[idx1];
        m1ch   = (*mcharge)[idx1];

        m2pt   = m2.Pt();
        m2eta  = m2.Eta();
        m2phi  = m2.Phi();
        m2iso  = (*cpiso)[idx2] + (*phiso)[idx2] + (*nhiso)[idx2] - ea*(*rho);
        m2id   = (*mid)[idx2];
	m2ch   = (*mcharge)[idx2];

	m3pt   = m3.Pt();
        m3eta  = m3.Eta();
        m3phi  = m3.Phi();
        m3iso  = (*cpiso)[idx3] + (*phiso)[idx3] + (*nhiso)[idx3] - ea*(*rho);
        m3id   = (*mid)[idx3];
	m3ch   = (*mcharge)[idx3];

	m4pt   = m4.Pt();
        m4eta  = m4.Eta();
        m4phi  = m4.Phi();
        m4iso  = (*cpiso)[idx4] + (*phiso)[idx4] + (*nhiso)[idx4] - ea*(*rho);
        m4id   = (*mid)[idx4];
	m4ch   = (*mcharge)[idx4];
	
	Run=*run;
	LumSec=*lumSec;
	
	vector<double> pts;
	pts.push_back(m1pt);
	pts.push_back(m2pt);
	pts.push_back(m3pt);
	pts.push_back(m4pt);
	std::sort(pts.begin(),pts.end(),greater<float>());
	float maxpT=pts[0];
	float submaxpT=pts[1];
	// cout<<"4 Muons in the Event"<<endl;
 /*
HIGH MASS TRIGGER NO CORRELATION: ID  0 - 4 - 9
'L1_DoubleMu_12_5',
'L1_DoubleMu_12_8',
'L1_DoubleMu_13_6',
'L1_DoubleMu_15_5',
'L1_DoubleMu_15_7',

'L1_TripleMu_4_4_4',
'L1_TripleMu_5_0_0',
'L1_TripleMu_5_3_3',
'L1_TripleMu_5_5_3',
'L1_QuadMu0',

THE LOW MASS TRIGGER: ID 10
'L1_DoubleMu0er1p5_SQ_OS_dR_Max1p4',

THE LOW MASS TRIGGER WITH CORR: 11 - 17
'L1_DoubleMu4p5er2p0_SQ_OS_Mass7to18',
'L1_DoubleMu4_SQ_OS_dR_Max1p2',
'L1_DoubleMu5_SQ_OS_Mass7to18',
'L1_DoubleMu_20_2_SQ_Mass_Max20',

'L1_DoubleMu0er1p4_SQ_OS_dR_Max1p4',

'L1_DoubleMu4p5_SQ_OS_dR_Max1p2',
'L1_DoubleMu6_SQ_OS',

THE LOW MASS TRIGGER TO MEASURE FAKE: ID 18 - 20 [ONLY IN FROM RUN 305405]
'L1_DoubleMu0er1p5_SQ_dR_Max1p4',
'L1_DoubleMu0er2_SQ_dR_Max1p4',
'L1_DoubleMu0_SQ'
	*/

	//'L1_DoubleMu4_SQ_OS_dR_Max1p2', [12]
	//'L1_DoubleMu4p5_SQ_OS_dR_Max1p2', [16]
	//
        mass   = mm.M();

	if(m1ch*m2ch*m3ch*m4ch<0.) continue;

	//if(mass>3. && mass<3.1) trkIsoh->Fill((*tkiso)[goodmuons[1]],m1.DeltaR(m2));
       	mass4  = mmmm.M();
        nvtx = *nverts;
        //outtree->Fill();
	
        bool passPVconstraint = false;
	bool passPVconstraintAll = false;
	float BSx = 0.084;
	float BSy = -0.03;
	if(treepath.find("_13TeV") != string::npos){ BSx = -0.029; BSy = 0.07; }
	float slidePt1 = mm.M()/3.;
	float slidePt2 = mm.M()/4.;



	float maxEta=TMath::Max(abs(m1eta),abs(m2eta));
	

	bool passTheL1Trigger=false;
	
     	if(l1Result->at(0)==true || l1Result->at(1)==true || l1Result->at(2)==true || l1Result->at(3)==true || l1Result->at(4)==true || 
	l1Result->at(11)==true || l1Result->at(13)==true ) passTheL1Trigger=true;

	

	


	if(nvtx>0) forLimitMassZ4Mu->Fill(mass4);
	if(nvtx>0 && passIsoLoose) forLimitMassZ4Mu_1->Fill(mass4);
	if(nvtx>1) forLimitMassZ4Mu_2->Fill(mass4);
	if(nvtx>1 && passIsoLoose) forLimitMassZ4Mu_3->Fill(mass4);
	if(passIsoLoose) forLimitMassZ4Mu_4->Fill(mass4);
	if(nvtx>1 && passIsoLoose && maxpT>20. && submaxpT>10) forLimitMassZ4Mu_5->Fill(mass4);
	if(nvtx>1 && passIsoLoose && maxpT>20. && submaxpT>10 &&( (abs((*vtxX)[0])<0.7 && abs((*vtxY)[0])<0.7) || (abs((*vtxX)[1])<0.7 && abs((*vtxY)[1])<0.7)) ) forLimitMassZ4Mu_6->Fill(mass4);

	if(nvtx>1 && passIsoLoose && maxpT>20. && submaxpT>10 &&( (abs((*vtxX)[0])<0.7 && abs((*vtxY)[0])<0.7) || (abs((*vtxX)[1])<0.7 && abs((*vtxY)[1])<0.7)) && mm.M()>75. && mm.M()<105) forLimitMassZ4Mu_7->Fill(mass4);
	

	//forLimitMassZ_1->Fill(mass);
	// dimupt->Fill(mm.Pt());

	// 	}


    //	if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 /*&& 		      passIsoLoose*/) forLimitMassZ_3->Fill(mass);

	//	if(m1ch*m2ch<0. && (l1Result->at(0)||l1Result->at(11)||l1Result->at(16))  && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 ) forLimitMassZ_4->Fill(mass);



	//if(m1ch*m2ch<0. && l1Result->at(11)  && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 /*&& 		      passIsoLoose*/) forLimitMassZ_3->Fill(mass);
	//if(m1ch*m2ch<0. && l1Result->at(0) && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 /*&& 		      passIsoLoose*/) forLimitMassZ_4->Fill(mass);

	   //if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && 		      passIsoLoose && (l1Result->at(0) || l1Result->at(8) || l1Result->at(11) || l1Result->at(13) || l1Result->at(12))) forLimitMassZ_2->Fill(mass);

	// if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && 		      passIsoLoose ) forLimitMassZ_3->Fill(mass);
	
	/*	   for(int l=0;l<50;l++){
	     if( m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && (*tkiso)[goodmuons[1]] < 0.01*l && (*tkiso)[goodmuons[0]] < 0.01*l )	forLimitMassZopt[l]->Fill(mass);
	   }

	*/
	/*	   


	  for(int l=0;l<50;l++){
	    if((l1Result->at(0) || l1Result->at(11) || l1Result->at(16)) && m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && (*tkiso)[goodmuons[1]] < 0.01*l && (*tkiso)[goodmuons[0]] < 0.01*l )	forLimitMassZoptX[l]->Fill(mass);
	   }

	for(int l=0;l<50;l++){
	    if((l1Result->at(4) || l1Result->at(11) || l1Result->at(16)) && m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && (*tkiso)[goodmuons[1]] < 0.01*l && (*tkiso)[goodmuons[0]] < 0.01*l )	forLimitMassZoptXX[l]->Fill(mass);
	   }


	for(int l=0;l<50;l++){
	     if(l1Result->at(4) && m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && (*tkiso)[goodmuons[1]] < 0.01*l && (*tkiso)[goodmuons[0]] < 0.01*l )	forLimitMassZoptXXX[l]->Fill(mass);
	   }

	*/


	/*for(int l=0;l<50;l++){
	    if((l1Result->at(4) || l1Result->at(11) || l1Result->at(16)) && m1ch*m2ch<0. && passPVconstraint && m1pt>4. && m2pt>4. && (*tkiso)[goodmuons[1]] < 0.01*l*m2pt && (*tkiso)[goodmuons[0]] < 0.01*l*m1pt )	forLimitMassZoptX[l]->Fill(mass);
	   }


	for(int l=0;l<50;l++){
	    if((l1Result->at(4) || l1Result->at(11) || l1Result->at(16)) && m1ch*m2ch<0. && passPVconstraint && m1pt>4. && m2pt>4. && (*tkiso)[goodmuons[1]] < 0.01*l && (*tkiso)[goodmuons[0]] < 0.01*l )	forLimitMassZoptXX[l]->Fill(mass);
	   }


	for(int l=0;l<50;l++){
	     if(l1Result->at(4) && m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && (*tkiso)[goodmuons[1]] < 0.01*l && (*tkiso)[goodmuons[0]] < 0.01*l )	forLimitMassZoptXXX[l]->Fill(mass);
	   }

		
	if(mass>80. && mass<100.){
			if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 ){ 
			  
			trkIsoRelZh->Fill((*tkiso)[idx1]);
			
			trkIsoZh->Fill((*tkiso)[idx1]*m1.P()); 
			
			npHitsZh->Fill((*nphits)[idx1]);
			tklayerZh->Fill((*ntklayers)[idx1]);
	       	
			nMuonHitsZh->Fill((*nmhits)[idx1]);	     	
			chi2Zh->Fill((*chi2)[idx1]);
			
			}
	}



	if(mass>2.99 && mass<3.1){
			if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 ){ 

			trkIsoRelJh->Fill((*tkiso)[idx1]);
			trkIsoJh->Fill((*tkiso)[idx1]*m1.P()); 
			npHitsJh->Fill((*nphits)[idx1]);
			tklayerJh->Fill((*ntklayers)[idx1]);
			nMuonHitsJh->Fill((*nmhits)[idx1]);
			chi2Jh->Fill((*chi2)[idx1]);
			}
	}


	if(mass>11.8 && mass<14){
			if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 ){ 
			dimuptF->Fill(mm.Pt());
			trkIsoRelFh->Fill((*tkiso)[idx1]);			
			trkIsoFh->Fill((*tkiso)[idx1]*m1.P()); 
			npHitsFh->Fill((*nphits)[idx1]);
			tklayerFh->Fill((*ntklayers)[idx1]);
			nMuonHitsFh->Fill((*nmhits)[idx1]);
			chi2Fh->Fill((*chi2)[idx1]);
			dr->Fill(m1.DeltaR(m2));
			}
	}

	if(mass>4.4 && mass<5.4){
			if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 ){ 
			dimuptF->Fill(mm.Pt());
			trkIsoRelF2h->Fill((*tkiso)[idx1]);			
			trkIsoF2h->Fill((*tkiso)[idx1]*m1.P()); 
			npHitsF2h->Fill((*nphits)[idx1]);
			tklayerF2h->Fill((*ntklayers)[idx1]);
			nMuonHitsF2h->Fill((*nmhits)[idx1]);
			chi2F2h->Fill((*chi2)[idx1]);
			dr->Fill(m1.DeltaR(m2));
			}
			}*/

	
	//cout<<"good"<<endl;

	
      }
   }

   /*dimupt->Write();
   dimuptF->Write();

     trkIsoZh->Write();	
     trkIsoJh->Write();
     trkIsoFh->Write();
     trkIsoF2h->Write();

     trkIsoRelZh->Write();
     trkIsoRelJh->Write();
     trkIsoRelFh->Write();
     trkIsoRelF2h->Write();

     npHitsZh->Write();
     npHitsJh->Write();
     npHitsFh->Write();
     npHitsF2h->Write();

     nMuonHitsZh->Write();
     nMuonHitsJh->Write();
     nMuonHitsFh->Write();
     nMuonHitsF2h->Write();

     chi2Zh->Write();
     chi2Jh->Write();
     chi2Fh->Write();
     chi2F2h->Write();

     tklayerZh	->Write();
     tklayerJh	->Write();
     tklayerFh	->Write();
     tklayerF2h	->Write();

     for(int l=0;l<50;l++){
       forLimitMassZopt[l]->Write();
       forLimitMassZoptX[l]->Write();
       forLimitMassZoptXX[l]->Write();
       forLimitMassZoptXXX[l]->Write();
       }*/
     //trkIsoh->Write();


	
forLimitMassZ4Mu->Write();
forLimitMassZ4Mu_1->Write();
forLimitMassZ4Mu_2->Write();
forLimitMassZ4Mu_3->Write();
forLimitMassZ4Mu_4->Write();
forLimitMassZ4Mu_5->Write();
forLimitMassZ4Mu_6->Write();
forLimitMassZ4Mu_7->Write();
   /*forLimitMassZ_1->Write();
   forLimitMassZ_2->Write();
   forLimitMassZ_3->Write();
   forLimitMassZ_4->Write();
   
   dr->Write();*/
   

    outfile->Close();

}

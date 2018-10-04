import ROOT
import os,sys
from ROOT import TGraphAsymmErrors
from ROOT import TGraphErrors
from ROOT import TColor
#from ROOT import TGraph
from array import array
from ROOT import *
from operator import truediv
import random
import math
import glob

ROOT.gStyle.SetOptStat(0)

a=(0.02**2)*0.0001

limit1=array('d')
limit195up=array('d')
limit195down=array('d')
limit168up=array('d')
limit168down=array('d')
limitObserved=array('d')
mass=array('d')

m=10.

for d in range(0,300):

	m=m+(m*0.01)
	file=glob.glob("higgsCombineasympMassIndex_"+str(d)+".AsymptoticLimits.mH*.root")	
	f=ROOT.TFile.Open(file[0])

	tree=f.Get("limit")
	tree.GetEntry(2)
	limit1.append(tree.limit*a)

	
	mass.append(m)
	print m

c1=ROOT.TCanvas("c1","c1",1000,600)
c1.SetGrid()
c1.SetLogy()
c1.SetLogx()

graph_limit1=ROOT.TGraph(len(mass),mass,limit1)
graph_limit1.SetMarkerStyle(34)
graph_limit1.SetMarkerSize(1)
graph_limit1.SetMarkerColor(kRed)
graph_limit1.SetLineColor(kRed)
graph_limit1.GetYaxis().SetRangeUser(10**(-7),5*10**(-5))
graph_limit1.GetYaxis().SetTitle("#epsilon^{2}")
graph_limit1.GetXaxis().SetTitle("Dark Photon Mass [GeV]")
graph_limit1.Draw("ACP")

c1.SaveAs("limit2018DarkPhoton.pdf")

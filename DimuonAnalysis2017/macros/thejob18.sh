#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh

cd /afs/cern.ch/work/j/jsalfeld/Princeton/DarkStuff/CMSSW_9_4_6/src/DarkPhotonAnalysis/DimuonAnalysis2017/macros/

eval `scramv1 runtime -sh` # cmsenv is an alias not on the workers

in=$1
out="${in/scout_/hists_}"
echo $out

root -l -b trimscoutMakeTheCardsxyz18.C\(\"$in\"\,\"$out\"\,false\)

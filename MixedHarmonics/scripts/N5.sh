#!/bin/sh
cd ..
DIRECTORY="results/v5"
if [ ! -d "$DIRECTORY" ]; then
    mkdir $DIRECTORY
    cp -r src $DIRECTORY/.
    cp ~/PbPb_2015/CMSSW_7_5_8_patch7/src/RecoHI/HiEvtPlaneAlgos/interface/HiEvtPlaneList.h  $DIRECTORY/.
    cp GenerateVN.C $DIRECTORY/.
    cp -r EfficiencyTables $DIRECTORY/.
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_vn_262548_262799/* > inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_vn_262800_263230/* >> inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_vn_263231_263359/* >> inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_vn_263360_263379/* >> inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_vn_263380_263614/* >> inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_vn_263615_263757/* >> inlist.dat
mv inlist.dat $DIRECTORY/.
fi
cd $DIRECTORY
if [ ! -d "results" ]; then
    mkdir results
    mkdir logs
fi
root -l -b -q 'GenerateVN.C+("N5SUB3", "PbPb", "inlist.dat", 5000)' > logs/N5.log
cd ..


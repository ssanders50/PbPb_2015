#!/bin/sh
rm logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_AMPT_calib1/* > logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_AMPT_calib2/* >> logs/default_inlist.dat
root -l -b -q 'MergeFiles.C("logs/default_inlist.dat","PbPbMCa_",20)'
rm logs/default_inlist.dat
ls -1 /rfs/sanders/tmp/PbPbMCa_*.root > logs/default_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/default_inlist.dat","PbPbMCb_",10)'
hadd -f /rfs/sanders/tmp/PbPb_AMPT.root /rfs/sanders/tmp/PbPMCb_*.root
#rm /rfs/sanders/tmp/PbPbMCa_*.root
#rm /rfs/sanders/tmp/PbPbMCb_*.root

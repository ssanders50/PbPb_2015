#!/bin/sh
rm logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb2015_AMPT_melt_batch1/* > logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb2015_AMPT_melt_batch2/* >> logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb2015_AMPT_melt_batch3/* >> logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb2015_AMPT_melt_batch4/* >> logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb2015_AMPT_melt_batch5/* >> logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb2015_AMPT_melt_batch6/* >> logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb2015_AMPT_melt_batch7/* >> logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb2015_AMPT_melt_batch8/* >> logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb2015_AMPT_melt_batch9/* >> logs/default_inlist.dat
root -l -b -q 'MergeFiles.C("logs/default_inlist.dat","PbPbMCa_",20)'
rm logs/default_inlist.dat
ls -1 /rfs/sanders/tmp/PbPbMCa_*.root > logs/default_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/default_inlist.dat","PbPbMCb_",10)'
hadd -f MH_AMPT.root /rfs/sanders/tmp/PbPbMCb_*.root
#rm /rfs/sanders/tmp/PbPbMCa_*.root
#rm /rfs/sanders/tmp/PbPbMCb_*.root

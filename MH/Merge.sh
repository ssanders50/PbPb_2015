#!/bin/sh
rm logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_MH_262548_262799/* > logs/default_inlist.dat
root -l -b -q 'MergeFiles.C("logs/default_inlist.dat","PbPb1a_",20)'
rm logs/default_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1a_*.root > logs/default_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/default_inlist.dat","PbPb1b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_262548_262799.root /rfs/sanders/tmp/PbPb1b_*.root
rm /rfs/sanders/tmp/PbPb1a_*.root
rm /rfs/sanders/tmp/PbPb1b_*.root

rm logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_MH_262800_263230/* > logs/default_inlist.dat
root -l -b -q 'MergeFiles.C("logs/default_inlist.dat","PbPb1a_",20)'
rm logs/default_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1a_*.root > logs/default_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/default_inlist.dat","PbPb1b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_262800_263230.root /rfs/sanders/tmp/PbPb1b_*.root
rm /rfs/sanders/tmp/PbPb1a_*.root
rm /rfs/sanders/tmp/PbPb1b_*.root

rm logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_MH_263231_263359/* > logs/default_inlist.dat
root -l -b -q 'MergeFiles.C("logs/default_inlist.dat","PbPb1a_",20)'
rm logs/default_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1a_*.root > logs/default_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/default_inlist.dat","PbPb1b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_263231_263359.root /rfs/sanders/tmp/PbPb1b_*.root
rm /rfs/sanders/tmp/PbPb1a_*.root
rm /rfs/sanders/tmp/PbPb1b_*.root

rm logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_MH_263360_263379/* > logs/default_inlist.dat
root -l -b -q 'MergeFiles.C("logs/default_inlist.dat","PbPb1a_",20)'
rm logs/default_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1a_*.root > logs/default_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/default_inlist.dat","PbPb1b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_263360_263379.root /rfs/sanders/tmp/PbPb1b_*.root
rm /rfs/sanders/tmp/PbPb1a_*.root
rm /rfs/sanders/tmp/PbPb1b_*.root

rm logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_MH_263380_263614/* > logs/default_inlist.dat
root -l -b -q 'MergeFiles.C("logs/default_inlist.dat","PbPb1a_",20)'
rm logs/default_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1a_*.root > logs/default_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/default_inlist.dat","PbPb1b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_263380_263614.root /rfs/sanders/tmp/PbPb1b_*.root
rm /rfs/sanders/tmp/PbPb1a_*.root
rm /rfs/sanders/tmp/PbPb1b_*.root


rm logs/default_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_MH_263615_263757/* > logs/default_inlist.dat
root -l -b -q 'MergeFiles.C("logs/default_inlist.dat","PbPb1a_",20)'
rm logs/default_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1a_*.root > logs/default_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/default_inlist.dat","PbPb1b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_263615_263757.root /rfs/sanders/tmp/PbPb1b_*.root
rm /rfs/sanders/tmp/PbPb1a_*.root
rm /rfs/sanders/tmp/PbPb1b_*.root

hadd -f MH.root /rfs/sanders/tmp/PbPb_2*.root

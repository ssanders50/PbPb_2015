#!/bin/sh
rm logs/default_262548_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_MH_262548_262799/* > logs/default_262548_inlist.dat
root -l -b -q 'MergeFiles.C("logs/default_262548_inlist.dat","PbPb1a_262548_",20)'
rm logs/default_262548_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1a_262548_*.root > logs/default_262548_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/default_262548_inlist.dat","PbPb1b_262548_",10)'
hadd -f /rfs/sanders/tmp/PbPb_262548_262799.root /rfs/sanders/tmp/PbPb1b_262548_*.root

rm logs/default_262800_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_MH_262800_263230/* > logs/default_262800_inlist.dat
root -l -b -q 'MergeFiles.C("logs/default_262800_inlist.dat","PbPb1a_262800_",20)'
rm logs/default_262800_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1a_262800_*.root > logs/default_262800_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/default_262800_inlist.dat","PbPb1b_262800_",10)'
hadd -f /rfs/sanders/tmp/PbPb_262800_263230.root /rfs/sanders/tmp/PbPb1b_262800_*.root

rm logs/default_263231_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_MH_263231_263359/* > logs/default_263231_inlist.dat
root -l -b -q 'MergeFiles.C("logs/default_263231_inlist.dat","PbPb1a_263231_",20)'
rm logs/default_263231_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1a_263231_*.root > logs/default_263231_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/default_263231_inlist.dat","PbPb1b_263231_",10)'
hadd -f /rfs/sanders/tmp/PbPb_263231_263359.root /rfs/sanders/tmp/PbPb1b_*.root

rm logs/default_263360_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_MH_263360_263379/* > logs/default_263360_inlist.dat
root -l -b -q 'MergeFiles.C("logs/default_263360_inlist.dat","PbPb1a_263360_",20)'
rm logs/default_263360_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1a_263360_*.root > logs/default_263360_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/default_263360_inlist.dat","PbPb1b_263360_",10)'
hadd -f /rfs/sanders/tmp/PbPb_263360_263379.root /rfs/sanders/tmp/PbPb1b_263360_*.root

rm logs/default_263380_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_MH_263380_263614/* > logs/default_263380_inlist.dat
root -l -b -q 'MergeFiles.C("logs/default_263380_inlist.dat","PbPb1a_263380_",20)'
rm logs/default_263380_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1a_263380_*.root > logs/default_263380_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/default_263380_inlist.dat","PbPb1b_263380_",10)'
hadd -f /rfs/sanders/tmp/PbPb_263380_263614.root /rfs/sanders/tmp/PbPb1b_263380_*.root

rm logs/default_263615_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_MH_263615_263757/* > logs/default_263615_inlist.dat
root -l -b -q 'MergeFiles.C("logs/default_263615_inlist.dat","PbPb1a_263615_",20)'
rm logs/default_263615_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1a_263615_*.root > logs/default_263615_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/default_263615_inlist.dat","PbPb1b_263615_",10)'
hadd -f /rfs/sanders/tmp/PbPb_263615_263757.root /rfs/sanders/tmp/PbPb1b_263615_*.root

hadd -f MH.root /rfs/sanders/tmp/PbPb_2*.root

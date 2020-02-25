#!/bin/sh
rm logs/wide_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_wide_262548_262799/* > logs/wide_inlist.dat
root -l -b -q 'MergeFiles.C("logs/wide_inlist.dat","PbPb_wide_a_",20)'
rm logs/wide_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_wide_a_*.root > logs/wide_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/wide_inlist.dat","PbPb_wide_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_wide_262548_262799.root /rfs/sanders/tmp/PbPb_wide_b_*.root
rm /rfs/sanders/tmp/PbPb_wide_a_*.root
rm /rfs/sanders/tmp/PbPb_wide_b_*.root

rm logs/wide_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_wide_262800_263230/* > logs/wide_inlist.dat
root -l -b -q 'MergeFiles.C("logs/wide_inlist.dat","PbPb_wide_a_",20)'
rm logs/wide_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_wide_a_*.root > logs/wide_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/wide_inlist.dat","PbPb_wide_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_wide_262800_263230.root /rfs/sanders/tmp/PbPb_wide_b_*.root
rm /rfs/sanders/tmp/PbPb_wide_a_*.root
rm /rfs/sanders/tmp/PbPb_wide_b_*.root

rm logs/wide_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_wide_263231_263359/* > logs/wide_inlist.dat
root -l -b -q 'MergeFiles.C("logs/wide_inlist.dat","PbPb_wide_a_",20)'
rm logs/wide_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_wide_a_*.root > logs/wide_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/wide_inlist.dat","PbPb_wide_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_wide_263231_263359.root /rfs/sanders/tmp/PbPb_wide_b_*.root
rm /rfs/sanders/tmp/PbPb_wide_a_*.root
rm /rfs/sanders/tmp/PbPb_wide_b_*.root

rm logs/wide_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_wide_263360_263379/* > logs/wide_inlist.dat
root -l -b -q 'MergeFiles.C("logs/wide_inlist.dat","PbPb_wide_a_",20)'
rm logs/wide_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_wide_a_*.root > logs/wide_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/wide_inlist.dat","PbPb_wide_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_wide_263360_263379.root /rfs/sanders/tmp/PbPb_wide_b_*.root
rm /rfs/sanders/tmp/PbPb_wide_a_*.root
rm /rfs/sanders/tmp/PbPb_wide_b_*.root

rm logs/wide_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_wide_263380_263614/* > logs/wide_inlist.dat
root -l -b -q 'MergeFiles.C("logs/wide_inlist.dat","PbPb_wide_a_",20)'
rm logs/wide_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_wide_a_*.root > logs/wide_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/wide_inlist.dat","PbPb_wide_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_wide_263380_263614.root /rfs/sanders/tmp/PbPb_wide_b_*.root
rm /rfs/sanders/tmp/PbPb_wide_a_*.root
rm /rfs/sanders/tmp/PbPb_wide_b_*.root


rm logs/wide_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_wide_263615_263757/* > logs/wide_inlist.dat
root -l -b -q 'MergeFiles.C("logs/wide_inlist.dat","PbPb_wide_a_",20)'
rm logs/wide_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_wide_a_*.root > logs/wide_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/wide_inlist.dat","PbPb_wide_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_wide_263615_263757.root /rfs/sanders/tmp/PbPb_wide_b_*.root
rm /rfs/sanders/tmp/PbPb_wide_a_*.root
rm /rfs/sanders/tmp/PbPb_wide_b_*.root

hadd -f MH_wide.root /rfs/sanders/tmp/PbPb_wide_*.root

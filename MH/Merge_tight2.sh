#!/bin/sh
rm logs/tight2_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_tight2_262548_262799/* > logs/tight2_inlist.dat
root -l -b -q 'MergeFiles.C("logs/tight2_inlist.dat","PbPb_tight2_a_",20)'
rm logs/tight2_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_tight2_a_*.root > logs/tight2_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/tight2_inlist.dat","PbPb_tight2_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_tight2_262548_262799.root /rfs/sanders/tmp/PbPb_tight2_b_*.root
rm /rfs/sanders/tmp/PbPb_tight2_a_*.root
rm /rfs/sanders/tmp/PbPb_tight2_b_*.root

rm logs/tight2_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_tight2_262800_263230/* > logs/tight2_inlist.dat
root -l -b -q 'MergeFiles.C("logs/tight2_inlist.dat","PbPb_tight2_a_",20)'
rm logs/tight2_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_tight2_a_*.root > logs/tight2_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/tight2_inlist.dat","PbPb_tight2_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_tight2_262800_263230.root /rfs/sanders/tmp/PbPb_tight2_b_*.root
rm /rfs/sanders/tmp/PbPb_tight2_a_*.root
rm /rfs/sanders/tmp/PbPb_tight2_b_*.root

rm logs/tight2_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_tight2_263231_263359/* > logs/tight2_inlist.dat
root -l -b -q 'MergeFiles.C("logs/tight2_inlist.dat","PbPb_tight2_a_",20)'
rm logs/tight2_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_tight2_a_*.root > logs/tight2_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/tight2_inlist.dat","PbPb_tight2_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_tight2_263231_263359.root /rfs/sanders/tmp/PbPb_tight2_b_*.root
rm /rfs/sanders/tmp/PbPb_tight2_a_*.root
rm /rfs/sanders/tmp/PbPb_tight2_b_*.root

rm logs/tight2_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_tight2_263360_263379/* > logs/tight2_inlist.dat
root -l -b -q 'MergeFiles.C("logs/tight2_inlist.dat","PbPb_tight2_a_",20)'
rm logs/tight2_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_tight2_a_*.root > logs/tight2_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/tight2_inlist.dat","PbPb_tight2_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_tight2_263360_263379.root /rfs/sanders/tmp/PbPb_tight2_b_*.root
rm /rfs/sanders/tmp/PbPb_tight2_a_*.root
rm /rfs/sanders/tmp/PbPb_tight2_b_*.root

rm logs/tight2_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_tight2_263380_263614/* > logs/tight2_inlist.dat
root -l -b -q 'MergeFiles.C("logs/tight2_inlist.dat","PbPb_tight2_a_",20)'
rm logs/tight2_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_tight2_a_*.root > logs/tight2_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/tight2_inlist.dat","PbPb_tight2_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_tight2_263380_263614.root /rfs/sanders/tmp/PbPb_tight2_b_*.root
rm /rfs/sanders/tmp/PbPb_tight2_a_*.root
rm /rfs/sanders/tmp/PbPb_tight2_b_*.root


rm logs/tight2_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_tight2_263615_263757/* > logs/tight2_inlist.dat
root -l -b -q 'MergeFiles.C("logs/tight2_inlist.dat","PbPb_tight2_a_",20)'
rm logs/tight2_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_tight2_a_*.root > logs/tight2_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/tight2_inlist.dat","PbPb_tight2_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_tight2_263615_263757.root /rfs/sanders/tmp/PbPb_tight2_b_*.root
rm /rfs/sanders/tmp/PbPb_tight2_a_*.root
rm /rfs/sanders/tmp/PbPb_tight2_b_*.root

hadd -f MH_tight2.root /rfs/sanders/tmp/PbPb_tight2_*.root

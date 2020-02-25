#!/bin/sh
rm logs/narrow_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_narrow_262548_262799/* > logs/narrow_inlist.dat
root -l -b -q 'MergeFiles.C("logs/narrow_inlist.dat","PbPb_narrow_a_",20)'
rm logs/narrow_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_narrow_a_*.root > logs/narrow_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/narrow_inlist.dat","PbPb_narrow_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_narrow_262548_262799.root /rfs/sanders/tmp/PbPb_narrow_b_*.root
rm /rfs/sanders/tmp/PbPb_narrow_a_*.root
rm /rfs/sanders/tmp/PbPb_narrow_b_*.root

rm logs/narrow_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_narrow_262800_263230/* > logs/narrow_inlist.dat
root -l -b -q 'MergeFiles.C("logs/narrow_inlist.dat","PbPb_narrow_a_",20)'
rm logs/narrow_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_narrow_a_*.root > logs/narrow_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/narrow_inlist.dat","PbPb_narrow_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_narrow_262800_263230.root /rfs/sanders/tmp/PbPb_narrow_b_*.root
rm /rfs/sanders/tmp/PbPb_narrow_a_*.root
rm /rfs/sanders/tmp/PbPb_narrow_b_*.root

rm logs/narrow_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_narrow_263231_263359/* > logs/narrow_inlist.dat
root -l -b -q 'MergeFiles.C("logs/narrow_inlist.dat","PbPb_narrow_a_",20)'
rm logs/narrow_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_narrow_a_*.root > logs/narrow_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/narrow_inlist.dat","PbPb_narrow_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_narrow_263231_263359.root /rfs/sanders/tmp/PbPb_narrow_b_*.root
rm /rfs/sanders/tmp/PbPb_narrow_a_*.root
rm /rfs/sanders/tmp/PbPb_narrow_b_*.root

rm logs/narrow_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_narrow_263360_263379/* > logs/narrow_inlist.dat
root -l -b -q 'MergeFiles.C("logs/narrow_inlist.dat","PbPb_narrow_a_",20)'
rm logs/narrow_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_narrow_a_*.root > logs/narrow_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/narrow_inlist.dat","PbPb_narrow_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_narrow_263360_263379.root /rfs/sanders/tmp/PbPb_narrow_b_*.root
rm /rfs/sanders/tmp/PbPb_narrow_a_*.root
rm /rfs/sanders/tmp/PbPb_narrow_b_*.root

rm logs/narrow_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_narrow_263380_263614/* > logs/narrow_inlist.dat
root -l -b -q 'MergeFiles.C("logs/narrow_inlist.dat","PbPb_narrow_a_",20)'
rm logs/narrow_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_narrow_a_*.root > logs/narrow_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/narrow_inlist.dat","PbPb_narrow_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_narrow_263380_263614.root /rfs/sanders/tmp/PbPb_narrow_b_*.root
rm /rfs/sanders/tmp/PbPb_narrow_a_*.root
rm /rfs/sanders/tmp/PbPb_narrow_b_*.root


rm logs/narrow_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_narrow_263615_263757/* > logs/narrow_inlist.dat
root -l -b -q 'MergeFiles.C("logs/narrow_inlist.dat","PbPb_narrow_a_",20)'
rm logs/narrow_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_narrow_a_*.root > logs/narrow_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/narrow_inlist.dat","PbPb_narrow_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_narrow_263615_263757.root /rfs/sanders/tmp/PbPb_narrow_b_*.root
rm /rfs/sanders/tmp/PbPb_narrow_a_*.root
rm /rfs/sanders/tmp/PbPb_narrow_b_*.root

hadd -f MH_narrow.root /rfs/sanders/tmp/PbPb_narrow_*.root

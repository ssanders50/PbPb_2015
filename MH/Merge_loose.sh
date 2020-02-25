#!/bin/sh
rm logs/loose_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_loose_262548_262799/* > logs/loose_inlist.dat
root -l -b -q 'MergeFiles.C("logs/loose_inlist.dat","PbPb_loose_a_",20)'
rm logs/loose_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_loose_a_*.root > logs/loose_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/loose_inlist.dat","PbPb_loose_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_loose_262548_262799.root /rfs/sanders/tmp/PbPb_loose_b_*.root
rm /rfs/sanders/tmp/PbPb_loose_a_*.root
rm /rfs/sanders/tmp/PbPb_loose_b_*.root

rm logs/loose_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_loose_262800_263230/* > logs/loose_inlist.dat
root -l -b -q 'MergeFiles.C("logs/loose_inlist.dat","PbPb_loose_a_",20)'
rm logs/loose_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_loose_a_*.root > logs/loose_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/loose_inlist.dat","PbPb_loose_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_loose_262800_263230.root /rfs/sanders/tmp/PbPb_loose_b_*.root
rm /rfs/sanders/tmp/PbPb_loose_a_*.root
rm /rfs/sanders/tmp/PbPb_loose_b_*.root

rm logs/loose_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_loose_263231_263359/* > logs/loose_inlist.dat
root -l -b -q 'MergeFiles.C("logs/loose_inlist.dat","PbPb_loose_a_",20)'
rm logs/loose_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_loose_a_*.root > logs/loose_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/loose_inlist.dat","PbPb_loose_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_loose_263231_263359.root /rfs/sanders/tmp/PbPb_loose_b_*.root
rm /rfs/sanders/tmp/PbPb_loose_a_*.root
rm /rfs/sanders/tmp/PbPb_loose_b_*.root

rm logs/loose_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_loose_263360_263379/* > logs/loose_inlist.dat
root -l -b -q 'MergeFiles.C("logs/loose_inlist.dat","PbPb_loose_a_",20)'
rm logs/loose_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_loose_a_*.root > logs/loose_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/loose_inlist.dat","PbPb_loose_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_loose_263360_263379.root /rfs/sanders/tmp/PbPb_loose_b_*.root
rm /rfs/sanders/tmp/PbPb_loose_a_*.root
rm /rfs/sanders/tmp/PbPb_loose_b_*.root

rm logs/loose_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_loose_263380_263614/* > logs/loose_inlist.dat
root -l -b -q 'MergeFiles.C("logs/loose_inlist.dat","PbPb_loose_a_",20)'
rm logs/loose_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_loose_a_*.root > logs/loose_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/loose_inlist.dat","PbPb_loose_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_loose_263380_263614.root /rfs/sanders/tmp/PbPb_loose_b_*.root
rm /rfs/sanders/tmp/PbPb_loose_a_*.root
rm /rfs/sanders/tmp/PbPb_loose_b_*.root


rm logs/loose_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_loose_263615_263757/* > logs/loose_inlist.dat
root -l -b -q 'MergeFiles.C("logs/loose_inlist.dat","PbPb_loose_a_",20)'
rm logs/loose_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb_loose_a_*.root > logs/loose_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/loose_inlist.dat","PbPb_loose_b_",10)'
hadd -f /rfs/sanders/tmp/PbPb_loose_263615_263757.root /rfs/sanders/tmp/PbPb_loose_b_*.root
rm /rfs/sanders/tmp/PbPb_loose_a_*.root
rm /rfs/sanders/tmp/PbPb_loose_b_*.root

hadd -f MH_loose.root /rfs/sanders/tmp/PbPb_loose_*.root

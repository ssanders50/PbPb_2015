#!/bin/sh
rm logs/flat_262548_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_flat_262548_262799/* > logs/flat_262548_inlist.dat
root -l -b -q 'MergeFiles.C("logs/flat_262548_inlist.dat","PbPb1flata_262548_",20)'
rm logs/flat_262548_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1flata_262548_*.root > logs/flat_262548_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/flat_262548_inlist.dat","PbPb1flatb_262548_",10)'
hadd -f /rfs/sanders/tmp/PbPb_flat_262548_262799.root /rfs/sanders/tmp/PbPb1flatb_262548_*.root

rm logs/flat_262800_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_flat_262800_263230/* > logs/flat_262800_inlist.dat
root -l -b -q 'MergeFiles.C("logs/flat_262800_inlist.dat","PbPb1flata_262800_",20)'
rm logs/flat_262800_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1flata_262800_*.root > logs/flat_262800_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/flat_262800_inlist.dat","PbPb1flatb_262800_",10)'
hadd -f /rfs/sanders/tmp/PbPb_flat_262800_263230.root /rfs/sanders/tmp/PbPb1flatb_262800_*.root

rm logs/flat_263231_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_flat_263231_263359/* > logs/flat_263231_inlist.dat
root -l -b -q 'MergeFiles.C("logs/flat_263231_inlist.dat","PbPb1flata_263231_",20)'
rm logs/flat_263231_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1flata_263231_*.root > logs/flat_263231_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/flat_263231_inlist.dat","PbPb1flatb_263231_",10)'
hadd -f /rfs/sanders/tmp/PbPb_flat_263231_263359.root /rfs/sanders/tmp/PbPb1flatb_*.root

rm logs/flat_263360_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_flat_263360_263379/* > logs/flat_263360_inlist.dat
root -l -b -q 'MergeFiles.C("logs/flat_263360_inlist.dat","PbPb1flata_263360_",20)'
rm logs/flat_263360_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1flata_263360_*.root > logs/flat_263360_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/flat_263360_inlist.dat","PbPb1flatb_263360_",10)'
hadd -f /rfs/sanders/tmp/PbPb_flat_263360_263379.root /rfs/sanders/tmp/PbPb1flatb_263360_*.root

rm logs/flat_263380_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_flat_263380_263614/* > logs/flat_263380_inlist.dat
root -l -b -q 'MergeFiles.C("logs/flat_263380_inlist.dat","PbPb1flata_263380_",20)'
rm logs/flat_263380_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1flata_263380_*.root > logs/flat_263380_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/flat_263380_inlist.dat","PbPb1flatb_263380_",10)'
hadd -f /rfs/sanders/tmp/PbPb_flat_263380_263614.root /rfs/sanders/tmp/PbPb1flatb_263380_*.root

rm logs/flat_263615_inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_flat_263615_263757/* > logs/flat_263615_inlist.dat
root -l -b -q 'MergeFiles.C("logs/flat_263615_inlist.dat","PbPb1flata_263615_",20)'
rm logs/flat_263615_inlist.dat
ls -1 /rfs/sanders/tmp/PbPb1flata_263615_*.root > logs/flat_263615_inlist.dat
root -l -b -q 'MergeFiles.C+("logs/flat_263615_inlist.dat","PbPb1flatb_263615_",10)'
hadd -f /rfs/sanders/tmp/PbPb_flat_263615_263757.root /rfs/sanders/tmp/PbPb1flatb_263615_*.root

hadd -f flat_flat.root /rfs/sanders/tmp/PbPb_flat_2*.root

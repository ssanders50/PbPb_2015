#!/bin/sh
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_tight_262548_262799/* > inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_tight_262800_263230/* >> inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_tight_263231_263359/* >> inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_tight_263360_263379/* >> inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_tight_263380_263614/* >> inlist.dat
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_tight_263615_263757/* >> inlist.dat
root -l -b -q ClearBadFiles.C+


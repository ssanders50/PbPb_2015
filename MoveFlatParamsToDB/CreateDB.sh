#!/bin/bash
cd EPCalib
rm *.so
rm *.d
rm *.pcm
rm -rf HiEvtPlaneList.h
rm -rf HiEvtPlaneFlatten.h
ln -s $CMSSW_BASE/src/RecoHI/HiEvtPlaneAlgos/interface/HiEvtPlaneList.h
ln -s $CMSSW_BASE/src/RecoHI/HiEvtPlaneAlgos/interface/HiEvtPlaneFlatten.h
cd ..
rm -rf data/*.root
rm -rf RescorTables
rm *.db
rm /rfs/sanders/tmpPbPb
rm /rfs/sanders/EPPbPb.root
rm tmp.lis

ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_calib_262548_262799/* > tmp.lis
mkdir RescorTables
root -l -b -q "EPCalib/EPCalib.C+(1,262799)"
rm offsets/offset_PbPb2015_1_262799.root
mv foff.root offsets/offset_PbPb2015_1_262799.root
cd data
rm rpflat_combined.root
ln -s /rfs/sanders/EPPbPb.root rpflat_combined.root
cd ..
cmsRun moveflatparamstodb_cfg.py print outputFile=HeavyIonRPRcd_PbPb2015_1_262799.db outputTag=HeavyIonRPRcd begin=1 end=262799
rm /rfs/sanders/tmpPbPb
rm save/EP_PbPb2015_1_262799.root
mv /rfs/sanders/EPPbPb.root save/EP_PbPb2015_1_262799.root
rm  -rf RescorSave/RescorTables_PbPb2016_1_262799
mv RescorTables RescorSave/RescorTables_PbPb2016_1_262799

mkdir RescorTables
rm tmp.lis
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_calib_262800_263230/* > tmp.lis
root -l -b -q "EPCalib/EPCalib.C+(262800,263230)"
cp foff.root offsets/offset_PbPb2015_262800_263230.root
cd data
rm data/rpflat_combined.root
ln -s /rfs/sanders/EPPbPb.root rpflat_combined.root
cd ..
cmsRun moveflatparamstodb_cfg.py print outputFile=HeavyIonRPRcd_PbPb2015_262800_263230.db outputTag=HeavyIonRPRcd begin=262800 end=263230
rm /rfs/sanders/tmpPbPb
rm save/EP_PbPb2015_262800_263230.root
mv /rfs/sanders/EPPbPb.root save/EP_PbPb2015_262800_263230.root
rm  -rf RescorSave/RescorTables_PbPb2015_262800_263230
mv RescorTables RescorSave/RescorTables_PbPb2015_262800_263230

mkdir RescorTables
rm tmp.lis
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_calib_263231_263359/* > tmp.lis
root -l -b -q "EPCalib/EPCalib.C+(263231,263359)"
cp foff.root offsets/offset_PbPb2015_263231_263359.root
cd data
rm data/rpflat_combined.root
ln -s /rfs/sanders/EPPbPb.root rpflat_combined.root
cd ..
cmsRun moveflatparamstodb_cfg.py print outputFile=HeavyIonRPRcd_PbPb2015_263231_263359.db outputTag=HeavyIonRPRcd begin=263231 end=263359
rm /rfs/sanders/tmpPbPb
rm save/EP_PbPb2015_263231_263359.root
mv /rfs/sanders/EPPbPb.root save/EP_PbPb2015_263231_263359.root
rm  -rf RescorSave/RescorTables_PbPb2015_263231_263359
mv RescorTables RescorSave/RescorTables_PbPb2015_263231_263359

mkdir RescorTables
rm tmp.lis
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_calib_263360_263379/* > tmp.lis
root -l -b -q "EPCalib/EPCalib.C+(263360,263379)"
cp foff.root offsets/offset_PbPb2015_263360_263379.root
cd data
rm data/rpflat_combined.root
ln -s /rfs/sanders/EPPbPb.root rpflat_combined.root
cd ..
cmsRun moveflatparamstodb_cfg.py print outputFile=HeavyIonRPRcd_PbPb2015_263360_263379.db outputTag=HeavyIonRPRcd begin=263360 end=263379
rm /rfs/sanders/tmpPbPb
rm save/EP_PbPb2015_263360_263379.root
mv /rfs/sanders/EPPbPb.root save/EP_PbPb2015_263360_263379.root
rm  -rf RescorSave/RescorTables_PbPb2015_263360_263379
mv RescorTables RescorSave/RescorTables_PbPb2015_263360_263379

mkdir RescorTables
rm tmp.lis
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_calib_263380_263614/* > tmp.lis
root -l -b -q "EPCalib/EPCalib.C+(263380,263614)"
cp foff.root offsets/offset_PbPb2015_263380_263614.root
cd data
rm data/rpflat_combined.root
ln -s /rfs/sanders/EPPbPb.root rpflat_combined.root
cd ..
cmsRun moveflatparamstodb_cfg.py print outputFile=HeavyIonRPRcd_PbPb2015_263380_263614.db outputTag=HeavyIonRPRcd begin=263380 end=263614
rm /rfs/sanders/tmpPbPb
rm save/EP_PbPb2015_263380_263614.root
mv /rfs/sanders/EPPbPb.root save/EP_PbPb2015_263380_263614.root
rm  -rf RescorSave/RescorTables_PbPb2015_263380_263614
mv RescorTables RescorSave/RescorTables_PbPb2015_263380_263614

mkdir RescorTables
rm tmp.lis
ls -1 /rfs/sanders/crab_projects/crab_PbPb_2015_calib_263615_263757/* > tmp.lis
root -l -b -q "EPCalib/EPCalib.C+(263615,263757)"
cp foff.root offsets/offset_PbPb2015_263615_263757.root
cd data
rm data/rpflat_combined.root
ln -s /rfs/sanders/EPPbPb.root rpflat_combined.root
cd ..
cmsRun moveflatparamstodb_cfg.py print outputFile=HeavyIonRPRcd_PbPb2015_263615_263757.db outputTag=HeavyIonRPRcd begin=263615 end=263757
rm /rfs/sanders/tmpPbPb
rm save/EP_PbPb2015_263615_263757.root
mv /rfs/sanders/EPPbPb.root save/EP_PbPb2015_263615_263757.root
rm  -rf RescorSave/RescorTables_PbPb2015_263615_263757
mv RescorTables RescorSave/RescorTables_PbPb2015_263615_263757

conddb_import -f sqlite_file:HeavyIonRPRcd_PbPb2015_1_262799.db -c sqlite_file:HeavyIonRPRcd_PbPb2015_offline.db -i HeavyIonRPRcd -t HeavyIonRPRcd_PbPb2015_offline -b 1 -e 262799
conddb_import -f sqlite_file:HeavyIonRPRcd_PbPb2015_262800_263230.db -c sqlite_file:HeavyIonRPRcd_PbPb2015_offline.db -i HeavyIonRPRcd -t HeavyIonRPRcd_PbPb2015_offline -b 262800 -e 263230
conddb_import -f sqlite_file:HeavyIonRPRcd_PbPb2015_263231_263359.db -c sqlite_file:HeavyIonRPRcd_PbPb2015_offline.db -i HeavyIonRPRcd -t HeavyIonRPRcd_PbPb2015_offline -b 263231 -e 263359
conddb_import -f sqlite_file:HeavyIonRPRcd_PbPb2015_263360_263379.db -c sqlite_file:HeavyIonRPRcd_PbPb2015_offline.db -i HeavyIonRPRcd -t HeavyIonRPRcd_PbPb2015_offline -b 263360 -e 263379
conddb_import -f sqlite_file:HeavyIonRPRcd_PbPb2015_263380_263614.db -c sqlite_file:HeavyIonRPRcd_PbPb2015_offline.db -i HeavyIonRPRcd -t HeavyIonRPRcd_PbPb2015_offline -b 263380 -e 263614
conddb_import -f sqlite_file:HeavyIonRPRcd_PbPb2015_263615_263757.db -c sqlite_file:HeavyIonRPRcd_PbPb2015_offline.db -i HeavyIonRPRcd -t HeavyIonRPRcd_PbPb2015_offline -b 263615 -e 263757

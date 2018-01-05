from WMCore.Configuration import Configuration
config = Configuration()
from CRABClient.UserUtilities import getUsernameFromSiteDB
config.section_('General')
config.General.requestName = 'PbPb_2015_calib_262548_262799'
config.General.transferOutputs = True
config.General.transferLogs = True
config.section_('JobType')
config.JobType.outputFiles = ['calib.root']
config.JobType.pyCfgParams = ['noprint']
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/home/sanders/PbPb_2015/CalibTree/calibtree_cfg.py'
config.JobType.maxJobRuntimeMin = 1315
config.section_('Data')
config.Data.allowNonValidInputDataset = True
config.Data.inputDataset = '/HIMinimumBias2/HIRun2015-25Aug2016-v1/AOD'
config.Data.runRange = '262548-262799'
config.Data.unitsPerJob = 30
config.Data.publication = False
config.Data.splitting = 'LumiBased'
config.Data.outLFNDirBase = '/store/user/ssanders/PbPb_2015_calib_262548_262799'
config.Data.lumiMask = 'Cert_262548-263757_PromptReco_HICollisions15_JSON.txt'
config.section_('User')
config.section_('Site')
config.Site.storageSite = 'T2_US_Vanderbilt'

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab_projects'

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException, hte:
            print hte.headers

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################
#submit(config)


config.Data.runRange = '262800-263230'
config.General.requestName = 'PbPb_2015_calib_262800_263230'
config.Data.outLFNDirBase = '/store/user/ssanders/PbPb_2015_calib_262800_263230'
#submit(config)

config.Data.runRange = '263231-263359'
config.General.requestName = 'PbPb_2015_calib_263231_263359'
config.Data.outLFNDirBase = '/store/user/ssanders/PbPb_2015_calib_263231_263359'
#submit(config)

config.Data.runRange = '263360-263379'
config.General.requestName = 'PbPb_2015_calib_263360_263379'
config.Data.outLFNDirBase = '/store/user/ssanders/PbPb_2015_calib_263360_263379'
#submit(config)

config.Data.runRange = '263380-263614'
config.General.requestName = 'PbPb_2015_calib_263380_263614'
config.Data.outLFNDirBase = '/store/user/ssanders/PbPb_2015_calib_263380_263614'
#submit(config)

config.Data.runRange = '263615-263757'
config.General.requestName = 'PbPb_2015_calib_263615_263757'
config.JobType.pyCfgParams = ['noprint','lumifile=Cert_263685-263757_PromptReco_HICollisions15_TrackerOnly_JSON.txt']
config.Data.lumiMask = 'Cert_263685-263757_PromptReco_HICollisions15_TrackerOnly_JSON.txt'
config.Data.outLFNDirBase = '/store/user/ssanders/PbPb_2015_calib_263615_263757'
submit(config)

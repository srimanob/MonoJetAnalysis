//////////////////////////////////////////////////////////////////////
//                                                                  //
//          Author:  Mehmet Vergili   vergili@cern.ch               //
//                                                                  //
//////////////////////////////////////////////////////////////////////
#include "EventData.h"
#include <iostream>
#include "time.h"
#include <TH1D.h>
#include "Operation.h"
#include "string.h"
#include <map>
#include <LHAPDF/LHAPDF.h>

using namespace std;
using namespace Operation;
using namespace LHAPDF;

EventData::EventData(const string &  fileName, UInt_t maxEvents, int isMC) : mDataSet("undefined") 
{
  string fileDirectory  = "root://eoscms//eos/cms/store/group/phys_exotica/monojet/ntuple-2012-v6A/";

  // Pileup
  mydataset["pileup"]   = "/afs/cern.ch/user/s/srimanob/public/ForMonoJet/PUHist/pileup_monojet_20130101_All2012_v6A.root";
  
  // Data
  mydataset["met1"]     = fileDirectory + "Data_V6A_2012A_part1.root";
  mydataset["met2"]     = fileDirectory + "Data_V6A_2012A_part2.root";
  mydataset["met3"]     = fileDirectory + "Data_V6A_2012A_part3.root";
  mydataset["met4"]     = fileDirectory + "Data_V6A_2012B_part1.root";
  mydataset["met5"]     = fileDirectory + "Data_V6A_2012B_part2.root";
  mydataset["met6"]     = fileDirectory + "Data_V6A_2012B_part3.root";
  mydataset["met7"]     = fileDirectory + "Data_V6A_2012B_part4.root";
  mydataset["met8"]     = fileDirectory + "Data_V6A_2012B_part5.root";
  mydataset["met9"]     = fileDirectory + "Data_V6A_2012C_part1.root";
  mydataset["met10"]    = fileDirectory + "Data_V6A_2012C_part2.root";
  mydataset["met11"]    = fileDirectory + "Data_V6A_2012C_part3.root";
  mydataset["met12"]    = fileDirectory + "Data_V6A_2012C_part4.root";
  mydataset["met13"]    = fileDirectory + "Data_V6A_2012C_part5.root";
  mydataset["met14"]    = fileDirectory + "Data_V6A_2012C_part6.root";
  mydataset["met15"]    = fileDirectory + "Data_V6A_2012C_part7.root";
  mydataset["met16"]    = fileDirectory + "Data_V6A_2012C_part8.root";
  mydataset["met17"]    = fileDirectory + "Data_V6A_2012D_part1.root";
  mydataset["met18"]    = fileDirectory + "Data_V6A_2012D_part2.root";
  mydataset["met19"]    = fileDirectory + "Data_V6A_2012D_part3.root";
  mydataset["met20"]    = fileDirectory + "Data_V6A_2012D_part4.root";
  mydataset["met21"]    = fileDirectory + "Data_V6A_2012D_part5.root";
  mydataset["met22"]    = fileDirectory + "Data_V6A_2012D_part6.root";
  mydataset["met23"]    = fileDirectory + "Data_V6A_2012D_part7.root";
  mydataset["met24"]    = fileDirectory + "Data_V6A_2012D_part8.root";
  mydataset["met25"]    = fileDirectory + "Data_V6A_2012D_part9.root";
  mylumi["met1"]        = 19461.;
  mylumi["met2"]        = 19461.;
  mylumi["met3"]        = 19461.;
  mylumi["met4"]        = 19461.;
  mylumi["met5"]        = 19461.;
  mylumi["met6"]        = 19461.;
  mylumi["met7"]        = 19461.;   
  mylumi["met8"]        = 19461.;
  mylumi["met9"]        = 19461.;
  mylumi["met10"]       = 19461.;
  mylumi["met11"]       = 19461.;
  mylumi["met12"]       = 19461.;
  mylumi["met13"]       = 19461.;
  mylumi["met14"]       = 19461.;
  mylumi["met15"]       = 19461.;
  mylumi["met16"]       = 19461.;
  
  // Znunu S10
  mydataset["znunu50"]    = fileDirectory + "MC_S10_V6A_ZJetsToNuNu_50_HT_100_10601pb.root";
  mydataset["znunu100"]   = fileDirectory + "MC_S10_V6A_ZJetsToNuNu_100_HT_200_27552pb.root";
  mydataset["znunu200p1"] = fileDirectory + "MC_S10_V6A_ZJetsToNuNu_200_HT_400_part1_121829pb.root";
  mydataset["znunu200p2"] = fileDirectory + "MC_S10_V6A_ZJetsToNuNu_200_HT_400_part2_121829pb.root";
  mydataset["znunu400"]   = fileDirectory + "MC_S10_V6A_ZJetsToNuNu_400_HT_inf_189986pb.root";
  mylumi["znunu50"]       = 10601.;
  mylumi["znunu100"]      = 27552.;
  mylumi["znunu200"]      = 121829.;
  mylumi["znunu400"]      = 189986.; 
   
  // W+Jets S10
  mydataset["wjets1"]    = fileDirectory + "MC_S10_V6A_WJetsToLNu_PtW-100_part1_55668pb.root";
  mydataset["wjets2"]    = fileDirectory + "MC_S10_V6A_WJetsToLNu_PtW-100_part2_55668pb.root";
  mydataset["wjets3"]    = fileDirectory + "MC_S10_V6A_WJetsToLNu_PtW-100_part3_55668pb.root";
  mydataset["wjets4"]    = fileDirectory + "MC_S10_V6A_WJetsToLNu_PtW-100_part4_55668pb.root";
  mydataset["wjets5"]    = fileDirectory + "MC_S10_V6A_WJetsToLNu_PtW-100_part5_55668pb.root";
  mylumi["wjets1"]       = 55668.;
  mylumi["wjets2"]       = 55668.;
  mylumi["wjets3"]       = 55668.;
  mylumi["wjets4"]       = 55668.;
  mylumi["wjets5"]       = 55668.;
  
  // Z+Jets S10
  mydataset["zjets1"]     = fileDirectory + "MC_S10_V6A_DYJetsToLL_M-50_8624pb.root";
  mydataset["zjets2"]     = fileDirectory + "MC_S10_V6A_DYJetsToLL_PtZ-100_77335pb.root";
  mylumi["zjets1"]        = 8624.;
  mylumi["zjets2"]        = 77335.;
  
  // TTbar S10
  mydataset["ttbar"]     = fileDirectory + "MC_S10_V6A_TTbar_MassiveBin_50798pb.root";
  mylumi["ttbar"]        = 50798.;
  
  // QCD S10
  mydataset["qcd300"]   = fileDirectory + "MC_S10_V6A_QCD_Pt-300to470_3398pb.root";
  mydataset["qcd470"]   = fileDirectory + "MC_S10_V6A_QCD_Pt-470to600_35080pb.root";
  mydataset["qcd600"]   = fileDirectory + "MC_S10_V6A_QCD_Pt-600to800_148032pb.root";
  mydataset["qcd800"]   = fileDirectory + "MC_S10_V6A_QCD_Pt-800to1000_1110712pb.root";
  mydataset["qcd1000"]  = fileDirectory + "MC_S10_V6A_QCD_Pt-1000to1400_2654173pb.root";
  mydataset["qcd1400"]  = fileDirectory + "MC_S10_V6A_QCD_Pt-1400to1800_58090059pb.root";
  mydataset["qcd1800"]  = fileDirectory + "MC_S10_V6A_QCD_Pt-1800toInf_543103333pb.root";
  mylumi["qcd300"]      = 3398.;
  mylumi["qcd470"]      = 35080.;
  mylumi["qcd600"]      = 148032.;
  mylumi["qcd800"]      = 1110712.;
  mylumi["qcd1000"]     = 2654173.;
  mylumi["qcd1400"]     = 58090059.;
  mylumi["qcd1800"]     = 543103333.;
  
  // Single-t S10
  mydataset["sints"]       = fileDirectory + "MC_S10_V6A_SingleT_s_92843pb.root";
  mydataset["sintt"]       = fileDirectory + "MC_S10_V6A_SingleT_t_79430pb.root";
  mydataset["sinttw"]      = fileDirectory + "MC_S10_V6A_SingleT_tw_44524pb.root";
  mydataset["sintbars"]    = fileDirectory + "MC_S10_V6A_SingleTbar_s_87484pb.root";
  mydataset["sintbart"]    = fileDirectory + "MC_S10_V6A_SingleTbar_t_77403pb.root";
  mydataset["sintbartw"]   = fileDirectory + "MC_S10_V6A_SingleTbar_tw_44148pb.root";
  mylumi["sints"]          = 92843.;
  mylumi["sintt"]          = 79430.;
  mylumi["sinttw"]         = 44524.;
  mylumi["sintbars"]       = 87484.;
  mylumi["sintbart"]       = 77403.;
  mylumi["sintbartw"]      = 44148.;
  
  // VBF-Invisible Higgs
  mydataset["vbf"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/VBF_InvisibleHiggs.root";
  mylumi["vbf"]  = 12100.;
  
  
  // DM-Stop / DM-Higgs
  mydataset["dmstop"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/DarkMatter/DM_Stop_mass210GeV_M230GeV_Lumi_98948pb.root";
  mydataset["dmhiggs"]  = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/DarkMatter/DM_Higgs_massXXXGeV_M125GeV_Lumi_8336pb.root";
  mylumi["dmstop"]      = 60803.;
  mylumi["dmhiggs"]     = 8336.;
  
  
  // Unparticles
  mydataset["unp_S0_dU1p5_LU6000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p5_LU6000_v3_8045pb.root";
  mydataset["unp_S0_dU1p5_LU7000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p5_LU7000_v3_9433pb.root";
  mydataset["unp_S0_dU1p5_LU8000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p5_LU8000_v3_10902pb.root";
  mydataset["unp_S0_dU1p5_LU9000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p5_LU9000_v3_12176pb.root";
  mydataset["unp_S0_dU1p6_LU4000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p6_LU4000_v3_15913pb.root";
  mydataset["unp_S0_dU1p6_LU5000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p6_LU5000_v3_21272pb.root";
  mydataset["unp_S0_dU1p6_LU6000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p6_LU6000_v3_27159pb.root";
  mydataset["unp_S0_dU1p6_LU7000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p6_LU7000_v3_33367pb.root";
  mydataset["unp_S0_dU1p7_LU1000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p7_LU1000_v3_2784pb.root";
  mydataset["unp_S0_dU1p7_LU2000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p7_LU2000_v3_13802pb.root";
  mydataset["unp_S0_dU1p7_LU3000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p7_LU3000_v3_29718pb.root"; 
  mydataset["unp_S0_dU1p8_LU1000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p8_LU1000_v3_6139pb.root";
  mydataset["unp_S0_dU1p8_LU2000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p8_LU2000_v3_35561pb.root";
  mydataset["unp_S0_dU1p8_LU3000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p8_LU3000_v3_86132pb.root"; 
  mydataset["unp_S0_dU1p9_LU1000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p9_LU1000_v3_13526pb.root";
  mydataset["unp_S0_dU1p9_LU2000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p9_LU2000_v3_95602pb.root";
  mydataset["unp_S0_dU1p9_LU3000"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p9_LU3000_v3_244798pb.root";
  //
  mylumi["unp_S0_dU1p5_LU6000"] = 8045.;
  mylumi["unp_S0_dU1p5_LU7000"] = 9433.;
  mylumi["unp_S0_dU1p5_LU8000"] = 10902.;
  mylumi["unp_S0_dU1p5_LU9000"] = 12176.;
  mylumi["unp_S0_dU1p6_LU4000"] = 15913.;
  mylumi["unp_S0_dU1p6_LU5000"] = 21272.;
  mylumi["unp_S0_dU1p6_LU6000"] = 27159.;
  mylumi["unp_S0_dU1p6_LU7000"] = 33367.;
  mylumi["unp_S0_dU1p7_LU1000"] = 2784.;
  mylumi["unp_S0_dU1p7_LU2000"] = 13802.;
  mylumi["unp_S0_dU1p7_LU3000"] = 29718.;
  mylumi["unp_S0_dU1p8_LU1000"] = 6139.;
  mylumi["unp_S0_dU1p8_LU2000"] = 35561.;
  mylumi["unp_S0_dU1p8_LU3000"] = 86132.;
  mylumi["unp_S0_dU1p9_LU1000"] = 13526.;
  mylumi["unp_S0_dU1p9_LU2000"] = 95602.;
  mylumi["unp_S0_dU1p9_LU3000"] = 244798.; 

  //mydataset["unp_S0_dU1p5_LU6000_ft0"]   = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/UNP_8TeV_v3/Unparticle_S0_dU1p5_LU6000_v3_8045pb_fixType0.root";
  //mylumi["unp_S0_dU1p5_LU6000_ft0"] = 8045.; 
  
  // ADD Model Samples 
  mydataset["d2md3"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D2_MD3000_v3_13065pb.root";
  mydataset["d2md4"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D2_MD4000_v3_40866pb.root";
  mydataset["d2md5"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D2_MD5000_v3_101419pb.root";
  mydataset["d2md6"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D2_MD6000_v3_206611pb.root";
  mydataset["d3md2"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D3_MD2000_v3_5219pb.root";
  mydataset["d3md3"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D3_MD3000_v3_37807pb.root";
  mydataset["d3md4"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D3_MD4000_v3_159438pb.root";
  mydataset["d3md5"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D3_MD5000_v3_465116pb.root"; 
  mydataset["d4md2"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D4_MD2000_v3_8045pb.root";
  mydataset["d4md3"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D4_MD3000_v3_77101pb.root"; 
  mydataset["d4md4"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D4_MD4000_v3_408163pb.root";
  mydataset["d4md5"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D4_MD5000_v3_1612903pb.root";
  mydataset["d5md1"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D5_MD1000_v3_298pb.root";
  mydataset["d5md2"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D5_MD2000_v3_11222pb.root";
  mydataset["d5md3"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D5_MD3000_v3_134048pb.root";
  mydataset["d5md4"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D5_MD4000_v3_937207pb.root";
  mydataset["d6md1"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D6_MD1000_v3_283pb.root";
  mydataset["d6md2"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D6_MD2000_v3_12692pb.root"; 
  mydataset["d6md3"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D6_MD3000_v3_190476pb.root";
  mydataset["d6md4"]    = "file:/data0/srimanob/Data/monojet/ntuple-2012-v2/ADD_8TeV_v3/ADD_D6_MD4000_v3_1724137pb.root"; 
  //
  mylumi["d2md3"]    = 13065.;
  mylumi["d2md4"]    = 40866.;
  mylumi["d2md5"]    = 101419.;
  mylumi["d2md6"]    = 206611.;
  mylumi["d3md2"]    = 5219.;
  mylumi["d3md3"]    = 37807.;
  mylumi["d3md4"]    = 159438.;
  mylumi["d3md5"]    = 465116.; 
  mylumi["d4md2"]    = 8045.;
  mylumi["d4md3"]    = 77101.; 
  mylumi["d4md4"]    = 408163.;
  mylumi["d4md5"]    = 1612903.;
  mylumi["d5md1"]    = 298.;
  mylumi["d5md2"]    = 11222.;
  mylumi["d5md3"]    = 134048.;
  mylumi["d5md4"]    = 937207.;
  mylumi["d6md1"]    = 283.;
  mylumi["d6md2"]    = 12692.; 
  mylumi["d6md3"]    = 190476.;
  mylumi["d6md4"]    = 1724137.;

  
  //Dark Matter
  mydataset["dmavd001"]   = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVd_mass001GeV_M40TeV_madgraph.root";
  mydataset["dmavd01"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVd_mass01GeV_M40TeV_madgraph.root";
  mydataset["dmavd1"]     = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVd_mass1GeV_M40TeV_madgraph.root";
  mydataset["dmavd10"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVd_mass10GeV_M40TeV_madgraph.root";
  mydataset["dmavd100"]   = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVd_mass100GeV_M40TeV_madgraph.root";
  mydataset["dmavd200"]   = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVd_mass200GeV_M40TeV_madgraph.root";
  mydataset["dmavd300"]   = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVd_mass300GeV_M40TeV_madgraph.root";
  mydataset["dmavd400"]   = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVd_mass400GeV_M40TeV_madgraph.root";
  mydataset["dmavd700"]   = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVd_mass700GeV_M40TeV_madgraph.root";
  mydataset["dmavd1000"]  = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVd_mass1000GeV_M40TeV_madgraph.root";
  //
  mydataset["dmavu001"]   = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVu_mass001GeV_M40TeV_madgraph.root";
  mydataset["dmavu01"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVu_mass01GeV_M40TeV_madgraph.root";
  mydataset["dmavu1"]     = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVu_mass1GeV_M40TeV_madgraph.root";
  mydataset["dmavu10"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVu_mass10GeV_M40TeV_madgraph.root";
  mydataset["dmavu100"]   = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVu_mass100GeV_M40TeV_madgraph.root";
  mydataset["dmavu200"]   = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVu_mass200GeV_M40TeV_madgraph.root";
  mydataset["dmavu300"]   = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVu_mass300GeV_M40TeV_madgraph.root";
  mydataset["dmavu400"]   = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVu_mass400GeV_M40TeV_madgraph.root";
  mydataset["dmavu700"]   = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVu_mass700GeV_M40TeV_madgraph.root";
  mydataset["dmavu1000"]  = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_AVu_mass1000GeV_M40TeV_madgraph.root";
  //
  mydataset["dmvd001"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vd_mass001GeV_M40TeV_madgraph.root";
  mydataset["dmvd01"]     = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vd_mass01GeV_M40TeV_madgraph.root";
  mydataset["dmvd1"]      = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vd_mass1GeV_M40TeV_madgraph.root";
  mydataset["dmvd10"]     = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vd_mass10GeV_M40TeV_madgraph.root";
  mydataset["dmvd100"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vd_mass100GeV_M40TeV_madgraph.root";
  mydataset["dmvd200"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vd_mass200GeV_M40TeV_madgraph.root";
  mydataset["dmvd300"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vd_mass300GeV_M40TeV_madgraph.root";
  mydataset["dmvd400"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vd_mass400GeV_M40TeV_madgraph.root";
  mydataset["dmvd700"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vd_mass700GeV_M40TeV_madgraph.root";
  mydataset["dmvd1000"]   = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vd_mass1000GeV_M40TeV_madgraph.root";
  //
  mydataset["dmvu001"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vu_mass001GeV_M40TeV_madgraph.root";
  mydataset["dmvu01"]     = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vu_mass01GeV_M40TeV_madgraph.root";
  mydataset["dmvu1"]      = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vu_mass1GeV_M40TeV_madgraph.root";
  mydataset["dmvu10"]     = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vu_mass10GeV_M40TeV_madgraph.root";
  mydataset["dmvu100"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vu_mass100GeV_M40TeV_madgraph.root";
  mydataset["dmvu200"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vu_mass200GeV_M40TeV_madgraph.root";
  mydataset["dmvu300"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vu_mass300GeV_M40TeV_madgraph.root";
  mydataset["dmvu400"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vu_mass400GeV_M40TeV_madgraph.root";
  mydataset["dmvu700"]    = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vu_mass700GeV_M40TeV_madgraph.root";
  mydataset["dmvu1000"]   = "/uscms_data/d1/lpcjm/DATA/DarkMatter/DM_Vu_mass1000GeV_M40TeV_madgraph.root";
  //
  mylumi["dmavd001"]  = 8000.;
  mylumi["dmavd01"]   = 8000.;  
  mylumi["dmavd1"]    = 8000.; 
  mylumi["dmavd10"]   = 8000.;
  mylumi["dmavd100"]  = 8000.;
  mylumi["dmavd200"]  = 8000.;
  mylumi["dmavd300"]  = 8000.;
  mylumi["dmavd400"]  = 8000.;
  mylumi["dmavd700"]  = 8000.;
  mylumi["dmavd1000"] = 8000.;
  //
  mylumi["dmavu001"]  = 8000.;
  mylumi["dmavu01"]   = 8000.;
  mylumi["dmavu1"]    = 8000.;
  mylumi["dmavu10"]   = 8000.;
  mylumi["dmavu100"]  = 8000.;
  mylumi["dmavu200"]  = 8000.;
  mylumi["dmavu300"]  = 8000.;
  mylumi["dmavu400"]  = 8000.;
  mylumi["dmavu700"]  = 8000.;
  mylumi["dmavu1000"] = 8000.;
  //
  mylumi["dmvd001"]  =  8000.;
  mylumi["dmvd01"]   =  8000.;
  mylumi["dmvd1"]    =  8000.;
  mylumi["dmvd10"]   =  8000.;
  mylumi["dmvd100"]  =  8000.;
  mylumi["dmvd200"]  =  8000.;
  mylumi["dmvd300"]  =  8000.;
  mylumi["dmvd400"]  =  8000.;
  mylumi["dmvd700"]  =  8000.;
  mylumi["dmvd1000"] =  8000.;
  //
  mylumi["dmvu001"]  =  8000.;
  mylumi["dmvu01"]   =  8000.;
  mylumi["dmvu1"]    =  8000.;
  mylumi["dmvu10"]   =  8000.;
  mylumi["dmvu100"]  =  8000.;
  mylumi["dmvu200"]  =  8000.;
  mylumi["dmvu300"]  =  8000.;
  mylumi["dmvu400"]  =  8000.;
  mylumi["dmvu700"]  =  8000.;
  mylumi["dmvu1000"] =  8000.;

	

	mEvent = 0;
	mMaxEvents = maxEvents;
	mFileName = fileName; 

	misMC = isMC;
	
	mJetType = "pf";
	mLepType = "m";

	mMetType = 10;

	mEnergyScale = 0.;
	
	mSecJetCut   = 30;

	
	
	TFile f1( mydataset["pileup"].c_str()  );
	TH1D *his = (TH1D*) f1.Get("pileup")->Clone();
	    
	mPileUpWeights = generate_flat10_weights(his);

	//setPDFPath("/uscmst1/prod/sw/cms/slc5_amd64_gcc434/external/lhapdf/5.6.0-cms4/share/lhapdf/PDFsets");
	//initPDFSet(1, "cteq66.LHgrid");
	//initPDFSet(2, "cteq66alphas.LHgrid"); //  alphaS uncert +/-

	//initPDFSet(3, "MSTW2008nlo68cl.LHgrid");
	//initPDFSet(2, "MSTW2008nlo68cl_asmz-68cl.LHgrid"); // alphaS uncert +
	//initPDFSet(3, "MSTW2008nlo68cl_asmz+68cl.LHgrid");  // alphaS uncert -

	//initPDFSet(1, "NNPDF20_100.LHgrid");
	//initPDFSet(2, "NNPDF20_100.LHgrid");
	//initPDFSet(3, "NNPDF20_100.LHgrid");


	///-------------Ntuple Variables --------------------------------------------------------------------------
	
	TFile* file = TFile::Open( mydataset[fileName].c_str() );
	TDirectory* myDir = (TDirectory*)file->Get("NtupleAnalyzer");
	mDataTree = (TTree*) myDir->Get("ntuple");

	mDataTree->SetBranchAddress("PDFWeights1", &mPDFWeights);

	mDataTree->SetBranchAddress("run"                                   ,&mrun                        );
	mDataTree->SetBranchAddress("event"                                 ,&mevent                      );
	mDataTree->SetBranchAddress("lumi"                                  ,&mlumi                       );
	mDataTree->SetBranchAddress("bx"                                    ,&mbx                         );
	mDataTree->SetBranchAddress("npvm1"                                 ,&mnpvm1                      );
	mDataTree->SetBranchAddress("npv0"                                  ,&mnpv0                       );
	mDataTree->SetBranchAddress("npvp1"                                 ,&mnpvp1                      );
	mDataTree->SetBranchAddress("ptHat"                                 ,&mptHat                      );
	
	mDataTree->SetBranchAddress("NoiseFlag"                             ,mNoiseFlag                   );

	mDataTree->SetBranchAddress("CaloTowerdEx"                          ,&mCaloTowerdEx               );
	mDataTree->SetBranchAddress("CaloTowerdEy"                          ,&mCaloTowerdEy               );

		
	mDataTree->SetBranchAddress("NCaloAK5Jets"                          ,&mNCaloAK5Jets               );
	mDataTree->SetBranchAddress("CaloAK5JetE"                           ,mCaloAK5JetE                 );
	mDataTree->SetBranchAddress("CaloAK5JetPt"                          ,mCaloAK5JetPt                );
	mDataTree->SetBranchAddress("CaloAK5JetPx"                          ,mCaloAK5JetPx                );
	mDataTree->SetBranchAddress("CaloAK5JetPy"                          ,mCaloAK5JetPy                );
	mDataTree->SetBranchAddress("CaloAK5JetPz"                          ,mCaloAK5JetPz                );
	mDataTree->SetBranchAddress("CaloAK5JetEta"                         ,mCaloAK5JetEta               );
	mDataTree->SetBranchAddress("CaloAK5JetPhi"                         ,mCaloAK5JetPhi               );
	mDataTree->SetBranchAddress("CaloAK5JetEmf"                         ,mCaloAK5JetEmf               );
	mDataTree->SetBranchAddress("CaloAK5JetfHPD"                        ,mCaloAK5JetfHPD              );
	mDataTree->SetBranchAddress("CaloAK5JetfRBX"                        ,mCaloAK5JetfRBX              );
	mDataTree->SetBranchAddress("CaloAK5JetN90Hits"                     ,mCaloAK5JetN90Hits           );
	mDataTree->SetBranchAddress("CaloAK5JetN90"                         ,mCaloAK5JetN90               );
	mDataTree->SetBranchAddress("CaloAK5JetSigEta"                      ,mCaloAK5JetSigEta            );
	mDataTree->SetBranchAddress("CaloAK5JetSigPhi"                      ,mCaloAK5JetSigPhi            );
	mDataTree->SetBranchAddress("CaloAK5JetIDEmf"                       ,mCaloAK5JetIDEmf             );
	mDataTree->SetBranchAddress("CaloAK5JetECor"                        ,mCaloAK5JetECor              );
	mDataTree->SetBranchAddress("CaloAK5JetPtCor"                       ,mCaloAK5JetPtCor             );
	mDataTree->SetBranchAddress("CaloAK5JetPxCor"                       ,mCaloAK5JetPxCor             );
	mDataTree->SetBranchAddress("CaloAK5JetPyCor"                       ,mCaloAK5JetPyCor             );
	mDataTree->SetBranchAddress("CaloAK5JetPzCor"                       ,mCaloAK5JetPzCor             );
	mDataTree->SetBranchAddress("CaloAK5JetBtagTkCountHighEff"          ,mCaloAK5JetBtagTkCountHighEff);
	mDataTree->SetBranchAddress("CaloAK5JetBTagSimpleSecVtx"            ,mCaloAK5JetBTagSimpleSecVtx  );
	mDataTree->SetBranchAddress("CaloAK5JetBTagCombSecVtx"              ,mCaloAK5JetBTagCombSecVtx    );
	mDataTree->SetBranchAddress("CaloAK5TrackPt"                        ,mCaloAK5TrackPt              );
	mDataTree->SetBranchAddress("CaloAK5JetIDLOOSE"                     ,mCaloAK5JetIDLOOSE           );
	mDataTree->SetBranchAddress("CaloAK5JetIDTIGHT"                     ,mCaloAK5JetIDTIGHT           );
		
	mDataTree->SetBranchAddress("NPFAK5Jets"                            ,&mNPFAK5Jets                ); 
	mDataTree->SetBranchAddress("PFAK5JetE"                             ,mPFAK5JetE                  ); 
	mDataTree->SetBranchAddress("PFAK5JetPt"                            ,mPFAK5JetPt                 ); 
	mDataTree->SetBranchAddress("PFAK5JetPx"                            ,mPFAK5JetPx                 ); 
	mDataTree->SetBranchAddress("PFAK5JetPy"                            ,mPFAK5JetPy                 ); 
	mDataTree->SetBranchAddress("PFAK5JetPz"                            ,mPFAK5JetPz                 ); 
	mDataTree->SetBranchAddress("PFAK5JetEta"                           ,mPFAK5JetEta                ); 
	mDataTree->SetBranchAddress("PFAK5JetPhi"                           ,mPFAK5JetPhi                ); 
	mDataTree->SetBranchAddress("PFAK5JetfHPD"                          ,mPFAK5JetfHPD               ); 
	mDataTree->SetBranchAddress("PFAK5JetfRBX"                          ,mPFAK5JetfRBX               ); 
	mDataTree->SetBranchAddress("PFAK5JetN90Hits"                       ,mPFAK5JetN90Hits            ); 
	mDataTree->SetBranchAddress("PFAK5JetN90"                           ,mPFAK5JetN90                ); 
	mDataTree->SetBranchAddress("PFAK5JetSigEta"                        ,mPFAK5JetSigEta             ); 
	mDataTree->SetBranchAddress("PFAK5JetSigPhi"                        ,mPFAK5JetSigPhi             ); 
	mDataTree->SetBranchAddress("PFAK5JetIDEmf"                         ,mPFAK5JetIDEmf              ); 
	mDataTree->SetBranchAddress("PFAK5JetECor"                          ,mPFAK5JetECor               ); 
	mDataTree->SetBranchAddress("PFAK5JetPtCor"                         ,mPFAK5JetPtCor              ); 
	mDataTree->SetBranchAddress("PFAK5JetPxCor"                         ,mPFAK5JetPxCor              ); 
	mDataTree->SetBranchAddress("PFAK5JetPyCor"                         ,mPFAK5JetPyCor              ); 
	mDataTree->SetBranchAddress("PFAK5JetPzCor"                         ,mPFAK5JetPzCor              ); 
	mDataTree->SetBranchAddress("PFAK5JetBtagTkCountHighEff"            ,mPFAK5JetBtagTkCountHighEff ); 
	mDataTree->SetBranchAddress("PFAK5JetBTagSimpleSecVtx"              ,mPFAK5JetBTagSimpleSecVtx   ); 
	mDataTree->SetBranchAddress("PFAK5JetBTagCombSecVtx"                ,mPFAK5JetBTagCombSecVtx     ); 
	mDataTree->SetBranchAddress("PFAK5JetNeuEmEngFrac"                  ,mPFAK5JetNeuEmEngFrac       ); 
	mDataTree->SetBranchAddress("PFAK5JetChaEmEngFrac"                  ,mPFAK5JetChaEmEngFrac       ); 
	mDataTree->SetBranchAddress("PFAK5JetChaHadEngFrac"                 ,mPFAK5JetChaHadEngFrac      ); 
	mDataTree->SetBranchAddress("PFAK5JetNeuHadEngFrac"                 ,mPFAK5JetNeuHadEngFrac      ); 
	mDataTree->SetBranchAddress("PFAK5JetChaMuEng"                      ,mPFAK5JetChaMuEng           ); 
	mDataTree->SetBranchAddress("PFAK5JetMuonEng"                       ,mPFAK5JetMuonEng            ); 
	mDataTree->SetBranchAddress("PFAK5JetPhotEng"                       ,mPFAK5JetPhotEng            ); 
	mDataTree->SetBranchAddress("PFAK5JetElecEng"                       ,mPFAK5JetElecEng            ); 
	mDataTree->SetBranchAddress("PFAK5JetNumOfChaMu"                    ,mPFAK5JetNumOfChaMu         ); 
	mDataTree->SetBranchAddress("PFAK5JetNumOfMuon"                     ,mPFAK5JetNumOfMuon          ); 
	mDataTree->SetBranchAddress("PFAK5JetNumOfPhot"                     ,mPFAK5JetNumOfPhot          ); 
	mDataTree->SetBranchAddress("PFAK5JetNumOfElec"                     ,mPFAK5JetNumOfElec          ); 
	mDataTree->SetBranchAddress("PFAK5JetNumOfNeu"                      ,mPFAK5JetNumOfNeu           ); 
	mDataTree->SetBranchAddress("PFAK5JetNumOfCha"                      ,mPFAK5JetNumOfCha           ); 
	mDataTree->SetBranchAddress("PFAK5JetNumOfNeuHad"                   ,mPFAK5JetNumOfNeuHad        ); 
	mDataTree->SetBranchAddress("PFAK5JetNumOfChaHad"                   ,mPFAK5JetNumOfChaHad        ); 
	mDataTree->SetBranchAddress("PFAK5JetNumOfDaughters"                ,mPFAK5JetNumOfDaughters     ); 
	mDataTree->SetBranchAddress("PFAK5JetIDLOOSE"                       ,mPFAK5JetIDLOOSE            ); 
	mDataTree->SetBranchAddress("PFAK5JetIDTIGHT"                       ,mPFAK5JetIDTIGHT            ); 
	mDataTree->SetBranchAddress("PFAK5uncer"                            ,mPFAK5uncer                 );
																								
																								
	mDataTree->SetBranchAddress("NMet"                                  ,&mNMet                      ); 
	mDataTree->SetBranchAddress("MetPt"                                 ,mMetPt                      ); 
	mDataTree->SetBranchAddress("MetPx"                                 ,mMetPx                      ); 
	mDataTree->SetBranchAddress("MetPy"                                 ,mMetPy                      ); 
	mDataTree->SetBranchAddress("MetPhi"                                ,mMetPhi                     ); 
	mDataTree->SetBranchAddress("MetSumEt"                              ,mMetSumEt                   ); 
	mDataTree->SetBranchAddress("MetSign"                               ,mMetSign                    ); 


	mDataTree->SetBranchAddress("NMuon"                                 ,&mNMuon                     ); 
	mDataTree->SetBranchAddress("MuonPt"                                ,mMuonPt                     ); 
	mDataTree->SetBranchAddress("MuonEt"                                ,mMuonEt                     ); 
	mDataTree->SetBranchAddress("MuonE"                                 ,mMuonE                      ); 
	mDataTree->SetBranchAddress("MuonPx"                                ,mMuonPx                     ); 
	mDataTree->SetBranchAddress("MuonPy"                                ,mMuonPy                     ); 
	mDataTree->SetBranchAddress("MuonPz"                                ,mMuonPz                     ); 
	mDataTree->SetBranchAddress("MuonEta"                               ,mMuonEta                    ); 
	mDataTree->SetBranchAddress("MuonPhi"                               ,mMuonPhi                    ); 
	mDataTree->SetBranchAddress("MuonCharge"                            ,mMuonCharge                 ); 
	mDataTree->SetBranchAddress("MuonIsGlobal"                          ,mMuonIsGlobal               ); 
	mDataTree->SetBranchAddress("MuonIsStandAlone"                      ,mMuonIsStandAlone           ); 
	mDataTree->SetBranchAddress("MuonIsTracker"                         ,mMuonIsTracker              ); 
	mDataTree->SetBranchAddress("MuonSumPtDR03"                         ,mMuonSumPtDR03              ); 
	mDataTree->SetBranchAddress("MuonSumPtDR05"                         ,mMuonSumPtDR05              ); 
	mDataTree->SetBranchAddress("MuonEmEtDR03"                          ,mMuonEmEtDR03               ); 
	mDataTree->SetBranchAddress("MuonHadEtDR03"                         ,mMuonHadEtDR03              ); 
	mDataTree->SetBranchAddress("MuonNumOfMatches"                      ,mMuonNumOfMatches           ); 
	mDataTree->SetBranchAddress("MuonCombChi2Norm"                      ,mMuonCombChi2Norm           ); 
	mDataTree->SetBranchAddress("MuonCombValidHits"                     ,mMuonCombValidHits          ); 
	mDataTree->SetBranchAddress("MuonCombLostHits"                      ,mMuonCombLostHits           ); 
	mDataTree->SetBranchAddress("MuonCombPt"                            ,mMuonCombPt                 ); 
	mDataTree->SetBranchAddress("MuonCombPz"                            ,mMuonCombPz                 ); 
	mDataTree->SetBranchAddress("MuonCombP"                             ,mMuonCombP                  ); 
	mDataTree->SetBranchAddress("MuonCombEta"                           ,mMuonCombEta                ); 
	mDataTree->SetBranchAddress("MuonCombPhi"                           ,mMuonCombPhi                ); 
	mDataTree->SetBranchAddress("MuonCombChi2"                          ,mMuonCombChi2               ); 
	mDataTree->SetBranchAddress("MuonCombCharge"                        ,mMuonCombCharge             ); 
	mDataTree->SetBranchAddress("MuonCombQOverPError"                   ,mMuonCombQOverPError        ); 
	mDataTree->SetBranchAddress("MuonCombNdof"                          ,mMuonCombNdof               ); 
	mDataTree->SetBranchAddress("MuonCombVx"                            ,mMuonCombVx                 ); 
	mDataTree->SetBranchAddress("MuonCombVy"                            ,mMuonCombVy                 ); 
	mDataTree->SetBranchAddress("MuonCombVz"                            ,mMuonCombVz                 ); 
	mDataTree->SetBranchAddress("MuonCombD0"                            ,mMuonCombD0                 ); 
	mDataTree->SetBranchAddress("MuonCombDz"                            ,mMuonCombDz                 ); 
	mDataTree->SetBranchAddress("MuonStandChi2Norm"                     ,mMuonStandChi2Norm          ); 
	mDataTree->SetBranchAddress("MuonStandValidHits"                    ,mMuonStandValidHits         ); 
	mDataTree->SetBranchAddress("MuonStandLostHits"                     ,mMuonStandLostHits          ); 
	mDataTree->SetBranchAddress("MuonStandPt"                           ,mMuonStandPt                ); 
	mDataTree->SetBranchAddress("MuonStandPz"                           ,mMuonStandPz                ); 
	mDataTree->SetBranchAddress("MuonStandP"                            ,mMuonStandP                 ); 
	mDataTree->SetBranchAddress("MuonStandEta"                          ,mMuonStandEta               ); 
	mDataTree->SetBranchAddress("MuonStandPhi"                          ,mMuonStandPhi               ); 
	mDataTree->SetBranchAddress("MuonStandChi2"                         ,mMuonStandChi2              ); 
	mDataTree->SetBranchAddress("MuonStandCharge"                       ,mMuonStandCharge            ); 
	mDataTree->SetBranchAddress("MuonStandQOverPError"                  ,mMuonStandQOverPError       ); 
	mDataTree->SetBranchAddress("MuonTrkChi2Norm"                       ,mMuonTrkChi2Norm            ); 
	mDataTree->SetBranchAddress("MuonTrkValidHits"                      ,mMuonTrkValidHits           ); 
	mDataTree->SetBranchAddress("MuonTrkLostHits"                       ,mMuonTrkLostHits            ); 
	mDataTree->SetBranchAddress("MuonTrkPt"                             ,mMuonTrkPt                  ); 
	mDataTree->SetBranchAddress("MuonTrkPz"                             ,mMuonTrkPz                  ); 
	mDataTree->SetBranchAddress("MuonTrkP"                              ,mMuonTrkP                   ); 
	mDataTree->SetBranchAddress("MuonTrkEta"                            ,mMuonTrkEta                 ); 
	mDataTree->SetBranchAddress("MuonTrkPhi"                            ,mMuonTrkPhi                 ); 
	mDataTree->SetBranchAddress("MuonTrkChi2"                           ,mMuonTrkChi2                ); 
	mDataTree->SetBranchAddress("MuonTrkCharge"                         ,mMuonTrkCharge              ); 
	mDataTree->SetBranchAddress("MuonTrkQOverPError"                    ,mMuonTrkQOverPError         ); 
	mDataTree->SetBranchAddress("MuonTrkDxy"                            ,mMuonTrkDxy                 ); 
	mDataTree->SetBranchAddress("MuonTrkNumOfValidPixHits"              ,mMuonTrkNumOfValidPixHits   ); 
																									
	mDataTree->SetBranchAddress("NPFMuon"                               ,&mNPFMuon                  );  
	mDataTree->SetBranchAddress("PFMuonPt"                              ,mPFMuonPt                  );  
	mDataTree->SetBranchAddress("PFMuonEt"                              ,mPFMuonEt                  );  
	mDataTree->SetBranchAddress("PFMuonE"                               ,mPFMuonE                   );  
	mDataTree->SetBranchAddress("PFMuonPx"                              ,mPFMuonPx                  );  
	mDataTree->SetBranchAddress("PFMuonPy"                              ,mPFMuonPy                  );  
	mDataTree->SetBranchAddress("PFMuonPz"                              ,mPFMuonPz                  );  
	mDataTree->SetBranchAddress("PFMuonEta"                             ,mPFMuonEta                 );  
	mDataTree->SetBranchAddress("PFMuonPhi"                             ,mPFMuonPhi                 );  
	mDataTree->SetBranchAddress("PFMuonCharge"                          ,mPFMuonCharge              );  
	mDataTree->SetBranchAddress("PFMuonIsGlobal"                        ,mPFMuonIsGlobal            );  
	mDataTree->SetBranchAddress("PFMuonIsStandAlone"                    ,mPFMuonIsStandAlone        );  
	mDataTree->SetBranchAddress("PFMuonIsTracker"                       ,mPFMuonIsTracker           );  
	mDataTree->SetBranchAddress("PFMuonChargedHadronIso"                ,mPFMuonChargedHadronIso    );  
	mDataTree->SetBranchAddress("PFMuonPhotonIso"                       ,mPFMuonPhotonIso           );  
	mDataTree->SetBranchAddress("PFMuonNeutralHadronIso"                ,mPFMuonNeutralHadronIso    );  
	mDataTree->SetBranchAddress("PFMuonisGMPT"                          ,mPFMuonisGMPT              );  
	mDataTree->SetBranchAddress("PFMuonNumOfMatches"                    ,mPFMuonNumOfMatches        );  
	mDataTree->SetBranchAddress("PFMuoninnertrackPt"                    ,mPFMuoninnertrackPt        );  
	mDataTree->SetBranchAddress("PFMuonnValidHits"                      ,mPFMuonnValidHits          );  
	mDataTree->SetBranchAddress("PFMuonnValidPixelHits"                 ,mPFMuonnValidPixelHits     );  
	mDataTree->SetBranchAddress("PFMuondxy"                             ,mPFMuondxy                 );  
	mDataTree->SetBranchAddress("PFMuondz"                              ,mPFMuondz                  );  
	mDataTree->SetBranchAddress("PFMuonCombChi2Norm"                    ,mPFMuonCombChi2Norm        );  
	mDataTree->SetBranchAddress("PFMuonCombValidHits"                   ,mPFMuonCombValidHits       );  
	mDataTree->SetBranchAddress("PFMuonCombLostHits"                    ,mPFMuonCombLostHits        );  
	mDataTree->SetBranchAddress("PFMuonCombPt"                          ,mPFMuonCombPt              );  
	mDataTree->SetBranchAddress("PFMuonCombPz"                          ,mPFMuonCombPz              );  
	mDataTree->SetBranchAddress("PFMuonCombP"                           ,mPFMuonCombP               );  
	mDataTree->SetBranchAddress("PFMuonCombEta"                         ,mPFMuonCombEta             );  
	mDataTree->SetBranchAddress("PFMuonCombPhi"                         ,mPFMuonCombPhi             );  
	mDataTree->SetBranchAddress("PFMuonCombChi2"                        ,mPFMuonCombChi2            );  
	mDataTree->SetBranchAddress("PFMuonCombCharge"                      ,mPFMuonCombCharge          );  
	mDataTree->SetBranchAddress("PFMuonCombQOverPError"                 ,mPFMuonCombQOverPError     );  
	mDataTree->SetBranchAddress("PFMuonCombNdof"                        ,mPFMuonCombNdof            );  
	mDataTree->SetBranchAddress("PFMuonCombVx"                          ,mPFMuonCombVx              );  
	mDataTree->SetBranchAddress("PFMuonCombVy"                          ,mPFMuonCombVy              );  
	mDataTree->SetBranchAddress("PFMuonCombVz"                          ,mPFMuonCombVz              );  
	mDataTree->SetBranchAddress("PFMuonCombD0"                          ,mPFMuonCombD0              );  
	mDataTree->SetBranchAddress("PFMuonCombDz"                          ,mPFMuonCombDz              );  
	mDataTree->SetBranchAddress("PFMuonStandChi2Norm"                   ,mPFMuonStandChi2Norm       );  
	mDataTree->SetBranchAddress("PFMuonStandValidHits"                  ,mPFMuonStandValidHits      );  
	mDataTree->SetBranchAddress("PFMuonStandLostHits"                   ,mPFMuonStandLostHits       );  
	mDataTree->SetBranchAddress("PFMuonStandPt"                         ,mPFMuonStandPt             );  
	mDataTree->SetBranchAddress("PFMuonStandPz"                         ,mPFMuonStandPz             );  
	mDataTree->SetBranchAddress("PFMuonStandP"                          ,mPFMuonStandP              );  
	mDataTree->SetBranchAddress("PFMuonStandEta"                        ,mPFMuonStandEta            );  
	mDataTree->SetBranchAddress("PFMuonStandPhi"                        ,mPFMuonStandPhi            );  
	mDataTree->SetBranchAddress("PFMuonStandChi2"                       ,mPFMuonStandChi2           );  
	mDataTree->SetBranchAddress("PFMuonStandCharge"                     ,mPFMuonStandCharge         );  
	mDataTree->SetBranchAddress("PFMuonStandQOverPError"                ,mPFMuonStandQOverPError    );  
	mDataTree->SetBranchAddress("PFMuonTrkChi2Norm"                     ,mPFMuonTrkChi2Norm         );  
	mDataTree->SetBranchAddress("PFMuonTrkValidHits"                    ,mPFMuonTrkValidHits        );  
	mDataTree->SetBranchAddress("PFMuonTrkLostHits"                     ,mPFMuonTrkLostHits         );  
	mDataTree->SetBranchAddress("PFMuonTrkPt"                           ,mPFMuonTrkPt               );  
	mDataTree->SetBranchAddress("PFMuonTrkPz"                           ,mPFMuonTrkPz               );  
	mDataTree->SetBranchAddress("PFMuonTrkP"                            ,mPFMuonTrkP                );  
	mDataTree->SetBranchAddress("PFMuonTrkEta"                          ,mPFMuonTrkEta              );  
	mDataTree->SetBranchAddress("PFMuonTrkPhi"                          ,mPFMuonTrkPhi              );  
	mDataTree->SetBranchAddress("PFMuonTrkChi2"                         ,mPFMuonTrkChi2             );  
	mDataTree->SetBranchAddress("PFMuonTrkCharge"                       ,mPFMuonTrkCharge           );  
	mDataTree->SetBranchAddress("PFMuonTrkQOverPError"                  ,mPFMuonTrkQOverPError      );  
	mDataTree->SetBranchAddress("PFMuonTrkDxy"                          ,mPFMuonTrkDxy              );  
	mDataTree->SetBranchAddress("PFMuonTrkNumOfValidPixHits"            ,mPFMuonTrkNumOfValidPixHits);  
																									
		
	mDataTree->SetBranchAddress("NElec"                                 ,&mNElec                   );   
	mDataTree->SetBranchAddress("ElecE"                                 ,mElecE                    );   
	mDataTree->SetBranchAddress("ElecPt"                                ,mElecPt                   );   
	mDataTree->SetBranchAddress("ElecPx"                                ,mElecPx                   );   
	mDataTree->SetBranchAddress("ElecPy"                                ,mElecPy                   );   
	mDataTree->SetBranchAddress("ElecPz"                                ,mElecPz                   );   
	mDataTree->SetBranchAddress("ElecEcalseed"                          ,mElecEcalseed             );   
	mDataTree->SetBranchAddress("ElecID80"                              ,mElecID80                 );   
	mDataTree->SetBranchAddress("ElecID95"                              ,mElecID95                 );   
	mDataTree->SetBranchAddress("ElecEta"                               ,mElecEta                  );   
	mDataTree->SetBranchAddress("ElecPhi"                               ,mElecPhi                  );   
	mDataTree->SetBranchAddress("ElecCharge"                            ,mElecCharge               );   
	mDataTree->SetBranchAddress("Elecdr03HcalTowerSumEt"                ,mElecdr03HcalTowerSumEt   );   
	mDataTree->SetBranchAddress("Elecdr03EcalRecHitSumEt"               ,mElecdr03EcalRecHitSumEt  );   
	mDataTree->SetBranchAddress("Elecdr03TkSumPt"                       ,mElecdr03TkSumPt          );   
	mDataTree->SetBranchAddress("ElecNumOfValidHits"                    ,mElecNumOfValidHits       );   
	mDataTree->SetBranchAddress("ElecInnerNumOfHits"                    ,mElecInnerNumOfHits       );   
	mDataTree->SetBranchAddress("Elecdist"                              ,mElecdist                 );   
	mDataTree->SetBranchAddress("Elecdcot"                              ,mElecdcot                 );   
	mDataTree->SetBranchAddress("ElecNormChi2"                          ,mElecNormChi2             );   
	mDataTree->SetBranchAddress("Elecdxy"                               ,mElecdxy                  );   
	mDataTree->SetBranchAddress("Elecdz"                                ,mElecdz                   );   
	mDataTree->SetBranchAddress("ElecdB"                                ,mElecdB                   );   
	mDataTree->SetBranchAddress("ElecIsEB"                              ,mElecIsEB                 );   
	mDataTree->SetBranchAddress("Elecfbrem"                             ,mElecfbrem                );   
	mDataTree->SetBranchAddress("ElecDEtaSuTrAtVtx"                     ,mElecDEtaSuTrAtVtx        );   
	mDataTree->SetBranchAddress("ElecDPhiSuTrAtVtx"                     ,mElecDPhiSuTrAtVtx        );   
	mDataTree->SetBranchAddress("ElecHadronicOverEm"                    ,mElecHadronicOverEm       );   
	mDataTree->SetBranchAddress("ElecHcalOverEcal"                      ,mElecHcalOverEcal         );   
	mDataTree->SetBranchAddress("ElecSuperClusOverP"                    ,mElecSuperClusOverP       );   
	mDataTree->SetBranchAddress("Elecetaeta"                            ,mElecetaeta               );   
	mDataTree->SetBranchAddress("Elecietaieta"                          ,mElecietaieta             );
																									
																									
	mDataTree->SetBranchAddress("NPFElec"                               ,&mNPFElec                  );  
	mDataTree->SetBranchAddress("PFElecCharge"                          ,mPFElecCharge              );  
	mDataTree->SetBranchAddress("PFElecIsEB"                            ,mPFElecIsEB                );  
	mDataTree->SetBranchAddress("PFElecPassTight"                       ,mPFElecPassTight           );  
	mDataTree->SetBranchAddress("PFElecE"                               ,mPFElecE                   );  
	mDataTree->SetBranchAddress("PFElecPt"                              ,mPFElecPt                  );  
	mDataTree->SetBranchAddress("PFElecPx"                              ,mPFElecPx                  );  
	mDataTree->SetBranchAddress("PFElecPy"                              ,mPFElecPy                  );  
	mDataTree->SetBranchAddress("PFElecPz"                              ,mPFElecPz                  );  
	mDataTree->SetBranchAddress("PFElecEta"                             ,mPFElecEta                 );  
	mDataTree->SetBranchAddress("PFElecPhi"                             ,mPFElecPhi                 );  
	mDataTree->SetBranchAddress("PFElecCharHadIso"                      ,mPFElecCharHadIso          );  
	mDataTree->SetBranchAddress("PFElecPhoIso"                          ,mPFElecPhoIso              );  
	mDataTree->SetBranchAddress("PFElecNeuHadIso"                       ,mPFElecNeuHadIso           );  
	mDataTree->SetBranchAddress("PFElecMva"                             ,mPFElecMva                 );  
	mDataTree->SetBranchAddress("PFElecdxy"                             ,mPFElecdxy                 );  
	mDataTree->SetBranchAddress("PFElecdz"                              ,mPFElecdz                  );  
	mDataTree->SetBranchAddress("PFElecHadOverEm"                       ,mPFElecHadOverEm           );  
	mDataTree->SetBranchAddress("PFElecHcalOverEm"                      ,mPFElecHcalOverEm          );  
	mDataTree->SetBranchAddress("PFElecSupClusOverP"                    ,mPFElecSupClusOverP        );  
	mDataTree->SetBranchAddress("PFElecInnerHits"                       ,mPFElecInnerHits           );  
	mDataTree->SetBranchAddress("PFElecConvDist"                        ,mPFElecConvDist            );  
	mDataTree->SetBranchAddress("PFElecConvDcot"                        ,mPFElecConvDcot            );
	mDataTree->SetBranchAddress("PFElecDEtaSuTrAtVtx"                   ,mPFElecDEtaSuTrAtVtx       );   
	mDataTree->SetBranchAddress("PFElecDPhiSuTrAtVtx"                   ,mPFElecDPhiSuTrAtVtx       );   
	mDataTree->SetBranchAddress("PFElecHadronicOverEm"                  ,mPFElecHadronicOverEm      );   
	mDataTree->SetBranchAddress("PFElecHcalOverEcal"                    ,mPFElecHcalOverEcal        );   
	mDataTree->SetBranchAddress("PFElecetaeta"                          ,mPFElecetaeta              );   
	mDataTree->SetBranchAddress("PFElecietaieta"                        ,mPFElecietaieta            );



					
	mDataTree->SetBranchAddress("NTau"                                  ,&mNTau                                ); 
	mDataTree->SetBranchAddress("TauE"                                  ,mTauE                                 ); 
	mDataTree->SetBranchAddress("TauPt"                                 ,mTauPt                                ); 
	mDataTree->SetBranchAddress("TauPx"                                 ,mTauPx                                ); 
	mDataTree->SetBranchAddress("TauPy"                                 ,mTauPy                                ); 
	mDataTree->SetBranchAddress("TauPz"                                 ,mTauPz                                ); 
	mDataTree->SetBranchAddress("TauEta"                                ,mTauEta                               ); 
	mDataTree->SetBranchAddress("TauPhi"                                ,mTauPhi                               ); 
	mDataTree->SetBranchAddress("TauEtaEtaMoment"                       ,mTauEtaEtaMoment                      ); 
	mDataTree->SetBranchAddress("TauPhiPhiMoment"                       ,mTauPhiPhiMoment                      ); 
	mDataTree->SetBranchAddress("TauEtaPhiMoment"                       ,mTauEtaPhiMoment                      ); 
	mDataTree->SetBranchAddress("TauTracksInvariantMass"                ,mTauTracksInvariantMass               ); 
	mDataTree->SetBranchAddress("TauSignalTracksInvariantMass"          ,mTauSignalTracksInvariantMass         ); 
	mDataTree->SetBranchAddress("TauMaximumHCALhitEt"                   ,mTauMaximumHCALhitEt                  ); 
	mDataTree->SetBranchAddress("TauIsolationECALhitsEtSum"             ,mTauIsolationECALhitsEtSum            ); 
	mDataTree->SetBranchAddress("TauIsolationTracksPtSum"               ,mTauIsolationTracksPtSum              ); 
	mDataTree->SetBranchAddress("TauLeadTrackHCAL3x3hottesthitDEta"     ,mTauLeadTrackHCAL3x3hottesthitDEta    ); 
	mDataTree->SetBranchAddress("TauLeadTrackHCAL3x3hitsEtSum"          ,mTauLeadTrackHCAL3x3hitsEtSum         ); 
	mDataTree->SetBranchAddress("TauLeadTracksignedSipt"                ,mTauLeadTracksignedSipt               ); 

	mDataTree->SetBranchAddress("TauDisByLooseCombinedIsolationDeltaBetaCorr" ,mTauDisByLooseCombinedIsolationDeltaBetaCorr);
	mDataTree->SetBranchAddress("TauDisDecayModeFinding"                      ,mTauDisDecayModeFinding);
	mDataTree->SetBranchAddress("TauDisAgainstElectronLoose"                  ,mTauDisAgainstElectronLoose);
	mDataTree->SetBranchAddress("TauDisAgainstMuonTight2"                     ,mTauDisAgainstMuonTight2);
	
	mDataTree->SetBranchAddress("TauJetPt"                                    ,mTauJetPt);
	mDataTree->SetBranchAddress("TauJetEta"                                   ,mTauJetEta);
	mDataTree->SetBranchAddress("TauJetPhi"                                   ,mTauJetPhi); 
	
	mDataTree->SetBranchAddress("NPFTau"                                ,&mNPFTau                              ); 
	mDataTree->SetBranchAddress("PFTauE"                                ,mPFTauE                               ); 
	mDataTree->SetBranchAddress("PFTauPt"                               ,mPFTauPt                              ); 
	mDataTree->SetBranchAddress("PFTauPx"                               ,mPFTauPx                              ); 
	mDataTree->SetBranchAddress("PFTauPy"                               ,mPFTauPy                              ); 
	mDataTree->SetBranchAddress("PFTauPz"                               ,mPFTauPz                              ); 
	mDataTree->SetBranchAddress("PFTauEta"                              ,mPFTauEta                             ); 
	mDataTree->SetBranchAddress("PFTauPhi"                              ,mPFTauPhi                             ); 
	mDataTree->SetBranchAddress("PFTauCharge"                           ,mPFTauCharge                          ); 

	mDataTree->SetBranchAddress("PFTauEtaEtaMoment"                     ,mPFTauEtaEtaMoment                    ); 
	mDataTree->SetBranchAddress("PFTauPhiPhiMoment"                     ,mPFTauPhiPhiMoment                    ); 
	mDataTree->SetBranchAddress("PFTauEtaPhiMoment"                     ,mPFTauEtaPhiMoment                    ); 
	mDataTree->SetBranchAddress("PFTauLeadPFChargedHadrCandsignedSipt"  ,mPFTauLeadPFChargedHadrCandsignedSipt ); 
	mDataTree->SetBranchAddress("PFTauIsoPFChargedHadrCandsPtSum"       ,mPFTauIsoPFChargedHadrCandsPtSum      ); 
	mDataTree->SetBranchAddress("PFTauIsoPFGammaCandsEtSum"             ,mPFTauIsoPFGammaCandsEtSum            ); 
	mDataTree->SetBranchAddress("PFTauMaximumHCALPFClusterEt"           ,mPFTauMaximumHCALPFClusterEt          ); 
	mDataTree->SetBranchAddress("PFTauEmFraction"                       ,mPFTauEmFraction                      ); 
	mDataTree->SetBranchAddress("PFTauHcalTotOverPLead"                 ,mPFTauHcalTotOverPLead                ); 
	mDataTree->SetBranchAddress("PFTauHcalMaxOverPLead"                 ,mPFTauHcalMaxOverPLead                ); 
	mDataTree->SetBranchAddress("PFTauHcal3x3OverPLead"                 ,mPFTauHcal3x3OverPLead                ); 
	mDataTree->SetBranchAddress("PFTauEcalStripSumEOverPLead"           ,mPFTauEcalStripSumEOverPLead          ); 
	mDataTree->SetBranchAddress("PFTauBremsRecoveryEOverPLead"          ,mPFTauBremsRecoveryEOverPLead         ); 
	mDataTree->SetBranchAddress("PFTauElectronPreIDOutput"              ,mPFTauElectronPreIDOutput             ); 
	mDataTree->SetBranchAddress("PFTauElectronPreIDDecision"            ,mPFTauElectronPreIDDecision           ); 
	mDataTree->SetBranchAddress("PFTauCaloComp"                         ,mPFTauCaloComp                        ); 
	mDataTree->SetBranchAddress("PFTauSegComp"                          ,mPFTauSegComp                         ); 
	mDataTree->SetBranchAddress("PFTauMuonDecision"                     ,mPFTauMuonDecision                    );

	mDataTree->SetBranchAddress("PFTauLeadTrackPtCut"                   ,mPFTauLeadTrackPtCut                  );
	mDataTree->SetBranchAddress("PFTauByIso"                            ,mPFTauByIso                           );
	mDataTree->SetBranchAddress("PFTauByTaNCfrHalfPercent"              ,mPFTauByTaNCfrHalfPercent             );

	mDataTree->SetBranchAddress("PFTauDisByLooseCombinedIsolationDeltaBetaCorr" ,mPFTauDisByLooseCombinedIsolationDeltaBetaCorr);
	mDataTree->SetBranchAddress("PFTauDisDecayModeFinding"                      ,mPFTauDisDecayModeFinding);
	mDataTree->SetBranchAddress("PFTauDisAgainstElectronLoose"                  ,mPFTauDisAgainstElectronLoose);
	mDataTree->SetBranchAddress("PFTauDisAgainstMuonTight2"                     ,mPFTauDisAgainstMuonTight2);
	
	mDataTree->SetBranchAddress("PFTauJetPt"                                    ,mPFTauJetPt);
	mDataTree->SetBranchAddress("PFTauJetEta"                                   ,mPFTauJetEta);
	mDataTree->SetBranchAddress("PFTauJetPhi"                                   ,mPFTauJetPhi);
	
	mDataTree->SetBranchAddress("WTauDecayMode"                                 ,&mWTauDecayMode);
	mDataTree->SetBranchAddress("WTauN"                                         ,&mWTauN);
	mDataTree->SetBranchAddress("WTauDecayId"                                   ,mWTauDecayId);
	mDataTree->SetBranchAddress("WTauDecayPt"                                   ,mWTauDecayPt);
	mDataTree->SetBranchAddress("WTauDecayEta"                                  ,mWTauDecayEta);
	mDataTree->SetBranchAddress("WTauDecayPhi"                                  ,mWTauDecayPhi); 
	mDataTree->SetBranchAddress("WTauDecayMass"                                 ,mWTauDecayMass);

																							
	mDataTree->SetBranchAddress("NPhot"                                 ,&mNPhot                                ); 
	mDataTree->SetBranchAddress("PhotE"                                 ,mPhotE                                 ); 
	mDataTree->SetBranchAddress("PhotPt"                                ,mPhotPt                                ); 
	mDataTree->SetBranchAddress("PhotPx"                                ,mPhotPx                                ); 
	mDataTree->SetBranchAddress("PhotPy"                                ,mPhotPy                                ); 
	mDataTree->SetBranchAddress("PhotPz"                                ,mPhotPz                                ); 
	mDataTree->SetBranchAddress("PhotEta"                               ,mPhotEta                               ); 
	mDataTree->SetBranchAddress("PhotPhi"                               ,mPhotPhi                               );   
	mDataTree->SetBranchAddress("PhotE1x5"                              ,mPhotE1x5                              ); 
	mDataTree->SetBranchAddress("PhotE2x5"                              ,mPhotE2x5                              ); 
	mDataTree->SetBranchAddress("PhotE5x5"                              ,mPhotE5x5                              ); 
	mDataTree->SetBranchAddress("PhotSigEta"                            ,mPhotSigEta                            ); 
	mDataTree->SetBranchAddress("PhotSigPhi"                            ,mPhotSigPhi                            ); 
	mDataTree->SetBranchAddress("PhotEcalIso04"                         ,mPhotEcalIso04                         ); 
	mDataTree->SetBranchAddress("PhotHcalIso04"                         ,mPhotHcalIso04                         ); 
	mDataTree->SetBranchAddress("PhotTrackIso04"                        ,mPhotTrackIso04                        ); 
	mDataTree->SetBranchAddress("PhotHasPixSeed"                        ,mPhotHasPixSeed                        ); 
	mDataTree->SetBranchAddress("PhotIsPhot"                            ,mPhotIsPhot                            ); 
	
	
	mDataTree->SetBranchAddress("NPV"                                   ,&mNPV                                  ); 
	mDataTree->SetBranchAddress("PVx"                                   ,mPVx                                   ); 
	mDataTree->SetBranchAddress("PVy"                                   ,mPVy                                   ); 
	mDataTree->SetBranchAddress("PVz"                                   ,mPVz                                   ); 
	mDataTree->SetBranchAddress("PVchi2"                                ,mPVchi2                                ); 
	mDataTree->SetBranchAddress("PVndof"                                ,mPVndof                                ); 
	mDataTree->SetBranchAddress("PVntracks"                             ,mPVntracks                             ); 
	
	mDataTree->SetBranchAddress("nHLT"                                  ,&mnHLT                                 ); 
	mDataTree->SetBranchAddress("HLTArray"                              ,mHLTArray                              ); 
	mDataTree->SetBranchAddress("HLTArray2"                             ,mHLTArray2                             ); 
	mDataTree->SetBranchAddress("HLTNames"                              ,mHLTNames                              ); 
	mDataTree->SetBranchAddress("HLTPreScale2"                          ,mHLTPreScale2                          ); 
	
	mDataTree->SetBranchAddress("nL1"                                   ,&mnL1                                  ); 
	mDataTree->SetBranchAddress("L1Array"                               ,mL1Array                               ); 
	mDataTree->SetBranchAddress("nL1T"                                  ,&mnL1T                                 ); 
	mDataTree->SetBranchAddress("L1TArray"                              ,mL1TArray                              ); 
	
	
	mDataTree->SetBranchAddress("BeamHaloTight"                         ,&mBeamHaloTight                        ); 
	mDataTree->SetBranchAddress("BeamHaloLoose"                         ,&mBeamHaloLoose                        ); 
	
	mDataTree->SetBranchAddress("TIV_N"                                 ,&mTIV_N                                 ); 
	mDataTree->SetBranchAddress("TIV"                                   ,mTIV                                   ); 
	mDataTree->SetBranchAddress("TIV_pt"                                ,mTIV_pt                                ); 
	mDataTree->SetBranchAddress("TIV_px"                                ,mTIV_px                                ); 
	mDataTree->SetBranchAddress("TIV_py"                                ,mTIV_py                                ); 
	mDataTree->SetBranchAddress("TIV_pz"                                ,mTIV_pz                                ); 
	mDataTree->SetBranchAddress("TIV_phi"                               ,mTIV_phi                               ); 
	mDataTree->SetBranchAddress("TIV_eta"                               ,mTIV_eta                               ); 
	mDataTree->SetBranchAddress("TIV_dsz"                               ,mTIV_dsz                               ); 
	mDataTree->SetBranchAddress("TIV_dxy"                               ,mTIV_dxy                               ); 
	mDataTree->SetBranchAddress("TIV_d0"                                ,mTIV_d0                                ); 
	mDataTree->SetBranchAddress("TIV_dz"                                ,mTIV_dz                                ); 
	mDataTree->SetBranchAddress("TIV_dsz_corr"                          ,mTIV_dsz_corr                          ); 
	mDataTree->SetBranchAddress("TIV_dxy_corr"                          ,mTIV_dxy_corr                          ); 
	mDataTree->SetBranchAddress("TIV_d0_corr"                           ,mTIV_d0_corr                           ); 
	mDataTree->SetBranchAddress("TIV_dz_corr"                           ,mTIV_dz_corr                           ); 
	mDataTree->SetBranchAddress("TIV_dR"                                ,mTIV_dR                                ); 
	mDataTree->SetBranchAddress("TIV_lead"                              ,mTIV_lead                              ); 
	mDataTree->SetBranchAddress("LowTIV"                                ,&mLowTIV                               ); 
	

	mDataTree->SetBranchAddress("NGenPar"                               ,&mNGenPar                              );
	mDataTree->SetBranchAddress("GenParId"                              ,mGenParId                              );
	mDataTree->SetBranchAddress("GenParStatus"                          ,mGenParStatus                          );
	mDataTree->SetBranchAddress("GenParE"                               ,mGenParE                               );
	mDataTree->SetBranchAddress("GenParPx"                              ,mGenParPx                              );
	mDataTree->SetBranchAddress("GenParPy"                              ,mGenParPy                              );
	mDataTree->SetBranchAddress("GenParPz"                              ,mGenParPz                              );
	mDataTree->SetBranchAddress("GenParEta"                             ,mGenParEta                             );
	mDataTree->SetBranchAddress("GenParPhi"                             ,mGenParPhi                             );
	mDataTree->SetBranchAddress("GenParCharge"                          ,mGenParCharge                          );
	mDataTree->SetBranchAddress("GenParPt"                              ,mGenParPt                              );
	mDataTree->SetBranchAddress("GenParMass"                            ,mGenParMass                            );
	mDataTree->SetBranchAddress("GenParMother1"                         ,mGenParMother1                         );
	mDataTree->SetBranchAddress("GenParMother2"                         ,mGenParMother2                         );
	mDataTree->SetBranchAddress("GenParDoughterOf"                      ,mGenParDoughterOf                      );



	mDataTree->SetBranchAddress(  "GenAK5JetE"                          ,mGenAK5JetE                            );
	mDataTree->SetBranchAddress(  "GenAK5JetPt"                         ,mGenAK5JetPt                           );
	mDataTree->SetBranchAddress(  "GenAK5JetPx"                         ,mGenAK5JetPx                           );
	mDataTree->SetBranchAddress(  "GenAK5JetPy"                         ,mGenAK5JetPy                           );
	mDataTree->SetBranchAddress(  "GenAK5JetPz"                         ,mGenAK5JetPz                           );
	mDataTree->SetBranchAddress(  "GenAK5JetEta"                        ,mGenAK5JetEta                          );
	mDataTree->SetBranchAddress(  "GenAK5JetPhi"                        ,mGenAK5JetPhi                          );
	mDataTree->SetBranchAddress(  "GenAK5JetEmEnergy"                   ,mGenAK5JetEmEnergy                     );
	mDataTree->SetBranchAddress(  "GenAK5JetHadEnergy"                  ,mGenAK5JetHadEnergy                    );

		
	mDataTree->SetBranchAddress( "GenScale"                                ,&mPDFGenScale );
	mDataTree->SetBranchAddress( "PDFx1"                                   ,&mPDFx1       );
	mDataTree->SetBranchAddress( "PDFx2"                                   ,&mPDFx2       );
	mDataTree->SetBranchAddress( "PDFf1"                                   ,&mPDFf1       );
	mDataTree->SetBranchAddress( "PDFf2"                                   ,&mPDFf2       );
	mDataTree->SetBranchAddress( "PDFscale"                                ,&mPDFscale    );
	mDataTree->SetBranchAddress( "PDFpdf1"                                 ,&mPDFpdf1     );
	mDataTree->SetBranchAddress( "PDFpdf2"                                 ,&mPDFpdf2     );


}


EventData::~EventData() 
{
	delete mDataTree;
}


bool EventData::GetNextEvent() 
{
	time_t rawtime;
	time ( &rawtime );

	if ( mEvent % 1000000 == 0 ) cout << mEvent << "   time:"<< ctime (&rawtime)  << endl;
	if ( mEvent == mMaxEvents ) return false;
	if ( !mDataTree->GetEntry(mEvent) ) return false;
	mEvent++;
 
	return true;
}


///------------------------------------------------------------------------------------------------------------------------------------


double EventData::Weight()
{   
	double ww = mylumi["met1"] / mylumi[ mFileName.c_str() ] ; 

	double pileup_weight=0.;

	if(misMC==1)
	{
		int mnpv=0;
		//if(mbx ==-1) mnpv= mnpvm1;
		//else if(mbx ==0) mnpv= mnpv0;
		//else if(mbx ==1) mnpv= mnpvp1;

		mnpv = mnpv0;
	
		size_t dd = mnpv;
	
		if( dd < mPileUpWeights.size() )
		{
			pileup_weight = mPileUpWeights[ mnpv ];
		}
		else{ //should not happen as we have a weight for all simulated n_pu multiplicities!
			//throw logic_error("n_pu too big");
		}
	}
	else
	{
		pileup_weight = 1;
	}

	double www = ww *pileup_weight; 
	//double www = ww; 

	return www;
}

/*
Double_t  EventData::PDFWeight( UInt_t id )
{	
	
  double  w1,w2;
	
	LHAPDF::usePDFMember(1, id ); 
	
	double basepdf1 = LHAPDF::xfx(1, mPDFx1, mPDFscale, mPDFf1)/mPDFx1;
	double basepdf2 = LHAPDF::xfx(1, mPDFx2, mPDFscale, mPDFf2)/mPDFx2;
	w1 = basepdf1*basepdf2;
	
	
 	LHAPDF::usePDFMember(3,0 );
 	
 	double basepdf1_ = LHAPDF::xfx(3, mPDFx1, mPDFscale, mPDFf1)/mPDFx1;
 	double basepdf2_ = LHAPDF::xfx(3, mPDFx2, mPDFscale, mPDFf2)/mPDFx2;
 	w2 = basepdf1_*basepdf2_;

	
	return w1/w2 ;

} 


Double_t  EventData::PDFWeightAlphaS( UInt_t id )
{

        double  w1;

        LHAPDF::usePDFMember(2,id );

        double basepdf1 = LHAPDF::xfx(2, mPDFx1, mPDFscale, mPDFf1)/mPDFx1;
        double basepdf2 = LHAPDF::xfx(2, mPDFx2, mPDFscale, mPDFf2)/mPDFx2;
        w1 = basepdf1*basepdf2;

	return w1;
}


Double_t  EventData::PDFWeightAlphaSmstw( UInt_t id )
{

        double  w1;
		int usemem =0;

		if(id==0) usemem=2;
		else if(id==1) usemem=3;

        LHAPDF::usePDFMember(usemem,0 );
        double basepdf1 = LHAPDF::xfx(usemem, mPDFx1, mPDFscale, mPDFf1)/mPDFx1;
        double basepdf2 = LHAPDF::xfx(usemem, mPDFx2, mPDFscale, mPDFf2)/mPDFx2;

        w1 = basepdf1*basepdf2;

		return w1;
} */



Int_t           EventData::IsMC()                                            {   return misMC;                                    }
string          EventData::JetType()                                         {   return mJetType;                                 }
string          EventData::LepType()                                         {   return mLepType;                                 }

int             EventData::MetType()                                         {   return mMetType;                                 }
float           EventData::SecJetCut()                                       {   return mSecJetCut;                               }
Double_t        EventData::PDFWeights(UInt_t id)                             {   return mPDFWeights[id];                          } 
float           EventData::EnergyScale()                                     {   return mEnergyScale;                             }





Int_t           EventData::run()                                             {   return  mrun;                                     }
Long64_t        EventData::event()                                           {   return  mevent;                                   }
Int_t           EventData::lumi()                                            {   return  mlumi;                                    }
Int_t           EventData::bx()                                              {   return  mbx;                                      }
Int_t           EventData::npvm1()                                           {   return  mnpvm1;                                   }
Int_t           EventData::npv0()                                            {   return  mnpv0;                                    }
Int_t           EventData::npvp1()                                           {   return  mnpvp1;                                   }

Double_t        EventData::ptHat()                                           {   return  mptHat;                                   }
Int_t           EventData::NoiseFlag(UInt_t id)                              {   return  mNoiseFlag[id];                           }

										
Int_t           EventData::NCaloAK5Jets()                                    {   return  mNCaloAK5Jets;                            }
Double_t        EventData::CaloAK5JetE(UInt_t id)                            {   return  mCaloAK5JetE[id];                         }
Double_t        EventData::CaloAK5JetPt(UInt_t id)                           {   return  mCaloAK5JetPt[id];                        }
Double_t        EventData::CaloAK5JetPx(UInt_t id)                           {   return  mCaloAK5JetPx[id];                        }
Double_t        EventData::CaloAK5JetPy(UInt_t id)                           {   return  mCaloAK5JetPy[id];                        }
Double_t        EventData::CaloAK5JetPz(UInt_t id)                           {   return  mCaloAK5JetPz[id];                        }
Double_t        EventData::CaloAK5JetEta(UInt_t id)                          {   return  mCaloAK5JetEta[id];                       }
Double_t        EventData::CaloAK5JetPhi(UInt_t id)                          {   return  mCaloAK5JetPhi[id];                       }
Double_t        EventData::CaloAK5JetEmf(UInt_t id)                          {   return  mCaloAK5JetEmf[id];                       }
Double_t        EventData::CaloAK5JetfHPD(UInt_t id)                         {   return  mCaloAK5JetfHPD[id];                      }
Double_t        EventData::CaloAK5JetfRBX(UInt_t id)                         {   return  mCaloAK5JetfRBX[id];                      }
Double_t        EventData::CaloAK5JetN90Hits(UInt_t id)                      {   return  mCaloAK5JetN90Hits[id];                   }
Int_t           EventData::CaloAK5JetN90(UInt_t id)                          {   return  mCaloAK5JetN90[id];                       }
Double_t        EventData::CaloAK5JetSigEta(UInt_t id)                       {   return  mCaloAK5JetSigEta[id];                    }
Double_t        EventData::CaloAK5JetSigPhi(UInt_t id)                       {   return  mCaloAK5JetSigPhi[id];                    }
Double_t        EventData::CaloAK5JetIDEmf(UInt_t id)                        {   return  mCaloAK5JetIDEmf[id];                     }
Double_t        EventData::CaloAK5JetECor(UInt_t id)                         {   return  mCaloAK5JetECor[id];                      }
Double_t        EventData::CaloAK5JetPtCor(UInt_t id)                        {   return  mCaloAK5JetPtCor[id];                     }
Double_t        EventData::CaloAK5JetPxCor(UInt_t id)                        {   return  mCaloAK5JetPxCor[id];                     }
Double_t        EventData::CaloAK5JetPyCor(UInt_t id)                        {   return  mCaloAK5JetPyCor[id];                     }
Double_t        EventData::CaloAK5JetPzCor(UInt_t id)                        {   return  mCaloAK5JetPzCor[id];                     }
Double_t        EventData::CaloAK5JetBtagTkCountHighEff(UInt_t id)           {   return  mCaloAK5JetBtagTkCountHighEff[id];        }
Double_t        EventData::CaloAK5JetBTagSimpleSecVtx(UInt_t id)             {   return  mCaloAK5JetBTagSimpleSecVtx[id];          }
Double_t        EventData::CaloAK5JetBTagCombSecVtx(UInt_t id)               {   return  mCaloAK5JetBTagCombSecVtx[id];            }
Double_t        EventData::CaloAK5TrackPt(UInt_t id)                         {   return  mCaloAK5TrackPt[id];                      }
Int_t           EventData::CaloAK5JetIDLOOSE(UInt_t id)                      {   return  mCaloAK5JetIDLOOSE[id];                   }
Int_t           EventData::CaloAK5JetIDTIGHT(UInt_t id)                      {   return  mCaloAK5JetIDTIGHT[id];                   }							
		
Int_t           EventData::NPFAK5Jets()                                      {   return  mNPFAK5Jets;                              }
Double_t        EventData::PFAK5JetE(UInt_t id)                              {   return  mPFAK5JetE[id];                           }
Double_t        EventData::PFAK5JetPt(UInt_t id)                             {   return  mPFAK5JetPt[id];                          }
Double_t        EventData::PFAK5JetPx(UInt_t id)                             {   return  mPFAK5JetPx[id];                          }
Double_t        EventData::PFAK5JetPy(UInt_t id)                             {   return  mPFAK5JetPy[id];                          }
Double_t        EventData::PFAK5JetPz(UInt_t id)                             {   return  mPFAK5JetPz[id];                          }
Double_t        EventData::PFAK5JetEta(UInt_t id)                            {   return  mPFAK5JetEta[id];                         }
Double_t        EventData::PFAK5JetPhi(UInt_t id)                            {   return  mPFAK5JetPhi[id];                         }
Double_t        EventData::PFAK5JetfHPD(UInt_t id)                           {   return  mPFAK5JetfHPD[id];                        }
Double_t        EventData::PFAK5JetfRBX(UInt_t id)                           {   return  mPFAK5JetfRBX[id];                        }
Double_t        EventData::PFAK5JetN90Hits(UInt_t id)                        {   return  mPFAK5JetN90Hits[id];                     }
Int_t           EventData::PFAK5JetN90(UInt_t id)                            {   return  mPFAK5JetN90[id];                         }
Double_t        EventData::PFAK5JetSigEta(UInt_t id)                         {   return  mPFAK5JetSigEta[id];                      }
Double_t        EventData::PFAK5JetSigPhi(UInt_t id)                         {   return  mPFAK5JetSigPhi[id];                      }
Double_t        EventData::PFAK5JetIDEmf(UInt_t id)                          {   return  mPFAK5JetIDEmf[id];                       }
Double_t        EventData::PFAK5JetECor(UInt_t id)                           {   return  mPFAK5JetECor[id];                        }

// Double_t        EventData::PFAK5JetPtCor(UInt_t id)                          {   return  mPFAK5JetPtCor[id];                       }
// Double_t        EventData::PFAK5JetPxCor(UInt_t id)                          {   return  mPFAK5JetPxCor[id];                       }
// Double_t        EventData::PFAK5JetPyCor(UInt_t id)                          {   return  mPFAK5JetPyCor[id];                       }
// Double_t        EventData::PFAK5JetPzCor(UInt_t id)                          {   return  mPFAK5JetPzCor[id];                       }

Double_t        EventData::PFAK5JetPtCor(UInt_t id)                     {    return  mPFAK5JetPtCor[id] * (1+ mEnergyScale*mPFAK5uncer[id] );      } 
Double_t        EventData::PFAK5JetPxCor(UInt_t id)                     {    return  mPFAK5JetPxCor[id] * (1+ mEnergyScale*mPFAK5uncer[id] );      } 
Double_t        EventData::PFAK5JetPyCor(UInt_t id)                     {    return  mPFAK5JetPyCor[id] * (1+ mEnergyScale*mPFAK5uncer[id] );      }
Double_t        EventData::PFAK5JetPzCor(UInt_t id)                     {    return  mPFAK5JetPzCor[id] * (1+ mEnergyScale*mPFAK5uncer[id] );      }



Double_t        EventData::PFAK5JetBtagTkCountHighEff(UInt_t id)             {   return  mPFAK5JetBtagTkCountHighEff[id];          }
Double_t        EventData::PFAK5JetBTagSimpleSecVtx(UInt_t id)               {   return  mPFAK5JetBTagSimpleSecVtx[id];            }
Double_t        EventData::PFAK5JetBTagCombSecVtx(UInt_t id)                 {   return  mPFAK5JetBTagCombSecVtx[id];              }
Double_t        EventData::PFAK5JetNeuEmEngFrac(UInt_t id)                   {   return  mPFAK5JetNeuEmEngFrac[id];                }
Double_t        EventData::PFAK5JetChaEmEngFrac(UInt_t id)                   {   return  mPFAK5JetChaEmEngFrac[id];                }
Double_t        EventData::PFAK5JetChaHadEngFrac(UInt_t id)                  {   return  mPFAK5JetChaHadEngFrac[id];               }
Double_t        EventData::PFAK5JetNeuHadEngFrac(UInt_t id)                  {   return  mPFAK5JetNeuHadEngFrac[id];               }
Double_t        EventData::PFAK5JetChaMuEng(UInt_t id)                       {   return  mPFAK5JetChaMuEng[id];                    }
Double_t        EventData::PFAK5JetMuonEng(UInt_t id)                        {   return  mPFAK5JetMuonEng[id];                     }
Double_t        EventData::PFAK5JetPhotEng(UInt_t id)                        {   return  mPFAK5JetPhotEng[id];                     }
Double_t        EventData::PFAK5JetElecEng(UInt_t id)                        {   return  mPFAK5JetElecEng[id];                     }
Int_t           EventData::PFAK5JetNumOfChaMu(UInt_t id)                     {   return  mPFAK5JetNumOfChaMu[id];                  }
Int_t           EventData::PFAK5JetNumOfMuon(UInt_t id)                      {   return  mPFAK5JetNumOfMuon[id];                   }
Int_t           EventData::PFAK5JetNumOfPhot(UInt_t id)                      {   return  mPFAK5JetNumOfPhot[id];                   }
Int_t           EventData::PFAK5JetNumOfElec(UInt_t id)                      {   return  mPFAK5JetNumOfElec[id];                   }
Int_t           EventData::PFAK5JetNumOfNeu(UInt_t id)                       {   return  mPFAK5JetNumOfNeu[id];                    }
Int_t           EventData::PFAK5JetNumOfCha(UInt_t id)                       {   return  mPFAK5JetNumOfCha[id];                    }
Int_t           EventData::PFAK5JetNumOfNeuHad(UInt_t id)                    {   return  mPFAK5JetNumOfNeuHad[id];                 }
Int_t           EventData::PFAK5JetNumOfChaHad(UInt_t id)                    {   return  mPFAK5JetNumOfChaHad[id];                 }
Int_t           EventData::PFAK5JetNumOfDaughters(UInt_t id)                 {   return  mPFAK5JetNumOfDaughters[id];              }
Int_t           EventData::PFAK5JetIDLOOSE(UInt_t id)                        {   return  mPFAK5JetIDLOOSE[id];                     }
Int_t           EventData::PFAK5JetIDTIGHT(UInt_t id)                        {   return  mPFAK5JetIDTIGHT[id];                     }
Double_t        EventData::PFAK5uncer(UInt_t id)                             {   return  mPFAK5uncer[id];                          }						
						
Int_t           EventData::NMet()                                            {   return  mNMet;                                    }


Double_t        EventData::MetPt(UInt_t id) 
{   

    Double_t jetx=0.;

    for(int i=0; i<mNPFAK5Jets;  i++)
    {
          jetx = jetx+  ( mEnergyScale*mPFAK5uncer[i]* mPFAK5JetPxCor[i] ) ;
    }
    double metx =  mMetPx[id]+jetx ;                               

    Double_t jety=0.;

      for(int i=0; i<mNPFAK5Jets;  i++)
      {
	   jety = jety+  ( mEnergyScale*mPFAK5uncer[i]* mPFAK5JetPyCor[i] ) ;
      }

      double mety =   mMetPy[id]+jety ;
    

      return  sqrt( metx*metx + mety*mety);
}




//Double_t        EventData::MetPx(UInt_t id)                                  {   return  mMetPx[id];                               }
//Double_t        EventData::MetPy(UInt_t id)                                  {   return  mMetPy[id];                               }
Double_t        EventData::MetPhi(UInt_t id)                                 {   return  mMetPhi[id];                              }
Double_t        EventData::MetSumEt(UInt_t id)                               {   return  mMetSumEt[id];                            }
Double_t        EventData::MetSign(UInt_t id)                                {   return  mMetSign[id];                             }


Double_t  EventData::MetPx(UInt_t id)
{
	Double_t jetx=0.;

	for(int i=0; i<mNPFAK5Jets;  i++)
	{
		jetx = jetx+  ( mEnergyScale*mPFAK5uncer[i]* mPFAK5JetPxCor[i] ) ; 	
	}
	return  mMetPx[id]+jetx  ;
}

Double_t  EventData::MetPy(UInt_t id)
{
	Double_t jety=0.;

	for(int i=0; i<mNPFAK5Jets;  i++)
	{
		jety = jety+  ( mEnergyScale*mPFAK5uncer[i]* mPFAK5JetPyCor[i] ) ; 
	}
	
	return  mMetPy[id]+jety ;
}
	



Int_t  EventData::NPFLep()
{
	Int_t send=0; 
	if(mLepType=="m") send=  mNPFMuon;
	if(mLepType=="e") send=  mNPFElec;
	if(mLepType=="t") send=  mNPFTau;
	return send; 
}

Double_t  EventData::PFLepPt(UInt_t id)
{
	Double_t send=0.; 
	if(mLepType=="m") send=  mPFMuonPt[id];
	if(mLepType=="e") send=  mPFElecPt[id];
	if(mLepType=="t") send=  mPFTauPt[id];
	return send; 
}
Double_t  EventData::PFLepE(UInt_t id)
{ 
	Double_t send=0.; 
	if(mLepType=="m") send=  mPFMuonE[id];
	if(mLepType=="e") send=  mPFElecE[id];
	if(mLepType=="t") send=  mPFTauE[id];
	return send; 
}
Double_t  EventData::PFLepPx(UInt_t id)
{
	Double_t send=0.; 
	if(mLepType=="m") send=  mPFMuonPx[id];
	if(mLepType=="e") send=  mPFElecPx[id];
	if(mLepType=="t") send=  mPFTauPx[id];
	return send; 
}
Double_t  EventData::PFLepPy(UInt_t id)
{
	Double_t send=0.; 
	if(mLepType=="m") send=  mPFMuonPy[id];
	if(mLepType=="e") send=  mPFElecPy[id];
	if(mLepType=="t") send=  mPFTauPy[id];
	return send; 
}
Double_t  EventData::PFLepPz(UInt_t id)
{
	Double_t send=0.; 
	if(mLepType=="m") send=  mPFMuonPz[id];
	if(mLepType=="e") send=  mPFElecPz[id];
	if(mLepType=="t") send=  mPFTauPz[id];
	return send; 
}
Double_t  EventData::PFLepEta(UInt_t id)
{
	Double_t send=0.; 
	if(mLepType=="m") send=  mPFMuonEta[id];
	if(mLepType=="e") send=  mPFElecEta[id];
	if(mLepType=="t") send=  mPFTauEta[id];
	return send; 
}
Double_t  EventData::PFLepPhi(UInt_t id)
{
	Double_t send=0.; 
	if(mLepType=="m") send=  mPFMuonPhi[id];
	if(mLepType=="e") send=  mPFElecPhi[id];
	if(mLepType=="t") send=  mPFTauPhi[id];
	return send; 
}
Int_t  EventData::PFLepCharge(UInt_t id)
{
	Int_t send=0; 
	if(mLepType=="m") send=  mPFMuonCharge[id];
	if(mLepType=="e") send=  mPFElecCharge[id];
	if(mLepType=="t") send=  mPFTauCharge[id]; 
	return send; 
}



Int_t           EventData::NMuon()                                           {   return  mNMuon;                                   }
Double_t        EventData::MuonPt(UInt_t id)                                 {   return  mMuonPt[id];                              }
Double_t        EventData::MuonEt(UInt_t id)                                 {   return  mMuonEt[id];                              }
Double_t        EventData::MuonE(UInt_t id)                                  {   return  mMuonE[id];                               }
Double_t        EventData::MuonPx(UInt_t id)                                 {   return  mMuonPx[id];                              }
Double_t        EventData::MuonPy(UInt_t id)                                 {   return  mMuonPy[id];                              }
Double_t        EventData::MuonPz(UInt_t id)                                 {   return  mMuonPz[id];                              }
Double_t        EventData::MuonEta(UInt_t id)                                {   return  mMuonEta[id];                             }
Double_t        EventData::MuonPhi(UInt_t id)                                {   return  mMuonPhi[id];                             }
Double_t        EventData::MuonCharge(UInt_t id)                             {   return  mMuonCharge[id];                          }
Int_t           EventData::MuonIsGlobal(UInt_t id)                           {   return  mMuonIsGlobal[id];                        }
Int_t           EventData::MuonIsStandAlone(UInt_t id)                       {   return  mMuonIsStandAlone[id];                    }
Int_t           EventData::MuonIsTracker(UInt_t id)                          {   return  mMuonIsTracker[id];                       }
Double_t        EventData::MuonSumPtDR03(UInt_t id)                          {   return  mMuonSumPtDR03[id];                       }
Double_t        EventData::MuonSumPtDR05(UInt_t id)                          {   return  mMuonSumPtDR05[id];                       }
Double_t        EventData::MuonEmEtDR03(UInt_t id)                           {   return  mMuonEmEtDR03[id];                        }
Double_t        EventData::MuonHadEtDR03(UInt_t id)                          {   return  mMuonHadEtDR03[id];                       }
Int_t           EventData::MuonNumOfMatches(UInt_t id)                       {   return  mMuonNumOfMatches[id];                    }
Double_t        EventData::MuonCombChi2Norm(UInt_t id)                       {   return  mMuonCombChi2Norm[id];                    }
Int_t           EventData::MuonCombValidHits(UInt_t id)                      {   return  mMuonCombValidHits[id];                   }
Int_t           EventData::MuonCombLostHits(UInt_t id)                       {   return  mMuonCombLostHits[id];                    }
Double_t        EventData::MuonCombPt(UInt_t id)                             {   return  mMuonCombPt[id];                          }
Double_t        EventData::MuonCombPz(UInt_t id)                             {   return  mMuonCombPz[id];                          }
Double_t        EventData::MuonCombP(UInt_t id)                              {   return  mMuonCombP[id];                           }
Double_t        EventData::MuonCombEta(UInt_t id)                            {   return  mMuonCombEta[id];                         }
Double_t        EventData::MuonCombPhi(UInt_t id)                            {   return  mMuonCombPhi[id];                         }
Double_t        EventData::MuonCombChi2(UInt_t id)                           {   return  mMuonCombChi2[id];                        }
Double_t        EventData::MuonCombCharge(UInt_t id)                         {   return  mMuonCombCharge[id];                      }
Double_t        EventData::MuonCombQOverPError(UInt_t id)                    {   return  mMuonCombQOverPError[id];                 }
Double_t        EventData::MuonCombNdof(UInt_t id)                           {   return  mMuonCombNdof[id];                        }
Double_t        EventData::MuonCombVx(UInt_t id)                             {   return  mMuonCombVx[id];                          }
Double_t        EventData::MuonCombVy(UInt_t id)                             {   return  mMuonCombVy[id];                          }
Double_t        EventData::MuonCombVz(UInt_t id)                             {   return  mMuonCombVz[id];                          }
Double_t        EventData::MuonCombD0(UInt_t id)                             {   return  mMuonCombD0[id];                          }
Double_t        EventData::MuonCombDz(UInt_t id)                             {   return  mMuonCombDz[id];                          }
Double_t        EventData::MuonStandChi2Norm(UInt_t id)                      {   return  mMuonStandChi2Norm[id];                   }
Int_t           EventData::MuonStandValidHits(UInt_t id)                     {   return  mMuonStandValidHits[id];                  }
Int_t           EventData::MuonStandLostHits(UInt_t id)                      {   return  mMuonStandLostHits[id];                   }
Double_t        EventData::MuonStandPt(UInt_t id)                            {   return  mMuonStandPt[id];                         }
Double_t        EventData::MuonStandPz(UInt_t id)                            {   return  mMuonStandPz[id];                         }
Double_t        EventData::MuonStandP(UInt_t id)                             {   return  mMuonStandP[id];                          }
Double_t        EventData::MuonStandEta(UInt_t id)                           {   return  mMuonStandEta[id];                        }
Double_t        EventData::MuonStandPhi(UInt_t id)                           {   return  mMuonStandPhi[id];                        }
Double_t        EventData::MuonStandChi2(UInt_t id)                          {   return  mMuonStandChi2[id];                       }
Double_t        EventData::MuonStandCharge(UInt_t id)                        {   return  mMuonStandCharge[id];                     }
Double_t        EventData::MuonStandQOverPError(UInt_t id)                   {   return  mMuonStandQOverPError[id];                }
Double_t        EventData::MuonTrkChi2Norm(UInt_t id)                        {   return  mMuonTrkChi2Norm[id];                     }
Int_t           EventData::MuonTrkValidHits(UInt_t id)                       {   return  mMuonTrkValidHits[id];                    }
Int_t           EventData::MuonTrkLostHits(UInt_t id)                        {   return  mMuonTrkLostHits[id];                     }
Double_t        EventData::MuonTrkPt(UInt_t id)                              {   return  mMuonTrkPt[id];                           }
Double_t        EventData::MuonTrkPz(UInt_t id)                              {   return  mMuonTrkPz[id];                           }
Double_t        EventData::MuonTrkP(UInt_t id)                               {   return  mMuonTrkP[id];                            }
Double_t        EventData::MuonTrkEta(UInt_t id)                             {   return  mMuonTrkEta[id];                          }
Double_t        EventData::MuonTrkPhi(UInt_t id)                             {   return  mMuonTrkPhi[id];                          }
Double_t        EventData::MuonTrkChi2(UInt_t id)                            {   return  mMuonTrkChi2[id];                         }
Double_t        EventData::MuonTrkCharge(UInt_t id)                          {   return  mMuonTrkCharge[id];                       }
Double_t        EventData::MuonTrkQOverPError(UInt_t id)                     {   return  mMuonTrkQOverPError[id];                  }
Double_t        EventData::MuonTrkDxy(UInt_t id)                             {   return  mMuonTrkDxy[id];                          }
Int_t           EventData::MuonTrkNumOfValidPixHits(UInt_t id)               {   return  mMuonTrkNumOfValidPixHits[id];            }
					
Int_t           EventData::NPFMuon()                                         {   return  mNPFMuon;                                 }
Double_t        EventData::PFMuonPt(UInt_t id)                               {   return  mPFMuonPt[id];                            }
Double_t        EventData::PFMuonEt(UInt_t id)                               {   return  mPFMuonEt[id];                            }
Double_t        EventData::PFMuonE(UInt_t id)                                {   return  mPFMuonE[id];                             }
Double_t        EventData::PFMuonPx(UInt_t id)                               {   return  mPFMuonPx[id];                            }
Double_t        EventData::PFMuonPy(UInt_t id)                               {   return  mPFMuonPy[id];                            }
Double_t        EventData::PFMuonPz(UInt_t id)                               {   return  mPFMuonPz[id];                            }
Double_t        EventData::PFMuonEta(UInt_t id)                              {   return  mPFMuonEta[id];                           }
Double_t        EventData::PFMuonPhi(UInt_t id)                              {   return  mPFMuonPhi[id];                           }
Int_t           EventData::PFMuonCharge(UInt_t id)                           {   return  mPFMuonCharge[id];                        }
Int_t           EventData::PFMuonIsGlobal(UInt_t id)                         {   return  mPFMuonIsGlobal[id];                      }
Int_t           EventData::PFMuonIsStandAlone(UInt_t id)                     {   return  mPFMuonIsStandAlone[id];                  }
Int_t           EventData::PFMuonIsTracker(UInt_t id)                        {   return  mPFMuonIsTracker[id];                     }
Double_t        EventData::PFMuonChargedHadronIso(UInt_t id)                 {   return  mPFMuonChargedHadronIso[id];              }
Double_t        EventData::PFMuonPhotonIso(UInt_t id)                        {   return  mPFMuonPhotonIso[id];                     }
Double_t        EventData::PFMuonNeutralHadronIso(UInt_t id)                 {   return  mPFMuonNeutralHadronIso[id];              }
Int_t           EventData::PFMuonisGMPT(UInt_t id)                           {   return  mPFMuonisGMPT[id];                        }
Int_t           EventData::PFMuonNumOfMatches(UInt_t id)                     {   return  mPFMuonNumOfMatches[id];                  }
Double_t        EventData::PFMuoninnertrackPt(UInt_t id)                     {   return  mPFMuoninnertrackPt[id];                  }
Int_t           EventData::PFMuonnValidHits(UInt_t id)                       {   return  mPFMuonnValidHits[id];                    }
Int_t           EventData::PFMuonnValidPixelHits(UInt_t id)                  {   return  mPFMuonnValidPixelHits[id];               }
Double_t        EventData::PFMuondxy(UInt_t id)                              {   return  mPFMuondxy[id];                           }
Double_t        EventData::PFMuondz(UInt_t id)                               {   return  mPFMuondz[id];                            }
Double_t        EventData::PFMuonCombChi2Norm(UInt_t id)                     {   return  mPFMuonCombChi2Norm[id];                  }
Int_t           EventData::PFMuonCombValidHits(UInt_t id)                    {   return  mPFMuonCombValidHits[id];                 }
Int_t           EventData::PFMuonCombLostHits(UInt_t id)                     {   return  mPFMuonCombLostHits[id];                  }
Double_t        EventData::PFMuonCombPt(UInt_t id)                           {   return  mPFMuonCombPt[id];                        }
Double_t        EventData::PFMuonCombPz(UInt_t id)                           {   return  mPFMuonCombPz[id];                        }
Double_t        EventData::PFMuonCombP(UInt_t id)                            {   return  mPFMuonCombP[id];                         }
Double_t        EventData::PFMuonCombEta(UInt_t id)                          {   return  mPFMuonCombEta[id];                       }
Double_t        EventData::PFMuonCombPhi(UInt_t id)                          {   return  mPFMuonCombPhi[id];                       }
Double_t        EventData::PFMuonCombChi2(UInt_t id)                         {   return  mPFMuonCombChi2[id];                      }
Double_t        EventData::PFMuonCombCharge(UInt_t id)                       {   return  mPFMuonCombCharge[id];                    }
Double_t        EventData::PFMuonCombQOverPError(UInt_t id)                  {   return  mPFMuonCombQOverPError[id];               }
Double_t        EventData::PFMuonCombNdof(UInt_t id)                         {   return  mPFMuonCombNdof[id];                      }
Double_t        EventData::PFMuonCombVx(UInt_t id)                           {   return  mPFMuonCombVx[id];                        }
Double_t        EventData::PFMuonCombVy(UInt_t id)                           {   return  mPFMuonCombVy[id];                        }
Double_t        EventData::PFMuonCombVz(UInt_t id)                           {   return  mPFMuonCombVz[id];                        }
Double_t        EventData::PFMuonCombD0(UInt_t id)                           {   return  mPFMuonCombD0[id];                        }
Double_t        EventData::PFMuonCombDz(UInt_t id)                           {   return  mPFMuonCombDz[id];                        }
Double_t        EventData::PFMuonStandChi2Norm(UInt_t id)                    {   return  mPFMuonStandChi2Norm[id];                 }
Int_t           EventData::PFMuonStandValidHits(UInt_t id)                   {   return  mPFMuonStandValidHits[id];                }
Int_t           EventData::PFMuonStandLostHits(UInt_t id)                    {   return  mPFMuonStandLostHits[id];                 }
Double_t        EventData::PFMuonStandPt(UInt_t id)                          {   return  mPFMuonStandPt[id];                       }
Double_t        EventData::PFMuonStandPz(UInt_t id)                          {   return  mPFMuonStandPz[id];                       }
Double_t        EventData::PFMuonStandP(UInt_t id)                           {   return  mPFMuonStandP[id];                        }
Double_t        EventData::PFMuonStandEta(UInt_t id)                         {   return  mPFMuonStandEta[id];                      }
Double_t        EventData::PFMuonStandPhi(UInt_t id)                         {   return  mPFMuonStandPhi[id];                      }
Double_t        EventData::PFMuonStandChi2(UInt_t id)                        {   return  mPFMuonStandChi2[id];                     }
Double_t        EventData::PFMuonStandCharge(UInt_t id)                      {   return  mPFMuonStandCharge[id];                   }
Double_t        EventData::PFMuonStandQOverPError(UInt_t id)                 {   return  mPFMuonStandQOverPError[id];              }
Double_t        EventData::PFMuonTrkChi2Norm(UInt_t id)                      {   return  mPFMuonTrkChi2Norm[id];                   }
Int_t           EventData::PFMuonTrkValidHits(UInt_t id)                     {   return  mPFMuonTrkValidHits[id];                  }
Int_t           EventData::PFMuonTrkLostHits(UInt_t id)                      {   return  mPFMuonTrkLostHits[id];                   }
Double_t        EventData::PFMuonTrkPt(UInt_t id)                            {   return  mPFMuonTrkPt[id];                         }
Double_t        EventData::PFMuonTrkPz(UInt_t id)                            {   return  mPFMuonTrkPz[id];                         }
Double_t        EventData::PFMuonTrkP(UInt_t id)                             {   return  mPFMuonTrkP[id];                          }
Double_t        EventData::PFMuonTrkEta(UInt_t id)                           {   return  mPFMuonTrkEta[id];                        }
Double_t        EventData::PFMuonTrkPhi(UInt_t id)                           {   return  mPFMuonTrkPhi[id];                        }
Double_t        EventData::PFMuonTrkChi2(UInt_t id)                          {   return  mPFMuonTrkChi2[id];                       }
Double_t        EventData::PFMuonTrkCharge(UInt_t id)                        {   return  mPFMuonTrkCharge[id];                     }
Double_t        EventData::PFMuonTrkQOverPError(UInt_t id)                   {   return  mPFMuonTrkQOverPError[id];                }
Double_t        EventData::PFMuonTrkDxy(UInt_t id)                           {   return  mPFMuonTrkDxy[id];                        }
Double_t        EventData::PFMuonTrkNumOfValidPixHits(UInt_t id)             {   return  mPFMuonTrkNumOfValidPixHits[id];          }
						
Int_t           EventData::NElec()                                           {   return  mNElec;                                   }
Double_t        EventData::ElecE(UInt_t id)                                  {   return  mElecE[id];                               }
Double_t        EventData::ElecPt(UInt_t id)                                 {   return  mElecPt[id];                              }
Double_t        EventData::ElecPx(UInt_t id)                                 {   return  mElecPx[id];                              }
Double_t        EventData::ElecPy(UInt_t id)                                 {   return  mElecPy[id];                              }
Double_t        EventData::ElecPz(UInt_t id)                                 {   return  mElecPz[id];                              }
Int_t           EventData::ElecEcalseed(UInt_t id)                           {   return  mElecEcalseed[id];                        }
Int_t           EventData::ElecID80(UInt_t id)                               {   return  mElecID80[id];                            }
Int_t           EventData::ElecID95(UInt_t id)                               {   return  mElecID95[id];                            }
Double_t        EventData::ElecEta(UInt_t id)                                {   return  mElecEta[id];                             }
Double_t        EventData::ElecPhi(UInt_t id)                                {   return  mElecPhi[id];                             }
Int_t           EventData::ElecCharge(UInt_t id)                             {   return  mElecCharge[id];                          }
Double_t        EventData::Elecdr03HcalTowerSumEt(UInt_t id)                 {   return  mElecdr03HcalTowerSumEt[id];              }
Double_t        EventData::Elecdr03EcalRecHitSumEt(UInt_t id)                {   return  mElecdr03EcalRecHitSumEt[id];             }
Double_t        EventData::Elecdr03TkSumPt(UInt_t id)                        {   return  mElecdr03TkSumPt[id];                     }
Int_t           EventData::ElecNumOfValidHits(UInt_t id)                     {   return  mElecNumOfValidHits[id];                  }
Int_t           EventData::ElecInnerNumOfHits(UInt_t id)                     {   return  mElecInnerNumOfHits[id];                  }
Double_t        EventData::Elecdist(UInt_t id)                               {   return  mElecdist[id];                            }
Double_t        EventData::Elecdcot(UInt_t id)                               {   return  mElecdcot[id];                            }
Double_t        EventData::ElecNormChi2(UInt_t id)                           {   return  mElecNormChi2[id];                        }
Double_t        EventData::Elecdxy(UInt_t id)                                {   return  mElecdxy[id];                             }
Double_t        EventData::Elecdz(UInt_t id)                                 {   return  mElecdz[id];                              }
Int_t           EventData::ElecdB(UInt_t id)                                 {   return  mElecdB[id];                              }
Int_t           EventData::ElecIsEB(UInt_t id)                               {   return  mElecIsEB[id];                            }
Double_t        EventData::Elecfbrem(UInt_t id)                              {   return  mElecfbrem[id];                           }
Double_t        EventData::ElecDEtaSuTrAtVtx(UInt_t id)                      {   return  mElecDEtaSuTrAtVtx[id];                   }
Double_t        EventData::ElecDPhiSuTrAtVtx(UInt_t id)                      {   return  mElecDPhiSuTrAtVtx[id];                   }
Double_t        EventData::ElecHadronicOverEm(UInt_t id)                     {   return  mElecHadronicOverEm[id];                  }
Double_t        EventData::ElecHcalOverEcal(UInt_t id)                       {   return  mElecHcalOverEcal[id];                    }
Double_t        EventData::ElecSuperClusOverP(UInt_t id)                     {   return  mElecSuperClusOverP[id];                  }
Double_t        EventData::Elecetaeta(UInt_t id)                             {   return  mElecetaeta[id];                          }
Double_t        EventData::Elecietaieta(UInt_t id)                           {   return  mElecietaieta[id];                        }
					
Int_t           EventData::NPFElec()                                         {   return  mNPFElec;                                 }
Int_t           EventData::PFElecCharge(UInt_t id)                           {   return  mPFElecCharge[id];                        }
Int_t           EventData::PFElecIsEB(UInt_t id)                             {   return  mPFElecIsEB[id];                          }
Double_t        EventData::PFElecPassTight(UInt_t id)                        {   return  mPFElecPassTight[id];                     }
Double_t        EventData::PFElecE(UInt_t id)                                {   return  mPFElecE[id];                             }
Double_t        EventData::PFElecPt(UInt_t id)                               {   return  mPFElecPt[id];                            }
Double_t        EventData::PFElecPx(UInt_t id)                               {   return  mPFElecPx[id];                            }
Double_t        EventData::PFElecPy(UInt_t id)                               {   return  mPFElecPy[id];                            }
Double_t        EventData::PFElecPz(UInt_t id)                               {   return  mPFElecPz[id];                            }
Double_t        EventData::PFElecEta(UInt_t id)                              {   return  mPFElecEta[id];                           }
Double_t        EventData::PFElecPhi(UInt_t id)                              {   return  mPFElecPhi[id];                           }
Double_t        EventData::PFElecCharHadIso(UInt_t id)                       {   return  mPFElecCharHadIso[id];                    }
Double_t        EventData::PFElecPhoIso(UInt_t id)                           {   return  mPFElecPhoIso[id];                        }
Double_t        EventData::PFElecNeuHadIso(UInt_t id)                        {   return  mPFElecNeuHadIso[id];                     }
Double_t        EventData::PFElecMva(UInt_t id)                              {   return  mPFElecMva[id];                           }
Double_t        EventData::PFElecdxy(UInt_t id)                              {   return  mPFElecdxy[id];                           }
Double_t        EventData::PFElecdz(UInt_t id)                               {   return  mPFElecdz[id];                            }
Double_t        EventData::PFElecHadOverEm(UInt_t id)                        {   return  mPFElecHadOverEm[id];                     }
Double_t        EventData::PFElecHcalOverEm(UInt_t id)                       {   return  mPFElecHcalOverEm[id];                    }
Double_t        EventData::PFElecSupClusOverP(UInt_t id)                     {   return  mPFElecSupClusOverP[id];                  }
Double_t        EventData::PFElecInnerHits(UInt_t id)                        {   return  mPFElecInnerHits[id];                     }
Double_t        EventData::PFElecConvDist(UInt_t id)                         {   return  mPFElecConvDist[id];                      }
Double_t        EventData::PFElecConvDcot(UInt_t id)                         {   return  mPFElecConvDcot[id];                      }
Double_t        EventData::PFElecDEtaSuTrAtVtx(UInt_t id)                    {   return  mPFElecDEtaSuTrAtVtx[id];                 }
Double_t        EventData::PFElecDPhiSuTrAtVtx(UInt_t id)                    {   return  mPFElecDPhiSuTrAtVtx[id];                 }
Double_t        EventData::PFElecHadronicOverEm(UInt_t id)                   {   return  mPFElecHadronicOverEm[id];                }
Double_t        EventData::PFElecHcalOverEcal(UInt_t id)                     {   return  mPFElecHcalOverEcal[id];                  }
Double_t        EventData::PFElecetaeta(UInt_t id)                           {   return  mPFElecetaeta[id];                        }
Double_t        EventData::PFElecietaieta(UInt_t id)                         {   return  mPFElecietaieta[id];                      }



							
Int_t           EventData::NTau()                                            {   return  mNTau;                                    }
Double_t        EventData::TauE(UInt_t id)                                   {   return  mTauE[id];                                }
Double_t        EventData::TauPt(UInt_t id)                                  {   return  mTauPt[id];                               }
Double_t        EventData::TauPx(UInt_t id)                                  {   return  mTauPx[id];                               }
Double_t        EventData::TauPy(UInt_t id)                                  {   return  mTauPy[id];                               }
Double_t        EventData::TauPz(UInt_t id)                                  {   return  mTauPz[id];                               }
Double_t        EventData::TauEta(UInt_t id)                                 {   return  mTauEta[id];                              }
Double_t        EventData::TauPhi(UInt_t id)                                 {   return  mTauPhi[id];                              }
Double_t        EventData::TauEtaEtaMoment(UInt_t id)                        {   return  mTauEtaEtaMoment[id];                     }
Double_t        EventData::TauPhiPhiMoment(UInt_t id)                        {   return  mTauPhiPhiMoment[id];                     }
Double_t        EventData::TauEtaPhiMoment(UInt_t id)                        {   return  mTauEtaPhiMoment[id];                     }
Double_t        EventData::TauTracksInvariantMass(UInt_t id)                 {   return  mTauTracksInvariantMass[id];              }
Double_t        EventData::TauSignalTracksInvariantMass(UInt_t id)           {   return  mTauSignalTracksInvariantMass[id];        }
Double_t        EventData::TauMaximumHCALhitEt(UInt_t id)                    {   return  mTauMaximumHCALhitEt[id];                 }
Double_t        EventData::TauIsolationECALhitsEtSum(UInt_t id)              {   return  mTauIsolationECALhitsEtSum[id];           }
Double_t        EventData::TauIsolationTracksPtSum(UInt_t id)                {   return  mTauIsolationTracksPtSum[id];             }
Double_t        EventData::TauLeadTrackHCAL3x3hottesthitDEta(UInt_t id)      {   return  mTauLeadTrackHCAL3x3hottesthitDEta[id];   }
Double_t        EventData::TauLeadTrackHCAL3x3hitsEtSum(UInt_t id)           {   return  mTauLeadTrackHCAL3x3hitsEtSum[id];        }
Double_t        EventData::TauLeadTracksignedSipt(UInt_t id)                 {   return  mTauLeadTracksignedSipt[id];              }

Double_t        EventData::TauDisByLooseCombinedIsolationDeltaBetaCorr(UInt_t id)  { return mTauDisByLooseCombinedIsolationDeltaBetaCorr[id]; }
Double_t        EventData::TauDisDecayModeFinding(UInt_t id)                       { return mTauDisDecayModeFinding[id]; }
Double_t        EventData::TauDisAgainstElectronLoose(UInt_t id)                   { return mTauDisAgainstElectronLoose[id]; }
Double_t        EventData::TauDisAgainstMuonTight2(UInt_t id)                      { return mTauDisAgainstMuonTight2[id]; }

Double_t        EventData::TauJetPt(UInt_t id)                                     { return mTauJetPt[id];  }
Double_t        EventData::TauJetEta(UInt_t id)                                    { return mTauJetEta[id]; }
Double_t        EventData::TauJetPhi(UInt_t id)                                    { return mTauJetPhi[id]; }
						
Int_t           EventData::NPFTau()                                          {   return  mNPFTau;                                  }
Double_t        EventData::PFTauE(UInt_t id)                                 {   return  mPFTauE[id];                              }
Double_t        EventData::PFTauPt(UInt_t id)                                {   return  mPFTauPt[id];                             }
Double_t        EventData::PFTauPx(UInt_t id)                                {   return  mPFTauPx[id];                             }
Double_t        EventData::PFTauPy(UInt_t id)                                {   return  mPFTauPy[id];                             }
Double_t        EventData::PFTauPz(UInt_t id)                                {   return  mPFTauPz[id];                             }
Double_t        EventData::PFTauEta(UInt_t id)                               {   return  mPFTauEta[id];                            }
Double_t        EventData::PFTauPhi(UInt_t id)                               {   return  mPFTauPhi[id];                            }
Int_t           EventData::PFTauCharge(UInt_t id)                            {   return  mPFTauCharge[id];                         }

Double_t        EventData::PFTauEtaEtaMoment(UInt_t id)                      {   return  mPFTauEtaEtaMoment[id];                   }
Double_t        EventData::PFTauPhiPhiMoment(UInt_t id)                      {   return  mPFTauPhiPhiMoment[id];                   }
Double_t        EventData::PFTauEtaPhiMoment(UInt_t id)                      {   return  mPFTauEtaPhiMoment[id];                   }
Double_t        EventData::PFTauLeadPFChargedHadrCandsignedSipt(UInt_t id)   {   return  mPFTauLeadPFChargedHadrCandsignedSipt[id];}
Double_t        EventData::PFTauIsoPFChargedHadrCandsPtSum(UInt_t id)        {   return  mPFTauIsoPFChargedHadrCandsPtSum[id];     }
Double_t        EventData::PFTauIsoPFGammaCandsEtSum(UInt_t id)              {   return  mPFTauIsoPFGammaCandsEtSum[id];           }
Double_t        EventData::PFTauMaximumHCALPFClusterEt(UInt_t id)            {   return  mPFTauMaximumHCALPFClusterEt[id];         }
Double_t        EventData::PFTauEmFraction(UInt_t id)                        {   return  mPFTauEmFraction[id];                     }
Double_t        EventData::PFTauHcalTotOverPLead(UInt_t id)                  {   return  mPFTauHcalTotOverPLead[id];               }
Double_t        EventData::PFTauHcalMaxOverPLead(UInt_t id)                  {   return  mPFTauHcalMaxOverPLead[id];               }
Double_t        EventData::PFTauHcal3x3OverPLead(UInt_t id)                  {   return  mPFTauHcal3x3OverPLead[id];               }
Double_t        EventData::PFTauEcalStripSumEOverPLead(UInt_t id)            {   return  mPFTauEcalStripSumEOverPLead[id];         }
Double_t        EventData::PFTauBremsRecoveryEOverPLead(UInt_t id)           {   return  mPFTauBremsRecoveryEOverPLead[id];        }
Double_t        EventData::PFTauElectronPreIDOutput(UInt_t id)               {   return  mPFTauElectronPreIDOutput[id];            }
Double_t        EventData::PFTauElectronPreIDDecision(UInt_t id)             {   return  mPFTauElectronPreIDDecision[id];          }
Double_t        EventData::PFTauCaloComp(UInt_t id)                          {   return  mPFTauCaloComp[id];                       }
Double_t        EventData::PFTauSegComp(UInt_t id)                           {   return  mPFTauSegComp[id];                        }
Double_t        EventData::PFTauMuonDecision(UInt_t id)                      {   return  mPFTauMuonDecision[id];                   }

Double_t        EventData::PFTauLeadTrackPtCut(UInt_t id)                    {   return  mPFTauLeadTrackPtCut[id];                 }
Double_t        EventData::PFTauByIso(UInt_t id)                             {   return  mPFTauByIso[id];                          }
Double_t        EventData::PFTauByTaNCfrHalfPercent(UInt_t id)               {   return  mPFTauByTaNCfrHalfPercent[id];            }

Double_t        EventData::PFTauDisByLooseCombinedIsolationDeltaBetaCorr(UInt_t id) { return mPFTauDisByLooseCombinedIsolationDeltaBetaCorr[id]; }
Double_t        EventData::PFTauDisDecayModeFinding(UInt_t id)                      { return mPFTauDisDecayModeFinding[id]; }
Double_t        EventData::PFTauDisAgainstElectronLoose(UInt_t id)                  { return mPFTauDisAgainstElectronLoose[id]; }
Double_t        EventData::PFTauDisAgainstMuonTight2(UInt_t id)                     { return mPFTauDisAgainstMuonTight2[id]; }

Double_t        EventData::PFTauJetPt(UInt_t id)                                    { return mPFTauJetPt[id];  }
Double_t        EventData::PFTauJetEta(UInt_t id)                                   { return mPFTauJetEta[id]; }
Double_t        EventData::PFTauJetPhi(UInt_t id)                                   { return mPFTauJetPhi[id]; }


Int_t           EventData::WTauDecayMode()                                   {   return mWTauDecayMode;         }
Int_t           EventData::WTauN()                                           {   return mWTauN;                 }
Int_t           EventData::WTauDecayId(UInt_t id)                            {   return mWTauDecayId[id];       }
Double_t        EventData::WTauDecayPt(UInt_t id)                            {   return mWTauDecayPt[id];       }
Double_t        EventData::WTauDecayEta(UInt_t id)                           {   return mWTauDecayEta[id];      }
Double_t        EventData::WTauDecayPhi(UInt_t id)                           {   return mWTauDecayPhi[id];      }
Double_t        EventData::WTauDecayMass(UInt_t id)                          {   return mWTauDecayMass[id];     }

						
Int_t           EventData::NPhot()                                           {   return  mNPhot;                                   }
Double_t        EventData::PhotE(UInt_t id)                                  {   return  mPhotE[id];                               }
Double_t        EventData::PhotPt(UInt_t id)                                 {   return  mPhotPt[id];                              }
Double_t        EventData::PhotPx(UInt_t id)                                 {   return  mPhotPx[id];                              }
Double_t        EventData::PhotPy(UInt_t id)                                 {   return  mPhotPy[id];                              }
Double_t        EventData::PhotPz(UInt_t id)                                 {   return  mPhotPz[id];                              }
Double_t        EventData::PhotEta(UInt_t id)                                {   return  mPhotEta[id];                             }
Double_t        EventData::PhotPhi(UInt_t id)                                {   return  mPhotPhi[id];                             }
Double_t        EventData::PhotE1x5(UInt_t id)                               {   return  mPhotE1x5[id];                            }
Double_t        EventData::PhotE2x5(UInt_t id)                               {   return  mPhotE2x5[id];                            }
Double_t        EventData::PhotE5x5(UInt_t id)                               {   return  mPhotE5x5[id];                            }
Double_t        EventData::PhotSigEta(UInt_t id)                             {   return  mPhotSigEta[id];                          }
Double_t        EventData::PhotSigPhi(UInt_t id)                             {   return  mPhotSigPhi[id];                          }
Double_t        EventData::PhotEcalIso04(UInt_t id)                          {   return  mPhotEcalIso04[id];                       }
Double_t        EventData::PhotHcalIso04(UInt_t id)                          {   return  mPhotHcalIso04[id];                       }
Double_t        EventData::PhotTrackIso04(UInt_t id)                         {   return  mPhotTrackIso04[id];                      }
Double_t        EventData::PhotHasPixSeed(UInt_t id)                         {   return  mPhotHasPixSeed[id];                      }
Double_t        EventData::PhotIsPhot(UInt_t id)                             {   return  mPhotIsPhot[id];                          }
						
Int_t           EventData::NPV()                                             {   return  mNPV;                                     }
Double_t        EventData::PVx(UInt_t id)                                    {   return  mPVx[id];                                 }
Double_t        EventData::PVy(UInt_t id)                                    {   return  mPVy[id];                                 }
Double_t        EventData::PVz(UInt_t id)                                    {   return  mPVz[id];                                 }
Double_t        EventData::PVchi2(UInt_t id)                                 {   return  mPVchi2[id];                              }
Double_t        EventData::PVndof(UInt_t id)                                 {   return  mPVndof[id];                              }
Int_t           EventData::PVntracks(UInt_t id)                              {   return  mPVntracks[id];                           }
						
Int_t           EventData::nHLT()                                            {   return  mnHLT;                                    }
Int_t           EventData::HLTArray(UInt_t id)                               {   return  mHLTArray[id];                            }
Int_t           EventData::HLTArray2(UInt_t id)                              {   return  mHLTArray2[id];                           }
string          EventData::HLTNames()                                        {   return  mHLTNames;                                }
Int_t           EventData::HLTPreScale2(UInt_t id)                           {   return  mHLTPreScale2[id];                        }
Int_t           EventData::nL1()                                             {   return  mnL1;                                     }
Int_t           EventData::L1Array(UInt_t id)                                {   return  mL1Array[id];                             }
Int_t           EventData::nL1T()                                            {   return  mnL1T;                                    }
Int_t           EventData::L1TArray(UInt_t id)                               {   return  mL1TArray[id];                            }
							
Int_t           EventData::BeamHaloTight()                                   {   return  mBeamHaloTight;                           }
Int_t           EventData::BeamHaloLoose()                                   {   return  mBeamHaloLoose;                           }
						


Int_t           EventData::TIV_N()                                           {   return  mTIV_N;                                   }
Float_t         EventData::TIV(UInt_t id)                                    {   return  mTIV[id];                                 }
Float_t         EventData::TIV_pt(UInt_t id)                                 {   return  mTIV_pt[id];                              }
Float_t         EventData::TIV_px(UInt_t id)                                 {   return  mTIV_px[id];                              }
Float_t         EventData::TIV_py(UInt_t id)                                 {   return  mTIV_py[id];                              }
Float_t         EventData::TIV_pz(UInt_t id)                                 {   return  mTIV_pz[id];                              }
Float_t         EventData::TIV_phi(UInt_t id)                                {   return  mTIV_phi[id];                             }
Float_t         EventData::TIV_eta(UInt_t id)                                {   return  mTIV_eta[id];                             }
Float_t         EventData::TIV_dsz(UInt_t id)                                {   return  mTIV_dsz[id];                             }
Float_t         EventData::TIV_dxy(UInt_t id)                                {   return  mTIV_dxy[id];                             }
Float_t         EventData::TIV_d0(UInt_t id)                                 {   return  mTIV_d0[id];                              }
Float_t         EventData::TIV_dz(UInt_t id)                                 {   return  mTIV_dz[id];                              }
Float_t         EventData::TIV_dsz_corr(UInt_t id)                           {   return  mTIV_dsz_corr[id];                        }
Float_t         EventData::TIV_dxy_corr(UInt_t id)                           {   return  mTIV_dxy_corr[id];                        }
Float_t         EventData::TIV_d0_corr(UInt_t id)                            {   return  mTIV_d0_corr[id];                         }
Float_t         EventData::TIV_dz_corr(UInt_t id)                            {   return  mTIV_dz_corr[id];                         }
Float_t         EventData::TIV_dR(UInt_t id)                                 {   return  mTIV_dR[id];                              }
Int_t           EventData::TIV_lead(UInt_t id)                               {   return  mTIV_lead[id];                            }
Float_t         EventData::LowTIV()                                          {   return  mLowTIV;                                  }

Int_t           EventData::NGenPar()                                         {    return  mNGenPar;                                }
Int_t           EventData::GenParId    (UInt_t id)                           {    return  mGenParId    [id];                       }
Int_t           EventData::GenParStatus(UInt_t id)                           {    return  mGenParStatus[id];                       }
Double_t        EventData::GenParE     (UInt_t id)                           {    return  mGenParE     [id];                       }
Double_t        EventData::GenParPx    (UInt_t id)                           {    return  mGenParPx    [id];                       }
Double_t        EventData::GenParPy    (UInt_t id)                           {    return  mGenParPy    [id];                       }
Double_t        EventData::GenParPz    (UInt_t id)                           {    return  mGenParPz    [id];                       }
Double_t        EventData::GenParEta   (UInt_t id)                           {    return  mGenParEta   [id];                       }
Double_t        EventData::GenParPhi   (UInt_t id)                           {    return  mGenParPhi   [id];                       }
Int_t           EventData::GenParCharge(UInt_t id)                           {    return  mGenParCharge[id];                       }
Double_t        EventData::GenParPt    (UInt_t id)                           {    return  mGenParPt    [id];                       }
Double_t        EventData::GenParMass  (UInt_t id)                           {    return  mGenParMass  [id];                       }
Int_t           EventData::GenParMother1(UInt_t id)                          {    return  mGenParMother1[id];                      }
Int_t           EventData::GenParMother2(UInt_t id)                          {    return  mGenParMother2[id];                      }
Int_t           EventData::GenParDoughterOf(UInt_t id)                       {    return  mGenParDoughterOf[id];                   }




Double_t        EventData::GenAK5JetE         (UInt_t id)                    {    return mGenAK5JetE          [id];                } 
Double_t        EventData::GenAK5JetPt        (UInt_t id)                    {    return mGenAK5JetPt         [id];                } 
Double_t        EventData::GenAK5JetPx        (UInt_t id)                    {    return mGenAK5JetPx         [id];                } 
Double_t        EventData::GenAK5JetPy        (UInt_t id)                    {    return mGenAK5JetPy         [id];                } 
Double_t        EventData::GenAK5JetPz        (UInt_t id)                    {    return mGenAK5JetPz         [id];                } 
Double_t        EventData::GenAK5JetEta       (UInt_t id)                    {    return mGenAK5JetEta        [id];                } 
Double_t        EventData::GenAK5JetPhi       (UInt_t id)                    {    return mGenAK5JetPhi        [id];                } 
Double_t        EventData::GenAK5JetEmEnergy  (UInt_t id)                    {    return mGenAK5JetEmEnergy   [id];                } 
Double_t        EventData::GenAK5JetHadEnergy (UInt_t id)                    {    return mGenAK5JetHadEnergy  [id];                } 
                                                                 

Double_t         EventData::PDFGenScale()                                    {   return  mPDFGenScale;                            }
Double_t         EventData::PDFx1()                                          {   return  mPDFx1;                                  }
Double_t         EventData::PDFx2()                                          {   return  mPDFx2;                                  }
Int_t            EventData::PDFf1()                                          {   return  mPDFf1;                                  }
Int_t            EventData::PDFf2()                                          {   return  mPDFf2;                                  }
Double_t         EventData::PDFscale()                                       {   return  mPDFscale;                               }
Double_t         EventData::PDFpdf1()                                        {   return  mPDFpdf1;                                }
Double_t         EventData::PDFpdf2()                                        {   return  mPDFpdf2;                                }



///-----------------------------------------------------------------------------------------------------------------------------------------
  
const std::string & EventData::DataSet()   { return mDataSet;          }
  
///-----------------------------------------------------------------------------------------------------------------------------------------



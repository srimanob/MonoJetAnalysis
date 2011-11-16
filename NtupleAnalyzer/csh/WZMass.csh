#!/bin/tcsh -f

rm *_muon*
rm output.root

hadd data_muon_3.root met*_WZAnalysis_3.root 
hadd data_muon_2.root met*_WZAnalysis_2.root 

hadd qcd_muon_3.root    qcd*WZAnalysis_3*

hadd ttbar_muon_3.root  ttbar_WZAnalysis_3.root  qcd_muon_3.root

hadd zjets_muon_3.root  zjets_WZAnalysis_3.root  ttbar_WZAnalysis_3.root  qcd*WZAnalysis_3*

hadd wjets_muon_3.root  wjets_WZAnalysis_3.root  zjets_WZAnalysis_3.root  ttbar_WZAnalysis_3.root  qcd*WZAnalysis_3*


hadd qcd_muon_2.root    qcd*WZAnalysis_2*

hadd ttbar_muon_2.root  ttbar_WZAnalysis_2.root  qcd_muon_2.root

hadd zjets_muon_2.root  zjets_WZAnalysis_2.root  ttbar_WZAnalysis_2.root  qcd*WZAnalysis_2*

hadd wjets_muon_2.root  wjets_WZAnalysis_2.root  zjets_WZAnalysis_2.root  ttbar_WZAnalysis_2.root  qcd*WZAnalysis_2*

hadd zinv_muon_2.root   znunu*_WZAnalysis_2.root   wjets_WZAnalysis_2.root  zjets_WZAnalysis_2.root  ttbar_WZAnalysis_2.root  qcd*WZAnalysis_2*



Merge WlepnuMT          "M_{T} [GeV/c^{2}]"  "Events / 10 GeV/c^{2} "  wjets_muon_3 "W#rightarrowl#nu" zjets_muon_3 "Z#rightarrowl^{+}l^{-}" ttbar_muon_3 "t#bar{t}" qcd_muon_3 "QCD"  data_muon_3  "Data"
Merge WlepnuMT_50_100   "M_{T} [GeV/c^{2}]"  "Events / 10 GeV/c^{2}"  wjets_muon_3 "W#rightarrowl#nu" zjets_muon_3 "Z#rightarrowl^{+}l^{-}" ttbar_muon_3 "t#bar{t}" qcd_muon_3 "QCD"  data_muon_3  "Data"

Merge ZleplepMT          "M [GeV/c^{2}]"      "Events / 4 GeV/c^{2}"  zjets_muon_3 "Z#rightarrowl^{+}l^{-}" ttbar_muon_3 "t#bar{t}" qcd_muon_3 "QCD" data_muon_3  "Data"
Merge ZleplepMT_81_101   "M [GeV/c^{2}]"      "Events / 4 GeV/c^{2}"  zjets_muon_3 "Z#rightarrowl^{+}l^{-}" ttbar_muon_3 "t#bar{t}" qcd_muon_3 "QCD" data_muon_3  "Data"

Merge WlepnuMT_2        "M_{T} [GeV/c^{2}]"  "Events / 10 GeV/c^{2}"  wjets_muon_3 "W#rightarrowl#nu" zjets_muon_3 "Z#rightarrowl^{+}l^{-}" ttbar_muon_3 "t#bar{t}" qcd_muon_3 "QCD" data_muon_3  "Data"

Merge WlepnuMT_210        "M_{T} [GeV/c^{2}]"  "Events / 10 GeV/c^{2}"  wjets_muon_3 "W#rightarrowl#nu" zjets_muon_3 "Z#rightarrowl^{+}l^{-}" ttbar_muon_3 "t#bar{t}" qcd_muon_3 "QCD" data_muon_3  "Data"

Merge WlepnuMT_310        "M_{T} [GeV/c^{2}]"  "Events / 10 GeV/c^{2}"  wjets_muon_3 "W#rightarrowl#nu" zjets_muon_3 "Z#rightarrowl^{+}l^{-}" ttbar_muon_3 "t#bar{t}" qcd_muon_3 "QCD" data_muon_3  "Data"



Merge WlepnuMT_50_100_2 "M_{T} [GeV/c^{2}]"  "Events / 10 GeV/c^{2}"  wjets_muon_3 "W#rightarrowl#nu" zjets_muon_3 "Z#rightarrowl^{+}l^{-}" ttbar_muon_3 "t#bar{t}" qcd_muon_3 "QCD" data_muon_3  "Data"

Merge ZleplepMT_2        "M [GeV/c^{2}]"      "Events / 4 GeV/c^{2}"  zjets_muon_3 "Z#rightarrowl^{+}l^{-}" ttbar_muon_3 "t#bar{t}" qcd_muon_3 "QCD" data_muon_3  "Data"
Merge ZleplepMT_81_101_2 "M [GeV/c^{2}]"      "Events / 4 GeV/c^{2}"  zjets_muon_3 "Z#rightarrowl^{+}l^{-}" ttbar_muon_3 "t#bar{t}" qcd_muon_3 "QCD" data_muon_3  "Data"

Merge ZleplepMT_60_120    "M [GeV/c^{2}]"      "Events / 2 GeV/c^{2}"  zjets_muon_3 "Z#rightarrowl^{+}l^{-}" ttbar_muon_3 "t#bar{t}"  data_muon_3  "Data"


Merge  ZleplepPT_60_120  "Z p_{T} [GeV/c]"  "Events / 20 GeV/c"  zjets_muon_3 "Z#rightarrowl^{+}l^{-}" ttbar_muon_3 "t#bar{t}"   data_muon_3  "Data"

Merge  ZleplepPT          "Z p_{T} [GeV/c]"  "Events / 20 GeV/c"  zjets_muon_3 "Z#rightarrowl^{+}l^{-}" ttbar_muon_3 "t#bar{t}"   data_muon_3  "Data"


Merge WlepnuPT_50_100    "W p_{T} [GeV/c]"  "Events / 20 GeV/c"  wjets_muon_3 "W#rightarrowl#nu" zjets_muon_3 "Z#rightarrowl^{+}l^{-}" ttbar_muon_3 "t#bar{t}"  data_muon_3  "Data"
Merge WlepnuPT           "W p_{T} [GeV/c]"  "Events / 20 GeV/c"  wjets_muon_3 "W#rightarrowl#nu" zjets_muon_3 "Z#rightarrowl^{+}l^{-}" ttbar_muon_3 "t#bar{t}"  data_muon_3  "Data"


 
Merge NofLep          "Muon Multiplicity"  "Events  "  zinv_muon_2 "Z#rightarrow#nu#nu" wjets_muon_2 "W#rightarrowl#nu" zjets_muon_2 "Z#rightarrowl^{+}l^{-}" ttbar_muon_2 "t#bar{t}" qcd_muon_2 "QCD" data_muon_2  "Data"
 


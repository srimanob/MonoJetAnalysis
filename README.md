Monojet Analysis Package
===============

For monojet analysis

How to checkout the package
--------------
<pre><code>cmsrel CMSSW_5_3_11_patch6
cd CMSSW_5_3_11_patch6/src
cmsenv
git init
git clone https://github.com/srimanob/MonoJetAnalysis
cd MonoJetAnalysis
git checkout tags/V53X_V06D_03
cd ..
cvs co -r V00-03-04 -d CMGTools/External UserCode/CMG/CMGTools/External
cvs co -r V00-00-31_patch1 -d EGamma/EGammaAnalysisTools UserCode/EGamma/EGammaAnalysisTools
scram b
</code></pre>

How to run ntuple maker
--------------

How to run analysis code
--------------
<pre><code>AnaMonoJet  [sample name]  -1  (0 for MC, 1 for MC)  (jet,met,jetmet,btagjet,btagmet,btagjetmet)  AnaMonoJet
</code></pre>

How to commit new version of code
--------------
<pre><code>git add [ files that you edited ]
git commit -m' a message'
git push origin master
git pull
</code></pre>

Monojet Analysis Package
===============

This is 53X branch, for 8 TeV analysis.

How to checkout the package
--------------
<pre><code>cmsrel CMSSW_5_3_11_patch6
cd CMSSW_5_3_11_patch6/src
cmsenv
git init
git clone -b 53X https://github.com/srimanob/MonoJetAnalysis
cd MonoJetAnalysis
git checkout tags/V53X_V06D_05
cd ..
scp -r [your-cern-account]@lxplus.cern.ch:/afs/cern.ch/user/s/srimanob/public/ForMonoJet/Production/Ver06E/CMSSW_5_3_9_patch3/src/CMGTools ./
scp -r [your-cern-account]@lxplus.cern.ch:/afs/cern.ch/user/s/srimanob/public/ForMonoJet/Production/Ver06E/CMSSW_5_3_9_patch3/src/EGamma ./
scram b
</code></pre>

How to run ntuple maker
--------------
<pre><code>cmsrel CMSSW_5_3_9_patch3
cd  CMSSW_5_3_9_patch3
rm –r src
scp -r [your-cern-account]@lxplus.cern.ch:/afs/cern.ch/user/s/srimanob/public/ForMonoJet/Production/Ver06E/CMSSW_5_3_9_patch3/src .
cd src
scram b
cd MonojetAnalysis/NtupleAnalyzer/test/config
</code></pre>
Edit the file monojet_ntuple_template_cfg.py
<pre><code>
python monojet_ntuple_template_cfg.py
cmsRun [filename-you-get-from-previous-step]
</code></pre>

How to run analysis code
--------------
<pre><code>AnaMonoJet  [sample name]  -1  (0 for MC, 1 for MC)  (jet,met,jetmet,btagjet,btagmet,btagjetmet) jetThreshold AnaMonoJet
</code></pre>

How to commit new version of code
--------------
<pre><code>After "git checkout"
git checkout 53X
git add [ files that you edited ]
git commit -m 'comment'
git push origin 53X
git tag -a [version] -m 'comment'
git push --tags
</code></pre>

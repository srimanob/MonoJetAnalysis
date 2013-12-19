#!/bin/tcsh
foreach x(`seq 1 1 5`)
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met1                0 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met2                0 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met3                0 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met4                0 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met5                0 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met6                0 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met7                0 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met8                0 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met9                0 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met10               0 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met11               0 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met12               0 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met13               0 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met14               0 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met15               0 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff met16               0 $x $2 $3 1nd
  
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff znunu50             1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff znunu100            1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff znunu200p1          1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff znunu200p2          1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff znunu400            1 $x $2 $3 1nd

    ./makejob_cuteff.csh $1 AnaMonoJetCutEff wjets1              1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff wjets2              1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff wjets3              1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff wjets4              1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff wjets5              1 $x $2 $3 1nd 
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff wjets6              1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff wjets7              1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff wjets8              1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff wjets9              1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff wjets10             1 $x $2 $3 1nd 
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff w4jets1             1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff w4jets2             1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff w4jets3             1 $x $2 $3 1nd

    ./makejob_cuteff.csh $1 AnaMonoJetCutEff zjets               1 $x $2 $3 1nd
    
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff ttbar               1 $x $2 $3 1nd

    ./makejob_cuteff.csh $1 AnaMonoJetCutEff qcd80               1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff qcd120              1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff qcd170              1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff qcd300              1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff qcd470              1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff qcd600              1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff qcd800              1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff qcd1000             1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff qcd1400             1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff qcd1800             1 $x $2 $3 1nd

    ./makejob_cuteff.csh $1 AnaMonoJetCutEff sints               1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff sintt               1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff sinttw              1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff sintbars            1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff sintbart            1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff sintbartw           1 $x $2 $3 1nd 

    ./makejob_cuteff.csh $1 AnaMonoJetCutEff dibosonWW           1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff dibosonWZ           1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff dibosonZZ           1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff dibosonWG           1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff dibosonZLLG         1 $x $2 $3 1nd
    ./makejob_cuteff.csh $1 AnaMonoJetCutEff dibosonZvvG         1 $x $2 $3 1nd
end

#!/bin/tcsh -f


SubmitCondor   met1            AnaMonoJetCutEff  0 cuteff
SubmitCondor   met2            AnaMonoJetCutEff  0 cuteff
SubmitCondor   met3            AnaMonoJetCutEff  0 cuteff

SubmitCondor   wjets1          AnaMonoJetCutEff  1 cuteff
SubmitCondor   wjets2          AnaMonoJetCutEff  1 cuteff
SubmitCondor   wjets3          AnaMonoJetCutEff  1 cuteff



SubmitCondor   ttbar           AnaMonoJetCutEff  1 cuteff
SubmitCondor   zjets           AnaMonoJetCutEff  1 cuteff

SubmitCondor   znunu50         AnaMonoJetCutEff  1 cuteff
SubmitCondor   znunu100        AnaMonoJetCutEff  1 cuteff
SubmitCondor   znunu200        AnaMonoJetCutEff  1 cuteff
SubmitCondor   znunu400        AnaMonoJetCutEff  1 cuteff


SubmitCondor   dmhiggs          AnaMonoJetCutEff  1 cuteff
SubmitCondor   dmstop           AnaMonoJetCutEff  1 cuteff



SubmitCondor   md2d3           AnaMonoJetCutEff  1 cuteff
SubmitCondor   dmavd1          AnaMonoJetCutEff  1 cuteff

SubmitCondor   qcd170          AnaMonoJetCutEff  1 cuteff
SubmitCondor   qcd300          AnaMonoJetCutEff  1 cuteff
SubmitCondor   qcd470          AnaMonoJetCutEff  1 cuteff
SubmitCondor   qcd600          AnaMonoJetCutEff  1 cuteff
SubmitCondor   qcd800          AnaMonoJetCutEff  1 cuteff
SubmitCondor   qcd1000         AnaMonoJetCutEff  1 cuteff
SubmitCondor   qcd1400         AnaMonoJetCutEff  1 cuteff
SubmitCondor   qcd1800         AnaMonoJetCutEff  1 cuteff
SubmitCondor   sintbars        AnaMonoJetCutEff  1 cuteff
SubmitCondor   sintbart        AnaMonoJetCutEff  1 cuteff
SubmitCondor   sintbartw       AnaMonoJetCutEff  1 cuteff
SubmitCondor   sintt           AnaMonoJetCutEff  1 cuteff
SubmitCondor   sinttw          AnaMonoJetCutEff  1 cuteff




























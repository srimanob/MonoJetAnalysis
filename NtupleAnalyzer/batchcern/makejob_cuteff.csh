#!/bin/tcsh

cp -rf cmssw_cuteff_temp.job CMSSW_$1_$2_$3_$4_$5_$6_$7.job
rm -rf temp


#$1
sed s/INPUT1/$1/g CMSSW_$1_$2_$3_$4_$5_$6_$7.job > temp
mv temp CMSSW_$1_$2_$3_$4_$5_$6_$7.job
#$2
sed s/INPUT2/$2/g CMSSW_$1_$2_$3_$4_$5_$6_$7.job > temp
mv temp CMSSW_$1_$2_$3_$4_$5_$6_$7.job
#$3
sed s/INPUT3/$3/g CMSSW_$1_$2_$3_$4_$5_$6_$7.job > temp
mv temp CMSSW_$1_$2_$3_$4_$5_$6_$7.job
#$4
sed s/INPUT4/$4/g CMSSW_$1_$2_$3_$4_$5_$6_$7.job > temp
mv temp CMSSW_$1_$2_$3_$4_$5_$6_$7.job
#$5
sed s/INPUT5/$5/g CMSSW_$1_$2_$3_$4_$5_$6_$7.job > temp
mv temp CMSSW_$1_$2_$3_$4_$5_$6_$7.job
#$6
sed s/INPUT6/$6/g CMSSW_$1_$2_$3_$4_$5_$6_$7.job > temp
mv temp CMSSW_$1_$2_$3_$4_$5_$6_$7.job


##
chmod a+x CMSSW_$1_$2_$3_$4_$5_$6_$7.job


## Send job
bsub -R "rusage[mem=4000]" -q $8 -o Log_$1_$2_$3_$4_$5_$6_$7 CMSSW_$1_$2_$3_$4_$5_$6_$7.job

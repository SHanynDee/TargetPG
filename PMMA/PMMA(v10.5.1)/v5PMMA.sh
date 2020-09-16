#!/bin/bash
##### The following line will request 1 node, each with 24 cores
##### Specifying memory requirement is unlikely to be necessary, as the 
##### compute nodes have 128 GB each.
#PBS -l select=1:ncpus=24:mem=64GB
## For your own benefit, try to estimate a realistic walltime request.  Over-estimating the 
## wallclock requirement interferes with efficient scheduling, will delay the launch of the job,
## and ties up more of your CPU-time allocation untill the job has finished.
#PBS -q serial
#PBS -P PHYS1327
#PHYS1327
#PBS -l walltime=3:00:00
#PBS -o /mnt/lustre/users/shart/Geant4.10.05/TargetPG/6MeVPMMA/build/PMMA.out
#PBS -e /mnt/lustre/users/shart/Geant4.10.05/TargetPG/6MeVPMMA/build/PMMA.err
#PBS -m abe
#PBS -M 1053929@students.wits.ac.za
##### Running commands

export GEANT4VERSION=10.5.1
export ROOTVERSION=6-20-04
export GEANT4HOME=/apps/chpc/phys/hep/geant4/v${GEANT4VERSION}/lib64/Geant4-${GEANT4VERSION}
export LHOME=/mnt/lustre/users/shart/Geant4.10.05/TargetPG
export PROJDIR=$LHOME/6MeVPMMA/build
export SRCDIR=$LHOME/6MeVPMMA
module add chpc/BIOMODULES
module add gcc/9.2.0
module add cmake/3.16.3
module add chpc/phys/geant4/10.5.1
module add chpc/phys/root/6-20-04
cd $PROJDIR

export DO_NOT_SET_PHP_AS_HP=1
export G4PARTICLEHPDATA=/apps/chpc/phys/hep/geant4/datasets/G4TENDL1.3.2/
export G4PHP_DO_NOT_ADJUST_FINAL_STATE=1

module list 
cmake -DCMAKE_INSTALL_PREFIX=${G4LIB}/../.. ..
make

./radioprotection PMMA.mac

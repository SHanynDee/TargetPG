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
#PBS -o /mnt/lustre/users/shart/Geant4.10.06/TargetPG/6MeVPMMA/PMMA.out
#PBS -e /mnt/lustre/users/shart/Geant4.10.06/TargetPG/6MeVPMMA/PMMA.err
#PBS -m abe
#PBS -M 1053929@students.wits.ac.za
##### Running commands

export GEANT4VERSION=10.6.1
export ROOTVERSION=6-20-04
export GEANT4HOME=/apps/chpc/phys/hep/geant4/v${GEANT4VERSION}/lib64/Geant4-${GEANT4VERSION}
export LHOME=/mnt/lustre/users/shart/Geant4.10.06/TargetPG
export PROJDIR=$LHOME/6MeVPMMA/build
export SRCDIR=$LHOME/6MeVPMMA
module add chpc/BIOMODULES
module add gcc/9.2.0
module add cmake/3.16.3
module add chpc/phys/geant4/10.6.1
module add chpc/phys/root/6-20-04
cd $PROJDIR

export G4NEUTRONHPDATA=/apps/chpc/phys/hep/geant4/datasets/Geant4-10.6.1/data/G4NDL4.6/
export G4ENSDFSTATEDATA=/apps/chpc/phys/hep/geant4/datasets/Geant4-10.6.1/data/
export G4ENSDFSTATEDATA=/apps/chpc/phys/hep/geant4/datasets/Geant4-10.6.1/data/G4ENSDFSTATE2.2/
export G4PARTICLEXSDATA=/apps/chpc/phys/hep/geant4/datasets/Geant4-10.6.1/data/G4PARTICLEXS2.1/
export G4LEDATA=/apps/chpc/phys/hep/geant4/datasets/Geant4-10.6.1/data/G4EMLOW7.7/
export G4LEVELGAMMADATA=/apps/chpc/phys/hep/geant4/datasets/Geant4-10.6.1/data/PhotonEvaporation5.5/

module list 
cmake -DCMAKE_INSTALL_PREFIX=${G4LIB}/../.. ..
make

./radioprotection PMMA.mac

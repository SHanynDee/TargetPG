//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// Authors: S. Guatelli and J. Davis, CMPR, UOW
// 

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "AnalysisManager.hh"

#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "EventAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(AnalysisManager* analysis):G4UserRunAction(),fEdep(0.),fEdep2(0.)
{ 
  // add new units for dose
  // 
  const G4double milligray = 1.e-3*gray;
  const G4double microgray = 1.e-6*gray;
  const G4double nanogray  = 1.e-9*gray;  
  const G4double picogray  = 1.e-12*gray;
   
  new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
  new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
  new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
  new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray); 

  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fEdep);
  accumulableManager->RegisterAccumulable(fEdep2); 
  
  analysisMan = analysis;
  analysisMan -> CreateNtuples();
}

RunAction::~RunAction()
{
	delete G4AnalysisManager::Instance();
	fTxtOutput.close();
	
}

void RunAction::BeginOfRunAction(const G4Run* /*aRun*/)
{

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();
  
	analysisMan -> OpenFile();
	
	fTxtOutput.open("outfile.txt");
	fTxtOutput <<"Event" 
	<< std::setw(20) << "Track"
	<< std::setw(20) <<"PDG"
	<< std::setw(20) <<"A"
	<< std::setw(20) <<"Z"
	<< std::setw(20) <<"Parent"
	<< std::setw(20) <<"InitEkin[keV]"
	<< std::setw(20) <<"EndEkin[keV]"
	<< std::setw(20) <<"InitPosX"
	<< std::setw(20) <<"InitPosY"
	<< std::setw(20) <<"InitPosZ"
	<< std::setw(20) <<"EndPosX"
	<< std::setw(20) <<"EndPosY"
	<< std::setw(20) <<"EndPosZ"
	<< std::setw(20) <<"TotEdep[keV]"
	<< std::setw(20) <<"TotTrack[mm]"
	<< std::setw(20) <<"InitVolume\n";
	
	fTxtOutput.close();

}

void RunAction::EndOfRunAction(const G4Run* run/*aRun*/)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables 
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  // Compute dose = total energy deposit in a run and its variance
  //
  G4double edep  = fEdep.GetValue();
  G4double edep2 = fEdep2.GetValue();
  
  G4double rms = edep2 - edep*edep/nofEvents;
  if (rms > 0.) rms = std::sqrt(rms); else rms = 0.; 
  
    const DetectorConstruction* detectorConstruction= static_cast<const DetectorConstruction*>
  (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  G4double mass = detectorConstruction->GetScoringVolume()->GetMass();
  G4double dose = edep/mass;
  G4double rmsDose = rms/mass; 

   analysisMan -> finish(); 
   
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::AddEdep(G4double edep)
{
  fEdep  += edep;
  fEdep2 += edep*edep;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

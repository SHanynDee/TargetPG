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
// Authors: Susanna Guatelli, susanna@uow.edu.au,
// Authors: Jeremy Davis, jad028@uowmail.edu.au
//

#include <stdlib.h>
#include "AnalysisManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <fstream>

AnalysisManager::AnalysisManager(G4String fileName)
{
  fFileName = fileName;
}

AnalysisManager::~AnalysisManager() 
{
}

void AnalysisManager::CreateNtuples() 
{ 
  G4AnalysisManager* manager = G4AnalysisManager::Instance();
  G4cout << "Using " << manager->GetType() << G4endl;
  
  manager->SetVerboseLevel(1);
  manager->SetNtupleMerging(true);
  
  
  //creating a ntuple, containing the information about secondary particles
  //manager -> CreateNtuple("InelasticStep", "InelasticStep");
  //manager -> CreateNtupleDColumn("Step");
  //manager -> CreateNtupleDColumn("Ekin");
  //manager -> FinishNtuple();
  
  manager -> CreateNtuple("GammaVertex", "GammaVertex");
  manager -> CreateNtupleDColumn("Ekin");
  manager -> CreateNtupleDColumn("FinalA");
  manager -> CreateNtupleDColumn("FinalZ");
  manager -> CreateNtupleDColumn("Step");
  manager -> CreateNtupleDColumn("EkinProton");
  manager -> CreateNtupleDColumn("Edep");
  manager -> FinishNtuple();

  manager -> CreateNtuple("ProtonEkin", "ProtonEkin");
  manager -> CreateNtupleDColumn("Ekin");
  manager -> CreateNtupleDColumn("PositionZ");
  manager -> FinishNtuple();


  //manager->SetFirstNtupleId(1);
   
}

void AnalysisManager::OpenFile()
{
	G4AnalysisManager* manager = G4AnalysisManager::Instance();
	
	// Create a root file
  //G4String fileName = "radioprotection";

  // Create directories  
  //manager->SetNtupleDirectoryName("radioprotection_ntuple");
  

  G4bool fileOpen = manager->OpenFile(fFileName);
  if (!fileOpen) {
    G4cout << "\n---> HistoManager::book(): cannot open " 
           << fFileName << G4endl;
    return;
  }
  
}

void AnalysisManager::FillVertex(G4double Ekin, G4int FinalA, G4int FinalZ, G4double Step, G4double EkinProton, G4double Edep)
{
  G4AnalysisManager* manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(0, 0, Ekin);
  manager -> FillNtupleDColumn(0, 1, FinalA);
  manager -> FillNtupleDColumn(0, 2, FinalZ);
  manager -> FillNtupleDColumn(0, 3, Step);
  manager -> FillNtupleDColumn(0, 4, EkinProton);
  manager -> FillNtupleDColumn(0, 6, Edep);
  manager -> AddNtupleRow(0);
}

/*void AnalysisManager::FillProton(G4double Ekin, G4double Step)
{

  G4AnalysisManager* manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(0, 0, Step);
  manager -> FillNtupleDColumn(0, 1, Ekin);
  manager -> AddNtupleRow(0);
}*/

void AnalysisManager::FillProton(G4double Ekin, G4double PositionZ)
{

  G4AnalysisManager* manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(1, 0, Ekin);
  manager -> FillNtupleDColumn(1, 1, PositionZ);
  manager -> AddNtupleRow(1);
}
 
 
void AnalysisManager::finish() 
{   
    G4AnalysisManager* manager = G4AnalysisManager::Instance();    
    manager -> Write();
    manager -> CloseFile();
}













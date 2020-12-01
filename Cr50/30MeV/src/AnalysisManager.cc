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


  manager -> CreateNtuple("GammaVertex", "GammaVertex");
  manager -> CreateNtupleDColumn("Ekin");
  manager -> CreateNtupleDColumn("FinalA");
  manager -> CreateNtupleDColumn("FinalZ");
  manager -> CreateNtupleDColumn("Step");
  manager -> CreateNtupleDColumn("EkinProton");
  manager -> CreateNtupleDColumn("Edep");
  manager -> CreateNtupleDColumn("PositionX");
  manager -> CreateNtupleDColumn("PositionY");
  manager -> CreateNtupleDColumn("PositionZ");
  manager -> FinishNtuple();

/*  manager -> CreateNtuple("ProtonInfo", "ProtonInfo");
  manager -> CreateNtupleDColumn("EkinProton");
  manager -> CreateNtupleDColumn("Edep");
  manager -> CreateNtupleDColumn("PositionX");
  manager -> CreateNtupleDColumn("PositionY");
  manager -> CreateNtupleDColumn("PositionZ");
  manager -> FinishNtuple();
*/
  manager->CreateH1("Eproton","Eproton no gate", 1000, 0. ,20.);
  manager->CreateH1("Eproton_gammagate","Eproton with gamma gate", 1000, 0. ,20.);
  manager->CreateH2("EprotonvsPosX","Eproton vs PositionX", 1000, 0. , 6., 1000, 0. ,20.);
  manager->CreateH2("EprotonvsPosX_gammagate","Eproton vs PositionX with gamma gate", 1000, 0. , 6., 1000, 0. ,20.);
  manager->CreateH2("EprotonvsEgamma_gammagate","Eproton vs Egamma with gamma gate", 1000, 0. ,20., 1000, 0. ,20.);
  
  manager->CreateH2("EprotonvsPosX","Eproton vs PositionX", 1000, 0. , 6., 1000, 0. ,20.);

  //manager->SetFirstNtupleId(1);

}

void AnalysisManager::OpenFile()
{
	G4AnalysisManager* manager = G4AnalysisManager::Instance();


  G4bool fileOpen = manager->OpenFile(fFileName);
  if (!fileOpen) {
    G4cout << "\n---> HistoManager::book(): cannot open "
           << fFileName << G4endl;
    return;
  }

}

void AnalysisManager::FillVertex(G4double Ekin, G4int FinalA, G4int FinalZ, G4double Step, G4double EkinProton, G4double Edep, G4double PositionX, G4double PositionY, G4double PositionZ)
{
  G4AnalysisManager* manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(0, 0, Ekin);
  manager -> FillNtupleDColumn(0, 1, FinalA);
  manager -> FillNtupleDColumn(0, 2, FinalZ);
  manager -> FillNtupleDColumn(0, 3, Step);
  manager -> FillNtupleDColumn(0, 4, EkinProton);
  manager -> FillNtupleDColumn(0, 5, Edep);
  manager -> FillNtupleDColumn(0, 6, PositionX);
  manager -> FillNtupleDColumn(0, 7, PositionY);
  manager -> FillNtupleDColumn(0, 8, PositionZ);
  manager -> FillH1(1, EkinProton);
  manager -> FillH2(1, PositionX, EkinProton);
  manager -> FillH2(2, Ekin, EkinProton);
  manager -> AddNtupleRow(0);
}

/*
void AnalysisManager::FillProton(G4double EkinProton, G4double Edep, G4double PositionX, G4double PositionY, G4double PositionZ)
{
  G4AnalysisManager* manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(1, 0, EkinProton);
  manager -> FillNtupleDColumn(1, 1, Edep);
  manager -> FillNtupleDColumn(1, 2, PositionX);
  manager -> FillNtupleDColumn(1, 3, PositionY);
  manager -> FillNtupleDColumn(1, 4, PositionZ);
  manager -> AddNtupleRow(1);
}
*/

void AnalysisManager::FillProton(G4double Eproton, G4double PosX)
{
  G4AnalysisManager* manager = G4AnalysisManager::Instance();
  manager -> FillH1(0, Eproton);
  manager -> FillH2(0, PosX, Eproton);
}

void AnalysisManager::finish()
{
    G4AnalysisManager* manager = G4AnalysisManager::Instance();
    manager -> Write();
    manager -> CloseFile();
}

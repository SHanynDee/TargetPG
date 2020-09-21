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
// $Id: StackingAction.cc 66536 2012-12-19 14:32:36Z ihrivnac $
// 
/// \file StackingAction.cc
/// \brief Implementation of the B3StackingAction class

#include "StackingAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include "G4Track.hh"
#include "G4NeutrinoE.hh"
#include "AnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::StackingAction(RunAction* runAction, EventAction* EventAction, AnalysisManager* pAnalysis)
:runStackAction(runAction), fEventAction(EventAction)
{
   analysis = pAnalysis; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::~StackingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack 
StackingAction::ClassifyNewTrack(const G4Track* track)
{

/*		G4ThreeVector vertex_pos = track -> GetPosition();
		if(vertex_pos.getX() >= 0 && vertex_pos.getX() < 300)
		{
			G4ThreeVector vertex_direction = track -> GetMomentumDirection();
			G4double vertex_energy = track -> GetKineticEnergy();
			analysis -> FillVertex(gammaEkin[i], FinalA, FinalZ, protonStep, protonE, protonStep, Edep);
		}
*/
	

  //  if (track->GetDynamicParticle() ->GetPDGcode() == 22) {
		//G4cout <<track->GetDynamicParticle() ->GetPDGcode() <<"\t" << track->GetParticleDefinition()->GetAtomicNumber() <<"\t" << track->GetParticleDefinition()->GetAtomicMass()<<"\t" <<track -> GetKineticEnergy()/MeV <<"\t" <<track -> GetCreatorProcess() -> GetProcessName()<<"\t"<< track ->GetParentID() << G4endl;
		//G4cout << "Ciao" << G4endl;
    	G4double vertex_energy = track -> GetKineticEnergy();
    	G4ThreeVector vertex_pos = track ->GetPosition();
    	G4ThreeVector vertex_direction = track -> GetMomentumDirection();
    	//analysis -> FillVertex(gammaEkin[i], FinalA, FinalZ, protonStep, protonE, Edep);
	//}
        
	
    
    //fEventAction->ResetPassCounter(); //collamaf: at each new track we reset the pass counter
    
	
	
	return fUrgent;
}
//kill secondary neutrino
//  if (track->GetDefinition() == G4NeutrinoE::NeutrinoE()) return fKill;
//  else return fUrgent;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

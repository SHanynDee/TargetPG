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

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "StackingAction.hh"
#include "G4RunManager.hh"
#include "AnalysisManager.hh"
#include "RunAction.hh"
#include "G4GeneralParticleSource.hh"

ActionInitialization::ActionInitialization(AnalysisManager* analysisMan):
G4VUserActionInitialization()
{
 analysis = analysisMan;
}


ActionInitialization::~ActionInitialization()
{
}

void ActionInitialization::BuildForMaster() const
{
	// In MT mode, to be clearer, the RunAction class for the master thread might be
	// different than the one used for the workers.
	// This RunAction will be called before and after starting the
	// workers.
	SetUserAction(new RunAction(analysis));
        RunAction* runAction = new RunAction;
        SetUserAction(runAction);

}

void ActionInitialization::Build() const
{
	// Initialize the primary particles
	PrimaryGeneratorAction* primary = new PrimaryGeneratorAction(analysis);
	SetUserAction(primary); 
	
	RunAction* runAction = new RunAction;
        SetUserAction(runAction);
        
	RunAction* run = new RunAction(analysis);
	SetUserAction(run);
	
	EventAction* eventAction = new EventAction(runAction);
        SetUserAction(eventAction);
	
	EventAction* event = new EventAction(analysis);
	SetUserAction(event);

	SteppingAction* step = new SteppingAction(eventAction);
	SetUserAction(step);
	
	SteppingAction* stepping = new SteppingAction(analysis);
	SetUserAction(stepping);
	
	StackingAction* stacking = new StackingAction(run, event, analysis);
        SetUserAction(stacking);
	
}  


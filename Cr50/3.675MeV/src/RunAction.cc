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
#include "AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"
#include "G4Run.hh"


RunAction::RunAction(AnalysisManager* analysis)
{ 

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

void RunAction::EndOfRunAction(const G4Run* /*aRun*/)
{
   analysisMan -> finish(); 
}


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
// Hadrontherapy advanced example for Geant4
// See more at: https://twiki.cern.ch/twiki/bin/view/Geant4/AdvancedExamplesHadrontherapy


#include "DetectorConstruction.hh"
#include "DetectorConstructionMessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4SystemOfUnits.hh"

   DetectorConstructionMessenger::DetectorConstructionMessenger(DetectorConstruction* detector)
:TargetGeom(detector)

{

    GeomDir = new G4UIdirectory("/changeTarget/");
    GeomDir -> SetGuidance("Command to Change geometry");

    changeTargetMatCmd = new G4UIcmdWithAString("/changeTarget/Material", this);
    changeTargetMatCmd -> SetGuidance("Change the target material");
    changeTargetMatCmd -> SetParameterName("TargetMaterial", false);
    changeTargetMatCmd -> SetDefaultValue("G4_BRAIN_ICRP");
    changeTargetMatCmd -> AvailableForStates(G4State_Idle);

    changeTargetSizeCmd = new G4UIcmdWith3VectorAndUnit("/changeTarget/Size",this);
    changeTargetSizeCmd -> SetGuidance("Insert sizes for X Y and Z dimensions of the Target");
    changeTargetSizeCmd -> SetParameterName("TargetSizeAlongX", "TargetSizeAlongY", "TargetSizeAlongZ", false);
    changeTargetSizeCmd -> SetDefaultUnit("mm");
    changeTargetSizeCmd -> SetUnitCandidates("nm um mm cm");
    changeTargetSizeCmd -> AvailableForStates(G4State_Idle);

}

DetectorConstructionMessenger::~DetectorConstructionMessenger()
{ 
    delete changeTargetMatCmd;
    delete changeTargetSizeCmd;
    delete GeomDir; 
}




//void DetectorConstructionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
//{ 
//    if( command == changeTargetMatCmd )
//    {
//		TargetGeom -> SetTargetMaterial(newValue);
//    }
//    else if( command == changeTargetSizeCmd)
//    {
//        TargetGeom -> SetTargetSize(changeTargetSizeCmd  -> GetNew3VectorValue(newValue));
//    }
//}


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

#ifndef DetectorConstructionMessenger_h
#define DetectorConstructionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"


class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAString;

class DetectorConstructionMessenger: public G4UImessenger
{
  public:
  DetectorConstructionMessenger(DetectorConstruction*);
  ~DetectorConstructionMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
private:

  // Pointer to the detector component
  DetectorConstruction* TargetGeom;

  G4UIdirectory* GeomDir; // Control of the geometry 
 
  G4UIcmdWithAString* changeTargetMatCmd;
  G4UIcmdWith3VectorAndUnit* changeTargetSizeCmd;
  // UI command to the TEPC position relative to the waterphantom
    

};
#endif

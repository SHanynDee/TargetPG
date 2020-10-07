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

#include "DetectorConstruction.hh"
#include "DetectorConstructionMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4PhysicalConstants.hh"
#include "G4RunManager.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4SystemOfUnits.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4AssemblyVolume.hh"
#include "G4Region.hh"

using namespace std;

DetectorConstruction::DetectorConstruction(AnalysisManager* analysis_manager):
logicTreatmentRoom(0), physicalTreatmentRoom(0), lTarget(0), pTarget(0)
{
  analysis = analysis_manager;
  TargetSize.setX(1*mm);
  TargetSize.setY(6*mm);
  TargetSize.setZ(1*mm);

}

DetectorConstruction::~DetectorConstruction(){

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	//messenger to move the TEPC
	dMessenger = new DetectorConstructionMessenger(this);

  
    // Treatment room sizes
    const G4double worldX = 1.0 *cm;
    const G4double worldY = 2.0 *cm;
    const G4double worldZ = 2.0 *cm;
    G4bool isotopes = false;
    
    //G4Material* airNist =  G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR", isotopes);
    G4Material* vacuumNist =  G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic", isotopes);

    G4Material* worldMaterial = vacuumNist;
    
    G4Box* treatmentRoom = new G4Box("World",
                                     worldX,
                                     worldY,
                                     worldZ);
    
    logicTreatmentRoom = new G4LogicalVolume(treatmentRoom,
                                             worldMaterial,
                                             "World",
                                             0,0,0);
    
    physicalTreatmentRoom = new G4PVPlacement(0,
                                              G4ThreeVector(),
                                              "World",
                                              logicTreatmentRoom,
                                              0,
                                              false,
                                              0);
    
    
    // The treatment room is invisible in the Visualisation
    logicTreatmentRoom -> SetVisAttributes (G4VisAttributes::GetInvisible());
    

    G4String symbol;                             
  G4double a;
  G4int z;
    //ElF19
    a = 19.00*g/mole;
    G4Element* elF19 = new G4Element ("Fluorine19", "F19", z=9.,a );
    
    //El31P
    a=30.97*g/mole;
    z=15.;
    G4Element* elP31 = new G4Element ("Phosphorus31", "P31", z, a );

    //ElCu63
     a=62.9295975*g/mole;
     z=29;
     G4Element* elCu63 = new G4Element ("Copper63", "Cu63", z, a );

     //ElSc45
     a=44.955912*g/mole;
     z=21;
     G4Element* elSc45 = new G4Element ("Scandium45", "Sc45", z, a );

     //ElNi60
     a=59.930786*g/mole;
     z=28;
     G4Element* elNi60 = new G4Element ("Nikel60", "Ni60", z, a );

     //ElY90
     a=88.90585*g/mole;
     z=39;
     G4Element* elY90 = new G4Element ("Ittrio90", "Y90", z, a );

     //ElCr50
     a=49.946041*g/mole;
     z=24;
     G4Element* elCr50 = new G4Element ("Chromium50", "Cr50", z, a );
     
     //63Cu
     G4Material*  Cu63 = new G4Material("Cu63", 8.96*g/cm3, 1);
     Cu63 -> AddElement(elCu63, 1);
    
    //19F
    G4Material* F19 = new G4Material("F19", 1.696*g/cm3, 1);
    F19 -> AddElement(elF19, 1);
    
    //31P
    G4Material*  P31 = new G4Material("P31", 1.823*g/cm3, 1);
    P31 -> AddElement(elP31, 1);

    //45Sc
    G4Material*  Sc45 = new G4Material("Sc45", 2.985*g/cm3, 1);
    Sc45 -> AddElement(elSc45, 1);

    //60Ni
    G4Material*  Ni60 = new G4Material("Ni60", 8.908*g/cm3, 1);
    Ni60 -> AddElement(elNi60, 1);

    //90Y
    G4Material*  Y90 = new G4Material("Y90", 4.472*g/cm3, 1);
    Y90 -> AddElement(elY90, 1);

    //50Cr                                                                                                                                   
    G4Material*  Cr50 = new G4Material("Cr50", 7.14*g/cm3, 1);
    Cr50 -> AddElement(elCr50, 1);

    
    G4Material* TargetMat = G4NistManager::Instance()->FindOrBuildMaterial("G4_BRAIN_ICRP", isotopes);
    G4Material* PMMA_MAT = G4NistManager::Instance()->FindOrBuildMaterial("G4_PLEXIGLASS", isotopes);
    G4Material* Chromium = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cr", isotopes);
    //TargetMat = P31;

   TargetMat = Cr50;
    
    sTarget = new G4Box("sTarget",
                                     TargetSize.getX()/2.,
                                     TargetSize.getY()/2.,
                                     TargetSize.getZ()/2.);
    
    lTarget = new G4LogicalVolume(sTarget,
                                             TargetMat,
                                             "lTarget",
                                             0,0,0);
    
    pTarget = new G4PVPlacement(0,
                                G4ThreeVector(TargetSize.getX()/2.,0.,0.),
                                              lTarget,
                                              "pTarget",
                                              logicTreatmentRoom,
                                              0,
                                              false,
                                              0);
    
    

        
return physicalTreatmentRoom; 

}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////// MESSENGER ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void DetectorConstruction::SetTargetMaterial(G4String materialChoice)
{
if (G4Material* pttoMaterial = G4NistManager::Instance()->FindOrBuildMaterial(materialChoice, false) )
    {
      if (pttoMaterial)
        {
	  //AbsMaterial  = pttoMaterial;
	  lTarget -> SetMaterial(pttoMaterial);
	  G4cout << "The material of the Absorber has been changed to " << materialChoice << G4endl;
        }
    }
  else
    {
      G4cout << "WARNING: material \"" << materialChoice << "\" doesn't exist in NIST elements/materials"
	    " table [located in $G4INSTALL/source/materials/src/G4NistMaterialBuilder.cc]" << G4endl;
      G4cout << "Use command \"/parameter/nist\" to see full materials list!" << G4endl;
    }

}

void DetectorConstruction::SetTargetSize(G4ThreeVector size)
{
  TargetSize = size;
  G4cout << "TARGET SIZE CHANGED:" << TargetSize.getX()/mm <<" "<<TargetSize.getY()/mm <<" " <<TargetSize.getZ()/mm <<G4endl;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

/*void DetectorConstruction::SetIsotopeFraction(G4double fraction)
{
    if (fraction < 0)
    	fFraction = 100;
    else
	{
        G4Material* 
       	TumorMaterial  = pttoMaterial;
        logicTumor -> SetMaterial(pttoMaterial);
        G4cout << "The material of the Tumor has been changed to " << materialChoice << G4endl;
    	}
  else
    {
      G4cout << "WARNING: material \"" << materialChoice << "\" doesn't exist in NIST elements/materials"
            " table [located in $G4INSTALL/source/materials/src/G4NistMaterialBuilder.cc]" << G4endl;
      G4cout << "Use command \"/parameter/nist\" to see full materials list!" << G4endl;
    }

}
*/

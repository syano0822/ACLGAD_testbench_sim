#include "G4NistManager.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

using namespace std;
  
class MyMaterial : public G4VUserDetectorConstruction {
public:

  static G4Material* DefineBrass() {
    G4NistManager* nist = G4NistManager::Instance();

    // 必要な元素を取得
    G4Element* Cu = nist->FindOrBuildElement("Cu");
    G4Element* Zn = nist->FindOrBuildElement("Zn");
    
    // 真鍮の定義
    G4double density = 8.5 * g/cm3;
    G4Material* brass = new G4Material("Brass", density, 2);
    brass->AddElement(Cu, 0.70);
    brass->AddElement(Zn, 0.30);

    return brass;
  }
  
  static G4Material* DefineFusedSilica()
  {
    G4NistManager* nist = G4NistManager::Instance();

    // シリコンと酸素を取得
    G4Element* Si = nist->FindOrBuildElement("Si");
    G4Element* O  = nist->FindOrBuildElement("O");

    // Fused Silicaの密度（約 2.20 g/cm^3）
    G4double density = 2.20*g/cm3;

    // Fused Silicaを定義 (SiO2)
    G4Material* fusedSilica = new G4Material("FusedSilica", density, 2);
    fusedSilica->AddElement(Si, 1);
    fusedSilica->AddElement(O,  2);

    return fusedSilica;
  }


  static G4Material* DefineS20()
  {
    G4NistManager* nist = G4NistManager::Instance();

    auto S20 = new G4Material("S20", 3.0*g/cm3, 4);
    S20->AddElement(G4Element::GetElement("Na"), 1);
    S20->AddElement(G4Element::GetElement("K"), 1);
    S20->AddElement(G4Element::GetElement("Sb"), 1);
    S20->AddElement(G4Element::GetElement("Cs"), 1);
    return S20;
  }

  
  static G4Material* DefinePLA()
  {
    ///*
    G4NistManager* nist = G4NistManager::Instance();
    G4Element* C  = nist->FindOrBuildElement("C");
    G4Element* H  = nist->FindOrBuildElement("H");
    G4Element* O  = nist->FindOrBuildElement("O");
  
    G4double density_PLA = 1.25*g/cm3;
    //G4double density_PLA = 1.56*g/cm3;
    
    auto* PLA = new G4Material("PLA", density_PLA, 3);
    PLA->AddElement(C, 3);
    PLA->AddElement(H, 4);
    PLA->AddElement(O, 2);
    return PLA;
    //*/
    /*
    G4NistManager* nist = G4NistManager::Instance();
    G4Element* C  = nist->FindOrBuildElement("C");
    G4Element* H  = nist->FindOrBuildElement("H");
    G4Element* O  = nist->FindOrBuildElement("O");
  
    G4double density_PLA = 1.25*g/cm3;
    
    auto* PLA = new G4Material("PLA", density_PLA, 3);
    PLA->AddElement(C, 3);
    PLA->AddElement(H, 4);
    PLA->AddElement(O, 2);
    
    auto* air = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
    
    G4double f = 0.1;
    G4Material* PLAmix = new G4Material("PLA_mix",
					  f * density_PLA + (1.-f)*air->GetDensity(),
					  2);
    PLAmix->AddMaterial(PLA,     f);
    PLAmix->AddMaterial(air,  1.-f);
    
    return PLAmix;
    */
  }

  static G4Material* DefinePLA15()
  {
    G4NistManager* nist = G4NistManager::Instance();
    G4Element* C  = nist->FindOrBuildElement("C");
    G4Element* H  = nist->FindOrBuildElement("H");
    G4Element* O  = nist->FindOrBuildElement("O");
  
    G4double density_PLA = 1.25*g/cm3;
    //G4double density_PLA = 1.56*g/cm3;
    
    auto* PLA = new G4Material("PLA", density_PLA, 3);
    PLA->AddElement(C, 3);
    PLA->AddElement(H, 4);
    PLA->AddElement(O, 2);
    
    auto* air = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
    
    G4double f = 0.15;
    G4Material* PLAmix = new G4Material("PLA_mix",
					  f * density_PLA + (1.-f)*air->GetDensity(),
					  2);
    PLAmix->AddMaterial(PLA,     f);
    PLAmix->AddMaterial(air,  1.-f);
    
    return PLAmix;
  }

};

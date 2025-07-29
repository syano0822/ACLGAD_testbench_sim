string test_bench_name = "SC2PC2L10C0";

// C++ 標準ライブラリ
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>

// ROOT
#include "TFile.h"
#include "TH2F.h"

// CADMesh
#include "TessellatedMesh.hh"

// 自作ヘッダー
//#include "MyMaterial.hh"
//#include "MyGlobals.hh"
//#include "TrackingAction.hh"
#include "MyPhotocathodeSD.hh"

// Geant4 コアランタイム／UI
#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4SDManager.hh"

// 物理過程リスト
#include "G4EmStandardPhysics_option4.hh"
#include "QBBC.hh"
#include "FTFP_BERT.hh"
#include "G4OpticalPhysics.hh"

// ジオメトリ構築用
#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"


// 可視化属性
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

// ユニットとベクトル
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

using namespace std;

class MyConstructTestBenchV3 : public G4VUserDetectorConstruction {
public:
  
  G4VPhysicalVolume* Construct() override {
    
    auto worldMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
    //auto worldMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
    
    auto worldSolid   = new G4Box("World", 1.0*m, 1.0*m, 1.0*m);
    auto worldLogical = new G4LogicalVolume(worldSolid,
                                            worldMaterial,
                                            "WorldLogical");
    auto worldPhys    = new G4PVPlacement(nullptr,
                                          G4ThreeVector(),
                                          worldLogical,
                                          "AirPhys",
                                          nullptr,
                                          false, 0);
    
    auto invisibleAttr = new G4VisAttributes();
    invisibleAttr->SetVisibility(false);
    worldLogical->SetVisAttributes(invisibleAttr);
    
    auto pcbMaterial = MyMaterial::DefinePLA();
    auto jigMaterial = MyMaterial::DefinePLA15();
    auto sensorMaterial = MyMaterial::DefinePLA();
    auto pmt_bodyMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");    
    auto collimatorMaterial = MyMaterial::DefinePLA();
    auto source_windowMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
    auto source_goldMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_Au");    
    auto sourceMaterial = MyMaterial::DefineBrass();
    
    ///*
    auto collimatorMesh     = CADMesh::TessellatedMesh::FromSTL(Form("../../cad/v3/mesh/%s/PMT_Collimator.stl",test_bench_name.c_str()));	
    auto collimatorSolid    = collimatorMesh->GetSolid();
    auto collimatorLogical   = new G4LogicalVolume(collimatorSolid, collimatorMaterial, "CollimatorLogical");
    new G4PVPlacement(nullptr,
		      G4ThreeVector(),
		      collimatorLogical,
		      "CollimatorPhys",
		      worldLogical,
		      false, 1);
    auto collimatorVis = new G4VisAttributes(G4Colour::Green());
    collimatorVis->SetVisibility(true);
    collimatorLogical->SetVisAttributes(collimatorVis);
    
    auto source_collimatorMesh     = CADMesh::TessellatedMesh::FromSTL(Form("../../cad/v3/mesh/%s/Source_Collimator.stl",test_bench_name.c_str()));	
    auto source_collimatorSolid    = source_collimatorMesh->GetSolid();
    auto source_collimatorLogical   = new G4LogicalVolume(source_collimatorSolid, collimatorMaterial, "Source_CollimatorLogical");
    new G4PVPlacement(nullptr,
		      G4ThreeVector(),
		      source_collimatorLogical,
		      "Source_CollimatorPhys",
		      worldLogical,
		      false, 1);
    auto source_collimatorVis = new G4VisAttributes(G4Colour::Green());
    source_collimatorVis->SetVisibility(true);
    source_collimatorLogical->SetVisAttributes(source_collimatorVis);
    //*/
    auto sourceMesh     = CADMesh::TessellatedMesh::FromSTL(Form("../../cad/v3/mesh/%s/Source.stl",test_bench_name.c_str()));	
    auto sourceSolid    = sourceMesh->GetSolid();
    auto sourceLogical   = new G4LogicalVolume(sourceSolid, sourceMaterial, "SourceLogical");
    new G4PVPlacement(nullptr,
		      G4ThreeVector(),
		      sourceLogical,
		      "SourcePhys",
		      worldLogical,
		      false, 1);
    auto sourceVis = new G4VisAttributes(G4Colour::Green());
    sourceVis->SetVisibility(false);
    sourceLogical->SetVisAttributes(sourceVis);

    auto source_windowMesh     = CADMesh::TessellatedMesh::FromSTL(Form("../../cad/v3/mesh/%s/Source_Window.stl",test_bench_name.c_str()));	
    auto source_windowSolid    = source_windowMesh->GetSolid();
    auto source_windowLogical   = new G4LogicalVolume(source_windowSolid, source_windowMaterial, "Source_WindowLogical");
    new G4PVPlacement(nullptr,
		      G4ThreeVector(),
		      source_windowLogical,
		      "Source_WindowPhys",
		      worldLogical,
		      false, 1);
    auto source_windowVis = new G4VisAttributes(G4Colour::Green());
    source_windowVis->SetVisibility(true);
    source_windowLogical->SetVisAttributes(source_windowVis);

    auto source_goldMesh     = CADMesh::TessellatedMesh::FromSTL(Form("../../cad/v3/mesh/%s/Source_Gold.stl",test_bench_name.c_str()));	
    auto source_goldSolid    = source_goldMesh->GetSolid();
    auto source_goldLogical   = new G4LogicalVolume(source_goldSolid, source_goldMaterial, "Source_GoldLogical");
    new G4PVPlacement(nullptr,
		      G4ThreeVector(),
		      source_goldLogical,
		      "Source_GoldPhys",
		      worldLogical,
		      false, 1);
    auto source_goldVis = new G4VisAttributes(G4Colour::Yellow());
    source_goldVis->SetVisibility(true);
    source_goldLogical->SetVisAttributes(source_goldVis);

    
    /*
    auto jigMesh     = CADMesh::TessellatedMesh::FromSTL(Form("../../cad/v3/mesh/%s/Jig.stl",test_bench_name.c_str()));	
    auto jigSolid    = jigMesh->GetSolid();
    auto jigLogical   = new G4LogicalVolume(jigSolid, jigMaterial, "Source_StageLogical");
    new G4PVPlacement(nullptr,
		      G4ThreeVector(),
		      jigLogical,
		      "Source_StagePhys",
		      worldLogical,
		      false, 1);
    auto jigVis = new G4VisAttributes(G4Colour::White());
    jigVis->SetVisibility(false);
    jigLogical->SetVisAttributes(jigVis);
    */
    /*
    auto pcb1Mesh     = CADMesh::TessellatedMesh::FromSTL("../../cad/v3/mesh/PCB.stl");	
    auto pcb1Solid    = pcb1Mesh->GetSolid();
    auto pcb1Logical  = new G4LogicalVolume(pcb1Solid, pcbMaterial, "PCBLogical");
    new G4PVPlacement(nullptr,
		      G4ThreeVector(),
		      pcb1Logical,
		      "PCBPhys",
		      worldLogical,
		      false, 2);
    auto pcb1Vis = new G4VisAttributes(G4Colour::White());
    pcb1Vis->SetVisibility(false);
    pcb1Logical->SetVisAttributes(pcb1Vis);
    */
    
    if (!(test_bench_name.find("C0") != std::string::npos)){
      auto sensor1Mesh     = CADMesh::TessellatedMesh::FromSTL(Form("../../cad/v3/mesh/%s/Sensor.stl",test_bench_name.c_str()));	
      auto sensor1Solid    = sensor1Mesh->GetSolid();
      auto sensor1Logical  = new G4LogicalVolume(sensor1Solid, sensorMaterial, "SENSORLogical");
      new G4PVPlacement(nullptr,
			G4ThreeVector(),
			sensor1Logical,
			"SENSORPhys",
			worldLogical,
			false, 2);
      auto sensor1Vis = new G4VisAttributes(G4Colour::Red());
      sensor1Vis->SetVisibility(true);
      sensor1Logical->SetVisAttributes(sensor1Vis);
    }
    
    auto pmt_bodyMesh     = CADMesh::TessellatedMesh::FromSTL(Form("../../cad/v3/mesh/%s/PMT.stl",test_bench_name.c_str()));	
    auto pmt_bodySolid    = pmt_bodyMesh->GetSolid();
    auto pmt_bodyLogical  = new G4LogicalVolume(pmt_bodySolid, pmt_bodyMaterial, "PMT_BODYLogical");
    auto pmt_bodyPhysical = new G4PVPlacement(nullptr,
					      G4ThreeVector(),
					      pmt_bodyLogical,
					      "PMT_BODYPhys",
					      worldLogical,
					      false, 2);
    auto pmt_bodyVis = new G4VisAttributes(G4Colour::Cyan());
    pmt_bodyVis->SetVisibility(false);
    pmt_bodyLogical->SetVisAttributes(pmt_bodyVis);

    auto fusedSilica = MyMaterial::DefineFusedSilica();
    G4MaterialPropertiesTable *fusedSilica_MPT = new G4MaterialPropertiesTable();
    fusedSilica_MPT->AddProperty("RINDEX", "Fused Silica");
    fusedSilica->SetMaterialPropertiesTable(fusedSilica_MPT);
    
    auto pmt_glassMesh     = CADMesh::TessellatedMesh::FromSTL(Form("../../cad/v3/mesh/%s/PMT_Glass.stl",test_bench_name.c_str()));	
    auto pmt_glassSolid    = pmt_glassMesh->GetSolid();
    auto pmt_glassLogical  = new G4LogicalVolume(pmt_glassSolid, fusedSilica, "PMT_GLASSLogical"); // ここが重要な変更点	
    auto pmt_glassPhysical = new G4PVPlacement(nullptr,
					       G4ThreeVector(),
					       pmt_glassLogical,
					       "PMT_GLASSPhys",
					       worldLogical,
					       false, 2);
    auto pmt_glassVis = new G4VisAttributes(G4Colour::Blue());
    pmt_glassVis->SetVisibility(false);
    pmt_glassLogical->SetVisAttributes(pmt_glassVis);

    
    auto S20 = MyMaterial::DefineFusedSilica();
    G4MaterialPropertiesTable *S20_MPT = new G4MaterialPropertiesTable();
    S20_MPT->AddProperty("RINDEX", "Fused Silica");
    S20->SetMaterialPropertiesTable(S20_MPT);
    
    auto pmt_cathodMesh     = CADMesh::TessellatedMesh::FromSTL(Form("../../cad/v3/mesh/%s/PMT_Cathod.stl",test_bench_name.c_str()));	
    auto pmt_cathodSolid    = pmt_cathodMesh->GetSolid();
    auto pmt_cathodLogical  = new G4LogicalVolume(pmt_cathodSolid, S20, "PhotocathodeLogical");
    auto pmt_cathodPhysical = new G4PVPlacement(nullptr,
					      G4ThreeVector(),
						pmt_cathodLogical,
					      "PMT_CATHODPhys",
					      worldLogical,
					      false, 2);
    auto pmt_cathodVis = new G4VisAttributes(G4Colour::Cyan());
    pmt_cathodVis->SetVisibility(false);
    pmt_cathodLogical->SetVisAttributes(pmt_cathodVis);

    auto photocathodeSurface = new G4OpticalSurface("PhotocathodeSurface");
    photocathodeSurface->SetType(dielectric_metal);
    photocathodeSurface->SetFinish(polished);
    photocathodeSurface->SetModel(unified);

    const G4int nEntries = 2;
    G4double photonEnergyPC[nEntries] = {2.0*eV, 3.5*eV};
    G4double reflectivityPC[nEntries] = {0.24, 0.24};  // 推奨値（仮）
    G4double efficiencyPC[nEntries] = {1.0000000000, 1.0000000000};    // QE (推奨値)
    
    auto surfaceMPT = new G4MaterialPropertiesTable();
    surfaceMPT->AddProperty("REFLECTIVITY", photonEnergyPC, reflectivityPC, nEntries);
    //surfaceMPT->DumpTable();
    photocathodeSurface->SetMaterialPropertiesTable(surfaceMPT);
    
    // LogicalBorderSurfaceの設定
    new G4LogicalBorderSurface("GlassToPhotocathode",
			       pmt_glassPhysical,          // 窓の物理ボリューム
			       pmt_cathodPhysical,   // 光電面の物理ボリューム
			       photocathodeSurface);
    
    auto* sdManager = G4SDManager::GetSDMpointer();
    auto* photocathodeSD = new MyPhotocathodeSD("PhotocathodeSD");
    sdManager->AddNewDetector(photocathodeSD);
    pmt_cathodLogical->SetSensitiveDetector(photocathodeSD);
    
    return worldPhys;
  }
};

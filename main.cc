#include "MyMaterial.hh"
#include "MyConstructTestBenchV3.hh"
#include "PrimaryGeneratorAction.hh"

//#include "MyGlobals.hh"
//#include "TrackingAction.hh"
//#include "ActionInitialization.hh"
//#include "SteppingAction.hh"
//#include "EventAction.hh"
//#include "Globals.hh"

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4NistManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4OpticalPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4VModularPhysicsList.hh"

// CADMesh
#include "TessellatedMesh.hh"

#include "FTFP_BERT.hh"
#include "QBBC.hh"
#include "Shielding.hh"


#include "TFile.h"
#include "TH2F.h"

using namespace std;

class MyPhysicsList : public G4VModularPhysicsList
{
public:
    MyPhysicsList()
    {
      RegisterPhysics(new G4EmStandardPhysics_option4());
      RegisterPhysics(new G4OpticalPhysics());
    }
};

int main(int argc, char** argv) {

  // 1) RunManager の生成
  auto* runManager = G4RunManagerFactory::CreateRunManager();
  
  runManager->SetUserInitialization(new MyConstructTestBenchV3());
  runManager->SetUserInitialization(new MyPhysicsList());
  runManager->SetUserAction(new PrimaryGeneratorAction()); 
  //runManager->SetUserInitialization(new ActionInitialization());  
  //auto* eventAction = new EventAction();
  //runManager->SetUserAction(eventAction);
  //runManager->SetUserAction(new SteppingAction(eventAction));
  
  // 3) 初期化
  runManager->Initialize();

  // 4) Visualization manager の初期化
  auto* visManager = new G4VisExecutive;
  visManager->Initialize();

  // 5) UI マネージャの取得
  auto* uiManager = G4UImanager::GetUIpointer();
  
  // 6) 対話モード判定＆マクロ実行
  G4UIExecutive* uiExec = nullptr;
  bool isInteractive = (argc == 1);
  if (isInteractive) {
    uiExec = new G4UIExecutive(argc, argv);
    uiManager->ApplyCommand("/control/execute ../init_vis.mac");
    uiManager->ApplyCommand("/run/beamOn 1");
  } else {
    const G4String batchMacro = argv[1];
    uiManager->ApplyCommand("/control/execute " + batchMacro);
    // 7) ビームオン
    uiManager->ApplyCommand("/run/beamOn 10000");
  }
  
  // 8) インタラクティブセッション開始
  if (uiExec) {
    uiExec->SessionStart();
    delete uiExec;
  }

  // 9) 後片付け
  delete visManager;
  delete runManager;
  return 0;

}

#include "MyPhotocathodeSD.hh"
#include "MyPhotocathodeHit.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpticalPhoton.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4StepPoint.hh"


MyPhotocathodeSD::MyPhotocathodeSD(const G4String& name)
    : G4VSensitiveDetector(name), fHitsCollection(nullptr), fHCID(-1)
{
  collectionName.insert("PhotocathodeHitsCollection");

  fQE = new TF1("eff","gaus(0)+gaus(3)",200,900);
  fQE->SetParameters(0.2*1.15*0.8,260,65,0.20,480,100);

  fRnd = new TRandom();
  
  fLambdaHist = new TH1D("hLambda", "", 1000, 0, 1000.0);
  fDetectLambdaHist = new TH1D("hDetectLambda", "", 1000, 0, 1000.0);

  fTotalLambdaHist = new TH1D("hTotalLambdaHist", "Total Photon Lambda", 500, 0.0, 10000);
  fDetectTotalLambdaHist = new TH1D("hDetectTotalLambdaHist", "Detected Total Photon Lambda", 500, 0.0, 10000);

  fTotalEnergyHist = new TH1D("hTotalEnergyHist", "Total Photon Energy", 500, 0.0, 500);
  fDetectTotalEnergyHist = new TH1D("hDetectTotalEnergyHist", "Detected Total Photon Energy", 500, 0.0, 500);
    
  fOutputFile = new TFile("photocathode_output.root", "RECREATE");
}

MyPhotocathodeSD::~MyPhotocathodeSD() {
  if (fOutputFile && fTotalEnergyHist) {
    fOutputFile->cd();

    fTotalEnergyHist->Write();
    fDetectTotalEnergyHist->Write();

    fTotalLambdaHist->Write();
    fDetectTotalLambdaHist->Write();

    fLambdaHist->Write();
    fDetectLambdaHist->Write();

    fOutputFile->Close();
    
    delete fTotalEnergyHist;
    delete fDetectTotalEnergyHist;

    delete fTotalLambdaHist;
    delete fDetectTotalLambdaHist;

    delete fLambdaHist;
    delete fDetectLambdaHist;

    delete fOutputFile;
  }
}

void MyPhotocathodeSD::Initialize(G4HCofThisEvent* hce)
{
  fHitsCollection = new MyPhotocathodeHitsCollection(SensitiveDetectorName, collectionName[0]);
  if (fHCID < 0)
    fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);

  hce->AddHitsCollection(fHCID, fHitsCollection);

  fTotalEnergy = 0.0;
  fDetectTotalEnergy = 0.0;

  fTotalLambda = 0.0;
  fDetectTotalLambda = 0.0;
}

G4bool MyPhotocathodeSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    auto track = step->GetTrack();
    if (track->GetDefinition() != G4OpticalPhoton::Definition())
        return false;

    auto postPoint = step->GetPostStepPoint();
    auto boundary = postPoint->GetStepStatus();

    if (boundary != fGeomBoundary)
        return false;

    G4double time = postPoint->GetGlobalTime();
    G4ThreeVector position = postPoint->GetPosition();
    G4double energy = track->GetTotalEnergy();
    
    float lambda = 1239.84/(energy/eV);

    float prob = fQE->Eval(lambda);    
    float rnd = fRnd->Uniform(0.,1.);

    fLambdaHist->Fill(lambda);
    fTotalEnergy += energy / eV;
    fTotalLambda += lambda;
    
    if (lambda<300. || lambda>900) return false;
    if (rnd>prob) return false;
    
    fDetectLambdaHist->Fill(lambda);
    fDetectTotalEnergy += energy / eV;
    fDetectTotalLambda += lambda;
    
    auto* hit = new MyPhotocathodeHit(time, position, energy);
    fHitsCollection->insert(hit);    
    track->SetTrackStatus(fStopAndKill);
    
    return true;
}

void MyPhotocathodeSD::EndOfEvent(G4HCofThisEvent* /*hce*/) {
  if (fHitsCollection->entries()>0) {
    fTotalEnergyHist->Fill(fTotalEnergy);
    fDetectTotalEnergyHist->Fill(fDetectTotalEnergy);

    fTotalLambdaHist->Fill(fTotalLambda);
    fDetectTotalLambdaHist->Fill(fDetectTotalLambda);
  }
}

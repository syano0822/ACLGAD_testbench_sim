#ifndef MyPhotocathodeSD_h
#define MyPhotocathodeSD_h 1

#include "G4VSensitiveDetector.hh"
#include "G4THitsCollection.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4VProcess.hh"

#include "MyPhotocathodeHit.hh"

#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TRandom.h"

class MyPhotocathodeSD : public G4VSensitiveDetector
{
public:
  MyPhotocathodeSD(const G4String& name);
  virtual ~MyPhotocathodeSD();

  virtual void Initialize(G4HCofThisEvent* hce) override;
  virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
  virtual void EndOfEvent(G4HCofThisEvent* hce) override;

private:
  MyPhotocathodeHitsCollection* fHitsCollection;
  G4int fHCID;

  TF1* fQE;
  TRandom* fRnd;
  
  TH1D* fLambdaHist = nullptr;
  TH1D* fDetectLambdaHist = nullptr;

  TH1D* fTotalLambdaHist = nullptr;
  TH1D* fDetectTotalLambdaHist = nullptr;    
  
  TH1D* fTotalEnergyHist = nullptr;
  TH1D* fDetectTotalEnergyHist = nullptr;
    
  TFile* fOutputFile = nullptr;
  
  float fDetectTotalEnergy;
  float fTotalEnergy;

  float fDetectTotalLambda;
  float fTotalLambda;

};

#endif

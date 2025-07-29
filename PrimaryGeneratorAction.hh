// PrimaryGeneratorAction.hh
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "TF1.h"    // ROOT のヘッダ
#include <TRandom3.h>

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  PrimaryGeneratorAction();
  ~PrimaryGeneratorAction() override;
  void GeneratePrimaries(G4Event* event) override;

private:
  G4ParticleGun*  fParticleGun;
  TF1*            fEfunc;       
  TF1*            fVxfunc;
  TF1*            fVyfunc;
  TF1*            fVzfunc;
  TF1*            fPxfunc;
  TF1*            fPyfunc;
  TF1*            fPzfunc;
  TRandom3        fRng;         
};

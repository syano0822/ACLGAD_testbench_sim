// PrimaryGeneratorAction.cc
#include "PrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(nullptr),
   fEfunc(nullptr),
   fVxfunc(nullptr),
   fVyfunc(nullptr),
   fPxfunc(nullptr),
   fPyfunc(nullptr)
{
  fParticleGun = new G4ParticleGun(1);
  auto particle = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  fParticleGun->SetParticleDefinition(particle);

  fEfunc = new TF1("fE"," (x<=0.546) ? ( sqrt(x*x)*x*pow(0.546-x,2)/0.0016174913 + sqrt(x*x)*x*pow(2.28-x,2)/2.0537756 ) : ( sqrt(x*x)*x*pow(2.28-x,2) )/2.0537756",0,2.280000);
  //fEfunc = new TF1("fE"," (x<=0.546) ? ( sqrt(x*x)*x*pow(0.546-x,2)/0.0016174913 + sqrt(x*x)*x*pow(2.28-x,2)/2.0537756 ) : ( sqrt(x*x)*x*pow(2.28-x,2) )/2.0537756",0.,1.80000);
  
  fVxfunc = new TF1("fVx","1",-1.5,1.5);
  fVyfunc = new TF1("fVy","1",-1.5,1.5);
  fVzfunc = new TF1("fVz","1",0,0.0000001);
  
  fPxfunc = new TF1("fPx","1",-.0001,.0001);
  fPyfunc = new TF1("fPy","1",-.0001,.0001);
  fPzfunc = new TF1("fPz","1",-10,0);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fEfunc;
  delete fVxfunc;
  delete fVyfunc;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  // ROOT 乱数でエネルギーサンプリング
  double KE = fEfunc->GetRandom();  // MeV 単位
  fParticleGun->SetParticleEnergy(KE);
  
  // 方向を一様な単位球上からサンプリング（例として z 方向固定）
  
  double px = fPxfunc->GetRandom();
  double py = fPyfunc->GetRandom();
  double pz = fPzfunc->GetRandom();
  fParticleGun->SetParticleMomentumDirection({px,py,pz});
  //fParticleGun->SetParticleMomentumDirection({0,0,-10});

  double vx = fVxfunc->GetRandom();
  double vy = fVyfunc->GetRandom();
  double vz = fVzfunc->GetRandom();
  fParticleGun->SetParticlePosition({vx,vy,vz});
  //fParticleGun->SetParticlePosition({0,0,0});
  
  // 発射位置をランダムに設定したいならここで fRng を使う
  // e.g. double x = fRng.Uniform(-1,1)*mm; …  
  fParticleGun->GeneratePrimaryVertex(event);
}

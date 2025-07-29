#ifndef MyPhotocathodeHit_h
#define MyPhotocathodeHit_h 1

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4Allocator.hh"
#include "G4THitsCollection.hh"

class MyPhotocathodeHit : public G4VHit
{
public:
  MyPhotocathodeHit();
  MyPhotocathodeHit(G4double time, G4ThreeVector position, G4double energy);
  virtual ~MyPhotocathodeHit();

  inline G4double GetTime() const { return fTime; }
  inline G4ThreeVector GetPosition() const { return fPosition; }
  inline G4double GetEnergy() const { return fEnergy; }

  virtual void Draw() override {}
  virtual void Print() override;

  // これだけで十分（重複しないように）
  void* operator new(size_t);
  void  operator delete(void*);

private:
  G4double fTime;
  G4ThreeVector fPosition;
  G4double fEnergy;
};

using MyPhotocathodeHitsCollection = G4THitsCollection<MyPhotocathodeHit>;
extern G4Allocator<MyPhotocathodeHit> MyPhotocathodeHitAllocator;

#endif

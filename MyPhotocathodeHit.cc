#include "G4SystemOfUnits.hh"
#include "MyPhotocathodeHit.hh"

G4Allocator<MyPhotocathodeHit> MyPhotocathodeHitAllocator;

MyPhotocathodeHit::MyPhotocathodeHit() : fTime(0), fEnergy(0), fPosition() {}
MyPhotocathodeHit::MyPhotocathodeHit(G4double time, G4ThreeVector position, G4double energy)
  : fTime(time), fPosition(position), fEnergy(energy)
{}

MyPhotocathodeHit::~MyPhotocathodeHit() {}

void MyPhotocathodeHit::Print() {
    G4cout << "Photocathode Hit: time=" << fTime / ns << " ns, energy=" << fEnergy / eV
           << " eV, position=" << fPosition << G4endl;
}

void* MyPhotocathodeHit::operator new(size_t)
{
  return (void*)MyPhotocathodeHitAllocator.MallocSingle();
}

void MyPhotocathodeHit::operator delete(void* hit)
{
  MyPhotocathodeHitAllocator.FreeSingle((MyPhotocathodeHit*)hit);
}


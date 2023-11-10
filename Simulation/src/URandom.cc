#include "ad_type.h"


#include "URandom.hh"

URandom::URandom(int seed) {
  fEngine.seed(seed);
  fDist = new std::uniform_real_distribution<G4double>(0.0, 1.0);
}

URandom::~URandom() {
  delete fDist;
}

G4double URandom::flat() {
  return fDist->operator()(fEngine);
}

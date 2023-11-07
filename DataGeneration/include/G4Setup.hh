
#ifndef G4Setup_HH
#define G4Setup_HH

#include <vector>
#include <string>

class G4Material;

// This builds a fake Geant4 geometry having the given list of NIST materials
// in the geometry with the given production threshold. The corresponding
// material-cuts couples will be built that are needed for the Geant4 and
// initialisation that in our case will include the G4HepEm data initialisation
// as well.

// A vector fo G4 NIST material names and the production cut value (in length [mm]).
void FakeG4Setup(const std::vector<std::string>& g4NISTMatNames, double prodcut, int verbose=0);

#endif // G4Setup_HH

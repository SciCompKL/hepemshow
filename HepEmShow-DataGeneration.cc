
// Geant4
#include "G4Setup.hh"
#include "Randomize.hh"

// G4HepEm
#include "G4HepEmDataJsonIO.hh"
#include "G4HepEmState.hh"
#include "G4HepEmData.hh"
#include "G4HepEmParameters.hh"

#include "G4HepEmRunManager.hh"
#include "G4HepEmRandomEngine.hh"

// geant4 types and units
#include "globals.hh"
#include "G4SystemOfUnits.hh"


#include <vector>
#include <string>

int main () {

  // secondary production threshold in length
  const G4double secProdThreshold = 0.7 * mm;

  // list of Geant4 (NIST) material names
  std::vector<std::string> matList {"G4_Galactic", "G4_PbWO4", "G4_lAr"};

  // output, i.e. the G4HepEm data, file name
  const G4String fileName    = "../data/hepem_data";
  const G4String g4hepemFile = fileName + ".json";

  // create a fake Geant4 geometry and init to have the material-cuts couples


  FakeG4Setup (matList, secProdThreshold, 1);

  // construct the G4HepEmRunManager, which will fill the data structures
  // on calls to Initialize
  auto* runMgr    = new G4HepEmRunManager(true);
  auto* rngEngine = new G4HepEmRandomEngine(G4Random::getTheEngine());
  runMgr->Initialize(rngEngine, 0);
  runMgr->Initialize(rngEngine, 1);
  runMgr->Initialize(rngEngine, 2);

  G4HepEmState state;
  state.fData       = runMgr->GetHepEmData();
  state.fParameters = runMgr->GetHepEmParameters();
  // Serialize to file
  {
    std::ofstream jsonOS{ g4hepemFile.c_str() };
    std::cout << "Serializing to " << g4hepemFile << "... " << std::flush;
    if(!G4HepEmStateToJson(jsonOS, &state))
    {
      std::cerr << "Failed to write G4HepEMState to " << g4hepemFile
                << std::endl;
      jsonOS.close();
      return 1;
    }
  }
  std::cout << "done" << std::endl;

  FreeG4HepEmData(state.fData);

  return 0;
}

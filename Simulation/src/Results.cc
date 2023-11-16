#include "ad_type.h"


#include "Results.hh"

#include <cmath>

#include <iostream>
#include <iomanip>
#include <fstream>


void WriteResults(struct Results& res, int numEvents) {
  // for the histograms, bring them to be mean per event and write
  const G4double norm = numEvents > 0 ? 1.0/numEvents : 1.0;
  res.fEdepPerLayer.Scale(norm);
  res.fGammaTrackLenghtPerLayer.Scale(norm);
  res.fElPosTrackLenghtPerLayer.Scale(norm);

  res.fEdepPerLayer.WriteToFile(false);

  std::ofstream edeps("edeps");
  for(int i=0; i<50; i++){
     edeps << std::setprecision(14) << res.fEdepPerLayer_Acc[i].getMean() << " " << res.fEdepPerLayer_Acc[i].getVar();
     #if CODI_FORWARD
        edeps << " " << res.fEdepPerLayer_AccD[i].getMean() << " " << res.fEdepPerLayer_AccD[i].getVar();
     #endif
     edeps << "\n";
  }
  edeps.close();

  #ifdef CODI_REVERSE
     std::ofstream barInputs("barInputs");
     barInputs << res.barThicknessAbsorber.getMean() << " " << res.barThicknessAbsorber.getVar() << "\n";
     barInputs << res.barThicknessGap.getMean() << " " << res.barThicknessGap.getVar() << "\n";
     barInputs << res.barParticleEnergy.getMean() << " " << res.barParticleEnergy.getVar() << "\n";
     barInputs.close();
  #endif


  res.fGammaTrackLenghtPerLayer.WriteToFile(false);
  res.fElPosTrackLenghtPerLayer.WriteToFile(false);

  //
  res.fEdepAbs  = res.fEdepAbs*norm;
  res.fEdepAbs2 = res.fEdepAbs2*norm;
  const G4double rmsEAbs = std::sqrt(std::abs(res.fEdepAbs2 - res.fEdepAbs*res.fEdepAbs));

  res.fEdepGap  = res.fEdepGap*norm;
  res.fEdepGap2 = res.fEdepGap2*norm;
  const G4double rmsEGap = std::sqrt(std::abs(res.fEdepGap2 - res.fEdepGap*res.fEdepGap));


  // the secondary type and step number statistics
  std::cout << " --- Results::WriteResults ---------------------------------- " << std::endl;

  std::cout << std::endl;
  std::cout << std::setprecision(6);
  std::cout << "Absorber: mean Edep = " << res.fEdepAbs << " [MeV] and  Std-dev = " << rmsEAbs << " [MeV]"<< std::endl;
  std::cout << "Gap     : mean Edep = " << res.fEdepGap << " [MeV] and  Std-dev = " << rmsEGap << " [MeV]"<< std::endl;

  std::cout << std::endl;
  std::cout << std::setprecision(14);
  std::cout << " Mean number of gamma       " << res.fNumSecGamma*norm    << std::endl;
  std::cout << " Mean number of e-          " << res.fNumSecElectron*norm << std::endl;
  std::cout << " Mean number of e+          " << res.fNumSecPositron*norm << std::endl;

  std::cout << std::endl;
  std::cout << std::setprecision(6)
            << " Mean number of e-/e+ steps " << res.fNumStepsElPos*norm  << std::endl;
  std::cout << " Mean number of gamma steps " << res.fNumStepsGamma*norm  << std::endl;
  std::cout << " ------------------------------------------------------------\n";

}

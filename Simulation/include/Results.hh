#include "ad_type.h"


#ifndef RESULTS_HH
#define RESULTS_HH

/**
 * @file    Results.hh
 * @author  M. Novak
 * @date    July 2023
 *
 * @brief A collection of data that are recorded during the simulation.
 *
 * The following data is recorded during the simulation (mean is per event):
 *  - mean values in the individual layers of the calorimeter for energy deposit,
 *    neutral (gamma) and charged (electron/positron) particle simulation steps
 *  - mean number of energy deposited in the `absorber` and `gap`
 *  - mean number of secondary gamma, electron and positrons produced
 *  - mean number of neutral (gamma) and charged (electron/positron)
 *
 * Quantities, recorded in the individual layers are stored in histograms and
 * written to files at the end of the simulation while the others are reported
 * in the screen. An example looks like
 * ```
 *       --- Results::WriteResults ----------------------------------
 *
 *       Absorber: mean Edep = 6722.95 [MeV] and  Std-dev = 309.636 [MeV]
 *       Gap     : mean Edep = 2571.75 [MeV] and  Std-dev = 118.507 [MeV]
 *
 *       Mean number of gamma       4457.043
 *       Mean number of e-          7957.899
 *       Mean number of e+          428.922
 *
 *       Mean number of e-/e+ steps 36097
 *       Mean number of gamma steps 40436.2
 *       ------------------------------------------------------------
 * ```
 */

#include "Hist.hh"
#include <vector>
#include "accumulator.hh"

/**
 * Data that needs to be accumulated during one `event` (the scope is one event):
 * - at the beginning of an `event`: usually reset (to zero)
 * - at the end of an `event`: usually written to the run scope data (see the
 *   `Results` below)
 */
struct ResultsPerEvent {
  G4double fEdepAbs       { 0.0 }; ///< energy deposit in the absorber during one event
  G4double fEdepGap       { 0.0 }; ///< energy deposit in the gap during one event
  //
  G4double fNumSecGamma   { 0.0 }; ///< number of seconday \f$\gamma\f$ particles generated during one event
  G4double fNumSecElectron{ 0.0 }; ///< number of seconday \f$e^-\f$ particles generated during one event
  G4double fNumSecPositron{ 0.0 }; ///< number of seconday \f$e^+\f$ particles generated during one event
  //
  G4double fNumStepsGamma { 0.0 }; ///< number of \f$\gamma\f$ simulation steps during one event
  G4double fNumStepsElPos { 0.0 }; ///< number of \f$e^-/e^+\f$ simulation steps during one event
};


/**
 * Data that are collected during the entire `run` of the simulation:
 * - at the beginning of the `ru`n: need to be initialised
 * - at the end of an `run`: written out (to file or to the std output)
 * Mean quantities are computed over the simulated events.
 */
struct Results {
  Hist fEdepPerLayer;              ///< mean energy deposit per-layer histogram
  Hist fEdepPerLayer_CurrentEvent;       ///< mean energy deposit per-layer histogram, current event
  std::vector<Accumulator<double>> fEdepPerLayer_Acc; ///< computes statistical properties of the energy deposit per layer per event
  #ifdef CODI_FORWARD
    std::vector<Accumulator<double>> fEdepPerLayer_AccD; ///< computes statistical properties of the dot value of the energy deposit per layer per event
  #endif
  #ifdef CODI_REVERSE
    std::vector<double> barEdep; ///< Bar values of the edeps, to be set in the beginning.
    Accumulator<double> barThicknessAbsorber, barThicknessGap, barParticleEnergy; ///< Accumulate the bar values of the thicknesses and energy.
    G4double pThicknessAbsorber, pThicknessGap, pParticleEnergy; ///< Copies of the thickness and energy variables used by the simulation, used as AD inputs.
  #endif
  Hist fGammaTrackLenghtPerLayer;  ///< mean number of \f$\gamma\f$ steps per-layer histogram
  Hist fElPosTrackLenghtPerLayer;  ///< mean number of \f$e^-/e^+\f$ steps per-layer histogram
  //
  G4double fEdepAbs        { 0.0 };  ///< mean energy deposit in the `absorber`
  G4double fEdepAbs2       { 0.0 };  ///< mean of the squared energy deposit in the `absorber`
  G4double fEdepGap        { 0.0 };  ///< mean energy deposit in the `gap`
  G4double fEdepGap2       { 0.0 };  ///< mean of the squared energy deposit in the `gap`
  //
  G4double fNumSecGamma    { 0.0 };  ///< mean number of the produced secondary \f$\gamma\f$ particles
  G4double fNumSecGamma2   { 0.0 };  ///< mean of the squared number of produced secondary \f$\gamma\f$ particles
  G4double fNumSecElectron { 0.0 };  ///< mean number of the produced secondary \f$e^-\f$ particles
  G4double fNumSecElectron2{ 0.0 };  ///< mean of the squared number of produced secondary \f$e^-\f$ particles
  G4double fNumSecPositron { 0.0 };  ///< mean number of the produced secondary \f$e^+\f$ particles
  G4double fNumSecPositron2{ 0.0 };  ///< mean of the squared number of produced secondary \f$e^+\f$ particles
  //
  G4double fNumStepsGamma  { 0.0 };  ///< mean number of \f$\gamma\f$ steps in the entire calorimeter
  G4double fNumStepsGamma2 { 0.0 };  ///< mean of the squared number of \f$\gamma\f$ steps in the entire calorimeter
  G4double fNumStepsElPos  { 0.0 };  ///< mean number of \f$e^-/e^+\f$ steps in the entire calorimeter
  G4double fNumStepsElPos2 { 0.0 };  ///< mean of the squared number of \f$e^-/e^+\f$ steps in the entire calorimeter
  ResultsPerEvent fPerEventRes;    ///< data structure to accumulate results during a single event
};

/** Writes the final results of the simulation.
 *
 * Writes the 3 histrograms (mean energy deposit, \f$\gamma\f$ and \f$e^-/e^+\f$ steps per-layer) into files
 * while all the other collected data to the screen.*/
void WriteResults(struct Results& res, int numEvents=1);

#endif // RESULTS_HH

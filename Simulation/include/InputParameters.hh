#include "ad_type.h"


#ifndef INPUTPARAMETERS_HH
#define INPUTPARAMETERS_HH

/**
 * @file    InputParameters.hh
 * @struct  InputParameters
 * @author  M. Novak
 * @date    Aug 2023
 *
 * @brief A data structure that encapsulates all the possible input arguments of the `HepEmShow` application.
 */

#include <iostream>
#include <string>
#include <vector>

// NOTE: this is Unix specific!
#include <getopt.h>


struct InputParameters {

  /** CTR with default values: default geometry, primary and event configuirations (see below) with
    * pre-generated data files expected at `../data/hepem_data` relative to the `HepEmShow` executable.*/
  InputParameters() : fG4HepEmDataFile("../data/hepem_data"), fRunVerbosity(1) {}


  /** The geometry related input arguments.*/
  struct Geometry {
    /** CTR with default values: 50 layers of 2.3 mm absorber and 5.7 mm gap with 400 mm transvers size.*/
    Geometry()
    : fNumLayers(50),
      fThicknessAbsorber(2.3),
      fThicknessGap(5.7),
      fThicknessCalo(0),
      fSizeTransverse(400.0) {}

    int    fNumLayers;         ///< number of layers in the calorimeter
    G4double fThicknessAbsorber; ///< absorber thickness along X in [mm]
    G4double fThicknessGap;      ///< gap thickness along X in [mm]
    G4double fThicknessCalo;     ///< calorimeter thickness along X [mm] ONLY if number of layers is zero
    G4double fSizeTransverse;    ///< calorimeter full size along YZ in [mm]
  };


  /** The primary partcile and events related input arguments. */
  struct PrimaryAndEvents {
    /**CTR with default values: simulate 1000 events, starting with an electron of 10 GeV each (do not report progress).*/
    PrimaryAndEvents( )
    : fParticleName("e-"),
      fParticleEnergy(10000.0),
      fNumEvents(1000),
      fRandomSeed(1234) {}

    std::string  fParticleName;   ///< primary particle name: {"e-", "e+" or "gamma"}
    G4double       fParticleEnergy; ///< primary particle energy in [MeV]
    int          fNumEvents;      ///< number of events to simulate (each will start with a single primary)
    G4double       fRandomSeed;     ///< seed for the random number generator
  };

  // all members
  Geometry         fGeometry;         ///< the geometry related configuration
  PrimaryAndEvents fPrimaryAndEvents; ///< the primary partcile and events related configuration
  std::string      fG4HepEmDataFile;  ///< the pre-generated data file (with path)
  int              fRunVerbosity;     ///< level of printout verbosity duing setting up: nothing when < 1.
  #ifdef CODI_REVERSE
    std::vector<double> barEdep;     ///< Bar values of the energy depositions
  #endif
};


void PrintParameters (const struct InputParameters& theParam) {

  std::cout << " \n === HepEmShow input parameters: "    << std::endl;
  std::cout << "     --- Geometry configuration: " << std::endl;
  std::cout << "         - number-of-layers      : "     << theParam.fGeometry.fNumLayers         << std::endl;
  std::cout << "         - absorber-thickness    : "     << theParam.fGeometry.fThicknessAbsorber << " [mm]" << std::endl;
  std::cout << "         - gap-thickness         : "     << theParam.fGeometry.fThicknessGap      << " [mm]" << std::endl;
  std::cout << "         - transverse-size       : "     << theParam.fGeometry.fSizeTransverse    << " [mm]" << std::endl;

  std::cout << "     --- Primary and Event configuration: " << std::endl;
  std::cout << "         - primary-particle      : "     << theParam.fPrimaryAndEvents.fParticleName   << std::endl;
  std::cout << "         - primary-energy        : "     << theParam.fPrimaryAndEvents.fParticleEnergy << " [MeV]" << std::endl;
  std::cout << "         - number-of-events      : "     << theParam.fPrimaryAndEvents.fNumEvents      <<  std::endl;
  std::cout << "         - random-seed           : "     << theParam.fPrimaryAndEvents.fRandomSeed     <<  std::endl;

  std::cout << "     --- Additional configuration: " << std::endl;
  std::cout << "         - g4hepem-data-file    : "     << theParam.fG4HepEmDataFile  << std::endl;
  std::cout << "         - run-verbosity        : "     << theParam.fRunVerbosity     << std::endl;

}


//
// options for providign input arguments to the `HepEmShow` application
static struct option options[] = {
  {"number-of-layers      (number of layers in the calorimeter)           - default: 50"     , required_argument, 0, 'l'},
  {"absorber-thickness    (in [mm] units)                                 - default: 2.3"    , required_argument, 0, 'a'},
  {"gap-thickness         (in [mm] units)                                 - default: 5.7"    , required_argument, 0, 'g'},
  {"transverse-size       (of the calorimeter in [mm] units)              - default: 400"    , required_argument, 0, 't'},

  {"primary-particle      (possible particle names: e-, e+ and gamma)     - default: e-"     , required_argument, 0, 'p'},
  {"primary-energy        (in [MeV] units)                                - default: 10 000" , required_argument, 0, 'e'},
  {"number-of-events      (number of primary events to simulate)          - default: 1000"   , required_argument, 0, 'n'},
  {"random-seed                                                           - default: 1234"   , required_argument, 0, 's'},

  {"g4hepem-data-file     (the pre-generated data file with its path)     - default: ../data/hepem_data" , required_argument, 0, 'd'},
  #ifdef CODI_REVERSE
    {"edep-bars             (bar values of edeps, in [MeV] units)           - default:: 0:0:...:0", required_argument, 0, 'b'},
  #endif
  {"run-verbosity         (verbosity of run information: nothing when 0)  - default: 1"      , required_argument, 0, 'v'},
  {"help"                                                                                    , no_argument      , 0, 'h'},
  {0, 0, 0, 0}
};


// auxiliary functions for obtaining input arguments
void Help() {
  std::cout<<"\n === Usage: HepEmShow [OPTIONS] \n"<<std::endl;
  for (int i = 0; options[i].name != NULL; i++) {
    printf("\t-%c  --%s\n", options[i].val, options[i].name);
  }
}

// Parses string 'number1:number2:...:numberN' into vector {number1,...,numberN}.
static inline std::vector<double> stod_array(const char* arg){
  std::vector<double> ret;
  std::string arg_s(arg);
  arg_s = arg_s + ":";
  size_t pos = 0;
  do {
     int sep = arg_s.find(":",pos);
     std::string s = arg_s.substr(pos,sep-pos);
     ret.push_back(std::stod(s.c_str()));
     pos = sep+1;
  } while(pos<arg_s.size());
  return ret;
}

// In forward-mode AD, allow real-number arguments to consist of two numbers separated by ':'.
// If existent, the second number specifies the dot value of the input argument.
static inline G4double parseRealInput(const char* arg){
  std::vector<double> arg_d = stod_array(arg);
  if(arg_d.size()==1){
     return arg_d[0];
  } else {
     if(arg_d.size()>2){
        std::cerr << "Specify 'number' or 'number:number', not more than two elements." << std::endl;
     }
     G4double ret = arg_d[0];
     #ifdef CODI_FORWARD
        SET_DOTVALUE(ret, arg_d[1]);
     #else
        std::cerr << "Ignoring specification of dot value in argument, as this is not a forward-mode AD build." << std::endl;
     #endif
     return ret;
  }
}


void GetOpt(int argc, char *argv[], InputParameters& param) {
  while (true) {
    int c, optidx = 0;
    c = getopt_long(argc, argv, "hl:a:g:t:p:e:n:s:d:v:b:", options, &optidx);
    if (c == -1)
      break;
    switch (c) {
    case 0:
       c = options[optidx].val;
       /* fall through */

    case 'l':
       param.fGeometry.fNumLayers = std::stoi(optarg);
       break;
    case 'a':
       param.fGeometry.fThicknessAbsorber = parseRealInput(optarg);
       break;
    case 'g':
       param.fGeometry.fThicknessGap = parseRealInput(optarg);
       break;
    case 't':
       param.fGeometry.fSizeTransverse = std::stod(optarg);
       break;

    case 'p':
       param.fPrimaryAndEvents.fParticleName = optarg;
       if ( !(param.fPrimaryAndEvents.fParticleName=="e-" || param.fPrimaryAndEvents.fParticleName=="e+" || param.fPrimaryAndEvents.fParticleName=="gamma") ) {
         std::cout << "\n *** Unknown primary particle name -p: " << optarg << std::endl;
         Help();
         exit(-1);
       }
       break;
    case 'e':
       param.fPrimaryAndEvents.fParticleEnergy = parseRealInput(optarg);
       break;
    case 'n':
       param.fPrimaryAndEvents.fNumEvents = std::stoi(optarg);
       break;
    case 's':
       param.fPrimaryAndEvents.fRandomSeed = std::stod(optarg);
       break;

    case 'd':
       param.fG4HepEmDataFile = optarg;
       break;
    case 'v':
       param.fRunVerbosity = std::stoi(optarg);
       break;

    case 'b':
       #ifdef CODI_REVERSE
          param.barEdep = stod_array(optarg);
       #else
          std::cerr << "Ignoring -b argument, as this is a not a reverse-AD build." << std::endl;
       #endif
       break;

    case 'h':
       Help();
       exit(-1);
       break;

    default:
      printf("\n *** Unknown input argument: %c\n",c);
      Help();
      exit(-1);
    }
   }
   // number of layers must be >= 1
   if (param.fGeometry.fNumLayers < 1 ) {
     printf("\n *** Calorimeter number of layers must be >= 1! \n");
     Help();
     exit(-1);
   }
   // check if the data file was given with/without extension
   if (param.fG4HepEmDataFile.find(".json")==std::string::npos) {
     param.fG4HepEmDataFile += ".json";
   }
   // print parameters if the verbosity > 0
   if (param.fRunVerbosity > 0) {
     PrintParameters(param);
   }
}



#endif // INPUTPARAMETERS_HH

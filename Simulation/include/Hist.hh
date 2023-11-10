#include "ad_type.h"


#ifndef HIST_H
#define HIST_H


/**
 * @file    Hist.hh
 * @class   Hist
 * @author  M. Novak
 * @date    July 2023
 *
 * @brief A simple histogram only to collect some data during the simulation.
 */


#include <vector>
#include <string>

class Hist {

public:

  /** Constructor
    *
    * @param filename String to be used as file name when writing into file.
    * @param min      Minimum bin value.
    * @param max      Maximum bin value.
    * @param numbin   Number of bins required between `min` and `max`.
    */
  Hist(const std::string& filename, G4double min, G4double max, int numbin);

  /** Constructor
    *
    * @param filename String to be used as file name when writing into file.
    * @param min      Minimum bin value.
    * @param max      Maximum bin value.
    * @param delta    Required width of a bin.
    */
  Hist(const std::string& filename, G4double min, G4double max, G4double delta);

  /** Default constructor */
  Hist();

   /** Destructor */
  ~Hist() {/*nothing to do*/}

  /** Auxiliary method to setup the initial state of the histogram.*/
  void Initialize();

  /** Method to modify the properties of the histogram
    *
    * @param filename The new name of the filename.
    * @param min      The new minimum bin value.
    * @param max      The new maximum bin value.
    * @param numbins  The new number of bins required between `min` and `max`.
    */
  void ReSet(const std::string& filename, G4double min, G4double max, int numbins);

  /** Method to populate the histogram with data: the corresponding bin content is increased by 1.
    *
    * @param x Value to add.
    */
  void Fill(G4double x);

  /** Method to populate the histogram with data and a weight: the corresponding bin content is increased by the weight.
    *
    * @param x Value to add.
    * @param w The corresponding weight.
    */
  void Fill(G4double x, G4double w);

  /** Method to scale all bin content by a constant.
    *
    * @param sc Scaling factor.
    */
  void Scale(G4double sc);

  /** Method to provide the number of bins.
    * @return Number of bins.
    */
  int     GetNumBins() const { return fNumBins; }
  G4double  GetDelta()   const { return fDelta;   }
  G4double  GetMin()     const { return fMin;     }
  G4double  GetMax()     const { return fMax;     }
  G4double  GetSum()     const { return fSum;     }
  const std::vector<G4double>& GetX() const { return fx; }
  const std::vector<G4double>& GetY() const { return fy; }

  // write result to file without (default) or after normalising
  void WriteToFile(bool isNorm=false);
  void WriteToFile(G4double norm);

  // Add the argument histogram to this (would be even nicer with operator overloading
  // but we keep it simple)
  void Add(const Hist* hist);


// Data members
private:
  std::string         fFileName;
  std::vector<G4double> fx;
  std::vector<G4double> fy;
  G4double              fMin;
  G4double              fMax;
  G4double              fDelta;
  G4double              fInvDelta;
  G4double              fSum;
  int                 fNumBins;
};

#endif

#include "ad_type.h"

#ifndef EVENTLOOP_HH
#define EVENTLOOP_HH

/**
 * @file    EventLoop.hh
 * @class   EventLoop
 * @author  M. Novak
 * @date    July 2023
 *
 * @brief Event loop for simulating the required number of primary tracks/events.
 *
 * The `EventLoop::ProcessEvents()` method is responsible to generate track(s) for
 * the required number of events and simulate the histories of all primary and
 * their secondary tracks.
 */


class G4HepEmTLData;
class G4HepEmState;
class G4HepEmTrack;

class PrimaryGenerator;
class Geometry;
class Results;

class EventLoop {

public:

  /** Generates and simulates the required number of events.
   *
   * Events, i.e. primary track(s) are generated by using the input `PrimaryGenerator`. At the beginning of each event, the `PrimaryGenerator` is used to
   * generate the primary track(s) that belong to the actual event. Note, that we have only one primary track per-event at the moment. The generated primary
   * track(s) is inserted/pushed into the `TrackStack` as the very first track and the simulation of the event starts. During the simulation of the event:
   *  - one track is popped from the stack and the appropriate `SteppingLoop` is called to simulate its entire history ina  step-by-step way
   *  - at the end of each simulation step, secondary tracks that are created in that step in the related physics interaction (if any), are inserted/pushed into the `TrackStack`
   * Simulation of the event is completed when the `TrackStack` becomes empty. See the implementation for more details.
   *
   * In order to be able to collect some infomation during the event processing, the `BeginOfEventAction()`/`EndOfEventAction()` methods are invoked before/after each event processing
   * while the `BeginOfTrackingAction()`/`EndOfTrackingAction()` methods are invoked before/after tracking each new track.
   *
   * @param theTLData a `G4HepEm` specific (thread local) object primarily used to obtain all physics related information from `G4HepEm` needed to compute a simulation step
   * @param theState a `G4HepEm` specific object that stores pointers to the top level `G4HepEm` data structure and parameters that are used by `G4HepEm` to provide all physics related infomation needed to compute a simulation step
   * @param thePrimaryGenerator the primary generator that is used to generate primary track(s) at the beginning of each event (only one primary track per event in our case now)
   * @param theGeometry the geometry of the application in which the input track history is simulated
   * @param theResult the data structure that holds all the infomation needs to be collected during the simulation.
   * @param numEventToSimulate number of events required to be simulated
   * @param verbosity to control the verbosity of printouts reporting progress and state of the event processing
   */
  static void ProcessEvents(G4HepEmTLData& theTLData, G4HepEmState& theState, PrimaryGenerator& thePrimaryGenerator, Geometry& theGeometry, Results& theResult, int numEventToSimulate, int verbosity);

private:
  EventLoop() = delete;

  /** Method invoked at the beginning of each event by passing the (single) primary track of the event.*/
  static void BeginOfEventAction(Results& theResult, int eventID, const G4HepEmTrack& thePrimaryTrack, Geometry& theGeometry);
  /** Method invoked at the end of each event.*/
  static void EndOfEventAction(  Results& theResult, int eventID);

  /** Method invoked before start tracking of a new track (provided as input argument).*/
  static void BeginOfTrackingAction(Results& theResult, G4HepEmTrack& theTrack);
  /** Method invoked after terminating tracking of a track (provided as input argument).*/
  static void EndOfTrackingAction(  Results& theResult, G4HepEmTrack& theTrack);


};

#endif // EVENTLOOP_HH

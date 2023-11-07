Code documentation of the ``Simulation`` part of the ``HepEmShow`` application.
----------------------------------------------------------------------------------


The main of the ``HepEmShow`` application
..............................................

.. doxygenfile:: HepEmShow.cc
   :project: HepEmShow a compact EM shower simulation



The ``Geometry`` description related code documentation
..........................................................

The :cpp:class:`Geometry` of this application is built up from 5 :cpp:class:`Box`
objects (by default, i.e. at non-zero ``gap`` thickness): an ``absorber`` and
a ``gap`` building up a ``layer`` that is repeated `N` times along the `x`-axis
building up and filling in the ``calorimeter`` that is centered at the origin
and placed in the ``world``.

.. doxygenclass:: Geometry
   :project: HepEmShow a compact EM shower simulation
   :members:
   :private-members:

.. doxygenclass:: Box
   :project: HepEmShow a compact EM shower simulation
   :members:
   :private-members:



The ``Physics`` code documentation
.............................................


.. doxygenclass:: Physics
   :project: HepEmShow a compact EM shower simulation


.. doxygenclass:: URandom
   :project: HepEmShow a compact EM shower simulation
   :members:
   :private-members:



The ``PrimaryGenerator`` code documentation
.............................................

.. doxygenclass:: PrimaryGenerator
   :project: HepEmShow a compact EM shower simulation
   :members:
   :private-members:




Auxiliary code documentation
.............................................


Collecting data during the simulation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


.. doxygenfile:: Results.hh
   :project: HepEmShow a compact EM shower simulation


.. doxygenclass:: Hist
   :project: HepEmShow a compact EM shower simulation
   :members:
   :private-members:


Providing input arguments to the ``HepEmShow`` application
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To see all configuration option, run the application as::

    ./HepEmShow --help

    === Usage: HepEmShow [OPTIONS]

   	-l  --number-of-layers      (number of layers in the calorimeter)           - default: 50
   	-a  --absorber-thickness    (in [mm] units)                                 - default: 2.3
   	-g  --gap-thickness         (in [mm] units)                                 - default: 5.7
   	-t  --transverse-size       (of the calorimeter in [mm] units)              - default: 400
   	-p  --primary-particle      (possible particle names: e-, e+ and gamma)     - default: e-
   	-e  --primary-energy        (in [MeV] units)                                - default: 10 000
   	-n  --number-of-events      (number of primary events to simulate)          - default: 1000
   	-s  --random-seed                                                           - default: 1234
   	-d  --g4hepem-data-file     (the pre-generated data file with its path)     - default: ../data/hepem_data
   	-v  --run-verbosity         (verbosity of run infomation: nothing when 0)   - default: 1
   	-h  --help


.. doxygenstruct:: InputParameters
   :project: HepEmShow a compact EM shower simulation
   :members:


Event loop, stepping loops and the track stack
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenclass:: EventLoop
   :project: HepEmShow a compact EM shower simulation
   :members:
   :private-members:


.. doxygenclass:: SteppingLoop
   :project: HepEmShow a compact EM shower simulation
   :members:
   :private-members:


.. doxygenclass:: TrackStack
   :project: HepEmShow a compact EM shower simulation
   :members:
   :private-members:

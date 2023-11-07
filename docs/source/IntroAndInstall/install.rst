.. _install_doc:

Build and Install
==================

Will come later but ``HepEmShow`` requires ``G4HepEm`` that provides its Physics (see more at the :ref:`The components of the simulation <simulation_components_doc>`).
``G4HepEm`` can be built with or without ``Geant4`` though a data file is needed
in the latter case. See more later ...


Build ``G4HepEm`` with or without ``Geant4`` dependence:
-----------------------------------------------------------


With ``Geant4`` (``G4HepEm_GEANT4_BUILD=ON`` default):
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
::

   cmake ../ -DGeant4_DIR=YOUR_GEANT4_INSTALL/lib(lib64)/cmake/Geant4/ -DCMAKE_INSTALL_PREFIX=YOUR_G4HEPEM_INSTALL



Without ``Geant4`` (``G4HepEm_GEANT4_BUILD=OFF``):
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
::

    cmake ../ -DG4HepEm_GEANT4_BUILD=OFF -DCMAKE_INSTALL_PREFIX=YOUR_G4HEPEM_INSTALL




Build ``HepEmShow`` with ``G4HepEm`` build with or without ``Geant4``:
------------------------------------------------------------------------

With a complete, ``Geant4`` dependent ``G4HepEm`` build:
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
::

    cmake ../ -DGeant4_DIR=YOUR_GEANT4_INSTALL/lib(lib64)/cmake/Geant4/ -DG4HepEm_DIR=YOUR_G4HEPEM_INSTALL/lib(lib64)/cmake/G4HepEm/ -DCMAKE_BUILD_TYPE=RELEASE


With a standalone, ``Geant4`` independent ``G4HepEm`` build:
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
::

     cmake ../ -DG4HepEm_DIR=YOUR_G4HEPEM_INSTALL/lib(lib64)/cmake/G4HepEm/ -DCMAKE_BUILD_TYPE=RELEASE



.. _install_Requirements:

Requirements
--------------



Build and install
--------------------

*This README is about the extension of HepEmShow with AD capabilities. See [README_ORIGINAL.md](README_ORIGINAL.md) for information about HepEmShow.*

# Differentiated HEP-style Electromagnetic Shower Simulation
Based on [G4HepEm](https://github.com/mnovak42/g4hepem/), [HepEmShow](https://github.com/mnovak42/hepemshow/) is a compact, self-contained simulation of electromagnetic showers in a simple sampling calorimeter. This repository contains a version of HepEmShow that has been extended with algorithmic differentiation (AD) capabilities using the [CoDiPack](https://github.com/SciCompKL/CoDiPack) AD tool. Along with [differentiated G4HepEm](https://github.com/SciCompKL/g4hepem/), this makes it possible to compute forward- and reverse-mode derivatives of 
- output variables of the simulation, such as energy depositions in the layers of the calorimeter,

with respect to 
- input variables of the simulation, such as the kinetic energy of the primary particles, and the geometric thicknesses of absorber and gap layers.

## Building from source
A version of HepEmShow without any AD capabilities can be built as usual: Build G4HepEm, download HepEmShow into some directory, enter that directory, checkout the `with_codipack` branch, and run
```bash
mkdir build
cd build
cmake ../ -DG4HepEm_DIR=path/to/g4hepem/install/lib/cmake/G4HepEm/ -DCMAKE_BUILD_TYPE=Release
make
```
To create a forward-mode or reverse-mode AD build, first build the respective version of G4HepEm. After this, the above `cmake` call for HepEmShow should automatically apply the same AD settings. You might have to specify the path to your [CoDiPack](https://github.com/SciCompKL/CoDiPack) directory via `-DCoDiPack_DIR=/path/to/CoDiPack/cmake`. Instead of `install/lib`, CMake may have used a variant like `install/lib64`.

If you want to make non-AD and AD builds at the same time, consider using directory names `build_no`/`build_ad` and `$PWD/../install_no`/`$PWD/../install_ad` instead of `build` and `$PWD/../install` in the above build commands.


## Computing derivatives

You can run differentiated versions of `HepEmShow` just like the original non-differentiated code. It will produce an additional file `edeps` with 50 rows. The *i*-th row contains the mean energy deposition (in MeV) and the mean squared energy deposition (in MeV²) of the *i*-th layer. 

In the **forward mode**, each line in the `edeps` file contains two additional numbers, namely, the mean derivative of the energy deposition and the mean squared derivative of the energy deposition in the respective layer. The AD inputs, with respect to which these derivatives are formed, are to be specified through the command-line interface as follows. In order to "seed" the primary energy (in MeV), absorber thickness (in mm), and gap thickness (in mm) with a non-zero dot-value, specify the respective dot-value behind the value passed to `-e`/`-a`/`-g`, separated by a colon. For example, 
```bash
./HepEmShow -n 1000 -e 10000:3.5 -a 2.3:1
```
means that you are interested in the derivative with respect to the primary energy (in MeV) times 3.5 plus the derivative with respect to the absorber thickness (in mm) times 1, averaged over 1000 events.

In the **reverse mode**, you can specify the bar-value of the energy deposition in all of the 50 layers via the `-b` command line argument. The values have to be separated by colons, and trailing zeros may be omitted. For example
```bash
./HepEmShow -n 1000 -e 10000 -b 1:0:4.5
```
means that you are interested in the derivative of the energy deposition in the first layer times 1 plus the derivative in the third layer times 4.5, averaged over 1000 events at 10000 MeV. The derivatives are computed in one stroke with respect to the absorber thickness (in mm), gap thickness (in mm) and primary energy (in MeV), and are written to a file `barInputs` in separate lines. The first entry in each of the three lines is the mean derivative, the second entry is the mean squared derivative.

## License Hints
The original version of [HepEmShow](https://github.com/mnovak42/hepemshow/) has been released under the [Apache License version 2.0](https://github.com/mnovak42/hepemshow/blob/master/LICENSE). Please note that CoDiPack has been released under the [GNU General Public License (GPL) version 3](https://github.com/SciCompKL/CoDiPack/blob/master/LICENSE), meaning that you must comply with the provisions of the GPL if you convey the combined work to others.

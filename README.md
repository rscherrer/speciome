# speciome

Simulation program for evolutionary biologists to study speciation with a complex genotype-phenotype map.

## Prerequisites

* A C++20 compiler (e.g. [GCC](https://gcc.gnu.org) or [Clang](https://clang.llvm.org))
* (optional) [CMake](docs/CMAKE.md) version 3.16 or higher
* (optional) R and [speciomer](https://github.com/rscherrer/speciomer) to read and analyze the data

## Build

Here are instructions to build with CMake, but you can compile the source code with the tools of your choice.

(Click [here](docs/BUILD.md) to build as developer.)

(Click [here](docs/PEREGRINE.md) to build on the [Peregrine](https://www.rug.nl/society-business/centre-for-information-technology/research/services/hpc/facilities/peregrine-hpc-cluster?lang=en) cluster.)

### Linux, MacOS

```shell
git clone git@github.com:rscherrer/speciome.git
cd speciome
cp CMakeLists_user.txt CMakeLists.txt # user configuration
mkdir build && cd build
cmake ..
cmake --build .
```

The executable `speciome` is built in `../bin/`.

### Windows

```cmd
git clone git@github.com:rscherrer/speciome.git
cd speciome
copy CMakeLists_user.txt CMakeLists.txt :: user configuration
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

The executable `speciome.exe` is built in `../bin/`.

### IDEs

Many IDEs support CMake out of the box. "Open folder" should do the trick...
You can use CMake to generate the input files for your favorite IDE too:

```shell
git clone git@github.com:rscherrer/speciome.git
cd speciome
cp CMakeLists_user.txt CMakeLists.txt # user configuration
mkdir build
cd build
# Generate VisualStudio project files
cmake -G "Visual Studio 17 2022" -A x64 ..
# Generate Xcode project files (Xcode must be installed)
cmake -G Xcode    
```

This will place the project files in `../build`.

## Use

Run a simulation with default parameters with:

```
./speciome 
```

Or provide a parameter file with non-default parameter values:

```
./speciome parameters.txt
```

### Parameter file

The parameter file must contain parameter names followed by their values, for example:

```
hsymmetry 1
ecosel 0.6
allfreq 0.2
nvertices 30 30 30
```

Parameters that are not provided in the parameter file will take default values. Beware that some parameters take multiple values. Click [here](docs/PARAMETERS.md) for a list of all parameters. To allow for replication, if `parsave` is set to 1, the parameters used in the simulation (including any automatically-generated `seed`) will be saved into a file named `paramlog.txt` within the working directory.

### Model description

This program runs an individual-based simulation where agents live, reproduce and die, through thousands of generations. Individuals have traits that are genetically encoded and can evolve. The model is built in such a way that under the right conditions, the population may split into two phenotypically distinct and reproductively isolated clusters, or species (i.e. speciaiton has happened). Importantly, the genotype codes for the phenotype in a nonlinear way allowing not only additive but also dominance, epistatic and environmental effects. See the accompanying manuscript for more information.

### Genetic architecture

The genetic architecture refers to the constant features of the genotype-phenotype map. Those are features that do not change through time and cannot evolve, including e.g. the number of chromosomes, numbers and positions of loci and topologies and interaction weights of the gene networks. If `archload` is set to 0, a new architecture is generated at the beginning of the simulation. Otherwise, the program will read an architecture from a file `architecture.txt` that must be present in the working directory. Click [here](docs/ARCHITECTURE.md) to see what a genetic architecture file should look like. If `archsave` is set to 1, the architecture that was used in the simulation (whether generated or provided) will be saved into `architecture.txt`.

### Saving data

Set `datsave` to 1 to allow data recording. The data are saved every `tsave` generations into binary `*.dat` files. Click [here](docs/VARIABLES.md) for a list of the variables that can be saved.

Each variable is saved as a vector of values (64bit double precision floating point numbers). By default the program will save all variables. Set `choosewhattosave` to 1 to decide which variables to save instead. The program will then expect a file `whattosave.txt` in the working directory. This file should be a list of names of variable to save. For example:

```
time
EI
SI
RI
locus_Fst
```

will save time, speciation metrics EI, SI and RI at each time point, and summary statistic Fst for each locus at each time point.

Some variables need other variables to be saved in order to be interpreted down the line. For example, `time` must be saved in order for the recorded time points to be appended to the resulting data tables. Or, the `population_sizes` in each recorded time point must be known for each individual to be assigned a time point in `individual_*` variables and in individual whole genomes.

### Reading data

The data are saved in binary to speed up the writing (and the reading) process. Plus, different users will need to combine the data in many different ways depending on the question they are asking. To read and assemble the data into analyzable datasets, use our R package [speciomer](https://github.com/rscherrer/speciomer). Note that some functions in this package will expect certain files (e.g. `paramlog.txt`, `architecture.txt` or `time.dat`) to be present. In general we advise the following:

* save the generative parameter values (`parsave 1`)
* have the genetic architecture at hand (e.g. `archsave 1`) to interpret the genetic data you might save (`locus_*`, `edge_*` and whole individual genomes)
* save `time`, as it is useful information for any of the other variables
* save `population_sizes` whenever `individual_*` variables or whole individual genomes are saved

### Saving genomes

Saving the whole genomes of all individuals through time takes a lot of space, for this reason this output is controlled separately from the other output variables. Click [here](docs/GENOMES.md) for details.

## About

This program is a descendent of [ExplicitGenomeSpeciation](https://github.com/rscherrer/ExplicitGenomeSpeciation). Disclaimer: this simulation program was used to get insights into the effect of the genetic architecture on the process of speciation. It was not designed as a statistical inference package or a data processing tool, although its simulations could in theory be used for training machine learning algorithms to recognize various evolutionary scenarios. This code comes with no guarantee whatsoever.

## Links

* [speciomer](https://github.com/rscherrer/speciomer): read the simulated data in R
* [speciomx](https://github.com/rscherrer/speciomx): deterministic approximation based on adaptive dynamics theory
* [speciome-analyses](https://github.com/rscherrer/speciome-analyses): analysis scripts and results of the study
* [speciome-ms](https://github.com/rscherrer/speciome-ms): manuscript
* [speciome-private](https://github.com/rscherrer/speciome-private): stuff that needs not be made public

## Permissions

Copyright (c) Raphael Scherrer and G. Sander van Doorn, 2023 (open source license will be added upon publication).

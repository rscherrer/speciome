# speciome

Simulation program for evolutionary biologists to study speciation with a complex genotype-phenotype map.

## Prerequisites

* [CMake](docs/CMAKE.md)
* C++20
* R and speciomer to read and analyze the data

## Build

### Linux, MacOS

```bash
git clone git@github.com:rscherrer/speciome.git
cd speciome
mkdir build && cd build
cmake ..
cmake --build .
```

The executable `speciome` is built in `../bin/`.

### Windows

```bash
git clone git@github.com:rscherrer/speciome.git
cd speciome
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

The executable `speciome.exe` is built in `../bin/`.

### IDEs

Many IDEs support CMake out of the box. "Open folder" should do the trick...
You can use CMake to generate the input files for your favorite IDE too:

```bash
git clone git@github.com:rscherrer/speciome.git
cd speciome
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

### Reading data

The data are saved in binary to speed up the writing (and the reading) process. Plus, different users will need to combine the data in many different ways depending on the question they are asking. To read and assemble the data into analyzable datasets, use our R package [speciomer](https://github.com/rscherrer/speciomer).

### Saving genomes

Saving the whole genomes of all individuals through time takes a lot of space, for this reason this output is controlled separately from the other output variables. If you set `gensave 1` in addition to `datsave 1` two things will be saved every `tsave` generations: 

| File | Variable |
|--|--|
| `individual_whole_genomes.dat` | The whole genome of each individual.|
| `individual_locus_genvalues.dat` | The genetic value of each locus in each individual. |

**Note:** To save space, we use the fact that alleles are binary (0 or 1). Each value in a full genome is an allele at a specific position along one of the two haplotypes of an individual. Therefore, a genome contains twice as many values as there are loci (the organism is diploid). Each value is either 0 or 1 (the two possible alleles). Haplotypes are saved in turns, such that the first N values are all alleles of the first haplotype and the next N values are all alleles of the second haplotype, where N is the number of loci. This does not mean that each saved individual genome is exactly 2N values long, though. In order to save space for this large amount of data, individual genomes are first split into blocks of 64 bits, and each block is converted into a 64bit integer, which is then saved as binary. Therefore, the output file `individual_whole_genomes.dat` must be interpreted on a bit-wise basis in order to retrieve the actual alleles of the individual (i.e. reading it as 64bit integers will show integer-equivalents of chunks of 64 alleles). This also means that for each individual, a multiple of 64 bits will be written to the file, even if 2N alleles is not necessarily a multiple of 64. In other words, for each individual 2N bits will be written to file, and the remaining part of the last 64bit-chunk will be filled with zeros. (You do not have to worry about all that, the R package [speciomer](https://github.com/rscherrer/speciomer) takes care of it.)

**Important:** whole individual genomes take a lot of space. For this reason we advise against saving them too often. To save regular variables frequently and whole genomes less frequently, we recommend running the same simulation twice with different values of `tsave` and making sure that the `seed` is the same. (The seed used by a simulation where no seed was provided can be retrieved in the `paramlog.txt` file, provided that `parsave` is set to 1, or in the `architecture.txt` file provided that `gensave` is set to 1.)

## Which variables to save

Some variables need other variables to be saved in order to be interpreted down the line. For example, `time` must be saved in order for the recorded time points to be appended to the resulting data tables. Or, the `population_sizes` in each recorded time point must be known for each individual to be assigned a time point in `individual_*` variables and in individual whole genomes.

In general we advise the following:

* have the genetic architecture at hand (e.g. `archsave 1`) to interpret the genetic data you might save (`locus_*`, `edge_*` and whole individual genomes)
* save `time`, as it is useful information for any of the other variables
* save `population_sizes` whenever `individual_*` variables or whole individual genomes are saved



We describe the different parameters (and their default value).

Ecological parameters:

* `rdynamics` (default 1) is the type of resource dynamics (0 for *logistic dynamics*, which assume a biotic resource with an intrinsic growth and a carrying capacity, or 1 for *chemostat dynamics* with and inflow and outflow of some abiotic resource)
* `replenish` (2375) and `capacity` (1) are the growth rate and carrying capacity, respectively, of the resources assuming logistic dynamics (`rdynamics 0`)
* `inflow` (400) and `outflow` (100) are the absolute inflow and relative outflow rates of the resources, respectively, assuming chemostat dynamics (`rdynamics 1`)
* `hsymmetry` (0) is the degree of homogeneity in resource distribution between the two habitats. It basically is a scaling factor to make the realized `replenish` (if logistic resource dynamics) or `inflow` (if chemostat resource dynamics) differ between the habitats, ranging between 0 and 1
* `ecosel` (1.8) is the ecological trade-off in utilization between the two resources. It must be zero or positive, and the higher it is, the less efficient is utilizing both resources instead of specializing on a single one
* `ecoscale` (1) is a scaling parameter for the phenotypic distance between the two ecological niches along the ecological trait axis. A value of 1 means that the peaks of the two niches in utilization efficiency are at -1 and +1, respectively. This parameter also scales the widths of the resource utilization curves accordingly
* `demesizes` (100, 0) are the number of individuals initialized in both habitats, respectively
* `dispersal` (0.01) is the proportion of individuals sampled to switch habitats every generation
* `birth` (1) is the base birth rate per female, independent of fitness
* `survival` (0.8) is the probability of survival of adult individuals from one generation to the next (it takes one generation for newborns to become adults)
* `sexsel` (10) is the sexual selection coefficient, a positive number mediating the general degree of choosiness of females towards males during the mating season
* `matingcost` (0.01) is the fitness cost of choosy females (that run the risk of remaining unmated)
* `ntrials` (100) is the number of mating trials to perform to measure the degree of reproductive isolation between the species

Genetic parameters:

* `nvertices` (30, 30, 30) and `nedges` (30, 0, 0) are the numbers of loci and edges, respectively, in each of the three gene networks (one for each trait in the following order: ecological, mating and neutral). `nvertices` must be at least 2 for each trait, and `nedges` cannot be higher than n (n - 1) / 2 (complete graph), if n is the number of vertice for a given trait. In practice, the preferential attachment algorithm may fail to attach all the requested edges of the network if nedges is close to the maximum possible number of edges. In this case the program will return an error. The number of edges should be at least n-1, which ensures that the network is connected (all the nodes are attached).
* `nchrom` (3) is the number of equally sized chromosomes
* `mutation` (0.001) is the mutation rate per locus
* `recombination` (3) is the recombination rate and corresponds more or less to the average number of crossovers during one recombination event. It is actually the rate of an exponential distribution describing the distance between successive crossover points
* `allfreq` (0.2) is the initial frequency of the 1-allele in the population
* `scaleA` (1, 1, 1), `scaleD` (0, 0, 0), `scaleI` (0, 0, 0) and `scaleE` (0, 0, 0) are scaling factors for each source of phenotypic variation in the quantitative genetics framework, i.e. additive, dominance, epistatic and environmental effects, respectively, for each of the three traits
* `skews` (1, 1, 1) are the skewnesses of each of the three gene networks
* `effectshape` (2) and `effectscale` (1) are the parameters of the distribution of additive effect sizes across loci. If the resulting distribution has variance 0, all the loci are assigned effect size 1
* `interactionshape` (5) and `interactionscale` (1) are the parameters of the distribution of epistatic interaction weights across edges. If the resulting distribution has variance 0, all the edges are assigned interaction weight 1 
* `dominancevar` (1) is the standard deviation of the distribution of dominance coefficients across loci. If 0, all the loci are assigned dominance coefficient 1

General simulation parameters:

* `tburnin` (0) is the duration of the burn-in period, in generations
* `tend` (10) is the number of generations to simulate (use a negative value to end the simulation during the burn-in)
* `tsave` (10) is the frequency at which to record the data
* `tcomplete` (1000000) is the time at which to force complete reproductive isolation between the two ecotypes (can mimic e.g. genomic incompatibilities between the two species, or the evolution of very good species recognition abilities)
* `talkative` (1) is either 0 or 1 and sets whether the simulation should print status information to the prompt
* `choosewhattosave` (0) is either 0 or 1 and sets whether the variables to save are specified in a separate file, the order file `whattosave.txt` (see below). If 0 all of the output variables are saved every `tsave` generations except for whole genomes
* `datsave` (1) sets whether to save the recorded variables to files
* `burninsave` (0) sets whether to save data during the burn-in phase too (time points belonging to the burn-in are negative)
* `gensave` (0) is either 0 or 1 and sets whether whole genomes should be saved every `tfreeze` generations (see below)
* `archsave` (0) is either 0 or 1 and sets whether the genetic architecture should be saved into file `architecture.txt` (see below)
* `archload` (0) sets whether the genetic architecture of the simulation should be loaded from file `architecture.txt` instead of generated anew
* `parsave` (1) sets whether to save the parameters of the simulation run to file, including the random seed, into a parameter-log file `paramlog.txt`
* `logsave` (0) sets whether the output to prompt should be redirected to a log file `log.txt`
* `seed` is the seed of the random number generator, and it is by default randomly generated based on the clock

Note that it is a good idea to set `parsave 1` and `logsave 1`, to make sure the full range of parameter values can be retrieved or the simulation progress can be monitored. Some analysis functions from the R package [speciomer](https://github.com/rscherrer/speciomer) actually expect the parameter-log file "paramlog.txt" to be present.


## Misc

This program was written in C++14 in QtCreator 4.9.2 (Qt 5.12.4) on Ubuntu 18.04 LTS, but should run on other platforms too.

This is a copy of the ExplicitGenomeSpeciation program, version 1.0. See https://github.com/rscherrer/ExplicitGenomeSpeciation for more details.

## Disclaimer

This simulation program was used to get insights into the effect of the genetic architecture on the process of speciation. It was not designed as a statistical inference package or a data processing tool, although its simulations could in theory be used for training machine learning algorithms to recognize various evolutionary scenarios.

This code comes with no guarantee whatsoever.

## Permissions

Copyright (c) Raphael Scherrer and G. Sander van Doorn, 2019

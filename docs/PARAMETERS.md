## List of parameters

| name | meaning | default value | note |
|--|--|--|--|
| rdynamics | Type of resource dynamics | 1 | The resource dynamics can be logistic (0) or chemostat-like (1). |
| replenish | Resource growth (logistic) | 2375 | Growth rate of the resource. |
| capacity | Resource capacity (logistic) | 1 | Carrying capacity of the resource. |
| inflow | Resource inflow (chemostat) | 400 | Absolute inflow of the resource. |
| outflow | Resource outflow (chemostat) | 100 | Relative outflow of the resource. |
| hsymmetry | Habitat symmetry | 0 | Degree of homogeneity in resource input between habitats (between 0 and 1). |
| ecosel | Trade-off strength | 1.8 | Utilization trade-off between the two resources. |
| ecoscale | Ecological scale | 1 | Location of the specialist phenotype in ecological trait space. |
| demesizes | Initial population sizes | 100 0 | Initial number of individuals in each habitat. |
| dispersal | Dispersal rate | 0.01 | Probability of dispersal to the other habitat per individual per generation. |
| birth | Baseline birth rate | 1 | Base number of offspring per female per generation. |
| survival | Survival rate | 0.8 | Probability of surviving to the next generation. |
| sexsel | Sexual selection coefficient | 10 | Parameter for the intensity of mate choice. |
| matingcost | Cost of choosiness | 0.01 | Probability that the mating season ends after examining a male. |
| ntrials | Number of mating trials | 100 | Number of trials to perform to measure reproductive isolation. |
| nvertices | Numbers of loci | 30 30 30 | Number of loci coding for each trait. |
| nedges | Numbers of edges | 30 30 30 | Number of edges for each trait. |
| nchrom | Number of chromosomes | 3 | Chromosomes all have equal lengths. |
| mutation | Mutation rate | 0.001 | Probability of mutation per locus. |
| recombination | Recombination rate | 3 | Rate of the exponential distribution describing the distance between two crossovers. |
| allfreq | Initial allele frequency | 0.2 | Starting frequency of the 1-allele. |
| scaleA | Scaling for additive effects | 1 1 1 | |
| scaleD | Scaling for dominance | 0 0 0 | |
| scaleI | Scaling for epistasis | 0 0 0 | |
| scaleE | Scaling for environmental effects | 0 0 0 | |
| skews | Network skewness | 1 1 1 | Skewness of the preferential attachment algorithm for each trait. |
| effectshape | Shape of effet size-distribution | 2 | Gamma distribution parameter. |
| effectscale | Scale of effect size-distribution | 1 | Gamma distribution parameter. |
| interactionshape | Shape of interaction weight-distribution | 5 | Gamma distribution parameter. |
| interactionscale | Scale of interaction weight-distribution | 1 | Gamma distribution parameter. |
| dominancevar | Standard deviation of dominance coefficient-distribution | 1 | Half-normal distribution parameter. |
| tburnin | Burn-in duration | 0 | In number of generations. |
| tend | Simulation time | 10 | In number of generations. |
| tsave | Saving frequency | 10 | In number of generations. |
| tcomplete | Speciation completion time | 1000000 | In number of generations. |
| talkative | Verbose | 1 | Yes (1) or no (0). |
| choosewhattosave | Whether to save specific variables | 0 | Yes (1) or no (0). |
| datsave | Whether to save to file | 1 | Yes (1) or no (0). |
| burninsave | Whether to save the burn-in | 0 | Yes (1) or no (0). |
| gensave | Whether genomes should be saved | 0 | Yes (1) or no (0). |
| archsave | Whether to save architecture | 0 | Yes (1) or no (0). |
| archload | Whether to load architecture | 0 | Yes (1) or no (0). |
| parsave | Whether to save parameters | 1 | Yes (1) or no (0). |
| logsave | Screen output to file | 0 | Yes (1) or no (0). |
| seed | Random number generator seed | Clock-generated | |

|--|--|--|--|

Ecological parameters:

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

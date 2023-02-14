## List of parameters

| Name | Meaning | Default | Note |
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
| nvertices | Numbers of loci | 30 30 30 | Number of loci coding for each trait. At least 2 for each trait. |
| nedges | Numbers of edges | 30 30 30 | Number of edges for each trait. Cannot be higher than n * (n - 1) / 2 (complete graph) if n is the number of vertices for a trait. In practice, the preferential attachment algorithm may fail to attach all the requested edges of the network if nedges is close to the maximum possible number of edges. In this case the program will return an error. The number of edges should be at least n-1, which ensures that the network is connected (all the nodes are attached). |
| nchrom | Number of chromosomes | 3 | Chromosomes all have equal lengths. |
| mutation | Mutation rate | 0.001 | Probability of mutation per locus. |
| recombination | Recombination rate | 3 | Rate of the exponential distribution describing the distance between two crossovers. |
| allfreq | Initial allele frequency | 0.2 | Starting frequency of the 1-allele. |
| scaleA | Scaling for additive effects | 1 1 1 | |
| scaleD | Scaling for dominance | 0 0 0 | |
| scaleI | Scaling for epistasis | 0 0 0 | |
| scaleE | Scaling for environmental effects | 0 0 0 | |
| skews | Network skewness | 1 1 1 | Skewness of the preferential attachment algorithm for each trait. |
| effectshape | Shape of effet size-distribution | 2 | Gamma distribution parameter. If the resulting distribution has variance 0, all the loci are assigned effect size 1. |
| effectscale | Scale of effect size-distribution | 1 | Gamma distribution parameter. If the resulting distribution has variance 0, all the loci are assigned effect size 1. |
| interactionshape | Shape of interaction weight-distribution | 5 | Gamma distribution parameter. If the resulting distribution has variance 0, all the edges are assigned interaction weight 1. |
| interactionscale | Scale of interaction weight-distribution | 1 | Gamma distribution parameter. If the resulting distribution has variance 0, all the edges are assigned interaction weight 1. |
| dominancevar | Standard deviation of dominance coefficient-distribution | 1 | Half-normal distribution parameter. If 0, all the loci are assigned dominance coefficient 1.|
| tburnin | Burn-in duration | 0 | In number of generations. |
| tend | Simulation time | 10 | In number of generations (in addition to the burn-in). |
| tsave | Saving frequency | 10 | In number of generations. |
| tcomplete | Speciation completion time | 1000000 | Number of generations after which reproductive isolation is imposed by force. |
| talkative | Verbose to screen | 1 | Yes (1) or no (0). |
| choosewhattosave | Whether to choose which variables to save | 0 | Yes (1) or no (0). |
| datsave | Whether to allow data recording to files | 1 | Yes (1) or no (0). |
| burninsave | Whether to save the burn-in | 0 | Yes (1) or no (0). |
| gensave | Whether genomes should be saved | 0 | Yes (1) or no (0). |
| archsave | Whether to save architecture | 0 | Yes (1) or no (0). |
| archload | Whether to load architecture | 0 | Yes (1) or no (0). |
| parsave | Whether to save parameters | 1 | Yes (1) or no (0). |
| logsave | Screen output to file | 0 | Yes (1) or no (0). |
| seed | Random number generator seed | Clock-generated | |
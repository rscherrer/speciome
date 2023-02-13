## Genetic architecture file

### Example

This is a file for an architecture with 3 loci coding for each trait, and where each network is a full graph (all three loci are connected in a triangle-shaped network). There are three chromosomes of equal size. All effect sizes, dominance coefficients and interaction weights are 0.1.

```
--parameters--
nvertices 3 3 3 
nedges 3 3 3 
nchrom 3

--architecture--
chromosomes 0.333333 0.666667 1 
traits 0 0 0 1 1 1 2 2 2 
locations 0.01 0.03 0.4 0.5 0.65 0.7 0.88 0.99 0.999
effects 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 
dominances 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 
from 0 0 0 1
to 0 1 2 2
weights 0 0.1 0.1 0.1 
from 1 3 3 4
to 1 4 5 5
weights 1 0.1 0.1 0.1 
from 2 6 6 7
to 2 7 8 8
weights 2 0.1 0.1 0.1 
```

### Rules

* The architecture file is a text file organized in two sections, each delimited by the header "--parameters--" or "--architecture--". Its name must be "architecture.txt" and it must be present in the working directory in order to be read.

* Under the "--parameters--" header are expected the names and values of parameters (or rather hyperparameters) that are important for the set-up of the genetic architecture. Those are `nchrom`, `nvertices` and `nedges`, and should be provided just like in a parameter file (see above). They will be used to read the right numer of entries from the following section, and to override the parameters in the model once the architecture is loaded.

* Under the "--architecture--" header are expected the names and values of the actual architecture fields, which are essentially lists of parameters. There are three kinds of fields, that differ in how many values they take: chromosome-wise fields, locus-wise fields and edge-wise fields.

- Chromosome-wise field: `chromosomes`, consisting of the end location of each chromosome (between 0 and 1, each representing the two ends of the genomes). One value per chromosome.

- Locus-wise fields: `traits`, `locations`, `effects` and `dominances` are the encoded traits (0, 1, or 2), genomic locations (between 0 and 1), additive effect sizes and dominance coefficients of each locus in the genome, respectively. One value per locus.

- Edge-wise fields: `from`, `to` and `weights` are respectively the indices of the first and second partner, and the interaction weight, of each edge. One value per edge. 

* Each field should be followed by the values it takes (e.g. `chromosomes 0.333333 0.666667 1`, `locations 0.01 0.02 0.45 0.6 0.8 0.9`), but if the field is an edge-wise field the values should be preceded by the index of the trait of the network that field belongs to (e.g. `weights 0 0.56 0.37 -0.45 0.67 0.1 -0.89`, where 0 in second position refers to the ecological trait). Fields and values are all separated by spaces.

A randomly-generated genetic architecture can be saved as a ready-to-use architecture file if `archsave` is set to 1 (in this case the architecture will be saved in the file `architecture.txt`). Note that architecture files saved by the program when `archsave` is 1 contain all the parameters of the model that generated the architecture. For any other architecture file supplied, you need to make sure that the aforementioned expected structure is respected and that all the necessary fields are present. Also note that in general it is a good idea to save the genetic architecture used if you are going to save and analyze genetic data from the simulation, as the output variables do not contain details about the architecture, which might make them difficult to interpret otherwise.

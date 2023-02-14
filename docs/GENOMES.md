## Saving genomes

If you set `gensave 1` in addition to `datsave 1` two things will be saved every `tsave` generations: 

| File | Variable |
|--|--|
| `individual_whole_genomes.dat` | The whole genome of each individual.|
| `individual_locus_genvalues.dat` | The genetic value of each locus in each individual. |

**Note:** To save space, we use the fact that alleles are binary (0 or 1). Each value in a full genome is an allele at a specific position along one of the two haplotypes of an individual. Therefore, a genome contains twice as many values as there are loci (the organism is diploid). Each value is either 0 or 1 (the two possible alleles). Haplotypes are saved in turns, such that the first N values are all alleles of the first haplotype and the next N values are all alleles of the second haplotype, where N is the number of loci. This does not mean that each saved individual genome is exactly 2N values long, though. In order to save space for this large amount of data, individual genomes are first split into blocks of 64 bits, and each block is converted into a 64bit integer, which is then saved as binary. Therefore, the output file `individual_whole_genomes.dat` must be interpreted on a bit-wise basis in order to retrieve the actual alleles of the individual (i.e. reading it as 64bit integers will show integer-equivalents of chunks of 64 alleles). This also means that for each individual, a multiple of 64 bits will be written to the file, even if 2N alleles is not necessarily a multiple of 64. In other words, for each individual 2N bits will be written to file, and the remaining part of the last 64bit-chunk will be filled with zeros. (You do not have to worry about all that, the R package [speciomer](https://github.com/rscherrer/speciomer) takes care of it.)

**Important:** whole individual genomes take a lot of space. For this reason we advise against saving them too often. To save regular variables frequently and whole genomes less frequently, we recommend running the same simulation twice with different values of `tsave` and making sure that the `seed` is the same. (The seed used by a simulation where no seed was provided can be retrieved in the `paramlog.txt` file, provided that `parsave` is set to 1, or in the `architecture.txt` file provided that `gensave` is set to 1.)


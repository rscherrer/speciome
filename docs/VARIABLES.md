## List of variables

| File | Variable |
|--|--|
| `time.dat` | Every saved time point. |
| `population_sizes.dat` | Total population size (across both habitats). |
| `ecotype_population_sizes.dat` | Population size of each ecotype. |
| `habitat_resources.dat` | Equilibrium resource concentration of each resource in each habitat. |
| `trait_means.dat` | Mean value of each trait across the whole population. |
| `trait_ecotype_means.dat` | Mean value of each trait in each ecotype. |
| `trait_varP.dat`, `trait_varG.dat`, `trait_varA.dat`, `trait_varD.dat`, `trait_varI.dat`, `trait_varN.dat` | Respectively the phenotypic, genetic, additive, dominance, interaction and non-additive variance for each trait. |
| `trait_varT.dat` | Variance in allele frequencies across loci coding for each trait. |
| `trait_Pst.dat`, `trait_Gst.dat`, `trait_Qst.dat`, `trait_Cst.dat` | Respectively the differentiation statistics between ecotypes for the phenotypic, genetic, additive and non-additive variance for each trait. |
| `trait_Fst.dat` | Fixation index, or genetic differentiation between the two ecotypes, for each trait. |
| `EI.dat`, `SI.dat`, `RI.dat` | Ecological, spatial and reproductive isolation between ecotypes, respectively. |
| `locus_varP.dat`, `locus_varG.dat`, `locus_varA.dat`, `locus_varD.dat`, `locus_varI.dat`, `locus_varN.dat` | Respectively the phenotypic, genetic, additive, dominance, interaction and non-additive variance for each locus in the genome. |
| `locus_Pst.dat`, `locus_Gst.dat`, `locus_Qst.dat`, `locus_Cst.dat`, `locus_Fst.dat` | Respectively the Pst, Gst, Qst, Cst and Fst for each locus. |
| `locus_alpha.dat` | The average mutational effect (i.e. slope of the regression of genetic values against genotypes across the whole population) of each locus. |
| `locus_meang.dat` | The mean genetic value of each locus in the whole population. |
| `locus_freq.dat` | The allele frequency (of the 1-allele) for each locus in the whole population. |
| `locus_ecotype_freq.dat` | The allele frequencies for each locus within each ecotype. |
| `locus_ecotype_hobs.dat` | The observed heterozygosity for each locus within each ecotype. |
| `edge_corgen.dat`, `edge_corbreed.dat`, `edge_corfreq.dat` | Respectively the pairwise correlations in genetic value, breeding value and allele frequency between the two interacting loci for each edge in all three networks (ordered by trait). |
| `edge_avgi.dat`, `edge_avgj.dat` | The expected epistatic variance in average effect of the first and second interacting loci, respectively, for each edge. `edge_avgi` corresponds to the expected effect of genetic variation at locus i on the variation in the additive effect of allele substitutions at locus j, and vice versa for `edge_avgj`. This is mostly for plotting purposes, to detect genes that are expected to modify the additive effects of their interacting partners. |
| `individual_ecotypes.dat`, `individual_habitats.dat` | The ecotype and habitat of each individual. |
| `individual_traits.dat` | The value of each trait for each individual. |
| `individual_midparents.dat` | The midparent phenotype (i.e. the mean between maternal and paternal values) for each trait for each individual. |


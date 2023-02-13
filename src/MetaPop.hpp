#ifndef SPECIOME_METAPOP_HPP
#define SPECIOME_METAPOP_HPP

// This header contains the class MetaPop. A MetaPop is a wrapper around a
// vector of Individual objects with a bunch of member functions applying
// a life cycle to those individuals. Note: it is called MetaPop because
// there are two patches linked by dispersal, so the model is technically
// a metapopulation.

#include "Param.hpp"
#include "GenArch.hpp"
#include "Individual.hpp"
#include "Utilities.hpp"

#include <cassert>

class MetaPop
{

    friend class Collector;
    friend class Locus;
    friend class Connexion;
    friend class Printer;
    friend class Freezer;
    friend class Pedigree;

public:

    MetaPop(const Param &pars, const GenArch &arch) :
        population(populate(pars, arch)),
        isburnin(pars.tburnin > 0),
        iscomplete(false),
        resources(utl::zeros(2u, 2u)),
        sexcounts(utl::uzeros(2u, 2u))
    {

    }

    ~MetaPop() {}

    void exitburnin();
    void complete(); // complete speciation (no more reproduction allowed)
    bool isextinct() const;

    void disperse(const Param&);
    void consume(const Param&);
    void reproduce(const Param&, const GenArch&);
    void survive(const Param&);

    size_t getSize() const;
    size_t getDemeSize(const size_t&) const;
    double getResource(const size_t&, const size_t&) const;
    double getSumFitness() const;
    double getVarFitness() const;
    double getMeanTrait(const size_t&) const;
    double getMeanEcotype(const size_t&) const;
    double getFitness(const size_t&) const;
    size_t getEcotype(const size_t&) const;
    size_t getHabitat(const size_t&) const;
    double getTrait(const size_t&, const size_t&) const;
    double getMidparent(const size_t&, const size_t&) const;
    double getLocusValue(const size_t&, const size_t&) const;
    size_t getAlleleSum() const;
    size_t getZygosity(const size_t&, const size_t&, const size_t&) const;
    Genome getFullGenome(const size_t&) const;
    std::bitset<64u> getGenomeChunk(const size_t&, const size_t&) const;

    void resetTraits(const size_t&, const double&, const Param&);
    void resetTraits(const size_t&, const size_t&, const double&, const Param&);
    void resetGenders(const bool&);
    void resetGenders(const size_t&, const bool&);

private:

    std::vector<Individual> populate(const Param&, const GenArch&);

    std::vector<Individual> population;
    bool isburnin;
    bool iscomplete;

    std::vector<std::vector<double> > resources; // per habitat per resource
    std::vector<std::vector<size_t> > sexcounts; // per habitat per sex

};

#endif

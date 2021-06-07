#include "Printer.h"

// Constructor
Printer::Printer(const std::string &orderfile) :
    filenames(whattosave(orderfile)),
    files({ })
{

}

Printer::~Printer() {
    shutdown();
}

void Printer::open() {

    files.reserve(filenames.size());

    // Open files
    for (size_t f = 0u; f < filenames.size(); ++f) {

        const std::string filename = filenames[f] + ".dat";
        Stream out(new std::ofstream);
        out->open(filename.c_str(), std::ios::binary);
        if (!out->is_open()) {
            std::string msg = "Unable to open output file " + filename;
            throw std::runtime_error(msg);
        }
        files.push_back(out);
    }

}

void Printer::shutdown()
{
    // Close files
    for (size_t f = 0u; f < files.size(); ++f)
        files[f]->close();
}

void Printer::print(const int &t, const Collector &c, const MetaPop &m)
{

    for (size_t f = 0u; f < filenames.size(); ++f) {

        if (filenames[f] == "time")
            stf::write(utl::int2dbl(t), files[f]);
        else if (filenames[f] == "population_sizes")
            stf::write(utl::size2dbl(c.counts[2u][2u]), files[f]);
        else if (filenames[f] == "ecotype_population_sizes")
            for (size_t eco = 0u; eco < 2u; ++eco)
                stf::write(utl::size2dbl(c.counts[2u][eco]), files[f]);
        else if (filenames[f] == "habitat_resources")
            for (size_t hab = 0u; hab < 2u; ++hab)
                for (size_t res = 0u; res < 2u; ++res)
                    stf::write(m.resources[hab][res], files[f]);
        else if (filenames[f] == "trait_means")
            for (size_t trait = 0u; trait < 3u; ++trait)
                stf::write(c.means[trait][2u][2u], files[f]);
        else if (filenames[f] == "ecotype_trait_means")
            for (size_t trait = 0u; trait < 3u; ++trait)
                for (size_t eco = 0u; eco < 2u; ++eco)
                    stf::write(c.means[trait][2u][eco], files[f]);
        else if (filenames[f] == "trait_varP")
            for (size_t trait = 0u; trait < 3u; ++trait)
                stf::write(c.varP[trait][2u], files[f]);
        else if (filenames[f] == "trait_varG")
            for (size_t trait = 0u; trait < 3u; ++trait)
                stf::write(c.varG[trait][2u], files[f]);
        else if (filenames[f] == "trait_varA")
            for (size_t trait = 0u; trait < 3u; ++trait)
                stf::write(c.varA[trait][2u], files[f]);
        else if (filenames[f] == "trait_varD")
            for (size_t trait = 0u; trait < 3u; ++trait)
                stf::write(c.varD[trait], files[f]);
        else if (filenames[f] == "trait_varI")
            for (size_t trait = 0u; trait < 3u; ++trait)
                stf::write(c.varI[trait], files[f]);
        else if (filenames[f] == "trait_varN")
            for (size_t trait = 0u; trait < 3u; ++trait)
                stf::write(c.varN[trait][2u], files[f]);
        else if (filenames[f] == "trait_varT")
            for (size_t trait = 0u; trait < 3u; ++trait)
                stf::write(c.varT[trait], files[f]);
        else if (filenames[f] == "trait_Pst")
            for (size_t trait = 0u; trait < 3u; ++trait)
                stf::write(c.Pst[trait], files[f]);
        else if (filenames[f] == "trait_Gst")
            for (size_t trait = 0u; trait < 3u; ++trait)
                stf::write(c.Gst[trait], files[f]);
        else if (filenames[f] == "trait_Qst")
            for (size_t trait = 0u; trait < 3u; ++trait)
                stf::write(c.Qst[trait], files[f]);
        else if (filenames[f] == "trait_Cst")
            for (size_t trait = 0u; trait < 3u; ++trait)
                stf::write(c.Cst[trait], files[f]);
        else if (filenames[f] == "trait_Fst")
            for (size_t trait = 0u; trait < 3u; ++trait)
                stf::write(c.Fst[trait], files[f]);
        else if (filenames[f] == "EI")
             stf::write(c.EI, files[f]);
        else if (filenames[f] == "SI")
             stf::write(c.SI, files[f]);
        else if (filenames[f] == "RI")
             stf::write(c.RI, files[f]);
        else if (filenames[f] == "locus_varP")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                stf::write(c.genomescan[l].varP[2u], files[f]);
        else if (filenames[f] == "locus_varG")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                stf::write(c.genomescan[l].varG[2u], files[f]);
        else if (filenames[f] == "locus_varA")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                stf::write(c.genomescan[l].varA[2u], files[f]);
        else if (filenames[f] == "locus_varD")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                stf::write(c.genomescan[l].varD, files[f]);
        else if (filenames[f] == "locus_varI")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                stf::write(c.genomescan[l].varI, files[f]);
        else if (filenames[f] == "locus_varN")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                stf::write(c.genomescan[l].varN[2u], files[f]);
        else if (filenames[f] == "locus_Pst")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                stf::write(c.genomescan[l].Pst, files[f]);
        else if (filenames[f] == "locus_Gst")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                stf::write(c.genomescan[l].Gst, files[f]);
        else if (filenames[f] == "locus_Qst")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                stf::write(c.genomescan[l].Qst, files[f]);
        else if (filenames[f] == "locus_Cst")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                stf::write(c.genomescan[l].Cst, files[f]);
        else if (filenames[f] == "locus_Fst")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                stf::write(c.genomescan[l].Fst, files[f]);
        else if (filenames[f] == "locus_alpha")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                stf::write(c.genomescan[l].alpha, files[f]);
        else if (filenames[f] == "locus_meang")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                stf::write(c.genomescan[l].meanG, files[f]);
        else if (filenames[f] == "locus_freq")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                stf::write(c.genomescan[l].freqs[2u], files[f]);
        else if (filenames[f] == "ecotype_locus_freq")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                for (size_t e = 0u; e < 2u; ++e)
                    stf::write(c.genomescan[l].freqs[e], files[f]);
        else if (filenames[f] == "ecotype_locus_hobs")
            for (size_t l = 0u; l < c.genomescan.size(); ++l)
                for (size_t e = 0u; e < 2u; ++e)
                    stf::write(c.genomescan[l].hobs[e], files[f]);
        else if (filenames[f] == "edge_corgen")
            for (size_t e = 0u; e < c.networkscan.size(); ++e)
                stf::write(c.networkscan[e].corgen, files[f]);
        else if (filenames[f] == "edge_corbreed")
            for (size_t e = 0u; e < c.networkscan.size(); ++e)
                stf::write(c.networkscan[e].corbreed, files[f]);
        else if (filenames[f] == "edge_corfreq")
            for (size_t e = 0u; e < c.networkscan.size(); ++e)
                stf::write(c.networkscan[e].corfreq, files[f]);
        else if (filenames[f] == "edge_avgi")
            for (size_t e = 0u; e < c.networkscan.size(); ++e)
                stf::write(c.networkscan[e].avgi, files[f]);
        else if (filenames[f] == "edge_avgj")
            for (size_t e = 0u; e < c.networkscan.size(); ++e)
                stf::write(c.networkscan[e].avgj, files[f]);
        else if (filenames[f] == "individual_ecotypes")
            for (size_t i = 0u; i < m.getSize(); ++i)
                stf::write(utl::size2dbl(m.getEcotype(i)), files[f]);
        else if (filenames[f] == "individual_habitats")
            for (size_t i = 0u; i < m.getSize(); ++i)
                stf::write(utl::size2dbl(m.getHabitat(i)), files[f]);
        else if (filenames[f] == "individual_traits")
            for (size_t i = 0u; i < m.getSize(); ++i)
                for (size_t trait = 0u; trait < 3u; ++trait)
                    stf::write(m.getTrait(i, trait), files[f]);
        else if (filenames[f] == "individual_midparents")
            for (size_t i = 0u; i < m.getSize(); ++i)
                for (size_t trait = 0u; trait < 3u; ++trait)
                    stf::write(m.getMidparent(i, trait), files[f]);
    }
}

std::vector<std::string> Printer::whattosave(const std::string &filename) const
{
    if (filename == "") {

        // Save the following variables if none defined

        return {

            "time",
            "population_sizes",
            "ecotype_population_sizes", // per ecotype
            "habitat_resources", // per habitat per resource
            "trait_means", // per trait
            "ecotype_trait_means", // per trait per ecotype
            "trait_varP", // per trait
            "trait_varG", // per trait
            "trait_varA", // per trait
            "trait_varD", // per trait
            "trait_varI", // per trait
            "trait_varN", // per trait
            "trait_varT", // per trait
            "trait_Pst", // per trait
            "trait_Gst", // per trait
            "trait_Qst", // per trait
            "trait_Cst", // per trait
            "trait_Fst", // per trait
            "EI",
            "SI",
            "RI",
            "locus_varP", // per locus
            "locus_varG", // per locus
            "locus_varA", // per locus
            "locus_varD", // per locus
            "locus_varI", // per locus
            "locus_varN", // per locus
            "locus_Pst", // per locus
            "locus_Gst", // per locus
            "locus_Qst", // per locus
            "locus_Cst", // per locus
            "locus_Fst", // per locus
            "locus_alpha", // per locus
            "locus_meang", // per locus
            "locus_freq", // per locus
            "ecotype_locus_freq", // per locus per ecotype
            "ecotype_locus_hobs", // per locus per ecotype
            "edge_corgen", // per edge
            "edge_corbreed", // per edge
            "edge_corfreq", // per edge
            "edge_avgi", // per edge
            "edge_avgj", // per edge
            "individual_ecotypes", // per individual
            "individual_habitats", // per individual
            "individual_traits", // per individual per trait
            "individual_midparents" // per individual per trait

        };

    }

    std::vector<std::string> variables;

    // Or read file defining what variables to save

    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        std::string msg = "Unable to open order file ";
        throw std::runtime_error(msg + filename);
    }

    std::string input;
    while (file >> input) variables.push_back(input);
    file.close();
    return variables;

}


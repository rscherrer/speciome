#include "Simul.hpp"

// This is the source code for the main simulation function

int simulate(const std::vector<std::string> &args)
{

    try
    {
        if (args.size() > 2u)
            throw std::runtime_error("More than one argument were supplied");

        // Create a default parameter set
        Param pars;

        // Read parameters from a file if supplied
        if (args.size() == 2) pars.read(args[1u]);

        // Create a genetic architecture
        GenArch arch = GenArch(pars);

        // Load the genetic architecture if necessary
        if (pars.archload) arch.load(pars);

        // Save parameters if necessary
        if (pars.parsave) pars.save();

        // Create a metapopulation with two demes
        MetaPop metapop = MetaPop(pars, arch);

        // Create an analytical module
        Collector collector = Collector(arch);

        // Create a printer
        const std::string order = pars.choosewhattosave ? "whattosave.txt" : "";
        Printer printer = Printer(order);
        if (pars.datsave) printer.open();

        // Open the freezer
        Freezer freezer = Freezer();
        if (pars.gensave) {

            freezer.open("individual_whole_genomes.dat");
            freezer.open("individual_locus_genvalues.dat");

        }

        // Redirect output to log file if needed
        if (pars.logsave) pars.logsave = std::freopen("log.txt", "w", stdout);

        // Open a log file
        std::cout << "Simulation started.\n";

        // Loop through time
        for (int t = -pars.tburnin; t <= pars.tend; ++t) {

            // Exit the burnin if needed
            if (t == 0) metapop.exitburnin();

            // Force-complete speciation if needed
            if (t == pars.tcomplete) metapop.complete();

            if (pars.talkative) std::cout << t << '\n';

            // Life cycle of the metapopulation
            metapop.consume(pars);

            const bool timetosave = t % pars.tsave == 0;

            // Analyze the metapopulation if needed
            if (pars.datsave && (t >= 0 || pars.burninsave) && timetosave) {

                // Collect stats
                collector.analyze(metapop, pars, arch);

                // Save them to files
                printer.print(t, collector, metapop);

                // Save whole genomes if needed (space-consuming)
                if (pars.gensave) freezer.freeze(metapop, pars.nloci);

            }

            metapop.reproduce(pars, arch);
            metapop.survive(pars);

            // Is the population still there?
            if (metapop.isextinct()) {
                std::cout << "The population went extinct at t = " << t << '\n';
                break;
            }

            metapop.disperse(pars);
        }

        std::cout << "Simulation ended.\n";
        if (pars.logsave) std::fclose(stdout);

        return 0;
    }
    catch (const std::exception& err)
    {
        std::cerr << "Exception: " << err.what() << '\n';
    }
    catch (const char* err)
    {
        std::cerr << "Exception: " << err << '\n';
    }
    catch (...)
    {
        std::cerr << "Unknown Exception\n";
    }
    return 1;
}

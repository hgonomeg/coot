#include "coordgen.hpp"
#include <coordgen/sketcherMinimizer.h>
#include <memory>

coot::layla::CoordgenOptions::CoordgenOptions() 
    :coordMap(nullptr),
    // We may want to tinker with this
    minimizerPrecision(0.01f),
    coordgenScaling(60.0)
{

}

unsigned int coot::layla::addCoordgenConformer(::RDKit::RWMol& mol,  const coot::layla::CoordgenOptions* const opts_in) {
    std::unique_ptr<CoordgenOptions> opts_default;
    const coot::layla::CoordgenOptions* opts = nullptr;
    if(!opts_in) {
        opts_default = std::make_unique<CoordgenOptions>();
        opts = opts_default.get();
    } else {
        opts = opts_in;
    }
    sketcherMinimizer minimizer(opts->minimizerPrecision);
    // Does it leak memory?
    auto* minimizer_mol = new sketcherMinimizerMolecule();

    // Does it leak memory?
    auto conf = new RDKit::Conformer(mol.getNumAtoms());
    conf->set3D(false);
    mol.clearConformers();
    auto res = mol.addConformer(conf, true);
    return res;
}
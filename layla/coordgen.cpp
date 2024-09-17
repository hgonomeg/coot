#include "coordgen.hpp"
#include <memory>

coot::layla::CoordgenOptions::CoordgenOptions() 
    :coordMap(nullptr)
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
    mol.clearConformers();
    return -1;
}
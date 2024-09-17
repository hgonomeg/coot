#ifndef LAYLA_COORDGEN_HPP
#define LAYLA_COORDGEN_HPP
#include <rdkit/GraphMol/RWMol.h>

namespace coot::layla {

struct CoordgenOptions {
    const RDGeom::INT_POINT2D_MAP* coordMap;
    const float minimizerPrecision;
    const double coordgenScaling;

    CoordgenOptions();
};

/// Generates a 2D conformer for a molecule and replaces the existing conformers.
/// Uses CoordGen library.
unsigned int addCoordgenConformer(::RDKit::RWMol& mol, const CoordgenOptions* const opts = nullptr);

} // namespace coot::layla


#endif
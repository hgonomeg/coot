#ifndef LAYLA_COORDGEN_HPP
#define LAYLA_COORDGEN_HPP
#include <rdkit/GraphMol/RWMol.h>
namespace coot::layla {

struct CoordgenOptions {

};

/// Todo: doc
unsigned int addCoordgenConformer(::RDKit::RWMol& mol, const CoordgenOptions* const opts = nullptr);

} // namespace coot::layla


#endif
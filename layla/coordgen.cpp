#include "coordgen.hpp"
#include <rdkit/GraphMol/RDKitBase.h>
#include <rdkit/GraphMol/MolTransforms/MolTransforms.h>
#include <rdkit/Geometry/Transform3D.h>
#include <coordgen/sketcherMinimizer.h>
#include <memory>
#ifdef __EMSCRIPTEN__
#include "../lhasa/glog_replacement.hpp"
#else
#include <glib.h>
#endif

coot::layla::CoordgenOptions::CoordgenOptions() 
    :coordMap(nullptr),
    // We may want to tinker with this
    // minimizerPrecision(0.01f),
    minimizerPrecision(3.f),
    coordgenScaling(30.0)
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
    // todo: maybe make this configurable?
    minimizer.setTreatNonterminalBondsToMetalAsZOBs(false);
    // Does it leak memory?
    auto* minimizer_mol = new sketcherMinimizerMolecule();

    std::vector<sketcherMinimizerAtom*> atoms(mol.getNumAtoms());
    for (auto atit = mol.beginAtoms(); atit != mol.endAtoms(); ++atit) {
        RDKit::Atom* rdatom = *atit;
        sketcherMinimizerAtom* atom = minimizer_mol->addNewAtom();
        atom->molecule = minimizer_mol;
        atom->atomicNumber = rdatom->getAtomicNum();
        atom->charge = rdatom->getFormalCharge();
        if(opts->coordMap) {
            auto coord_it = opts->coordMap->find(rdatom->getIdx());
            if(coord_it != opts->coordMap->end()) {
                const RDGeom::Point2D& coords = coord_it->second;
                // atom->fixed = true;
                atom->constrained = true;
                atom->rigid = true;
                // atom->force = sketcherMinimizerPointF(
                //     coords.x * opts->coordgenScaling, coords.y * opts->coordgenScaling
                // );
                // or just `atom->coordinates` ?
                atom->templateCoordinates = sketcherMinimizerPointF(
                    coords.x * opts->coordgenScaling, coords.y * opts->coordgenScaling
                );
            }
        }
        atoms[rdatom->getIdx()] = atom;
    }

    std::vector<sketcherMinimizerBond*> bonds(mol.getNumBonds());
    for (auto bondit = mol.beginBonds(); bondit != mol.endBonds(); ++bondit) {
        RDKit::Bond* rdbond = *bondit;
        sketcherMinimizerBond* bond = minimizer_mol->addNewBond(
            atoms[rdbond->getBeginAtomIdx()],
            atoms[rdbond->getEndAtomIdx()]
        );
        // FIX: This is no doubt wrong
        switch (rdbond->getBondType()) {
            case RDKit::Bond::ZERO:
                bond->bondOrder = 0;
                break;
            case RDKit::Bond::SINGLE:
                bond->bondOrder = 1;
                break;
            case RDKit::Bond::DOUBLE:
                bond->bondOrder = 2;
                break;
            case RDKit::Bond::TRIPLE:
                bond->bondOrder = 3;
                break;
            case RDKit::Bond::AROMATIC:
                bond->bondOrder = 1;
                break;
            default:
                g_warning("addCoordgenConformer: Unknown bond type: %i", rdbond->getBondType());
        }
        bonds[rdbond->getIdx()] = bond;
    }

    minimizer_mol->assignBondsAndNeighbors(atoms, bonds);
    // todo: stereo bonds

    minimizer.initialize(minimizer_mol);
    // minimizer.minimizeMolecule(minimizer_mol);
    minimizer.runGenerateCoordinates();

    // Does it leak memory?
    auto conf = new RDKit::Conformer(mol.getNumAtoms());
    conf->set3D(false);

    for (unsigned int i = 0; i < mol.getNumAtoms(); ++i) {
        auto coords = RDGeom::Point3D(
            atoms[i]->coordinates.x() / opts->coordgenScaling,
            atoms[i]->coordinates.y() / opts->coordgenScaling, 
            0.0
        );
        // if(opts->coordMap) {
        //     auto coord_it = opts->coordMap->find(i);
        //     if(coord_it != opts->coordMap->end()) {
        //         const RDGeom::Point2D& map_coords = coord_it->second;
        //         coords = RDGeom::Point3D(map_coords.x, map_coords.y, 0.0);
        //     }
        // }
        conf->setAtomPos(i, coords);
    }

    mol.clearConformers();
    auto res = mol.addConformer(conf, true);
    if (!opts->coordMap || opts->coordMap->empty()) {
        //RDGeom::Point3D centroid{0.0, 0.0, 0.0};
        // center the coordinates
        RDGeom::Transform3D tf;
        auto centroid = MolTransforms::computeCentroid(*conf);
        centroid *= -1;
        tf.SetTranslation(centroid);
        MolTransforms::transformConformer(*conf, tf);
    }

    return res;
}
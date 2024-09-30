/* layla/utils.cpp
 * 
 * Copyright 2023 by Global Phasing Ltd.
 * Author: Jakub Smulski
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA
 */

#include "utils.hpp"
#include <rdkit/GraphMol/MolOps.h>
#ifndef __EMSCRIPTEN__
#include <glib-2.0/glib.h>
#else
#include "../lhasa/glog_replacement.hpp"
#endif
#include <cairo.h>
#include <cairo/cairo-pdf.h>
#include <cairo/cairo-svg.h>
#include "ligand_editor_canvas.hpp"

void coot::layla::remove_non_polar_hydrogens(RDKit::RWMol& mol) {
    std::vector<RDKit::Atom*> atoms_to_be_removed;

    
    // RDKit::MolOps::removeHs()

    auto atoms = mol.atoms();
    for(RDKit::Atom* atom: atoms) {
        if(atom->getAtomicNum() == 1) {
            if(atom->getFormalCharge() == 0) {
                atoms_to_be_removed.push_back(atom);
            }
        }
    }

    for(RDKit::Atom* atom: atoms_to_be_removed) {
        mol.removeAtom(atom);
        try {
            RDKit::MolOps::sanitizeMol(mol);
        } catch (std::exception& e) {
            g_warning("Could not sanitize molecule while removing non-polar hydrogens: %s", e.what());
        }
    }
}

void coot::layla::export_with_cairo(CootLigandEditorCanvas* canvas, std::string path, ExportMode mode, int width, int height) {
    cairo_surface_t* target = nullptr;
    auto draw = [&](){
        if(target) {
            cairo_t* cr = cairo_create(target);
            coot_ligand_editor_canvas_draw_on_cairo_surface(canvas, cr);
        }
    };
    auto ends_with = [](std::string const & value, std::string const & ending){
        if (ending.size() > value.size()) 
            return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    };
    switch (mode) {
        case ExportMode::PDF: {
            if(!ends_with(path, ".pdf")) {
                path += ".pdf";
            }
            target = cairo_pdf_surface_create(path.c_str(), width, height);
            draw();
            break;
        }
        case ExportMode::PNG: {
            // target = cairo_image_surface_create(CAIRO_FORMAT_RGBA128F, width, height);
            target = cairo_image_surface_create(CAIRO_FORMAT_RGB24, width, height);
            draw();
            if(!ends_with(path, ".png")) {
                path += ".png";
            }
            cairo_surface_write_to_png(target, path.c_str());
            break;
        }
        case ExportMode::SVG: {
            if(!ends_with(path, ".svg")) {
                path += ".svg";
            }
            target = cairo_svg_surface_create(path.c_str(), width, height);
            draw();
            break;
        }
        default: {
            break;
        }
    }
    if(target) {
        cairo_surface_destroy(target);
    }
}
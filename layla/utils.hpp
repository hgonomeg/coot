/* layla/utils.hpp
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

#ifndef LAYLA_UTILS_HPP
#define LAYLA_UTILS_HPP
#include <rdkit/GraphMol/RWMol.h>
#include "ligand_editor_canvas.hpp"

namespace coot::layla {


enum class ExportMode: unsigned char {
    PDF,
    PNG,
    SVG
};

void export_with_cairo(CootLigandEditorCanvas* canvas, std::string path, ExportMode mode, int width, int height);

void remove_non_polar_hydrogens(RDKit::RWMol& mol);

}

#endif //  LAYLA_UTILS_HPP
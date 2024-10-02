/* layla/main.cpp
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

// #include "Python.h"
#include <gtk/gtk.h>
#include <thread>
#include <boost/program_options.hpp>
#include "utils/coot-utils.hh"
#include "state.hpp"
#include "generators.hpp"
#include "ui.hpp"
#include "utils.hpp"
#include <iostream>
#include <rdkit/GraphMol/RWMol.h>
#include <rdkit/GraphMol/SmilesParse/SmilesParse.h>
// #include "python_utils.hpp"

struct RuntimeOpts {
    std::optional<std::string> smiles_input;
    std::string output_format;
    std::optional<std::string> output_file;
    unsigned int width, height;
};



int headless_mode(RuntimeOpts& opts) {
    auto format_opt = coot::layla::parse_export_mode(opts.output_format);
    if(!format_opt) {
        std::cerr << "Could not parse output format. See --help for a list of available options.";
        return 1;
    }
    coot::layla::ExportMode emode = *format_opt;

    RDKit::RWMol* molecule = RDKit::SmilesToMol(*opts.smiles_input, 0, false);
    if(!molecule) {
        std::cerr << "RDKit::RWMol* is a nullptr. The SMILES code from commandline options is probably invalid.";
        return 2;
    }
    auto mol_shptr = std::shared_ptr<RDKit::RWMol>(molecule);
    CootLigandEditorCanvas* canvas = coot_ligand_editor_canvas_new();
    gtk_widget_set_size_request(GTK_WIDGET(canvas),  opts.width, opts.height);
    if(coot_ligand_editor_canvas_append_molecule(canvas, std::move(mol_shptr)) == -1) {
        std::cerr << "coot_ligand_editor_canvas_append_molecule() returned -1: The molecule could not be appended to the canvas.";
        g_object_ref_sink(canvas);
        return 3;
    }
    // todo: find a way to center molecule
    coot::layla::export_with_cairo(canvas, *opts.output_file, emode, opts.width, opts.height);
    g_object_ref_sink(canvas);
    return 0;
}

int main(int argc, char** argv) {
    using namespace coot::layla;
    namespace po = boost::program_options;

    po::options_description desc("Options for Layla");
    desc.add_options()
        ("help,h", "Show help")
        ("smiles,s", po::value<std::string>()->value_name("SMILES"),                       "Input SMILES string")
        ("format,f", po::value<std::string>()->value_name("FORMAT")->default_value("svg"), "Output format for headless image generation [svg | png | pdf]")
        ("output,o", po::value<std::string>()->value_name("OUTPUT_FILE"),                  "Output file for headless image generation")
        ("width",  po::value<unsigned int>()->value_name("WIDTH")->default_value(1024),  "Width of output image")
        ("height", po::value<unsigned int>()->value_name("HEIGHT")->default_value(1024), "Height of output image")
    ;

    po::positional_options_description pos_opt;
    pos_opt.add("smiles", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
          options(desc).positional(pos_opt).run(), vm);
    po::notify(vm);    

    if(vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }

    RuntimeOpts runtime_opts;
    if(vm.count("smiles")) {
        runtime_opts.smiles_input = vm["smiles"].as<std::string>();
    }

    if(vm.count("format")) {
        runtime_opts.output_format = vm["format"].as<std::string>();
    }

    if(vm.count("output")) {
        runtime_opts.output_file = vm["output"].as<std::string>();
    }

    if(vm.count("width")) {
        runtime_opts.width = vm["width"].as<unsigned int>();
    }

    if(vm.count("height")) {
        runtime_opts.height = vm["height"].as<unsigned int>();
    }

    // Unfortunately, we have to do that here even though we're not using GUI for headless mode.
    // The reason is that the canvas is a GtkWidget.
    //
    // Luckily this does not seem to be a big deal.
    gtk_init();

    if(runtime_opts.smiles_input.has_value() && runtime_opts.output_file.has_value()) {
        return headless_mode(runtime_opts);
    }

    // std::thread python_init_thread([argc,argv](){
    //     setup_python_basic(argc, argv);
    //     setup_python_module("coot");
    //     setup_python_module("coot_utils");
    // });

    // python_init_thread.detach();

    GtkApplication* app = gtk_application_new("org.pemsley.Layla", G_APPLICATION_NON_UNIQUE);

    GError *error = NULL;
    g_application_register(G_APPLICATION(app), NULL, &error);

    g_signal_connect(app, "activate", G_CALLBACK(+[](GtkApplication* app, gpointer user_data) {

        RuntimeOpts* opts = (RuntimeOpts*)(user_data);

        auto* builder = load_gtk_builder();
        coot::layla::global_layla_gtk_builder = builder;

        auto *win = coot::layla::setup_main_window(app, builder);

        auto* icon_theme = gtk_icon_theme_get_for_display(gtk_widget_get_display(GTK_WIDGET(win)));

        std::string package_dir = coot::package_data_dir();
        std::string prefix_dir = coot::prefix_dir();
        std::string pixmaps_path_for_icons = coot::util::append_dir_dir(package_dir, "pixmaps");
        std::string prefix_main_path_for_icons = coot::util::append_dir_dir(prefix_dir, "share");
        prefix_main_path_for_icons = coot::util::append_dir_dir(prefix_main_path_for_icons, "icons");
        gtk_icon_theme_add_search_path(icon_theme, pixmaps_path_for_icons.c_str());
        gtk_icon_theme_add_search_path(icon_theme, prefix_main_path_for_icons.c_str());

        coot::layla::global_generator_request_task_cancellable = nullptr;

        gtk_window_present(GTK_WINDOW(win));
        gtk_application_add_window(app, GTK_WINDOW(win));

        // TODO: Fix molecule from commandline not centered
        if(opts->smiles_input) {
            g_idle_add(G_SOURCE_FUNC(+[](gpointer user_data){
                RuntimeOpts* opts = (RuntimeOpts*)(user_data);
                RDKit::RWMol* molecule = RDKit::SmilesToMol(*opts->smiles_input, 0, false);
                if(!molecule) {
                    g_warning("RDKit::RWMol* is a nullptr. The SMILES code from commandline options is probably invalid.");
                } else {
                    g_info("SMILES Import: Molecule constructed.");
                    coot::layla::global_instance->append_molecule(molecule);
                }
                return false;
            }), user_data);
        }

    }), &runtime_opts);

    auto ret = g_application_run(G_APPLICATION(app), 0, 0);
    g_info("Exiting...");
    delete coot::layla::global_instance;
    return ret;
}

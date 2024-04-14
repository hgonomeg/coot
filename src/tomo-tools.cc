
#include <chrono>

#include <clipper/ccp4/ccp4_map_io.h>
#include "utils/coot-utils.hh"
#include "coot-utils/coot-map-heavy.hh"
#include "coot-utils/mini-texture.hh"
#include "graphics-info.h"

//! negative becomes positive and positive becomes negative.
//! Apply an offset so that most of the map is above zero.
//!
void reverse_map(int imol_map) {

   graphics_info_t g;
   if (g.is_valid_map_molecule(imol_map)) {
      g.molecules[imol_map].reverse_map();
      g.graphics_draw();
   }
}


void tomo_section_view(int imol, int axis_id);

void set_tomo_section_view_section(int imol, int section_index) {

   GtkWidget *scale = widget_from_builder("tomo_scale");
   GtkAdjustment *adjustment = gtk_range_get_adjustment(GTK_RANGE(scale));
   if (adjustment) {
      gtk_adjustment_set_value(adjustment, section_index);
   }
}


void tomo_scale_adjustment_changed(GtkAdjustment *adj, gpointer user_data) {

   double v = gtk_adjustment_get_value(adj);
   int section = static_cast<int>(v);
   int imol = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(adj), "imol"));
   graphics_info_t g;
   g.set_tomo_section_view_section(imol, section);
   g.graphics_grab_focus();

}

int setup_tomo_slider(int imol) {

   int section = -1;
   graphics_info_t g;
   if (g.is_valid_map_molecule(imol)) {

      const auto &xmap = g.molecules[imol].xmap;

      // move this into graphics_info_t
      clipper::Grid_sampling gs = xmap.grid_sampling();
      int n_sections = gs.nw();
      int mid_section = n_sections/2;
      section = mid_section;

      GtkWidget *tomo_box = widget_from_builder("tomo_slider_vbox");
      GtkWidget *scale = widget_from_builder("tomo_scale");
      gtk_widget_set_visible(tomo_box, TRUE);
      GtkAdjustment *adjustment = gtk_range_get_adjustment(GTK_RANGE(scale));
      if (adjustment) {
         g_object_set_data(G_OBJECT(adjustment), "imol", GINT_TO_POINTER(imol));
         std::string end_str = std::to_string(n_sections - 1);
         double dns_1 = static_cast<double>(n_sections-1);
         gtk_adjustment_set_lower(adjustment, 0);
         gtk_adjustment_set_upper(adjustment, n_sections-1);
         gtk_adjustment_set_step_increment(adjustment, 1.0);
         gtk_adjustment_set_page_increment(adjustment, 5.0);
         gtk_adjustment_set_page_size(adjustment, 0.0);
         gtk_adjustment_set_value(adjustment, mid_section);
         gtk_scale_set_draw_value(GTK_SCALE(scale), TRUE);
         gtk_scale_set_digits(GTK_SCALE(scale), 0);
         gtk_scale_add_mark(GTK_SCALE(scale), 0, GTK_POS_BOTTOM, "0");
         gtk_scale_add_mark(GTK_SCALE(scale), dns_1, GTK_POS_BOTTOM, end_str.c_str());
      }
   }
   return section;
}

void tomo_section_view(int imol, int section_index) {

   // auto tp_start = std::chrono::high_resolution_clock::now();
   graphics_info_t g;
   if (g.is_valid_map_molecule(imol)) {
      g.zoom = 20000.0f; // or should be in setup_tomo_slider()?
      g.set_tomo_section_view_section(imol, section_index);
      g.clipping_front = 4.5;       // c.f. scene_preset_figure_making_action()
      g.clipping_back  = 1.3;

      clipper::Cell cell = g.molecules[imol].xmap.cell();
      clipper::Coord_orth pt(cell.a() * 0.5f, cell.b() * 0.5, cell.c() * 0.5f);
      g.set_rotation_centre(pt);
   }
   // auto tp_now = std::chrono::high_resolution_clock::now();
   // auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(tp_now - tp_start);

}

#ifdef STANDALONE
int main(int argc, char **argv) {
   int status = 0;
   if (argc > 1) {
      std::string map_file_name(argv[1]);
      clipper::CCP4MAPfile file;
      clipper::Xmap<float> xmap;
      if (coot::file_exists(map_file_name)) {
         file.open_read(map_file_name);
         file.import_xmap(xmap);
         file.close_read();
         mini_texture_t(xmap, 128, 0, 1);
      }
   }
   return status;
}
#endif
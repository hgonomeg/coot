/* Generated by build-guile-gtk from "coot-gtk2.defs".  Do not edit. */

#ifdef USE_GUILE_GTK

#include <gtk/gtk.h>
#include "c-interface-gtk-widgets.h"

#include "c-interface-gtk-widgets.h"

#include <libguile.h>
#include <guile-gtk.h>

/* #include "config.h" */
/* #include "compat.h" */
#include <c-interface.h>

extern sgtk_enum_info sgtk_sgtk_timestamp_info;
extern sgtk_enum_info sgtk_gdk_window_type_info;
extern sgtk_enum_info sgtk_gdk_window_class_info;
extern sgtk_enum_info sgtk_gdk_image_type_info;
extern sgtk_enum_info sgtk_gdk_visual_type_info;
extern sgtk_enum_info sgtk_gdk_font_type_info;
extern sgtk_enum_info sgtk_gdk_function_info;
extern sgtk_enum_info sgtk_gdk_fill_info;
extern sgtk_enum_info sgtk_gdk_line_style_info;
extern sgtk_enum_info sgtk_gdk_cap_style_info;
extern sgtk_enum_info sgtk_gdk_join_style_info;
extern sgtk_enum_info sgtk_gdk_cursor_type_info;
extern sgtk_enum_info sgtk_gdk_event_type_info;
extern sgtk_enum_info sgtk_gdk_filter_return_info;
extern sgtk_enum_info sgtk_gdk_crossing_mode_info;
extern sgtk_enum_info sgtk_gdk_notify_type_info;
extern sgtk_enum_info sgtk_gdk_subwindow_mode_info;
extern sgtk_enum_info sgtk_gdk_status_info;
extern sgtk_enum_info sgtk_gdk_byte_order_info;
extern sgtk_enum_info sgtk_gdk_selection_info;
extern sgtk_enum_info sgtk_gdk_selection_type_info;
extern sgtk_enum_info sgtk_gdk_target_info;
extern sgtk_enum_info sgtk_gdk_property_state_info;
extern sgtk_enum_info sgtk_gdk_prop_mode_info;
extern sgtk_enum_info sgtk_gdk_overlap_type_info;
extern sgtk_enum_info sgtk_gdk_drag_protocol_info;
extern sgtk_enum_info sgtk_gdk_gravity_info;
extern sgtk_enum_info sgtk_gdk_visibility_state_info;
extern sgtk_enum_info sgtk_gdk_input_source_info;
extern sgtk_enum_info sgtk_gdk_rgb_dither_info;
extern sgtk_enum_info sgtk_gdk_fill_rule_info;
extern sgtk_enum_info sgtk_gtk_window_type_info;
extern sgtk_enum_info sgtk_gtk_state_type_info;
extern sgtk_enum_info sgtk_gtk_direction_type_info;
extern sgtk_enum_info sgtk_gtk_shadow_type_info;
extern sgtk_enum_info sgtk_gtk_arrow_type_info;
extern sgtk_enum_info sgtk_gtk_pack_type_info;
extern sgtk_enum_info sgtk_gtk_policy_type_info;
extern sgtk_enum_info sgtk_gtk_update_type_info;
extern sgtk_enum_info sgtk_gtk_visibility_info;
extern sgtk_enum_info sgtk_gtk_window_position_info;
extern sgtk_enum_info sgtk_gtk_submenu_direction_info;
extern sgtk_enum_info sgtk_gtk_submenu_placement_info;
extern sgtk_enum_info sgtk_gtk_metric_type_info;
extern sgtk_enum_info sgtk_gtk_relief_style_info;
extern sgtk_enum_info sgtk_gtk_scroll_type_info;
extern sgtk_enum_info sgtk_gtk_position_type_info;
extern sgtk_enum_info sgtk_gtk_preview_type_info;
extern sgtk_enum_info sgtk_gtk_selection_mode_info;
extern sgtk_enum_info sgtk_gtk_orientation_info;
extern sgtk_enum_info sgtk_gtk_toolbar_style_info;
extern sgtk_enum_info sgtk_gtk_toolbar_child_type_info;
extern sgtk_enum_info sgtk_gtk_button_box_style_info;
extern sgtk_enum_info sgtk_gtk_tree_view_mode_info;
extern sgtk_enum_info sgtk_gtk_curve_type_info;
extern sgtk_enum_info sgtk_gtk_fundamental_type_info;
extern sgtk_enum_info sgtk_gtk_justification_info;
extern sgtk_enum_info sgtk_gtk_spin_button_update_policy_info;
extern sgtk_enum_info sgtk_gtk_spin_type_info;
extern sgtk_enum_info sgtk_gtk_cell_type_info;
extern sgtk_enum_info sgtk_gtk_sort_type_info;
extern sgtk_enum_info sgtk_gtk_anchor_type_info;
extern sgtk_enum_info sgtk_gtk_text_direction_info;
extern sgtk_enum_info sgtk_gtk_ctree_pos_info;
extern sgtk_enum_info sgtk_gtk_ctree_line_style_info;
extern sgtk_enum_info sgtk_gtk_toolbar_space_style_info;
extern sgtk_enum_info sgtk_gtk_progress_bar_orientation_info;
extern sgtk_enum_info sgtk_gtk_progress_bar_style_info;
extern sgtk_enum_info sgtk_gtk_icon_size_info;
extern sgtk_enum_info sgtk_gtk_message_type_info;
extern sgtk_enum_info sgtk_gtk_buttons_type_info;
extern sgtk_enum_info sgtk_gtk_calendar_display_options_info;
extern sgtk_enum_info sgtk_gtk_wrap_mode_info;
extern sgtk_enum_info sgtk_gdk_window_attributes_type_info;
extern sgtk_enum_info sgtk_gdk_window_hints_info;
extern sgtk_enum_info sgtk_gdk_event_mask_info;
extern sgtk_enum_info sgtk_gdk_modifier_type_info;
extern sgtk_enum_info sgtk_gdk_input_condition_info;
extern sgtk_enum_info sgtk_gdk_drag_action_info;
extern sgtk_enum_info sgtk_gdk_wmdecoration_info;
extern sgtk_enum_info sgtk_gdk_wmfunction_info;
extern sgtk_enum_info sgtk_gtk_attach_options_info;
extern sgtk_enum_info sgtk_gtk_signal_run_type_info;
extern sgtk_enum_info sgtk_gtk_widget_flags_info;
extern sgtk_enum_info sgtk_gtk_arg_flags_info;
extern sgtk_enum_info sgtk_gtk_accel_flags_info;
extern sgtk_enum_info sgtk_gtk_dest_defaults_info;
extern sgtk_enum_info sgtk_gtk_dialog_flags_info;
extern sgtk_boxed_info sgtk_gtimer_info;
extern sgtk_boxed_info sgtk_gdk_rgb_cmap_info;
extern sgtk_boxed_info sgtk_gdk_font_info;
extern sgtk_boxed_info sgtk_gdk_event_info;
extern sgtk_boxed_info sgtk_gdk_color_info;
extern sgtk_boxed_info sgtk_gdk_region_info;
extern sgtk_boxed_info sgtk_gdk_cursor_info;
extern sgtk_boxed_info sgtk_pango_language_info;
extern sgtk_boxed_info sgtk_pango_font_description_info;
extern sgtk_boxed_info sgtk_pango_font_metrics_info;
extern sgtk_boxed_info sgtk_gtk_selection_data_info;
extern sgtk_boxed_info sgtk_gtk_notebook_page_info;
extern sgtk_boxed_info sgtk_gtk_text_iter_info;
extern sgtk_object_info sgtk_gobject_info;
extern sgtk_object_info sgtk_gdk_display_info;
extern sgtk_object_info sgtk_gdk_colormap_info;
extern sgtk_object_info sgtk_gdk_visual_info;
extern sgtk_object_info sgtk_gdk_drawable_info;
extern sgtk_object_info sgtk_gdk_window_info;
extern sgtk_object_info sgtk_gdk_pixmap_info;
extern sgtk_object_info sgtk_gdk_image_info;
extern sgtk_object_info sgtk_gdk_drag_context_info;
extern sgtk_object_info sgtk_gdk_gc_info;
extern sgtk_object_info sgtk_pango_context_info;
extern sgtk_object_info sgtk_pango_layout_info;
extern sgtk_object_info sgtk_gtk_accel_group_info;
extern sgtk_object_info sgtk_gtk_style_info;
extern sgtk_object_info sgtk_gtk_object_info;
extern sgtk_object_info sgtk_gtk_widget_info;
extern sgtk_object_info sgtk_gtk_container_info;
extern sgtk_object_info sgtk_gtk_fixed_info;
extern sgtk_object_info sgtk_gtk_tree_item_info;
extern sgtk_object_info sgtk_gtk_tree_info;
extern sgtk_object_info sgtk_gtk_adjustment_info;
extern sgtk_object_info sgtk_gtk_clist_info;
extern sgtk_object_info sgtk_gtk_bin_info;
extern sgtk_object_info sgtk_gtk_event_box_info;
extern sgtk_object_info sgtk_gtk_window_info;
extern sgtk_object_info sgtk_gtk_handle_box_info;
extern sgtk_object_info sgtk_gtk_box_info;
extern sgtk_object_info sgtk_gtk_button_box_info;
extern sgtk_object_info sgtk_gtk_hbutton_box_info;
extern sgtk_object_info sgtk_gtk_vbutton_box_info;
extern sgtk_object_info sgtk_gtk_toolbar_info;
extern sgtk_object_info sgtk_gtk_table_info;
extern sgtk_object_info sgtk_gtk_button_info;
extern sgtk_object_info sgtk_gtk_toggle_button_info;
extern sgtk_object_info sgtk_gtk_check_button_info;
extern sgtk_object_info sgtk_gtk_radio_button_info;
extern sgtk_object_info sgtk_gtk_misc_info;
extern sgtk_object_info sgtk_gtk_arrow_info;
extern sgtk_object_info sgtk_gtk_label_info;
extern sgtk_object_info sgtk_gtk_layout_info;
extern sgtk_object_info sgtk_gtk_tips_query_info;
extern sgtk_object_info sgtk_gtk_vbox_info;
extern sgtk_object_info sgtk_gtk_hbox_info;
extern sgtk_object_info sgtk_gtk_item_info;
extern sgtk_object_info sgtk_gtk_item_factory_info;
extern sgtk_object_info sgtk_gtk_combo_info;
extern sgtk_object_info sgtk_gtk_statusbar_info;
extern sgtk_object_info sgtk_gtk_gamma_curve_info;
extern sgtk_object_info sgtk_gtk_separator_info;
extern sgtk_object_info sgtk_gtk_hseparator_info;
extern sgtk_object_info sgtk_gtk_vseparator_info;
extern sgtk_object_info sgtk_gtk_frame_info;
extern sgtk_object_info sgtk_gtk_aspect_frame_info;
extern sgtk_object_info sgtk_gtk_progress_bar_info;
extern sgtk_object_info sgtk_gtk_progress_info;
extern sgtk_object_info sgtk_gtk_tooltips_info;
extern sgtk_object_info sgtk_gtk_menu_shell_info;
extern sgtk_object_info sgtk_gtk_menu_bar_info;
extern sgtk_object_info sgtk_gtk_menu_info;
extern sgtk_object_info sgtk_gtk_menu_item_info;
extern sgtk_object_info sgtk_gtk_image_info;
extern sgtk_object_info sgtk_gtk_image_menu_item_info;
extern sgtk_object_info sgtk_gtk_tearoff_menu_item_info;
extern sgtk_object_info sgtk_gtk_accel_label_info;
extern sgtk_object_info sgtk_gtk_check_menu_item_info;
extern sgtk_object_info sgtk_gtk_radio_menu_item_info;
extern sgtk_object_info sgtk_gtk_separator_menu_item_info;
extern sgtk_object_info sgtk_gtk_option_menu_info;
extern sgtk_object_info sgtk_gtk_pixmap_info;
extern sgtk_object_info sgtk_gtk_viewport_info;
extern sgtk_object_info sgtk_gtk_scrolled_window_info;
extern sgtk_object_info sgtk_gtk_list_item_info;
extern sgtk_object_info sgtk_gtk_list_info;
extern sgtk_object_info sgtk_gtk_notebook_info;
extern sgtk_object_info sgtk_gtk_editable_info;
extern sgtk_object_info sgtk_gtk_entry_info;
extern sgtk_object_info sgtk_gtk_spin_button_info;
extern sgtk_object_info sgtk_gtk_text_info;
extern sgtk_object_info sgtk_gtk_alignment_info;
extern sgtk_object_info sgtk_gtk_drawing_area_info;
extern sgtk_object_info sgtk_gtk_curve_info;
extern sgtk_object_info sgtk_gtk_preview_info;
extern sgtk_object_info sgtk_gtk_file_selection_info;
extern sgtk_object_info sgtk_gtk_font_selection_dialog_info;
extern sgtk_object_info sgtk_gtk_color_selection_dialog_info;
extern sgtk_object_info sgtk_gtk_color_selection_info;
extern sgtk_object_info sgtk_gtk_range_info;
extern sgtk_object_info sgtk_gtk_scale_info;
extern sgtk_object_info sgtk_gtk_hscale_info;
extern sgtk_object_info sgtk_gtk_vscale_info;
extern sgtk_object_info sgtk_gtk_scrollbar_info;
extern sgtk_object_info sgtk_gtk_hscrollbar_info;
extern sgtk_object_info sgtk_gtk_vscrollbar_info;
extern sgtk_object_info sgtk_gtk_ruler_info;
extern sgtk_object_info sgtk_gtk_hruler_info;
extern sgtk_object_info sgtk_gtk_vruler_info;
extern sgtk_object_info sgtk_gtk_dialog_info;
extern sgtk_object_info sgtk_gtk_input_dialog_info;
extern sgtk_object_info sgtk_gtk_message_dialog_info;
extern sgtk_object_info sgtk_gtk_calendar_info;
extern sgtk_object_info sgtk_gtk_plug_info;
extern sgtk_object_info sgtk_gtk_socket_info;
extern sgtk_object_info sgtk_gtk_paned_info;
extern sgtk_object_info sgtk_gtk_hpaned_info;
extern sgtk_object_info sgtk_gtk_vpaned_info;
extern sgtk_object_info sgtk_gtk_text_tag_table_info;
extern sgtk_object_info sgtk_gtk_text_buffer_info;
extern sgtk_object_info sgtk_gtk_text_view_info;
extern sgtk_object_info sgtk_gtk_about_dialog_info;

static sgtk_type_info *type_infos[] = {
  NULL
};

static GtkTypeInfo *type_infos_gtk[] = {
  NULL
};

static char s_main_statusbar[] = "main-statusbar";

SCM
sgtk_main_statusbar ()
{
  GtkWidget* cr_ret;
  cr_ret = main_statusbar ();

  return sgtk_wrap_gtkobj ((GObject*)cr_ret);
}

static char s_main_menubar[] = "coot-main-menubar";

SCM
sgtk_main_menubar ()
{
  GtkWidget* cr_ret;
  cr_ret = main_menubar ();

  return sgtk_wrap_gtkobj ((GObject*)cr_ret);
}

static char s_main_toolbar[] = "main-toolbar";

SCM
sgtk_main_toolbar ()
{
  GtkWidget* cr_ret;
  cr_ret = main_toolbar ();

  return sgtk_wrap_gtkobj ((GObject*)cr_ret);
}

static char s_main_hbox[] = "main-hbox";

SCM
sgtk_main_hbox ()
{
  GtkWidget* cr_ret;
  cr_ret = main_hbox();
  return sgtk_wrap_gtkobj ((GObject*)cr_ret);
}

void
coot_init_glue_types ()
{
  static int done = 0;
  if (!done)
    {
      done = 1;
      sgtk_register_type_infos (type_infos);
      sgtk_register_type_infos_gtk (type_infos_gtk);
    }
}


void
coot_init_glue ()
{

  coot_init_glue_types ();
  sgtk_init_gtk_gtk_glue_types ();
  sgtk_init_gtk_gdk_glue_types ();
  scm_c_define_gsubr(s_main_toolbar,   0, 0, 0, sgtk_main_toolbar);
  scm_c_define_gsubr(s_main_menubar,   0, 0, 0, sgtk_main_menubar);
  scm_c_define_gsubr(s_main_statusbar, 0, 0, 0, sgtk_main_statusbar);
  scm_c_define_gsubr(s_main_hbox,      0, 0, 0, sgtk_main_hbox);
}

#endif //  USE_GUILE

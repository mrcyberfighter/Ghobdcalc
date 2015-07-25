/**
 * Ghobdcalc 
 * Copyright (C) 2014 Bruggemann Eddie.
 * 
 * This file is part of Ghobdcalc.
 * Ghobdcalc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Ghobdcalc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Ghobdcalc. If not, see <http://www.gnu.org/licenses/>
 * 
 ************************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <errno.h>
#include <locale.h>
#include <wchar.h>


#include <gtk/gtk.h>  

#include "GUI/structures.c"

#include "structures/structures.c"

Saving_output_format *operand_output_format ;

Saving_HTML_output_settings *html_settings_gui ;

struct Saving_settings saving_settings ;

struct HTML_settings html_settings ;



#include "bases_utils.c"   /** Include the hobdcalc developpment files. */

struct Operations operations  ;

struct Operations save_operation[1024]  ;

struct Operande entry_values ;

struct Memory_Management memory_management ;

struct Memory_Items memory[255] ;


#include "main_utils.c"  /** Include the Ghodbcalc functions set files. */

#include "gui_utils.c"   /** Include the gui dialog windows code files. */ 

GUI *gui ;

int saving_index ;

guint8 current_entry = 0 ;

gboolean metric_degrees = TRUE ;

static void destroy(GtkWidget *widget ,gpointer pointer) ;

static gboolean delete_event(GtkWidget *widget,GdkEvent *event,gpointer pointer) ;

  
void generate_gui(gchar *css_filepath, GUI *gui) ;  

void base_toggle(GtkToggleButton *button, Button_set *button_set) ;

void set_buttons_sensitivity_digits_set_base_2(Button_set *button_set)  ;
void set_buttons_sensitivity_digits_set_base_8(Button_set *button_set)  ;
void set_buttons_sensitivity_digits_set_base_10(Button_set *button_set) ;
void set_buttons_sensitivity_digits_set_base_16(Button_set *button_set) ;

void press_a_digit(GtkButton *Button, Entry_fields *entry_fields) ;

gboolean key_press_callback(GtkWidget *widget, GdkEventKey  *event, gpointer   user_data) ;

gboolean toggle_angle_metric(GtkToggleButton *button,gpointer *data) ;


gboolean check_entry_max_buf_size(char *input) ;

void unget_entry(GtkWidget *entry,guint8 offset) ;

void convert_operand_in_base(guint8 base) ;

void reset_computing(GtkButton *button,Entry_fields *entry_fields) ;
void erasing(GtkButton *button,Entry_fields *entry_fields) ;
void delete(GtkButton *button,Entry_fields *entry_fields) ;

void press_math_operation_button(GtkButton *Button, Entry_fields *entry_fields) ;
void press_power_operation_button(GtkButton *Button, Entry_fields *entry_fields) ;

void operations_store(GtkButton *button, Operand_sign *operand_sign) ;

void compute_result(GtkButton *button, gpointer *user_data) ;

void revert_result(GtkButton *button, Entry_fields *entry_fields) ;

void memory_operation(GtkButton *button,gpointer *memnav_pos) ;

void store_operation(GtkWidget *widget,int *saving_idx) ;

void diplay_operation_resgistering_message_dialog(void) ;


gboolean destroy_register_message(GtkWidget *widget) ;

gboolean is_nan_or_infinity_error_message(void) ;

gboolean is_entry_empty(const char *input) ;

void clean_up(void) ;



int main(int argc, char *argv[]) {
  
  atexit(clean_up);
  
  gtk_init(&argc,&argv) ;
  
  gui=g_slice_new(GUI) ;
  
  operand_output_format = g_slice_new(Saving_output_format) ;
  
  html_settings_gui = g_slice_new(Saving_HTML_output_settings)  ;
  
  generate_gui(NULL,gui) ;
  
  gtk_widget_show_all(gui->main_window) ;
  
  gtk_main() ;
  
  return 0 ;
    
}

static void destroy(GtkWidget *widget,gpointer pointer) {
  gtk_main_quit() ;
}

static gboolean delete_event(GtkWidget *widget,GdkEvent *event,gpointer pointer) {
  
  if (event->type == GDK_DELETE) {
    return FALSE ;
  }
  else {
    return TRUE ;
  }
}

void generate_gui(gchar *css_filepath,GUI *gui) {
  
  init_calculator() ;
  
  init_current_entry() ;
  
  init_saving_settings() ;
  
  init_html_settings() ;
  
  operations.current_base=10 ;
  
  static int save_idx=0 ;
  
  saving_index=0 ;
  
  memory_management.mem_counter=0 ;
  memory_management.mem_nav_pos=-1 ;
  
  
  gui->main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
  
  g_object_set(gui->main_window, "border-width", 10,NULL) ;
  
  gui->main_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,5) ;
  
  
  
  gtk_window_set_title(GTK_WINDOW(gui->main_window),"Ghobdcalc") ;
  
  gtk_widget_set_size_request(gui->main_window,-1,-1) ;
  
  gtk_window_set_resizable(GTK_WINDOW(gui->main_window),FALSE) ;
  
  gtk_window_set_position(GTK_WINDOW(gui->main_window),GTK_WIN_POS_CENTER) ;
  
  GError *err ;
  
  gtk_window_set_default_icon_from_file("/usr/share/Ghobdcalc/Icon/Ghobdcalc_icon.png",&err);
  
  
  gui->menu=g_slice_new(Menu) ;
  
  gui->menu->menubar=gtk_menu_bar_new() ;
  
  gui->menu->main_menu = gtk_menu_new() ;
  
  gui->menu->main_menu_item = gtk_menu_item_new() ;
  
  gui->menu->main_menu_item_label = gtk_label_new("  Menu") ;
  
  gui->menu->main_menu_item_image = gtk_image_new_from_icon_name("preferences-system",GTK_ICON_SIZE_MENU) ;
  
  gui->menu->main_menu_item_button_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,FALSE) ;
  
  gtk_box_pack_start(GTK_BOX(gui->menu->main_menu_item_button_hbox),gui->menu->main_menu_item_image,FALSE,FALSE,0) ;
  
  gtk_box_pack_start(GTK_BOX(gui->menu->main_menu_item_button_hbox),gui->menu->main_menu_item_label,FALSE,FALSE,0) ;
  
  gtk_container_add(GTK_CONTAINER(gui->menu->main_menu_item),gui->menu->main_menu_item_button_hbox) ;
  
  
  gui->menu->main_menu_export_item = gtk_menu_item_new() ;
  
  gui->menu->main_menu_export_label = gtk_label_new("  Export as.") ;
  
  gui->menu->main_menu_export_image = gtk_image_new_from_icon_name("document-new",GTK_ICON_SIZE_MENU) ;
  
  gui->menu->main_menu_export_button_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,FALSE) ;
  
  gtk_box_pack_start(GTK_BOX(gui->menu->main_menu_export_button_hbox),gui->menu->main_menu_export_image,FALSE,FALSE,0) ;
  
  gtk_box_pack_start(GTK_BOX(gui->menu->main_menu_export_button_hbox),gui->menu->main_menu_export_label,FALSE,FALSE,0) ;
  
  gtk_container_add(GTK_CONTAINER(gui->menu->main_menu_export_item),gui->menu->main_menu_export_button_hbox) ;
  
  
  gui->menu->main_menu_separator_1 = gtk_separator_menu_item_new() ;
  
  
  gui->menu->main_menu_about_item = gtk_menu_item_new() ;
  
  gui->menu->main_menu_about_label = gtk_label_new("  About") ;
  
  gui->menu->main_menu_about_image = gtk_image_new_from_icon_name("help-about",GTK_ICON_SIZE_MENU) ;
  
  gui->menu->main_menu_about_button_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,FALSE) ;
  
  gtk_box_pack_start(GTK_BOX(gui->menu->main_menu_about_button_hbox),gui->menu->main_menu_about_image,FALSE,FALSE,0) ;
  
  gtk_box_pack_start(GTK_BOX(gui->menu->main_menu_about_button_hbox),gui->menu->main_menu_about_label,FALSE,FALSE,0) ;
  
  gtk_container_add(GTK_CONTAINER(gui->menu->main_menu_about_item),gui->menu->main_menu_about_button_hbox) ;
  
  
  gui->menu->main_menu_separator_2 = gtk_separator_menu_item_new() ;
  
  
  gui->menu->main_menu_quit_item = gtk_menu_item_new() ;
  
  gui->menu->main_menu_quit_label = gtk_label_new("  Quit") ;
  
  gui->menu->main_menu_quit_image = gtk_image_new_from_icon_name("application-exit",GTK_ICON_SIZE_MENU) ;
  
  gui->menu->main_menu_quit_button_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,FALSE) ;
  
  gtk_box_pack_start(GTK_BOX(gui->menu->main_menu_quit_button_hbox),gui->menu->main_menu_quit_image,FALSE,FALSE,0) ;
  
  gtk_box_pack_start(GTK_BOX(gui->menu->main_menu_quit_button_hbox),gui->menu->main_menu_quit_label,FALSE,FALSE,0) ;
  
  gtk_container_add(GTK_CONTAINER(gui->menu->main_menu_quit_item),gui->menu->main_menu_quit_button_hbox) ;
 
  
  gtk_menu_shell_append(GTK_MENU_SHELL(gui->menu->menubar),gui->menu->main_menu_item) ;
  
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(gui->menu->main_menu_item),gui->menu->main_menu);
  
  gtk_menu_shell_append(GTK_MENU_SHELL(gui->menu->main_menu),gui->menu->main_menu_export_item) ;
  
  gtk_menu_shell_append(GTK_MENU_SHELL(gui->menu->main_menu),gui->menu->main_menu_separator_1) ;
  
  gtk_menu_shell_append(GTK_MENU_SHELL(gui->menu->main_menu),gui->menu->main_menu_about_item) ;
  
  gtk_menu_shell_append(GTK_MENU_SHELL(gui->menu->main_menu),gui->menu->main_menu_separator_2) ;
  
  gtk_menu_shell_append(GTK_MENU_SHELL(gui->menu->main_menu),gui->menu->main_menu_quit_item) ;
  
  
  gtk_widget_set_tooltip_text(gui->menu->main_menu_export_item,"Generate an calculation data sheet, from saved operations, as an text, csv or html document.") ;
  gtk_widget_set_tooltip_text(gui->menu->main_menu_about_item,"Display informations about Ghobdcalc.") ;
  gtk_widget_set_tooltip_text(gui->menu->main_menu_quit_item,"Quit the application.") ;
  
  g_signal_connect(G_OBJECT(gui->menu->main_menu_export_item),"activate",G_CALLBACK(export_dialog), &save_idx) ;
  
  g_signal_connect(G_OBJECT(gui->menu->main_menu_about_item),"activate",G_CALLBACK(display_about_dialog),NULL) ;
  
  g_signal_connect(G_OBJECT(gui->menu->main_menu_quit_item),"activate",G_CALLBACK(gtk_main_quit),NULL) ;
  
  gui->upper_grid = gtk_grid_new() ;
  
  g_object_set(gui->upper_grid, "border-width",5,NULL) ;
  
  
  gtk_grid_set_column_spacing(GTK_GRID(gui->upper_grid),12) ;
  gtk_grid_set_row_spacing(GTK_GRID(gui->upper_grid),5) ;
  
  gui->entry_fields=g_slice_new(Entry_fields) ;
  
  gui->entry_fields->upper_entry = gtk_entry_new() ;
    
  g_object_set(G_OBJECT(gui->entry_fields->upper_entry),"editable",FALSE,NULL) ;
  
  
  
  gtk_entry_set_alignment(GTK_ENTRY(gui->entry_fields->upper_entry),0.5);
  
  gui->mem_add_button =  gtk_button_new_with_label(" MEM ADD ") ;
  gui->mem_del_button =  gtk_button_new_with_label(" MEM DEL ") ;
  gui->mem_get_button =  gtk_button_new_with_label(" MEM GET ") ;
  
  
  g_object_set_data(G_OBJECT(gui->mem_add_button),"mem_op","save") ;
  g_object_set_data(G_OBJECT(gui->mem_del_button),"mem_op","del") ;
  g_object_set_data(G_OBJECT(gui->mem_get_button),"mem_op","get") ;
  
  g_signal_connect(G_OBJECT(gui->mem_add_button),"clicked",G_CALLBACK(memory_operation),NULL) ;
  g_signal_connect(G_OBJECT(gui->mem_del_button),"clicked",G_CALLBACK(memory_operation),NULL) ;
  g_signal_connect(G_OBJECT(gui->mem_get_button),"clicked",G_CALLBACK(memory_operation),NULL) ;
  
  gtk_widget_set_tooltip_text(gui->mem_add_button,"Add the current value to memory.") ;
  gtk_widget_set_tooltip_text(gui->mem_del_button,"Delete the current memory item.") ;
  gtk_widget_set_tooltip_text(gui->mem_get_button,"Set the current memory item as value.") ;
  
  gui->entry_fields->operand_1_entry = gtk_entry_new() ;
  gui->entry_fields->operand_2_entry = gtk_entry_new() ;
  gui->entry_fields->result_entry    = gtk_entry_new() ;
  
  g_object_set(G_OBJECT(gui->entry_fields->operand_1_entry),"editable",TRUE,NULL) ;
  g_object_set(G_OBJECT(gui->entry_fields->operand_2_entry),"editable",FALSE,NULL) ;
  g_object_set(G_OBJECT(gui->entry_fields->result_entry),"editable",FALSE,NULL) ;
  
  
  g_object_set(G_OBJECT(gui->entry_fields->upper_entry),"can-focus",FALSE,NULL) ;
  g_object_set(G_OBJECT(gui->entry_fields->operand_1_entry),"can-focus",FALSE,NULL) ;
  g_object_set(G_OBJECT(gui->entry_fields->operand_2_entry),"can-focus",FALSE,NULL) ;
  g_object_set(G_OBJECT(gui->entry_fields->result_entry),"can-focus",FALSE,NULL) ;
  
  
  gtk_entry_set_alignment(GTK_ENTRY(gui->entry_fields->operand_1_entry),0.5);
  gtk_entry_set_alignment(GTK_ENTRY(gui->entry_fields->operand_2_entry),0.5);
  gtk_entry_set_alignment(GTK_ENTRY(gui->entry_fields->result_entry),0.5);
  
  gtk_entry_set_width_chars(GTK_ENTRY(gui->entry_fields->operand_1_entry),64);
  gtk_entry_set_width_chars(GTK_ENTRY(gui->entry_fields->operand_2_entry),64);
  gtk_entry_set_width_chars(GTK_ENTRY(gui->entry_fields->result_entry),64);
  
  
  
  gui->operand_sign = g_slice_new(Operand_sign) ;
  
  gui->operand_sign->operand_1_sign_button = gtk_button_new_with_label("  <  ") ;
  gui->operand_sign->operand_2_sign_button = gtk_button_new_with_label("  <  ") ;
  gui->result_sign_button    = gtk_button_new_with_label("  =  ") ;
  
  gui->command_store_button  = gtk_button_new_with_label(" SAVING ") ;
  gui->command_delete_button = gtk_button_new_with_label(" DELETE ") ;
  gui->command_revert_button = gtk_button_new_with_label(" REVERT ") ;
 
  
  g_signal_connect(G_OBJECT(gui->command_store_button),"clicked",G_CALLBACK(store_operation),&save_idx) ;
  g_signal_connect(G_OBJECT(gui->command_delete_button),"clicked",G_CALLBACK(delete),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->command_revert_button),"clicked",G_CALLBACK(revert_result),gui->entry_fields) ;
  
  gtk_widget_set_tooltip_text(gui->command_store_button,"Store the current operation.\nSo that you can export the saved operations\nas an an calculation data sheet as an text, csv or html document.") ;
  gtk_widget_set_tooltip_text(gui->command_delete_button,"Delete the entire current operand value.") ;
  gtk_widget_set_tooltip_text(gui->command_revert_button,"Revert the result value as operand 1 value.") ;
  
  g_signal_connect(G_OBJECT(gui->result_sign_button),"clicked",G_CALLBACK(compute_result),NULL) ;
  
  gtk_widget_set_tooltip_text(gui->result_sign_button,"Compute the operation.") ;
  
  
  gtk_grid_attach(GTK_GRID(gui->upper_grid),gui->entry_fields->upper_entry,            0,0,5,1) ;
  
  gtk_grid_attach(GTK_GRID(gui->upper_grid),gui->mem_add_button,         1,1,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->upper_grid),gui->mem_del_button,         1,2,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->upper_grid),gui->mem_get_button,         1,3,1,1) ;
  
  gtk_grid_attach(GTK_GRID(gui->upper_grid),gui->entry_fields->operand_1_entry,        2,1,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->upper_grid),gui->entry_fields->operand_2_entry,        2,2,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->upper_grid),gui->entry_fields->result_entry   ,        2,3,1,1) ;
  
  gtk_grid_attach(GTK_GRID(gui->upper_grid),gui->operand_sign->operand_1_sign_button,  3,1,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->upper_grid),gui->operand_sign->operand_2_sign_button,  3,2,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->upper_grid),gui->result_sign_button   ,  3,3,1,1) ;
  
  gtk_grid_attach(GTK_GRID(gui->upper_grid),gui->command_store_button  , 4,1,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->upper_grid),gui->command_delete_button  , 4,2,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->upper_grid),gui->command_revert_button , 4,3,1,1) ;
  
  
  gui->mem_nav_grid = gtk_grid_new() ;
  
  g_object_set(gui->mem_nav_grid, "border-width",5,NULL) ;
  
  gtk_grid_set_column_spacing(GTK_GRID(gui->mem_nav_grid),15) ;
  gtk_grid_set_row_spacing(GTK_GRID(gui->mem_nav_grid),5) ;
  
  gui->mem_nav_titel_button =  gtk_button_new_with_label(" MEM NAV ") ;
  
  gui->mem_nav_plus_button  =  gtk_button_new_with_label("NAV  ( + )") ;
  
  gui->mem_nav_minus_button  =  gtk_button_new_with_label("NAV  ( - )") ;
  
  g_object_set_data(G_OBJECT(gui->mem_nav_titel_button), "mem_op", "cur") ;
  g_object_set_data(G_OBJECT(gui->mem_nav_plus_button) , "mem_op", "nav+") ;
  g_object_set_data(G_OBJECT(gui->mem_nav_minus_button), "mem_op", "nav-") ;
  
  g_signal_connect(G_OBJECT(gui->mem_nav_titel_button) ,"clicked", G_CALLBACK(memory_operation), NULL) ;
  g_signal_connect(G_OBJECT(gui->mem_nav_plus_button) ,"clicked", G_CALLBACK(memory_operation), NULL) ;
  g_signal_connect(G_OBJECT(gui->mem_nav_minus_button),"clicked", G_CALLBACK(memory_operation), NULL) ;
  
  gtk_widget_set_tooltip_text(gui->mem_nav_titel_button,"Display the current selected memory item.") ;
  gtk_widget_set_tooltip_text(gui->mem_nav_plus_button,"Navigate in the memory items.\nSo that you can select the wanted memory item to retrieve.") ;
  gtk_widget_set_tooltip_text(gui->mem_nav_minus_button,"Navigate in the memory items.\nSo that you can select the wanted memory item to retrieve.") ;
  
  gtk_grid_attach(GTK_GRID(gui->mem_nav_grid),gui->mem_nav_titel_button, 0,0,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->mem_nav_grid),gui->mem_nav_plus_button,  0,1,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->mem_nav_grid),gui->mem_nav_minus_button, 0,2,1,1) ;
  
  
  
  gui->button_set_grid = gtk_grid_new() ;
  
  g_object_set(gui->button_set_grid, "border-width",5,NULL) ;
  
  gtk_grid_set_column_spacing(GTK_GRID(gui->button_set_grid),15) ;
  gtk_grid_set_row_spacing(GTK_GRID(gui->button_set_grid),5) ;
  
  gui->button_set=g_slice_new(Button_set) ;
  
  
  gui->button_set->button_n_0   =  gtk_button_new_with_label(" 0 ") ;
  gui->button_set->button_n_1   =  gtk_button_new_with_label(" 1 ") ;
  gui->button_set->button_n_2   =  gtk_button_new_with_label(" 2 ") ;
  gui->button_set->button_n_3   =  gtk_button_new_with_label(" 3 ") ;
  gui->button_set->button_n_4   =  gtk_button_new_with_label(" 4 ") ;
  gui->button_set->button_n_5   =  gtk_button_new_with_label(" 5 ") ;
  
  gui->button_set->button_n_6   =  gtk_button_new_with_label(" 6 ") ;
  gui->button_set->button_n_7   =  gtk_button_new_with_label(" 7 ") ;
  gui->button_set->button_n_8   =  gtk_button_new_with_label(" 8 ") ;
  gui->button_set->button_n_9   =  gtk_button_new_with_label(" 9 ") ;
  gui->button_set->button_n_A   =  gtk_button_new_with_label(" A ") ;
  
  gui->button_set->button_n_B   =  gtk_button_new_with_label(" B ") ;
  gui->button_set->button_n_C   =  gtk_button_new_with_label(" C ") ;
  gui->button_set->button_n_D   =  gtk_button_new_with_label(" D ") ;
  gui->button_set->button_n_E   =  gtk_button_new_with_label(" E ") ;
  gui->button_set->button_n_F   =  gtk_button_new_with_label(" F ") ;
  
  gui->button_set->button_comma =  gtk_button_new_with_label(" . ") ;
  
  gui->button_set->button_base_hex =  gtk_toggle_button_new_with_label(" HEX ") ;
  gui->button_set->button_base_oct =  gtk_toggle_button_new_with_label(" OCT ") ;
  gui->button_set->button_base_bin =  gtk_toggle_button_new_with_label(" BIN ") ;
  gui->button_set->button_base_dec =  gtk_toggle_button_new_with_label(" DEC ") ;
  
  g_object_set(G_OBJECT(gui->button_set->button_base_dec),"active",TRUE,NULL) ;
  
  g_object_set_data(G_OBJECT(gui->button_set->button_n_0),"digit","0") ;
  g_object_set_data(G_OBJECT(gui->button_set->button_n_1),"digit","1") ;
  g_object_set_data(G_OBJECT(gui->button_set->button_n_2),"digit","2") ;
  g_object_set_data(G_OBJECT(gui->button_set->button_n_3),"digit","3") ;
  g_object_set_data(G_OBJECT(gui->button_set->button_n_4),"digit","4") ;
  
  g_object_set_data(G_OBJECT(gui->button_set->button_n_5),"digit","5") ;
  g_object_set_data(G_OBJECT(gui->button_set->button_n_6),"digit","6") ;
  g_object_set_data(G_OBJECT(gui->button_set->button_n_7),"digit","7") ;
  g_object_set_data(G_OBJECT(gui->button_set->button_n_8),"digit","8") ;
  g_object_set_data(G_OBJECT(gui->button_set->button_n_9),"digit","9") ;
  
  g_object_set_data(G_OBJECT(gui->button_set->button_n_A),"digit","A") ;
  g_object_set_data(G_OBJECT(gui->button_set->button_n_B),"digit","B") ;
  g_object_set_data(G_OBJECT(gui->button_set->button_n_C),"digit","C") ;
  g_object_set_data(G_OBJECT(gui->button_set->button_n_D),"digit","D") ;
  g_object_set_data(G_OBJECT(gui->button_set->button_n_E),"digit","E") ;
  g_object_set_data(G_OBJECT(gui->button_set->button_n_F),"digit","F") ;
  
  g_object_set_data(G_OBJECT(gui->button_set->button_comma),"digit",".") ;
  
  g_signal_connect(G_OBJECT(gui->button_set->button_n_0),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_n_1),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_n_2),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_n_3),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_n_4),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  
  g_signal_connect(G_OBJECT(gui->button_set->button_n_5),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_n_6),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_n_7),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_n_8),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_n_9),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  
  g_signal_connect(G_OBJECT(gui->button_set->button_n_A),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_n_B),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_n_C),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_n_D),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_n_E),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_n_F),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  
  g_signal_connect(G_OBJECT(gui->button_set->button_comma),"clicked",G_CALLBACK(press_a_digit),gui->entry_fields) ;
  
  set_buttons_sensitivity_digits_set_base_10(gui->button_set) ;
  
  g_signal_connect(G_OBJECT(gui->button_set->button_base_hex),"toggled",G_CALLBACK(base_toggle),gui->button_set) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_base_oct),"toggled",G_CALLBACK(base_toggle),gui->button_set) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_base_bin),"toggled",G_CALLBACK(base_toggle),gui->button_set) ;
  g_signal_connect(G_OBJECT(gui->button_set->button_base_dec),"toggled",G_CALLBACK(base_toggle),gui->button_set) ;
  
  gtk_widget_set_tooltip_text(gui->button_set->button_base_hex,"Convert the current value in hexadecimal base value.\nOr set this base as current base.") ;
  gtk_widget_set_tooltip_text(gui->button_set->button_base_oct,"Convert the current value in octal base value.\nOr set this base as current base.") ;
  gtk_widget_set_tooltip_text(gui->button_set->button_base_bin,"Convert the current value in binar base value.\nOr set this base as current base.") ;
  gtk_widget_set_tooltip_text(gui->button_set->button_base_dec,"Convert the current value in decimal base value.\nOr set this base as current base.") ;
  
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_0, 0,0,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_1, 1,0,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_2, 2,0,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_3, 3,0,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_4, 4,0,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_5, 5,0,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_6, 6,0,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_7, 7,0,1,1) ;
  
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_8, 0,1,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_9, 1,1,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_A, 2,1,1,1) ;
  
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_B, 3,1,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_C, 4,1,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_D, 5,1,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_E, 6,1,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_n_F, 7,1,1,1) ;
  
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_base_hex, 0,2,2,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_base_oct, 2,2,2,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_base_bin, 4,2,2,1) ;
  gtk_grid_attach(GTK_GRID(gui->button_set_grid),gui->button_set->button_base_dec, 6,2,2,1) ;
  
  
  
  gui->operators_grid = gtk_grid_new() ;
  
  g_object_set(gui->operators_grid, "border-width",5,NULL) ; 
  
  gtk_grid_set_column_spacing(GTK_GRID(gui->operators_grid),15) ;
  gtk_grid_set_row_spacing(GTK_GRID(gui->operators_grid),5) ;
  
  gui->operators = g_slice_new(Operators) ;
  
  gui->operators->operator_add_button      = gtk_button_new_with_label(" + ") ;
  gui->operators->operator_sub_button      = gtk_button_new_with_label(" - ") ;
  gui->operators->operator_mul_button      = gtk_button_new_with_label(" × ") ;
  gui->operators->operator_div_button      = gtk_button_new_with_label(" ÷ ") ;
  gui->operators->operator_modulo_button   = gtk_button_new_with_label(" % ") ;
  
  g_object_set_data(G_OBJECT(gui->operators->operator_sub_button),"digit","-") ;
  
  g_object_set_data(G_OBJECT(gui->operators->operator_add_button),"opcode"," + ") ;
  g_object_set_data(G_OBJECT(gui->operators->operator_sub_button),"opcode"," - ") ;
  g_object_set_data(G_OBJECT(gui->operators->operator_mul_button),"opcode"," × ") ;
  g_object_set_data(G_OBJECT(gui->operators->operator_div_button),"opcode"," ÷ ") ;
  g_object_set_data(G_OBJECT(gui->operators->operator_modulo_button),"opcode"," % ") ;
  
  g_signal_connect(G_OBJECT(gui->operators->operator_add_button),"clicked",G_CALLBACK(operations_store),gui->operand_sign) ;
  g_signal_connect(G_OBJECT(gui->operators->operator_sub_button),"clicked",G_CALLBACK(operations_store),gui->operand_sign) ;
  g_signal_connect(G_OBJECT(gui->operators->operator_mul_button),"clicked",G_CALLBACK(operations_store),gui->operand_sign) ;
  g_signal_connect(G_OBJECT(gui->operators->operator_div_button),"clicked",G_CALLBACK(operations_store),gui->operand_sign) ;
  g_signal_connect(G_OBJECT(gui->operators->operator_modulo_button),"clicked",G_CALLBACK(operations_store),gui->operand_sign) ;
  
  gtk_widget_set_tooltip_text(gui->operators->operator_add_button,"Set the current operation to be an addition.\nAdd operand 1 and operand 2.") ;
  gtk_widget_set_tooltip_text(gui->operators->operator_sub_button,"Set the current operation to be an substraction.\nSubstract operand 2 from operand 1.") ;
  gtk_widget_set_tooltip_text(gui->operators->operator_mul_button,"Set the current operation to be an multiplication.\nMultiply operand 1 with operand 2.") ;
  gtk_widget_set_tooltip_text(gui->operators->operator_div_button,"Set the current operation to be an division.\nDivide operand 1 per operand 2.") ;
  gtk_widget_set_tooltip_text(gui->operators->operator_modulo_button,"Set the current operation to be an euclidian division.\nDivide operand 1 per operand 2 and give the rest of the division.") ;
  
  gtk_grid_attach(GTK_GRID(gui->operators_grid),gui->operators->operator_add_button, 0,0,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->operators_grid),gui->operators->operator_sub_button, 1,0,1,1) ;
  
  gtk_grid_attach(GTK_GRID(gui->operators_grid),gui->operators->operator_mul_button, 0,1,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->operators_grid),gui->operators->operator_div_button, 1,1,1,1) ;
  
  gtk_grid_attach(GTK_GRID(gui->operators_grid),gui->button_set->button_comma, 0,2,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->operators_grid),gui->operators->operator_modulo_button, 1,2,1,1) ;
  
    
  gui->commands_grid = gtk_grid_new() ;
  
  g_object_set(gui->commands_grid, "border-width",5,NULL) ;  
  
  gtk_grid_set_column_spacing(GTK_GRID(gui->commands_grid),15) ;
  gtk_grid_set_row_spacing(GTK_GRID(gui->commands_grid),5) ;
  
  gui->command_erase_button = gtk_button_new_with_label("  ERASE  ") ;
  gui->command_reset_button = gtk_button_new_with_label("  RESET  ") ;
  gui->command_enter_button = gtk_button_new_with_label("  ENTER  ") ;
  
  g_signal_connect(G_OBJECT(gui->command_erase_button),"clicked",G_CALLBACK(erasing),gui->entry_fields) ;     
  g_signal_connect(G_OBJECT(gui->command_reset_button),"clicked",G_CALLBACK(reset_computing ),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->command_enter_button),"clicked",G_CALLBACK(compute_result),NULL) ;
  
  gtk_widget_set_tooltip_text(gui->command_erase_button,"Erase one digit from the current value.") ;
  gtk_widget_set_tooltip_text(gui->command_reset_button,"Reset the operation.") ;
  gtk_widget_set_tooltip_text(gui->command_enter_button,"Compute the result from the operation.") ;
  
  gtk_grid_attach(GTK_GRID(gui->commands_grid),gui->command_erase_button, 0,0,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->commands_grid),gui->command_reset_button, 0,1,1,1) ;
  gtk_grid_attach(GTK_GRID(gui->commands_grid),gui->command_enter_button, 0,2,1,1) ;
  
  gui->middle_hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
  
  GtkWidget  *padding_box1 = gtk_button_new() ;
  GtkWidget  *padding_box2 = gtk_button_new() ;
  
  g_object_set(padding_box1, "relief", GTK_RELIEF_NONE,NULL) ;
  g_object_set(padding_box2, "relief", GTK_RELIEF_NONE,NULL) ;
  
  gtk_widget_set_child_visible(padding_box1,FALSE);
  gtk_widget_set_child_visible(padding_box2,FALSE);
  
  gtk_box_pack_start(GTK_BOX(gui->middle_hbox), gui->mem_nav_grid,    TRUE,FALSE,0)   ;
  gtk_box_pack_start(GTK_BOX(gui->middle_hbox), padding_box1,         TRUE,FALSE,0)  ;
  gtk_box_pack_start(GTK_BOX(gui->middle_hbox), gui->button_set_grid, TRUE,FALSE,5)  ;
  gtk_box_pack_start(GTK_BOX(gui->middle_hbox), gui->operators_grid,  TRUE,FALSE,5)  ;
  gtk_box_pack_start(GTK_BOX(gui->middle_hbox), padding_box2,         TRUE,FALSE,0)  ;
  gtk_box_pack_start(GTK_BOX(gui->middle_hbox), gui->commands_grid,   TRUE,FALSE,0)   ;
  
  
  
  gui->bottom_hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);        
  
  gui->angle_hbox  = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);  
  
  gui->degrees_button = gtk_toggle_button_new_with_label(" DEG ") ;
  gui->radians_button = gtk_toggle_button_new_with_label(" RAD ") ;
  
  g_object_set_data(G_OBJECT(gui->degrees_button),"metric","degrees") ;
  g_object_set_data(G_OBJECT(gui->radians_button),"metric","radians") ;
  
  gtk_widget_set_tooltip_text(gui->degrees_button,"Threath the values as degrees for trigonometric operations.") ;
  gtk_widget_set_tooltip_text(gui->radians_button,"Threath the values as radians for trigonometric operations.") ;
  
  g_object_set(G_OBJECT(gui->degrees_button), "active", TRUE,  NULL) ;
  
  g_signal_connect(G_OBJECT(gui->degrees_button),"toggled",G_CALLBACK(toggle_angle_metric),NULL) ;
  g_signal_connect(G_OBJECT(gui->radians_button),"toggled",G_CALLBACK(toggle_angle_metric),NULL) ;
  
  gtk_box_pack_start(GTK_BOX(gui->angle_hbox), gui->degrees_button,    TRUE,TRUE,0)  ;
  gtk_box_pack_start(GTK_BOX(gui->angle_hbox), gui->radians_button,    TRUE,TRUE,0)  ;
  
  gui->trigonometric_hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
  
  gui->cos_button = gtk_button_new_with_label(" COS ") ;
  gui->sin_button = gtk_button_new_with_label(" SIN ") ;
  gui->tan_button = gtk_button_new_with_label(" TAN ") ;  
  
  g_object_set_data(G_OBJECT(gui->cos_button),"opcode","cos") ;
  g_object_set_data(G_OBJECT(gui->sin_button),"opcode","sin") ;
  g_object_set_data(G_OBJECT(gui->tan_button),"opcode","tan") ;
  
  gtk_widget_set_tooltip_text(gui->cos_button,"Compute the cosine from the current value and give the result as an conversion back.") ;
  gtk_widget_set_tooltip_text(gui->sin_button,"Compute the sine from the current value and give the result as an conversion back.") ;
  gtk_widget_set_tooltip_text(gui->tan_button,"Compute the tangent from the current value and give the result as an conversion back.") ;
  
  gtk_box_pack_start(GTK_BOX(gui->trigonometric_hbox), gui->cos_button,    TRUE,TRUE,0)  ;
  gtk_box_pack_start(GTK_BOX(gui->trigonometric_hbox), gui->sin_button,    TRUE,TRUE,0)  ;
  gtk_box_pack_start(GTK_BOX(gui->trigonometric_hbox), gui->tan_button,    TRUE,TRUE,0)  ;
  
  gui->arc_trigonometric_hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
  
  gui->acos_button = gtk_button_new_with_label(" ACOS ") ;
  gui->asin_button = gtk_button_new_with_label(" ASIN ") ;
  gui->atan_button = gtk_button_new_with_label(" ATAN ") ;  
  
  g_object_set_data(G_OBJECT(gui->acos_button),"opcode","acos") ;
  g_object_set_data(G_OBJECT(gui->asin_button),"opcode","asin") ;
  g_object_set_data(G_OBJECT(gui->atan_button),"opcode","atan") ;
  
  gtk_widget_set_tooltip_text(gui->acos_button,"Compute the arccosine from the current value and give the result as an conversion back.") ;
  gtk_widget_set_tooltip_text(gui->asin_button,"Compute the arcsine from the current value and give the result as an conversion back.") ;
  gtk_widget_set_tooltip_text(gui->atan_button,"Compute the arctangent from the current value and give the result as an conversion back.") ;
  
  gtk_box_pack_start(GTK_BOX(gui->arc_trigonometric_hbox), gui->acos_button,    TRUE,TRUE,0)  ;
  gtk_box_pack_start(GTK_BOX(gui->arc_trigonometric_hbox), gui->asin_button,    TRUE,TRUE,0)  ;
  gtk_box_pack_start(GTK_BOX(gui->arc_trigonometric_hbox), gui->atan_button,    TRUE,TRUE,0)  ;
  
  gui->hyperbel_trigonometric_hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
  
  gui->cosh_button = gtk_button_new_with_label(" COSH ") ;
  gui->sinh_button = gtk_button_new_with_label(" SINH ") ;
  gui->tanh_button = gtk_button_new_with_label(" TANH ") ;  
  
  g_object_set_data(G_OBJECT(gui->cosh_button),"opcode","cosh") ;
  g_object_set_data(G_OBJECT(gui->sinh_button),"opcode","sinh") ;
  g_object_set_data(G_OBJECT(gui->tanh_button),"opcode","tanh") ;
  
  gtk_widget_set_tooltip_text(gui->cosh_button,"Compute the hyperbolic cosine from the current value and give the result as an conversion back.") ;
  gtk_widget_set_tooltip_text(gui->sinh_button,"Compute the hyperbolic sine from the current value and give the result as an conversion back.") ;
  gtk_widget_set_tooltip_text(gui->tanh_button,"Compute the hyperbolic tangent from the current value and give the result as an conversion back.") ;
  
  gtk_box_pack_start(GTK_BOX(gui->hyperbel_trigonometric_hbox), gui->cosh_button,    TRUE,TRUE,0)  ;
  gtk_box_pack_start(GTK_BOX(gui->hyperbel_trigonometric_hbox), gui->sinh_button,    TRUE,TRUE,0)  ;
  gtk_box_pack_start(GTK_BOX(gui->hyperbel_trigonometric_hbox), gui->tanh_button,    TRUE,TRUE,0)  ;
  
  
  gui->base_bottom_hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
  
  gtk_box_set_homogeneous(GTK_BOX(gui->base_bottom_hbox),TRUE) ;
  
  gui->sqrt_button = gtk_button_new_with_label(" SQRT ") ;
  gui->pow_button  = gtk_button_new_with_label(" POW  ") ;
  gui->abs_button  = gtk_button_new_with_label(" ABS  ") ;
  
  g_object_set_data(G_OBJECT(gui->sqrt_button),"opcode", "sqrt") ;
  g_object_set_data(G_OBJECT(gui->abs_button),"opcode",  "abs")  ;
  
  gtk_widget_set_tooltip_text(gui->sqrt_button,"Compute the square root from the current value and give the result as an conversion back.") ;
  gtk_widget_set_tooltip_text(gui->pow_button,"You must set the base of the power, press this button and give the exponent and press this button again to get the result.") ;
  gtk_widget_set_tooltip_text(gui->abs_button,"Compute the absolute value from the current value and give the result as an conversion back.") ;
  
  gtk_box_pack_start(GTK_BOX(gui->base_bottom_hbox), gui->sqrt_button,    TRUE,TRUE,0)  ;
  gtk_box_pack_start(GTK_BOX(gui->base_bottom_hbox), gui->pow_button,     TRUE,TRUE,0)  ;
  gtk_box_pack_start(GTK_BOX(gui->base_bottom_hbox), gui->abs_button,     TRUE,TRUE,0)  ;
  
  g_signal_connect(G_OBJECT(gui->cos_button),"clicked",G_CALLBACK(press_math_operation_button),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->sin_button),"clicked",G_CALLBACK(press_math_operation_button),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->tan_button),"clicked",G_CALLBACK(press_math_operation_button),gui->entry_fields) ;
  
  g_signal_connect(G_OBJECT(gui->acos_button),"clicked",G_CALLBACK(press_math_operation_button),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->asin_button),"clicked",G_CALLBACK(press_math_operation_button),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->atan_button),"clicked",G_CALLBACK(press_math_operation_button),gui->entry_fields) ;
  
  g_signal_connect(G_OBJECT(gui->cosh_button),"clicked",G_CALLBACK(press_math_operation_button),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->sinh_button),"clicked",G_CALLBACK(press_math_operation_button),gui->entry_fields) ;
  g_signal_connect(G_OBJECT(gui->tanh_button),"clicked",G_CALLBACK(press_math_operation_button),gui->entry_fields) ;
  
  g_signal_connect(G_OBJECT(gui->sqrt_button),"clicked",G_CALLBACK(press_math_operation_button),gui->entry_fields) ;
  
  g_signal_connect(G_OBJECT(gui->pow_button),"clicked",G_CALLBACK(press_power_operation_button),gui->entry_fields) ;
  
  g_signal_connect(G_OBJECT(gui->abs_button),"clicked",G_CALLBACK(press_math_operation_button),gui->entry_fields) ;
  
  
  gtk_box_pack_start(GTK_BOX(gui->bottom_hbox), gui->angle_hbox,                      FALSE,FALSE,5)  ;
  gtk_box_pack_start(GTK_BOX(gui->bottom_hbox), gui->trigonometric_hbox,              FALSE,FALSE,5)  ;
  gtk_box_pack_start(GTK_BOX(gui->bottom_hbox), gui->arc_trigonometric_hbox,          FALSE,FALSE,5)  ;
  gtk_box_pack_start(GTK_BOX(gui->bottom_hbox), gui->hyperbel_trigonometric_hbox,     FALSE,FALSE,5)  ;
  gtk_box_pack_start(GTK_BOX(gui->bottom_hbox), gui->base_bottom_hbox,                FALSE,FALSE,5)  ;
  
  gtk_box_pack_start(GTK_BOX(gui->main_vbox),gui->menu->menubar,    TRUE,TRUE, 5) ;
  gtk_box_pack_start(GTK_BOX(gui->main_vbox),gui->upper_grid,    TRUE,TRUE, 5) ;
  gtk_box_pack_start(GTK_BOX(gui->main_vbox),gui->middle_hbox,   TRUE,TRUE, 5) ;
  gtk_box_pack_start(GTK_BOX(gui->main_vbox), gui->bottom_hbox,  TRUE,TRUE, 5) ;
  
  gtk_container_add(GTK_CONTAINER(gui->main_window),gui->main_vbox) ;
  
  g_signal_connect(G_OBJECT(gui->main_window),"delete-event",G_CALLBACK(delete_event),NULL) ;
  g_signal_connect(G_OBJECT(gui->main_window),"destroy",G_CALLBACK(destroy),NULL) ;
  
  
}
    
void base_toggle(GtkToggleButton *button, Button_set *button_set) {
  
    
    if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_set->button_base_dec)) && ( operations.current_base == 10 ) ) {
      ;
    }
    
    else if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_set->button_base_dec)) && ( operations.current_base != 10 ) ) {
      
      if ( is_nan_or_infinity_error_message() ) {
	g_object_set(G_OBJECT(button_set->button_base_bin),"active",FALSE,NULL) ;
        g_object_set(G_OBJECT(button_set->button_base_oct),"active",FALSE,NULL) ;
        g_object_set(G_OBJECT(button_set->button_base_hex),"active",FALSE,NULL) ;
	
	set_buttons_sensitivity_digits_set_base_10(button_set) ;
	
	operations.current_base = 10 ;
        
	return ;
      }
      
      g_object_set(G_OBJECT(button_set->button_base_bin),"active",FALSE,NULL) ;
      g_object_set(G_OBJECT(button_set->button_base_oct),"active",FALSE,NULL) ;
      g_object_set(G_OBJECT(button_set->button_base_hex),"active",FALSE,NULL) ;
      
      set_buttons_sensitivity_digits_set_base_10(button_set) ;
      
      convert_operand_in_base(10)  ;
      
      operations.current_base = 10 ;
      
      return ;
    }
    
    if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_set->button_base_bin)) && ( operations.current_base == 2 ) ) {
      ;
    }
    
    else if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_set->button_base_bin)) && ( operations.current_base != 2 ) ) {
      
      if ( is_nan_or_infinity_error_message() ) {
	
	
	g_object_set(G_OBJECT(button_set->button_base_dec),"active",FALSE,NULL) ;
        g_object_set(G_OBJECT(button_set->button_base_oct),"active",FALSE,NULL) ;
        g_object_set(G_OBJECT(button_set->button_base_hex),"active",FALSE,NULL) ;
	
	set_buttons_sensitivity_digits_set_base_2(button_set) ;
	
	operations.current_base = 2 ;
        
	return ;
      }
      
      g_object_set(G_OBJECT(button_set->button_base_dec),"active",FALSE,NULL) ;
      g_object_set(G_OBJECT(button_set->button_base_oct),"active",FALSE,NULL) ;
      g_object_set(G_OBJECT(button_set->button_base_hex),"active",FALSE,NULL) ;
      
      set_buttons_sensitivity_digits_set_base_2(button_set) ;
      
      convert_operand_in_base(2)  ;
      
      operations.current_base = 2 ;
      
      return ;
    }
    
    if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_set->button_base_bin)) && ( operations.current_base == 8 ) ) {
      ;
    }
    
    else if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_set->button_base_oct)) && ( operations.current_base != 8 ) ) {
      
      if ( is_nan_or_infinity_error_message() ) {
	g_object_set(G_OBJECT(button_set->button_base_dec),"active",FALSE,NULL) ;
        g_object_set(G_OBJECT(button_set->button_base_bin),"active",FALSE,NULL) ;
        g_object_set(G_OBJECT(button_set->button_base_hex),"active",FALSE,NULL) ;
	
	set_buttons_sensitivity_digits_set_base_8(button_set) ;
	
	operations.current_base = 8 ;
        
	return ;
      }
      
      g_object_set(G_OBJECT(button_set->button_base_dec),"active",FALSE,NULL) ;
      g_object_set(G_OBJECT(button_set->button_base_bin),"active",FALSE,NULL) ;
      g_object_set(G_OBJECT(button_set->button_base_hex),"active",FALSE,NULL) ;
      
      set_buttons_sensitivity_digits_set_base_8(button_set) ;
      
      convert_operand_in_base(8)  ;
      
      operations.current_base = 8 ;
      
      return ;
    }
    
    if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_set->button_base_bin)) && ( operations.current_base == 16 ) ) {
      ;
    }
    
    else if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_set->button_base_hex)) && ( operations.current_base != 16 ) ) {
      
      if ( is_nan_or_infinity_error_message() ) {
	g_object_set(G_OBJECT(button_set->button_base_dec),"active",FALSE,NULL) ;
        g_object_set(G_OBJECT(button_set->button_base_bin),"active",FALSE,NULL) ;
        g_object_set(G_OBJECT(button_set->button_base_oct),"active",FALSE,NULL) ;
	
	set_buttons_sensitivity_digits_set_base_16(button_set) ;
	
	operations.current_base = 16 ;
        
	return ;
      }
      
      g_object_set(G_OBJECT(button_set->button_base_dec),"active",FALSE,NULL) ;
      g_object_set(G_OBJECT(button_set->button_base_bin),"active",FALSE,NULL) ;
      g_object_set(G_OBJECT(button_set->button_base_oct),"active",FALSE,NULL) ;
      
      set_buttons_sensitivity_digits_set_base_16(button_set) ;
      
      convert_operand_in_base(16)  ;
      
      operations.current_base = 16 ;
      
      return ;
    }
    
    
}

void set_buttons_sensitivity_digits_set_base_2(Button_set *button_set) {
  
  gtk_widget_set_sensitive(button_set->button_n_2,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_3,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_4,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_5,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_6,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_7,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_8,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_9,FALSE) ;
  
  gtk_widget_set_sensitive(button_set->button_n_A,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_B,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_C,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_D,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_E,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_F,FALSE) ;
  
  return ;
}
  
void set_buttons_sensitivity_digits_set_base_8(Button_set *button_set) {
  
  gtk_widget_set_sensitive(button_set->button_n_2,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_3,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_4,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_5,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_6,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_7,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_8,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_9,FALSE) ;
  
  gtk_widget_set_sensitive(button_set->button_n_A,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_B,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_C,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_D,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_E,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_F,FALSE) ;
  
  return ;
}

void set_buttons_sensitivity_digits_set_base_10(Button_set *button_set) {
  
  gtk_widget_set_sensitive(button_set->button_n_2,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_3,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_4,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_5,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_6,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_7,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_8,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_9,TRUE) ;
  
  gtk_widget_set_sensitive(button_set->button_n_A,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_B,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_C,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_D,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_E,FALSE) ;
  gtk_widget_set_sensitive(button_set->button_n_F,FALSE) ;
  
  return ;
}
      
void set_buttons_sensitivity_digits_set_base_16(Button_set *button_set) {
  
  gtk_widget_set_sensitive(button_set->button_n_2,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_3,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_4,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_5,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_6,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_7,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_8,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_9,TRUE) ;
  
  gtk_widget_set_sensitive(button_set->button_n_A,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_B,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_C,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_D,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_E,TRUE) ;
  gtk_widget_set_sensitive(button_set->button_n_F,TRUE) ;
  
  return ;
}



void press_a_digit(GtkButton *Button, Entry_fields *entry_fields) {

  if  (current_entry == 0) {
    /* This mean we in the first operand entry */
    
    gchar *current_value=g_malloc0(sizeof(char) * 128) ;
    
    g_stpcpy(current_value,(const gchar *) gtk_entry_get_text(GTK_ENTRY(entry_fields->operand_1_entry)) ) ;
    
    
    
    if ( ( is_string_float(current_value) || is_entry_empty(current_value) ) &&  g_strcmp0(g_object_get_data(G_OBJECT(Button),"digit"),".") == 0 ) {
      
      g_free(current_value) ;
      return ;
    }
    
    
    g_strlcat(current_value,(const gchar *) g_object_get_data(G_OBJECT(Button),"digit"),-1) ;
    
    if (check_entry_max_buf_size(current_value)) { 
      g_free(current_value) ;
      return ;
    }
    
    gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_1_entry),(const gchar *) current_value) ;
    gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),(const gchar *) "") ;
    
    
    g_free(current_value) ;
    
  }
  else if (current_entry == 1) {
    /* This mean we in the second operand entry */
    
    gchar *current_value=g_malloc0(sizeof(char)* 128) ;
    
    g_stpcpy(current_value,(const gchar *) gtk_entry_get_text(GTK_ENTRY(entry_fields->operand_2_entry)) ) ;
    
    if ( ( is_string_float(current_value) || is_entry_empty(current_value) ) && g_strcmp0(g_object_get_data(G_OBJECT(Button),"digit"), ".") == 0) {
      g_free(current_value) ;
      return ;
    }
    
    g_strlcat(current_value,(const gchar *) g_object_get_data(G_OBJECT(Button),"digit"),-1) ;
    
    
    
    if (check_entry_max_buf_size(current_value)) {
      g_free(current_value) ;
      return ;
    }
    
    
    
    gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_2_entry),(const gchar *) current_value) ;
    gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),(const gchar *) "") ;
    
    
    g_free(current_value) ;
  }
    
    
  
  return ; 
}

void operations_store(GtkButton *button, Operand_sign *operand_sign) {
   
  if ( is_nan_or_infinity_error_message() ) {
    return ;
  }
  
  /* for minus Check wether the first char entry is set for negativ value entering */
  
  if ( g_object_get_data(G_OBJECT(button),"digit") && current_entry == 0 && g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_1_entry)),"") == 0) {
    gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_1_entry),"-") ;
    return ;
  }
  else if ( g_object_get_data(G_OBJECT(button),"digit") && current_entry == 1 && g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_2_entry)),"") == 0) {
    gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),"-") ;
    return ;
  }
    
  
  if (current_entry == 0) {
    gchar *current_value=g_malloc0(sizeof(char) * 128) ;
    
    g_stpcpy(current_value,(const gchar *) gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_1_entry)) ) ;
    
    if ( is_entry_empty(current_value) ) {
      g_free(current_value) ;
      return ;
    }
    
    if (! thread_operand_1(current_value,is_string_float(current_value)) ){
      ;
    }
    
    
    
    
    
    current_entry = 1 ;  
    
    g_free(current_value) ;
  }
  else if (current_entry == 1) {
    
    gchar *current_value=g_malloc0(sizeof(char) * 128) ;
    
    
    
    
    g_stpcpy(current_value,(const gchar *) gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_2_entry)) ) ;
    
    if ( is_entry_empty(current_value) ) {
      g_free(current_value) ;
      return ;
    }
    
    exchange_comma_and_float_point(current_value) ;
    
    reset_operand2() ;
    
    if (! thread_operand_2(current_value,is_string_float(current_value)) ) {
      
      ;
    }
    
    g_free(current_value) ;
  }
    
  else if (current_entry == 2) {
     
    gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->result_entry), "") ;
    gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry) , "") ;
    
    
    current_entry = 1 ;  
    
    switch (operations.current_base) {
      case 2 :
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),operations.operande_2.operande_bin_str) ;
	break ;
      case 8 :
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),operations.operande_2.operande_oct_str) ;
	break ;	
      case 10 :
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),operations.operande_2.operande_dec_str) ;
	break ;
     case 16 :
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),operations.operande_2.operande_hex_str) ;
	break ; 	
    }
    
  }
  
  gtk_button_set_label(GTK_BUTTON(operand_sign->operand_2_sign_button),g_object_get_data(G_OBJECT(button),"opcode")) ;  
    
    if ( g_strcmp0(g_object_get_data(G_OBJECT(button),"opcode"), " + ") == 0 ) {
      operations.current_operator=0 ;
    }
    else if ( g_strcmp0(g_object_get_data(G_OBJECT(button),"opcode"), " - ") == 0 ) {
      operations.current_operator=1 ;
    }
    else if ( g_strcmp0(g_object_get_data(G_OBJECT(button),"opcode"), " × ") == 0 ) {
      operations.current_operator=2 ;
    }
    else if ( g_strcmp0(g_object_get_data(G_OBJECT(button),"opcode"), " ÷ ") == 0 ) {
      operations.current_operator=3 ;
    }
    else if ( g_strcmp0(g_object_get_data(G_OBJECT(button),"opcode"), " % ") == 0 ) {
      operations.current_operator=4 ;
    }
    
    
    
  return ;
  
}


    





void compute_result(GtkButton *button, gpointer *user_data) {
  
  if ( is_nan_or_infinity_error_message() ) {
    return ;
  }
  
  if (current_entry == 1) {
    
    if (operations.current_operator == '^') {
      
      return ;
    }
    
    gchar *current_value=g_malloc0(sizeof(char) * 128) ;
    
    g_stpcpy(current_value,(const gchar *) gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_2_entry)) ) ;
    
    exchange_comma_and_float_point(current_value) ;
    
    if (! thread_operand_2(current_value,is_string_float(current_value)) ) {
      ;
    }
    
    g_free(current_value) ;
    
    reset_result() ;
    calc_computing_result(operations.current_operator) ;
    
    current_entry = 2 ;
  }
  
  else if (current_entry == 2) {
    
    reset_result() ;
    
    calc_computing_result(operations.current_operator) ;
    
    
  }
  
  switch (operations.current_base) {
    case 2 :
      gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->result_entry),operations.result.operande_bin_str) ;
      gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),operations.result.operande_bin_str) ;
      break ;
    case 8 :
      gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->result_entry),operations.result.operande_oct_str) ;
      gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),operations.result.operande_oct_str) ;
      break ;	 
    case 10 :
      gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->result_entry),operations.result.operande_dec_str) ;
      gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),operations.result.operande_dec_str) ;
      break ;
    case 16 :
      gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->result_entry),operations.result.operande_hex_str) ;
      gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),operations.result.operande_hex_str) ;
      break ;
  }
    
  if ( (g_strcmp0(operations.result.operande_string,"value out of range (underflow or overflow)") == 0) || (g_strcmp0(operations.result.operande_string,"Zero division error !!!") == 0) ) {
    gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->result_entry),operations.result.operande_string) ;
    gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),operations.result.operande_string) ;
  }
    
  
  
  return ;
}

void convert_operand_in_base(guint8 base) {
  
  gchar *input=g_malloc0(128) ;
  
  /* store all converted values for back converting. */
  
  
  
  if (current_entry == 0) {
    if ( is_entry_empty(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_1_entry))) ) {
      return ;
    }
    
    _Bool value_as_changed=false ;
    
    switch (operations.current_base) {
      case 2 :
	if (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_1_entry)),entry_values.operande_bin_str) != 0) {
	  value_as_changed=true ;
	}
	break ;
      case 8 :
	if (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_1_entry)),entry_values.operande_oct_str) != 0) {
	  value_as_changed=true ;
	}
	break ;
      case 10 :
	if (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_1_entry)),entry_values.operande_dec_str) != 0) {
	  value_as_changed=true ;
	}
	break ;
      case 16 :
	if (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_1_entry)),entry_values.operande_hex_str) != 0) {
	  value_as_changed=true ;
	}
	break ;
    }
    
    if (value_as_changed) {
      
      reset_current_entry() ;
      
      g_stpcpy(input,gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_1_entry)) ) ;  
      
      if (input[strlen(input)-1] == '.') {
	input[strlen(input)-1] ='\0' ;
      }
      
      if ( is_entry_empty(input) ) {
        return ;
      }
      
      register_current_operand(input) ;
    }
    
    
    
    switch (base) {
      case 2 :
        gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_1_entry),entry_values.operande_bin_str) ;
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_bin_str) ;
        break ;
      case 8 :
        gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_1_entry),entry_values.operande_oct_str) ;
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_oct_str) ;
        break ;	 
      case 10 :
        gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_1_entry),entry_values.operande_dec_str) ;
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_dec_str) ;
        break ;
      case 16 :
        gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_1_entry),entry_values.operande_hex_str) ;
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_hex_str) ;
        break ;
    }
    
    operations.current_base=base ;
    operations.operande_1.operand_base=base ;
      
  }
  else if (current_entry == 1) {
    if ( is_entry_empty(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_2_entry))) ) {
      return ;
    }
    
    
    
    _Bool value_as_changed=false ;
    
    switch (operations.current_base) {
      case 2 :
	if (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_2_entry)),entry_values.operande_bin_str) != 0) {
	  value_as_changed=true ;
	}
	break ;
      case 8 :
	if (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_2_entry)),entry_values.operande_oct_str) != 0) {
	  value_as_changed=true ;
	}
	break ;
      case 10 :
	if (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_2_entry)),entry_values.operande_dec_str) != 0) {
	  value_as_changed=true ;
	}
	break ;
      case 16 :
	if (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_2_entry)),entry_values.operande_hex_str) != 0) {
	  value_as_changed=true ;
	}
	break ;
    }
    
    if (value_as_changed) {
      
      reset_current_entry() ;
      
      g_stpcpy(input,gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_2_entry)) ) ;  
      
      if (input[strlen(input)-1] == '.') {
	input[strlen(input)-1] ='\0' ;
      }
      
      if ( is_entry_empty(input) ) {
        return ;
      }
      
      register_current_operand(input) ;
    }
    
    switch (base) {
      case 2 :
        gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),entry_values.operande_bin_str) ;
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_bin_str) ;
        break ;
      case 8 :
        gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),entry_values.operande_oct_str) ;
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_oct_str) ;
        break ;	 
      case 10 :
        gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),entry_values.operande_dec_str) ;
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_dec_str) ;
        break ;
      case 16 :
        gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),entry_values.operande_hex_str) ;
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_hex_str) ;
        break ;
    }
    
    operations.current_base=base ;
    operations.operande_2.operand_base=base ;
    
  }
  else { 
    if ( (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->result_entry)),"") == 0) || (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->result_entry)),"value out of range (underflow or overflow)") == 0) ||  (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->result_entry)),"Zero division error !!!") == 0) ) {
      return ;
    }
    
    
    switch (base) {
      case 2 :
        gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->result_entry),operations.result.operande_bin_str) ;
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),operations.result.operande_bin_str) ;
        break ;
      case 8 :
        gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->result_entry),operations.result.operande_oct_str) ;
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),operations.result.operande_oct_str) ;
        break ;	 
      case 10 :
        gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->result_entry),operations.result.operande_dec_str) ;
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),operations.result.operande_dec_str) ;
        break ;
      case 16 :
        gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->result_entry),operations.result.operande_hex_str) ;
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),operations.result.operande_hex_str) ;
        break ;
    }
    
    operations.current_base=base ;
    operations.result.operand_base=base ;
      
  }
  
  
  g_free(input) ;
  return ;
}


gboolean toggle_angle_metric(GtkToggleButton *button,gpointer *data) {
  if ( metric_degrees && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gui->radians_button)) ) {
    
    g_object_set(G_OBJECT(gui->radians_button), "active", TRUE,  NULL) ;
    g_object_set(G_OBJECT(gui->degrees_button), "active", FALSE, NULL) ;
    
    gtk_widget_set_sensitive(gui->radians_button,FALSE) ;
    gtk_widget_set_sensitive(gui->degrees_button,TRUE) ;
    
    metric_degrees = FALSE ;
    
    return FALSE ;
    
  }
  
  else if ( ! metric_degrees && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gui->degrees_button)) ) {
    
    g_object_set(G_OBJECT(gui->degrees_button), "active", TRUE,  NULL) ;
    g_object_set(G_OBJECT(gui->radians_button), "active", FALSE, NULL) ;
    
    gtk_widget_set_sensitive(gui->radians_button,TRUE) ;
    gtk_widget_set_sensitive(gui->degrees_button,FALSE) ;
    
    metric_degrees = TRUE ;
    
    
    
    return FALSE ;
  }
  
  return FALSE ;
}



void press_math_operation_button(GtkButton *Button, Entry_fields *entry_fields) {
  
  if ( is_nan_or_infinity_error_message() ) {
    return ;
  }
  
  gchar *current_value=g_malloc0(128) ;
  
  guint8 opcode ;
  
  if ( g_strcmp0(g_object_get_data(G_OBJECT(Button),"opcode"), "cos") == 0 ) {
    opcode=1 ;
  }
  else if ( g_strcmp0(g_object_get_data(G_OBJECT(Button),"opcode"),  "sin") == 0 ) {
    opcode=2 ;
  }
  else if ( g_strcmp0(g_object_get_data(G_OBJECT(Button),"opcode"), "tan") == 0 ) {
    opcode=3 ;
  }
  else if ( g_strcmp0(g_object_get_data(G_OBJECT(Button),"opcode"), "acos") == 0 ) {
    opcode=4 ;
  }
  else if ( g_strcmp0(g_object_get_data(G_OBJECT(Button),"opcode"), "asin") == 0 ) {
    opcode=5 ;
  }
  else if ( g_strcmp0(g_object_get_data(G_OBJECT(Button),"opcode"), "atan") == 0 ) {
    opcode=6 ;
  }
  else if ( g_strcmp0(g_object_get_data(G_OBJECT(Button),"opcode"), "cosh") == 0 ) {
    opcode=7 ;
  }
  else if ( g_strcmp0(g_object_get_data(G_OBJECT(Button),"opcode"), "sinh") == 0 ) {
    opcode=8 ;
  }
  else if ( g_strcmp0(g_object_get_data(G_OBJECT(Button),"opcode"), "tanh") == 0 ) {
    opcode=9 ;
  }
  else if ( g_strcmp0(g_object_get_data(G_OBJECT(Button),"opcode"), "sqrt") == 0 ) {
    opcode=10 ;
  }
  else if ( g_strcmp0(g_object_get_data(G_OBJECT(Button),"opcode"), "abs") == 0 ) {
    opcode=11 ;
  }
  
  if (current_entry == 0) {
    
    g_stpcpy(current_value,(const gchar *) gtk_entry_get_text(GTK_ENTRY(entry_fields->operand_1_entry)) ) ;
    
    if ( is_entry_empty(current_value) ) {
      g_free(current_value) ;
      return ;
    }
    
    reset_current_entry() ;
    process_math_operation(current_value,opcode,metric_degrees) ;
    
    switch (operations.current_base) {
      case 2 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_1_entry),entry_values.operande_bin_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),entry_values.operande_bin_str) ;
        break ;
      case 8 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_1_entry),entry_values.operande_oct_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),entry_values.operande_oct_str) ;
        break ;	 
      case 10 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_1_entry),entry_values.operande_dec_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),entry_values.operande_dec_str) ;
        break ;
      case 16 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_1_entry),entry_values.operande_hex_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),entry_values.operande_hex_str) ;
        break ;
    }
  }
  
  else if (current_entry == 1) {
    
    g_stpcpy(current_value,(const gchar *) gtk_entry_get_text(GTK_ENTRY(entry_fields->operand_2_entry)) ) ;
    
    if ( is_entry_empty(current_value) ) {
      g_free(current_value) ;
      return ;
    }
    
    reset_current_entry() ;
    process_math_operation(current_value,opcode,metric_degrees) ;
    
    switch (operations.current_base) {
      case 2 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_2_entry),entry_values.operande_bin_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),entry_values.operande_bin_str) ;
        break ;
      case 8 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_2_entry),entry_values.operande_oct_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),entry_values.operande_oct_str) ;
        break ;	 
      case 10 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_2_entry),entry_values.operande_dec_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),entry_values.operande_dec_str) ;
        break ;
      case 16 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_2_entry),entry_values.operande_hex_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),entry_values.operande_hex_str) ;
        break ;
    }
  }
  
  else if (current_entry == 2) {
    
    g_stpcpy(current_value,(const gchar *) gtk_entry_get_text(GTK_ENTRY(entry_fields->result_entry)) ) ;
    
    if ( is_entry_empty(current_value) ) {
      g_free(current_value) ;
      return ;
    }
    
    reset_current_entry() ;
    process_math_operation(current_value,opcode,metric_degrees) ;
    
    copy_entry_in_result() ;
    
    switch (operations.current_base) {
      case 2 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->result_entry),operations.result.operande_bin_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),operations.result.operande_bin_str) ;
        break ;
      case 8 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->result_entry),operations.result.operande_oct_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),operations.result.operande_oct_str) ;
        break ;	 
      case 10 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->result_entry),operations.result.operande_dec_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),operations.result.operande_dec_str) ;
        break ;
      case 16 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->result_entry),operations.result.operande_hex_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),operations.result.operande_hex_str) ;
        break ;
    }
  }
  
  g_free(current_value) ;
  return ;
}

void press_power_operation_button(GtkButton *Button, Entry_fields *entry_fields) {
  
  if (current_entry == 0) {
    
    if ( g_strcmp0(gtk_entry_get_text(GTK_ENTRY(entry_fields->operand_1_entry)),"") == 0 ) {
      gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry), "Enter the base from the power and then press the POW button to set the exponent") ;
      return ;
    }
    
    else {
      gchar *current_value=g_malloc0(128) ;
      
      g_stpcpy(current_value, gtk_entry_get_text(GTK_ENTRY(entry_fields->operand_1_entry)) ) ;
      
      if (! thread_operand_1(current_value,is_string_float(current_value)) ){
        ;
      }
      
      g_free(current_value) ;
      
      gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry), "Base from power set. Set the exponent now and then press the POW button again to get the result.") ;
      gtk_button_set_label(GTK_BUTTON(gui->operand_sign->operand_2_sign_button)," ^ ") ; 
      
      current_entry=1 ;
      operations.current_operator='^' ;
      return ;
    }
  }
  else if (current_entry == 1) {
    if ( g_strcmp0(gtk_entry_get_text(GTK_ENTRY(entry_fields->operand_2_entry)),"") == 0 ) {
      
      gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry), "Enter the exponent from the power and then press the POW button again to get the result.") ;
      gtk_button_set_label(GTK_BUTTON(gui->operand_sign->operand_2_sign_button)," ^ ") ; 
      
      return ;
    }
    else {
      
      gchar *current_value=g_malloc0(128) ;
      
      g_stpcpy(current_value, gtk_entry_get_text(GTK_ENTRY(entry_fields->operand_2_entry)) ) ;
      
      if (! thread_operand_2(current_value,is_string_float(current_value)) ){
        ;
      }
      
      current_entry=2 ;
      
      g_free(current_value) ;
      
      reset_result() ;
      process_power_operation() ;
      
      switch (operations.current_base) {
      case 2 :
	gtk_entry_set_text(GTK_ENTRY(entry_fields->result_entry),operations.result.operande_bin_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),operations.result.operande_bin_str) ;
	break ;
      case 8 :
	gtk_entry_set_text(GTK_ENTRY(entry_fields->result_entry),operations.result.operande_oct_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),operations.result.operande_oct_str) ;
	break ;	 
      case 10 :
	gtk_entry_set_text(GTK_ENTRY(entry_fields->result_entry),operations.result.operande_dec_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),operations.result.operande_dec_str) ;
	break ;
      case 16 :
	gtk_entry_set_text(GTK_ENTRY(entry_fields->result_entry),operations.result.operande_hex_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),operations.result.operande_hex_str) ;
	break ;
      }
      
      if ( g_strcmp0(operations.result.operande_string,"value out of range (underflow or overflow)") == 0 ) {
	gtk_entry_set_text(GTK_ENTRY(entry_fields->result_entry),operations.result.operande_string) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),operations.result.operande_string) ;
      }
      
      gtk_button_set_label(GTK_BUTTON(gui->operand_sign->operand_2_sign_button)," ^ ") ; 
      
      operations.current_operator='^' ;
      
    }
    
  }
  
  else if (current_entry == 2) {
    gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->result_entry), "") ;
    gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry) , "") ;
    
    
    current_entry = 1 ;  
    
    switch (operations.current_base) {
      case 2 :
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),operations.operande_2.operande_bin_str) ;
	break ;
      case 8 :
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),operations.operande_2.operande_oct_str) ;
	break ;	
      case 10 :
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),operations.operande_2.operande_dec_str) ;
	break ;
     case 16 :
	gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),operations.operande_2.operande_hex_str) ;
	break ; 	
    }
    
    gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry), "Set the exponent and then press the POW button to get the result.") ;
    gtk_button_set_label(GTK_BUTTON(gui->operand_sign->operand_2_sign_button)," ^ ") ; 
    
    operations.current_operator='^' ;
  }
  return ;
}
      
void memory_operation(GtkButton *button,gpointer *memnav_pos) {
  
  
  if ( g_strcmp0(g_object_get_data(G_OBJECT(button),"mem_op"),"save") == 0 ) {
    
    
    
    if ( is_nan_or_infinity_error_message() ) {
      /** Display the unavailibility to save result */
      gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),"Unable to store an error value in memory !") ;
      return ;
      
    }
    
    if (memory_management.mem_counter > 255) {
      /** Display the unavailibility to save result **/
      gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),"Unable to store value in memory: memory full.") ;
      return ;
      
    }
      
    
    
    if (current_entry == 0) {
      
      char *current_value=g_malloc0(128) ;
       
      reset_current_entry() ;
      
      g_stpcpy(current_value,gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_1_entry)) ) ;  
      
      if ( is_entry_empty(current_value) ) {
        g_free(current_value) ;
        return ;
      }
      
      register_current_operand(current_value) ;
      
      g_free(current_value) ;
      
      add_memory(memory_management.mem_counter) ;
      
    }
    else if (current_entry == 1) {
      
      char *current_value=g_malloc0(128) ;
      
      reset_current_entry() ;
      
      g_stpcpy(current_value,gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_2_entry)) ) ;  
      
      if ( is_entry_empty(current_value) ) {
        g_free(current_value) ;
        return ;
      }
      
      register_current_operand(current_value) ;
      
      g_free(current_value) ;
      
      add_memory(memory_management.mem_counter) ;
      
      
    }
    else if (current_entry == 2) {
      
      if ( (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->result_entry)),"value out of range (underflow or overflow)") == 0) || (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->result_entry)),"Zero division error !!!") == 0) ) {
        gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),"Unable to store an error value in memory !") ;
	return ;
      }
      
      copy_result_in_entry() ;
      
      add_memory(memory_management.mem_counter) ;
      
    }
    
    memory_management.mem_counter++ ;
    memory_management.mem_nav_pos=memory_management.mem_counter-1 ;
    
    gchar *msg_store_in_memory_at = g_malloc0(128) ;
    
    sprintf(msg_store_in_memory_at,"Value in base %d stored in memory at position: %d",operations.current_base,memory_management.mem_counter) ;
    
    msg_store_in_memory_at[127]='\0' ;
    
    gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),msg_store_in_memory_at) ;
    
    g_free(msg_store_in_memory_at) ;
    
    return ;
      
  }
  
  else if ( g_strcmp0(g_object_get_data(G_OBJECT(button),"mem_op"),"get") == 0 && (memory_management.mem_counter != 0) ) {
    
    get_item_from_memory(memory_management.mem_nav_pos) ;
    
    if (current_entry == 0) {
      
      
      
      switch (entry_values.operand_base) {
	case 2 :
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->button_set->button_base_bin),TRUE) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_1_entry),entry_values.operande_bin_str) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_bin_str) ;
	  set_buttons_sensitivity_digits_set_base_2(gui->button_set) ;
	  break ;
	case 8 :
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->button_set->button_base_oct),TRUE) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_1_entry),entry_values.operande_oct_str) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_oct_str) ;
	  set_buttons_sensitivity_digits_set_base_8(gui->button_set) ;
	  break ;	 
	case 10 :
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->button_set->button_base_dec),TRUE) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_1_entry),entry_values.operande_dec_str) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_dec_str) ;
	  set_buttons_sensitivity_digits_set_base_10(gui->button_set) ;
	  break ;
	case 16 :
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->button_set->button_base_hex),TRUE) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_1_entry),entry_values.operande_hex_str) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_hex_str) ;
	  set_buttons_sensitivity_digits_set_base_16(gui->button_set) ;
	  break ;
      }
      
      
      operations.current_base=entry_values.operand_base ;
      
      
      
      return ;
      
    }
    
    else if (current_entry == 1) {
      
      
      
      switch (entry_values.operand_base) {
	case 2 :
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->button_set->button_base_bin),TRUE) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),entry_values.operande_bin_str) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_bin_str) ;
	  set_buttons_sensitivity_digits_set_base_2(gui->button_set) ;
	  break ;
	case 8 :
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->button_set->button_base_oct),TRUE) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),entry_values.operande_oct_str) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_oct_str) ;
	  set_buttons_sensitivity_digits_set_base_8(gui->button_set) ;
	  break ;	 
	case 10 :
          gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->button_set->button_base_dec),TRUE) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),entry_values.operande_dec_str) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_dec_str) ;
	  set_buttons_sensitivity_digits_set_base_10(gui->button_set) ;
	  break ;
	case 16 :
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->button_set->button_base_hex),TRUE) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->operand_2_entry),entry_values.operande_hex_str) ;
	  gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),entry_values.operande_hex_str) ;
	  set_buttons_sensitivity_digits_set_base_16(gui->button_set) ;
	  break ;
      }
      
      operations.current_base=entry_values.operand_base ;
      
            
      return ;
      
    }
    
  }
  
  else if ( g_strcmp0(g_object_get_data(G_OBJECT(button),"mem_op"),"del") == 0 && (memory_management.mem_counter != 0) ) {
    
    del_item_from_memory(memory_management.mem_nav_pos) ;
    
    gchar *msg_del_from_memory_at = g_malloc0(128) ;
    
    sprintf(msg_del_from_memory_at,"Memory item at position %d delete from memory !",memory_management.mem_nav_pos) ;
    
    gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),msg_del_from_memory_at) ;
    
    memory_management.mem_counter-- ;
    
    g_free(msg_del_from_memory_at) ;
    
    return ;
    
  }
  
  else if ( g_strcmp0(g_object_get_data(G_OBJECT(button),"mem_op"),"cur") == 0 && (memory_management.mem_counter != 0) ) {
    
    get_item_from_memory(memory_management.mem_nav_pos) ;
    
    gchar *msg_nav_cur_get_memory_item = g_malloc0(128) ;
    
    switch (entry_values.operand_base) {
	
      case 2 :
	sprintf(msg_nav_cur_get_memory_item,"Memory item [%d] -> %s [base %d]",memory_management.mem_nav_pos,entry_values.operande_bin_str,entry_values.operand_base) ;
	break ;
      
      case 8 :
	sprintf(msg_nav_cur_get_memory_item,"Memory item [%d] -> %s [base %d]",memory_management.mem_nav_pos,entry_values.operande_oct_str,entry_values.operand_base) ;
	break ;  

      case 10 :
	sprintf(msg_nav_cur_get_memory_item,"Memory item [%d] -> %s [base %d]",memory_management.mem_nav_pos,entry_values.operande_dec_str,entry_values.operand_base) ;
	break ;
      
      case 16 :
	sprintf(msg_nav_cur_get_memory_item,"Memory item [%d] -> %s [base %d]",memory_management.mem_nav_pos,entry_values.operande_hex_str,entry_values.operand_base) ;
	break ; 
	
    }	
    
    msg_nav_cur_get_memory_item[127]='\0' ;
    
    gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),msg_nav_cur_get_memory_item) ;
    
    g_free(msg_nav_cur_get_memory_item) ;
    
    return ;
  }
  
  else if ( g_strcmp0(g_object_get_data(G_OBJECT(button),"mem_op"),"nav+") == 0 && (memory_management.mem_counter != 0) ) {
    
    
    
    if ( (memory_management.mem_nav_pos+1 >= memory_management.mem_counter) || (memory_management.mem_nav_pos+1 > 254) ) {
      return ;
    }
    
    memory_management.mem_nav_pos++ ;
    
    get_item_from_memory(memory_management.mem_nav_pos) ;
    
    gchar *msg_nav_incr_get_memory_item = g_malloc0(128) ;
    
    switch (entry_values.operand_base) {
	
      case 2 :
	sprintf(msg_nav_incr_get_memory_item,"Memory item [%d] -> %s [base %d]",memory_management.mem_nav_pos,entry_values.operande_bin_str,entry_values.operand_base) ;
	break ;
      
      case 8 :
	sprintf(msg_nav_incr_get_memory_item,"Memory item [%d] -> %s [base %d]",memory_management.mem_nav_pos,entry_values.operande_oct_str,entry_values.operand_base) ;
	break ;  

      case 10 :
	sprintf(msg_nav_incr_get_memory_item,"Memory item [%d] -> %s [base %d]",memory_management.mem_nav_pos,entry_values.operande_dec_str,entry_values.operand_base) ;
	break ;
      
      case 16 :
	sprintf(msg_nav_incr_get_memory_item,"Memory item [%d] -> %s [base %d]",memory_management.mem_nav_pos,entry_values.operande_hex_str,entry_values.operand_base) ;
	break ; 
	
    }	
    
    msg_nav_incr_get_memory_item[127]='\0' ;
    
    gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),msg_nav_incr_get_memory_item) ;
    
    g_free(msg_nav_incr_get_memory_item) ;
    
    return ;
  }
  
  else if ( g_strcmp0(g_object_get_data(G_OBJECT(button),"mem_op"),"nav-") == 0 && (memory_management.mem_counter != 0) ) {
    
    if (memory_management.mem_nav_pos-1 < 0 ) {
      return ;
    }
    
    memory_management.mem_nav_pos-- ;
    
    get_item_from_memory(memory_management.mem_nav_pos) ;
    
    gchar *msg_nav_decr_get_memory_item = g_malloc0(128) ;
    
    switch (entry_values.operand_base) {
	
      case 2 :
	sprintf(msg_nav_decr_get_memory_item,"Memory item [%d] -> %s [base %d]",memory_management.mem_nav_pos,entry_values.operande_bin_str,entry_values.operand_base) ;
	break ;
      
      case 8 :
	sprintf(msg_nav_decr_get_memory_item,"Memory item [%d] -> %s [base %d]",memory_management.mem_nav_pos,entry_values.operande_oct_str,entry_values.operand_base) ;
	break ;  

      case 10 :
	sprintf(msg_nav_decr_get_memory_item,"Memory item [%d] -> %s [base %d]",memory_management.mem_nav_pos,entry_values.operande_dec_str,entry_values.operand_base) ;
	break ;
      
      case 16 :
	sprintf(msg_nav_decr_get_memory_item,"Memory item [%d] -> %s [base %d]",memory_management.mem_nav_pos,entry_values.operande_hex_str,entry_values.operand_base) ;
	break ; 
	
    }	
    
    msg_nav_decr_get_memory_item[127]='\0' ;
    
    gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),msg_nav_decr_get_memory_item) ;
    
    g_free(msg_nav_decr_get_memory_item) ;
    
    return ;
    
  }
  
  
    
}
      

void store_operation(GtkWidget *widget,int *saving_idx) {
    
  if (current_entry == 2) {
    
    if ( (g_strcmp0(operations.result.operande_string,"value out of range (underflow or overflow)") == 0) || (g_strcmp0(operations.result.operande_string,"Zero division error !!!") == 0 ) || is_nan_or_infinity_error_message() ) { 
      
      gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),"Saving failed: cannot store operation with error result !") ;
      
      return ;
    }
    
    if ((*saving_idx) > 1024) {
      
      gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),"Saving failed: cannot store more than 1024 operations !") ;
      
      return ;
    }
    
    register_operations(*saving_idx) ;
    
    gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),"Operation registered") ;
    
    diplay_operation_resgistering_message_dialog() ;
   
    
    (*saving_idx)++ ;
    
    saving_index=(*saving_idx) ;
    
  }
  else {
    gtk_entry_set_text(GTK_ENTRY(gui->entry_fields->upper_entry),"Saving failed: Can store only entire operations ! Use the memory function (MEM ADD) to store an single value.") ;
  }
  
  return ;
  
}

void diplay_operation_resgistering_message_dialog(void) {
  GtkWidget *message_registering_dialog = gtk_message_dialog_new(GTK_WINDOW(gui->main_window),0,GTK_MESSAGE_INFO,GTK_BUTTONS_NONE,"Operation registered");
  
  
  g_timeout_add(1250, (GSourceFunc)destroy_register_message,message_registering_dialog) ;
  
  gtk_dialog_run(GTK_DIALOG(message_registering_dialog)) ;
  
  return ;
}

gboolean destroy_register_message(GtkWidget *widget) {
  gtk_widget_destroy(widget) ;
  
  return FALSE ;
}

void revert_result(GtkButton *button, Entry_fields *entry_fields) {
  
  if ( is_nan_or_infinity_error_message() ) {
    return ;
  }
  
  revert_result_values() ;
  reset_computing(NULL,entry_fields) ;
  
  
  switch (operations.current_base) {
      case 2 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_1_entry),entry_values.operande_bin_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),entry_values.operande_bin_str) ;
        break ;
      case 8 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_1_entry),entry_values.operande_oct_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),entry_values.operande_oct_str) ;
        break ;	 
      case 10 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_1_entry),entry_values.operande_dec_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),entry_values.operande_dec_str) ;
        break ;
      case 16 :
        gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_1_entry),entry_values.operande_hex_str) ;
	gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),entry_values.operande_hex_str) ;
        break ;
    }
  
  
  return ;
}  
  
  
  

void reset_computing(GtkButton *button,Entry_fields *entry_fields) {
  reset_calculator() ;
  
  gtk_button_set_label(GTK_BUTTON(gui->operand_sign->operand_2_sign_button)," < ") ; 
  gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_1_entry), "") ;
  gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_2_entry), "") ;
  gtk_entry_set_text(GTK_ENTRY(entry_fields->result_entry)   , "") ;
  gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry)    , "") ;
  
  current_entry = 0 ;
  
  return ;
}

void erasing(GtkButton *button,Entry_fields *entry_fields) {
  
  if ( is_nan_or_infinity_error_message() ) {
    return ;
  }
  
  if ( (current_entry == 0) && (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(entry_fields->operand_1_entry)),"") != 0) ) {
    unget_entry(entry_fields->operand_1_entry,1) ;
  }
  
  else if ( (current_entry == 1) && (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(entry_fields->operand_2_entry)),"") != 0) ) {
    unget_entry(entry_fields->operand_2_entry,1) ;
  }
  
  return ;
}

void delete(GtkButton *button,Entry_fields *entry_fields) {
  
  if ( current_entry == 0 ) {
    gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_1_entry), "") ;
    gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),     "") ;
  }
  
  else if ( current_entry == 1 ) {
    gtk_entry_set_text(GTK_ENTRY(entry_fields->operand_2_entry), "") ;
    gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),     "") ;
  }
  /* Non sense to delete result and view a bug that this operation is the cause of.
  else if ( current_entry == 2 ) {
    gtk_entry_set_text(GTK_ENTRY(entry_fields->result_entry), "") ;
    gtk_entry_set_text(GTK_ENTRY(entry_fields->upper_entry),  "") ;
    reset_result() ;
    current_entry=1 ;
    
  }
  */
  return ;
}
  
void unget_entry(GtkWidget *entry,guint8 offset) {
  gchar *entry_content=g_malloc0(128) ;
  
  g_stpcpy(entry_content, gtk_entry_get_text(GTK_ENTRY(entry)) ) ;
  entry_content[strlen(entry_content)-offset]='\0' ;
  gtk_entry_set_text(GTK_ENTRY(entry),entry_content) ;
  
  g_free(entry_content) ;
  
  return ;
}
  
  
gboolean check_entry_max_buf_size(char *input) {
  exchange_comma_and_float_point(input) ;
  
  
  if (is_string_float(input) ) {
       
    char *ptr_float_part ;
    
    char *input_copy=g_malloc0(128) ;
    
    g_stpcpy(input_copy,input) ;
    
    ptr_float_part=strchr(input_copy,'.') ;
    
    *ptr_float_part='\0' ;
    
    ptr_float_part=strchr(input,'.') ;
    
    ptr_float_part++ ;
    
    switch (operations.current_base) {
      
      case 2  :
	
	
	if ( ( (int) strlen(ptr_float_part) + (int) strlen(input_copy) ) > 63 ) {
	  
	  
	  if (current_entry == 0) {
	    unget_entry(gui->entry_fields->operand_1_entry,0) ;
	    g_free(input_copy) ;
	    return TRUE ;
	  }
	  else if (current_entry == 1) {
	    unget_entry(gui->entry_fields->operand_2_entry,0) ;
	    g_free(input_copy) ;
	    return TRUE ;
	  }
	  
	  g_free(input_copy) ;
	}
	
	break ;
	
      case 8  :
	
	if ( ( (int) strlen(ptr_float_part) + (int) strlen(input_copy) ) > 21 ) {
	  if (current_entry == 0) {
	    unget_entry(gui->entry_fields->operand_1_entry,0) ;
	    g_free(input_copy) ;
	    return TRUE ;
	  }
	  else if (current_entry == 1) {
	    unget_entry(gui->entry_fields->operand_2_entry,0) ;
	    g_free(input_copy) ;
	    return TRUE ;
	  }
	  
	  g_free(input_copy) ;
	} 
        
        break ;
      
      case 10 :
    
	if ( ( (int) strlen(ptr_float_part) + (int) strlen(input_copy) ) > 19 ) {
	  
	  if (current_entry == 0) {
	    unget_entry(gui->entry_fields->operand_1_entry,0) ;
	    g_free(input_copy) ;
	    return TRUE ;
	  }
	  else if (current_entry == 1) {
	    unget_entry(gui->entry_fields->operand_2_entry,0) ;
	    g_free(input_copy) ;
	    return TRUE ;
	  }
	  
	  g_free(input_copy) ;
	}
	
	break ;
	
      case 16  :
	
	if ( ( (int) strlen(ptr_float_part) + (int) strlen(input_copy) ) > 16 ) {
	  if (current_entry == 0) {
	    unget_entry(gui->entry_fields->operand_1_entry,0) ;
	    g_free(input_copy) ;
	    return TRUE ;
	  }
	  else if (current_entry == 1) {
	    unget_entry(gui->entry_fields->operand_2_entry,0) ;
	    g_free(input_copy) ;
	    return TRUE ;
	  }
	  
	  g_free(input_copy) ;
	}
	
	break ;
    

    }
  }
  
  else {
    if (g_ascii_strtoll(input,NULL,operations.current_base) ==  G_MAXINT64 || g_ascii_strtoll(input,NULL,operations.current_base) ==  G_MININT64) {
	if (current_entry == 0) {
	  unget_entry(gui->entry_fields->operand_1_entry,0) ;
	  return TRUE ;
	}
	else if (current_entry == 1) {
	  unget_entry(gui->entry_fields->operand_2_entry,0) ;
	  return TRUE ;
	}
	
      }
  }
  return FALSE ;
}  
  
gboolean is_entry_empty(const char *input) {
  if ( g_strcmp0(input,"") == 0 ) {
    return TRUE ;
  }
  else if  ( (int) strlen(input) == 1 && input[0] == '-') {
    return TRUE ;
  }
  
  return FALSE ;
}
  
gboolean is_nan_or_infinity_error_message(void) {
  if (current_entry == 0 && ( g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_1_entry)),"Conversion result NaN (Not A Number) value error.") == 0 || g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_1_entry)),"Conversion result Infinity value error.") == 0 ) )  {
      
    return TRUE ;
  }
  else if (current_entry == 1 && ( g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_2_entry)),"Conversion result NaN (Not A Number) value error.") == 0 || g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->operand_2_entry)),"Conversion result Infinity value error.") == 0 ) ) {
    return TRUE ;
  }
  else if (current_entry == 2 && ( g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->result_entry)),"Conversion result NaN (Not A Number) value error.") == 0 || g_strcmp0(gtk_entry_get_text(GTK_ENTRY(gui->entry_fields->result_entry)),"Conversion result Infinity value error.") == 0 ) ) {
    return TRUE ;
  }
  
  return FALSE ;
  
}

void clean_up(void) {
  
  g_slice_free(Menu,gui->menu)  ;
  
  g_slice_free(Entry_fields,gui->entry_fields)  ;
  
  g_slice_free(Operand_sign,gui->operand_sign) ;
  
  g_slice_free(Button_set,gui->button_set) ;
  
  g_slice_free(Operators,gui->operators) ;
  
  g_slice_free(GUI,gui) ;
  
  g_slice_free(Saving_output_format,operand_output_format) ;
  
  g_slice_free(Saving_HTML_output_settings,html_settings_gui) ;
  
  
  free(operations.operande_1.operande_string) ;

  free(operations.operande_1.operande_bin_str) ;
  free(operations.operande_1.operande_oct_str) ;
  free(operations.operande_1.operande_hex_str) ;
  free(operations.operande_1.operande_dec_str) ;
  

  free(operations.operande_2.operande_string) ;
  
  free(operations.operande_2.operande_bin_str) ;
  free(operations.operande_2.operande_oct_str) ;
  free(operations.operande_2.operande_hex_str) ;
  free(operations.operande_2.operande_dec_str) ; 

  
  free(operations.result.operande_string) ;
  
  free(operations.result.operande_bin_str) ;
  free(operations.result.operande_oct_str) ;
  free(operations.result.operande_hex_str) ;
  free(operations.result.operande_dec_str) ; 
  
  
  
  free(entry_values.operande_string) ;

  free(entry_values.operande_bin_str) ;
  free(entry_values.operande_oct_str) ;
  free(entry_values.operande_hex_str) ;
  free(entry_values.operande_dec_str) ;
  
  
  free(saving_settings.title) ;
  free(saving_settings.filepath) ;
  
  
  
  free(html_settings.bg_color) ;
  free(html_settings.fg_color) ;
  free(html_settings.border_color) ;
  free(html_settings.fontname) ;
  free(html_settings.border_style) ;
  free(html_settings.border_type) ;
  
  
  int item_index = memory_management.mem_counter ;
  
  while (item_index > 0) {
    free(memory[item_index].memory_item.operande_bin_str) ;
    free(memory[item_index].memory_item.operande_oct_str) ;
    free(memory[item_index].memory_item.operande_dec_str) ;
    free(memory[item_index].memory_item.operande_hex_str) ;
    
    item_index-- ;
  }
  
      
  while (saving_index > 0) {
    
    free(save_operation[item_index].operande_1.operande_bin_str) ;
    free(save_operation[item_index].operande_1.operande_oct_str) ;
    free(save_operation[item_index].operande_1.operande_dec_str) ;
    free(save_operation[item_index].operande_1.operande_hex_str) ; 
    
    free(save_operation[item_index].operande_2.operande_bin_str) ;
    free(save_operation[item_index].operande_2.operande_oct_str) ;
    free(save_operation[item_index].operande_2.operande_dec_str) ;
    free(save_operation[item_index].operande_2.operande_hex_str) ;
    
    free(save_operation[item_index].result.operande_bin_str) ;
    free(save_operation[item_index].result.operande_oct_str) ;
    free(save_operation[item_index].result.operande_dec_str) ;
    free(save_operation[item_index].result.operande_hex_str) ;
    
    saving_index-- ;
  }
  
  return ;
}


void cannot_export_success_message_dialog(const char *filename) ;

void export_dialog(GtkWidget *widget, int *saving_idx) ;

void init_saving_settings(void) ;
void init_html_settings(void)   ;

void reset_saving_settings(void) ;
void reset_html_settings(void)   ;

gboolean set_saving_file_format(GtkWidget *widget,int filetype) ;

gboolean toggle_saving_default_operand_format(GtkWidget *widget,gpointer *data) ;

gboolean toggle_saving_setting_bases_all_operand_16(GtkWidget *widget,int *clean) ;
gboolean toggle_saving_setting_bases_all_operand_8(GtkWidget *widget,int *clean) ;
gboolean toggle_saving_setting_bases_all_operand_2(GtkWidget *widget,int *clean) ;
gboolean toggle_saving_setting_bases_all_operand_10(GtkWidget *widget,int *clean) ;

gboolean saving_settings_set_operand_1_base(GtkWidget *widget,int base) ;
gboolean saving_settings_set_operand_2_base(GtkWidget *widget,int base) ;
gboolean saving_settings_set_result_base(GtkWidget *widget,int base) ;


gboolean saving_display_title(GtkWidget *widget,gpointer *data) ;
gboolean saving_display_bases(GtkWidget *widget,gpointer *data) ;
gboolean saving_settings_use_notation(GtkWidget *widget,_Bool use_raw_notation) ;
gboolean saving_settings_actions(GtkWidget *widget,int *item_idx) ;
gboolean save_as_file(GtkButton *button,gpointer *data) ;

void cannot_export_no_data_message_dialog(void) ;

void set_html_colors_settings(void) ;

void saving_get_html_settings(GtkWidget *html_settings_dialog) ;


void saving_settings_check_filetype(char *filename) ;

void saving_settings_update_filetype(char *filename) ;


gboolean get_title(GtkWidget *widget) ;


void saving_settings_set_hex_fields_sensitive(gboolean set_active) ;
void saving_settings_set_hex_fields_insensitive(gboolean set_active)  ;

void saving_settings_set_oct_fields_sensitive(gboolean set_active) ;
void saving_settings_set_oct_fields_insensitive(gboolean set_active)  ;

void saving_settings_set_bin_fields_sensitive(gboolean set_active) ;
void saving_settings_set_bin_fields_insensitive(gboolean set_active)  ;

void saving_settings_set_dec_fields_sensitive(gboolean set_active) ;
void saving_settings_set_dec_fields_insensitive(gboolean set_active)  ;


void switch_saving_hex_all_operand_active(void) ;
void switch_saving_oct_all_operand_active(void) ;
void switch_saving_bin_all_operand_active(void) ;
void switch_saving_dec_all_operand_active(void) ;  
  

void saving_settings_clean_set_all_operand_on_base_16(void) ;
void saving_settings_clean_set_all_operand_on_base_8(void) ;
void saving_settings_clean_set_all_operand_on_base_2(void) ;
void saving_settings_clean_set_all_operand_on_base_10(void) ;


void export_dialog(GtkWidget *widget, int *saving_idx) {
  
  if (*saving_idx == 0) {
    cannot_export_no_data_message_dialog() ;
    return ;
  }
  
  
  
  
  GtkWidget *vbox,*content_area;
  
  operand_output_format->save_settings_dialog = gtk_dialog_new() ;
  
  gtk_window_set_title(GTK_WINDOW(operand_output_format->save_settings_dialog),"Export settings");
  
  gtk_container_set_border_width(GTK_CONTAINER(operand_output_format->save_settings_dialog),12) ;
  
  content_area = gtk_dialog_get_content_area(GTK_DIALOG (operand_output_format->save_settings_dialog));
  
  vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,FALSE) ;
  
  /** Begin "Main settings" part configuration. **/ 
  
  GtkWidget *main_settings_frame = gtk_frame_new("  Main settings.  ") ;
  
  GtkWidget *main_settings_grid  = gtk_grid_new() ;
  
  gtk_grid_set_row_spacing(GTK_GRID(main_settings_grid),8);
  
  gtk_grid_set_column_spacing(GTK_GRID(main_settings_grid),16);
  
  g_object_set(G_OBJECT(main_settings_grid),"margin",8,NULL) ;
  
  GtkWidget *main_settings_title_hbox   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,FALSE) ;
  
  GtkWidget *main_settings_title_button = gtk_button_new() ;
  
  
  GtkWidget *main_settings_title_image = gtk_image_new_from_icon_name("gtk-edit",GTK_ICON_SIZE_BUTTON);
  
  GtkWidget *main_settings_title_label = gtk_label_new("Set title") ;
  
  gtk_box_pack_start(GTK_BOX(main_settings_title_hbox),main_settings_title_image,FALSE,FALSE,8) ;
  
  gtk_box_pack_start(GTK_BOX(main_settings_title_hbox),main_settings_title_label,FALSE,FALSE,0) ;
  
  gtk_button_set_relief(GTK_BUTTON(main_settings_title_button), GTK_RELIEF_NONE);
  
  gtk_container_add(GTK_CONTAINER(main_settings_title_button),main_settings_title_hbox) ;
  
  
  operand_output_format->main_settings_title_entry  = gtk_entry_new() ;
  
  gtk_entry_set_alignment(GTK_ENTRY(operand_output_format->main_settings_title_entry),0.5);
  
  gtk_entry_set_text(GTK_ENTRY(operand_output_format->main_settings_title_entry),saving_settings.title) ;
  
  gtk_entry_set_width_chars(GTK_ENTRY(operand_output_format->main_settings_title_entry),39) ;
  
  GtkWidget *main_settings_file_hbox   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,FALSE) ;
  
  
  
  GtkWidget *main_settings_file_button = gtk_button_new() ;
  
  GtkWidget *main_settings_file_image  = gtk_image_new_from_icon_name("document-save-as",GTK_ICON_SIZE_BUTTON);
  
  GtkWidget *main_settings_file_label  = gtk_label_new("Export as") ;
  
  gtk_box_pack_start(GTK_BOX(main_settings_file_hbox),main_settings_file_image,FALSE,FALSE,8) ;
  
  gtk_box_pack_start(GTK_BOX(main_settings_file_hbox),main_settings_file_label,FALSE,FALSE,0) ;
  
  gtk_container_add(GTK_CONTAINER(main_settings_file_button),main_settings_file_hbox) ;
  
  gtk_button_set_relief(GTK_BUTTON(main_settings_file_button), GTK_RELIEF_NONE);
  
  g_signal_connect(G_OBJECT(main_settings_file_button),"clicked",G_CALLBACK(save_as_file),NULL) ;
  
  operand_output_format->main_settings_file_entry  = gtk_entry_new() ;
  
  gtk_entry_set_alignment(GTK_ENTRY(operand_output_format->main_settings_file_entry),0.5);
  
  gtk_entry_set_width_chars(GTK_ENTRY(operand_output_format->main_settings_file_entry),39) ;
  
  g_object_set(G_OBJECT(operand_output_format->main_settings_file_entry),"editable",FALSE,NULL) ;
  
  gtk_grid_attach(GTK_GRID(main_settings_grid),main_settings_title_button ,0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(main_settings_grid),operand_output_format->main_settings_title_entry ,1, 0, 1, 1);
  
  gtk_grid_attach(GTK_GRID(main_settings_grid),main_settings_file_button ,0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(main_settings_grid),operand_output_format->main_settings_file_entry  ,1, 1, 1, 1);
  
  gtk_container_add(GTK_CONTAINER(main_settings_frame),main_settings_grid) ;
  
  /** End "Main settings" part configuration. **/ 
  
  
  
  /** Begin "File format" part configuration. **/ 
  
  GtkWidget *file_format_frame = gtk_frame_new("  File format.  ") ;
  
  GtkWidget *file_format_grid  = gtk_grid_new() ;
  
  gtk_grid_set_row_spacing(GTK_GRID(file_format_grid),8);
  
  gtk_grid_set_column_spacing(GTK_GRID(file_format_grid),16);
  
  gtk_grid_set_column_homogeneous(GTK_GRID(file_format_grid),TRUE);
  
  g_object_set(G_OBJECT(file_format_grid),"margin",8,NULL) ;
  
  operand_output_format->file_format_txt_radiobutton = gtk_radio_button_new_with_label(NULL,"text file");
  
  
  
  operand_output_format->file_format_csv_radiobutton = gtk_radio_button_new_with_label(NULL,"csv file");
  
  
  
  gtk_radio_button_join_group(GTK_RADIO_BUTTON(operand_output_format->file_format_csv_radiobutton), GTK_RADIO_BUTTON(operand_output_format->file_format_txt_radiobutton));
  
  
  operand_output_format->file_format_html_radiobutton = gtk_radio_button_new_with_label(NULL,"html file");
  
  gtk_radio_button_join_group(GTK_RADIO_BUTTON(operand_output_format->file_format_html_radiobutton), GTK_RADIO_BUTTON(operand_output_format->file_format_csv_radiobutton));
  
  g_object_set(G_OBJECT(operand_output_format->file_format_txt_radiobutton),  "margin-left", 48, NULL) ;
  g_object_set(G_OBJECT(operand_output_format->file_format_csv_radiobutton),  "margin-left", 48, NULL) ;
  g_object_set(G_OBJECT(operand_output_format->file_format_html_radiobutton), "margin-left", 48, NULL) ;
  
  gtk_grid_attach(GTK_GRID(file_format_grid),operand_output_format->file_format_txt_radiobutton  ,0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(file_format_grid),operand_output_format->file_format_csv_radiobutton  ,1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(file_format_grid),operand_output_format->file_format_html_radiobutton ,2, 0, 1, 1);
  
  if (saving_settings.file_format == 1) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_txt_radiobutton),TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_csv_radiobutton),FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_html_radiobutton),FALSE);
  }
  else if (saving_settings.file_format == 2) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_txt_radiobutton),FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_csv_radiobutton),TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_html_radiobutton),FALSE);
  }
  else if (saving_settings.file_format == 3) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_txt_radiobutton),FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_csv_radiobutton),FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_html_radiobutton),TRUE);
  }
  
  g_signal_connect(G_OBJECT(operand_output_format->file_format_txt_radiobutton),  "clicked", G_CALLBACK(set_saving_file_format), (int *) 1) ;
  g_signal_connect(G_OBJECT(operand_output_format->file_format_csv_radiobutton),  "clicked", G_CALLBACK(set_saving_file_format), (int *) 2) ;
  g_signal_connect(G_OBJECT(operand_output_format->file_format_html_radiobutton), "clicked", G_CALLBACK(set_saving_file_format), (int *) 3) ;
  
  gtk_container_add(GTK_CONTAINER(file_format_frame),file_format_grid) ;
  
  /** End "Main settings" part configuration. **/ 
  
  
  
  
  /** Begin "Ouput format" part configuration. **/ 
  
  GtkWidget *output_format_frame = gtk_frame_new("  Output format.  ") ;
  
  GtkWidget *output_format_grid  = gtk_grid_new() ;
  
  gtk_grid_set_row_spacing(GTK_GRID(output_format_grid),8);
  
  gtk_grid_set_column_spacing(GTK_GRID(output_format_grid),16);
  
  gtk_grid_set_column_homogeneous(GTK_GRID(output_format_grid),TRUE);
  
  g_object_set(G_OBJECT(output_format_grid),"margin",8,NULL) ;
  
  
  GtkWidget *label_format_header = gtk_label_new("Format") ;
  
  GtkWidget *label_op1_header = gtk_label_new("Op1") ;
  
  GtkWidget *label_op2_header = gtk_label_new("Op2") ;
  
  GtkWidget *label_res_header = gtk_label_new("Res") ;
  
  GtkWidget *label_all_header = gtk_label_new("All") ;
  
  
  
  GtkWidget *label_hex_format = gtk_label_new("Hex") ;
  
  operand_output_format->radio_hex_op1_format = gtk_radio_button_new(NULL) ;
  
  operand_output_format->radio_hex_op2_format = gtk_radio_button_new(NULL) ;
  
  operand_output_format->radio_hex_res_format = gtk_radio_button_new(NULL) ;
  
  operand_output_format->check_hex_all_format = gtk_check_button_new() ;
  
  
  
  g_object_set(G_OBJECT(operand_output_format->radio_hex_op1_format),"margin-left",30,NULL) ;
  g_object_set(G_OBJECT(operand_output_format->radio_hex_op2_format),"margin-left",30,NULL) ;
  g_object_set(G_OBJECT(operand_output_format->radio_hex_res_format),"margin-left",30,NULL) ;
  g_object_set(G_OBJECT(operand_output_format->check_hex_all_format),"margin-left",30,NULL) ;
  
  
  GtkWidget *label_oct_format = gtk_label_new("Oct") ;
  
  operand_output_format->radio_oct_op1_format = gtk_radio_button_new(NULL) ;
  
  
  
  operand_output_format->radio_oct_op2_format = gtk_radio_button_new(NULL) ;
  
  
  
  operand_output_format->radio_oct_res_format = gtk_radio_button_new(NULL) ;
  
  
  
  operand_output_format->check_oct_all_format = gtk_check_button_new() ;
  
  g_object_set(G_OBJECT(operand_output_format->radio_oct_op1_format),"margin-left",30,NULL) ;
  g_object_set(G_OBJECT(operand_output_format->radio_oct_op2_format),"margin-left",30,NULL) ;
  g_object_set(G_OBJECT(operand_output_format->radio_oct_res_format),"margin-left",30,NULL) ;
  g_object_set(G_OBJECT(operand_output_format->check_oct_all_format),"margin-left",30,NULL) ;
  
  
  
  GtkWidget *label_bin_format = gtk_label_new("Bin") ;
  
  operand_output_format->radio_bin_op1_format = gtk_radio_button_new(NULL) ;
  
  operand_output_format->radio_bin_op2_format = gtk_radio_button_new(NULL) ;
  
  operand_output_format->radio_bin_res_format = gtk_radio_button_new(NULL) ;
 
  operand_output_format->check_bin_all_format = gtk_check_button_new() ;
  
  
  g_object_set(G_OBJECT(operand_output_format->radio_bin_op1_format),"margin-left",30,NULL) ;
  g_object_set(G_OBJECT(operand_output_format->radio_bin_op2_format),"margin-left",30,NULL) ;
  g_object_set(G_OBJECT(operand_output_format->radio_bin_res_format),"margin-left",30,NULL) ;
  g_object_set(G_OBJECT(operand_output_format->check_bin_all_format),"margin-left",30,NULL) ;
 
  
  
  GtkWidget *label_dec_format = gtk_label_new("Dec") ;
  
  operand_output_format->radio_dec_op1_format = gtk_radio_button_new(NULL) ;
  
  operand_output_format->radio_dec_op2_format = gtk_radio_button_new(NULL) ;
  
  operand_output_format->radio_dec_res_format = gtk_radio_button_new(NULL) ;
  
  operand_output_format->check_dec_all_format = gtk_check_button_new() ;
  
  
  g_object_set(G_OBJECT(operand_output_format->radio_dec_op1_format),"margin-left",30,NULL) ;
  g_object_set(G_OBJECT(operand_output_format->radio_dec_op2_format),"margin-left",30,NULL) ;
  g_object_set(G_OBJECT(operand_output_format->radio_dec_res_format),"margin-left",30,NULL) ;
  g_object_set(G_OBJECT(operand_output_format->check_dec_all_format),"margin-left",30,NULL) ;
  
  
  
  gtk_radio_button_join_group(GTK_RADIO_BUTTON(operand_output_format->radio_oct_op1_format), GTK_RADIO_BUTTON(operand_output_format->radio_hex_op1_format));
  gtk_radio_button_join_group(GTK_RADIO_BUTTON(operand_output_format->radio_bin_op1_format), GTK_RADIO_BUTTON(operand_output_format->radio_oct_op1_format));
  gtk_radio_button_join_group(GTK_RADIO_BUTTON(operand_output_format->radio_dec_op1_format), GTK_RADIO_BUTTON(operand_output_format->radio_bin_op1_format));
  
  gtk_radio_button_join_group(GTK_RADIO_BUTTON(operand_output_format->radio_oct_op2_format), GTK_RADIO_BUTTON(operand_output_format->radio_hex_op2_format));
  gtk_radio_button_join_group(GTK_RADIO_BUTTON(operand_output_format->radio_bin_op2_format), GTK_RADIO_BUTTON(operand_output_format->radio_oct_op2_format));
  gtk_radio_button_join_group(GTK_RADIO_BUTTON(operand_output_format->radio_dec_op2_format), GTK_RADIO_BUTTON(operand_output_format->radio_bin_op2_format));
  
  gtk_radio_button_join_group(GTK_RADIO_BUTTON(operand_output_format->radio_oct_res_format), GTK_RADIO_BUTTON(operand_output_format->radio_hex_res_format));
  gtk_radio_button_join_group(GTK_RADIO_BUTTON(operand_output_format->radio_bin_res_format), GTK_RADIO_BUTTON(operand_output_format->radio_oct_res_format));
  gtk_radio_button_join_group(GTK_RADIO_BUTTON(operand_output_format->radio_dec_res_format), GTK_RADIO_BUTTON(operand_output_format->radio_bin_res_format));
  
  
  GtkWidget *label_as_registered_format = gtk_label_new("") ;
  
  gtk_label_set_markup(GTK_LABEL(label_as_registered_format),"<big>Use the same base as registered for all operand.</big>");
  
  operand_output_format->check_as_registered_format = gtk_check_button_new() ;
  
  g_object_set(G_OBJECT(operand_output_format->check_as_registered_format),"margin-left",30,NULL) ;
  
  
  
  if (saving_settings.use_default_format) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_as_registered_format),TRUE) ;
    
    gtk_widget_set_sensitive(operand_output_format->radio_hex_op1_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_hex_op2_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_hex_res_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->check_hex_all_format,FALSE) ;
    
    gtk_widget_set_sensitive(operand_output_format->radio_oct_op1_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_oct_op2_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_oct_res_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->check_oct_all_format,FALSE) ;
    
    gtk_widget_set_sensitive(operand_output_format->radio_bin_op1_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_bin_op2_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_bin_res_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->check_bin_all_format,FALSE) ;
    
    gtk_widget_set_sensitive(operand_output_format->radio_dec_op1_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_dec_op2_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_dec_res_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->check_dec_all_format,FALSE) ;
  }
  else {
    ;
  }
  
  static int *clean = 0 ;
  
  g_signal_connect(G_OBJECT(operand_output_format->radio_hex_op1_format),"clicked",G_CALLBACK(saving_settings_set_operand_1_base), (int *) 16) ;
  g_signal_connect(G_OBJECT(operand_output_format->radio_hex_op2_format),"clicked",G_CALLBACK(saving_settings_set_operand_2_base), (int *) 16) ;
  g_signal_connect(G_OBJECT(operand_output_format->radio_hex_res_format),"clicked",G_CALLBACK(saving_settings_set_result_base)   , (int *) 16) ;
  
  g_signal_connect(G_OBJECT(operand_output_format->radio_oct_op1_format),"clicked",G_CALLBACK(saving_settings_set_operand_1_base), (int *) 8) ;
  g_signal_connect(G_OBJECT(operand_output_format->radio_oct_op2_format),"clicked",G_CALLBACK(saving_settings_set_operand_2_base), (int *) 8) ;
  g_signal_connect(G_OBJECT(operand_output_format->radio_oct_res_format),"clicked",G_CALLBACK(saving_settings_set_result_base)   , (int *) 8) ;
  
  g_signal_connect(G_OBJECT(operand_output_format->radio_bin_op1_format),"clicked",G_CALLBACK(saving_settings_set_operand_1_base), (int *) 2) ;
  g_signal_connect(G_OBJECT(operand_output_format->radio_bin_op2_format),"clicked",G_CALLBACK(saving_settings_set_operand_2_base), (int *) 2) ;
  g_signal_connect(G_OBJECT(operand_output_format->radio_bin_res_format),"clicked",G_CALLBACK(saving_settings_set_result_base)   , (int *) 2) ;
  
  g_signal_connect(G_OBJECT(operand_output_format->radio_dec_op1_format),"clicked",G_CALLBACK(saving_settings_set_operand_1_base), (int *) 10) ;
  g_signal_connect(G_OBJECT(operand_output_format->radio_dec_op2_format),"clicked",G_CALLBACK(saving_settings_set_operand_2_base), (int *) 10) ;
  g_signal_connect(G_OBJECT(operand_output_format->radio_dec_res_format),"clicked",G_CALLBACK(saving_settings_set_result_base)   , (int *) 10) ;
  
  
  g_signal_connect(G_OBJECT(operand_output_format->check_as_registered_format),"clicked",G_CALLBACK(toggle_saving_default_operand_format),NULL) ;
  
  g_signal_connect(G_OBJECT(operand_output_format->check_bin_all_format),"clicked",G_CALLBACK(toggle_saving_setting_bases_all_operand_2), &clean) ;  
  g_signal_connect(G_OBJECT(operand_output_format->check_oct_all_format),"clicked",G_CALLBACK(toggle_saving_setting_bases_all_operand_8), &clean) ; 
  g_signal_connect(G_OBJECT(operand_output_format->check_dec_all_format),"clicked",G_CALLBACK(toggle_saving_setting_bases_all_operand_10), &clean) ; 
  g_signal_connect(G_OBJECT(operand_output_format->check_hex_all_format),"clicked",G_CALLBACK(toggle_saving_setting_bases_all_operand_16), &clean) ;   
    
  
  gtk_grid_attach(GTK_GRID(output_format_grid),label_format_header     ,0, 0, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),label_op1_header        ,1, 0, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),label_op2_header        ,2, 0, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),label_res_header        ,3, 0, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),label_all_header        ,4, 0, 1, 1) ;
  
  gtk_grid_attach(GTK_GRID(output_format_grid),label_hex_format        ,0, 1, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->radio_hex_op1_format    ,1, 1, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->radio_hex_op2_format    ,2, 1, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->radio_hex_res_format    ,3, 1, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->check_hex_all_format    ,4, 1, 1, 1) ;
  
  gtk_grid_attach(GTK_GRID(output_format_grid),label_oct_format        ,0, 2, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->radio_oct_op1_format    ,1, 2, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->radio_oct_op2_format    ,2, 2, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->radio_oct_res_format    ,3, 2, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->check_oct_all_format    ,4, 2, 1, 1) ;
  
  gtk_grid_attach(GTK_GRID(output_format_grid),label_bin_format        ,0, 3, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->radio_bin_op1_format    ,1, 3, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->radio_bin_op2_format    ,2, 3, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->radio_bin_res_format    ,3, 3, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->check_bin_all_format    ,4, 3, 1, 1) ;
  
  gtk_grid_attach(GTK_GRID(output_format_grid),label_dec_format        ,0, 4, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->radio_dec_op1_format    ,1, 4, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->radio_dec_op2_format    ,2, 4, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->radio_dec_res_format    ,3, 4, 1, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->check_dec_all_format    ,4, 4, 1, 1) ;
  
  gtk_grid_attach(GTK_GRID(output_format_grid),label_as_registered_format    ,0, 5, 4, 1) ;
  gtk_grid_attach(GTK_GRID(output_format_grid),operand_output_format->check_as_registered_format    ,4, 5, 1, 1) ;
  
  gtk_container_add(GTK_CONTAINER(output_format_frame),output_format_grid) ;
  
  /** End "Ouput format" part configuration. **/ 
  
  
  
  
  /** Begin "Options" part configuration. **/ 
  
  GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,FALSE) ;
  
  gtk_box_set_spacing(GTK_BOX(hbox),16);
  
  
  
  GtkWidget *display_options_frame = gtk_frame_new("  Display options.  ") ;
  
  GtkWidget *display_options_grid  = gtk_grid_new() ;
  
  gtk_grid_set_row_spacing(GTK_GRID(display_options_grid),8);
  
  gtk_grid_set_column_spacing(GTK_GRID(display_options_grid),16);
  
  
  g_object_set(G_OBJECT(display_options_grid),"margin",8,NULL) ;
  
  
  GtkWidget *display_options_display_title_label = gtk_label_new("Display the title in the file. ") ;
  
  operand_output_format->display_options_display_title_check = gtk_check_button_new() ;
  
  GtkWidget *display_options_display_base_label  = gtk_label_new("Include bases prefix.          ") ;
  
  operand_output_format->display_options_display_base_check  = gtk_check_button_new() ;
  
  g_signal_connect(G_OBJECT(operand_output_format->display_options_display_title_check),"clicked",G_CALLBACK(saving_display_title),NULL) ;
  g_signal_connect(G_OBJECT(operand_output_format->display_options_display_base_check),"clicked",G_CALLBACK(saving_display_bases),NULL) ;
  
  gtk_grid_attach(GTK_GRID(display_options_grid),display_options_display_title_label     ,0, 0, 1, 1) ;
  gtk_grid_attach(GTK_GRID(display_options_grid),operand_output_format->display_options_display_title_check     ,1, 0, 1, 1) ;
  gtk_grid_attach(GTK_GRID(display_options_grid),display_options_display_base_label      ,0, 1, 1, 1) ;
  gtk_grid_attach(GTK_GRID(display_options_grid),operand_output_format->display_options_display_base_check      ,1, 1, 1, 1) ;
  
  if (saving_settings.display_title) {
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->display_options_display_title_check),TRUE) ;
  }
  else {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->display_options_display_title_check),FALSE) ;
  }
  
  if (saving_settings.display_bases) {
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->display_options_display_base_check),TRUE) ;
  }
  else {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->display_options_display_base_check),FALSE) ;
  }
  
  gtk_container_add(GTK_CONTAINER(display_options_frame),display_options_grid) ;
  
  gtk_widget_set_hexpand(display_options_frame, TRUE);
  
  
  
  GtkWidget *notation_frame = gtk_frame_new("  Notation.  ") ;
  
  GtkWidget *notation_grid  = gtk_grid_new() ;
  
  gtk_grid_set_row_spacing(GTK_GRID(notation_grid),8);
  
  gtk_grid_set_column_spacing(GTK_GRID(notation_grid),16);
  
  
  g_object_set(G_OBJECT(notation_grid),"margin",8,NULL) ;
  
  
  GtkWidget *notation_enginer_label = gtk_label_new(  "Use enginer notation.         ") ;
  
  operand_output_format->notation_enginer_radio = gtk_radio_button_new(NULL) ;
  
  GtkWidget *notation_numbers_label  = gtk_label_new( "Use raw numbers notation.") ;
  
  operand_output_format->notation_numbers_radio  = gtk_radio_button_new(NULL) ;
  
  gtk_radio_button_join_group(GTK_RADIO_BUTTON(operand_output_format->notation_numbers_radio), GTK_RADIO_BUTTON(operand_output_format->notation_enginer_radio));
  
  gtk_grid_attach(GTK_GRID(notation_grid),notation_enginer_label     ,0, 0, 1, 1) ;
  gtk_grid_attach(GTK_GRID(notation_grid),operand_output_format->notation_enginer_radio     ,1, 0, 1, 1) ;
  gtk_grid_attach(GTK_GRID(notation_grid),notation_numbers_label     ,0, 1, 1, 1) ;
  gtk_grid_attach(GTK_GRID(notation_grid),operand_output_format->notation_numbers_radio     ,1, 1, 1, 1) ;
  
  if (saving_settings.use_raw_notation) {
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->notation_enginer_radio),FALSE) ;
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->notation_numbers_radio),TRUE) ;
  }
  else {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->notation_numbers_radio),TRUE) ;
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->notation_enginer_radio),FALSE) ;
  }
  
  g_signal_connect(G_OBJECT(operand_output_format->notation_enginer_radio),"clicked",G_CALLBACK(saving_settings_use_notation),(_Bool *) false) ;
  g_signal_connect(G_OBJECT(operand_output_format->notation_numbers_radio),"clicked",G_CALLBACK(saving_settings_use_notation),(_Bool *) true) ;
  
  gtk_container_add(GTK_CONTAINER(notation_frame),notation_grid) ;
 
  gtk_box_pack_start(GTK_BOX(hbox),display_options_frame,FALSE,TRUE,0) ; 
  gtk_box_pack_start(GTK_BOX(hbox),notation_frame,FALSE,TRUE,0) ; 
  
  /** End "Options" part configuration. **/ 
  
  
  /** Begin "Options" part configuration. **/ 
  
  
  GtkWidget *actions_frame = gtk_frame_new("  Actions.  ") ;
  
  GtkWidget *actions_grid  = gtk_grid_new() ;
  
  gtk_grid_set_row_spacing(GTK_GRID(actions_grid),8);
  
  gtk_grid_set_column_spacing(GTK_GRID(actions_grid),16);
  
  gtk_grid_set_column_homogeneous(GTK_GRID(actions_grid),TRUE);
  
  g_object_set(G_OBJECT(actions_grid),"margin",8,NULL) ;
  
  
  GtkWidget *cancel_button = gtk_button_new_with_label("Cancel") ;
  
  GtkWidget *reset_button = gtk_button_new_with_label("Reset") ;
  
  GtkWidget *export_button = gtk_button_new_with_label("Export") ;
  
  gtk_grid_attach(GTK_GRID(actions_grid),cancel_button     ,0, 0, 1, 1) ;
  gtk_grid_attach(GTK_GRID(actions_grid),reset_button      ,1, 0, 1, 1) ;
  gtk_grid_attach(GTK_GRID(actions_grid),export_button     ,2, 0, 1, 1) ;
  
  g_object_set_data(G_OBJECT(cancel_button),"action", "cancel") ;
  g_object_set_data(G_OBJECT(reset_button),"action", "reset") ;
  g_object_set_data(G_OBJECT(export_button),"action", "export") ;
  
  g_signal_connect(G_OBJECT(cancel_button),"clicked",G_CALLBACK(saving_settings_actions), saving_idx) ;
  g_signal_connect(G_OBJECT(reset_button),"clicked",G_CALLBACK(saving_settings_actions),  saving_idx) ;
  g_signal_connect(G_OBJECT(export_button),"clicked",G_CALLBACK(saving_settings_actions), saving_idx) ;
  
  gtk_container_add(GTK_CONTAINER(actions_frame),actions_grid) ;
  
  
   
  gtk_box_pack_start(GTK_BOX(vbox),main_settings_frame,FALSE,FALSE,8) ;
  gtk_box_pack_start(GTK_BOX(vbox),file_format_frame,FALSE,FALSE,8) ;
  gtk_box_pack_start(GTK_BOX(vbox),output_format_frame,FALSE,FALSE,8) ;
  gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,8) ;
  gtk_box_pack_start(GTK_BOX(vbox),actions_frame,FALSE,FALSE,0) ;
  
  gtk_container_add(GTK_CONTAINER(content_area),vbox) ;
  
  reset_saving_settings() ;
  
  gtk_widget_show_all(operand_output_format->save_settings_dialog) ;
  
}

void init_saving_settings(void) {
  saving_settings.title=calloc(256,sizeof(char)) ;
  saving_settings.filepath=calloc(256,sizeof(char)) ;
  saving_settings.fileset=false ;
  saving_settings.file_format=1 ; /* 1 = txt ; 2 = csv ; 3 = html ; */
  saving_settings.op1_format=10 ;
  saving_settings.op2_format=10 ;
  saving_settings.res_format=10 ;
  saving_settings.use_default_format=true ;
  saving_settings.display_title=true ;
  saving_settings.display_bases=false ;
  saving_settings.use_raw_notation=true ;
  
  strcpy(saving_settings.title,"Calc") ;
  
}

void reset_saving_settings(void) {
  memset(saving_settings.title,'\0',256) ;
  memset(saving_settings.filepath,'\0',256) ;
  saving_settings.fileset=false ;
  saving_settings.file_format=1 ; /* 1 = txt ; 2 = csv ; 3 = html ; */
  saving_settings.op1_format=10 ;
  saving_settings.op2_format=10 ;
  saving_settings.res_format=10 ;
  saving_settings.use_default_format=true ;
  saving_settings.display_title=true ;
  saving_settings.display_bases=false ;
  saving_settings.use_raw_notation=true ;
  
  strcpy(saving_settings.title,"Calc") ;
  
  gtk_entry_set_text(GTK_ENTRY(operand_output_format->main_settings_title_entry),saving_settings.title) ;
  gtk_entry_set_text(GTK_ENTRY(operand_output_format->main_settings_file_entry),"") ;
  
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_txt_radiobutton),TRUE);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_csv_radiobutton),FALSE);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_html_radiobutton),FALSE);
  
  
    
  gtk_widget_set_sensitive(operand_output_format->radio_hex_op1_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_hex_op2_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_hex_res_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->check_hex_all_format,FALSE) ;
  
  gtk_widget_set_sensitive(operand_output_format->radio_oct_op1_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_oct_op2_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_oct_res_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->check_oct_all_format,FALSE) ;
  
  gtk_widget_set_sensitive(operand_output_format->radio_bin_op1_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_bin_op2_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_bin_res_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->check_bin_all_format,FALSE) ;
  
  gtk_widget_set_sensitive(operand_output_format->radio_dec_op1_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_dec_op2_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_dec_res_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->check_dec_all_format,FALSE) ;
  
  
  
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->display_options_display_title_check),TRUE) ;  
  
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->display_options_display_base_check),FALSE) ;
  
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->notation_enginer_radio),FALSE) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->notation_numbers_radio),TRUE) ;
  
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_hex_all_format),FALSE);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_oct_all_format),FALSE);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_bin_all_format),FALSE);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_dec_all_format),FALSE);
  
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_as_registered_format),TRUE) ;
  
}

gboolean set_saving_file_format(GtkWidget *widget,int filetype) {
  if (filetype == 1 && saving_settings.file_format != 1) {
    saving_settings.file_format=1 ;
  }
  else if (filetype == 2 && saving_settings.file_format != 2) {
    saving_settings.file_format=2 ;
  }
  else if (filetype == 3 && saving_settings.file_format != 3) {
    saving_settings.file_format=3 ;
  }
  
  if (saving_settings.fileset) {
    saving_settings_update_filetype(saving_settings.filepath) ;
    gtk_entry_set_text(GTK_ENTRY(operand_output_format->main_settings_file_entry),g_filename_display_basename(saving_settings.filepath) ) ;
  }
  
  return FALSE ;
}
  
gboolean toggle_saving_default_operand_format(GtkWidget *widget,gpointer *data) {
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(operand_output_format->check_as_registered_format)) ) {
    
    gtk_widget_set_sensitive(operand_output_format->radio_hex_op1_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_hex_op2_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_hex_res_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->check_hex_all_format,FALSE) ;
    
    gtk_widget_set_sensitive(operand_output_format->radio_oct_op1_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_oct_op2_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_oct_res_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->check_oct_all_format,FALSE) ;
    
    gtk_widget_set_sensitive(operand_output_format->radio_bin_op1_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_bin_op2_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_bin_res_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->check_bin_all_format,FALSE) ;
    
    gtk_widget_set_sensitive(operand_output_format->radio_dec_op1_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_dec_op2_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->radio_dec_res_format,FALSE) ;
    gtk_widget_set_sensitive(operand_output_format->check_dec_all_format,FALSE) ;
    
    saving_settings.use_default_format=true ;
  }
  else {
      
      saving_settings.use_default_format=false ;
    
      gtk_widget_set_sensitive(operand_output_format->radio_hex_op1_format,TRUE) ;
      gtk_widget_set_sensitive(operand_output_format->radio_hex_op2_format,TRUE) ;
      gtk_widget_set_sensitive(operand_output_format->radio_hex_res_format,TRUE) ;
      gtk_widget_set_sensitive(operand_output_format->check_hex_all_format,TRUE) ;
      
      gtk_widget_set_sensitive(operand_output_format->radio_oct_op1_format,TRUE) ;
      gtk_widget_set_sensitive(operand_output_format->radio_oct_op2_format,TRUE) ;
      gtk_widget_set_sensitive(operand_output_format->radio_oct_res_format,TRUE) ;
      gtk_widget_set_sensitive(operand_output_format->check_oct_all_format,TRUE) ;
      
      gtk_widget_set_sensitive(operand_output_format->radio_bin_op1_format,TRUE) ;
      gtk_widget_set_sensitive(operand_output_format->radio_bin_op2_format,TRUE) ;
      gtk_widget_set_sensitive(operand_output_format->radio_bin_res_format,TRUE) ;
      gtk_widget_set_sensitive(operand_output_format->check_bin_all_format,TRUE) ;
      
      gtk_widget_set_sensitive(operand_output_format->radio_dec_op1_format,TRUE) ;
      gtk_widget_set_sensitive(operand_output_format->radio_dec_op2_format,TRUE) ;
      gtk_widget_set_sensitive(operand_output_format->radio_dec_res_format,TRUE) ;
      gtk_widget_set_sensitive(operand_output_format->check_dec_all_format,TRUE) ;
    
      
    if (saving_settings.op1_format == saving_settings.op2_format && saving_settings.op1_format == saving_settings.res_format && saving_settings.op2_format == saving_settings.res_format) {
            
      switch (saving_settings.op1_format) {
	case 2 : 
          saving_settings_set_bin_fields_insensitive(TRUE) ;
	  switch_saving_bin_all_operand_active() ;
	  break ;
	case 8 :
	  saving_settings_set_oct_fields_insensitive(TRUE) ;
	  switch_saving_oct_all_operand_active() ;
	  break ;
	case 10 :
	  saving_settings_set_dec_fields_insensitive(TRUE) ;
	  switch_saving_dec_all_operand_active() ;
	  break ;
	case 16 :  
	  saving_settings_set_hex_fields_insensitive(TRUE) ;
	  switch_saving_hex_all_operand_active() ;
	  break ;
      }
    }
    
    else {
      
      
      
      saving_settings_set_hex_fields_sensitive(TRUE) ;
      saving_settings_set_oct_fields_sensitive(TRUE) ;
      saving_settings_set_bin_fields_sensitive(TRUE) ;
      saving_settings_set_dec_fields_sensitive(TRUE) ;
      
      switch (saving_settings.op1_format) {
	
	case 2 : 
          gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_bin_op1_format),TRUE) ;  
	  break ;
	  
	case 8 :
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_oct_op1_format),TRUE) ;  
	  break ;
	  
	case 10 :
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_dec_op1_format),TRUE) ;  
	  break ;
	  
	case 16 :  
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_hex_op1_format),TRUE) ;  
	  break ;
	
      }
      
      switch (saving_settings.op2_format) {
	
	case 2 : 
          gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_bin_op2_format),TRUE) ;  
	  break ;
	  
	case 8 :
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_oct_op2_format),TRUE) ;  
	  break ;
	  
	case 10 :
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_dec_op2_format),TRUE) ;  
	  break ;
	  
	case 16 :  
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_hex_op2_format),TRUE) ;  
	  break ;
	
      }
      
      switch (saving_settings.res_format) {
	
	case 2 : 
          gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_bin_res_format),TRUE) ;  
	  break ;
	  
	case 8 :
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_oct_res_format),TRUE) ;  
	  break ;
	  
	case 10 :
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_dec_res_format),TRUE) ;  
	  break ;
	  
	case 16 :  
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_hex_res_format),TRUE) ;  
	  break ;
	
      }
      
      
    }
  }
  return FALSE ;
}



gboolean toggle_saving_setting_bases_all_operand_16(GtkWidget *widget,int *clean) {
  
  
  if (  gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) ) {
    
    saving_settings_set_hex_fields_insensitive(FALSE) ;
  
    saving_settings_set_bin_fields_insensitive(FALSE) ;
    saving_settings_set_oct_fields_insensitive(FALSE) ;
    saving_settings_set_dec_fields_insensitive(FALSE) ;
    
    saving_settings.op1_format = saving_settings.op2_format = saving_settings.res_format = 16 ;
    
    *clean = 1 ;
    saving_settings_clean_set_all_operand_on_base_16() ;
    *clean = 0 ;
  }
  else {
    
    
    if ( *clean == 0) { 
    
      saving_settings_set_hex_fields_sensitive(FALSE) ;
    
      saving_settings_set_bin_fields_sensitive(TRUE) ;
      saving_settings_set_oct_fields_sensitive(TRUE) ;
      saving_settings_set_dec_fields_sensitive(TRUE) ;
    }
    
  }
    
  return FALSE ;
}

gboolean toggle_saving_setting_bases_all_operand_8(GtkWidget *widget,int *clean) {
  
  
  if (  gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) ) {
        
    saving_settings_set_oct_fields_insensitive(FALSE) ;
  
    saving_settings_set_bin_fields_insensitive(FALSE) ;
    saving_settings_set_dec_fields_insensitive(FALSE) ;
    saving_settings_set_hex_fields_insensitive(FALSE) ;
    
    saving_settings.op1_format = saving_settings.op2_format = saving_settings.res_format = 8 ;
    
    *clean = 1 ;
    saving_settings_clean_set_all_operand_on_base_8() ;
    *clean = 0 ;
  }
  else {
        
    if ( *clean == 0) { 
    
      saving_settings_set_oct_fields_sensitive(FALSE) ;
    
      saving_settings_set_bin_fields_sensitive(TRUE) ;
      saving_settings_set_dec_fields_sensitive(TRUE) ;
      saving_settings_set_hex_fields_sensitive(TRUE) ;
    
      
    }
    
  }
      
  return FALSE ;
  
}

gboolean toggle_saving_setting_bases_all_operand_2(GtkWidget *widget,int *clean) {
    
  if (  gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) ) {
        
    saving_settings_set_bin_fields_insensitive(FALSE) ;
  
    saving_settings_set_oct_fields_insensitive(FALSE) ;
    saving_settings_set_dec_fields_insensitive(FALSE) ;
    saving_settings_set_hex_fields_insensitive(FALSE) ;
    
    saving_settings.op1_format = saving_settings.op2_format = saving_settings.res_format = 2 ;
    
    *clean = 1 ;
    saving_settings_clean_set_all_operand_on_base_2() ;
    *clean = 0 ;
  }
  else {
       
    if ( *clean == 0) {
    
      saving_settings_set_bin_fields_sensitive(FALSE) ;
      
      saving_settings_set_oct_fields_sensitive(TRUE) ;
      saving_settings_set_dec_fields_sensitive(TRUE) ;
      saving_settings_set_hex_fields_sensitive(TRUE) ;
    }
    
  }
  
  return FALSE ;
}

gboolean toggle_saving_setting_bases_all_operand_10(GtkWidget *widget,int *clean) {
    
  if (  gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) ) {
    
    saving_settings_set_dec_fields_insensitive(FALSE) ;
  
    saving_settings_set_bin_fields_insensitive(FALSE) ;
    saving_settings_set_oct_fields_insensitive(FALSE) ;
    saving_settings_set_hex_fields_insensitive(FALSE) ;
    
    saving_settings.op1_format = saving_settings.op2_format = saving_settings.res_format = 10 ;
    *clean = 1 ;
    saving_settings_clean_set_all_operand_on_base_10() ;
    *clean = 0 ;
  }
  else {
        
    if ( *clean == 0) {
    
      saving_settings_set_dec_fields_sensitive(FALSE) ;
    
      saving_settings_set_bin_fields_sensitive(TRUE) ;
      saving_settings_set_oct_fields_sensitive(TRUE) ;
      saving_settings_set_hex_fields_sensitive(TRUE) ;
    }
  }
      
  return FALSE ;
}

gboolean saving_settings_set_operand_1_base(GtkWidget *widget,int base) {
  saving_settings.op1_format=base ;
  return FALSE ;
}

gboolean saving_settings_set_operand_2_base(GtkWidget *widget,int base) {
  saving_settings.op2_format=base ;
  return FALSE ;
}

gboolean saving_settings_set_result_base(GtkWidget *widget,int base) {
  saving_settings.res_format=base ;
  return FALSE ;
}

gboolean saving_display_title(GtkWidget *widget,gpointer *data) {
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) ) { 
    saving_settings.display_title=true ;
  }
  else {
    saving_settings.display_title=false ;
  }
  return  FALSE ;
}

gboolean saving_display_bases(GtkWidget *widget,gpointer *data) {
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) ) { 
    saving_settings.display_bases=true ;
  }
  else {
    saving_settings.display_bases=false ;
  }
  return FALSE ;
}

gboolean saving_settings_use_notation(GtkWidget *widget,_Bool use_raw_notation) {
  if (use_raw_notation && (! saving_settings.use_raw_notation) ) {
    saving_settings.use_raw_notation=true ;
    return FALSE ;
  }
  
  else if (! use_raw_notation && saving_settings.use_raw_notation ) {
    
    
    saving_settings.use_raw_notation=false ;
    if (saving_settings.use_default_format) {
      
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_as_registered_format),FALSE) ;
      
      saving_settings_set_dec_fields_insensitive(FALSE) ;
  
      saving_settings_set_bin_fields_insensitive(FALSE) ;
      saving_settings_set_oct_fields_insensitive(FALSE) ;
      saving_settings_set_hex_fields_insensitive(FALSE) ;
      
      saving_settings.op1_format = saving_settings.op2_format = saving_settings.res_format = 10 ;
      
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_dec_all_format),TRUE) ;
      
      saving_settings_clean_set_all_operand_on_base_10() ;
      
      saving_settings.use_default_format=false ;
      
    }
    else {
      
      saving_settings_set_dec_fields_insensitive(FALSE) ;
  
      saving_settings_set_bin_fields_insensitive(FALSE) ;
      saving_settings_set_oct_fields_insensitive(FALSE) ;
      saving_settings_set_hex_fields_insensitive(FALSE) ;
      
      saving_settings.op1_format = saving_settings.op2_format = saving_settings.res_format = 10 ;
      
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_dec_all_format),TRUE) ;
      
      saving_settings_clean_set_all_operand_on_base_10() ;
      
    }
    return FALSE ;
      
      
  }
  return FALSE ;
}

gboolean get_title(GtkWidget *widget) {
  if ( (g_strcmp0(gtk_entry_get_text(GTK_ENTRY(widget)),"") != 0) && (saving_settings.display_title) ) {
    if ( strlen(gtk_entry_get_text(GTK_ENTRY(widget))) > 240 ) {
      gtk_entry_set_text(GTK_ENTRY(widget),"Title too long !!!") ;
      return FALSE ;
    }
    
    g_stpcpy(saving_settings.title,gtk_entry_get_text(GTK_ENTRY(widget))) ;
    return TRUE ;
  }
  else if (! saving_settings.display_title) {
    return TRUE ;
  }
  
  return FALSE ;
}

gboolean saving_settings_actions(GtkWidget *widget,int *item_idx) {
    
  if ( strcmp(g_object_get_data(G_OBJECT(widget),"action"),"cancel") == 0) {
    reset_saving_settings() ;
    gtk_widget_destroy(operand_output_format->save_settings_dialog) ;
    return FALSE ;
  }
  else if (strcmp(g_object_get_data(G_OBJECT(widget),"action"),"reset") == 0) {
    
    reset_saving_settings() ;
    return FALSE ;
  }
  else if (strcmp(g_object_get_data(G_OBJECT(widget),"action"),"export") == 0) {
        
    if (! get_title(operand_output_format->main_settings_title_entry) ) {
            
      return FALSE ;
    }
    if (! saving_settings.fileset) {
      gtk_entry_set_text(GTK_ENTRY(operand_output_format->main_settings_file_entry),"You must choose a file to export datas.") ;
      return FALSE ;
    }
   
    
    gtk_widget_destroy(operand_output_format->save_settings_dialog) ;
    
    if (saving_settings.file_format == 1) {
      save_as_txt(*item_idx) ;
    }
    
    else if (saving_settings.file_format == 2) {
      save_as_csv(*item_idx) ;
    }
    
    else if (saving_settings.file_format == 3) {
      set_html_colors_settings() ;
      save_as_html(*item_idx) ;
    }
    
    cannot_export_success_message_dialog(saving_settings.filepath) ;
    
    return FALSE ;
  }
  return FALSE ;
}
    

gboolean save_as_file(GtkButton *button,gpointer *data) {
  GtkWidget *file_chooser = gtk_file_chooser_dialog_new ("Save as file",
                             NULL,
                             GTK_FILE_CHOOSER_ACTION_SAVE,
                              "Cancel",
                              GTK_RESPONSE_CANCEL,
                               "Save as",
                               GTK_RESPONSE_ACCEPT,
                               NULL);
			       
  
  gint res;
  
  GtkFileChooser *chooser;
  
  chooser = GTK_FILE_CHOOSER (file_chooser);
  
  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser),g_get_home_dir()) ;
  
  gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
  
  res = gtk_dialog_run (GTK_DIALOG (file_chooser));
  
  if (res == GTK_RESPONSE_ACCEPT)
  {
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (file_chooser);
    filename = gtk_file_chooser_get_filename(chooser);
    
    
    
    memset(saving_settings.filepath,'\0',256) ;
    
    stpcpy(saving_settings.filepath,filename) ;
    
    saving_settings_check_filetype(saving_settings.filepath) ;
    
    gtk_entry_set_text(GTK_ENTRY(operand_output_format->main_settings_file_entry),g_filename_display_basename(saving_settings.filepath) ) ;
    
    saving_settings.fileset=true ;
    
    g_free (filename);
  }

  gtk_widget_destroy(file_chooser);
  
  return FALSE ;
}

void saving_settings_check_filetype(char *filename) {
  char *point ;
  if (saving_settings.file_format == 1) {
    if ( (point=strrchr(g_filename_display_basename(filename),'.')) == NULL  )  {
      strcat(filename,".txt") ;
    }
    else {
      if (g_strcmp0(point,".csv") == 0) {
	saving_settings.file_format=2 ;
  	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_txt_radiobutton),FALSE) ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_csv_radiobutton),TRUE) ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_html_radiobutton),FALSE) ;
      }
      else if (g_strcmp0(point,".html") == 0) {
	
	saving_settings.file_format=3 ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_txt_radiobutton),FALSE) ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_csv_radiobutton),FALSE) ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_html_radiobutton),TRUE) ;
      }
      else if (g_strcmp0(point,".txt") != 0) {
	strcat(filename,".txt") ;
      }
    }
  }
  if (saving_settings.file_format == 2) {
    if ( (point=strrchr(g_filename_display_basename(filename),'.')) == NULL ) {
      strcat(filename,".csv") ;
    }
    else {
   
      if (g_strcmp0(point,".txt") == 0) {
	saving_settings.file_format=1 ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_txt_radiobutton),TRUE) ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_csv_radiobutton),FALSE) ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_html_radiobutton),FALSE) ;
      }
      else if (g_strcmp0(point,".html") == 0) {
	saving_settings.file_format=3 ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_txt_radiobutton),FALSE) ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_csv_radiobutton),FALSE) ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_html_radiobutton),TRUE) ;
      }
      else if (g_strcmp0(point,".csv") != 0) {
	strcat(filename,".csv") ;
      }
      
    }
  }
  else if (saving_settings.file_format == 3) {
    if ( (point=strrchr(g_filename_display_basename(filename),'.')) == NULL) {
      strcat(filename,".html") ;
    }
    else {
      
      if (g_strcmp0(point,".txt") == 0) {
	saving_settings.file_format=1 ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_txt_radiobutton),TRUE) ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_csv_radiobutton),FALSE) ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_html_radiobutton),FALSE) ;
      }
      else if (g_strcmp0(point,".csv") == 0) {
	saving_settings.file_format=2 ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_txt_radiobutton),FALSE) ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_csv_radiobutton),TRUE) ;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->file_format_html_radiobutton),FALSE) ;
      }
      else if (g_strcmp0(point,".html") != 0) {
	
	strcat(filename,".html") ;
      }
      
    }
  }
}

void saving_settings_update_filetype(char *filename) {
  char *point ;
  int c, cc ;
  
  point=strrchr(filename,'.') ;
  
  if (saving_settings.file_format == 1) {
    if (g_strcmp0(point,".txt") == 0) {
	return ;
      
    }
    else if (g_strcmp0(point,".csv") == 0) {
      int c, cc ;
      for (c=strlen(filename)-1, cc=0 ; cc < 3 ; c--, cc++) {
	filename[c]='\0' ;
      }
      
    }
    else if (g_strcmp0(point,".html") == 0) {
      for (c=strlen(filename)-1, cc=0 ; cc < 4 ; c--, cc++) {
	filename[c]='\0' ;
      }
    }
    strcat(filename,"txt") ;
      
  }
  
  else if (saving_settings.file_format == 2) {
    if (g_strcmp0(point,".csv") == 0) {
	return ;
      
    }
    else if (g_strcmp0(point,".txt") == 0) {
      
      
      for (c=strlen(filename)-1, cc=0 ; cc < 3 ; c--, cc++) {
	filename[c]='\0' ;
      }
      
    }
    
    else if (g_strcmp0(point,".html") == 0) {
      for (c=strlen(filename)-1, cc=0 ; cc < 4 ; c--, cc++) {
	filename[c]='\0' ;
      }
    }
    strcat(filename,"csv") ;
      
  }
  
  else if (saving_settings.file_format == 3) {
    
    if (g_strcmp0(point,".html") == 0) {
	return ;
      
    }
    else if ( (g_strcmp0(point,".txt") == 0) || (g_strcmp0(point,".csv") == 0) ) {
      int c, cc ;
      for (c=strlen(filename)-1, cc=0 ; cc < 3 ; c--, cc++) {
	filename[c]='\0' ;
      }
      
    }
    
    strcat(filename,"html") ;
   }
   filename[strlen(filename)]='\0' ;
   
   return ;
}

void saving_settings_set_bin_fields_sensitive(gboolean set_active) {
  if (set_active) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_bin_all_format),FALSE) ;
  }
  gtk_widget_set_sensitive(operand_output_format->radio_bin_op1_format,TRUE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_bin_op2_format,TRUE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_bin_res_format,TRUE) ;
}

void saving_settings_set_bin_fields_insensitive(gboolean set_active) {
  if (set_active) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_bin_all_format),TRUE) ;
  }
  gtk_widget_set_sensitive(operand_output_format->radio_bin_op1_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_bin_op2_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_bin_res_format,FALSE) ;
}

void saving_settings_set_oct_fields_sensitive(gboolean set_active) {
  if (set_active) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_oct_all_format),FALSE) ;
  }
  gtk_widget_set_sensitive(operand_output_format->radio_oct_op1_format,TRUE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_oct_op2_format,TRUE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_oct_res_format,TRUE) ;
}

void saving_settings_set_oct_fields_insensitive(gboolean set_active) {
  if (set_active) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_oct_all_format),TRUE) ;
  }
  gtk_widget_set_sensitive(operand_output_format->radio_oct_op1_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_oct_op2_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_oct_res_format,FALSE) ;
}

void saving_settings_set_hex_fields_sensitive(gboolean set_active) {
  if (set_active) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_hex_all_format),FALSE) ;  
  }
    
  gtk_widget_set_sensitive(operand_output_format->radio_hex_op1_format,TRUE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_hex_op2_format,TRUE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_hex_res_format,TRUE) ;
}

void saving_settings_set_hex_fields_insensitive(gboolean set_active) {
  if (set_active) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_hex_all_format),TRUE) ;
  }
  gtk_widget_set_sensitive(operand_output_format->radio_hex_op1_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_hex_op2_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_hex_res_format,FALSE) ;
}

void saving_settings_set_dec_fields_sensitive(gboolean set_active) {
  if (set_active) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_dec_all_format),FALSE) ;
  }
  gtk_widget_set_sensitive(operand_output_format->radio_dec_op1_format,TRUE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_dec_op2_format,TRUE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_dec_res_format,TRUE) ;
}

void saving_settings_set_dec_fields_insensitive(gboolean set_active) {
  if (set_active) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_dec_all_format),TRUE) ;
  }
  gtk_widget_set_sensitive(operand_output_format->radio_dec_op1_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_dec_op2_format,FALSE) ;
  gtk_widget_set_sensitive(operand_output_format->radio_dec_res_format,FALSE) ;
}


void switch_saving_bin_all_operand_active(void) {
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_bin_op1_format),TRUE) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_bin_op2_format),TRUE) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_bin_res_format),TRUE) ;
}
	

void switch_saving_oct_all_operand_active(void) {
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_oct_op1_format),TRUE) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_oct_op2_format),TRUE) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_oct_res_format),TRUE) ;
}
	

void switch_saving_hex_all_operand_active(void) {
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_hex_op1_format),TRUE) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_hex_op2_format),TRUE) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_hex_res_format),TRUE) ;
}
	

void switch_saving_dec_all_operand_active(void) {
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_dec_op1_format),TRUE) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_dec_op2_format),TRUE) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->radio_dec_res_format),TRUE) ;
}




void saving_settings_clean_set_all_operand_on_base_16(void) {
  if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(operand_output_format->check_bin_all_format)) ) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_bin_all_format),FALSE) ;
  }
  if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(operand_output_format->check_oct_all_format)) ) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_oct_all_format),FALSE) ;
  }
  if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(operand_output_format->check_dec_all_format)) ) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_dec_all_format),FALSE) ;
  }
}

void saving_settings_clean_set_all_operand_on_base_8(void) {
  if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(operand_output_format->check_hex_all_format)) ) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_hex_all_format),FALSE) ;
  }
  if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(operand_output_format->check_bin_all_format)) ) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_bin_all_format),FALSE) ;
  }
  if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(operand_output_format->check_dec_all_format)) ) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_dec_all_format),FALSE) ;
  }
}

void saving_settings_clean_set_all_operand_on_base_2(void) {
  if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(operand_output_format->check_hex_all_format)) ) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_hex_all_format),FALSE) ;
  }
  if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(operand_output_format->check_oct_all_format)) ) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_oct_all_format),FALSE) ;
  }
  if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(operand_output_format->check_dec_all_format)) ) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_dec_all_format),FALSE) ;
  }
}


void saving_settings_clean_set_all_operand_on_base_10(void) {
  if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(operand_output_format->check_hex_all_format)) ) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_hex_all_format),FALSE) ;
  }
  if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(operand_output_format->check_oct_all_format)) ) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_oct_all_format),FALSE) ;
  }
  if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(operand_output_format->check_bin_all_format)) ) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(operand_output_format->check_bin_all_format),FALSE) ;
  }
}



void set_html_colors_settings(void) {
  
  GtkWidget *html_settings_dialog, *content_area ;
  
  GdkRGBA background_color, font_color, border_color ;
  
  background_color.red   = 1.0 ;
  background_color.green = 1.0 ;
  background_color.blue  = 1.0 ;
  background_color.alpha  = 1.0 ;
  
  font_color.red   = 0.0 ;
  font_color.green = 0.0 ;
  font_color.blue  = 0.0 ;
  font_color.alpha  = 1.0 ;
  
  border_color.red   = 0.0 ;
  border_color.green = 0.0 ;
  border_color.blue  = 0.0 ;
  border_color.alpha  = 1.0 ;
  
  html_settings_gui = g_slice_new(Saving_HTML_output_settings)  ;
  
  html_settings_dialog =  gtk_dialog_new() ;
  
  gtk_window_set_title(GTK_WINDOW(html_settings_dialog),"HTML export settings");
  
  gtk_dialog_add_button(GTK_DIALOG(html_settings_dialog),"OK", GTK_RESPONSE_OK);
  
  gtk_container_set_border_width(GTK_CONTAINER(html_settings_dialog),12) ;
  
  content_area = gtk_dialog_get_content_area(GTK_DIALOG (html_settings_dialog));
  
  GtkWidget *html_settings_grid = gtk_grid_new() ;  
  
  gtk_grid_set_row_spacing(GTK_GRID(html_settings_grid),8);
  
  gtk_grid_set_column_spacing(GTK_GRID(html_settings_grid),16);
  
  gtk_grid_set_column_homogeneous(GTK_GRID(html_settings_grid),TRUE);
  
  g_object_set(G_OBJECT(html_settings_grid),"margin",8,NULL) ;
  
  
  GtkWidget *html_color_settings_background_color_label = gtk_button_new_with_label("Background color") ; 
  
  html_settings_gui->html_color_settings_background_color_button = gtk_color_button_new() ;
  
  gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(html_settings_gui->html_color_settings_background_color_button) ,&background_color);
  
  
  GtkWidget *html_color_settings_font_color_label = gtk_button_new_with_label("Font color") ; 
  
  html_settings_gui->html_color_settings_font_color_button = gtk_color_button_new() ;
  
  gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(html_settings_gui->html_color_settings_font_color_button) ,&font_color);
  
  
  GtkWidget *html_color_settings_border_color_label = gtk_button_new_with_label("Border color") ; 
  
  html_settings_gui->html_color_settings_border_color_button = gtk_color_button_new() ;
  
  gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(html_settings_gui->html_color_settings_border_color_button) ,&border_color);
  
    
  GtkWidget *html_font_settings_label = gtk_button_new_with_label("Select Font") ; 
  
  
  
  html_settings_gui->html_font_settings_font_combo = gtk_combo_box_text_new() ;
  
  int c ;
  
  char *fonts[21]={"Andale","Arial","Courier",
                   "Comic Sans MS","Courier New",
		   "Georgia","Helvetica","Impact",
		   "Lucida","Marlett","Monospace",
		   "Palatino","Sans Serif","Serif", 
		   "Tahoma","Trebuchet MS","Verdana",
		   "Times New Roman",NULL}  ;
  
  for (c=0 ; fonts[c] != NULL ; c++) {
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(html_settings_gui->html_font_settings_font_combo),fonts[c]);
  }
  
  gtk_combo_box_set_active(GTK_COMBO_BOX(html_settings_gui->html_font_settings_font_combo),1);
  
  g_object_set(G_OBJECT(html_settings_gui->html_font_settings_font_combo),"wrap-width",2,NULL ) ;
  
  
  GtkWidget *html_font_size_settings_label = gtk_button_new_with_label("Font-size (px)") ; 
  
  GtkAdjustment *adjustment_font_size;

  adjustment_font_size = gtk_adjustment_new (12.0, 1.0, 128.0, 1.0, 1.0, 0.0);
  
  html_settings_gui->html_font_size_settings_spinner = gtk_spin_button_new(adjustment_font_size,1,0);
  
  GtkWidget *html_bold_settings_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,FALSE) ;
  
  
  GtkWidget *html_bold_settings_label = gtk_label_new("") ;
  
  gtk_label_set_markup(GTK_LABEL(html_bold_settings_label),"<big>Set in <b>bold</b>.</big>") ;
  
  html_settings_gui->html_bold_settings_check = gtk_check_button_new();
  
  gtk_box_pack_start(GTK_BOX(html_bold_settings_hbox),html_settings_gui->html_bold_settings_check,FALSE,FALSE,4) ;
  gtk_box_pack_start(GTK_BOX(html_bold_settings_hbox),html_bold_settings_label                    ,FALSE,FALSE,4) ;
  
  GtkWidget *html_italic_settings_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,FALSE) ;
  
  GtkWidget *html_italic_settings_label = gtk_label_new("") ;
  
  gtk_label_set_markup(GTK_LABEL(html_italic_settings_label),"<big>Set in <i>italic</i>.</big>") ;
  
  html_settings_gui->html_italic_settings_check = gtk_check_button_new();
  
  gtk_box_pack_start(GTK_BOX(html_italic_settings_hbox),html_settings_gui->html_italic_settings_check,FALSE,FALSE,4) ;
  gtk_box_pack_start(GTK_BOX(html_italic_settings_hbox),html_italic_settings_label                    ,FALSE,FALSE,4) ;
  
  
  
  GtkWidget *html_border_style_settings_label = gtk_button_new_with_label("Border style") ; 
  
  html_settings_gui->html_border_style_settings_combo = gtk_combo_box_text_new() ;
  
  char *borders[10]={"dashed","dotted","double",
                   "groove","inset","outset",
		   "ridge","solid","none",
		   NULL}  ;
  
  for (c=0 ; borders[c] != NULL ; c++) {
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(html_settings_gui->html_border_style_settings_combo),borders[c]);
  }
  
  gtk_combo_box_set_active(GTK_COMBO_BOX(html_settings_gui->html_border_style_settings_combo),7);
  
  GtkWidget *html_border_size_settings_label = gtk_button_new_with_label("Border-size (px)") ; 
  
  GtkAdjustment *adjustment_border_size;

  adjustment_border_size = gtk_adjustment_new (4.0, 1.0, 128.0, 1.0, 1.0, 0.0);
  
  html_settings_gui->html_border_size_settings_spinner = gtk_spin_button_new(adjustment_border_size,1,0);
  
  
  GtkWidget *html_border_settings_settings_label = gtk_button_new_with_label("Border settings") ; 
  
  html_settings_gui->html_border_type_settings_combo = gtk_combo_box_text_new() ;
  
  char *settings[3]={"separate","collapse",NULL}  ;
  
  for (c=0 ; settings[c] != NULL ; c++) {
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(html_settings_gui->html_border_type_settings_combo),settings[c]);
  }
  
  gtk_combo_box_set_active(GTK_COMBO_BOX(html_settings_gui->html_border_type_settings_combo),0);
  
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_color_settings_background_color_label ,                     0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_settings_gui->html_color_settings_background_color_button , 1, 0, 1, 1);
  
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_color_settings_font_color_label ,                           0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_settings_gui->html_color_settings_font_color_button ,       1, 1, 1, 1);
  
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_color_settings_border_color_label ,                         0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_settings_gui->html_color_settings_border_color_button ,     1, 2, 1, 1);
  
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_font_settings_label ,                                       0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_settings_gui->html_font_settings_font_combo ,               1, 3, 1, 1);
  
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_font_size_settings_label ,                                  0, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_settings_gui->html_font_size_settings_spinner ,             1, 4, 1, 1);
  
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_bold_settings_hbox ,                                        0, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_italic_settings_hbox ,                                      1, 5, 1, 1);
  
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_border_style_settings_label ,                               0, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_settings_gui->html_border_style_settings_combo ,       1, 6, 1, 1);
  
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_border_size_settings_label ,                                0, 7, 1, 1);
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_settings_gui->html_border_size_settings_spinner ,           1, 7, 1, 1);
  
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_border_settings_settings_label ,                             0, 8, 1, 1);
  gtk_grid_attach(GTK_GRID(html_settings_grid),html_settings_gui->html_border_type_settings_combo ,     1, 8, 1, 1);
  
  gtk_container_add(GTK_CONTAINER(content_area),html_settings_grid) ;
  
  g_signal_connect(G_OBJECT(html_settings_dialog),"response",G_CALLBACK(saving_get_html_settings), html_settings_dialog);
  
 
  gtk_widget_show_all(html_settings_dialog) ;
  
  gtk_dialog_run(GTK_DIALOG(html_settings_dialog)) ;
  
}

void init_html_settings(void) {
  html_settings.bg_color     = calloc((int) strlen("#FFFFFF")+1,sizeof(char)) ;
  html_settings.fg_color     = calloc((int) strlen("#FFFFFF")+1,sizeof(char)) ;
  html_settings.border_color = calloc((int) strlen("#FFFFFF")+1,sizeof(char)) ;
  html_settings.fontname     = calloc(32,sizeof(char)) ;
  html_settings.border_style = calloc(32,sizeof(char)) ;
  html_settings.border_type  = calloc(32,sizeof(char)) ;
}

void reset_html_settings(void) {
  memset(html_settings.bg_color,'\0',(int) strlen("#FFFFFF")+1) ;
  memset(html_settings.fg_color,'\0',(int) strlen("#FFFFFF")+1) ;
  memset(html_settings.border_color,'\0',(int) strlen("#FFFFFF")+1) ;
  
  memset(html_settings.fontname,'\0',32) ;
  memset(html_settings.border_style,'\0',32) ;
  memset(html_settings.border_type,'\0',32) ;
}


void saving_get_html_settings(GtkWidget *html_settings_dialog) {
   
   GdkRGBA background_color, font_color, border_color ;
   
   gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(html_settings_gui->html_color_settings_background_color_button),&background_color) ;
   
   gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(html_settings_gui->html_color_settings_font_color_button),&font_color) ;
   
   gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(html_settings_gui->html_color_settings_border_color_button),&border_color) ;
   
   html_settings.font_size = (unsigned int) gtk_spin_button_get_value(GTK_SPIN_BUTTON(html_settings_gui->html_font_size_settings_spinner)) ; 
   
   html_settings.bold   = (_Bool)  gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(html_settings_gui->html_bold_settings_check)) ;
   html_settings.italic = (_Bool)  gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(html_settings_gui->html_italic_settings_check)) ;
   
   html_settings.border_size = (unsigned int) gtk_spin_button_get_value(GTK_SPIN_BUTTON(html_settings_gui->html_border_size_settings_spinner)) ;    
    
   sprintf(html_settings.bg_color,"#%02x%02x%02x",(unsigned int) round(background_color.red*255.0) , (unsigned int) round(background_color.green*255), (unsigned int) round(background_color.blue*255)) ;
   sprintf(html_settings.fg_color,"#%02x%02x%02x",(unsigned int) round(font_color.red*255.0) , (unsigned int) round(font_color.green*255), (unsigned int) round(font_color.blue*255)) ;
   sprintf(html_settings.border_color,"#%02x%02x%02x",(unsigned int) round(border_color.red*255.0) , (unsigned int) round(border_color.green*255), (unsigned int) round(border_color.blue*255)) ;
   sprintf(html_settings.fontname,"%s",gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(html_settings_gui->html_font_settings_font_combo))) ;
   sprintf(html_settings.border_style,"%s",gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(html_settings_gui->html_border_style_settings_combo))) ;
   sprintf(html_settings.border_type,"%s",gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(html_settings_gui->html_border_type_settings_combo))) ;
   
   gtk_widget_destroy(html_settings_dialog) ;
   
   return ;
}

void cannot_export_no_data_message_dialog(void) {
  GtkWidget *message_error_no_data_export_dialog = gtk_message_dialog_new(NULL,0,GTK_MESSAGE_ERROR,GTK_BUTTONS_CLOSE,"Cannot generate calculation data sheet !\nNo operation registered.\nUse the \"Saving\" button to register operations.") ;
  
  gtk_dialog_run(GTK_DIALOG(message_error_no_data_export_dialog)) ;
  
  gtk_widget_destroy(message_error_no_data_export_dialog);
  
  return ;
}

void cannot_export_success_message_dialog(const char *filename) {
  GtkWidget *message_error_no_data_export_dialog = gtk_message_dialog_new(NULL,0,GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"Calculation data sheet saved as file:\n\t%s\n",g_filename_display_basename(filename)) ;
  
  gtk_dialog_run(GTK_DIALOG(message_error_no_data_export_dialog)) ;
  
  gtk_widget_destroy(message_error_no_data_export_dialog);
  
  return ;
}

typedef struct  {
  
  GtkWidget *upper_entry ;
  GtkWidget *operand_1_entry ;
  GtkWidget *operand_2_entry ;
  GtkWidget *result_entry    ;
  
  
} Entry_fields ;

typedef struct {
  
  GtkWidget *button_n_0 ;
  GtkWidget *button_n_1 ;
  GtkWidget *button_n_2 ;
  GtkWidget *button_n_3 ;
  GtkWidget *button_n_4 ;
  GtkWidget *button_n_5 ;
  
  GtkWidget *button_n_6 ;
  GtkWidget *button_n_7 ;
  GtkWidget *button_n_8 ;
  GtkWidget *button_n_9 ;
  GtkWidget *button_n_A ;
  
  GtkWidget *button_n_B ;
  GtkWidget *button_n_C ;
  GtkWidget *button_n_D ;
  GtkWidget *button_n_E ;
  GtkWidget *button_n_F ;
  
  GtkWidget *button_comma  ;
  
  GtkWidget *button_base_hex ;
  GtkWidget *button_base_oct ;
  GtkWidget *button_base_bin ;
  GtkWidget *button_base_dec ;
  
} Button_set ;

typedef struct {
  
  GtkWidget *operator_add_button    ;
  GtkWidget *operator_sub_button    ;
  GtkWidget *operator_mul_button    ;
  GtkWidget *operator_div_button    ;
  GtkWidget *operator_modulo_button ;
} Operators ;

typedef struct {
  GtkWidget *operand_1_sign_button ;
  GtkWidget *operand_2_sign_button ;
} Operand_sign ;

typedef struct {
  GtkWidget *menubar ;

  GtkWidget *main_menu ;
  
  GtkWidget *main_menu_item ;
  
  GtkWidget *main_menu_item_label ;
  
  GtkWidget *main_menu_item_image ;
  
  GtkWidget *main_menu_item_button_hbox ;
  
  
  
  GtkWidget *main_menu_export_item ;
  
  GtkWidget *main_menu_export_label ;
  
  GtkWidget *main_menu_export_image ;
  
  GtkWidget *main_menu_export_button_hbox ;
  
  
  GtkWidget *main_menu_separator_1 ;
  
  
  GtkWidget *main_menu_about_item ;
  
  GtkWidget *main_menu_about_label ;
  
  GtkWidget *main_menu_about_image ;
  
  GtkWidget *main_menu_about_button_hbox ;
  
  
  GtkWidget *main_menu_separator_2 ;
  
  
  GtkWidget *main_menu_quit_item ;
  
  GtkWidget *main_menu_quit_label ;
  
  GtkWidget *main_menu_quit_image ;
  
  GtkWidget *main_menu_quit_button_hbox ;
  
} Menu ;

typedef struct {
  
  
  GtkWidget *main_window ;
  
  GtkWidget *main_vbox ;
  
  Menu *menu ;
  
  
  /* Upper part of the GUI widgets. */
  GtkWidget *upper_grid ;
  
  
  
  GtkWidget *mem_add_button ;
  GtkWidget *mem_del_button ;
  GtkWidget *mem_get_button ;
  
  Entry_fields *entry_fields  ;
  
  Operand_sign *operand_sign ;
  
  GtkWidget *result_sign_button ;
  
  GtkWidget *command_store_button ;
  GtkWidget *command_delete_button ;
  GtkWidget *command_revert_button ;
  
  /* MEM nav part of the GUI */
  
  GtkWidget *mem_nav_grid ;
  
  GtkWidget *mem_nav_titel_button ; 
  
  GtkWidget *mem_nav_plus_button ;
  
  GtkWidget *mem_nav_minus_button ;
  
  /* */
  
  GtkWidget *middle_hbox ;
  
  /* */
  
  GtkWidget *button_set_grid ;
  
  Button_set *button_set ;
  
  /* */
  
  GtkWidget *operators_grid  ;
  
  Operators *operators ;
  
  /**/
  
  GtkWidget *commands_grid  ;
  
  GtkWidget *command_erase_button  ;
  GtkWidget *command_reset_button  ;
  GtkWidget *command_enter_button  ;
  
  /* */
  
  GtkWidget *bottom_hbox ;
  
  GtkWidget *angle_hbox ;
  
  GtkWidget *degrees_button ;
  GtkWidget *radians_button ; 
  
  GtkWidget *trigonometric_hbox ;
  
  GtkWidget *cos_button ;
  GtkWidget *sin_button ;
  GtkWidget *tan_button ;
  
  GtkWidget *arc_trigonometric_hbox ;
  
  GtkWidget *acos_button ;
  GtkWidget *asin_button ;
  GtkWidget *atan_button ;
  
  GtkWidget *hyperbel_trigonometric_hbox ;
  
  GtkWidget *cosh_button ;
  GtkWidget *sinh_button ;
  GtkWidget *tanh_button ;
  
  GtkWidget *base_bottom_hbox ;
  
  GtkWidget *sqrt_button ;
  GtkWidget *pow_button  ;
  GtkWidget *abs_button  ;
} GUI ; 

typedef struct {
  
  GtkWidget *radio_hex_op1_format ;
  GtkWidget *radio_hex_op2_format ;
  GtkWidget *radio_hex_res_format ;
  GtkWidget *check_hex_all_format ;
  
  GtkWidget *radio_oct_op1_format ;
  GtkWidget *radio_oct_op2_format ;
  GtkWidget *radio_oct_res_format ;
  GtkWidget *check_oct_all_format ;
  
  GtkWidget *radio_bin_op1_format ;
  GtkWidget *radio_bin_op2_format ;
  GtkWidget *radio_bin_res_format ;
  GtkWidget *check_bin_all_format ;
  
  GtkWidget *radio_dec_op1_format ;
  GtkWidget *radio_dec_op2_format ;
  GtkWidget *radio_dec_res_format ;
  GtkWidget *check_dec_all_format ;
  
  GtkWidget *check_as_registered_format ;
  
  GtkWidget *main_settings_title_entry ;
  GtkWidget *main_settings_file_entry ;
  
  GtkWidget *save_settings_dialog ;
  
  GtkWidget *file_format_txt_radiobutton ;
  GtkWidget *file_format_csv_radiobutton ;
  GtkWidget *file_format_html_radiobutton ;
  
  GtkWidget *display_options_display_title_check ;
  GtkWidget *display_options_display_base_check ;
  
  GtkWidget *notation_enginer_radio ;
  GtkWidget *notation_numbers_radio ;
  
} Saving_output_format ;

typedef struct {
  GtkWidget *html_color_settings_background_color_button ;
  GtkWidget *html_color_settings_font_color_button ;
  GtkWidget *html_color_settings_border_color_button ;
  GtkWidget *html_font_settings_font_combo ;
  GtkWidget *html_font_size_settings_spinner ;
  GtkWidget *html_bold_settings_check ;
  GtkWidget *html_italic_settings_check ;
  GtkWidget *html_border_style_settings_combo ;
  GtkWidget *html_border_size_settings_spinner ;
  GtkWidget *html_border_type_settings_combo ;
  
} Saving_HTML_output_settings ;


gboolean destroy_register_message(GtkWidget *widget) {
  gtk_widget_destroy(widget) ;
  
  return FALSE ;
}

void diplay_operation_resgistering_message_dialog(void) {
  GtkWidget *message_registering_dialog = gtk_message_dialog_new(NULL,0,GTK_MESSAGE_INFO,GTK_BUTTONS_NONE,"Operation registered");
  
  //g_object_set(G_OBJECT(message_registering_dialog),"accept-focus",FALSE,NULL) ; 
  
  g_timeout_add(11125, (GSourceFunc)destroy_register_message,message_registering_dialog) ;
  
  gtk_dialog_run(GTK_DIALOG(message_registering_dialog)) ;
  
  //gtk_widget_show(message_registering_dialog) ;
  
  //sleep(3) ;
  
  //gtk_widget_destroy(message_registering_dialog);
  
  return ;
}


void cannot_export_file_error_message_dialog(const char *filename,const char *error_message) {
  GtkWidget *message_error_export_dialog = gtk_message_dialog_new(NULL,0,GTK_MESSAGE_ERROR,GTK_BUTTONS_CLOSE,"Cannot generate calculation data sheet as file:\n\t%s\n\n%s",g_filename_display_basename(filename),error_message) ;
  
  gtk_dialog_run(GTK_DIALOG(message_error_export_dialog)) ;
  
  gtk_widget_destroy(message_error_export_dialog);
  
  return ;
}

void cannot_export_success_message_dialog(const char *filename) {
  GtkWidget *message_error_no_data_export_dialog = gtk_message_dialog_new(NULL,0,GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"Calculation data sheet saved as file:\n\t%s\n",g_filename_display_basename(filename)) ;
  
  gtk_dialog_run(GTK_DIALOG(message_error_no_data_export_dialog)) ;
  
  gtk_widget_destroy(message_error_no_data_export_dialog);
  
  return ;
}
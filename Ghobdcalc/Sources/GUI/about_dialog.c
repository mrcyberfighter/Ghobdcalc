

void display_about_dialog(GtkWidget *widget,gpointer data) {
    
  GtkWidget *about_dialog = gtk_about_dialog_new();
    
  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog),"Ghobdcalc") ;
  
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_dialog),"1.0.0") ;
  
  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog),"Copyright (C) 2014 Brüggeman Eddie gplv3 License") ;
  
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog),"Ghobdcalc an multibase calculator with severals functions\nContact: <mrcyberfighter@gmail.com>") ; 
  
   
  gchar *license_file_content ;
  gchar *licence_path=g_malloc0(256) ;
  
  g_stpcpy(licence_path,"/usr/share/Ghobdcalc") ;
  strcat(licence_path,"/License/gpl.txt") ;
  
  g_file_get_contents(licence_path,&license_file_content,NULL,NULL);
  
  g_free(licence_path) ;
  
  gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(about_dialog),license_file_content);
  
  g_free(license_file_content) ;
  
  gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG(about_dialog),FALSE);
  
  const gchar *thanks[2] = {"Thank's to my mother, my family and the doctors.",NULL} ;
  
  gtk_about_dialog_add_credit_section(GTK_ABOUT_DIALOG(about_dialog),"Thank's",thanks);
  
  const gchar *advice[2] = {"Stay away from drugs: drugs destroy your brain and your life.",NULL} ;
  
  gtk_about_dialog_add_credit_section(GTK_ABOUT_DIALOG(about_dialog),"Advice:",advice);
  
  
  
  const gchar *author[2] = {"Brüggemann Eddie (alias mrcyrberfighter)",NULL} ;
  
  gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about_dialog),author);
  
  
  gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(about_dialog),NULL) ;
    
  gtk_dialog_run(GTK_DIALOG(about_dialog)) ;
    
  gtk_widget_destroy(about_dialog) ;
}
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

void cannot_export_file_error_message_dialog(const char *filename,const char *error_message) {
  /** Display an error message in case the file cannot be created or overriden.
   * **************************************************************************/
  
  GtkWidget *message_error_export_dialog = gtk_message_dialog_new(NULL,0,GTK_MESSAGE_ERROR,GTK_BUTTONS_CLOSE,"Cannot generate calculation data sheet as file:\n\t%s\n\n%s",g_filename_display_basename(filename),error_message) ;
  
  gtk_dialog_run(GTK_DIALOG(message_error_export_dialog)) ;
  
  gtk_widget_destroy(message_error_export_dialog);
  
  return ;
}





void register_operations(int item_index) {
  /** Register an operation for further exporting. **/
  
  struct Operande operande1 ;
  struct Operande operande2 ;
  struct Operande result    ;
  
  operande1.operande_bin_str=calloc(128,sizeof(char)) ;
  operande1.operande_oct_str=calloc(128,sizeof(char)) ;
  operande1.operande_dec_str=calloc(128,sizeof(char)) ;
  operande1.operande_hex_str=calloc(128,sizeof(char)) ;
  operande1.operande_string =calloc(127,sizeof(char)) ;
  
  strcpy(operande1.operande_bin_str,operations.operande_1.operande_bin_str) ;
  operande1.operande_bin_str[127]='\0' ;
  strcpy(operande1.operande_oct_str,operations.operande_1.operande_oct_str) ;
  operande1.operande_oct_str[127]='\0' ;
  strcpy(operande1.operande_dec_str,operations.operande_1.operande_dec_str) ;
  operande1.operande_dec_str[127]='\0' ;
  strcpy(operande1.operande_hex_str,operations.operande_1.operande_hex_str) ;
  operande1.operande_hex_str[127]='\0' ;
  
  operande1.operand_base = operations.operande_1.operand_base ;
  
  operande1.operande_is_float = operations.operande_1.operande_is_float ;
  
  if (operande1.operande_is_float) {
    operande1.operande_digit.operande_float = operations.operande_1.operande_digit.operande_float ;
  }
  else {
    operande1.operande_digit.operande_int = operations.operande_1.operande_digit.operande_int ;
  }
    
  
  operande2.operande_bin_str=calloc(128,sizeof(char)) ;
  operande2.operande_oct_str=calloc(128,sizeof(char)) ;
  operande2.operande_dec_str=calloc(128,sizeof(char)) ;
  operande2.operande_hex_str=calloc(128,sizeof(char)) ;
  operande2.operande_string =calloc(127,sizeof(char)) ;
  
  strcpy(operande2.operande_bin_str,operations.operande_2.operande_bin_str) ;
  operande2.operande_bin_str[127]='\0' ;
  strcpy(operande2.operande_oct_str,operations.operande_2.operande_oct_str) ;
  operande2.operande_oct_str[127]='\0' ;
  strcpy(operande2.operande_dec_str,operations.operande_2.operande_dec_str) ;
  operande2.operande_dec_str[127]='\0' ;
  strcpy(operande2.operande_hex_str,operations.operande_2.operande_hex_str) ;
  operande2.operande_hex_str[127]='\0' ;
  
  operande2.operand_base = operations.operande_2.operand_base ;
  
  operande2.operande_is_float = operations.operande_2.operande_is_float ;
  
  if (operande2.operande_is_float) {
    operande2.operande_digit.operande_float = operations.operande_2.operande_digit.operande_float ;
  }
  else {
    operande2.operande_digit.operande_int = operations.operande_2.operande_digit.operande_int ;
  }
  
  result.operande_bin_str=calloc(128,sizeof(char)) ;
  result.operande_oct_str=calloc(128,sizeof(char)) ;
  result.operande_dec_str=calloc(128,sizeof(char)) ;
  result.operande_hex_str=calloc(128,sizeof(char)) ;
  result.operande_string =calloc(127,sizeof(char)) ;
  
  strcpy(result.operande_bin_str,operations.result.operande_bin_str) ;
  result.operande_bin_str[127]='\0' ;
  strcpy(result.operande_oct_str,operations.result.operande_oct_str) ;
  result.operande_oct_str[127]='\0' ;
  strcpy(result.operande_dec_str,operations.result.operande_dec_str) ;
  result.operande_dec_str[127]='\0' ;
  strcpy(result.operande_hex_str,operations.result.operande_hex_str) ;
  result.operande_hex_str[127]='\0' ;
  
  result.operand_base = operations.result.operand_base ;
  
  result.operande_is_float = operations.result.operande_is_float ;
  
  if (result.operande_is_float) {
    result.operande_digit.operande_float = operations.result.operande_digit.operande_float ;
  }
  else {
    result.operande_digit.operande_int = operations.result.operande_digit.operande_int ;
  }
  
  save_operation[item_index].operande_1 = operande1  ;
  save_operation[item_index].operande_2 = operande2  ;
  save_operation[item_index].result     = result     ;

  save_operation[item_index].current_base     = operations.current_base     ;
  save_operation[item_index].current_operator = operations.current_operator ;
  
  return ;
}

int compute_string_length(struct Operande *operande,uint8_t operand) {
  /** Compute string length needed for the text file format by exporting.
   *  For separator length, space amount for littler operand from the right.
   *  ! This function is called for every operand string to get the maximal length of it.
   **************************************************************************************/
  
  uint8_t base ;
  
  if (saving_settings.use_default_format) {
    base=operande->operand_base ;
  }
  else {
    switch (operand) {
      case 1 :
	base = saving_settings.op1_format ;
	break ;
      case 2 :
	base = saving_settings.op2_format ;
	break ;
      case 3 :
	base = saving_settings.res_format ;
	break ;
    }
  }
      
  
  char *string_for_strlen=calloc(128+2,sizeof(char)) ;
  
  int string_length ;
  
  switch (base) {
    case 2 :
      
      sprintf(string_for_strlen,"%s%s",(saving_settings.display_bases == 1) ? "0b" : "", operande->operande_bin_str) ;
      string_length = (int ) strlen(string_for_strlen) ;
      free(string_for_strlen) ;
      return string_length ;
      
    case 8 :  
      
      sprintf(string_for_strlen,"%s%s",(saving_settings.display_bases == 1) ? "0" : "", operande->operande_oct_str) ;
      string_length = (int ) strlen(string_for_strlen) ;
      free(string_for_strlen) ;
      return string_length ;
      
    case 10 :
      
      if (saving_settings.use_raw_notation)  {
        sprintf(string_for_strlen,"%s",operande->operande_dec_str) ;
      }
      else {
	if (operande->operande_is_float) {
	  sprintf(string_for_strlen,"%e",(double) operande->operande_digit.operande_float) ;
	}
	else if (! operande->operande_is_float) {
	  sprintf(string_for_strlen,"%e",(double) operande->operande_digit.operande_int) ;
	} 
      }
	  
      string_length = (int ) strlen(string_for_strlen) ;
      free(string_for_strlen) ;
      return string_length ;
      
    case 16 :
      
      sprintf(string_for_strlen,"%s%s",(saving_settings.display_bases == 1) ? "0x" : "",operande->operande_hex_str) ;
      string_length = (int ) strlen(string_for_strlen) ;
      free(string_for_strlen) ;
      return string_length ;
  }
  return 0 ;
}

void set_current_string(struct Operande *operande,char *current_string,uint8_t operand) {
  /** Saving the current string in relationship of the base to format it for export.
   *********************************************************************************/
  
  uint8_t base ;
  
  if (saving_settings.use_default_format) {
    base=operande->operand_base ;
  }
  else {
    switch (operand) {
      case 1 :
	base = saving_settings.op1_format ;
	break ;
      case 2 :
	base = saving_settings.op2_format ;
	break ;
      case 3 :
	base = saving_settings.res_format ;
	break ;
    }
  }
  
  switch (base) {
    case 2 :
      
      sprintf(current_string,"%s%s",(saving_settings.display_bases == 1) ? "0b" : "", operande->operande_bin_str) ;
      return ;
      
    case 8 :  
      
      sprintf(current_string,"%s%s",(saving_settings.display_bases == 1) ? "0" : "", operande->operande_oct_str) ;
      return ;
      
    case 10 :
      
      if (saving_settings.use_raw_notation)  {
        sprintf(current_string,"%s",operande->operande_dec_str) ;
      }
      else {
	if (operande->operande_is_float) {
	  sprintf(current_string,"%e",(double) operande->operande_digit.operande_float) ;
	}
	else if (! operande->operande_is_float) {
	  sprintf(current_string,"%e",(double) operande->operande_digit.operande_int) ;
	} 
      }
      return ;
      
    case 16 :
      
      sprintf(current_string,"%s%s",(saving_settings.display_bases == 1) ? "0x" : "",operande->operande_hex_str) ;
      return ;
  }
}

void save_as_txt(int item_idx) {
  /** Export all registered operations items in a text file. 
   * *******************************************************/
  
  int c ;
  
  int max_strlen=0 ;
  
  for (c=0 ; c < item_idx ; c++) {
    /** Search the greatest string length in relationship to the base to display it in
     *  and the notation to use.
     * ********************************************************************************/
    
    if (compute_string_length(&save_operation[c].operande_1,1) > max_strlen)
      max_strlen = compute_string_length(&save_operation[c].operande_1,1) ;
    
    if (compute_string_length(&save_operation[c].operande_2,2) > max_strlen) {
      max_strlen = compute_string_length(&save_operation[c].operande_2,2) ;
    }
    
    if (compute_string_length(&save_operation[c].result,3) > max_strlen) {
      max_strlen = compute_string_length(&save_operation[c].result,3) ;
    }
    
  }
  
    
  FILE *fp ;
  
  errno=0 ; 
 
  if  ( (fp=fopen(saving_settings.filepath,"w")) == NULL ) {
    cannot_export_file_error_message_dialog(saving_settings.filepath,strerror(errno)) ;
    return ; 
  }
  
  char *spaces=calloc(128+2,sizeof(char)) ;
  
  char *current_string=calloc(128+2,sizeof(char)) ;
  char *current_line=calloc(256+2,sizeof(char)) ;
  char *separator=calloc(256+2,sizeof(char)) ;
  
  char *title_fmt=calloc(256,sizeof(char)) ;
  char *title_border=calloc(256+2,sizeof(char)) ;
  char *spaces1=calloc(128,sizeof(char)) ;
  char *spaces2=calloc(128,sizeof(char)) ;
  
  int title_spacing=1 ;
 
  if (saving_settings.display_title) {
    
    
    
    if (max_strlen+9 >= (int) strlen(saving_settings.title)+4) {
      /** Computing of the space between the title and the title decoration borders. 
       *  In relation ship of:
       *  -) The title length
       *  -) The maximal operand item length.
       *****************************************************************************/
      
      title_spacing= (int) ceil(( (max_strlen+9) - (strlen(saving_settings.title)+4) ) / 2) ;
      
      /** Set space at the left of the title **/ 
      memset(spaces1,' ',title_spacing) ;
      /** Set space at the right of the title by taking odd values in charge. **/  
      memset(spaces2,' ', ( ((max_strlen % 2 != 0) && (strlen(saving_settings.title) % 2 == 0)) || ((max_strlen % 2 == 0) && (strlen(saving_settings.title) % 2 != 0)) ) ? title_spacing : title_spacing+1 ) ;
    
      
    }
    else {
      /** Default space length: the title is greater the the maximal operand string length. **/
      memset(spaces1,' ',title_spacing) ;
      memset(spaces2,' ',title_spacing) ;
    }
    
    
    
    sprintf(title_fmt,"\n\t=>%s%s%s<=\t\n",spaces1,saving_settings.title,spaces2) ;
    
    free(spaces1) ;
    free(spaces2) ;
    
    
    strcat(title_border,"\t") ;
    
    for (c=0 ; c < (int) strlen(title_fmt)-4 ; c++) {
      strcat(title_border,"-") ;
    }
    
    
    fwrite(title_border, sizeof(char), strlen(title_border), fp)  ;
    fwrite(title_fmt, sizeof(char), strlen(title_fmt), fp)       ;
    fwrite(title_border, sizeof(char), strlen(title_border), fp)  ;
    
    free(title_fmt) ;
    free(title_border) ;
  
    
  }
  
  
  strcat(separator,"\t") ;
  
  for (c=0 ; c < max_strlen+9 ; c++) {
    strcat(separator,"-") ;
  }
  strcat(separator,"\t") ;
  
  
  fwrite("\n\n", sizeof(char), strlen("\n\n"), fp)  ;
  
  uint8_t base ;
  
  for (c=0 ; c < item_idx ; c++) {
    /** Writing all items to file. **/
    
    memset(current_string,'\0',128+2) ;
    memset(spaces,'\0',128+2) ;  
    

    set_current_string(&save_operation[c].operande_1,current_string,1) ;
    
    
    memset(spaces,' ',max_strlen-(int) strlen(current_string)) ;
    
    fwrite(separator,sizeof(char),strlen(separator),fp) ;
    
    fwrite("\n", sizeof(char), strlen("\n"), fp)  ;
    
    
  
    if (saving_settings.use_default_format) {
      base = save_operation[c].operande_1.operand_base ;
    }
    else {
      base = saving_settings.op1_format ;
    }
    
    sprintf(current_line,"\t%c %s %s %s\t\n",' ',spaces,current_string, (base == 2) ? "(bin)" : (base == 8) ? "(oct)" : (base == 10) ? "(dec)" : (base == 16) ? "(hex)" : "(err)") ;
    
    fwrite(current_line,sizeof(char),strlen(current_line),fp);
    
    memset(current_string,'\0',128+2) ;
    memset(spaces,'\0',128+2) ;
    memset(current_line,'\0',256+2) ;
    
    set_current_string(&save_operation[c].operande_2,current_string,2) ;
    
    memset(spaces,' ',max_strlen-(int) strlen(current_string)) ;
    
    if ( save_operation[c].current_operator == '+' ) {
      fwrite("\t+ ",sizeof(char),strlen("\t+ "),fp) ;
    }
    else if ( save_operation[c].current_operator == '-' ) {
      fwrite("\t- ",sizeof(char),strlen("\t- "),fp) ;
    }
    else if ( save_operation[c].current_operator == '*' ) {
      fwrite("\t× ",sizeof(char),strlen("\t× "),fp) ;
    }
    else if ( save_operation[c].current_operator == '/' ) {
      fwrite("\t÷ ",sizeof(char),strlen("\t÷ "),fp) ;
    }
    else if ( save_operation[c].current_operator == '%' ) {
      fwrite("\t% ",sizeof(char),strlen("\t% "),fp) ;
    }
    else if ( save_operation[c].current_operator == '^' ) {
      fwrite("\t^ ",sizeof(char),strlen("\t^ "),fp) ;
    }
    
    if (saving_settings.use_default_format) {
      base = save_operation[c].operande_2.operand_base ;
    }
    else {
      base = saving_settings.op2_format ;
    }
    
    sprintf(current_line,"%s %s %s\t\n",spaces,current_string, (base == 2) ? "(bin)" : (base == 8) ? "(oct)" : (base == 10) ? "(dec)" : (base == 16) ? "(hex)" : "(err)") ;
    fwrite(current_line,sizeof(char),strlen(current_line),fp);
    
    memset(current_string,'\0',128+2) ;
    memset(spaces,'\0',128+2) ;
    memset(current_line,'\0',256+2) ;
    
    set_current_string(&save_operation[c].result,current_string,3) ;
    
    memset(spaces,' ',max_strlen-(int) strlen(current_string) ) ;
    
    if (saving_settings.use_default_format) {
      base = save_operation[c].result.operand_base ;
    }
    else {
      base = saving_settings.res_format ;
    }
    
    sprintf(current_line,"\t= %s %s %s\t\n",spaces,current_string, (base == 2) ? "(bin)" : (base == 8) ? "(oct)" : (base == 10) ? "(dec)" : (base == 16) ? "(hex)" : "(err)") ;
    fwrite(current_line,sizeof(char),strlen(current_line),fp);
        
    fflush(fp) ;
  }
  
  fwrite(separator,sizeof(char),strlen(separator),fp) ;
  
  fwrite("\n\n", sizeof(char), strlen("\n\n"), fp)  ;
  
  fflush(fp) ;
  fclose(fp) ;
  
  
  free(separator) ;
  free(spaces) ;
  free(current_line) ;
  free(current_string) ;
  
  return ;
}
    
    
  
void save_as_csv(int item_idx) {
  /** Export all operations registered in a comma separated values file. 
   * *******************************************************************/
  
  int c ;
  
  FILE *fp ;
  
  errno=0 ;  
  
  if  ( (fp=fopen(saving_settings.filepath,"w")) == NULL ) {
    cannot_export_file_error_message_dialog(saving_settings.filepath,strerror(errno)) ;
    return ; 
  }
  
  
  char *current_string=calloc(128+2,sizeof(char)) ;
  char *current_line=calloc(256+2,sizeof(char)) ;
  
  for (c=0 ; c < item_idx ; c++) {
    /** Write every item to file **/
    
    memset(current_string,'\0',128+2) ;  
    
    set_current_string(&save_operation[c].operande_1,current_string,1) ;
    
    sprintf(current_line,"%s,",current_string) ;
    
    fwrite(current_line,sizeof(char),strlen(current_line),fp);
    
    memset(current_string,'\0',128+2) ;
    memset(current_line,'\0',256+2) ;
    
    set_current_string(&save_operation[c].operande_2,current_string,2) ;
    
    if ( save_operation[c].current_operator == '+' ) {
      fwrite("+,",sizeof(char),strlen("+,"),fp) ;
    }
    else if ( save_operation[c].current_operator == '-' ) {
      fwrite("-,",sizeof(char),strlen("-,"),fp) ;
    }
    else if ( save_operation[c].current_operator == '*' ) {
      fwrite("×,",sizeof(char),strlen("×,"),fp) ;
    }
    else if ( save_operation[c].current_operator == '/' ) {
      fwrite("÷,",sizeof(char),strlen("÷,"),fp) ;
    }
    else if ( save_operation[c].current_operator == '%' ) {
      fwrite("%,",sizeof(char),strlen("%,"),fp) ;
    }
    else if ( save_operation[c].current_operator == '^' ) {
      fwrite("^,",sizeof(char),strlen("^,"),fp) ;
    }
    
    sprintf(current_line,"%s,",current_string) ;
    fwrite(current_line,sizeof(char),strlen(current_line),fp);
    
    memset(current_string,'\0',128+2) ;
    memset(current_line,'\0',256+2) ;
    
    set_current_string(&save_operation[c].result,current_string,3) ;
    
    
    sprintf(current_line,"=, %s\n",current_string) ;
    fwrite(current_line,sizeof(char),strlen(current_line),fp);
        
    fflush(fp) ;
  }
  
  fflush(fp) ;
  fclose(fp) ;
  
  
  free(current_line) ;
  free(current_string) ;
  
  return ;
}

void save_as_html(int item_idx) {
  /** Export all operations registered in a html file. 
   * *************************************************/
  
  int c ;
  
  FILE *fp ;
  
  errno=0 ;  
  
  if  ( (fp=fopen(saving_settings.filepath,"w")) == NULL ) {
    cannot_export_file_error_message_dialog(saving_settings.filepath,strerror(errno)) ;
    return ; // Set a error message dialog !!!
  }
  
  
  
  
  char *current_string=calloc(128+2,sizeof(char)) ;
  char *current_line=calloc(256+2,sizeof(char)) ;
  
  
  /** Write the HTML header in relationship to the wanted settings. **/ 
  fwrite("<!DOCTYPE html>\n<html lang=\'en\'>\n",sizeof(char),strlen("<!DOCTYPE html>\n<html lang=\'en\'>\n"),fp) ;
  
  sprintf(current_line,"<title>%s</title>\n<meta charset=\'utf-8\'>\n<head>\n<style>\n",(saving_settings.display_title) ? saving_settings.title : "") ;
  
  fwrite(current_line,sizeof(char),strlen(current_line),fp );
  
  memset(current_line,'\0',256+2) ;
  
  sprintf(current_line,"body\t{ font-family : \"%s\" ; font-size : %dpx ; background-color : %s ; color : %s ; font-weight : %s ; font-style : %s ; }\nh1\t{ text-decoration : underline ; }\n",html_settings.fontname,html_settings.font_size,html_settings.bg_color,html_settings.fg_color,(html_settings.bold) ? "bold" : "none",(html_settings.italic) ? "italic" : "none") ;  
  fwrite(current_line,sizeof(char),strlen(current_line),fp );
  
  memset(current_line,'\0',256+2) ;
  
  sprintf(current_line,"table\t{ text-align : center ; border: %s %dpx %s ; border-collapse : %s ; }\n",html_settings.border_color,html_settings.border_size,html_settings.border_style,html_settings.border_type) ;
  
  fwrite(current_line,sizeof(char),strlen(current_line),fp );
  
  memset(current_line,'\0',256+2) ;
  
  sprintf(current_line,"td\t{ text-align : center ; border: %s %dpx %s ; padding : %dpx ;}\n</style>\n</head>\n<body>\n",html_settings.border_color,html_settings.border_size,html_settings.border_style, (int) round(html_settings.font_size / 2)) ;
  
  fwrite(current_line,sizeof(char),strlen(current_line),fp );
  
  memset(current_line,'\0',256+2) ;
  
  
  /** Write the HTML body title and the table header cells in relationship to the wanted settings. **/ 
  sprintf(current_line,"<h1 align=\"center\">%s</h1>\n<br>\n<table align=\"center\">\n<tr>\n<td>Operand 1</td><td>Sign</td><td>Operand 2</td><td>Equal</td><td>Result</td>\n</tr>\n",(saving_settings.display_title) ? saving_settings.title : "")  ;
  
  fwrite(current_line,sizeof(char),strlen(current_line),fp );
  
  memset(current_line,'\0',256+2) ;
  
  for (c=0 ; c < item_idx ; c++) {
    /** Write all operations items to file in an table. **/
    
    memset(current_string,'\0',128+2) ;
      
    
    set_current_string(&save_operation[c].operande_1,current_string,1) ;
    
    sprintf(current_line,"<tr>\n<td>%s</td>",current_string) ;
    
    fwrite(current_line,sizeof(char),strlen(current_line),fp);
    
    memset(current_string,'\0',128+2) ;
    memset(current_line,'\0',256+2) ;
    
    set_current_string(&save_operation[c].operande_2,current_string,2) ;
    
    if ( save_operation[c].current_operator == '+' ) {
      fwrite("<td>+</td>",sizeof(char),strlen("<td>+</td>"),fp) ;
    }
    else if ( save_operation[c].current_operator == '-' ) {
      fwrite("<td>-</td>",sizeof(char),strlen("<td>-</td>"),fp) ;
    }
    else if ( save_operation[c].current_operator == '*' ) {
      fwrite("<td>×</td>",sizeof(char),strlen("<td>×</td>"),fp) ;
    }
    else if ( save_operation[c].current_operator == '/' ) {
      fwrite("<td>÷</td>",sizeof(char),strlen("<td>÷</td>"),fp) ;
    }
    else if ( save_operation[c].current_operator == '%' ) {
      fwrite("<td>%</td>",sizeof(char),strlen("<td>%</td>"),fp) ;
    }
    else if ( save_operation[c].current_operator == '^' ) {
      fwrite("<td>^</td>",sizeof(char),strlen("<td>^</td>"),fp) ;
    }
    
    sprintf(current_line,"<td>%s</td><td>=</td>",current_string) ;
    fwrite(current_line,sizeof(char),strlen(current_line),fp);
    
    memset(current_string,'\0',128+2) ;
    memset(current_line,'\0',256+2) ;
    
    set_current_string(&save_operation[c].result,current_string,3) ;
    
    
    sprintf(current_line,"<td>%s</td>\n</tr>\n",current_string) ;
    fwrite(current_line,sizeof(char),strlen(current_line),fp);
    
    
    fflush(fp) ;
  }
  
  fwrite("</table>\n</body>\n</html>\n",sizeof(char),strlen("</table>\n</body>\n</html>\n"),fp );
  
  fflush(fp) ;
  fclose(fp) ;
  
  
  free(current_line) ;
  free(current_string) ;
  
  return ;
}


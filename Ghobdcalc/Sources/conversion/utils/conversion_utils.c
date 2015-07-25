/*
 * hobdcalc 
 * Copyright (C) 2014 Bruggemann Eddie.
 * 
 * This file is part of hobdcalc.
 * hobdcalc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * hobdcalc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with hobdcalc. If not, see <http://www.gnu.org/licenses/>
 * 
 ************************************************************************************/


enum {HEX_A=10,HEX_B,HEX_C,HEX_D,HEX_E,HEX_F} ;
enum {HEX_0=0,HEX_1,HEX_2,HEX_3,HEX_4,HEX_5,HEX_6,HEX_7,HEX_8,HEX_9} ;

int get_digit(int c) {
  
  /** Return the value for char if HEXADECIMAL else for getting the integer value from base */
  char res ;
  res=(char) c ;
  if ((res == 'F') || (res == 'f')) {
    return HEX_F ;
  }
  else if ((res == 'E') || (res == 'e')){
    return HEX_E ;
  }
  else if ((res == 'D') || (res == 'd')) {
    return HEX_D ;
  }
  else if ((res == 'C') || (res == 'c')) {
    return HEX_C ;
  }
  else if ((res == 'B') || (res == 'b')) {
    return HEX_B ;
  }
  else if ((res == 'A') || (res == 'a')) {
    return HEX_A ;
  }
  else if (res == '9') {
    return HEX_9 ;
  }
  else if (res == '8') {
    return HEX_8 ;
  }
  else if (res == '7') {
    return HEX_7 ;
  }
  else if (res == '6') {
    return HEX_6 ;
  }
  else if (res == '5') {
    return HEX_5 ;
  }
  else if (res == '4') {
    return HEX_4 ;
  }
  else if (res == '3') {
    return HEX_3 ;
  }
  else if (res == '2') {
    return HEX_2 ;
  }
  else if (res == '1') {
    return HEX_1 ;
  }
  else if (res == '0') {
    return HEX_0 ;
  }
  return -1 ;
  
}

char set_digit(int c) {
  /** Return the char if HEXADECIMAL else for setting the integer value from base */
  if (c == 15) {
    return 'F' ;
  }
  else if (c == 14){
    return 'E' ;
  }
  else if (c== 13) {
    return 'D' ;
  }
  else if (c == 12) {
    return 'C' ;
  }
  else if (c == 11) {
    return 'B' ;
  }
  else if (c == 10) {
    return 'A' ;
  }
  else if (c == 9) {
    return '9' ;
  }
  else if (c == 8) {
    return '8' ;
  }
  else if (c == 7) {
    return '7' ;
  }
  else if (c == 6) {
    return '6' ;
  }
  else if (c == 5) {
    return '5' ;
  }
  else if (c == 4) {
    return '4' ;
  }
  else if (c == 3) {
    return '3' ;
  }
  else if (c == 2) {
    return '2' ;
  }
  else if (c == 1) {
    return '1' ;
  }
  else if (c == 0) {
    return '0' ;
  }
  return -1 ;
  
}


void splitter(char *string,char *res_int,char *res_float) {
  char *str_to_split=malloc(strlen(string)+1) ;
  strcpy(str_to_split,string) ;
  char *token=NULL ;
  int part=0 ;
  
  while (str_to_split != NULL) {
    token=strtok(str_to_split,".") ;
    if (token == NULL) {
      break ;
    }
    else {
      if ( part == 0) { 
        strcpy(res_int,token) ;
        part=1 ;
	str_to_split += strlen(token)+1 ;
	continue ;
      }
      else if (part == 1) {
        strcpy(res_float,token) ;
        str_to_split=NULL ;	
      }
      
      
    }
  }
  
  str_to_split=NULL ;
  return ;
}

long double string_to_long_double(char *input) {
  
  
  long double res_tmp ;
  long double res_rounded ;
  
  long double cc ;
  
  int8_t c ;
  
  long double fp_exp ;
  
  char *ptr_float_point ;
  
  _Bool is_negativ = false ;
  
  char *integer_part_str=calloc(32,sizeof(char)) ;
  char *float_part_str=calloc(32,sizeof(char)) ;
  char *res_string=calloc(32,sizeof(char)) ;
  
  
  if (input[0] == '-') {
    input++ ;
    is_negativ=true ;
  }
  
  strcpy(integer_part_str,input) ;
  
  strcpy(float_part_str,input) ;
  
  
  
  ptr_float_point=strchr(input,'.') ;
  
  
  integer_part_str[ptr_float_point-input]='\0' ; 
  
  
  res_tmp = 0.0 ;
  
  for (c=(int) strlen(integer_part_str)-1, cc=1 ; c >= 0 ; c--,cc *= 10) {
    res_tmp += ((int) (integer_part_str[c] - 48) * cc) ;
    
    float_part_str++ ;
    
    if (c == 0) {
      float_part_str++ ; 
      break ;
    }
    
  }
  
  
  for (c=0, fp_exp=0.10000000000000000 ; c < (int) strlen(float_part_str) ; c++, fp_exp /= 10.0 ) {
    char *exponent_str=calloc(32,sizeof(char)) ;
    
    sprintf(exponent_str,"%.*Lf",c+1,fp_exp) ;
   
    sscanf(exponent_str,"%Lf",&fp_exp) ;
    
    res_tmp += ((int) (float_part_str[c] - 48) * fp_exp) ;
    
    free(exponent_str) ;
  }
  
  sprintf(res_string,"%.*Lf",(int) strlen(float_part_str),res_tmp) ;
    
    
  sscanf(res_string,"%Lf",&res_rounded) ;
  
  for (c=(int) strlen(integer_part_str)-1 ; c >= 0 ; c--) { 
    float_part_str-- ;
    if (c == 0) {
      float_part_str-- ; 
      break ;
    }
  }
  
  
  
  free(integer_part_str) ;
  free(float_part_str) ;
  free(res_string) ;
  
  if (is_negativ) {
    res_rounded = -res_rounded ;
    input-- ;
  }
  
  
  return res_rounded ;
}
  


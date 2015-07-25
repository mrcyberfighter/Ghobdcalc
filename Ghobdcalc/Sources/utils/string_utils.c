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

void exchange_comma_and_float_point(char *string) {
  /** Exchange the decimal symbol comming from the GUI string in relationship to the value of the setlocale() setting LC_NUMERIC 
   *  from the local settings set by GTK at initialisation.
   *  If the local settings provide an comma as separator (char ',') he is exchange to an point.
   *****************************************************************************************************************************/
  
  char *ptr_floating_point ;
  
  if ( (ptr_floating_point=strchr(string,',')) != NULL) {
    string[ptr_floating_point-string]='.' ;
  }
  
  return ;
}

_Bool is_string_float(const char *string) {
  /** Return if the given string represent an float value.
   *  The given string must be normalise with the exchange_comma_and_float_point() function before.
   * **********************************************************************************************/
  if (strchr(string,'.') != NULL) {
    return true ;
  }
  else {
    return false ;
  }
}


long long convert_input_to_int(char *input_string) {
  /** Convert the given string representing any value in base [ 2 | 8 | 16 ]
   *  to an integer value and return it.
   *  In relationship to the current base.
   * *********************************************************************/
  long long res ;
  
  switch (operations.current_base) {
    case 2 :
      res=bintoint(input_string)       ;  /** convert from binar base to decimal basis:             sea the ../conversion/int_bin/calc_int_bin.c file. */ 
      break ;
    case 8 :
      res=octtoint(input_string)       ;  /** convert from octal base to decimal basis:             sea the ../conversion/int_oct/calc_int_oct.c file. */ 
      break ;
    case 10 :  
      res=strtoll(input_string,NULL,0) ;  /** convert an string to an long long type value                                                          */ 
      break ;  
    case 16 :
      res=hextoint(input_string)       ;  /** convert from hexadecimal base to decimal basis:       sea the ../conversion/int_hex/calc_int_hex.c file. */ 
      break ;
  }
  
  return res ;
}

long double convert_input_to_float(char *input_string) {
  /** Convert given string representing any value in base [ 2 | 8 | 16 ]
   *  to an float value and return it.
   *  In relationship to the current base. 
   * ********************************************************************/
  long double res ;
  
  switch (operations.current_base) {
    case 2 :
      res=binfloattofloat(input_string) ;  /** convert from binar base to decimal basis :           sea the ../conversion/float_to_bin/float_bin.c file */
      break ;
    case 8 :
      res=octfloattofloat(input_string) ;  /** convert from octal base to decimal basis:            sea the ../conversion/float_to_oct/float_oct.c file */
      break ;
    case 10 :
      res=strtold(input_string,NULL)    ;  /** convert an string to the an long double type value                                                    */
      break ;
    case 16 :
      res=hexfloattofloat(input_string) ;  /** convert from hexadecimal base to decimal basis:      sea the ../conversion/float_to_hex/float_hex.c file */
      break ;
  }
  
  return res ;
}

void convert_int_to_base(long long input,char *output_string,int8_t output_base) {
  /** Convert the integer input value to an string 
   *  representing an value in base [ 2 | 8 | 16 ].
   * *********************************************************/
  
  switch (output_base) {
    case 2 :
      inttobin(input,output_string) ;  /** convert from decimal base to binar basis:                sea the ../conversion/int_bin/int_bin.c file. */  
      break ;
    case 8 :
      inttooct(input,output_string) ;  /** convert from decimal base to octal basis:                sea the ../conversion/int_oct/int_oct.c file. */  
      break ;
    case 16 :
      inttohex(input,output_string) ;  /** convert from decimal base to hexadeimal basis:           sea the ../conversion/int_hex/int_hex.c file. */  
      break ;
  }
  
  return ;
}

void convert_float_to_base(long double input,char *output_string,int8_t output_base) {
  /** Convert the float input value to an string 
   *  representing an value in base [ 2 | 8 | 16 ].
   * *********************************************************/
  
  switch (output_base) {
    case 2 :
      floattobinfloat(input,output_string) ;  /** convert from decimal base to binar basis :        sea the ../conversion/float_to_bin/float_bin.c file */
      break ;
    case 8 :
      floattooctfloat(input,output_string) ;  /** convert from decimal base to octal basis:         sea the ../conversion/float_to_oct/float_oct.c file */
      break ;  
    case 16 :
      floattohexfloat(input,output_string) ;  /** convert from hexadecimal base to decimal basis:   sea the ../conversion/float_to_hex/float_hex.c file */
      break ;
  }
  
  return ;
}

_Bool strip_zero(char *input) {
  /** Strip unwanted zeros upto the floating-point in case he is reach, he is removed and the result is convert to an integer 
   *  and a true value is returned marking the conversion take place. 
   * *************************************************************************************************************************/
  unsigned int c ;
  for (c=strlen(input)-1 ; input[c] == '0' ; c-- ) {
    input[c]='\0' ;
  }
  if (input[c] == '.' ) {
    input[c]='\0' ;
    return true ;
  }
  return false ;
}

void strip_to_int(char *input) {
  /** Strip unwanted zeros upto the floating-point. 
   * **********************************************/
  unsigned int c ;
  for (c=strlen(input)-1 ; input[c] != '.' ; c-- ) {
    input[c]='\0' ;
  }
  
  
  input[c++]='\0' ;
  
  
  return ;
}

void erase_zero_from_result(void) {
  /** Strip unwanted zeros from the result container operand string upto the floating-point 
   *  in case he is reach, he is removed and the result is convert to an integer.
   ****************************************************************************************/
  unsigned int c ;
  for (c=strlen(operations.result.operande_string)-1 ; operations.result.operande_string[c] == '0' ; c-- ) {
    operations.result.operande_string[c]='\0' ;
  }
  if (operations.result.operande_string[c] == '.' || operations.result.operande_string[c] == ',' ) {
    operations.result.operande_string[c]='\0' ;
    operations.result.operande_is_float=false ;
  }
  
}

      
      
   

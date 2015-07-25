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

#define IS_DEC_BASE (operations.current_base == 10)

#define BUF_SIZE 128

_Bool is_zero_division_error(void) {
  /** Check if the second operand value is equal to zero 
   *  and is called in case the operation is an division.
   * ****************************************************/
  
  if (! operations.operande_2.operande_is_float ) {
    if (operations.operande_2.operande_digit.operande_int == 0) {
      sprintf(operations.result.operande_string,"Zero division error !!!") ;
      return true ;
    }
  }
  else {
    if ( operations.operande_2.operande_digit.operande_float == 0.0 ) {
      sprintf(operations.result.operande_string,"Zero division error !!!") ;
      return true ;
    }
  }
  return false ;
}
    
  

_Bool is_negativ(char *input) {
  /** Simple check is the value is negativ by checking the value of the first
   *  character from the string given as argument.
   * *************************************************************************/
  
  if (input[0] == '-') {
    return true ;
  }
  return false ;
}

void fill_result_structure(void) {
  /** This function fill the operations structure result item,
   *  in relationship to the computed result value from the operation,
   *  with filling every base string values.
   * *****************************************************************/
  
  char *output=calloc(128,sizeof(char)) ;
  
  
  if (operations.result.operande_is_float) {

  
    floattobinfloat(operations.result.operande_digit.operande_float,output) ;
    output[127]='\0' ;
    exchange_comma_and_float_point(output) ;
    
    
    strip_zero(output) ;
    strcpy(operations.result.operande_bin_str,output) ;
    
    
    memset(output,'\0',128) ;
    
    floattooctfloat(operations.result.operande_digit.operande_float,output) ;
    output[127]='\0' ;
    exchange_comma_and_float_point(output) ;
    strip_zero(output) ;
    strcpy(operations.result.operande_oct_str,output) ;
    
    memset(output,'\0',128) ;
    
    
    
    /* We must find the right  rounding (%.?lf) for exactly computation. */
    char *ptr_comma  ;
    char *operand_string=calloc(128,sizeof(char)) ;
    
    sprintf(operand_string,"%.15lf",(double) operations.result.operande_digit.operande_float) ;
    
    exchange_comma_and_float_point(operand_string) ;
    
    ptr_comma=strchr(operand_string,'.') ;
    
    
    
    operand_string[ptr_comma-operand_string]='\0' ;
    
        
    if ((int) strlen(operand_string) >= 15) {
      /* We must find the right  rounding (%.?lf) for exactly computation. */
      sprintf(operations.result.operande_dec_str,"%.4Lf",operations.result.operande_digit.operande_float) ;
    }
    else {
      sprintf(operations.result.operande_dec_str,"%.*lf",15 - (int) strlen(operand_string),(double) operations.result.operande_digit.operande_float) ;
    }
    
    free(operand_string) ;
    
    
    exchange_comma_and_float_point(operations.result.operande_dec_str) ;
    
    if ( strip_zero(operations.result.operande_dec_str) ) {
      operations.result.operande_is_float=false ;
    }
    
    memset(output,'\0',128) ;
    
    
    floattohexfloat(operations.result.operande_digit.operande_float,output) ;
    output[127]='\0' ;
    

    
    exchange_comma_and_float_point(output) ;
    strip_zero(output) ;
    strcpy(operations.result.operande_hex_str,output) ;
    
    
    
    switch (operations.current_base) {
      case 2 :
	strcpy(operations.result.operande_string,operations.result.operande_bin_str) ;
        break ;
      case 8 :
	strcpy(operations.result.operande_string,operations.result.operande_oct_str) ;
        break ;
      case 10 :
	strcpy(operations.result.operande_string,operations.result.operande_dec_str) ;
        break ;
      case 16 :
	strcpy(operations.result.operande_string,operations.result.operande_hex_str) ;
        break ;	
    }
    
    
  }
  
  else {
  
    inttobin(operations.result.operande_digit.operande_int,output) ;
    output[128]='\0' ;
    strcpy(operations.result.operande_bin_str,output) ;
    
    memset(output,'\0',128) ;
    
    inttooct(operations.result.operande_digit.operande_int,output) ;
    output[128]='\0' ;
    strcpy(operations.result.operande_oct_str,output) ;
    
    memset(output,'\0',128) ;
    
    
    if (! (operations.current_base == 10) ) {
      sprintf(output,"%Li",operations.result.operande_digit.operande_int) ;
      output[128]='\0' ;
      strcpy(operations.result.operande_dec_str,output) ;
      memset(output,'\0',128) ;
    }
    else {
      char *operand_string=calloc(128,sizeof(char)) ;
    
      sprintf(operand_string,"%Li",operations.result.operande_digit.operande_int) ;
      strcpy(operations.result.operande_dec_str,operand_string) ;
      
      free(operand_string) ;
    }
    
    
    
    
    inttohex(operations.result.operande_digit.operande_int,output) ;
    output[128]='\0' ;
    strcpy(operations.result.operande_hex_str,output) ;
    
    
    switch (operations.current_base) {
      case 2 :
	strcpy(operations.result.operande_string,operations.result.operande_bin_str) ;
        break ;
      case 8 :
	strcpy(operations.result.operande_string,operations.result.operande_oct_str) ;
        break ;
      case 10 :
	strcpy(operations.result.operande_string,operations.result.operande_dec_str) ;
        break ;
      case 16 :
	strcpy(operations.result.operande_string,operations.result.operande_hex_str) ;
        break ;	
    }
      
  }
  
  operations.result.operand_base=operations.current_base ;
  
  free(output) ;
  
  return ;
} 
  

void convert_float_to_base_string(long double to_compute,char *res_as_base) {
  
  /** Convert an float value in base 10 in any supported base [ 2 | 8 | 16 ] */
  
  switch (operations.current_base) {
    case 2 :
      floattobinfloat(to_compute,res_as_base) ;
      res_as_base[strlen(res_as_base)]='\0' ;
      break ;
    case 8 :
      floattooctfloat(to_compute,res_as_base) ;
      res_as_base[strlen(res_as_base)]='\0' ;
      break ;
    case 16 :
      floattohexfloat(to_compute,res_as_base) ;
      res_as_base[strlen(res_as_base)]='\0' ;
      break ;
  }
  return ;
}

void convert_int_to_base_string(long double to_compute,char *res_as_base) {
  /** Convert an integer value in base 10 in any supported base [ 2 | 8 | 16 ] */
  switch (operations.current_base) {
    case 2 :
      inttobin(to_compute,res_as_base) ;
      break ;
    case 8 :
      inttooct(to_compute,res_as_base) ;
      break ;
    case 16 :
      inttohex(to_compute,res_as_base) ;
      break ;
  }
  return ;
}

_Bool result_float_is_overflow(long double to_compute) {
  /** Check if the given float argument overflow or underflow the long double type */
  
  char *to_compute_as_str=calloc(128,sizeof(char)) ;
  sprintf(to_compute_as_str,"%.19Lf",to_compute) ;
  long double res ;
  errno=0 ;
  res=strtold(to_compute_as_str,NULL) ;
  
  if ( isnan(res) ) {
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    fprintf(stderr,"DEBUG %s -> case isnan\n",__func__) ;
    free(to_compute_as_str) ;
    return true ;
  }
  else if ( isinf(res) == 1 || isinf(res) == -1 ) {
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    fprintf(stderr,"DEBUG %s -> case isinf\n",__func__) ;
    free(to_compute_as_str) ;
    return true ;
  }
  
  if (errno == ERANGE ) {
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    fprintf(stderr,"DEBUG %s -> case 2\n",__func__) ;
    free(to_compute_as_str) ;
    return true ;
  }
  if ((res < 0) && (res <= LLONG_MIN)) {
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    fprintf(stderr,"DEBUG %s -> case 3\n",__func__) ;
    free(to_compute_as_str) ;
    return true ;
  }
  if ((res > 0) && (res >= LLONG_MAX)) {
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    fprintf(stderr,"DEBUG %s -> case 4\n",__func__) ;
    free(to_compute_as_str) ;
    return true ;
  }
  free(to_compute_as_str) ;
  return false ;
}

_Bool result_int_is_overflow(char *check_for_overflow) {
  /** Check if the given integer argument overflow or underflow the long long type */
  
  errno=0 ;
  
  if ( ((int) strlen(check_for_overflow)) > 19) {
    sprintf(operations.result.operande_string,"%s","value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( (strtoll(check_for_overflow,NULL,0) >= LLONG_MAX) || (strtoll(check_for_overflow,NULL,0) <= LLONG_MIN) || errno == ERANGE ) {
    sprintf(operations.result.operande_string,"%s","value out of range (underflow or overflow)") ;
    return true ;
  }
  
  return false ;
}


_Bool result_add_int_is_overflow(long long op1, long long op2) {
  /** Check if the given operands added overflow or underflow the long long type 
   *  By converting it to an long double string, calling strtoll() and check if errno contaions an error value.
   ************************************************************************************************************/
  
  char *to_compute_as_str=calloc(128,sizeof(char)) ;
  long double res_as_ld  = (long double) op1 + (long double) op2 ;
  
  
  sprintf(to_compute_as_str,"%Lf",res_as_ld) ;
  
  exchange_comma_and_float_point(to_compute_as_str) ;
  
  
  strip_to_int(to_compute_as_str) ;
   
  errno=0 ;
  
  if ( (strtoll(to_compute_as_str,NULL,0) >= LLONG_MAX) || (strtoll(to_compute_as_str,NULL,0) <= LLONG_MIN) || errno == ERANGE ) {
    sprintf(operations.result.operande_string,"%s","value out of range (underflow or overflow)") ;
    free(to_compute_as_str) ;
    fprintf(stdout,"%s -> case with strtoll oberflow detecting\n",__func__) ;
    return true ;
  }
  
  memset(to_compute_as_str,'\0',128) ;
  sprintf(to_compute_as_str,"%Li",op1 + op2) ;
  
  /** Here we check if the result sign correspond to the operand adding logic issue.
   *  Maybe not needed because the above check overflow the long long limit, and the work is done.
   ***********************************************************************************************/ 
  if ( ( is_negativ(operations.operande_1.operande_dec_str) &&  ! is_negativ(operations.operande_2.operande_dec_str) ) && ( llabs(op1) < llabs(op2) ) && is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( ( is_negativ(operations.operande_1.operande_dec_str) &&  ! is_negativ(operations.operande_2.operande_dec_str) ) && (llabs(op1) > llabs(op2) ) && ! is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( (! is_negativ(operations.operande_1.operande_dec_str) &&  is_negativ(operations.operande_2.operande_dec_str) ) && ( llabs(op1) < llabs(op2) ) && ! is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( (! is_negativ(operations.operande_1.operande_dec_str) &&  is_negativ(operations.operande_2.operande_dec_str) ) && (llabs(op1) > llabs(op2)) && is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( (is_negativ(operations.operande_1.operande_dec_str) &&  is_negativ(operations.operande_2.operande_dec_str) ) &&  ! is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( (! is_negativ(operations.operande_1.operande_dec_str) &&  ! is_negativ(operations.operande_2.operande_dec_str) ) &&  is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    return true ;
  }
 
  free(to_compute_as_str) ;
  return false ;
}

_Bool result_sub_int_is_overflow(long long op1, long long op2) {
  /** Check if the given operands subtract overflow or underflow the long long type 
   *  By converting it to an long double string, calling strtoll() and check if errno contaions an error value.
   ************************************************************************************************************/
  
  char *to_compute_as_str=calloc(128,sizeof(char)) ;
  long double res_as_ld  = (long double) op1 - (long double) op2 ;
    
  sprintf(to_compute_as_str,"%Lf",res_as_ld) ;
  
  exchange_comma_and_float_point(to_compute_as_str) ;
    
  strip_to_int(to_compute_as_str) ;
  
  
  errno=0 ;
  
  if ( (strtoll(to_compute_as_str,NULL,0) >= LLONG_MAX) || (strtoll(to_compute_as_str,NULL,0) <= LLONG_MIN) || errno == ERANGE ) {
    sprintf(operations.result.operande_string,"%s","value out of range (underflow or overflow)") ;
    free(to_compute_as_str) ;
    fprintf(stdout,"%s -> case with strtoll oberflow detecting\n",__func__) ;
    return true ;
  }
  
  memset(to_compute_as_str,'\0',128) ;
  sprintf(to_compute_as_str,"%Li",op1 - op2) ;
  
  
  /** Here we check if the result sign correspond to the operand substract logic issue.
   *  Maybe not needed because the above check overflow the long long limit, and the work is done.
   ***********************************************************************************************/ 
  if ( ( is_negativ(operations.operande_1.operande_dec_str) &&  ! is_negativ(operations.operande_2.operande_dec_str) ) && ! is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( ( ! is_negativ(operations.operande_1.operande_dec_str) &&  is_negativ(operations.operande_2.operande_dec_str) ) && is_negativ(to_compute_as_str) ) {
    fprintf(stdout,"case 2\n") ;
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( (! is_negativ(operations.operande_1.operande_dec_str) &&  ! is_negativ(operations.operande_2.operande_dec_str) ) && (llabs(op1) > llabs(op2)) && is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( (! is_negativ(operations.operande_1.operande_dec_str) &&  ! is_negativ(operations.operande_2.operande_dec_str) ) && (llabs(op1) < llabs(op2)) && ! is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( (is_negativ(operations.operande_1.operande_dec_str) &&  is_negativ(operations.operande_2.operande_dec_str) ) && (llabs(op1) > llabs(op2)) && is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    return true ;
  }
  else if ( (is_negativ(operations.operande_1.operande_dec_str) &&  is_negativ(operations.operande_2.operande_dec_str) ) && (llabs(op1) < llabs(op2)) && ! is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    return true ;
  }
  
  free(to_compute_as_str) ;
  
  
  return false ;
}

_Bool result_mul_int_is_overflow(long long op1, long long op2) {
  /** Check if the given operands multiplication overflow or underflow the long long type 
   *  By converting it to an long double string, calling strtoll() and check if errno contaions an error value.
   ************************************************************************************************************/
  
  char *to_compute_as_str=calloc(128,sizeof(char)) ;
  long double res_as_ld  = (long double) op1 * (long double) op2 ;
  
  
  sprintf(to_compute_as_str,"%Lf",res_as_ld) ;
  
  exchange_comma_and_float_point(to_compute_as_str) ;
  
  
  strip_to_int(to_compute_as_str) ;
    
  errno=0 ;
  
  if ( (strtoll(to_compute_as_str,NULL,0) >= LLONG_MAX) || (strtoll(to_compute_as_str,NULL,0) <= LLONG_MIN) || errno == ERANGE ) {
    sprintf(operations.result.operande_string,"%s","value out of range (underflow or overflow)") ;
    free(to_compute_as_str) ;
    return true ;
  }
  
  memset(to_compute_as_str,'\0',128) ;
  sprintf(to_compute_as_str,"%Li",op1 * op2) ;
  
  /** Here we check if the result sign correspond to the operand multiplying logic issue.
   *  Maybe not needed because the above check overflow the long long limit, and the work is done.
   ***********************************************************************************************/ 
  if ( ( is_negativ(operations.operande_1.operande_dec_str) &&  ! is_negativ(operations.operande_2.operande_dec_str) ) && ! is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"%s","value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( ( ! is_negativ(operations.operande_1.operande_dec_str) &&  is_negativ(operations.operande_2.operande_dec_str) ) && ! is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"%s","value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( (! is_negativ(operations.operande_1.operande_dec_str) &&  ! is_negativ(operations.operande_2.operande_dec_str) ) && is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"%s","value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( (is_negativ(operations.operande_1.operande_dec_str) &&  is_negativ(operations.operande_2.operande_dec_str) ) && is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"%s","value out of range (underflow or overflow)") ;
    return true ;
  }
  
  free(to_compute_as_str) ;
  
  return false ;
}

_Bool result_div_int_is_overflow(long long op1, long long op2) {
  /** Check if the given operands division overflow or underflow the long long type 
   *  By converting it to an long double string, calling strtoll() and check if errno contaions an error value.
   ************************************************************************************************************/
  
  char *to_compute_as_str=calloc(128,sizeof(char)) ;
  long double res_as_ld  = (long double) op1 / (long double) op2 ;
  
  
  sprintf(to_compute_as_str,"%Lf",res_as_ld) ;
  
  exchange_comma_and_float_point(to_compute_as_str) ;
  
  strip_to_int(to_compute_as_str) ;
  
  errno=0 ;
  
  if ( (strtoll(to_compute_as_str,NULL,0) >= LLONG_MAX) || (strtoll(to_compute_as_str,NULL,0) <= LLONG_MIN) || errno == ERANGE ) {
    sprintf(operations.result.operande_string,"%s","value out of range (underflow or overflow)") ;
    free(to_compute_as_str) ;
    return true ;
  }
  
  memset(to_compute_as_str,'\0',128) ;
  sprintf(to_compute_as_str,"%Li",op1 / op2) ;
  
  /** Here we check if the result sign correspond to the operand dividing logic issue.
   *  Maybe not needed because the above check overflow the long long limit, and the work is done.
   ***********************************************************************************************/ 
  if ( ( is_negativ(operations.operande_1.operande_dec_str) &&  ! is_negativ(operations.operande_2.operande_dec_str) )  && (! is_negativ(to_compute_as_str)) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( ( ! is_negativ(operations.operande_1.operande_dec_str) &&  is_negativ(operations.operande_2.operande_dec_str) ) && ! is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( (! is_negativ(operations.operande_1.operande_dec_str) &&  ! is_negativ(operations.operande_2.operande_dec_str) ) && is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    return true ;
  }
  else if ( (is_negativ(operations.operande_1.operande_dec_str) &&  is_negativ(operations.operande_2.operande_dec_str) ) && is_negativ(to_compute_as_str) ) {
    free(to_compute_as_str) ;
    sprintf(operations.result.operande_string,"value out of range (underflow or overflow)") ;
    return true ;
  }
  
  free(to_compute_as_str) ;
  return false ;
}

      

_Bool calc_computing_result(int8_t opcode) {
  
  /** This function compute the result field from the Operation structure
   *  In relation ship to:
   *  -) The operation type [addition | substraction | multiplication | division | modulo ]  
   *  -) The operande datatype [ decimal | hexadecimal | octal | binar ]
   *  -) The operandes value type [ integer | float ]
   * **************************************************************************************/
  
  char commands_signs[5]={'+','-','*','/','%'} ;                /** Operator table                  */
  
  unsigned char current_operator = commands_signs[opcode] ;     /** Getting the current operator   */
  
  _Bool is_result_integer=false ;
  
  
  switch(current_operator) {
    case '+' :
         
      if (operations.operande_1.operande_is_float && (! operations.operande_2.operande_is_float) ) {
	
	
	
	char *check_result=calloc(128,sizeof(char)) ;
	
	sprintf(check_result,"%.19Lf",operations.operande_1.operande_digit.operande_float + operations.operande_2.operande_digit.operande_int) ;
	
	exchange_comma_and_float_point(check_result) ;
	
	if ( strip_zero(check_result) ) {
	  is_result_integer=true ;
	}
	
	
	
	
	if (! is_result_integer) {
	
	    if (result_float_is_overflow(operations.operande_1.operande_digit.operande_float + operations.operande_2.operande_digit.operande_int) ){
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    }  
	    
	    
	    operations.result.operande_is_float=true ;
	    operations.result.operande_digit.operande_float= operations.operande_1.operande_digit.operande_float + operations.operande_2.operande_digit.operande_int ;
	    
	}
	    
	else {
	  
	  if (result_add_int_is_overflow(operations.operande_1.operande_digit.operande_float, operations.operande_2.operande_digit.operande_int) ) {
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    }
	    
	    
	    operations.result.operande_is_float=false ;
	    operations.result.operande_digit.operande_int= operations.operande_1.operande_digit.operande_float + operations.operande_2.operande_digit.operande_int ;
	  }
	 
	 
	fill_result_structure()  ;
	
	operations.current_operator='+' ;
	
	return true ;
      }
      
      else if ( (! operations.operande_1.operande_is_float) && operations.operande_2.operande_is_float ) {
	
	char *check_result=calloc(128,sizeof(char)) ;
	
	sprintf(check_result,"%.19Lf",operations.operande_1.operande_digit.operande_int + operations.operande_2.operande_digit.operande_float) ;
	
	exchange_comma_and_float_point(check_result) ;
	
	if ( strip_zero(check_result) ) {
	  is_result_integer=true ;
	}
	
	
	if (! is_result_integer) {
	
	      if (result_float_is_overflow(operations.operande_1.operande_digit.operande_int + operations.operande_2.operande_digit.operande_float) ) {
		/** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
		free(check_result) ;
		return false ;
	      }
	      
	      
	      operations.result.operande_is_float=true ;
	      operations.result.operande_digit.operande_float=operations.operande_1.operande_digit.operande_int + operations.operande_2.operande_digit.operande_float ;
	      
	}
	
	else {
	    if ( result_int_is_overflow(check_result) ) {
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    } 
	  
	    
	    if (result_add_int_is_overflow(operations.operande_1.operande_digit.operande_int, operations.operande_2.operande_digit.operande_float) ) {
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    }
	    
	    
	    operations.result.operande_is_float=false ;
	    operations.result.operande_digit.operande_int =  operations.operande_1.operande_digit.operande_int + operations.operande_2.operande_digit.operande_float ;
	  }
	
	free(check_result) ;
	
	fill_result_structure()  ;
	operations.current_operator='+' ;
	
	return true ;
      }
      
      else if ( operations.operande_1.operande_is_float && operations.operande_2.operande_is_float ) {
	
	char *check_result=calloc(128,sizeof(char)) ;
	
	sprintf(check_result,"%.19Lf",operations.operande_1.operande_digit.operande_float + operations.operande_2.operande_digit.operande_float) ;
	
	exchange_comma_and_float_point(check_result) ;
	
	if ( strip_zero(check_result) ) {
	  is_result_integer=true ;
	}
	
	
	if (! is_result_integer) {
	
	    if (result_float_is_overflow(operations.operande_1.operande_digit.operande_float + operations.operande_2.operande_digit.operande_float) ) {
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    }
	    
	    
	
	    operations.result.operande_is_float=true ;
	    operations.result.operande_digit.operande_float=operations.operande_1.operande_digit.operande_float + operations.operande_2.operande_digit.operande_float ;
	    
	
	}
	
	else {
	      if ( result_int_is_overflow(check_result) ) {
		/** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
		free(check_result) ;
		return false ;
	      } 
	  
	      
	     
	      operations.result.operande_is_float=false ;
	      operations.result.operande_digit.operande_int = operations.operande_1.operande_digit.operande_float + operations.operande_2.operande_digit.operande_float ;
	}
	
	free(check_result) ;
	
	fill_result_structure()  ;
	operations.current_operator='+' ;
	
	return true ;
      }
      
      else {
	
	
	if (result_add_int_is_overflow(operations.operande_1.operande_digit.operande_int, operations.operande_2.operande_digit.operande_int) ) {
	  /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	  return false ;
	}
	
	
	
	operations.result.operande_is_float=false ;
	operations.result.operande_digit.operande_int=operations.operande_1.operande_digit.operande_int + operations.operande_2.operande_digit.operande_int ;
	
	fill_result_structure() ;
	operations.current_operator='+' ;
	
	return true ;
      }
    
    case '-' :
      
      if (operations.operande_1.operande_is_float && (! operations.operande_2.operande_is_float) ) {
	
	char *check_result=calloc(128,sizeof(char)) ;
	
	sprintf(check_result,"%.19Lf",operations.operande_1.operande_digit.operande_float - operations.operande_2.operande_digit.operande_int) ;
	
	exchange_comma_and_float_point(check_result) ;
	
	if ( strip_zero(check_result) ) {
	  is_result_integer=true ;
	}
	
	
	if (! is_result_integer) {
	  
	
	    if (result_float_is_overflow(operations.operande_1.operande_digit.operande_float - operations.operande_2.operande_digit.operande_int) ){
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    }
	    
	    
	    
	    operations.result.operande_is_float=true ;
	    operations.result.operande_digit.operande_float= operations.operande_1.operande_digit.operande_float -  operations.operande_2.operande_digit.operande_int ;
	    
	}
	
	else {
	    
	    if ( result_int_is_overflow(check_result) ) {
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    } 
	    
	    if (result_sub_int_is_overflow(operations.operande_1.operande_digit.operande_float, operations.operande_2.operande_digit.operande_int) ) {
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    }
	    
	    
	    operations.result.operande_is_float=false ;
	    operations.result.operande_digit.operande_int=operations.operande_1.operande_digit.operande_float - operations.operande_2.operande_digit.operande_int ;
	}
	
	free(check_result) ;
	
	fill_result_structure() ;
	operations.current_operator='-' ;
	
	return true ;
      }
      
      else if ( (! operations.operande_1.operande_is_float) && operations.operande_2.operande_is_float ) {
	
	char *check_result=calloc(128,sizeof(char)) ;
	
	sprintf(check_result,"%.19Lf",operations.operande_1.operande_digit.operande_int - operations.operande_2.operande_digit.operande_float) ;
	
	exchange_comma_and_float_point(check_result) ;
	
	if ( strip_zero(check_result) ) {
	  is_result_integer=true ;
	}
	
	
	if (! is_result_integer) {
	
	    if (result_float_is_overflow(operations.operande_1.operande_digit.operande_int - operations.operande_2.operande_digit.operande_float) ) {
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    }
	    
	    
	    operations.result.operande_is_float=true ;
	    operations.result.operande_digit.operande_float= operations.operande_1.operande_digit.operande_int - operations.operande_2.operande_digit.operande_float ;
	    
	}
	
	else {
	    
	    if ( result_int_is_overflow(check_result) ) {
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    } 
	    
	    if (result_sub_int_is_overflow(operations.operande_1.operande_digit.operande_int, operations.operande_2.operande_digit.operande_float) ) {
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    }
	    
	    
	    
	    operations.result.operande_is_float=false ;
	    operations.result.operande_digit.operande_int= operations.operande_1.operande_digit.operande_int - operations.operande_2.operande_digit.operande_float ;
	
	  
	}
	
	free(check_result) ;
	
	fill_result_structure()  ; 
	operations.current_operator='-' ;
	
	return true ;
      }
      
      else if ( operations.operande_1.operande_is_float && operations.operande_2.operande_is_float ) {
	
	char *check_result=calloc(128,sizeof(char)) ;
	
	sprintf(check_result,"%.19Lf",operations.operande_1.operande_digit.operande_float - operations.operande_2.operande_digit.operande_float) ;
	
	exchange_comma_and_float_point(check_result) ;
	
	if ( strip_zero(check_result) ) {
	  is_result_integer=true ;
	}
	
	
	if (! is_result_integer) {
	
	    if (result_float_is_overflow(operations.operande_1.operande_digit.operande_float - operations.operande_2.operande_digit.operande_float) ) {
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    }
	    
	    
	    
	    operations.result.operande_is_float=true ;
	    operations.result.operande_digit.operande_float=operations.operande_1.operande_digit.operande_float - operations.operande_2.operande_digit.operande_float ;
	    
	}
	
	else {
	      
	      if ( result_int_is_overflow(check_result) ) {
		/** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
		free(check_result) ;
		return false ;
	      } 
	   
	      if (result_sub_int_is_overflow(operations.operande_1.operande_digit.operande_float, operations.operande_2.operande_digit.operande_float) ) {
		/** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
		free(check_result) ;
		return false ;
	      }
	      
	      
	      
	      operations.result.operande_is_float=false ;
	      operations.result.operande_digit.operande_int=operations.operande_1.operande_digit.operande_float - operations.operande_2.operande_digit.operande_float ;
	
	  
	}
	 
	free(check_result) ; 
	 
	fill_result_structure()  ;
	operations.current_operator='-' ;
	
	return true ;
      }
      
      else {
	
	if (result_sub_int_is_overflow(operations.operande_1.operande_digit.operande_int, operations.operande_2.operande_digit.operande_int) ) {
	  /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	  return false ;
	}
	
	
	operations.result.operande_is_float=false ;
	operations.result.operande_digit.operande_int=operations.operande_1.operande_digit.operande_int - operations.operande_2.operande_digit.operande_int ;
	
	fill_result_structure() ;
	operations.current_operator='-' ;
	
        return true ;
      }
    
    case '*' :
      
      if (operations.operande_1.operande_is_float && (! operations.operande_2.operande_is_float) ) {
	
	char *check_result=calloc(128,sizeof(char)) ;
	
	sprintf(check_result,"%.19Lf",operations.operande_1.operande_digit.operande_float * operations.operande_2.operande_digit.operande_int) ;
	
	exchange_comma_and_float_point(check_result) ;
	
	if ( strip_zero(check_result) ) {
	  is_result_integer=true ;
	}
	
	
	
	
	
	if (! is_result_integer) {
	
	    if (result_float_is_overflow(operations.operande_1.operande_digit.operande_float * operations.operande_2.operande_digit.operande_int) ){
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    }
	    
	    
	    operations.result.operande_is_float=true ;
	    
	    operations.result.operande_digit.operande_float= operations.operande_1.operande_digit.operande_float * operations.operande_2.operande_digit.operande_int ;
	    
	}
	
	else {
	  
	  if ( result_int_is_overflow(check_result) ) {
	    /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	    free(check_result) ;
	    return false ;
	  }
	  
	  if (result_mul_int_is_overflow(operations.operande_1.operande_digit.operande_float, operations.operande_2.operande_digit.operande_int) ) {
	    /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	    free(check_result) ;
	    return false ;
	  }
	  
	  
	  
	  operations.result.operande_is_float=false ;
	  operations.result.operande_digit.operande_int = operations.operande_1.operande_digit.operande_float * operations.operande_2.operande_digit.operande_int ;
	  
      }
	  
	free(check_result) ;  
	
 	fill_result_structure()  ;
	
	operations.current_operator='*' ;
	
	return true ;
      }
      
      else if ( (! operations.operande_1.operande_is_float) && operations.operande_2.operande_is_float ) {
	
	char *check_result=calloc(128,sizeof(char)) ;
	
	sprintf(check_result,"%.19Lf",operations.operande_1.operande_digit.operande_int * operations.operande_2.operande_digit.operande_float) ;
	
	exchange_comma_and_float_point(check_result) ;
	
	if ( strip_zero(check_result) ) {
	  is_result_integer=true ;
	}
	
	
	
	if (! is_result_integer) {
	
	    if (result_float_is_overflow(operations.operande_1.operande_digit.operande_int * operations.operande_2.operande_digit.operande_float) ) {
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    }
	    
	    
	    operations.result.operande_is_float=true ;
	    operations.result.operande_digit.operande_float= operations.operande_1.operande_digit.operande_int * operations.operande_2.operande_digit.operande_float ;
	    
	}
	
	else {
	      
	      if ( result_int_is_overflow(check_result) ) {
		/** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
		free(check_result) ;
		return false ;
	      }
	  
	      if (result_mul_int_is_overflow(operations.operande_1.operande_digit.operande_int,  operations.operande_2.operande_digit.operande_float) ) {
		/** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
		free(check_result) ;
		return false ;
	      }
	      
	      
	      operations.result.operande_is_float=false ;
	      operations.result.operande_digit.operande_int =  operations.operande_1.operande_digit.operande_int * operations.operande_2.operande_digit.operande_float ;
	
	}
	  
	free(check_result) ;  
	fill_result_structure()  ;
	operations.current_operator='*' ;
	
	return true ;
      }
      
      else if ( operations.operande_1.operande_is_float && operations.operande_2.operande_is_float ) {
	
	char *check_result=calloc(128,sizeof(char)) ;
	
	sprintf(check_result,"%.19Lf",operations.operande_1.operande_digit.operande_float * operations.operande_2.operande_digit.operande_float) ;
	
	exchange_comma_and_float_point(check_result) ;
	
	if ( strip_zero(check_result) ) {
	  is_result_integer=true ;
	}
	
	if (! is_result_integer) {
	
	    if (result_float_is_overflow(operations.operande_1.operande_digit.operande_float * operations.operande_2.operande_digit.operande_float) ) {
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    }
	    
	    
	    
	    operations.result.operande_is_float=true ;
	    operations.result.operande_digit.operande_float= operations.operande_1.operande_digit.operande_float * operations.operande_2.operande_digit.operande_float ;
	    
	}
	
	else {
	     
	    if ( result_int_is_overflow(check_result) ) {
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    }
	   
	    if (result_mul_int_is_overflow(operations.operande_1.operande_digit.operande_float, operations.operande_2.operande_digit.operande_float) ) {
	      /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	      free(check_result) ;
	      return false ;
	    }
	    
	    
	    operations.result.operande_is_float=false ;
	    operations.result.operande_digit.operande_int = operations.operande_1.operande_digit.operande_float * operations.operande_2.operande_digit.operande_float ;
	
      }
      
      free(check_result) ;
      
      fill_result_structure()  ;
      operations.current_operator='*' ;
      
      return true ;
      
      }
      
      else {
	
	if (result_mul_int_is_overflow(operations.operande_1.operande_digit.operande_int, operations.operande_2.operande_digit.operande_int) ) {
	  /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	  return false ;
	}
	
	
	operations.result.operande_is_float=false ;
	operations.result.operande_digit.operande_int=operations.operande_1.operande_digit.operande_int * operations.operande_2.operande_digit.operande_int ;
      
      
      fill_result_structure() ;
      operations.current_operator='*' ;
      
      return true ;
    }
    
    case '/' :
      
      if (operations.operande_1.operande_is_float && (! operations.operande_2.operande_is_float) ) {
	
	if ( is_zero_division_error() ) {
	  return false ;
	}
	
	if (result_float_is_overflow(operations.operande_1.operande_digit.operande_float / operations.operande_2.operande_digit.operande_int) ){
	  /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	  return false ;
	}
	
	
	
	
	
	operations.result.operande_is_float=true ;
	operations.result.operande_digit.operande_float=operations.operande_1.operande_digit.operande_float / operations.operande_2.operande_digit.operande_int ;
	
	fill_result_structure()  ;
	operations.current_operator='/' ;
	
	return true ;
      }
      
      else if ( (! operations.operande_1.operande_is_float) && operations.operande_2.operande_is_float ) {
	
	if ( is_zero_division_error() ) {
	  return false ;
	}
	
	if  ( ! operations.operande_2.operande_digit.operande_float ) {
	  return false ;
	}
	
	if (result_float_is_overflow(operations.operande_1.operande_digit.operande_int / operations.operande_2.operande_digit.operande_float) ) {
	  /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	  return false ;
	}
	
	
	
	operations.result.operande_is_float=true ;
	operations.result.operande_digit.operande_float= operations.operande_1.operande_digit.operande_int / operations.operande_2.operande_digit.operande_float ;
	
	fill_result_structure()  ;
	operations.current_operator='/' ;
	
	return true ;
      }
      
      else if ( operations.operande_1.operande_is_float && operations.operande_2.operande_is_float ) {
	
	if ( is_zero_division_error() ) {
	  return false ;
	}
	
	if  ( ! operations.operande_2.operande_digit.operande_float ) {
	  return false ;
	}
	
	if (result_float_is_overflow(operations.operande_1.operande_digit.operande_float / operations.operande_2.operande_digit.operande_float) ) {
	  /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	  return false ;
	}
	
	
	
	operations.result.operande_is_float=true ;
	operations.result.operande_digit.operande_float=operations.operande_1.operande_digit.operande_float / operations.operande_2.operande_digit.operande_float ;
	
	fill_result_structure()  ;
        operations.current_operator='/' ;
	
        return true ;
      }
      
      
      
      
      else {
	
	if ( is_zero_division_error() ) {
	  return false ;
	}
	
	long double op1_to_float ; 
	long double op2_to_float ; 
	
	op1_to_float = operations.operande_1.operande_digit.operande_int  ; // We not alter the first operand value in case of operator change and recomputing.
	op2_to_float = operations.operande_2.operande_digit.operande_int  ; // We not alter the second operand value in case of operator change and recomputing.
	
	
        char *check_result=calloc(128,sizeof(char)) ;
	
	sprintf(check_result,"%.19Lf",op1_to_float / op2_to_float ) ;
	
	exchange_comma_and_float_point(check_result) ;
	
	if ( strip_zero(check_result) ) {
	  is_result_integer=true ;
	  
	}
	
	
	if (! is_result_integer) {
	  
	  
	  operations.result.operande_is_float=true ;
	  operations.result.operande_digit.operande_float= op1_to_float / op2_to_float ;
	  
	}
	
	else {
	  
	  if ( result_int_is_overflow(check_result) ) {
	    /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	    free(check_result) ;
	    return false ;
	  } 
	  
	  if (result_div_int_is_overflow(operations.operande_1.operande_digit.operande_int, operations.operande_2.operande_digit.operande_int) ) {
	    /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	    free(check_result) ;
	    return false ;
	  }
	  
	  
	    
	    operations.result.operande_is_float=false ;
	    operations.result.operande_digit.operande_int= strtoll(check_result,NULL,0) ;
	}
	
	free(check_result) ;
	
	fill_result_structure()  ;
	operations.current_operator='/' ;
	
        return true ;
      }
    
    case '%' :
      
      if (operations.operande_1.operande_is_float && (! operations.operande_2.operande_is_float) ) {
	
	if (result_float_is_overflow(fmodl(operations.operande_1.operande_digit.operande_float,operations.operande_2.operande_digit.operande_int)) ) {
	  /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	  return false ;
	}
	
	
	
	operations.result.operande_is_float=true ;
	operations.result.operande_digit.operande_float=fmodl(operations.operande_1.operande_digit.operande_float, operations.operande_2.operande_digit.operande_int) ;
	fill_result_structure()  ;
	operations.current_operator='%' ;
	
	return true ;
      }
      
      else if ( (! operations.operande_1.operande_is_float) && operations.operande_2.operande_is_float ) {
	
	if (result_float_is_overflow(fmodl( operations.operande_1.operande_digit.operande_int, operations.operande_2.operande_digit.operande_float)) ) {
	  /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	  return false ;
	}
	
	
	
	operations.result.operande_is_float=true ;
	operations.result.operande_digit.operande_float=fmodl( operations.operande_1.operande_digit.operande_int, operations.operande_2.operande_digit.operande_float) ;
	
	fill_result_structure()  ;
	operations.current_operator='%' ;
	
	return true ;
      }
      
      else if ( operations.operande_1.operande_is_float && operations.operande_2.operande_is_float ) {
	
	if (result_float_is_overflow(fmodl(operations.operande_1.operande_digit.operande_float,operations.operande_2.operande_digit.operande_float)) ) {
	  /** Overflow and underflow check, from the result value, (Ghodbcalc is limited to 8 bytes) */
	  return false ;
	}
	
	
	operations.result.operande_is_float=true ;
	operations.result.operande_digit.operande_float=fmodl(operations.operande_1.operande_digit.operande_float,operations.operande_2.operande_digit.operande_float) ;
	
	fill_result_structure()  ;
	operations.current_operator='%' ;
	
	return true ;
      }
      
      else {
	
	operations.result.operande_is_float=false ;
	operations.result.operande_digit.operande_int=operations.operande_1.operande_digit.operande_int % operations.operande_2.operande_digit.operande_int ;
	
	fill_result_structure()  ;
	operations.current_operator='%' ;
	
        return true ;
      }
    }
    return false ;
}
      







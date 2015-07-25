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


#define CUR_BASE_IS_DEC (operations.current_base == 10)

#define BUF_SIZE 128

#define PI 3.141592653589793

void init_calculator(void) {
  
  /** Initialize the calculator by reserving memory for the operations container members by start. 
   * *********************************************************************************************/
  
  operations.operande_1.operande_string=calloc(128,sizeof(char)) ;

  operations.operande_1.operande_digit.operande_float=0.0 ;
  operations.operande_1.operande_digit.operande_int=0 ;
  
  operations.operande_1.operande_is_float=false ;

  operations.operande_1.operande_bin_str=calloc(128,sizeof(char)) ;
  operations.operande_1.operande_oct_str=calloc(128,sizeof(char)) ;
  operations.operande_1.operande_hex_str=calloc(128,sizeof(char)) ;
  operations.operande_1.operande_dec_str=calloc(128,sizeof(char)) ;
  


  operations.operande_2.operande_string=calloc(128,sizeof(char)) ;
  
  operations.operande_2.operande_digit.operande_float=0.0 ;
  operations.operande_2.operande_digit.operande_int=0 ;
  
  operations.operande_2.operande_is_float=false ;
  
  operations.operande_2.operande_bin_str=calloc(128,sizeof(char)) ;
  operations.operande_2.operande_oct_str=calloc(128,sizeof(char)) ;
  operations.operande_2.operande_hex_str=calloc(128,sizeof(char)) ;
  operations.operande_2.operande_dec_str=calloc(128,sizeof(char)) ; 

  
  operations.result.operande_string=calloc(128,sizeof(char)) ;

  operations.result.operande_digit.operande_float=0.0 ;
  operations.result.operande_digit.operande_int=0 ;
  
  operations.result.operande_is_float=false ;
  
  operations.result.operande_bin_str=calloc(128,sizeof(char)) ;
  operations.result.operande_oct_str=calloc(128,sizeof(char)) ;
  operations.result.operande_hex_str=calloc(128,sizeof(char)) ;
  operations.result.operande_dec_str=calloc(128,sizeof(char)) ; 
  
  operations.current_operator=255 ;
  
  return ; 
}

void reset_calculator(void) {
  
  /** Reset the calculator: all members from the operations container are cleaned . 
   * ******************************************************************************/
  
  /***         Operand 1 items.                         ***/
  memset(operations.operande_1.operande_string,'\0',128) ; 

  operations.operande_1.operande_digit.operande_float=0.0 ;
  operations.operande_1.operande_digit.operande_int=0 ;
  
  operations.operande_1.operande_is_float=false ;

  memset(operations.operande_1.operande_bin_str,'\0',128) ; 
  memset(operations.operande_1.operande_oct_str,'\0',128) ; 
  memset(operations.operande_1.operande_hex_str,'\0',128) ; 
  memset(operations.operande_1.operande_dec_str,'\0',128) ;
  /********************************************************/

  
  
  
  /***         Operand 2 items.                         ***/
  memset(operations.operande_2.operande_string,'\0',128) ; 
  
  operations.operande_2.operande_digit.operande_float=0.0 ;
  operations.operande_2.operande_digit.operande_int=0 ;
  
  operations.operande_2.operande_is_float=false ;
  
  memset(operations.operande_2.operande_bin_str,'\0',128) ; 
  memset(operations.operande_2.operande_oct_str,'\0',128) ; 
  memset(operations.operande_2.operande_hex_str,'\0',128) ; 
  memset(operations.operande_2.operande_dec_str,'\0',128) ;  
  /********************************************************/
  
  
  
  
  /***             Result items.                           ***/
  memset(operations.result.operande_string,'\0',128) ; 

  operations.result.operande_digit.operande_float=0.0 ;
  operations.result.operande_digit.operande_int=0 ;
  
  operations.result.operande_is_float=false ;
  
  memset(operations.result.operande_bin_str,'\0',128) ; 
  memset(operations.result.operande_oct_str,'\0',128) ; 
  memset(operations.result.operande_hex_str,'\0',128) ; 
  memset(operations.result.operande_dec_str,'\0',128) ;  
  /***********************************************************/
  
  
  
  
  
  operations.current_operator=255 ; /** storage for the computing operator: +, -, *, /, %. */ 
  
  return ; 
}

void reset_result(void) {
  /** Reset all the result members from the operations. 
   * **********************************************************/
  
  /***             Result items.                           ***/
  memset(operations.result.operande_string,'\0',128) ; 

  operations.result.operande_digit.operande_float=0.0 ;
  operations.result.operande_digit.operande_int=0 ;
  
  operations.result.operande_is_float=false ;
  
  memset(operations.result.operande_bin_str ,'\0',128) ;
  memset(operations.result.operande_oct_str ,'\0',128) ;
  memset(operations.result.operande_hex_str ,'\0',128) ;
  memset(operations.result.operande_dec_str ,'\0',128) ;
  
  /********************************************************/
  
  return ; 
}

void init_current_entry(void) {
  /** Initialize the needed current entry storage container items.
   *  by reserving memory at start. 
   * *************************************************************/
  
  
  entry_values.operande_string  = calloc(128,sizeof(char)) ;

  entry_values.operande_bin_str = calloc(128,sizeof(char)) ;
  entry_values.operande_oct_str = calloc(128,sizeof(char)) ;
  entry_values.operande_hex_str = calloc(128,sizeof(char)) ;
  entry_values.operande_dec_str = calloc(128,sizeof(char)) ;
  
  return ; 
}

void reset_current_entry(void) {
  
  /** Initialize the calclator by start and by user res ('=') command input. 
   * ***********************************************************************/
  
  memset(entry_values.operande_string ,'\0',128) ;

  memset(entry_values.operande_bin_str ,'\0',128) ;
  memset(entry_values.operande_oct_str ,'\0',128) ;
  memset(entry_values.operande_hex_str ,'\0',128) ;
  memset(entry_values.operande_dec_str ,'\0',128) ;
  
  return ; 
}

void reset_operand2(void) {
  /** Reset all the operand 2 container members from the operations. 
   * ***************************************************************/
  
  /***         Operand 2 items.                         ***/
  memset(operations.operande_2.operande_string,'\0',128) ; 
  
  operations.operande_2.operande_digit.operande_float=0.0 ;
  operations.operande_2.operande_digit.operande_int=0 ;
  
  operations.operande_2.operande_is_float=false ;
  
  memset(operations.operande_2.operande_bin_str,'\0',128) ; 
  memset(operations.operande_2.operande_oct_str,'\0',128) ; 
  memset(operations.operande_2.operande_hex_str,'\0',128) ; 
  memset(operations.operande_2.operande_dec_str,'\0',128) ;
  /********************************************************/
  
  return ;  
}

void copy_entry_in_result(void) {
  /** This function is needed for applying mathematic conversion operations on the result.
   *  The datas are copy to the result container after conversion for data storage purpose.
   * **************************************************************************************/
  
  reset_result() ; 
  
  if (entry_values.operande_is_float) {
    operations.result.operande_is_float=true ;
    operations.result.operande_digit.operande_float=entry_values.operande_digit.operande_float ;
  }
  else {
    operations.result.operande_is_float=false ;
    operations.result.operande_digit.operande_int=entry_values.operande_digit.operande_int ;
  }
  
  strcpy(operations.result.operande_bin_str,entry_values.operande_bin_str) ;
  strcpy(operations.result.operande_oct_str,entry_values.operande_oct_str) ;
  strcpy(operations.result.operande_dec_str,entry_values.operande_dec_str) ;
  strcpy(operations.result.operande_hex_str,entry_values.operande_hex_str) ;
  
  operations.result.operand_base=operations.current_base ;
  
  return ;
  
}

void copy_result_in_entry(void) {
  /** This function copy the result datas to the current entry container
   *  for applying an result memory storing operation.
   * *******************************************************************/
  
  
  reset_current_entry() ;
  
  if (operations.result.operande_is_float) {
    entry_values.operande_is_float=true ;
    entry_values.operande_digit.operande_float=operations.result.operande_digit.operande_float ;
  }
  else {
    entry_values.operande_is_float=false ;
    entry_values.operande_digit.operande_int=operations.result.operande_digit.operande_int ;
  }
  
  strcpy(entry_values.operande_bin_str,operations.result.operande_bin_str) ;
  strcpy(entry_values.operande_oct_str,operations.result.operande_oct_str) ;
  strcpy(entry_values.operande_dec_str,operations.result.operande_dec_str) ;
  strcpy(entry_values.operande_hex_str,operations.result.operande_hex_str) ;
  
  entry_values.operand_base=operations.current_base ;
  
  switch (entry_values.operand_base) {
    
    case 2 :
      strcpy(entry_values.operande_string,operations.result.operande_bin_str) ;
      break ;
      
    case 8 :
      strcpy(entry_values.operande_string,operations.result.operande_oct_str) ;
      break ;  
      
    case 10 :
      strcpy(entry_values.operande_string,operations.result.operande_dec_str) ;
      break ;   
  
    case 16 :
      strcpy(entry_values.operande_string,operations.result.operande_hex_str) ;
      break ;
  }
  
  return ;
}

void revert_result_values(void) {
  /** This function copy the result datas to the current entry container
   *  for applying the revert result to the operand 1 functionnality.
   * *******************************************************************/
  
  
  reset_current_entry() ;
  
  if (operations.result.operande_is_float) {
    entry_values.operande_is_float=true ;
    entry_values.operande_digit.operande_float=operations.result.operande_digit.operande_float ;
  }
  else {
    entry_values.operande_is_float=false ;
    entry_values.operande_digit.operande_int=operations.result.operande_digit.operande_int ;
  }
  
  strcpy(entry_values.operande_bin_str,operations.result.operande_bin_str) ;
  strcpy(entry_values.operande_oct_str,operations.result.operande_oct_str) ;
  strcpy(entry_values.operande_dec_str,operations.result.operande_dec_str) ;
  strcpy(entry_values.operande_hex_str,operations.result.operande_hex_str) ;
  
  //operations.current_base=operations.result.operand_base ;
  
}



_Bool thread_operand_1(char *input,_Bool is_float) {
  
  /** Store the first operand values:
   * 
   *  All the members from the operand 1 storage container
   *  are set in relationship to:
   *  -) case the value is an float or an integer ;
   *  -) the current base.
   *  All the supported bases [ 2 | 8 | 10 | 16 ] values 
   *  are computed and stored in an specific member.
   ********************************************************/ 
  
  if (is_float) {
    
    /** The input string contains the decimal separator. */ 
    
    if (strip_zero(input)) {
      /** The float value has be converted to an integer value from the strip_zero() function. */
      if ( ! CUR_BASE_IS_DEC )  {
	/* The current base is different from the decimal basis. */
      
        /** We convert the input string to an long long type value. */
	long long conversion_res=convert_input_to_int(input) ;
	strcpy(operations.operande_1.operande_string,input) ;
	operations.operande_1.operande_digit.operande_int=conversion_res ;
      }
      
      else {
	/* The current base is the decimal basis. */
	
	/** We store the numeric value after type conversion. */
	strcpy(operations.operande_1.operande_string,input) ;
	operations.operande_1.operande_digit.operande_int=strtoll(operations.operande_1.operande_string,NULL,0) ;
      }
      
      char *res_conversion=calloc(BUF_SIZE,sizeof(char)) ;
      
      /** Storing the binar form from the operand as a string. */
      convert_int_to_base(operations.operande_1.operande_digit.operande_int,res_conversion,2) ;
      strcpy(operations.operande_1.operande_bin_str,res_conversion) ;
      operations.operande_1.operande_bin_str[127]='\0' ;
      memset(res_conversion,'\0',BUF_SIZE) ;
      
      
      /** Storing the octal form from the operand as a string. */
      convert_int_to_base(operations.operande_1.operande_digit.operande_int,res_conversion,8) ;
      strcpy(operations.operande_1.operande_oct_str,res_conversion) ;
      operations.operande_1.operande_oct_str[127]='\0' ;
      memset(res_conversion,'\0',BUF_SIZE) ;
      
      /** Storing the hexadecimal form from the operand as a string. */
      convert_int_to_base(operations.operande_1.operande_digit.operande_int,res_conversion,16) ;
      strcpy(operations.operande_1.operande_hex_str,res_conversion) ;
      operations.operande_1.operande_hex_str[127]='\0' ;
      memset(res_conversion,'\0',BUF_SIZE) ;
      
      /** Storing the decimal form from the operand as a string. */
      sprintf(res_conversion,"%Li",operations.operande_1.operande_digit.operande_int) ;
      strcpy(operations.operande_1.operande_dec_str,res_conversion) ;
      operations.operande_1.operande_dec_str[127]='\0' ;
      
      free(res_conversion) ;
      
      operations.operande_1.operande_is_float=false ;
    }
    
    else {
      
      /** The value is an float. */
      
      if ( ! CUR_BASE_IS_DEC )  {
	/* The current base is different from the decimal basis. */
	
	/** We convert the input string to an long double type value. */
	long double conversion_res ;
	conversion_res=convert_input_to_float(input) ;
	strcpy(operations.operande_1.operande_string,input) ;
        operations.operande_1.operande_digit.operande_float=conversion_res ;
		
      }
      
      else {
	/* The current base is the decimal basis. */
	
	/** We store the numeric value after type conversion. */
        strcpy(operations.operande_1.operande_string,input) ;
        operations.operande_1.operande_digit.operande_float=g_strtod(operations.operande_1.operande_string,NULL) ;
      }
      
      char *res_conversion=calloc(BUF_SIZE,sizeof(char)) ;
      
      /** Storing the binar form from the operand as a string. */
      convert_float_to_base(operations.operande_1.operande_digit.operande_float,res_conversion,2) ;
      strcpy(operations.operande_1.operande_bin_str,res_conversion) ;
      operations.operande_1.operande_bin_str[127]='\0' ;
      memset(res_conversion,'\0',BUF_SIZE) ;
      
      /** Storing the octal form from the operand as a string. */
      convert_float_to_base(operations.operande_1.operande_digit.operande_float,res_conversion,8) ;
      strcpy(operations.operande_1.operande_oct_str,res_conversion) ;
      operations.operande_1.operande_oct_str[127]='\0' ;
      memset(res_conversion,'\0',BUF_SIZE) ;
      
      /** Storing the hexadecimal form from the operand as a string. */
      convert_float_to_base(operations.operande_1.operande_digit.operande_float,res_conversion,16) ;
      strcpy(operations.operande_1.operande_hex_str,res_conversion) ;
      operations.operande_1.operande_hex_str[127]='\0' ;
      memset(res_conversion,'\0',BUF_SIZE) ;
      
      /** Storing the decimal form from the operand as a string. */
      sprintf(res_conversion,"%.14lf",(double) operations.operande_1.operande_digit.operande_float) ;
      strcpy(operations.operande_1.operande_dec_str,res_conversion) ;
      operations.operande_1.operande_dec_str[127]='\0' ;
      exchange_comma_and_float_point(operations.operande_1.operande_dec_str) ;
      strip_zero(operations.operande_1.operande_dec_str) ;
      
      free(res_conversion) ;
      
      operations.operande_1.operande_is_float=true ;
    }
    
  }
  
  else {
    
    /** The value is an integer. */
    
    if ( ! CUR_BASE_IS_DEC )  {
      /* The current base is different from the decimal basis. */
      
      /** We convert the input string to an long long type value. */
      long long conversion_res=convert_input_to_int(input) ;
      strcpy(operations.operande_1.operande_string,input) ;
      operations.operande_1.operande_digit.operande_int=conversion_res ;
      
      
    }
    
    else { 
      /* The current base is the decimal basis. */
      
      /** We store the numeric value after type conversion. */
      strcpy(operations.operande_1.operande_string,input) ;
      operations.operande_1.operande_digit.operande_int=strtoll(operations.operande_1.operande_string,NULL,0) ;
      
    }
    
    char *res_conversion=calloc(BUF_SIZE,sizeof(char)) ;
    
    /** Storing the binar form from the operand as a string. */
    convert_int_to_base(operations.operande_1.operande_digit.operande_int,res_conversion,2) ;
    strcpy(operations.operande_1.operande_bin_str,res_conversion) ;
    operations.operande_1.operande_bin_str[127]='\0' ;
    memset(res_conversion,'\0',BUF_SIZE) ;
    
    /** Storing the octal form from the operand as a string. */
    convert_int_to_base(operations.operande_1.operande_digit.operande_int,res_conversion,8) ;
    strcpy(operations.operande_1.operande_oct_str,res_conversion) ;
    operations.operande_1.operande_oct_str[127]='\0' ;
    memset(res_conversion,'\0',BUF_SIZE) ;
    
    /** Storing the hexadecimal form from the operand as a string. */
    convert_int_to_base(operations.operande_1.operande_digit.operande_int,res_conversion,16) ;
    strcpy(operations.operande_1.operande_hex_str,res_conversion) ;
    operations.operande_1.operande_hex_str[127]='\0' ;
    memset(res_conversion,'\0',BUF_SIZE) ;
    
    /** Storing the decimal form from the operand as a string. */
    sprintf(res_conversion,"%Li",operations.operande_1.operande_digit.operande_int) ;
    strcpy(operations.operande_1.operande_dec_str,res_conversion) ;
    operations.operande_1.operande_dec_str[127]='\0' ;
    
    free(res_conversion) ;
    
    operations.operande_1.operande_is_float=false ;
    
  }
  
  operations.operande_1.operand_base=operations.current_base ;
    
  return true ;
}

_Bool thread_operand_2(char *input,_Bool is_float) {
  
  /** Store the first operand values:
   * 
   *  All the members from the operand 1 storage container
   *  are set in relationship to:
   *  -) case the value is an float or an integer ;
   *  -) the current base.
   *  All the supported bases [ 2 | 8 | 10 | 16 ] values 
   *  are computed and stored in an specific member.
   ********************************************************/ 
  
  if (is_float) {
    /** The input string contains the decimal separator. */ 
    
    if (strip_zero(input)) {
      /** The float value has be converted to an integer value from the strip_zero() function. */
      
      if ( ! CUR_BASE_IS_DEC )  {
	/* The current base is different from the decimal basis. */
	
	/** We convert the input string to an long long type value. */
	long long conversion_res=convert_input_to_int(input) ;
	strcpy(operations.operande_2.operande_string,input) ;
	operations.operande_2.operande_digit.operande_int=conversion_res ;
      }
      
      else {
	/* The current base is the decimal basis. */
      
        /** We store the numeric value after type conversion. */
	strcpy(operations.operande_2.operande_string,input) ;
	operations.operande_2.operande_digit.operande_int=strtoll(operations.operande_2.operande_string,NULL,0) ;
      }
      
      char *res_conversion=calloc(BUF_SIZE,sizeof(char)) ;
      
      /** Storing the binar form from the operand as a string. */
      convert_int_to_base(operations.operande_2.operande_digit.operande_int,res_conversion,2) ;
      strcpy(operations.operande_2.operande_bin_str,res_conversion) ;
      operations.operande_2.operande_bin_str[127]='\0' ;
      memset(res_conversion,'\0',BUF_SIZE) ;
      
      /** Storing the octal form from the operand as a string. */
      convert_int_to_base(operations.operande_2.operande_digit.operande_int,res_conversion,8) ;
      strcpy(operations.operande_2.operande_oct_str,res_conversion) ;
      operations.operande_2.operande_oct_str[127]='\0' ;
      memset(res_conversion,'\0',BUF_SIZE) ;
      
      /** Storing the hexadecimal form from the operand as a string. */
      convert_int_to_base(operations.operande_2.operande_digit.operande_int,res_conversion,16) ;
      strcpy(operations.operande_2.operande_hex_str,res_conversion) ;
      operations.operande_2.operande_hex_str[127]='\0' ;
      memset(res_conversion,'\0',BUF_SIZE) ;
      
      /** Storing the decimal form from the operand as a string. */
      sprintf(res_conversion,"%Li",operations.operande_2.operande_digit.operande_int) ;
      strcpy(operations.operande_2.operande_dec_str,res_conversion) ;
      operations.operande_2.operande_dec_str[127]='\0' ;
      
      
      free(res_conversion) ;
      
      operations.operande_2.operande_is_float=false ;
    }
    
    else {
      
      /** The value is an float. */
      
      if ( ! CUR_BASE_IS_DEC )  {
	/* The current base is different from the decimal basis. */
	
	/** We convert the input string to an long double type value. */
	long double conversion_res ;
	conversion_res=convert_input_to_float(input) ;
	strcpy(operations.operande_2.operande_string,input) ;
        operations.operande_2.operande_digit.operande_float=conversion_res ;
	
      }
      
      else {
	/* The current base is the decimal basis. */
      
        /** We store the numeric value after type conversion. */
        strcpy(operations.operande_2.operande_string,input) ;
        operations.operande_2.operande_digit.operande_float=g_strtod(operations.operande_2.operande_string,NULL) ;
      }
      
      char *res_conversion=calloc(BUF_SIZE,sizeof(char)) ;
      
      /** Storing the binar form from the operand as a string. */
      convert_float_to_base(operations.operande_2.operande_digit.operande_float,res_conversion,2) ;
      strcpy(operations.operande_2.operande_bin_str,res_conversion) ;
      operations.operande_2.operande_bin_str[127]='\0' ;
      memset(res_conversion,'\0',BUF_SIZE) ;
      
      /** Storing the octal form from the operand as a string. */
      convert_float_to_base(operations.operande_2.operande_digit.operande_float,res_conversion,8) ;
      strcpy(operations.operande_2.operande_oct_str,res_conversion) ;
      operations.operande_2.operande_oct_str[127]='\0' ;
      memset(res_conversion,'\0',BUF_SIZE) ;
      
      /** Storing the hexadecimal form from the operand as a string. */
      convert_float_to_base(operations.operande_2.operande_digit.operande_float,res_conversion,16) ;
      strcpy(operations.operande_2.operande_hex_str,res_conversion) ;
      operations.operande_2.operande_hex_str[127]='\0' ;
      memset(res_conversion,'\0',BUF_SIZE) ;
      
      /** Storing the decimal form from the operand as a string. */
      sprintf(res_conversion,"%.14lf",(double) operations.operande_2.operande_digit.operande_float) ;
      strcpy(operations.operande_2.operande_dec_str,res_conversion) ;
      operations.operande_2.operande_dec_str[127]='\0' ;
      exchange_comma_and_float_point(operations.operande_2.operande_dec_str) ;
      strip_zero(operations.operande_2.operande_dec_str) ;
      
      
      free(res_conversion) ;
      
      operations.operande_2.operande_is_float=true ;
    }
  }
  
  else {
    
    /** The value is an integer. */
    
    if ( ! CUR_BASE_IS_DEC )  {
      /* The current base is different from the decimal basis. */
	
      /** We convert the input string to an long long type value. */
      long long conversion_res=convert_input_to_int(input) ;
      strcpy(operations.operande_2.operande_string,input) ;
      operations.operande_2.operande_digit.operande_int=conversion_res ;
      
      
    }
    
    else {  
      /* The current base is the decimal basis. */
      
      /** We store the numeric value after type conversion. */
      strcpy(operations.operande_2.operande_string,input) ;
      operations.operande_2.operande_digit.operande_int=strtoll(operations.operande_2.operande_string,NULL,0) ;
      
    }
    
    char *res_conversion=calloc(BUF_SIZE,sizeof(char)) ;
    
    /** Storing the binar form from the operand as a string. */
    convert_int_to_base(operations.operande_2.operande_digit.operande_int,res_conversion,2) ;
    strcpy(operations.operande_2.operande_bin_str,res_conversion) ;
    operations.operande_2.operande_bin_str[127]='\0' ;
    memset(res_conversion,'\0',BUF_SIZE) ;
    
    /** Storing the octal form from the operand as a string. */
    convert_int_to_base(operations.operande_2.operande_digit.operande_int,res_conversion,8) ;
    strcpy(operations.operande_2.operande_oct_str,res_conversion) ;
    operations.operande_2.operande_oct_str[127]='\0' ;
    memset(res_conversion,'\0',BUF_SIZE) ;
    
    /** Storing the hexadecimal form from the operand as a string. */
    convert_int_to_base(operations.operande_2.operande_digit.operande_int,res_conversion,16) ;
    strcpy(operations.operande_2.operande_hex_str,res_conversion) ;
    operations.operande_2.operande_hex_str[127]='\0' ;
    memset(res_conversion,'\0',BUF_SIZE) ;
    
    /** Storing the decimal form from the operand as a string. */
    sprintf(res_conversion,"%Li",operations.operande_2.operande_digit.operande_int) ;
    strcpy(operations.operande_2.operande_dec_str,res_conversion) ;
    operations.operande_2.operande_dec_str[127]='\0' ;
    
    free(res_conversion) ;
    
    operations.operande_2.operande_is_float=false ;
    
  }
  
  operations.operande_2.operand_base=operations.current_base ;
  
  return true ;
}
 
void process_math_operation(char *input,int8_t op_code,_Bool is_degrees) {
  /** This function perform all mathematic operations on an operand (except the power which is a special case).
   *  And store the result in the current entry container so that we can apply the operation on every wanted operand.
   ******************************************************************************************************************/  
  
  exchange_comma_and_float_point(input) ;
  
  char *res_str=calloc(128,sizeof(char))  ;
  
  long double op_nb ;
  long double res   ;
  
  if ( is_string_float(input) ) {
    
    if (CUR_BASE_IS_DEC) {
      /* The current base is the decimal basis. */
      
      op_nb=string_to_long_double(input)  ;  /** Getting the numeric value from user entry. */
      
    }
    
    else if ( ! CUR_BASE_IS_DEC )  {
      /* The current base is different from the decimal basis. */
      
      op_nb=convert_input_to_float(input) ;  /** Getting the numeric value from user entry. */
      
    }
  
  }
  
  else {
    
    op_nb=(long double) strtoll(input,NULL,operations.current_base) ; /** Getting the numeric value from user entry. */
  
  }
  
  
  if (is_degrees && op_code != 10 && op_code != 11 ) {
    /* Convert input numeric value number into radians for trigonometric operations. */
    
    op_nb = op_nb / 180.0 * PI ; 
  }
  
  
  switch (op_code) {
    case 1 :
      res=cosl(op_nb) ;      
      break ;
      
    case 2 :
      res=sinl(op_nb) ;
      break ;  
      
    case 3 :
      res=tanl(op_nb) ;
      break ; 
      
    case 4 :
      res=acosl(op_nb) ;
      break ;
      
    case 5 :
      res=asinl(op_nb) ;
      break ;  
      
    case 6 :
      res=atanl(op_nb) ;
      break ;
      
    case 7 :
      res=coshl(op_nb) ;
      break ;
      
    case 8 :
      res=sinhl(op_nb) ;
      break ;
      
    case 9 :
      res=tanhl(op_nb) ;
      break ; 
      
    case 10 :
      res=sqrtl(op_nb) ;
      break ;
      
    case 11 :
      res=fabsl(op_nb) ;
      break ;   
  }
  
  if ( isnan(res) ) {
    strcpy(entry_values.operande_bin_str,"Conversion result NaN (Not A Number) value error.") ;
    strcpy(entry_values.operande_oct_str,"Conversion result NaN (Not A Number) value error.") ;
    strcpy(entry_values.operande_hex_str,"Conversion result NaN (Not A Number) value error.") ;
    strcpy(entry_values.operande_dec_str,"Conversion result NaN (Not A Number) value error.") ;
    
    return ;
  }
  else if ( isinf(res) == 1 || isinf(res) == -1 ) {
    strcpy(entry_values.operande_bin_str,"Conversion result Infinity value error.") ;
    strcpy(entry_values.operande_oct_str,"Conversion result Infinity value error.") ;
    strcpy(entry_values.operande_hex_str,"Conversion result Infinity value error.") ;
    strcpy(entry_values.operande_dec_str,"Conversion result Infinity value error.") ;
    
    return ;
  }
  
    
  
  sprintf(res_str,"%Lf",res) ;
    
  exchange_comma_and_float_point(res_str) ;
  
  if (! strip_zero(res_str) ) {
    
      /** The result is an float because the function strip_zero() return false. */
      
      memset(res_str,'\0',128) ;
      
      /** Storing the binar form from the result as a string. */
      floattobinfloat(res,res_str) ;
      res_str[127]='\0' ;
      strcpy(entry_values.operande_bin_str,res_str) ;
      
      
      memset(res_str,'\0',128) ;
      
      /** Storing the octal form from the result as a string. */
      floattooctfloat(res,res_str) ;
      res_str[127]='\0' ;
      strcpy(entry_values.operande_oct_str,res_str) ;
      
      memset(res_str,'\0',128) ;
      
      /** Storing the hexadecimal form from the result as a string. */
      floattohexfloat(res,res_str) ;
      res_str[127]='\0' ;
      strcpy(entry_values.operande_hex_str,res_str) ;
      
      memset(res_str,'\0',128) ;
      
      /** Storing the decimal form from the result as a string. */
      sprintf(res_str,"%.14Lf",res) ;
      res_str[127]='\0' ;
      strcpy(entry_values.operande_dec_str,res_str) ;
      exchange_comma_and_float_point(entry_values.operande_dec_str) ;
      strip_zero(entry_values.operande_dec_str) ;
      
     
      
      entry_values.operande_is_float=true ;
      entry_values.operande_digit.operande_float=res ;
  }
  
  else {
    
      /** The result is an integer because the function strip_zero() return true. */  
    
      memset(res_str,'\0',128) ;
      
      /** Storing the binar form from the result as a string. */
      inttobin(res,res_str) ;
      res_str[127]='\0' ;
      strcpy(entry_values.operande_bin_str,res_str) ;
      
      memset(res_str,'\0',128) ;
      
      /** Storing the octal form from the result as a string. */
      inttooct(res,res_str) ;
      res_str[127]='\0' ;
      strcpy(entry_values.operande_oct_str,res_str) ;
      
      memset(res_str,'\0',128) ;
      
      /** Storing the hexadecimal form from the result as a string. */
      inttohex(res,res_str) ;
      res_str[127]='\0' ;
      strcpy(entry_values.operande_hex_str,res_str) ;
      
      memset(res_str,'\0',128) ;
      
      /** Storing the decimal form from the result as a string. */
      sprintf(res_str,"%Li",(long long) res) ;
      res_str[127]='\0' ;
      strcpy(entry_values.operande_dec_str,res_str) ;
      
      
      
      
      entry_values.operande_is_float=false ;
      entry_values.operande_digit.operande_int=res ;
  }
  
  free(res_str) ;
  
  return ;
}
 
void process_power_operation(void) { 
  
  long double power_result_as_float ;
  char *power_result_string = calloc(128,sizeof(char)) ;
  long double operand_pow_1, operand_pow_2 ;
  
  if (operations.operande_1.operande_is_float && operations.operande_2.operande_is_float ) {
      
    power_result_as_float=powl(operations.operande_1.operande_digit.operande_float,operations.operande_2.operande_digit.operande_float) ;
  } 
  else if (operations.operande_1.operande_is_float && ! operations.operande_2.operande_is_float ) {
    
    operand_pow_2=operations.operande_2.operande_digit.operande_int ;    
    power_result_as_float=powl(operations.operande_1.operande_digit.operande_float,operand_pow_2) ;
  }   
  else if (! operations.operande_1.operande_is_float && operations.operande_2.operande_is_float ) {
    
    operand_pow_1=operations.operande_1.operande_digit.operande_int ;
    power_result_as_float=powl(operand_pow_1, operations.operande_2.operande_digit.operande_float) ;
  } 
  else if (! operations.operande_1.operande_is_float && ! operations.operande_2.operande_is_float ) {
    
    operand_pow_1=operations.operande_1.operande_digit.operande_int ;
    operand_pow_2=operations.operande_2.operande_digit.operande_int ;  
    power_result_as_float=powl(operand_pow_1,operand_pow_2) ;
  }
  
  
  sprintf(power_result_string,"%Lf",power_result_as_float) ;
  
  power_result_string[127]='\0' ;
  
  
  exchange_comma_and_float_point(power_result_string) ;  
  
  
  if (! strip_zero(power_result_string) ) {
       
      if (result_float_is_overflow(power_result_as_float) ) {
	free(power_result_string) ;
	return ;
      }
     
      /** The result is an float because the function strip_zero() return false. */
      
      memset(power_result_string,'\0',128) ;
      
      /** Storing the binar form from the result as a string. */
      floattobinfloat(power_result_as_float,power_result_string) ;
      power_result_string[127]='\0' ;
      strcpy(operations.result.operande_bin_str,power_result_string) ;
      
      
      memset(power_result_string,'\0',128) ;
      
      /** Storing the octal form from the result as a string. */
      floattooctfloat(power_result_as_float,power_result_string) ;
      power_result_string[127]='\0' ;
      strcpy(operations.result.operande_oct_str,power_result_string) ;
      
      memset(power_result_string,'\0',128) ;
      
      /** Storing the hexadecimal form from the result as a string. */
      floattohexfloat(power_result_as_float,power_result_string) ;
      power_result_string[127]='\0' ;
      strcpy(operations.result.operande_hex_str,power_result_string) ;
      
      memset(power_result_string,'\0',128) ;
      
      /** Storing the decimal form from the result as a string. */
      sprintf(power_result_string,"%.14Lf",power_result_as_float) ;
      power_result_string[127]='\0' ;
      strcpy(operations.result.operande_dec_str,power_result_string) ;
      exchange_comma_and_float_point(operations.result.operande_dec_str) ;
      strip_zero(operations.result.operande_dec_str) ;
      
      
      
      operations.result.operande_is_float=true ;
      operations.result.operande_digit.operande_float=power_result_as_float ;
    
  }
  
  else {
     
      /** The result is an integer because the function strip_zero() return true. */  
      
      if (result_int_is_overflow(power_result_string) ) {
	free(power_result_string) ;
	return ;
      }
      
      memset(power_result_string,'\0',128) ;
      
      /** Storing the binar form from the result as a string. */
      inttobin(power_result_as_float,power_result_string) ;
      power_result_string[127]='\0' ;
      strcpy(operations.result.operande_bin_str,power_result_string) ;
      
      memset(power_result_string,'\0',128) ;
      
      /** Storing the octal form from the result as a string. */
      inttooct(power_result_as_float,power_result_string) ;
      power_result_string[127]='\0' ;
      strcpy(operations.result.operande_oct_str,power_result_string) ;
      
      memset(power_result_string,'\0',128) ;
      
      /** Storing the hexadecimal form from the result as a string. */
      inttohex(power_result_as_float,power_result_string) ;
      power_result_string[127]='\0' ;
      strcpy(operations.result.operande_hex_str,power_result_string) ;
      
      memset(power_result_string,'\0',128) ;
      
      /** Storing the decimal form from the result as a string. */
      sprintf(power_result_string,"%Li",(long long) power_result_as_float) ;
      power_result_string[127]='\0' ;
      strcpy(operations.result.operande_dec_str,power_result_string) ;
      
      
      
      
      operations.result.operande_is_float=false ;
      operations.result.operande_digit.operande_int=(long long) power_result_as_float ;
  }
  
  free(power_result_string) ;
  
  return ;
}
    
    
 
_Bool register_current_operand(char *input) {
  
  /** Store the current entry values:
   * 
   *  All the members from the current entry storage container
   *  are set in relationship to:
   *  -) case the value is an float or an integer ;
   *  -) the current base.
   *  All the supported bases [ 2 | 8 | 10 | 16 ] values 
   *  are computed and stored in an specific member.
   ********************************************************/ 
  
  char *output=calloc(128,sizeof(char)) ;
  
  long double from_float_value_dec ;
  long long from_int_value_dec ;
  
  if (is_string_float(input)) {
    
    /** The current entry is an float. */
    
    strip_zero(input) ;
    
    exchange_comma_and_float_point(input) ;
    
    switch (operations.current_base) {
      case 2 :
	/* Convert the input string (binar string) to an numeric value. */
	from_float_value_dec=binfloattofloat(input) ;
	break ;
      case 8 :
	/* Convert the input string (octal string) to an numeric value. */
	from_float_value_dec=octfloattofloat(input) ;
	break ;
      case 10 :
	/* Convert the input string (decimal string) to an numeric value. */
	from_float_value_dec=string_to_long_double(input) ;
	break ;  
      case 16 :
	/* Convert the input string (hexadecimal string) to an numeric value. */
	from_float_value_dec=hexfloattofloat(input) ;
	break ;
    }
    
    /** Storing the binar form from the current entry as a string. */
    floattobinfloat(from_float_value_dec,output) ;
    output[127]='\0' ;
    strcpy(entry_values.operande_bin_str,output) ;
    
    memset(output,'\0',128) ;
    
    /** Storing the octal form from the current entry as a string. */
    floattooctfloat(from_float_value_dec,output) ;
    output[127]='\0' ;
    strcpy(entry_values.operande_oct_str,output) ;
    
    memset(output,'\0',128) ;
    
    /** Storing the hexadecimal form from the current entry as a string. */
    floattohexfloat(from_float_value_dec,output) ;
    output[127]='\0' ;
    strcpy(entry_values.operande_hex_str,output) ;
    
    memset(output,'\0',128) ;
    
    /** Storing the decimal form from the current entry as a string. */
    if (! (operations.current_base == 10) ) {
      /* We must find the right  rounding (%.?lf) for exactly computation. */
      
      char *ptr_comma  ;
      char *operand_string=calloc(128,sizeof(char)) ;
      
      sprintf(operand_string,"%.19Lf",from_float_value_dec) ;
      
      exchange_comma_and_float_point(operand_string) ;
      
      ptr_comma=strchr(operand_string,'.') ;
      
      
      
      operand_string[ptr_comma-operand_string]='\0' ;
      
	  
      if ((int) strlen(operand_string) > 18) {
	/* We must find the right  rounding (%.?lf) for exactly computation. */
	sprintf(output,"%.1Lf",from_float_value_dec) ;
      }
      else {
	sprintf(output,"%.*Lf",19 - (int) strlen(operand_string),from_float_value_dec) ;
      }
      
      output[127]='\0' ;
      strcpy(entry_values.operande_dec_str,output) ;
      exchange_comma_and_float_point(entry_values.operande_dec_str) ;
      strip_zero(entry_values.operande_dec_str) ;
      
    }
    else {
      strcpy(entry_values.operande_dec_str,input) ;
      strip_zero(entry_values.operande_dec_str) ;
    }
    
    
    
    
    
    
    /* Copy the current entry container members to the main current entry string,
     * in relationship to the current base.
     * **************************************************************************/
    switch (operations.current_base) {
      case 2 :
	strcpy(entry_values.operande_string,entry_values.operande_bin_str) ;
        break ;
      case 8 :
	strcpy(entry_values.operande_string,entry_values.operande_oct_str) ;
        break ;
      case 10 :
	strcpy(entry_values.operande_string,entry_values.operande_dec_str) ;
        break ;
      case 16 :
	strcpy(entry_values.operande_string,entry_values.operande_hex_str) ;
        break ;	
    }
    
  }    
 
 else {
     /** The current entry is an integer. */
    
    switch (operations.current_base) {
      case 2 :
	/* Convert the input string (binar string) to an numeric value. */
	from_int_value_dec=bintoint(input) ;
	break ;
      case 8 :
	/* Convert the input string (octal string) to an numeric value. */
	from_int_value_dec=octtoint(input) ;
	break ;
      case 10 :
	/* Convert the input string (decimal string) to an numeric value. */
	from_int_value_dec=strtoll(input,NULL,0) ;
	break ;  
      case 16 :
	/* Convert the input string (hexadecimal string) to an numeric value. */
	from_int_value_dec=hextoint(input) ;
	break ;
    }
    
    
    /** Storing the binar form from the current entry as a string. */
    inttobin(from_int_value_dec,output) ;
    output[127]='\0' ;
    strcpy(entry_values.operande_bin_str,output) ;
    
    memset(output,'\0',128) ;
    
    /** Storing the octal form from the current entry as a string. */
    inttooct(from_int_value_dec,output) ;
    output[127]='\0' ;
    strcpy(entry_values.operande_oct_str,output) ;
    
    memset(output,'\0',128) ;
    
    /** Storing the hexadecimal form from the current entry as a string. */
    inttohex(from_int_value_dec,output) ;
    output[127]='\0' ;
    strcpy(entry_values.operande_hex_str,output) ;
    
    memset(output,'\0',128) ;
    
    /** Storing the decimal form from the current entry as a string. */
    if (! (operations.current_base == 10) ) {
      sprintf(output,"%Li",from_int_value_dec) ;
      output[127]='\0' ;
      strcpy(entry_values.operande_dec_str,output) ;
    }
    else {
      strcpy(entry_values.operande_dec_str,input) ;
    }
    
    
    
    /* Copy the current entry container members to the main current entry string,
     * in relationship to the current base.
     * **************************************************************************/
    switch (operations.current_base) {
      case 2 :
	strcpy(entry_values.operande_string,entry_values.operande_bin_str) ;
        break ;
      case 8 :
	strcpy(entry_values.operande_string,entry_values.operande_oct_str) ;
        break ;
      case 10 :
	strcpy(entry_values.operande_string,entry_values.operande_dec_str) ;
        break ;
      case 16 :
	strcpy(entry_values.operande_string,entry_values.operande_hex_str) ;
        break ;	
    }
   
  }
  
  entry_values.operand_base = operations.current_base ;
   
  free(output) ;
  
  return true ;
} 
 
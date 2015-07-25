
_Bool convert_from_base_to_base(char *input,char *output, uint8_t from_base,uint8_t to_base) {
  /** Print the given "convert from_base value to_base result */
  
  if (from_base == to_base) {
    return false ;
  }
  
  fprintf(stderr,"[DEBUG we in %s from base : %d to base: %d\n",__func__,from_base,to_base) ;
  
  long double from_float_value_dec ;
  long long from_int_value_dec ;
  
  if (is_string_float(input)) {
    
    strip_zero(input) ;
    
    exchange_comma_and_float_point(input) ;
    
    fprintf(stderr,"[DEBUG input from %s : %s\n",__func__,input) ;
    
    fprintf(stderr,"[DEBUG we in %s from base : %d\n",__func__,from_base) ;
    
    //fprintf(stderr,"%s [DEBUG convert in base 10: %Lf \n",__func__,from_float_value_dec) ;
    
    from_float_value_dec=strtold(input,NULL) ;
    
    fprintf(stderr,"%s [DEBUG sscanf result: %Lf\n",__func__ ,from_float_value_dec) ;
    
    fprintf(stderr,"%s [DEBUG before switch from_base\n",__func__) ;
    switch (from_base) {
      case 2 :
	from_float_value_dec=binfloattofloat(input) ;
	break ;
      case 8 :
	from_float_value_dec=octfloattofloat(input) ;
	break ;
      case 10 :
	from_float_value_dec=g_strtod(input,NULL) ;
	if (strip_zero(input)) {
	  ; // Check overflow error ;
	}
	break ;  
      case 16 :
	from_float_value_dec=hexfloattofloat(input) ;
	break ;
    }
    
    fprintf(stderr,"%s [DEBUG before switch to_base: %.18Lf\n",__func__,from_float_value_dec) ;
    
    switch (to_base) {
      case 2 :
	floattobinfloat(from_float_value_dec,output) ;
	fprintf(stderr,"%s [DEBUG in switch to_base: %s\n",__func__,output) ;
	output[128]='\0' ;
	break ;
      case 8 :
	floattooctfloat(from_float_value_dec,output) ;
	output[128]='\0' ;
	break ;
      case 10 :
	sprintf(output,"%.15Lf",from_float_value_dec) ;
	output[128]='\0' ;
	break ;
      case 16 :
	floattohexfloat(from_float_value_dec,output) ;
	output[128]='\0' ;
	break ;	
    }
    strip_zero(output) ;
    operations.current_base=to_base ;
    return true ;
      
  }
 
 else {
   from_int_value_dec=convert_input_to_int(input) ; /** Convert in base 10 */
    if (! is_integer_in_base_entry_value_in_valid_range((long long) from_int_value_dec,input) ) {
      /** User entry has generate an value overflow | underflow (hobdcalc is limited to 8 bytes) */
      return false ;
    }
    
    else {
      switch (from_base) {
	case 2 :
          from_int_value_dec=bintoint(input) ;
	  break ;
	case 8 :
          from_int_value_dec=octtoint(input) ;
	  break ;
	case 10 :
          from_int_value_dec=strtod(input,NULL) ;
	  break ;  
        case 16 :
          from_int_value_dec=hextoint(input) ;
	  break ;
      }
    
    if (! is_integer_in_base_entry_value_in_valid_range((long long) from_int_value_dec,input) ) {
      /** User entry has generate an value overflow | underflow (hobdcalc is limited to 8 bytes) */
      return false ;
    }
    
    switch (to_base) {
      case 2 :
	inttobin(from_int_value_dec,output) ;
	output[128]='\0' ;
	break ;
      case 8 :
	inttooct(from_int_value_dec,output) ;
	output[128]='\0' ;
	break ;
      case 10 :
	sprintf(output,"%Li",from_int_value_dec) ;
	output[128]='\0' ;
	break ;
      case 16 :
	inttohex(from_int_value_dec,output) ;
	output[128]='\0' ;
        break ;	
    }
    operations.current_base=to_base ;
    return true ;
    }
  }
    
} 
 
    
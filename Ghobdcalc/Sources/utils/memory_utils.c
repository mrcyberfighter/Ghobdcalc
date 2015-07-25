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
  
void add_memory(int item_index) {
  /** Add an operand to memory **/
  
  
  if (entry_values.operande_is_float) {
    memory[item_index].memory_item.operande_is_float=true ;
    memory[item_index].memory_item.operande_digit.operande_float=entry_values.operande_digit.operande_float ;
  }
  else {
    memory[item_index].memory_item.operande_is_float=false ;
    memory[item_index].memory_item.operande_digit.operande_int=entry_values.operande_digit.operande_int ;
  }
  
  memory[item_index].memory_item.operande_bin_str=calloc(128,sizeof(char)) ;
  memory[item_index].memory_item.operande_oct_str=calloc(128,sizeof(char)) ;
  memory[item_index].memory_item.operande_dec_str=calloc(128,sizeof(char)) ;
  memory[item_index].memory_item.operande_hex_str=calloc(128,sizeof(char)) ;
  
  
  strcpy(memory[item_index].memory_item.operande_bin_str,entry_values.operande_bin_str) ;
  strcpy(memory[item_index].memory_item.operande_oct_str,entry_values.operande_oct_str) ;
  strcpy(memory[item_index].memory_item.operande_dec_str,entry_values.operande_dec_str) ;
  strcpy(memory[item_index].memory_item.operande_hex_str,entry_values.operande_hex_str) ;
  
  memory[item_index].memory_item.operand_base=operations.current_base ;
  
  
  return ;
}

void get_item_from_memory(int item_index) {
  /** Get an memory item get back as an entry_values structure **/
  
  if (memory[item_index].memory_item.operande_is_float) {
    entry_values.operande_is_float=true ;
    entry_values.operande_digit.operande_float=memory[item_index].memory_item.operande_digit.operande_float ;
  }
  else {
    entry_values.operande_is_float=false ;
    entry_values.operande_digit.operande_int=memory[item_index].memory_item.operande_digit.operande_int ;
  }
  
  strcpy(entry_values.operande_bin_str,memory[item_index].memory_item.operande_bin_str) ;
  strcpy(entry_values.operande_oct_str,memory[item_index].memory_item.operande_oct_str) ;
  strcpy(entry_values.operande_dec_str,memory[item_index].memory_item.operande_dec_str) ;
  strcpy(entry_values.operande_hex_str,memory[item_index].memory_item.operande_hex_str) ;
  
  entry_values.operand_base=memory[item_index].memory_item.operand_base ;

  return ;
  
}

void del_item_from_memory(int item_index) {
  /** Delete an item from memory **/
  
  memory_management.mem_counter-- ;
  int c=item_index ;
  int i=memory_management.mem_counter ;
  
  for ( ; c < i ; c++ ) {
    
    struct Operande tmp = memory[c+1].memory_item ;
    memory[c].memory_item=tmp ;
       
  }
  
  return ;
}


Ghobdcalc
=========

 **Ghobdcalc**: An multibase calculator with several functionnalities.            
                                                                              
 :Writing by: **Eddie Brüggemann** 
                                                 
 :Language: **C**
                                               
 :Writing start: 31/10/2014          
                                           
 :Writing end: 13/12/2014            
                                           
 :Revision: None 
                                                               
 :Contact: <mrcyberfighter@gmail.com>
                                             
 :Credits: Thank's to my mother, my family and to the doctors.       
                                                                              

Main Description                               
----------------
 
 
 
    
   **Ghobdcalc** (for Graphical Hexadecimal Octal Binar Decimal Calculator), build  
    
   on the developpment files from the `libHOBDCalc  <https://github.com/mrcyberfighter/libHOBDCalc>`_.             
    
   With **GTK+3** as HMI (Human Machine Interface):                                 
                                                                              
    
   an multibase calculator with several functionnalities...                     
                                                                              
 
 * **Ghobdcalc** support 4 differents bases as entry values or converting output
  
    format:
                                                                       
    -) The **decimal base**.
                                                          
    -) The **binar base**.  
                                                          
    -) The **octal base**.  
                                                          
    -) The **hexadecimal base**.
    
    .. 
                                                       
        You can entry values in the wanted base and convert the value in any      
    
        supported base by hitting the corresponding toggle button wich will set   
    
        the current base andor converting the current value in the wanted base.  
                                                                              
 * Ghobdcalc support signed integer values limited                           
    
   from *9223372036854775807* to *-9223372036854775808*.                         
    
   and signed floating-point values composed from 19 digits in decimal base. 
   
   The same limits are apply to values in the other supported bases.         
   
   What permit the computing for the most purpose.                           
   
   So Ghobdcalc is limited to values encoded on 8 bytes.                     
                                                                              
**Ghobdcalc** provide several calculator functionnalities:
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                    
                                                                              
    - The **ERASE** button erase one digit from the current value.               
                                                                              
    - The **DELETE** button erase all digits from the current value.             
                                                                              
    - The **REVERT** button set the result of an operation as first operand      
       value. With which you can continue chain operations.                   
                                                                              
    - The **ENTER** button compute the result from two operand and give the      
       result in the current set base.                                        
                                                                              
    - The **RESET** button reset all fields.                                     
                                                                              
                                                                              
    - The basic operators buttons:                                           
                                                                              
      + The **\+** button set the operation to be an addition, by displaying    
         
        an **\+** sign in the operator filed.                                   
                                                                              
      + The **\-** button set the operation to be an substraction, by           
        
        displaying an **\-** sign in the operator field.                        
                                                                              
      + The **×** button set the operation to be an multiplication, by         
        
        displaying an **×** sign in the operator field.                        
                                                                              
      + The **÷** button set the operation to be an division, by displaying    
        
        an **÷** sign in the operator field.                                   
                                                                              
      + The **%** button set the operation to be an Euclidian division,        
        
        what perform the division from the two operands and give the rest    
        
        of the entire values division, by displaying an **%** sign in the      
        
        operator field.                                                      
                                                                              
      You must press the **=** or **ENTER** button to perform the operation.        
      
      What permit to change the operator before result computing.             
                                                                              
      You can change the operator even after having hit the **=** or **ENTER**      
      
      button and the second operand can be edit after hit an operator button. 
                                                                              

The mathematic specific operators button:
*****************************************                            
                                                                              
      + The **DEG** or **RAD** toggle buttons set the values to be take in charge    
         
        as degrees if the **DEG** button is down or                             
        
        as radians if the **RAD** button is down.                               
                                                                              
                                                                              
      + The **COS** button convert the current value in the cosine              
         
        from the current value in relationship to the current metric        
         
        (degrees or radians).                                               
                                                                              
      + The **SIN** button convert the current value in the sine                
         
        from the current value in relationship to the current metric        
         
        (degrees or radians).                                               
                                                                              
      + The **TAN** button convert the current value in the tangent             
         
        from the current value in relationship to the current metric        
         
        (degrees or radians).                                               
                                                                              
                                                                              
      + The **ACOS** button convert the current value in the arccosine          
         
        from the current value in relationship to the current metric        
         
        (degrees or radians).                                               
                                                                              
      + The **ASIN** button convert the current value in the arcsine            
         
        from the current value in relationship to the current metric        
         
        (degrees or radians).                                               
                                                                              
      + The **ATAN** button convert the current value in the arctangent         
         
        from the current value in relationship to the current metric        
          
        (degrees or radians).                                               
                                                                              
                                                                              
      + The **COSH** button convert the current value in the hyperbel cosine    
         
        from the current value in relationship to the current metric        
          
        (degrees or radians).                                               
                                                                              
      + The **SINH** button convert the current value in the hyperbel sine      
         
        from the current value in relationship to the current metric        
         
        (degrees or radians).                                               
                                                                              
      + The **TANH** button convert the current value in the hyperbel tangent   
         
        from the current value in relationship to the current metric        
         
        (degrees or radians).                                               
                                                                              
                                                                              
      + The **SQRT** button convert the current value in his square root value. 
                                                                              
      + The **ABS** button convert the current value in his absolute value.     
                                                                              
      + The **POW** button is different because it need 2 values to compute an  
         
        power:                                                              
         
        The base: the first operand. After define it press the **POW** button   
          
        to set the exponent as the second operand and finally press the **POW** 
         
        button again to compute the power.                                  
      
                                                                           
The memory functionnalities:
****************************                                           
                                                                              
       Ghobdcalc provide an memory for registering specific values for resusing it later.                                                     
                                                                              
      + The **MEM ADD** button add the current value to the memory.             
                                                                              
      + The **MEM DEL** button delete the memory entry pointed from the memory  
         
        navigating curser.                                                  
                                                                              
      + The **MEM GET** button set the memory entry pointed from the memory     
         
        navigating curser as current operand.                               
                                                                              
      + The **MEM NAV** button display the memory entry pointed from the memory 
         
        navigating in the top bar.                                          
                                                                              
      + The **MEM NAV (+)** button increment the memory navigating pointer.     
                                                                              
      + The **MEM NAV (-)** button decrement the memory navigating pointer.     
                                                                              
                                                                              
The saving & export functionnalities:
*************************************                                  
									    
      Ghobdcalc provide an mechanic to save the content of operations and    
      
      export it as an computing datasheet in 3 differents files format.      
									    
      - The **SAVING** button save the current operation for exporting it in    
	    
	    the computing datasheet.                                            
									    
      - The **Export as** button reachable throught the menu button will        
	    
	    display an export settings windows where you can set how the        
	    
	    datasheet will be generate.                                         
									    
	You can export the saved operations as                              
									    
	+ An formatted text file.                                          
									    
	+ An simple csv (Comma Separated Value) file.                      
	  
	  Chart with multiple columns.                                     
									    
	+ An high configurable html file.                                  
	  
	  where the operations are presented in an table.                  
                                                                              


This programm is under copyright from the GPL GNU GENERAL PUBLIC LICENSE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

.. 

   **Ghobdcalc** (for Graphical Hexadecimal Octal Binar Decimal Calculator)
   
   an multibase calculator with several functionnalities...  
   
   Copyright (C) 2014 Brüggemann Eddie.

   This file is part of **Ghobdcalc**.
   
   **Ghobdcalc** is free software: you can redistribute it and/or modify
   
   it under the terms of the GNU General Public License as published by
   
   the Free Software Foundation, either version 3 of the License, or
   
   (at your option) any later version.

   **Ghobdcalc** is distributed in the hope that it will be useful,
   
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   
   along with **Ghobdcalc**. If not, see <http://www.gnu.org/licenses/> 
   
   
   
                     


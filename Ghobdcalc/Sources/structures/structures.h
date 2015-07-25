

/** Operand placeholder structure used for computing */
struct Operande {
  gchar *operande_string ;
  
  union Operande_digit{
    long long operande_int ;
    long double operande_float;
  } operande_digit ;

  gboolean operande_is_float ;

  gchar *operande_bin_str ;
  gchar *operande_oct_str ;
  gchar *operande_hex_str ;
  gchar *operande_dec_str ;
  
  gint8 operand_base ;


} ;


/** Operation placeholder structure for getting result from 2 operand */
struct Operations {
  struct Operande operande_1 ;
  struct Operande operande_2 ;
  struct Operande result ;
  gint8 current_base ;
  gint8 current_operator ;
  
} ;

struct Memory_Management {
  int mem_counter ;
  int mem_nav_pos ;
} ;

struct Memory_Items {
  struct Operande memory_item ;
} ;


struct Saving_settings {
  char *title ;
  char *filepath ;
  _Bool fileset  ;
  uint8_t file_format ;
  uint8_t op1_format  ;
  uint8_t op2_format  ;
  uint8_t res_format  ;
  _Bool   use_default_format ;
  _Bool   display_title ;
  _Bool   display_bases ;
  _Bool   use_raw_notation ;

} ;

struct HTML_settings {
  char *fontname ;
  char *bg_color ;
  char *fg_color ;
  char *border_color ;
  uint8_t font_size  ;
  _Bool bold ;
  _Bool italic ;
  char *border_style ;
  char *border_type  ;
  uint8_t border_size ;
  
} ;





 
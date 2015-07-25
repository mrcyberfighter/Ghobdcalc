#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Ghobdcalc], [1.0.0], [mrcyberfighter@gmail.com])
AC_CONFIG_SRCDIR([.])
AC_CONFIG_HEADERS([config.h])





# Checks for programs.
AC_PROG_CC_C_O
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MKDIR_P
AC_PROG_RANLIB


HAVE_GTK_3=no


AC_CHECK_LIB([gtk-3],
             [gtk_window_new], 
            
            
            
            
            
            HAVE_GTK_3=yes,
           
            
             AC_MSG_ERROR(Cannot find gtk-3 !!!
            
    ***************           Ghobdcalc required gtk-3.     **************
    Install the gtk-3 library from your packet-manager or from the source.
    You most have the development files installed:
    The package is suffix with -dev or -devel and prefix with libgtk-3.
    Then retry to build Ghobdcalc...
    **********************************************************************
                  , 1)
            
              )
                 








# Checks for header files.
AC_CHECK_HEADERS([inttypes.h locale.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_STRTOD
AC_CHECK_HEADERS([inttypes.h locale.h stdlib.h string.h wchar.h tgmath.h])


#Warning about the libgtk-3 package.
if test "x${HAVE_GTK_3}" = xyes ; then
AC_MSG_NOTICE([gtk-3 warning:
 
     ***********         WARNING ABOUT THE gtk-3 PACKAGE         **********
     Make sure you get the development package from gtk+-3.0 installed the
     package is suffix with -dev or -devel and prefix with libgtk-3.
     **********************************************************************
    ])
fi 



AC_OUTPUT



echo "
  ************************ ${PACKAGE_STRING} **********************
 
  System check OK but take a look at the warnings upper.
   
  Package: ${PACKAGE_NAME}    
  Packages Dependencies: gtk-3, libm.
                        
  Version: ${PACKAGE_VERSION}
 
  ${PACKAGE_NAME} an multibase calculator with severals
  functionnalities.
 
  Author: Bruggemann Eddie.
  contact: ${PACKAGE_BUGREPORT}
 
  Now enter:
 
  $ make
  $ sudo make install
 
  To build and install ${PACKAGE_NAME}. "
/*****************************************************************************

macro_api.c

Examples of building APIs using preprocessor macros.

*****************************************************************************/

/*----------------------------------------------------------------------------
Includes
----------------------------------------------------------------------------*/

#include <stdio.h>

/*----------------------------------------------------------------------------
Macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------
Pre-processor double-expansion stringification.
----------------------------------------------------------*/
#define ppstr_( _s ) #_s
#define ppstr( _s ) ppstr_( _s )

/*----------------------------------------------------------
Example of using all variadic arguments.
----------------------------------------------------------*/
#define source_printf( ... ) \
    printf( __FILE__ ":" ppstr( __LINE__ ) "> " __VA_ARGS__ )

/*----------------------------------------------------------
Example of using named and variadic arguments.
----------------------------------------------------------*/
#define identified_printf( _id, ... ) \
    printf( ppstr( _id ) ": " __VA_ARGS__ )

/*----------------------------------------------------------------------------
Types and Structures
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
Memory Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
Module Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
Module Prototypes
----------------------------------------------------------------------------*/


/*--------------------------------------------------------------------
Program Entry Point
--------------------------------------------------------------------*/
int main( int argc, const char** argv ) {

    //Passing no arguments (since the macro does pass something itself).
    source_printf();

    printf( "\n" );

    //Passing a single argument.
    source_printf( "Hello World.\n" );

    //Passing two arguments.
    source_printf( "Hello %s.\n", "Foo" );

    //Passing the one named argument.
    identified_printf( 42 );

    printf( "\n" );

    //Passing one named argument and one extra argument.
    identified_printf( 43, "This is bar.\n" );

    //Making sure we can still pass our own data.
    identified_printf( 44, "This is %s.\n", "biz" );

    return 0;
}


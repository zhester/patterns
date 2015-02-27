/*****************************************************************************

jumping.c

Example of using setjmp/longjmp as error reporting/vectoring from a library.

*****************************************************************************/

/*----------------------------------------------------------------------------
Includes
----------------------------------------------------------------------------*/

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------------
Macros
----------------------------------------------------------------------------*/

#define API_ERROR ( 66 )            /* an error code for the API            */

#define api_get_status( _r ) ( ( _r )->jump_status )
                                    /* de-couple jump status member         */
#define api_setjmp( _r ) setjmp( ( _r )->jump_buffer )
                                    /* de-couple jump buffer member         */

/*----------------------------------------------------------------------------
Types and Structures
----------------------------------------------------------------------------*/

typedef struct api_s {              /* API resource type                    */
    unsigned long   api_data;       /* some data significant to the API     */
    jmp_buf         jump_buffer;    /* exception jump buffer                */
    int             jump_status;    /* the current status for the jump      */
} api_type;

/*----------------------------------------------------------------------------
Memory Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
Module Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
Module Prototypes
----------------------------------------------------------------------------*/

unsigned long api_call(                 /* important API function           */
    api_type*           resource,       /* API resource pointer             */
    unsigned long       value           /* user information for API usage   */
);                                      /* returns something useful         */

void api_init_resource(                 /* initialize the API's resource    */
    api_type*           resource        /* API resource pointer             */
);

/*----------------------------------------------------------------------------
Implementation
----------------------------------------------------------------------------*/

/*==========================================================================*/
int main(                               /* program entry point              */
    int                 argc,           /* number of arguments              */
    const char**        argv            /* list of arguments                */
) {                                     /* return program exit status       */

    /*------------------------------------------------------------------
    Local Variables
    ------------------------------------------------------------------*/
    unsigned long       api_data;       /* normal return value from API     */
    api_type            api_resource;   /* the resource used by the API     */
    int                 jump_result;    /* result of `setjmp()`             */

    /*------------------------------------------------------------------
    Here, the API helps us initialize its resource in our memory.
    ------------------------------------------------------------------*/
    api_init_resource( &api_resource );

    /*------------------------------------------------------------------
    Set the jump location using an API convenience macro.

    We can also do this ourselves as such:
        jump_result = setjmp( api_resource.jump_buffer );

    When `setjmp()` "returns" 0, the location is being set.
    When `setjmp()` "returns" non-zero, program execution has jumped to
    this location.
    ------------------------------------------------------------------*/
    jump_result = api_setjmp( &api_resource );
    if( jump_result != 0 ) {

        /*--------------------------------------------------------------
        The API encountered something it considers an exception to
        normal operation.  This API has decided to communicate exception
        codes via the jump's expanded value.
        --------------------------------------------------------------*/
        printf(
            "Encountered an exception with value %d.  API reports %d.\n",
            jump_result,
            api_get_status( &api_resource )
        );

        /*--------------------------------------------------------------
        Execution will continue from here, so we need to clean up, and
        bail out before allowing execution to start back into the API.
        --------------------------------------------------------------*/
        return EXIT_FAILURE;
    }

    /*------------------------------------------------------------------
    Use the API expecting everything to go fine.
    ------------------------------------------------------------------*/
    api_data = api_call( &api_resource, 42 );

    printf( "API call #1 returned %d.\n", api_data );

    /*------------------------------------------------------------------
    Use the API.  I got a bad feeling about this.
    ------------------------------------------------------------------*/
    api_data = api_call( &api_resource, 0 );

    printf( "API call #2 returned %d.\n", api_data );

    /*------------------------------------------------------------------
    Return to the shell.
    ------------------------------------------------------------------*/
    return EXIT_SUCCESS;
}


/*==========================================================================*/
unsigned long api_call(                 /* important API function           */
    api_type*           resource,       /* API resource pointer             */
    unsigned long       value           /* user information for API usage   */
) {                                     /* returns something useful         */

    /*------------------------------------------------------------------
    Perform some non-trival validation on how the API was called.
    ------------------------------------------------------------------*/
    if( value == 0 ) {

        /*--------------------------------------------------------------
        Set some additional information about why we're bailing out.
        --------------------------------------------------------------*/
        resource->jump_status = 99;

        /*--------------------------------------------------------------
        "Throw" an exception.
        --------------------------------------------------------------*/
        longjmp( resource->jump_buffer, API_ERROR );
    }

    /*------------------------------------------------------------------
    Return data because that's what we need to do.
    ------------------------------------------------------------------*/
    return value >> 1;
}


/*==========================================================================*/
void api_init_resource(                 /* initialize the API's resource    */
    api_type*           resource        /* API resource pointer             */
) {

    /*------------------------------------------------------------------
    This would be typical, library-style memory initialization and
    default value setup.
    ------------------------------------------------------------------*/
    memset( resource, 0, sizeof( api_type ) );
    resource->api_data = 26;
}


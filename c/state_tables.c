/****************************************************************************
    State Machine Using a Table

    State machines are bread-and-butter patterns for embedded systems.  The
    typical state machine is implemented with a state variable and a large
    switch-case construct to control execution.  The goal of this pattern is
    to make maintenance of the state machine more easily controlled without
    affecting performance.

    Maintenance of a state machine module involves the following actions:
        - Adding/removing states
        - Adding/removing transition events
        - Splitting/merging existing state execution
        - Altering transitions between states

    General Usage Rules
        - Do not allow direct access to the state variable
            - Provide functions that clearly describe the inputs
            - Use logic local to the state machine to perform the
                transitions based on inputs
****************************************************************************/

typedef unsigned char state_t;      //current state type

enum {                              //state machine states
    STATE_INIT,
    STATE_IDLE,
    STATE_ONE,
    STATE_TWO,
    STATE_THREE,
    STATE_NUM_STATES
};

typedef void ( *state_fn )( void ); //state execution function type

typedef struct state_table_s {
    state_t             state;
    state_fn            exec[ STATE_NUM_STATES ];
} state_table_t;


static void check_transition( void );
static void exec_init( void );
static void exec_idle( void );
static void exec_one( void );
static void exec_two( void );
static void exec_three( void );

static const state_table_t table = {
    STATE_INIT,
    {
        exec_init,
        exec_idle,
        exec_one,
        exec_two,
        exec_three
    }
};

static unsigned char input_a;
static unsigned int input_b;
static float input_c;


void state_init( void ) {
    //initializer code
}

void state_exec( void ) {
    //execute the current state
}

void state_input_a( unsigned char value ) {
    //input value "A" into the state machine
}
void state_input_b( unsigned int value ) {
    //input value "B" into the state machine
}
void state_input_c( float value ) {
    //input value "C" into the state machine
}


static void check_transition( void ) {
    //some code can be condensed with a common transition function
    //  in many cases, though, the transitions are explicitly coded
    //  in each execution function
}

static void exec_init( void ) {
    //execute init state
}

static void exec_idle( void ) {
    //execute idle state
}

static void exec_one( void ) {
    //execute state "1"
}

static void exec_two( void ) {
    //execute state "2"
}

static void exec_three( void ) {
    //execute state "3"
}


/*----------------------------------------------------------
Interface usage example.
----------------------------------------------------------*/
int main( int argc, char** argv ) {
    int loops = 100;

    //possible module initialization
    state_init();

    while( loops > 0 ) {

        //do system I/O here

        //adjust inputs into the state machine as needed
        state_input_a( 42 );
        state_input_b( 14400 );
        state_input_c( 3.14159f );

        //give the state machine some time to execute
        state_exec();

        loops -= 1;
    }
    return 0;
}





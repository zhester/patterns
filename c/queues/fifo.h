/****************************************************************************
    Abstracted FIFO

    The goal is to provide a general-purpose FIFO queue implementation that
    does not depend on the type of data being queued, and works without
    dynamic memory features.

    Core Requirements:
        - Overrun/underrun protection
        - Protectable critical sections (index/pointer updates)
        - Minimal/optional memory copying; two-step enqueue/dequeue
        - Allow users to operate in queue memory (allocate/free operations)
            - Allow freeing by pointer, index, and unique item ID
        - Non-destructive reference to current items
    Optional Requirements:
        - Add a method to auto-circulate when enqueuing
            - Will need to add drop statistics
        - Maximum, average, instantaneous allocation statistics
        - Item memory usage statistics (how much of a single item is really
            used for a transaction?)
        - Queue usage statistics (total data moved through queue)
    Possible Features:
****************************************************************************/

typedef struct fifo_item_s {
    void* data;
    long  length;
} fifo_item_t;

typedef struct fifo_s {
} fifo_t;



#define fifo_declare( _symbol, _len, _item_size )                            \
    fifo_item_t _symbol[ _len ]

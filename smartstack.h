#ifndef SMARTSTACK_H
#define SMARTSTACK_H

    /* DEBUG_SMARTSTACK ON/OFF SWITCH; LEFT DEFINED BY DEFAULT */
    #ifndef DEBUG_SMARTSTACK
        #define DEBUG_SMARTSTACK
    #endif

    #ifndef __cplusplus
        #include <stdbool.h>
    #endif

    #include <stdlib.h>

    struct smartstack_st
    {
        size_t capacity;
        size_t end_index;
        void* data;
    };
    typedef struct smartstack_st smartstack_t;

    smartstack_t* smartstack_construct(     size_t size_in_bytes);
    void smartstack_destruct(               smartstack_t** obj);

    void* smartstack_peek_raw(              smartstack_t* obj, size_t bytes);

    void smartstack_push_raw(               smartstack_t* obj, const char type[], void* value);

    void smartstack_pop_raw(                smartstack_t* obj, const char type[]);

    bool smartstack_isempty(                smartstack_t* obj);

    bool smartstack_isfull_raw(             smartstack_t* obj, const char type[]);

    #define smartstack_create(              NAME, SIZE_IN_BYTES) \
        smartstack_t* NAME __attribute__((__cleanup__(smartstack_destruct))) \
            = smartstack_construct(         SIZE_IN_BYTES)

    #define smartstack_peek(                INSTANCE, TYPE) \
        (TYPE*)smartstack_peek_raw(         INSTANCE, sizeof(TYPE))

    #define smartstack_push(                INSTANCE, TYPE, VALUE) \
        smartstack_push_raw(                INSTANCE, #TYPE, &VALUE)

    #define smartstack_pop(                 INSTANCE, TYPE) \
        smartstack_pop_raw(                 INSTANCE, #TYPE)

    #define smartstack_isfull(              INSTANCE, TYPE) \
        smartstack_isfull_raw(              INSTANCE, #TYPE)

#endif

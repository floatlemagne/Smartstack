#include "smartstack.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#ifdef DEBUG_SMARTSTACK
    #include <stdio.h>
    #include <inttypes.h>
    #define SMARTSTACK_LOG_BEGIN stdout, "\033[0;31m"
    #define SMARTSTACK_LOG_END "\033[0m"
#endif

smartstack_t*
smartstack_construct(size_t size_in_bytes)
{
    smartstack_t* new_stack = (smartstack_t*)malloc(sizeof(smartstack_t));
    assert(new_stack != NULL && "Construction of new smartstack failed!");

    new_stack->data         = malloc(size_in_bytes);
    new_stack->capacity     = size_in_bytes;
    new_stack->end_index    = 0;

    assert(new_stack->data != NULL && "Memory allocation of new smartstack failed!");
    
    #ifdef DEBUG_SMARTSTACK
        fprintf(SMARTSTACK_LOG_BEGIN "Constructing smartstack of %zu bytes @ 0x%p.\n\n" 
                SMARTSTACK_LOG_END, new_stack->capacity, new_stack);
    #endif

    return new_stack;
}

void
smartstack_destruct(smartstack_t** obj)
{
    #ifdef DEBUG_SMARTSTACK
        fprintf(SMARTSTACK_LOG_BEGIN "Automatically freeing smartstack of %zu bytes @ 0x%p as it exits scope.\n\n" 
                SMARTSTACK_LOG_END, (*obj)->capacity, *obj);
    #endif

    free((*obj)->data);
    free(*obj);

    *obj = NULL;
}

void*
smartstack_peek_raw(smartstack_t* obj, size_t bytes)
{
    size_t current_index = obj->end_index - 1;
    return ((char*)obj->data + ((bytes * current_index) * bytes));
}

void
smartstack_push_raw(smartstack_t* obj, const char type[], void* value)
{
    assert((!strcmp(type, "int") || !strcmp(type, "float") || !strcmp(type, "char") || !strcmp(type, "double")) && "Invalid or unsupported type!");

    if(!strcmp(type, "int")) {
        assert((obj->end_index < (obj->capacity / sizeof(int))) && "Stack overflow!");
        *((int*)(obj->data) + (obj->end_index * sizeof(int))) = *(int*)value;
        #ifdef DEBUG_SMARTSTACK
        fprintf(SMARTSTACK_LOG_BEGIN "Pushing element %zu @ 0x%p in smartstack @ 0x%p.\n\n" 
                SMARTSTACK_LOG_END, obj->end_index, ((int*)(obj->data) + (obj->end_index)), obj);
        #endif
    }
    else if(!strcmp(type, "float")) {
        assert((obj->end_index < (obj->capacity / sizeof(float))) && "Stack overflow!");
        *((float*)(obj->data) + (obj->end_index * sizeof(float))) = *(float*)value;
        #ifdef DEBUG_SMARTSTACK
        fprintf(SMARTSTACK_LOG_BEGIN "Pushing element %zu @ 0x%p in smartstack @ 0x%p.\n\n" 
                SMARTSTACK_LOG_END, obj->end_index, ((float*)(obj->data) + (obj->end_index)), obj);
        #endif
    }
    else if(!strcmp(type, "char")) {
        assert((obj->end_index < (obj->capacity / sizeof(char))) && "Stack overflow!");
        *((char*)(obj->data) + (obj->end_index)) = *(char*)value;
        #ifdef DEBUG_SMARTSTACK
        fprintf(SMARTSTACK_LOG_BEGIN "Pushing element %zu @ 0x%p in smartstack @ 0x%p.\n\n" 
                SMARTSTACK_LOG_END, obj->end_index, ((char*)(obj->data) + (obj->end_index)), obj);
        #endif
    }
    else if(!strcmp(type, "double")) {
        assert((obj->end_index < (obj->capacity / sizeof(double))) && "Stack overflow!");
        *((double*)(obj->data) + (obj->end_index * sizeof(double))) = *(double*)value;
        #ifdef DEBUG_SMARTSTACK
        fprintf(SMARTSTACK_LOG_BEGIN "Pushing element %zu @ 0x%p in smartstack @ 0x%p.\n\n" 
                SMARTSTACK_LOG_END, obj->end_index, ((double*)(obj->data) + (obj->end_index)), obj);
        #endif
    }
    obj->end_index += 1;
}

void
smartstack_pop_raw(smartstack_t* obj, const char type[])
{
    assert((!strcmp(type, "int") || !strcmp(type, "float") || !strcmp(type, "char") || !strcmp(type, "double")) 
    && "Invalid or unsupported type!");
    
    if(obj->end_index > 0) {
        obj->end_index -= 1;
        if(!strcmp(type, "int")) {
        #ifdef DEBUG_SMARTSTACK
            fprintf(SMARTSTACK_LOG_BEGIN "Popping element %zu @ 0x%p in smartstack @ 0x%p.\n\n" 
                    SMARTSTACK_LOG_END, obj->end_index, ((int*)(obj->data) + (obj->end_index)), obj);
            #endif
        }
        else if(!strcmp(type, "float")) {
            #ifdef DEBUG_SMARTSTACK
            fprintf(SMARTSTACK_LOG_BEGIN "Popping element %zu @ 0x%p in smartstack @ 0x%p.\n\n" 
                    SMARTSTACK_LOG_END, obj->end_index, ((float*)(obj->data) + (obj->end_index)), obj);
            #endif
        }
        else if(!strcmp(type, "char")) {
            #ifdef DEBUG_SMARTSTACK
            fprintf(SMARTSTACK_LOG_BEGIN "Popping element %zu @ 0x%p in smartstack @ 0x%p.\n\n" 
                    SMARTSTACK_LOG_END, obj->end_index, ((char*)(obj->data) + (obj->end_index)), obj);
            #endif
        }
        else if(!strcmp(type, "double")) {
            #ifdef DEBUG_SMARTSTACK
            fprintf(SMARTSTACK_LOG_BEGIN "Popping element %zu @ 0x%p in smartstack @ 0x%p.\n\n" 
                    SMARTSTACK_LOG_END, obj->end_index, ((double*)(obj->data) + (obj->end_index)), obj);
            #endif
        }
    }
}

bool
smartstack_isempty(smartstack_t* obj)
{
    return obj->end_index == 0;
}

bool
smartstack_isfull_raw(smartstack_t* obj, const char type[])
{
    assert((!strcmp(type, "int") || !strcmp(type, "float") || !strcmp(type, "char") || !strcmp(type, "double")) 
    && "Invalid or unsupported type!");
    
    if(!strcmp(type, "int"))                return obj->end_index == obj->capacity / sizeof(int);
    else if(!strcmp(type, "float"))         return obj->end_index == obj->capacity / sizeof(float);
    else if(!strcmp(type, "char"))          return obj->end_index == obj->capacity / sizeof(char);
    else if(!strcmp(type, "double"))        return obj->end_index == obj->capacity / sizeof(double);
    return 0;
}
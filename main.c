#include "smartstack.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    smartstack_create(stack1, 4);                   /* Creating a smartstack named stack1 of 4 bytes. */

    int value = 100;

    smartstack_push(stack1, int, value);            /* Pushing 4-byte value onto the stack. Your stack is now full,
                                                       so pushing any more will trigger stack overflow. Value parameter
                                                       must be a variable. */

    smartstack_pop(stack1, int);                    /* Popping off element 0 (value of 100). Now the stack is empty. */

    int* elem = smartstack_peek(stack1, int);       /* Set pointer to point at element at top of stack1. */

    printf("%d", *elem);                            /* Viewing topmost element of stack. This will print a garbage value. */
    
    smartstack_create(stack2, 128);
    
    for(unsigned int i = 0; i < stack2->capacity / sizeof(int); ++i)
    {
        smartstack_push(stack2, int, i);
        /* Define DEBUG_SMARTSTACK in smartstack.h to see where it's pushed in memory */
    }

    /* Both stack1 and stack2 automatically destruct once they're out of scope */

    return 0;
}
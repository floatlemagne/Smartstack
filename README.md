# Smartstack
A C library for stack-like dynamic data structures

## Important Note
This library is intended to be compiled on GCC. Using any different compiler (e.g. Clang, MSVC, etc.) will lead to unintended memory leaks due to an implementation of SBRM, among other problems.

## About
The header file smartstack.h provides functions and macros for the implementation of a stack-like dynamic data structure. It provides bounds-checking, stack-like behavior, scope-based resource management, and memory leak prevention.

## How-to
Along with this program is an example program to show how to create a smartstack, and perform stack-like operations such as pushing, popping, and peeking at elements in the data structure. I will not cover the intricacies of smartstack, however you may view the header file (smartstack.h) and implementation file (smartstack.c) to see how it works inside.
### Functions to never use
Never use these functions anywhere in your code:
- `smartstack_construct()`
- `smartstack_destruct()`
- `smartstack_push_raw()`
- `smartstack_pop_raw()`
- `smartstack_peek_raw()`
- `smartstack_isfull_raw()`
Unless you fully understand how these functions work, using these functions will lead to undefined behavior if not careful. Instead, use the `smartstack_create()` macro to call `smartstack_construct_raw()`, and the macro counterparts to the functions ending in `_raw`.
### Debugging your smartstack
If you would like to view the memory addresses that values are placed in inside your code, then you must place this statement inside smartstack.h: `#define DEBUG_SMARTSTACK`. This will allow you to see the memory address of your struct and its elements as you push back and pop off elements in the stack.
### Makefile
To quickly compile and run your code, you can use the Makefile provided here. Simply replace `TARGET`'s value with the name of your file (the one with your `main()` function).

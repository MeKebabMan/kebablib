#ifndef KEBAB_H
#define KEBAB_H

#ifdef __cplusplus
extern "C" 
{
#endif


/*
KebabLib!

A library containing useful marcos and functions for my projects, feel free to use!

Library flags:

KEBAB_DEBUG (Enables debug logs and the use of assertions)

KEBAB_ABORT (Enables abort() on fatal errors handled by the library)

*/

// Headers

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// Marcos

/**
    Forces the inline (Gives a strong-hint to the compiler)
    WARNING: INLINE MAY NOT WORK WITH "-O0" FLAG OR WITH COMPLEX STUFF EVEN WITH "force_inline"!
*/
#if defined(__GNUC__) || defined(__clang__)

#define force_inline __attribute__((always_inline)) inline

#elif defined(__MSC_VER__)

#define force_inline __forceinline

#else

#define force_inline inline

#endif

/// if the character is a math operator
#define isMathOperator(c) ((c) == '+' || (c) == '-' || (c) == '*' || (c) == '/' || (c) == '^' || (c) == '%')

/// Frees the pointer using free(1) and then sets it to NULL
#define nullFree(pointer) \
        do { \
            free((pointer)); \
            (pointer) = NULL; \
        } while(0);

// Functions

/**
    Turns a string into a integar
    SUPPORT: +1234, -1234
    WARNING: DOES NOT SUPPORT DECIMALS
    RETURN: 0 for success, -1 for failure
*/
int strToInt(const char* __restrict__ src, intmax_t* _out, size_t nbytes);

/**
    Turns a string into a integar
    SUPPORT: +1234
    WARNING: DOES NOT SUPPORT DECIMALS OR NEGATIVE VALUES!
    RETURN: 0 for success, -1 for failure
*/
int strToUint(const char* __restrict__ src, uintmax_t* _out, size_t nbytes);

/**
    Checks if the string is integar only!
    SUPPORT: +1234, -1234
    WARNING: DOES NOT SUPPORT DECIMALS
    RETURN: 1 (true) for YES, 0 (false) for NO
*/
bool isIntegar(const char* __restrict__ src, size_t nbytes);

/**
    Turns a string into a float
    SUPPORT: 1.34, .5, 523, +1.34, 1.34e2, -1.34, 1.34e+343, 1.34e-34 (EXPONENT AND FRACTIONS)
    WARNING: DO NOT USE THIS FOR HANDLING DOUBLE!
    RETURN: 0 for success, -1 for failure
*/
int strToFloat(const char* __restrict__ src, float* _out, size_t nbytes);

/**
    Turns a string into a double
    SUPPORT: 1.34, .5, 523, +1.34, 1.34e2, -1.34, 1.34e+343, 1.34e-34 (EXPONENT AND FRACTIONS)
    RETURN: 0 for success, -1 for failure
*/
int strToDouble(const char* __restrict__ src, double* _out, size_t nbytes);

/**
    Checks if the string is a decimal
    SUPPORT: 1.34, .5, 523, +1.34, 1.34e2, -1.34, 1.34e+343, 1.34e-34 (EXPONENT AND FRACTIONS)
    RETURN: 1 (true) for YES, 0 (false) for NO
*/
bool isDecimal(const char* __restrict__ src, size_t nbytes);

/** 
    Calloc(2) + memcpy(3), simple, predictable and effective, also safer then realloc(2) because it wont silently change memory locations causing dangling pointers
    INFO: New memory will be allocated using calloc(2) and your old memory will be safely copied using memcpy(3) and your old memory will be freed and its variable will be replaced with the new memory
    NOTES: ResizeMemory(3) WILL abort() IF calloc(2) fails (The current state is PROBABLY unsafe) ALSO make sure that (void** restrict memory) IS A POINTER TO A VARIABLE!
    RETURN: 0 for success, -1 for failure
*/
int resizeMemory(void** __restrict__ memory, size_t oldMemory, size_t newMemory);

/**
    FNV-1a 32bit hash, simple and effective!
    RETURN: Hash
*/
uint32_t simpleHashU32(const void* __restrict__ src, size_t nbytes);

/**
    FNV-1a 64bit hash, simple and effective!
    RETURN: Hash
*/
uint64_t simpleHashU64(const void* __restrict__ src, size_t nbytes);

#ifdef __cplusplus
}
#endif

#endif 
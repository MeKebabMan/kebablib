/**
* @file kebablib.h
* @brief A library containing useful marcos and functions for my projects.
*/

#ifndef KEBAB_H
#define KEBAB_H

#ifdef __cplusplus
extern "C" 
{
#endif

// Headers

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// Macros 

/**
* @brief Forces the inline (Gives a strong-hint to the compiler)
* @note Inline may still be rejected by the compiler if it is too complex or uses va_args
*/
#if defined(__GNUC__) || defined(__clang__)

#define force_inline __attribute__((always_inline)) inline

#elif defined(_MSC_VER)

#define force_inline __forceinline

#else

#define force_inline inline

#endif

/**
* @brief Is a math operator.
* @note Supported operators: +, -, *, /, ^, %
*/
#define isMathOperator(c) ((c) == '+' || (c) == '-' || (c) == '*' || (c) == '/' || (c) == '^' || (c) == '%')

/**
* @brief Frees the pointer and sets its variable to NULL
*/
#define nullFree(pointer) \
        do { \
            if ((pointer) != NULL) { \
                free((pointer)); \
                (pointer) = NULL; \
            } \
        } while(0);

/**
* @brief Safely change pointer values
*/
#define nullSet(pointer, value) \
        do { \
            if ((pointer) != NULL) { \
                *(pointer) = (value); \
            } \
        } while(0);        

// Functions

/**
* @brief Turns a string into a integer.
*
* @param src The input string.
* @param out A pointer to store the integer.
* @param nbytes Number of bytes to read.
* @return 0 on success, -1 on failure.
*
* @note Supports -1234, +1234. Does NOT support decimals!
*/
int strToInt(const char* __restrict__ src, intmax_t* _out, size_t nbytes);

/**
* @brief Turns a string into a integer.
*
* @param src The input string.
* @param out A pointer to store the integer.
* @param nbytes Number of bytes to read.
* @return 0 on success, -1 on failure.
*
* @note Supports +1234. Does NOT support decimals and negative values!
*/
int strToUint(const char* __restrict__ src, uintmax_t* _out, size_t nbytes);

/**
* @brief Checks if the the string is a integer.
*
* @param src The input string.
* @param nbytes Number of bytes to read.
* @return 1 (true) for YES, 0 (false) for NO.
*
* @note Supports +1234, -1234. Does NOT support decimals!
*/
bool isIntegar(const char* __restrict__ src, size_t nbytes);

/**
* @brief Turns a string into a float.
*
* @param src The input string.
* @param out A pointer to store the float.
* @param nbytes Number of bytes to read.
* @return 0 on success, -1 on failure.
*
* @note Supports 1.34, .5, 523, +1.34, 1.34e2, -1.34, 1.34e+343, 1.34e-34. Do not use this for handling double!
*/
int strToFloat(const char* __restrict__ src, float* _out, size_t nbytes);

/**
* @brief Turns a string into a double.
* 
* @param src The input string.
* @param out A pointer to store the double.
* @param nbytes Number of bytes to read.
* @return 0 on success, -1 on failure.
*
* @note Supports 1.34, .5, 523, +1.34, 1.34e2, -1.34, 1.34e+343, 1.34e-34 (EXPONENT AND FRACTIONS) 
*/
int strToDouble(const char* __restrict__ src, double* _out, size_t nbytes);

/**
* @brief Checks if the string is a decimal.
*
* @param src The input string.
* @param nbytes Number of bytes to read.
* @return 1 (true) for YES, 0 (false) for NO.
*
* @note Supports 1.34, .5, 523, +1.34, 1.34e2, -1.34, 1.34e+343, 1.34e-34 (EXPONENT AND FRACTIONS)
*/
bool isDecimal(const char* __restrict__ src, size_t nbytes);

/**
* @brief Uses calloc(2) + memcpy(3) to resize memory in a simple, safe and predictable way.
*
* @param memory A pointer to the VARIABLE that holds a pointer to the MEMORY (void**)
* @param oldMemory The size of the old memory.
* @param newMemory The size of the new memory.
* @return 0 on success, -1 on failure
* 
* @note Safely copies memory using memcpy(3) and if you define KEBAB_ABORT it will abort() on fatal errors 
*/
int resizeMemory(void** __restrict__ memory, size_t oldMemory, size_t newMemory);

/**
* @brief FNV-1a 32bit hash, simple and effective!
*
* @param src The input.
* @param nbytes Number of bytes to read.
* @return Hash
*/
uint32_t simpleHashU32(const void* __restrict__ src, size_t nbytes);

/**
* @brief FNV-1a 64bit hash, simple and effective!
*
* @param src The input.
* @param nbytes Number of bytes to read.
* @return Hash
*/
uint64_t simpleHashU64(const void* __restrict__ src, size_t nbytes);

#ifdef __cplusplus
}
#endif

#endif 
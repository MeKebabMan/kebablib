#include <kebablib.h>
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Macros I decided to define to help me out for this FILE
*/

#ifdef KEBAB_ABORT

#define kebab_abort() abort();

#else

#define kebab_abort() (void)0

#endif

/*
    Define macros for more readable boolean returns
*/

#define KEBAB_YES 1
#define KEBAB_NO 0

#ifdef KEBAB_DEBUG

#define kebab_log(stream, message) \
    do { \
        fputs("KebabLib: ", (stream)); \
        fputs((message), (stream)); \
        fputc('\n', (stream)); \
    } while(0);

#define fkebab_log(stream, format, ...) \
    do { \
        fprintf((stream), "KebabLib: (%s: %s) " format "\n", __FILE__, __func__, __VA_ARGS__); \
    } while(0);

/*
    Define a macro for assertions..
*/

#ifndef NDEBUG
#define kebab_assert(expression) \
                    do {\
                        assert((expression));\
                    } while(0);
#else
#define kebab_assert(expression) (void)0
#endif

#else
#define kebab_log(stream, message) (void)0
#define fkebab_log(stream, format, ...) (void)0
#define kebab_assert(expression) (void)0
#endif

/*
    Number / deicmal functions

    I created these because the glibc versions of these do a bit extra which kind of slows it down or makes it harder to work with..
*/

int strToInt(const char* restrict src, intmax_t* out, size_t nbytes) {
    if (src == NULL || out == NULL) {
        kebab_log(stdout, "Got NULL arguments");
        return -1;
    }

    *out = 0;

    if (nbytes == 0) {
        return 0;
    }

    bool isNegative = false;
    size_t bytesRead = 0;
    
    if (*src == '-') {
        src++;
        bytesRead++;
        isNegative = true;
    }

    while (*src != '\0' && bytesRead != nbytes) {
        kebab_assert(bytesRead < nbytes);

        if (*src >= 48 && *src <= 57) {

            intmax_t integar = *src - 48;

            *out = *out * 10 + integar;

        } else {
            fkebab_log(stdout, "Unexpected character '%c'", *src);
            return -1;
        }

        src++;
        bytesRead++;
    }

    if (isNegative) {
        *out = *out * -1;
    }

    return 0;
}

int strToUint(const char *restrict src, uintmax_t *out, size_t nbytes) {
    if (src == NULL || out == NULL) {
        kebab_log(stderr, "Got NULL arguments");
        return -1;
    }

    *out = 0;
    
    if (nbytes == 0) {
        return 0;
    }

    size_t bytesRead = 0;
    while (*src != '\0' && bytesRead != nbytes) {
        kebab_assert(bytesRead < nbytes);

        if (*src >= 48 && *src <= 57) {

            uintmax_t integar = *src - 48;

            *out = *out * 10 + integar;

        } else {
            fkebab_log(stdout, "Unexpected character '%c'", *src);
            return -1;
        }

        src++;
        bytesRead++;
    }

    return 0;
}

bool isIntegar(const char *restrict src, size_t nbytes) {

    if (src == NULL) {
        kebab_log(stderr, "Got NULL arguments");
        return KEBAB_NO;
    }

    if (nbytes == 0) {
        return KEBAB_YES;
    }

    size_t bytesRead = 0;
    
    if (*src == '-' || *src == '+') {
        src++;
        bytesRead++;
    }

    while (*src != '\0' && bytesRead != nbytes) {
        kebab_assert(bytesRead < nbytes);

        if (*src >= 48 && *src <= 57) {
            src++;
            bytesRead++;
        
            continue;
        }

        fkebab_log(stdout, "Unexpected character '%c'", *src);
        return KEBAB_NO;
    }

    return KEBAB_YES;
}

int strToFloat(const char* restrict src, float* out, size_t nbytes) {
    if (src == NULL || out == NULL) {
        kebab_log(stderr, "Got NULL arguments");
        return -1;
    }

    *out = 0.0f;

    if (nbytes == 0) {
        return 0; // skip
    }

    // Exponents
    bool inExponent = false;
    bool isNegativeExponent = false;
    intmax_t Exponent = 0;

    // Fractions
    bool isFraction = false;
    float fractionDivisor = 10.0f;

    // Digits
    bool isNegative = false;

    size_t bytesRead = 0;

    if (*src == '-') {
        src++;
        bytesRead++;
        isNegative = true;
    } else if (*src == '+') {
        src++;
        bytesRead++;
    }

    while (*src != '\0' && bytesRead != nbytes) {
        kebab_assert(bytesRead < nbytes); // Sanity check for over flows

        if (*src >= 48 && *src <= 57) {
            
            int digit = *src - 48;

            if (inExponent) {
                // Exponent
                Exponent = Exponent * 10 + digit;

            } else if (isFraction) {
                // Fraction
                *out = *out + ((float)digit / fractionDivisor);
                fractionDivisor = fractionDivisor * 10;

            } else {
                // Digit

                *out = *out * 10 + digit;

            }

        } else if (*src == '.') {
            // Fraction
            if (isFraction || inExponent) {
                kebab_log(stdout, "More then one '.' (Fraction) or '.' (Fraction) in 'E' (Exponent)");
                return -1;
            }

            isFraction = true;

        } else if (*src == 'e' || *src == 'E') {
            // Exponent
            if (inExponent) {
                kebab_log(stdout, "More then one 'E' (Exponent)");
                return -1;
            }

            inExponent = true;

            src++;
            bytesRead++;

            kebab_assert(bytesRead < nbytes); // Sanity check for over flows

            if (*src != '\0' && bytesRead != nbytes) {

                if (*src == '-') {
                    isNegativeExponent = true;
                } else if (*src == '+') {
                    // Nothing
                } else if (*src >= 48 && *src <= 57) {
                    continue;
                } else {
                    fkebab_log(stdout, "Unexpected character '%c' after 'E' (Exponent)", *src);
                    return -1;
                }

            } else {
                kebab_log(stdout, "Expected digit after 'E' (Exponent)");
                return -1;
            }

        } else {
            fkebab_log(stdout, "Unexpected character '%c'", *src);
            return -1;
        }
        
        src++;
        bytesRead++;

    }

    if (inExponent) {
        if (isNegativeExponent) {
            Exponent = Exponent * -1;
        }
        *out = *out * powf(10.0f, Exponent);
    }

    if (isNegative) {
        *out = *out * -1;
    }

    return 0;
}

int strToDouble(const char *restrict src, double *out, size_t nbytes) {
    if (src == NULL || out == NULL) {
        kebab_log(stderr, "Got NULL arguments");
        return -1;
    }

    *out = 0.0f; // Init out

    if (nbytes == 0) { // Skip useless parsing
        return 0;
    }

    // Exponents
    bool inExponent = false;
    bool isNegativeExponent = false;
    intmax_t Exponent = 0;

    // Fraction
    bool isFraction = false;
    double fractionDivisor = 10.0f;

    // Digit
    bool isNegative = false;

    size_t bytesRead = 0;

    if (*src == '-') {
        src++;
        bytesRead++;
        isNegative = true;
    } else if (*src == '+') {
        src++;
        bytesRead++;
    }

    while (*src != '\0' && bytesRead != nbytes) {
        kebab_assert(bytesRead < nbytes); // Sanity checks

        if (*src >= 48 && *src <= 57) {
            // Digit

            int digit = *src - 48;

            if (inExponent) {

                Exponent = Exponent * 10 + digit;

            } else if (isFraction) {

                *out = *out + ((double)digit / fractionDivisor);
                fractionDivisor = fractionDivisor * 10;

            } else {

                *out = *out * 10 + digit;

            }

        } else if (*src == '.') {
            // Fraction
            if (isFraction || inExponent) {
                kebab_log(stdout, "More then one '.' (Fraction) or '.' (Fraction) after 'E' (Exponents)");
                return -1;
            }

            isFraction = true;

        } else if (*src == 'e' || *src == 'E') {
            // Exponent
            if (inExponent) {
                kebab_log(stdout, "More then one 'E' (Exponent)");
                return -1;
            }

            inExponent = true;

            src++;
            bytesRead++;

            kebab_assert(bytesRead < nbytes);
            
            if (*src != '\0' && bytesRead != nbytes) {
                
                if (*src == '-') {
                    isNegativeExponent = true;
                } else if (*src == '+') {
                    // NOTHING
                } else if (*src >= 48 && *src <= 57) {
                    continue; // Skip incrementing..
                } else {
                    fkebab_log(stdout, "Unexpected character '%c'", *src);
                    return -1; 
                }

            } else {
                kebab_log(stdout, "Expected digit after 'E' (Exponent)");
                return -1;
            }

        } else {
            fkebab_log(stdout, "Unexpected character '%c'", *src);
            return -1;
        }

        src++;
        bytesRead++;
    }

    if (inExponent) {
        if (isNegativeExponent) {
            Exponent = Exponent * -1;
        }
        *out = *out * pow(10.0f, Exponent);
    }

    if (isNegative) {
        *out = *out * -1;
    }

    return 0;
}

bool isDecimal(const char *restrict src, size_t nbytes) {
    if (src == NULL) {
        kebab_log(stderr, "Got NULL arguments");
        return KEBAB_NO;
    }

    if (nbytes == 0) { // Skip useless parsing
        return KEBAB_YES;   
    }

    size_t bytesRead = 0;    

    if (*src == '-' || *src== '+') {
        src++;
        bytesRead++;        
    }

    bool hasExponent = false;
    bool isFraction = false;

    while (*src != '\0' && bytesRead != nbytes) {
        kebab_assert(bytesRead < nbytes);

        if (*src == '.') {
            // Fraction
            if (isFraction || hasExponent) {
                kebab_log(stdout, "More then one '.' or '.' (Fraction) in 'E' (Exponent)");
                return KEBAB_NO;
            }

            isFraction = true;
            src++;
            bytesRead++;
            continue;
        }

        if (*src == 'e' || *src == 'E') {
            // Exponent
            if (hasExponent) {
                kebab_log(stdout, "More then one 'E' (Exponent)");
                return KEBAB_NO;
            }

            hasExponent = true;

            src++;
            bytesRead++;

            kebab_assert(bytesRead < nbytes);

            if (*src != '\0' && bytesRead != nbytes) {

                if (*src == '+' || *src == '-') {
                    src++;
                    bytesRead++;
                } else if (*src >= 48 && *src <= 57) {
                    src++;
                    bytesRead++;
                } else {
                    fkebab_log(stdout, "Unexpected character '%c' after 'E' (Exponent)", *src);
                    return KEBAB_NO;
                }

            } else {
                kebab_log(stdout, "Expected digit after 'E' (Exponent)");
                return KEBAB_NO;
            }
            
            continue;
        }

        if (*src >= 48 && *src <= 57) {
            src++;
            bytesRead++;
            continue;
        }

        fkebab_log(stdout, "Unexpected character '%c'", *src);
        return KEBAB_NO;
    }

    return KEBAB_YES;
}

/*
    Memory functions
*/

int resizeMemory(void **restrict memory, size_t oldMemory, size_t newMemory) {
    if (memory == NULL || *memory == NULL) {
        kebab_log(stderr, "Got NULL arguments or a pointer to NULL");
        return -1;
    }

    if (newMemory == 0) {
        
        nullFree(*memory);

        return 0;
    }

    // Allocate new memory
    void* resizedMem = calloc(newMemory, 1);
    if (resizedMem == NULL) {
        
        perror("calloc");
        kebab_log(stderr, "FAILED TO ALLOCATE MEMORY");
        kebab_abort();

        return -1;
    }

    size_t safeCopyMem = oldMemory;
    if (safeCopyMem > newMemory) {
        safeCopyMem = newMemory;
    }

    memcpy(resizedMem, *memory, safeCopyMem);

    // Free old memory
    free(*memory);

    // Replace pointer
    *memory = resizedMem;

    return 0;
}

/*
    Hashing functions
*/

uint32_t simpleHashU32(const void* restrict src, size_t nbytes) {

    uint32_t hash = 2166136261u;
    uint32_t prime = 16777619u;

    for (size_t index = 0; index < nbytes; index++) {
        hash = hash ^ ((const uint8_t*)src)[index];
        hash = hash * prime; 
    }

    return hash;
}

uint64_t simpleHashU64(const void *restrict src, size_t nbytes) {

    uint64_t hash = 14695981039346656037u;
    uint64_t prime = 1099511628211u;
    
    for (size_t index = 0; index < nbytes; index++) {
        hash = hash ^ ((const uint8_t*)src)[index];
        hash = hash * prime;
    }

    return hash;
}
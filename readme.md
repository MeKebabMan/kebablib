# KebabLib

A library containing useful functions and marcos for my projects, feel free to use!

### Notes

I will continue on building up this library by adding functions and marcos that I find useful while building my projects, I am still learning so feel free to give me advice!

### Library flags

You can add the following:

``-DKEBAB_DEBUG`` to enable debug logs and assertions.

``-DKEBAB_ABORT`` to enable abort on fatal errors.

### Guide to compiling

You can use the makefile and create a .so / .dll

```bash
# EXAMPLE
make CompileLib=true LibExtension=dll
```

OR you can manually compile by just dropping the .c and .h into your project directory and compiling it like its own of your own, however please compile with ``-lm`` as this library uses functions like ``pow()`` and etc

```bash
# EXAMPLE
gcc kebablic.c -o something.out -Iinclude -lm
```

### Functions
```c

/**
    Turns a string into a integar
    SUPPORT: +1234, -1234
    WARNING: DOES NOT SUPPORT DECIMALS
    RETURN: 0 for success, -1 for failure
*/
intmax_t strToInt()

/**
    Turns a string into a integar
    SUPPORT: +1234
    WARNING: DOES NOT SUPPORT DECIMALS OR NEGATIVE VALUES!
    RETURN: 0 for success, -1 for failure
*/
uintmax_t strToUint()

/**
    Checks if the string is integar only!
    SUPPORT: +1234, -1234
    WARNING: DOES NOT SUPPORT DECIMALS
    RETURN: 1 (true) for YES, 0 (false) for NO
*/
_Bool isIntegar()

/**
    Turns a string into a float
    SUPPORT: 1.34, .5, 523, +1.34, 1.34e2, -1.34, 1.34e+343, 1.34e-34 (EXPONENT AND FRACTIONS)
    WARNING: DO NOT USE THIS FOR HANDLING DOUBLE!
    RETURN: 0 for success, -1 for failure
*/
float strToFloat()

/**
    Turns a string into a double
    SUPPORT: 1.34, .5, 523, +1.34, 1.34e2, -1.34, 1.34e+343, 1.34e-34 (EXPONENT AND FRACTIONS)
    RETURN: 0 for success, -1 for failure
*/
double strToDouble()

/**
    Checks if the string is a decimal
    SUPPORT: 1.34, .5, 523, +1.34, 1.34e2, -1.34, 1.34e+343, 1.34e-34 (EXPONENT AND FRACTIONS)
    RETURN: 1 (true) for YES, 0 (false) for NO
*/
_Bool isDecimal()

/** 
    Calloc(2) + memcpy(3), simple, predictable and effective, also safer then realloc(2) because it wont silently change memory locations causing dangling pointers
    INFO: New memory will be allocated using calloc(2) and your old memory will be safely copied using memcpy(3) and your old memory will be freed and its variable will be replaced with the new memory
    NOTES: ResizeMemory(3) WILL abort() IF calloc(2) fails (The current state is PROBABLY unsafe) ALSO make sure that (void** restrict memory) IS A POINTER TO A VARIABLE!
    RETURN: 0 for success, -1 for failure
*/
int resizeMemory()

/**
    FNV-1a 32bit hash, simple and effective!
    RETURN: Hash
*/
uint32_t simpleHash32()

/**
    FNV-1a 64bit hash, simple and effective!
    RETURN: Hash
*/
uint64_t simpleHash64() // FNV-1a 64bit

```

### Marcos
```c

nullFree() // Frees the memory and sets its variable to NULL

force_inline // Gives a strong-hint to the compiler for inline

isMathOperator() // I dont think I need to explain this

```

### Contributing

Feel free to contribute! Just make sure you write clean and nice code also if your new to contributing dont be scared just try it out!
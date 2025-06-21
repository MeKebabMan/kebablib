# Functions

Kebablib has useful functions that may help you!

### String-handling functions

``strToInt``
* Params: src, out, nbytes
* Return: 0 on success, -1 on failure
* Note: Supports -1234, +1234. Does NOT support decimals!

``strToUint``
* Params: src, out, nbytes
* Return: 0 on success, -1 on failure
* Note: Supports +1234. Does NOT support decimals and negative values!

``isIntegar``
* Params: src, nbytes
* Return: 1 (true) for YES, 0 (false) for NO
* Note: Supports +1234, -1234. Does NOT support decimals!

``strToFloat``
* Params: src, out, nbytes
* Return: 0 on success, -1 on failure
* Note: Supports 1.34, .5, 523, +1.34, 1.34e2, -1.34, 1.34e+343, 1.34e-34. Do not use this for handling double!

``strToDouble``
* Params: src, out, nbytes
* Return: 0 on success, -1 on failure
* Note: Supports 1.34, .5, 523, +1.34, 1.34e2, -1.34, 1.34e+343, 1.34e-34 (EXPONENT AND FRACTIONS)

``isDecimal``
* Params: src, nbytes
* Return: 1 (true) for YES, 0 (false) for NO
* Note: Supports 1.34, .5, 523, +1.34, 1.34e2, -1.34, 1.34e+343, 1.34e-34 (EXPONENT AND FRACTIONS)


### Memory-handling functions

``resizeMemory``
* Brief: Uses calloc(2) + memcpy(3) to resize memory in a simple, safe and predictable way. 
* Params, memory (a pointer to a VARIABLE), oldMemory, newMemory
* Return: 0 on success, -1 on failure
* Note: Safely copies memory using memcpy(3) and if you define KEBAB_ABORT it will abort() on fatal errors

### Misc (stuff that are really simple to create)

In this case you can create these your self but theres no real point to be honest.. I created these just so I dont need to create them again.

``simpleHash32``
* Brief: FNV-1a 32bit hashing
* Params: src, nbytes
* Return: Hash

``simpleHash64``
* Brief: FNV-1a 64bit hashing
* Params: src, nbytes
* Return: Hash
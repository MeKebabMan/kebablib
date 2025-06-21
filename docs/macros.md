# Macros

Kebablib has a bunch of macros that help take advantage of certain compilers or get rid of the need to write the same exact marco for every project you do!

### Normal macros

``force_inline``
* Brief: Gives a strong-hint to the compiler to inline
* Note: The compiler may still reject the inline if it is too complex or uses va_args or ``-O0`` is enabled

### Function macros

``isMathOperator``
* Brief: is (X) a math operator?
* Params: c (char)
* Note: Supported operators: +, -, *, /, ^, %

``nullFree``
* Brief: Frees the pointer and sets its variable to NULL
* Note: uses ``free(1)`` to free the memory
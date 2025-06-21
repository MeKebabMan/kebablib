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
# Docs

Please take a look at the ``docs/`` directory in the repository

### Contributing

Feel free to contribute! Just make sure you write clean and nice code also if your new to contributing dont be scared just try it out!s
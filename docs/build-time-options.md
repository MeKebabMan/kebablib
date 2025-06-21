# Build time options

Kebablib has build-time options that change the libraries behavior.

### Avaliable options

``KEBAB_DEBUG``
* Enables debug logs and the use of ``assert()``
* Helps with catching bugs or incorrect use of certain functions
* Normally combined with AddressSanitizer and ``-g`` during development
* May hinder performance, do not use for release builds!

``KEBAB_ABORT``
* Enables the use of ``abort()`` on fatal errors
* Doesn't change performance just calls ``abort()`` on fatal errors
* If your program attempts to restart or continue even after a **FATAL** error then you shouldn't use this

Use these options by adding ``-DKEBAB_DEBUG`` or ``-DKEBAB_ABORT`` to your compiler flags

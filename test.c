#include <KebabLib.h>
#include <assert.h>
#include <stdint.h>
#include <assert.h>

/*

USED FOR TESTING! Some times main() is empty.. some times main() is not empty
theres just a lot of random stuff here for testing

*/

int main() {

    // Tests

    assert(isIntegar("-123", 4));
    assert(isDecimal("1.34e3", 6));

    assert(strToInt("-123", &(intmax_t){0}, 4) == 0);
    assert(strToUint("1234", &(uintmax_t){0}, 4) == 0);

    assert(strToFloat("1.34e1", &(float){0}, 6) == 0);
    assert(strToDouble("1.34e2", &(double){0}, 6) == 0);

    assert(simpleHashU32("Hello test", 10) == 4052702601);
    assert(simpleHashU64("Hello world", 11) == 2815866345377719495);

    /*

    #include <stdio.h>
    #include <stdlib.h>

    // Test with valgrind or ASan
    void* memory = malloc(5);
    if (memory == NULL) {
        puts("Failed to allocate memory for test");
        return -1;
    }

    assert(resizeMemory(&memory, 5, 2) == 0);

    free(memory);

    */



    return 0;
}
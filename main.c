#include "lib/strings.h"
#include "lib/io.h"
#include "lib/typedefs.h"
#include "lib/crypto.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void assert_reversed();
void assert_truncated();

int main() {
    clearscreen();
    assert_reversed();
    assert_truncated();

    char* my_string = readline("Input something: ");
    
    if (my_string == NULL) {
        eputs("[tests] readline() failed.");
        return 1;
    }

    printf("[tests] user input: %s\n", my_string);

    char* password = readpassword("ENTER PASSWORD (will not echo): ");

    if (password == NULL) {
        eputs("[tests] readpassword() failed.");
        return 1;
    }

    printf("\n[tests] password you entered: %s\n", password);
    printf("The fnv1a hash of your password: 0x%x\n", fnv1a_hash(password));
    eputs("[tests] this message should appear on stderr!");

    free(my_string);
    free(password);
    return 0;
}

void assert_reversed() {
    char* my_string = "Hello!";
    char* reversed = strrev(my_string);
    
    if (strcmp(reversed, "!olleH") == 0) {
        puts("[tests] strrev passed!");
    }
    else {
        eputs("[tests] strrev failed!");
        eprintf("strrev input: %s\nstrrev output: %s\n", my_string, reversed);
    }
    
    free(reversed);
}

void assert_truncated() {
    char* my_string = "Hello!";
    char* truncated = strtrunc(my_string, 3);
    
    if (strcmp(truncated, "Hel") == 0) {
        puts("[tests] strtrunc passed!");
    }
    else {
        eputs("[tests] strtrunc failed!");
        eprintf("strtrunc input: %s\nstrtrunc output: %s\n", my_string, truncated);
    }

    free(truncated);
}

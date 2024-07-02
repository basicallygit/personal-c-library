/*
 * various functions for handling
 * I/O operations
 *
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#define __clearscreen() system("cls")

#else
#include <unistd.h>
#include <termios.h>
#define __clearscreen() printf("\033[1;1H\033[2J")

#endif

#define eprintf(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define eputs(str) fprintf(stderr, "%s\n", str)

// Increment in chunks of 32 bytes per realloc
#define READLINE_BUF_INCREMENT 32

char* readline(const char* prompt) {
    if (prompt != NULL)
	printf("%s", prompt);
		
    char* input = malloc(READLINE_BUF_INCREMENT);
    if (input == NULL)
	return NULL;
	
    size_t size = 0;
    size_t capacity = READLINE_BUF_INCREMENT;

    int c;
    while((c = getchar()) != '\n' && c != EOF) {
	if (size + 1 >= capacity) {
	    capacity += READLINE_BUF_INCREMENT;
	    char* temp = realloc(input, capacity);
			
	    if (temp == NULL) {
		free(input);
		return NULL;
	    }
	    input = temp;
	}
	input[size++] = c;
    }

    input[size] = '\0';

    return input;
}

char* readpassword(const char* prompt) {
#ifdef _WIN32
    HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hstdin, &mode);
    SetConsoleMode(hstdin, mode & (~ENABLE_ECHO_INPUT));

    char* input = readline(prompt);
    SetConsoleMode(hstdin, mode);

#else
    struct termios old_settings, new_settings;

    tcgetattr(STDIN_FILENO, &old_settings);
    new_settings = old_settings;

    new_settings.c_lflag &= (~ECHO); //disable character echo
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

    char* input = readline(prompt);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings); //restore character echo

#endif
    return input;
}

void clearscreen() {
    __clearscreen();
}

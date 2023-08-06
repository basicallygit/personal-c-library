#ifndef IO_H
#define IO_H

#define eprintf(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define eputs(str) fprintf(stderr, "%s\n", str)

char* readline(const char* prompt);
char* readpassword(const char* prompt);
void clearscreen();

#endif

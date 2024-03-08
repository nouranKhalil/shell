#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LIMIT 100

int main() {
    char str[MAX_LIMIT];
    printf("Enter command with full path: ");
    fgets(str, MAX_LIMIT, stdin);

    // Remove trailing newline character
    str[strcspn(str, "\n")] = 0;

    const char delimiter[] = " ";
    char *token = strtok(str, delimiter);
    char *input[MAX_LIMIT]; // Adjusted to fit maximum number of arguments
    int size = 0;

    while (token != NULL && size < MAX_LIMIT - 1) { // Avoid overflow
        input[size++] = token;
        token = strtok(NULL, delimiter); 
    } 
    input[size] = NULL; // NULL terminate the argument list
    execvp(input[0], input);
    
    // If execvp fails, the following lines will be executed
    perror("execvp"); // Print error message
    return 1; // Return non-zero to indicate failure
}

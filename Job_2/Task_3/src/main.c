#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "string_processor.h"

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    while (getchar() != '\n'); // Очистка буфера
    
    while (1) {
        char* input = readline("Enter string (Ctrl+D to exit): ");
        if (!input) break;
        
        char* result = process_string(input, n);
        printf("Result: %s\n", result);
        
        free(input);
        free(result);
    }
    
    return 0;
}
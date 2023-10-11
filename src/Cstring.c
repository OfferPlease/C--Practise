#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // allocate memory on heap
    // char * str;
    // str = malloc(6*sizeof(char));
    // allocate memory on stack
    char str[6];
    // strcpy will automatically copy '\0'
    strcpy(str,"hello");
    printf("%s\n", str);
    printf("%d", strlen(str));
    // free(str);
    return 0;
}
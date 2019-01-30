#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t NUM_OF_ELEMENTS=10;

char* allocate_memory(void)
{
    char *str = (char*)malloc(sizeof(char)*NUM_OF_ELEMENTS);
    if (NULL == str) exit(1);
    return str;
}

void free_memory(char *str)
{
    (NULL == str) ? NULL : free(str);
}

void fill_memory(char *str)
{
    memset(str, '-', NUM_OF_ELEMENTS*sizeof(char));
}

int main()
{
    char *str=NULL;
    fill_memory(str);
    str=allocate_memory();
    printf("%s\n", str);
    free_memory(str);
    return 0;
}

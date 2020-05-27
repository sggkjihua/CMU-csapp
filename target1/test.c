
#include <stdio.h>    
#include <string.h>    
    
void evilfunction(char *name) {    
    char buffer[100];    
    strcpy(buffer, name); 
    printf("Xiaolin J %s\n", buffer);
}    
    
int main(int argc, char **argv) {    
    evilfunction(argv[1]);    
    return 0;    
}
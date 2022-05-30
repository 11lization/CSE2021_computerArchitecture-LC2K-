/* Assembler code fragment for LC-2K */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXLINELENGTH 1000
#define ADD 0
#define NOR 1
#define LW 2
#define SW 3
#define BEQ 4
#define JALR 5
#define HALT 6
#define NOOP 7

int readAndParse(FILE *, char *, char *, char *, char *, char *);

int isNumber(char *string){    
    /* return 1 if string is a number */
    int i;
    return( (sscanf(string, "%d", &i)) == 1);
}

int instructionTypeR(char *arg0, char *arg1, char*arg2){
    if(!isNumber(arg0) && !isNumber(arg1) && !isNumber(arg2)){
        printf("error: arg is not a number\n")
        exit(1);
    }

    int regA = atoi(arg0) << 19;
    int regB = atoi(arg1) << 16;
    int destReg = atoi(arg2);

    return regA | regB | destReg;
}

int instructionTypeI(char *arg0, char *arg1, char*arg2, int isBeq){
    if(!isNumber(arg0) && !isNumber(arg1)){
        printf("error: arg is not a number\n")
        exit(1);
    }

    int regA = atoi(arg0) << 19;
    int regB = atoi(arg1) << 16;
}

int instructionTypeJ(char *arg0, char *arg1){
    if(!isNumber(arg0) && !isNumber(arg1)){
        printf("error: arg is not a number\n")
        exit(1);
    }

    int regA = atoi(arg0) << 19;
    int regB = atoi(arg1) << 16;

    return regA | regB;
}

int main(int argc, char *argv[]){    
    char *inFileString, *outFileString;
    FILE *inFilePtr, *outFilePtr;
    char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH],
            arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];
    if (argc != 3) {
        printf("error: usage: %s <assembly-code-file> <machine-code-file>\n",
            argv[0]);
        exit(1);
    }
    inFileString = argv[1];
    outFileString = argv[2];
    inFilePtr = fopen(inFileString, "r");
    if (inFilePtr == NULL) {
        printf("error in opening %s\n", inFileString);
        exit(1);
    }
    outFilePtr = fopen(outFileString, "w");
    if (outFilePtr == NULL) {
        printf("error in opening %s\n", outFileString);
        exit(1);
    }
    /* here is an example for how to use readAndParse to read a line from
        inFilePtr */
    if (! readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2) ) {
        /* reached end of file */
    }
    /* this is how to rewind the file ptr so that you start reading from the
        beginning of the file */
    rewind(inFilePtr);
    /* after doing a readAndParse, you may want to do the following to test the
        opcode */
    while(readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)){
        int machineCode = 0;
        
        if(!strcmp(opcode, "add"))
            machineCode = (ADD << 22) | instructionTypeR(arg0, arg1, arg2);
        else if(!strcmp(opcode, "nor"))
            machineCode = (NOR << 22) | instructionTypeR(arg0, arg1, arg2);
        else if(!strcmp(opcode, "lw"))
            machineCode = (LW << 22) | instructionTypeI(arg0, arg1, arg2, 0);
        else if(!strcmp(opcode, "sw"))
            machineCode = (SW << 22) | instructionTypeI(arg0, arg1, arg2, 0);
        else if(!strcmp(opcode, "beq"))
            machineCode = (BEQ << 22) | instructionTypeI(arg0, arg1, arg2, 1);
        else if(!strcmp(opcode, "jalr"))
            machineCode = (JALR << 22) | instructionTypeI(arg0, arg1);
        else if(!strcmp(opcode, "halt"))
            machineCode = HALT << 22;
        else if(!strcmp(opcode, "noop"))
            machineCode = NOOP << 22;
        else if(!strcmp(opcode, ".fill"))

    }
    return(0);
}/*
 * Read and parse a line of the assembly-language file.  Fields are returned
 * in label, opcode, arg0, arg1, arg2 (these strings must have memory already
 * allocated to them).
 *
 * Return values:
 *     0 if reached end of file
 *     1 if all went well
 *
 * exit(1) if line is too long.
 */
int readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0, char *arg1, char *arg2){
    char line[MAXLINELENGTH];
    char *ptr = line;
    /* delete prior values */
    label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0';
    /* read the line from the assembly-language file */
    if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL) {
        /* reached end of file */
        return(0);
    }
    /* check for line too long (by looking for a \n) */
    if (strchr(line, '\n') == NULL) {
        /* line too long */
        printf("error: line too long\n");
        exit(1);
    }
    /* is there a label? */
    ptr = line;
    if (sscanf(ptr, "%[^\t\n\r ]", label)) {
        /* successfully read label; advance pointer over the label */
        ptr += strlen(label);
    }
    /*
     * Parse the rest of the line.  Would be nice to have real regular
     * expressions, but scanf will suffice.
     */
    sscanf(ptr, "%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]",
        opcode, arg0, arg1, arg2);
    return(1);
}

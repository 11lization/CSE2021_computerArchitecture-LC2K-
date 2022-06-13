/* LC-2K Instruction-level simulator */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NUMMEMORY 65536 /* maximum number of words in memory */
#define NUMREGS 8 /* number of machine registers */
#define MAXLINELENGTH 1000
#define ADD 0
#define NOR 1
#define LW 2
#define SW 3
#define BEQ 4
#define JALR 5
#define HALT 6
#define NOOP 7

typedef struct stateStruct {
    int pc;
    int mem[NUMMEMORY];
    int reg[NUMREGS];
    int numMemory;
} stateType;

void printState(stateType *);

int convertNum(int num){
    /* convert a 16-bit number into a 32-bit Linux integer */
    if (num & (1<<15) ) {
        num -= (1<<16);
    }
    
    return(num);
}

int main(int argc, char *argv[]){    
    char line[MAXLINELENGTH];
    int total, i;
    stateType state;
    FILE *filePtr;
    
    if (argc != 2) {
        printf("error: usage: %s <machine-code file>\n", argv[0]);
        exit(1);
    }
    
    filePtr = fopen(argv[1], "r");
    
    if (filePtr == NULL) {
        printf("error: can't open file %s", argv[1]);
        perror("fopen");
        exit(1);
    }
    
    /* read in the entire machine-code file into memory */
    for (state.numMemory = 0; fgets(line, MAXLINELENGTH, filePtr) != NULL; state.numMemory++) {
        if (sscanf(line, "%d", state.mem+state.numMemory) != 1) {
            printf("error in reading address %d\n", state.numMemory);
            exit(1);
        }
        printf("memory[%d]=%d\n", state.numMemory, state.mem[state.numMemory]);
    }

    memset(state.reg, 0, sizeof(int) * NUMREGS);
    state.pc = 0;

    while(1){
        int inst = state.mem[state.pc];
        int opcode = inst >> 22;
        int arg0 = (inst >> 19) & 0x7;
        int arg1 = (inst >> 16) & 0x7;
        int arg2 = inst & 0x7;
        int offset = inst & 0xFFFF;

        if(opcode < ADD || opcode > NOOP)
            break;
        
        printState(&state);

        if(opcode == ADD){
            state.reg[arg2] = state.reg[arg0] + state.reg[arg1];
        }
        else if(opcode == NOR){
            state.reg[arg2] = ~(state.reg[arg0] | state.reg[arg1]);
        }
        else if(opcode == LW){
            state.reg[arg1] = state.mem[convertNum(state.reg[arg0] + offset)];
        }
        else if(opcode == SW){
            state.mem[convertNum(state.reg[arg0] + offset)] = state.reg[arg1];
        }
        else if(opcode == BEQ){
            if(state.reg[arg0] == state.reg[arg1])
                state.pc = state.pc + convertNum(offset);
        }
        else if(opcode == JALR){
            state.reg[arg1] = state.pc + 1;
            state.pc = state.reg[arg0] - 1;
        }
        else if(opcode == HALT){
            state.pc++;
            total++;
            break;
        }
        else if(opcode == NOOP){}

        state.pc++;
        total++;
    }

    printf("machine halted\n");
    printf("total of %d instructions executed\n", total);
    printf("final state of machine:\n");
    printState(&state);

    return(0);
}

void printState(stateType *statePtr)
{    int i;
    printf("\n@@@\nstate:\n");
    printf("\tpc %d\n", statePtr->pc);
    printf("\tmemory:\n");
    for (i=0; i<statePtr->numMemory; i++) {
        printf("\t\tmem[ %d ] %d\n", i, statePtr->mem[i]);
    }
    printf("\tregisters:\n");
    for (i=0; i<NUMREGS; i++) {
        printf("\t\treg[ %d ] %d\n", i, statePtr->reg[i]);
    }
    printf("end state\n");
}
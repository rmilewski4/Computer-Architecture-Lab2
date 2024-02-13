#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

char prog_file[32];
int maxfilesize = 50;
int maxinstsize = 255;
typedef struct instruction_array_struct {
    char* instruction;
    //Should hold type (i.e. R, I, S, etc.)
    char type;
    uint32_t opcode;
    uint32_t rd;
    uint32_t funct3;
    uint32_t rs1;
    uint32_t rs2;
    uint32_t funct7;
    uint32_t imm11_0;
    uint32_t imm4_0;
    uint32_t imm4_1and11;
    uint32_t imm12and10_5;
} instruction;  
//takes in the instructionarray with instruction already loaded and determines opcode and rest of registers.
void split_input(instruction* instructionarray);
//Read in input from prog_file and store into memory array.
void load_program(instruction* instruction_array);

//Needed to initalize array to store instructions
instruction* initalize_program();

//Free malloc'd memory
void cleanup_program(instruction* instruction_array);
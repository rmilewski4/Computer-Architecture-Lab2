#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

char prog_file[32];
int maxfilesize = 50;
int maxinstsize = 255;
int numinstructions = 0;
typedef struct instruction_array_struct {
    char* instruction;
    //Should hold type (i.e. R, I, S, etc.)
    char type;
    char name[7];
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
instruction add_processing(instruction);
enum opcode {
    R=51,IImm=19,ILd=3,S=32,B=99,J=111,jalr=103,lui=55,auipc=12,ecall=115
};
enum funct3 {
    add=0,sub=0,xor
};
//takes in the instructionarray with instruction already loaded and determines opcode and rest of registers.
void split_input(instruction* instructionarray);
//Read in input from prog_file and store into memory array.
void load_program(instruction* instruction_array);

//Needed to initalize array to store instructions
instruction* initalize_program();

//Free malloc'd memory
void cleanup_program(instruction* instruction_array);
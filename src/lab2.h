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
//R-type
instruction r_processing(instruction i, char*split);
instruction add_processing(instruction i);
instruction sub_processing(instruction i);
instruction xor_processing(instruction i);
instruction or_processing(instruction i);
instruction and_processing(instruction i);
instruction sll_processing(instruction i);
instruction srl_processing(instruction i);
instruction sra_processing(instruction i);
instruction slt_processing(instruction i);
instruction sltu_processing(instruction i);
//I-im
instruction addi_processing(instruction);
instruction xori_processing(instruction);
instruction ori_processing(instruction);
instruction andi_processing(instruction);
instruction slli_processing(instruction);
instruction srli_processing(instruction);
instruction srai_processing(instruction);
instruction slti_processing(instruction);
instruction slti_processing(instruction);
instruction sltiu_processing(instruction);
//I-load
instruction lb_processing(instruction);
instruction lh_processing(instruction);
instruction lw_processing(instruction);
instruction lbu_processing(instruction);
instruction lhu_processing(instruction);
//S-type
instruction sb_processing(instruction);
instruction sh_processing(instruction);
instruction sw_processing(instruction);
//b-type
instruction beq_processing(instruction);
instruction bne_processing(instruction);
instruction blt_processing(instruction);
instruction bge_processing(instruction);
instruction bltu_processing(instruction);
instruction bgeu_processing(instruction);
//jump
instruction jal_processing(instruction);
instruction jalr_processing(instruction);
//u-type
instruction lui_processing(instruction);
instruction auipc_processing(instruction);
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
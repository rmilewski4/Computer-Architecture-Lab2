#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>
uint32_t numinstructions = 0;
int maxfilesize = 50;
int maxinstsize = 255;
//struct used to hold data about each instruction and any possible field in use
typedef struct instruction_array_struct {
    char* instruction;
    //Should hold type (i.e. R, I, S, etc.)
    char type;
    char* label;
    uint32_t pc;
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
    uint32_t imm11_5;
    uint32_t imm31_12;
} instruction;  
//struct used to map all processing functions
typedef struct {
    char* name;
    instruction (*processing_func)(instruction);
} InstructionMapping;
void scan_for_labels(instruction* instruction_array);
int checkForLabels(instruction i);
//calculate label offset used for branching instructions. Accepts list of instructions, current instruction's PC & Label trying to reach. Returns imm offset needed for instructions.
uint32_t calculateLabelOffset(instruction* instruction_array, uint32_t currentPC, char* label);
//R-type
instruction r_processing(instruction i, char*split, FILE* fp);
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
instruction iim_processing(instruction i, char*split, FILE* fp);
instruction addi_processing(instruction i);
instruction xori_processing(instruction i);
instruction ori_processing(instruction i);
instruction andi_processing(instruction i);
instruction slli_processing(instruction i);
instruction srli_processing(instruction i);
instruction srai_processing(instruction i);
instruction slti_processing(instruction i);
instruction sltiu_processing(instruction i);
//I-load
instruction ild_processing(instruction i, char*split, FILE* fp);
instruction lb_processing(instruction i);
instruction lh_processing(instruction i);
instruction lw_processing(instruction i);
instruction lbu_processing(instruction i);
instruction lhu_processing(instruction i);
//S-type
instruction s_processing(instruction i, char* split, FILE* fp);
instruction sb_processing(instruction i);
instruction sh_processing(instruction i);
instruction sw_processing(instruction i);
//b-type
instruction b_processing(instruction* instruction_array, instruction i, char* split, FILE* fp);
instruction beq_processing(instruction i);
instruction bne_processing(instruction i);
instruction blt_processing(instruction i);
instruction bge_processing(instruction i);
instruction bltu_processing(instruction i);
instruction bgeu_processing(instruction i);
//jump
instruction j_processing(instruction* instruction_array, instruction i, char* split, FILE* fp);
instruction jal_processing(instruction i);
instruction jalr_processing(instruction i);
//u-type
instruction u_processing(instruction i, char* split, FILE* fp);
instruction lui_processing(instruction i);
instruction auipc_processing(instruction i);
//ecall
void ecall_encoding(instruction i, FILE* fp);
instruction ecall_processing(instruction i);
//ebreak
void ebreak_encoding(instruction i, FILE* fp);
instruction ebreak_processing(instruction i);
//array for all possible assembly names and their processing function as a function pointer
InstructionMapping mappings[] = {
        {"add", add_processing},
        {"sub", sub_processing},
        {"xor", xor_processing},
        {"or", or_processing},
        {"and", and_processing},
        {"sll", sll_processing},
        {"srl", srl_processing},
        {"sra", sra_processing},
        {"slt",slt_processing},
        {"sltu",sltu_processing},
        {"addi",addi_processing},
        {"xori",xori_processing},
        {"ori",ori_processing},
        {"andi",andi_processing},
        {"slli",slli_processing},
        {"srli",srli_processing},
        {"srai",srai_processing},
        {"slti",slti_processing},
        {"sltiu",sltiu_processing},
        {"lb", lb_processing},
        {"lh", lh_processing},
        {"lw", lw_processing},
        {"lbu", lbu_processing},
        {"lhu", lhu_processing},
        {"sb", sb_processing},
        {"sh", sh_processing},
        {"sw", sw_processing},
        {"beq", beq_processing},
        {"bne", bne_processing},
        {"blt", blt_processing},
        {"bge", bge_processing},
        {"bltu", bltu_processing},
        {"bgeu", bgeu_processing},
        {"jal", jal_processing},
        {"jalr", jalr_processing},
        {"lui", lui_processing},
        {"auipc", auipc_processing},
        {"ecall", ecall_processing},
        {"ebreak", ebreak_processing}
};
//takes in the instructionarray with instruction already loaded and determines opcode and rest of registers.
void split_input(instruction* instructionarray);

//counts number of lines in file
uint32_t countFileLines(FILE * fp);

//count number of characters in line
uint32_t countCharactersInLine(FILE * fp, size_t offset);

//Read in input from prog_file and store into memory array.
void load_program(instruction* instruction_array, char * prog_file);

//Needed to initalize array to store instructions
instruction* initalize_program();

//Free malloc'd memory
void cleanup_program(instruction* instruction_array);
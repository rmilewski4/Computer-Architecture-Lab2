#include "lab2.h"
//create R-processing,I,etc. to handle all register operations
instruction add_processing(instruction i) {
    i.type = 'R';
    i.opcode = 51;
    i.funct3 = 0;
    i.funct7 = 0;

}

void split_input(instruction* instruction_array) {
    for(int i = 0; i < numinstructions;i++) {
        char* instruction = instruction_array[i].instruction;
        char* split;
        split=strtok(instruction, " ");
        strcpy(instruction_array[i].name,split);
        //R-Type
        if(strncmp("add",split,3)==0) {
            instruction_array[i].type = 'R';
            //opcode of 0110011 in binary is 51 in decimal
            instruction_array[i].opcode = 51;
            instruction_array[i].funct3 = 0;
            instruction_array[i].funct7 = 0;
        }
        else if(strncmp("sub",split,3)==0) {
            instruction_array[i].type = 'R';
            instruction_array[i].opcode = 51;
            instruction_array[i].funct3 = 0;
            //0x20 in hex is 32 decimal
            instruction_array[i].funct7 = 32;
        }
        else if(strncmp("xor",split,3)==0) {
            instruction_array[i].type = 'R';
            instruction_array[i].opcode = 51;
            instruction_array[i].funct3 = 4;
            instruction_array[i].funct7 = 0;
        }
        else if(strncmp("or",split,2)==0) {
            instruction_array[i].type = 'R';
            instruction_array[i].opcode = 51;
            instruction_array[i].funct3 = 6;
            instruction_array[i].funct7 = 0;
        }
        else if(strncmp("and",split,3)==0) {
            instruction_array[i].type = 'R';
            instruction_array[i].opcode = 51;
            instruction_array[i].funct3 = 7;
            instruction_array[i].funct7 = 0;
        }
        else if(strncmp("sll",split,3)==0) {
            instruction_array[i].type = 'R';
            instruction_array[i].opcode = 51;
            instruction_array[i].funct3 = 1;
            instruction_array[i].funct7 = 0;
        }
        else if(strncmp("srl",split,3)==0) {
            instruction_array[i].type = 'R';
            instruction_array[i].opcode = 51;
            instruction_array[i].funct3 = 5;
            instruction_array[i].funct7 = 0;
        }
        else if(strncmp("sra",split,3)==0) {
            instruction_array[i].type = 'R';
            instruction_array[i].opcode = 51;
            instruction_array[i].funct3 = 5;
            instruction_array[i].funct7 = 32;
        }
        else if(strncmp("slt",split,3)==0) {
            instruction_array[i].type = 'R';
            instruction_array[i].opcode = 51;
            instruction_array[i].funct3 = 2;
            instruction_array[i].funct7 = 0;
        }
        else if(strncmp("sltu",split,4)==0) {
            instruction_array[i].type = 'R';
            instruction_array[i].opcode = 51;
            instruction_array[i].funct3 = 3;
            instruction_array[i].funct7 = 0;
        }
        //I-Immediate instructions
    }
}

void cleanup_program(instruction* instruction_array) {
    for(int i = 0; i < maxfilesize; i++) {
        free(instruction_array[i].instruction);
    }
    free(instruction_array);
}

//for wes to implement, filename stored in prog_file add counter to get number of instructions, stored in numinstructions
void load_program(instruction* instruction_array) {

}

instruction* initalize_program() {
    instruction* inst_array = malloc(maxfilesize*sizeof(instruction));
    memset(inst_array,0,sizeof(instruction));
    for(int i = 0; i < maxfilesize; i++ ) {
        inst_array[i].instruction = malloc(maxinstsize*sizeof(char));
        memset(inst_array[i].instruction,0,maxinstsize);
    }
    return inst_array;
}

int main(int argc, char*argv[]) {
	if (argc < 2) {
		printf("Error: You should provide input file.\nUsage: %s <input program> \n\n",  argv[0]);
		exit(1);
	}
    strcpy(prog_file,argv[1]);
    instruction* instruction_array = initalize_program();
    load_program(instruction_array);
    cleanup_program(instruction_array);
}
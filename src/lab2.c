#include "lab2.h"

void split_input(instruction* instruction_array) {
    char* instruction = instruction_array->instruction;
    char* split;
    split=strtok(instruction, " ");
    strcpy(instruction_array->name,split);
    //R-Type
    if((strncmp("add",split,3)==0)) {
        instruction_array->type = 'R';
        //opcode of 0110011 in binary is 51 in decimal
        instruction_array->opcode = 51;
        instruction_array->funct3 = 0;
    }
}

void cleanup_program(instruction* instruction_array) {
    for(int i = 0; i < maxfilesize; i++) {
        free(instruction_array[i].instruction);
    }
    free(instruction_array);
}

//for wes to implement, filename stored in prog_file
void load_program(instruction* instruction_array) {

}

instruction* initalize_program() {
    instruction* inst_array = malloc(maxfilesize*sizeof(instruction));
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
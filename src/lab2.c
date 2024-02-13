#include "lab2.h"

void cleanup_program(instruction* instruction_array) {
    for(int i = 0; i < maxfilesize; i++) {
        free(instruction_array[i].instruction);
    }
    free(instruction_array);
}

//for wes to implement, filename stored in prog_file
void load_program(instruction* instruction_array[]) {

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
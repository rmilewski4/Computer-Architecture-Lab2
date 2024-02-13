#include "lab2.h"

//for wes to implement, filename stored in prog_file
void load_program(char* instruction_array[]) {

}

char** initalize_program() {
    char** inst_array = malloc(maxfilesize*sizeof(char*));
    for(int i = 0; i < maxfilesize; i++ ) {
        inst_array[i] = malloc(maxinstsize*sizeof(char));
        memset(inst_array[i],0,maxinstsize);
    }
    return inst_array;
}

int main(int argc, char*argv[]) {
	if (argc < 2) {
		printf("Error: You should provide input file.\nUsage: %s <input program> \n\n",  argv[0]);
		exit(1);
	}
    strncpy(prog_file,argv[1],32);
    char** instruction_array = initalize_program();
    load_program(instruction_array);

}
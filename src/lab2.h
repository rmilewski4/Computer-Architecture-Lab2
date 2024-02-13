#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

char prog_file[32];
int maxfilesize = 50;
int maxinstsize = 255;
//Read in input from prog_file and store into memory array.
void load_program(char* instruction_array[]);

//Needed to initalize array to store instructions
char** initalize_program();

//Free malloc'd memory
void cleanup_program(char** instruction_array);
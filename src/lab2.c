#include "lab2.h"
//TODO: create rest of I-processing,S,etc. to handle all register operations
//follow how the r instructions are implemented.
//finally create functions that create the machine code number.
instruction r_processing(instruction i, char*split) {
    //pull out rd
    split = strtok(NULL, ",");
    if(strncmp(split,"zero",4)==0) {
        i.rd = 0;
    }
    else {
        //skip past the x character in register names
        split++;
        uint32_t rd = strtol(split,NULL,10);
        i.rd = rd;
    }
    //pull out rs1
    split = strtok(NULL,", ");
    if(strncmp(split,"zero",4)==0) {
        i.rs1 = 0;
    }
    else {
        split++;
        uint32_t rs1 = strtol(split,NULL,10);
        i.rs1 = rs1;
    }
    //pull out rs2
    split = strtok(NULL,", ");
    if(strncmp(split,"zero",4)==0) {
        i.rs2 = 0;
    }
    else {
        split++;
        uint32_t rs2 = strtol(split,NULL,10);
        i.rs2 = rs2;
    }
    printf("rd = %d, rs1 = %d, rs2 = %d\n",i.rd,i.rs1,i.rs2);
    return i;
}
instruction add_processing(instruction i) {
    i.type = 'R';
    //opcode of 0110011 in binary is 51 in decimal
    i.opcode = 51;
    i.funct3 = 0;
    i.funct7 = 0;
    return i;
}
instruction sub_processing(instruction i) {
    i.type = 'R';
    i.opcode = 51;
    i.funct3 = 0;
    i.funct7 = 32;
    return i;
}
instruction xor_processing(instruction i) {
    i.type = 'R';
    i.opcode = 51;
    i.funct3 = 4;
    i.funct7 = 0;
    return i;
}
instruction or_processing(instruction i) {
    i.type = 'R';
    i.opcode = 51;
    i.funct3 = 6;
    i.funct7 = 0;
    return i;
}
instruction and_processing(instruction i) {
    i.type = 'R';
    i.opcode = 51;
    i.funct3 = 7;
    i.funct7 = 0;
    return i;
}
instruction sll_processing(instruction i) {
    i.type = 'R';
    i.opcode = 51;
    i.funct3 = 1;
    i.funct7 = 0;
    return i;
}
instruction srl_processing(instruction i) {
    i.type = 'R';
    i.opcode = 51;
    i.funct3 = 5;
    i.funct7 = 0;
    return i;
}
instruction sra_processing(instruction i) {
    i.type = 'R';
    i.opcode = 51;
    i.funct3 = 5;
    i.funct7 = 32;
    return i;
}
instruction slt_processing(instruction i) {
    i.type = 'R';
    i.opcode = 51;
    i.funct3 = 2;
    i.funct7 = 0;
    return i;
}
instruction sltu_processing(instruction i) {
    i.type = 'R';
    i.opcode = 51;
    i.funct3 = 3;
    i.funct7 = 0;
    return i;
}
void split_input(instruction* instruction_array) {
    for(int i = 0; i < numinstructions;i++) {
        char* instruction = instruction_array[i].instruction;
        char* split;
        split=strtok(instruction, " ");
        printf("Name is %s\n",split);
        //R-Type, check for string length of name of instruction to avoid catching immediate instructions as well.
        if(strncmp("add",split,3)==0 && (strlen(split)==3)) {
            instruction_array[i] = add_processing(instruction_array[i]);
        }
        else if(strncmp("sub",split,3)==0 && (strlen(split)==3)) {
            instruction_array[i] = sub_processing(instruction_array[i]);
        }
        else if(strncmp("xor",split,3)==0) {
            instruction_array[i] = xor_processing(instruction_array[i]);
        }
        else if(strncmp("or",split,2)==0 && (strlen(split)==2)) {
            instruction_array[i] = or_processing(instruction_array[i]);
        }
        else if(strncmp("and",split,3)==0 && (strlen(split)==3)) {
            instruction_array[i] = and_processing(instruction_array[i]);
        }
        else if(strncmp("sll",split,3)==0 && (strlen(split)==3)) {
            instruction_array[i] = sll_processing(instruction_array[i]);
        }
        else if(strncmp("srl",split,3)==0 && (strlen(split)==3)) {
            instruction_array[i] = srl_processing(instruction_array[i]);
        }
        else if(strncmp("sra",split,3)==0 && (strlen(split)==3)) {
            instruction_array[i] = sra_processing(instruction_array[i]);
        }
        else if(strncmp("slt",split,3)==0 && (strlen(split)==3)) {
            instruction_array[i] = slt_processing(instruction_array[i]);
        }
        else if(strncmp("sltu",split,4)==0 && (strlen(split)==4)) {
            instruction_array[i] = sltu_processing(instruction_array[i]);
        }
        if(instruction_array[i].type == 'R') {
            instruction_array[i] = r_processing(instruction_array[i],split);
        }
        //I-Immediate instructions
    }
}

void cleanup_program(instruction* instruction_array) {
    for(int i = 0; i < maxfilesize; i++) {
        free(instruction_array[i].instruction);
    }
    free(instruction_array);
    instruction_array=NULL;
}

//for wes to implement, filename stored in prog_file add counter to get number of instructions, stored in numinstructions
void load_program(instruction* instruction_array) {
    numinstructions = 3;
    strcpy(instruction_array[0].instruction,"add x10, zero, x32\0");
    strcpy(instruction_array[1].instruction,"add x11, x10, x9\0");
    strcpy(instruction_array[2].instruction,"addi x12, zero, 20\0");
}

instruction* initalize_program() {
    instruction* inst_array = malloc(maxfilesize*sizeof(instruction));
    for(int i = 0; i < maxfilesize; i++ ) {
        inst_array[i].instruction = malloc(maxinstsize*sizeof(char));
        memset(inst_array[i].instruction,0,maxinstsize);
        inst_array[i].funct3 = 0;
        inst_array[i].funct7 = 0;
        inst_array[i].imm11_0 = 0;
        inst_array[i].imm12and10_5 = 0;
        inst_array[i].imm4_0 = 0;
        inst_array[i].imm4_1and11 = 0;
        inst_array[i].opcode = 0;
        inst_array[i].rd = 0;
        inst_array[i].rs1 = 0;
        inst_array[i].rs2 = 0;
        inst_array[i].type = 0;

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
    split_input(instruction_array);
    cleanup_program(instruction_array);
}
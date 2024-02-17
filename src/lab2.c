#include "lab2.h"
//TODO: create rest of Iload-processing,S,etc. to handle all register operations
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
instruction iim_processing(instruction i, char*split) {
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
    //pull out imm
    split = strtok(NULL,", ");
    uint32_t imm = strtol(split,NULL,10);
    //checking if instruction is the srai, slli, or srli which needs to conserve the 0x20 or 0x00 in the 5:11 bits
    if((i.funct3 == 1) || i.funct3 == 5) {
        //we only want the first 5 bits to conserve the 0x20 or 0x00, so we create a bitmask and AND it with the original data stored in immediate
        uint32_t imm5bitmask = 31;
        imm &= imm5bitmask;
        //perform bitwise OR to keep both sections intact.
        i.imm11_0 |= imm;
    }
    else {
        i.imm11_0 = imm;
    }
    printf("rd = %d, rs1 = %d, imm = %d\n",i.rd,i.rs1,i.imm11_0);
    return i;
}
instruction ild_processing(instruction i, char*split) {
    //pull out rd
    split = strtok(NULL, ", ");
    if(strncmp(split,"zero",4)==0) {
        i.rd = 0;
    }
    else {
        //skip past the x character in register names
        split++;
        uint32_t rd = strtol(split,NULL,10);
        i.rd = rd;
    }
    //pull out imm
    split = strtok(NULL, "(");
    uint32_t imm = strtol(split, NULL, 10);
    i.imm11_0 = imm;
    //pull out rs1
    split = strtok(NULL, ")");
    split++;
    uint32_t rs1 = strtol(split, NULL, 10);
    i.rs1 = rs1;
    printf("rd = %d, imm = %d, rs1 = %d\n",i.rd,i.imm11_0,i.rs1);
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

//I-immediate processing instructions
instruction addi_processing(instruction i) {
    i.type = 'I';
    i.opcode = 19;
    i.funct3 = 0;
    return i;
}
instruction xori_processing(instruction i) {
    i.type = 'I';
    i.opcode = 19;
    i.funct3 = 4;
    return i;
}
instruction ori_processing(instruction i) {
    i.type = 'I';
    i.opcode = 19;
    i.funct3 = 6;
    return i;
}
instruction andi_processing(instruction i) {
    i.type = 'I';
    i.opcode = 19;
    i.funct3 = 7;
    return i;
}
instruction slli_processing(instruction i) {
    i.type = 'I';
    i.opcode = 19;
    i.funct3 = 1;
    return i;
}
instruction srli_processing(instruction i) {
    i.type = 'I';
    i.opcode = 19;
    i.funct3 = 5;
    return i;
}
instruction srai_processing(instruction i) {
    i.type = 'I';
    i.opcode = 19;
    i.funct3 = 5;
    //11_0 is set to 2048 because srai specifies that imm[5:11]=0x20. To set it to this number, we set the 11th bit to a one and the rest to 0, which is 2048
    i.imm11_0 = 2048;
    return i;
}
instruction slti_processing(instruction i) {
    i.type = 'I';
    i.opcode = 19;
    i.funct3 = 2;
    return i;
}
instruction sltiu_processing(instruction i) {
    i.type = 'I';
    i.opcode = 19;
    i.funct3 = 3;
    return i;
}
//i-load instructions
instruction lb_processing(instruction i) {
    i.type = 'I';
    i.opcode = 3;
    i.funct3 = 0;
    return i;
}
instruction lh_processing(instruction i) {
    i.type = 'I';
    i.opcode = 3;
    i.funct3 = 1;
    return i;
}
instruction lw_processing(instruction i) {
    i.type = 'I';
    i.opcode = 3;
    i.funct3 = 2;
    return i;
}
instruction lbu_processing(instruction i) {
    i.type = 'I';
    i.opcode = 3;
    i.funct3 = 4;
    return i;
}
instruction lhu_processing(instruction i) {
    i.type = 'I';
    i.opcode = 3;
    i.funct3 = 5;
    return i;
}
//S-type
instruction sb_processing(instruction i) {
    i.type = 'S';
    i.opcode = 35;
    i.funct3 = 0;
    return i;
}
instruction sh_processing(instruction i) {
    i.type = 'S';
    i.opcode = 35;
    i.funct3 = 1;
    return i;
}
instruction sw_processing(instruction i) {
    i.type = 'S';
    i.opcode = 35;
    i.funct3 = 2;
    return i;
}
//b-type
instruction beq_processing(instruction i) {
    i.type = 'B';
    i.opcode = 99;
    i.funct3 = 0;
    return i;
}
instruction bne_processing(instruction i) {
    i.type = 'B';
    i.opcode = 99;
    i.funct3 = 1;
    return i;
}
instruction blt_processing(instruction i) {
    i.type = 'B';
    i.opcode = 99;
    i.funct3 = 4;
    return i;
}
instruction bge_processing(instruction i) {
    i.type = 'B';
    i.opcode = 99;
    i.funct3 = 5;
    return i;
}
instruction bltu_processing(instruction i) {
    i.type = 'B';
    i.opcode = 99;
    i.funct3 = 6;
    return i;
}
instruction bgeu_processing(instruction i) {
    i.type = 'B';
    i.opcode = 99;
    i.funct3 = 7;
    return i;
}
//jump
instruction jal_processing(instruction i) {
    i.type = 'J';
    i.opcode = 111;
    return i;
}
instruction jalr_processing(instruction i) {
    i.type = 'I';
    i.opcode = 103;
    i.funct3 = 0;
    return i;
}
//u-type
instruction lui_processing(instruction i) {
    i.type = 'U';
    i.opcode = 55;
    return i;
}
instruction auipc_processing(instruction i) {
    i.type = 'U';
    i.opcode = 23;
    return i;
}

instruction ecall_processing(instruction i) {
    i.type = 'I';
    i.opcode = 115;
    i.funct3 = 0;
    return i;
}
void split_input(instruction* instruction_array) {
    //loop through all instructoins
    for(int i = 0; i < numinstructions;i++) {
        char* instruction = instruction_array[i].instruction;
        char* split;
        //pull out name of instruction first
        split=strtok(instruction, " ");
        printf("Name is %s\n",split);
        //loop through the above array of possibilities to try and find a match in that array
        for(int maps = 0; maps < sizeof(mappings)/sizeof(mappings[0]);maps++) {
            if(strncmp(mappings[maps].name,split,strlen(mappings[maps].name))==0 && strlen(split)==strlen(mappings[maps].name)) {
                //if a match was found, update the instruction array using the function pointer inside of the above mappings array
                instruction_array[i] = mappings[maps].processing_func(instruction_array[i]);
                //break out of searching through the array since a match was found
                break;
            }
        }
        if(instruction_array[i].type == 'R') {
            instruction_array[i] = r_processing(instruction_array[i],split);
        }
        else if(instruction_array[i].type == 'I' && instruction_array[i].opcode == 19) {
            instruction_array[i] = iim_processing(instruction_array[i],split);
        }
        else if(instruction_array[i].type == 'I' && (instruction_array[i].opcode == 3 || instruction_array[i].opcode == 103)) {
            instruction_array[i] = ild_processing(instruction_array[i],split);
        }
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
    strcpy(instruction_array[1].instruction,"lh x11, 30(x29)\0");
    strcpy(instruction_array[2].instruction,"srai x12, zero, 20\0");
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
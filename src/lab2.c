#include "lab2.h"


//function used to identify rd, rs1, rs2 for R instructions and also write the machine code for these instructions
//to the output file.
instruction r_processing(instruction i, char*split, FILE* fp) {
    //pull out rd, split based on comma in instruction
    split = strtok(NULL, ",");
    //Identify if zero was used 
    if(strncmp(split,"zero",4)==0) {
        i.rd = 0;
    }
    else {
        //skip past the x character in register names to get just the register number
        split++;
        //convert to a decimal value
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
    //Shifting the positions of the various fields of the instructions of R instructions
    uint32_t shiftedrd = i.rd << 7;
    uint32_t shiftedfunct3 = i.funct3 << 12;
    uint32_t shiftedrs1 = i.rs1 << 15;
    uint32_t shiftedrs2 = i.rs2 << 20;
    uint32_t shiftedfunct7 = i.funct7 << 25;
    //The full instruction is all of the shifted fields ORd together to get the complete instruction
    uint32_t fullinstruction = i.opcode | shiftedrd | shiftedfunct3 | shiftedrs1 | shiftedrs2 | shiftedfunct7;
    //write to the file
    fprintf(fp,"%08x\n", fullinstruction);
    return i;
}
//Similar to the R-instruction processing, except instead of rs2, we process an immediate value
instruction iim_processing(instruction i, char*split, FILE* fp) {
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
    //Similar to r-instruction machine code conversion, except we make use of the imm11_0 field
    uint32_t shiftedrd = i.rd << 7;
    uint32_t shiftedfunct3 = i.funct3 << 12;
    uint32_t shiftedrs1 = i.rs1 << 15;
    uint32_t shiftedimm11_0 = i.imm11_0 << 20;
    uint32_t fullinstruction = i.opcode | shiftedrd | shiftedfunct3 | shiftedrs1 | shiftedimm11_0;
    fprintf(fp,"%08x\n", fullinstruction);
    return i;
}
//Processing for i-load type instructions, using just an rd, immediate and rs1 
instruction ild_processing(instruction i, char*split, FILE* fp) {
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
    //split based on the first parenthesis to extract
    split = strtok(NULL, "(");
    uint32_t imm = strtol(split, NULL, 10);
    i.imm11_0 = imm;
    //pull out rs1
    split = strtok(NULL, ")");
    split++;
    uint32_t rs1 = strtol(split, NULL, 10);
    i.rs1 = rs1;
    //This encoding is identical to the i-load since they are both i-type instructions.
    uint32_t shiftedrd = i.rd << 7;
    uint32_t shiftedfunct3 = i.funct3 << 12;
    uint32_t shiftedrs1 = i.rs1 << 15;
    uint32_t shiftedimm11_0 = i.imm11_0 << 20;
    uint32_t fullinstruction = i.opcode | shiftedrd | shiftedfunct3 | shiftedrs1 | shiftedimm11_0;
    fprintf(fp,"%08x\n", fullinstruction);
    return i;
}
//store-instruction processing, using rs2, immediate and rs1
instruction s_processing(instruction i, char* split, FILE* fp) {
    //pull out rs2
    split = strtok(NULL, ", ");
    if(strncmp(split,"zero",4)==0) {
        i.rs2 = 0;
    }
    else {
        //skip past the x character in register names
        split++;
        uint32_t rs2 = strtol(split,NULL,10);
        i.rs2 = rs2;
    }
    //pull out imm
    split = strtok(NULL, "(");
    uint32_t imm = strtol(split, NULL, 10);
    //since the s-type splits the immediate field into 2 separate portions, we create bitmasks and extract each section
    //from the immediate.
    uint32_t zerotofourbitmask = 31;
    uint32_t fivetoelevenbitmask = 4064;
    i.imm4_0 = imm & zerotofourbitmask;
    i.imm11_5 = imm & fivetoelevenbitmask;
    //pull out rs1
    split = strtok(NULL, ")");
    if(strncmp(split,"zero",4)==0) {
        i.rs1 = 0;
    }
    else {
        //skip past the x character in register names
        split++;
        uint32_t rs1 = strtol(split,NULL,10);
        i.rs1 = rs1;
    }
    //Encoding the machine code using the given fields
    uint32_t shiftedimm4_0 = i.imm4_0 << 7;
    uint32_t shiftedfunct3 = i.funct3 << 12;
    uint32_t shiftedrs1 = i.rs1 << 15;
    uint32_t shiftedrs2 = i.rs2 << 20;
    uint32_t shiftedimm11_5 = i.imm11_5 << 25;
    uint32_t fullinstruction = i.opcode | shiftedimm4_0 | shiftedfunct3 | shiftedrs1 | shiftedrs2 | shiftedimm11_5;
    fprintf(fp,"%08x\n", fullinstruction);
    return i;
}
//process branch instructions using rs1, rs2, and the immdiate/label field
instruction b_processing(instruction* instruction_array, instruction i, char* split, FILE* fp) {
    //pull out rs1
    split = strtok(NULL, ",");
    if(strncmp(split,"zero",4)==0) {
        i.rs1 = 0;
    }
    else {
        //skip past the x character in register names
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
    //pull out imm/label
    split = strtok(NULL,", ");
    uint32_t imm = 0;
    //if not a digit, must be a label, so calculate address
    if(!isdigit(split[0])) {
        //Use function to get offset if it is a label
        imm = calculateLabelOffset(instruction_array,i.pc,split);
    }
    else {
        //If it is a digit, we just convert it to a decimal to get the offset
        imm = strtol(split,NULL,10);
    }
    //Use bitmask to separate immediate into 2 fields
    uint32_t imm4to1bitmask = 30;
    uint32_t imm4to1 = imm & imm4to1bitmask;
    uint32_t bit11mask = 2048;
    uint32_t bit11 = (imm & bit11mask) >> 11;
    //change the first bit from the 0'th to 11th by doing an OR with the two.
    i.imm4_1and11 = imm4to1 | bit11;
    uint32_t bit12mask = 4096;
    //grab bit 12 and shift into bit 11's spot that it will be taking
    uint32_t bit12 = (imm & bit12mask) >> 1;
    uint32_t bits10to5mask = 2016;
    uint32_t imm10to5 = imm & bits10to5mask;
    i.imm12and10_5 = (imm10to5 | bit12) >> 5;
    uint32_t shiftedfunct3 = i.funct3 << 12;
    uint32_t shiftedrs1 = i.rs1 << 15;
    uint32_t shiftedrs2 = i.rs2 << 20;
    uint32_t shiftedimm4_1and11 = i.imm4_1and11 << 7;
    uint32_t shiftedimm12and10_5 = i.imm12and10_5 << 25;
    uint32_t fullinstruction = i.opcode | shiftedimm4_1and11 | shiftedfunct3 | shiftedrs1 | shiftedrs2 | shiftedimm12and10_5;
    fprintf(fp,"%08x\n", fullinstruction);
    return i;
}
//Process jump instructions that take an rd and immediate field
instruction j_processing(instruction* instruction_array, instruction i, char* split, FILE* fp) {
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
    //pull out imm/label
    split = strtok(NULL,", ");
    uint32_t imm = 0;
    //if not a digit, must be a label, so calculate address
    if(!isdigit(split[0])) {
        imm = calculateLabelOffset(instruction_array,i.pc,split);
    }
    else {
        imm = strtol(split,NULL,10);
    }
    //encode the immediate as specified by instruction specification
    uint32_t imm19to12 = (imm & 0xFF000) >> 12;
    uint32_t bit11mask = 2048;
    uint32_t bit11 = (imm & bit11mask) >> 3;
    uint32_t bit10to1 = (imm & 2046) << 8;
    uint32_t bit20 = (imm & 1048576) >> 1;
    i.imm31_12 = imm19to12 | bit10to1 | bit11 | bit20;
    uint32_t shiftedrd = i.rd << 7;
    uint32_t shifted20and10_1and11and19_12 = i.imm31_12 << 12;
    uint32_t fullinstruction = i.opcode | shiftedrd | shifted20and10_1and11and19_12;
    fprintf(fp,"%08x\n", fullinstruction);
    return i;
}
//Process upper instructions that take rd and immediate fields
instruction u_processing(instruction i, char* split, FILE* fp) {
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
    split = strtok(NULL,", ");
    uint32_t imm = 0;
    imm = strtol(split, NULL, 10);
    //Only use bits 31-12 as specified. 
    imm = (imm & 0xFFFFF000) >> 12;
    i.imm31_12 = imm;
    uint32_t shiftedrd = i.rd << 7;
    uint32_t shifted31_12 = i.imm31_12 << 12;
    uint32_t fullinstruction = i.opcode | shiftedrd | shifted31_12;
    fprintf(fp,"%08x\n", fullinstruction);
    return i;
}
//Function to print the machine code of an ecall, which is just the opcode
void ecall_encoding(instruction i, FILE* fp) {
    fprintf(fp, "%08x\n", i.opcode);
}
//The below functions fill in the type field, opcode, funct3 & 7 (if needed) and any immediates (if needed)
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
//Function that is used to split up the input of the given asm instructions
void split_input(instruction* instruction_array) {
    FILE* fp = NULL;
    fp = fopen("output.txt", "w");
    //loop through all instructions
    for(uint32_t i = 0; i < numinstructions ;i++) {
        char* instruction = instruction_array[i].instruction;
        char* split;
        //pull out name of instruction first, this is for when no labels are on the current line.
        if(checkForLabels(instruction_array[i])==0) {
            split=strtok(instruction, " ");
        }
        else if(checkForLabels(instruction_array[i])==1) {
            //this means that it is a label on its own line, so we will continue with the loop as there are no more instructions on the line.
            continue;
        }
        else {
            //otherwise, there is a label on the current line, so we already started splitting the instruction with strtok in scan_for_labels, so we continue
            //If we already parsed a label on this line
            split = strtok(instruction, " ");
            //skip past the first label, to get to instruction
            split = strtok(NULL, " ");
        }
        //loop through the above array of possibilities to try and find a match in that array
        for(int maps = 0; maps < sizeof(mappings)/sizeof(mappings[0]);maps++) {
            if(strncmp(mappings[maps].name,split,strlen(mappings[maps].name))==0 && strlen(split)==strlen(mappings[maps].name)) {
                //if a match was found, update the instruction array using the function pointer inside of the above mappings array
                instruction_array[i] = mappings[maps].processing_func(instruction_array[i]);
                //break out of searching through the array since a match was found
                break;
            }
        }
        //if the given instruction was not found in the loop, the opcode is set to 0 and this indicates error for that instruction
        if(instruction_array[i].opcode == 0) {
            printf("Malformed instruction! Please check your instruction and reformat if needed\n");
            continue;
        }
        //Look through all possible types to process each individually
        if(instruction_array[i].type == 'R') {
            instruction_array[i] = r_processing(instruction_array[i],split, fp);
        }
        //For i-immediate instructions
        else if(instruction_array[i].type == 'I' && instruction_array[i].opcode == 19) {
            instruction_array[i] = iim_processing(instruction_array[i],split, fp);
        }
        //dealing with i-load and jalr
        else if(instruction_array[i].type == 'I' && (instruction_array[i].opcode == 3 || instruction_array[i].opcode == 103)) {
            instruction_array[i] = ild_processing(instruction_array[i],split, fp);
        }
        else if(instruction_array[i].type == 'S') {
            instruction_array[i] = s_processing(instruction_array[i],split, fp);
        }
        else if(instruction_array[i].type == 'B') {
            instruction_array[i] = b_processing(instruction_array, instruction_array[i],split, fp);
        }
        else if(instruction_array[i].type == 'J') {
            instruction_array[i] = j_processing(instruction_array,instruction_array[i],split, fp);
        }
        else if(instruction_array[i].type == 'U') {
            instruction_array[i] = u_processing(instruction_array[i],split, fp);
        }
        //opcode of 115 indicates ecall so that is how it is processed
        else if(instruction_array[i].opcode == 115) {
            ecall_encoding(instruction_array[i], fp);
        }
    }
    //close file when done
    fclose(fp);
}
//Function frees malloc'd memory at completion
void cleanup_program(instruction* instruction_array) {
    for(int i = 0; i < maxfilesize; i++) {
        free(instruction_array[i].instruction);
        instruction_array[i].instruction = NULL;
        free(instruction_array[i].label);
        instruction_array[i].label = NULL;
    }
    free(instruction_array);
    instruction_array=NULL;
}

uint32_t countCharactersInLine(FILE * fp, size_t offset){
    fseek(fp, offset, SEEK_SET); // go to start of instruction
    uint32_t charCount = 1;
    int ch = ' ';
    while((ch = getc(fp)) != EOF){ // while not at end of file
        if(ch == '\n'){
            break;
        }
        charCount++;
    }
    fseek(fp, offset, SEEK_SET); // go back to start of instruction
    return charCount;
}

uint32_t countFileLines(FILE * fp){
    uint32_t numLines = 1; //starting at first line
    while(!feof(fp)){ //while file isnt at the end
        char ch = fgetc(fp); 
        if(ch == '\n'){ //find new line
            numLines++;
        }
    }
    return numLines;
}

void load_program(instruction* instruction_array, char * prog_file) {

    FILE * fp = fopen(prog_file, "r");
    //Indicate error if issues with file
    if(fp == NULL){
        printf("Error, your input file did not successfully open!");
        exit(1);
    }
    //Count the number of lines to get the number of instructions
    numinstructions = countFileLines(fp);
    //point back to start of file
    fseek(fp, 0, SEEK_SET);
    uint32_t * lineCharacterArray = malloc(sizeof(uint32_t) * numinstructions);
    //count line characters, put them in array
    size_t offset = 0;
    lineCharacterArray[0] = countCharactersInLine(fp, offset);
    for(uint32_t i = 1; i < numinstructions; i++){
        offset += lineCharacterArray[i - 1];
        lineCharacterArray[i] = countCharactersInLine(fp, offset);        
    }

    for(uint32_t i = 1; i < numinstructions; i++) 
        lineCharacterArray[i]++; //add one character to each charCount for null terminator

    fseek(fp, 0, SEEK_SET); //back to start of file again
    //create str array for each instruction
    for (uint32_t i = 0; i < numinstructions; i++) {
        //Actually get the instruction on each line and save it
        char* output = fgets(instruction_array[i].instruction, lineCharacterArray[i] + 1, fp);
        if(output == NULL) {
            printf("an error occured reading the file!\nExiting!\n");
            free(lineCharacterArray);
            return;
        }
        //Loop to set null terminator
        for(int z = 0; z < lineCharacterArray[i]; z++) {
            //if a newline was found in an instruction, replace it with a null terminator
            if(instruction_array[i].instruction[z] == '\n') {
                instruction_array[i].instruction[z] = '\0';
            }
        }
        //This null terminator being added covers the EOF case
        instruction_array[i].instruction[lineCharacterArray[i]] = '\0';
    }

    uint32_t pc = 0;
    for(uint32_t i = 0; i<numinstructions;i++) {
        //check for labels on their own line and increment accordingly. Labels on their own line should point to the next instruction.
        if(checkForLabels(instruction_array[i])!=1) {
            instruction_array[i].pc = pc;
        }
        else{
            //if label found is on it's own line, increment it's pc to point to next instruction.
            instruction_array[i].pc = pc;
            continue;
        }        
        pc += 4;
    }
    free(lineCharacterArray);
    fclose(fp);
}
//This function checks to see if the current instruction has a label attached to it, so it can be tracked
//return type of 1 indicates a label on it's own line, return type of 2 indicates label attached to instruction, return type of 0 means no label.
int checkForLabels(instruction i) {
    char* instscan = i.instruction;
    //loop until null terminator reached
    while(*instscan != '\0') {
        //if colon found, which means a label is on the line then return given return value
        if(*instscan == ':') {
            //If the next character after the colon is the end of the string, then it's on its own line so return 1
            if(*(instscan + 1) == '\0') {
                return 1;
            }
            return 2;
        }
        instscan++;
    }
    return 0;
}
//Function used to scan for labels throughout the entire program
void scan_for_labels(instruction* instruction_array) {
    for(int i = 0; i < numinstructions; i++) {
        if(checkForLabels(instruction_array[i])) {
            //if label was found, catalog it and have instruction skip past it on the current line.
            //using a duplicate of the instruction because we will be using strtok which modifies the original string
            char* instructiondupe = malloc(sizeof(char)*strlen(instruction_array[i].instruction));
            strncpy(instructiondupe,instruction_array[i].instruction,strlen(instruction_array[i].instruction));
            char* split;
            //pull out name of instruction first
            split=strtok(instructiondupe, ": ");
            //save label into array
            strncpy(instruction_array[i].label,split,strlen(instructiondupe));
            free(instructiondupe);
        }
    }
}
//function used to calculate offset needed for branching instructions
uint32_t calculateLabelOffset(instruction* instruction_array, uint32_t currentPC, char* label) {
    //need to loop through array until we find the given label
    for(int i = 0; i< numinstructions;i++) {
        if(strncmp(instruction_array[i].label,label,strlen(label))==0) {
            //if label found at current position, we can now calculate offset. which is just the label's pc - current
            return instruction_array[i].pc - currentPC;
        }
    }
    //if label wasn't found, there was some type of error, so we return an offset of 0 to indicate this
    return 0;
}
//function used to create memory for array and initalize elements
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
        inst_array[i].imm11_5 = 0;
        inst_array[i].imm31_12 = 0;
        inst_array[i].pc = 0;
        inst_array[i].label = malloc(maxinstsize*sizeof(char));
        memset(inst_array[i].label,0,maxinstsize);
    }
    return inst_array;
}
int main(int argc, char*argv[]) {
	if (argc < 2) {
		printf("Error: You should provide input file.\nUsage: %s <input program> \n\n",  argv[0]);
		exit(1);
	}
    char * prog_file = malloc(strlen(argv[1]) + 1); // file length
    strcpy(prog_file,argv[1]);
    instruction* instruction_array = initalize_program();
    load_program(instruction_array, prog_file);
    scan_for_labels(instruction_array);
    split_input(instruction_array);
    cleanup_program(instruction_array);
    free(prog_file);
}
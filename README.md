# Computer-Architecture-Lab2

Need:
1. Function to read in data from file, most likely will need to store each line in one string to start
2. Split string based on operation and inputs. Split based on operation first, which can then be used to figure out instruction type. Once instruction type is known, can split rest of string and identify specific registers like rd, funct3, etc.
3. Once each input is known, convert to hex & shift to given position in string.
4. Finally, write output to screen/file.

Things to look into: how dealing with branches will work. Especially labels. For dealing with labels, we may need a sort of 'psuedo' program counter to calculate how big of a jump will will need.
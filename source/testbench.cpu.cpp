/*
 * Project:
 *     Simple Mips-like CPU on Xilinx Vivado Cpp
 *     (with Out-of-Order execution and Tomasulo's algorithm implementation)
 * Author:
 *     Grammatopoulos Athanasios-Vasileios (agrammatopoulos@isc.tuc.gr)
 * Purpose:
 *     Project for the "Computer architecture Course" on Technical University of Crete
 *
 * Copyright (c) Grammatopoulos Athanasios-Vasileios. All rights reserved.
 * Licensed under the MIT License. For more info see the LICENSE file.
 *
 * File:
 *     Run the cpu function
 */

// Libraries
#include "global_vars.h"
#include "testbench.h"
// Debug Libraries
using namespace std;

/*
 * Main code
 */
int main(int argc, char** argv) {
	// Print info
	printf("\n");
	printf("  Sample program execution ...\n");

	// Variables
	int pc = 0;
	bit32* results = (bit32*) malloc(1 * sizeof(bit32));
	
	// Init register file data
	bit32* data = (bit32*) malloc(32 * sizeof(bit32));
	for (int i = 0; i < 32; ++i){
		data[i] = 0b0;
	}
	// Init program's commands
	bit32* commands = (bit32*) malloc(64 * sizeof(bit32));
	for (int i = 0; i < 32; ++i){
		commands[i] = 0b0;
	}

	// Sample register file data
	data[1] = 0b1;
	data[2] = 0b10;
	data[3] = 0b11;
	data[4] = 0b100;
	data[30] = 0b1;

	// Print asm code
	printf("\n");
	printf("    Code\n");
	printf("      ADD  R11  R1   R2   \n");
	printf("      ADD  R12  R11  R3   \n");
	printf("      ADD  R13  R12  R4   \n");
	printf("      SUB  R14  R11  R1   \n");
	printf("      OR   R14  R3   R2   \n");
	printf("      NOP  R0   R0   R0   \n");
	printf("      ADD  R31  R0   R30  < Stop CPU\n");
	printf("      NOP  R0   R0   R0   \n");
	printf("\n");
	printf("    RS init\n");
	for (int i = 0; i < 8; ++i) {
		printf("      R%d\t=\t%d\t\tR%d\t=\t%d\t\tR%d\t=\t%d\t\tR%d\t=\t%d\n", i*4, data[i*4], i*4+1, data[i*4+1], i*4+2, data[i*4+2], i*4+3, data[i*4+3]);
	}
	printf("\n");

	// Init program's code
	pc = 0;
	// Command         ADD R11  R1   R2   
	commands[pc] = ((0b0100010110000100010) << 13); pc++;
	// Command         ADD R12  R11  R3   
	commands[pc] = ((0b0100011000101100011) << 13); pc++;
	// Command         ADD R13  R12  R4   
	commands[pc] = ((0b0100011010110000100) << 13); pc++;
	// Command         SUB R14  R11  R1   
	commands[pc] = ((0b0101011100101100001) << 13); pc++;
	// Command         OR  R14  R3   R2   
	commands[pc] = ((0b0001011100001100010) << 13); pc++;
	// Command         NOP R0   R0   R0   
	commands[pc] = ((0b1100000000000000000) << 13); pc++;

	// End Command (Write 0b1 on R31)
	// Command         ADD R31  R0   R30  
	commands[pc] = ((0b0001111110000011110) << 13); pc++;
	// Command         NOP R0   R0   R0   
	commands[pc] = ((0b1100000000000000000) << 13); pc++;

	// Run the sample program
	cpu(results, data, commands, pc - 1);
	printf("  Program was executed in %d cycles\n", results[0]);
	printf("\n");
	printf("    RS after the execution\n");
	for (int i = 0; i < 8; ++i) {
		printf("      R%d\t=\t%d\t\tR%d\t=\t%d\t\tR%d\t=\t%d\t\tR%d\t=\t%d\n", i*4, data[i*4], i*4+1, data[i*4+1], i*4+2, data[i*4+2], i*4+3, data[i*4+3]);
	}
	printf("\n");

	// Return
	return 0;
}

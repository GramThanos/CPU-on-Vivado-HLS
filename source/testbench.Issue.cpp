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
 *     Testbench for the command Issue unit
 */

// Libraries
#include "global_vars.h"
#include "testbench.h"
// Debug Libraries
using namespace std;

/*
 * Testbench main code
 */
int main(int argc, char** argv) {
	// Test info
	printf("\n");
	printf("\n");
	printf("\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("  Test Issue unit\n");
	printf("\n");

	// Test variables
	int errors = 0;
	int test_no = 0;
	int pc = 0;
	bit32* results = (bit32*) malloc(1 * sizeof(bit32));
	
	// Demo register file data
	bit32* data = (bit32*) malloc(32 * sizeof(bit32));
	for (int i = 0; i < 32; ++i){
		data[i] = 0b0;
	}
	// Demo program to run
	bit32* commands = (bit32*) malloc(64 * sizeof(bit32));
	for (int i = 0; i < 32; ++i){
		commands[i] = 0b0;
	}

	// Register data
	data[1] = 0b1;
	data[2] = 0b10;
	data[3] = 0b11;
	data[4] = 0b100;


	// ------------------------------------------------------------------------
	// Test - Run sample program 1
	// ------------------------------------------------------------------------
	test_no++;
	printf("  Test %d (Run sample program 1) ... \n", test_no);
	printf("  Run unrelated commands with many NOPs between them.\n");
	pc = 0;
	// Command         ADD R5   R1   R2   
	commands[pc] = ((0b0100001010000100010) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
	// Command         ADD R6   R3   R4   
	commands[pc] = ((0b0100001100001100100) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
	// Command         ADD R7   R1   R3   
	commands[pc] = ((0b0100001110000100101) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
	// Command         AND R7   R1   R3   
	commands[pc] = ((0b0000001110000100101) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
		// Command         NOP R0   R0   R0   
		commands[pc] = ((0b1100000000000000000) << 13);pc++;
	// Command         NOP R0   R0   R0   
	commands[pc] = ((0b1100000000000000000) << 13);pc++;
	// Run it!
	test_Issue(results, data, commands, pc - 1, 10);
	// Check results
	if (data[5] != 0b11) {
		printf("  Test failed (Command 1 returned %d instead of %d)", data[5], 0b11);
		errors++;
	}
	else if (data[6] != 0b111) {
		printf("  Test failed (Command 7 returned %d instead of %d)", data[6], 0b111);
		errors++;
	}
	else if (data[7] != 1) {
		printf("  Test failed (Command 19 returned %d instead of %d)", data[7], 1);
		errors++;
	}
	else {
		printf("  Test passed");
	}
	printf("\n");
	printf("  Program was executed in %d cycles\n", results[0]);
	printf("\n");

	/*
	// Print all registers
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("      Register Values\n");
	for (int i = 0; i < 32; ++i){
		printf("  R%d ", i);
		if(i <= 9) printf(" ");
		printBits((bit32) data[i], 32);
		printf("\n");
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	*/



	// ------------------------------------------------------------------------
	// Test - Run sample program 2
	// ------------------------------------------------------------------------
	test_no++;
	printf("  Test %d (Run sample program 2) ... \n", test_no);
	printf("  Run unrelated commands one after the other.\n");
	pc = 0;
	// Command         ADD R8   R1   R2   
	commands[pc] = ((0b0100010000000100010) << 13);pc++;
	// Command         ADD R9   R3   R4   
	commands[pc] = ((0b0100010010001100100) << 13);pc++;
	// Command         ADD R10  R1   R3   
	commands[pc] = ((0b0100010100000100101) << 13);pc++;
	// Command         NOP R0   R0   R0   
	commands[pc] = ((0b1100000000000000000) << 13);pc++;
	// Run it!
	test_Issue(results, data, commands, pc - 1, 10);
	// Check results
	if (data[8] != 0b11) {
		printf("  Test failed (Command 1 returned %d instead of %d)", data[8], 0b11);
		errors++;
	}
	else if (data[9] != 0b111) {
		printf("  Test failed (Command 2 returned %d instead of %d)", data[9], 0b111);
		errors++;
	}
	else if (data[10] != 0b100) {
		printf("  Test failed (Command 3 returned %d instead of %d)", data[10], 0b100);
		errors++;
	}
	else {
		printf("  Test passed");
	}
	printf("\n");
	printf("  Program was executed in %d cycles\n", results[0]);
	printf("\n");

	/*
	// Print all registers
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("      Register Values\n");
	for (int i = 0; i < 32; ++i){
		printf("  R%d ", i);
		if(i <= 9) printf(" ");
		printBits((bit32) data[i], 32);
		printf("\n");
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	*/



	// ------------------------------------------------------------------------
	// Test - Run sample program 3
	// ------------------------------------------------------------------------
	test_no++;
	printf("  Test %d (Run sample program 3) ... \n", test_no);
	printf("  Run multiple related commands one after the other.\n");
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
	// Run it!
	test_Issue(results, data, commands, pc - 1, 10);
	// Check results
	if (data[11] != 3) {
		printf("  Test failed (Command 1 returned %d instead of %d)", data[11], 6);
		errors++;
	}
	else if (data[12] != 6) {
		printf("  Test failed (Command 2 returned %d instead of %d)", data[12], 6);
		errors++;
	}
	else if (data[13] != 10) {
		printf("  Test failed (Command 3 returned %d instead of %d)", data[13], 10);
		errors++;
	}
	else if (data[14] != 3) {
		printf("  Test failed (Command 5 returned %d instead of %d)", data[14], 3);
		errors++;
	}
	else {
		printf("  Test passed");
	}
	printf("\n");
	printf("  Program was executed in %d cycles\n", results[0]);
	printf("\n");

	/*
	// Print all registers
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("      Register Values\n");
	for (int i = 0; i < 32; ++i){
		printf("  R%d ", i);
		if(i <= 9) printf(" ");
		printBits((bit32) data[i], 32);
		printf("\n");
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	*/





	// ------------------------------------------------------------------------
	// Results
	// ------------------------------------------------------------------------
	printf("\n");
	printf("  Passed %d/%d tests\n", test_no - errors, test_no);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n");
	printf("\n");

	// Return errors
	return (errors > 0) ? 1 : 0;
}

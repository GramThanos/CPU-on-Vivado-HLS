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
 *     Top level function for the command Issue unit testbench
 */

// Libraries
#include "global_vars.h"
#include "Issue.h"
#include "ReorderBuffer.h"
// Debug Libraries
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
// Debug Variables
#define _TESTBENCH_PRINTS_ false

// Help functions
void decodeCommand(bit32 command, bit2* type, bit2* func, bit5* Rd, bit5* Rs, bit5* Rt);
void printReorderBuffer(Issue* issue);

/*
 * Top level testbench function
 * Test the command Issue unit
 *
 * Parameters
 *     bit32 results[1]      CPU executed cycles
 *     bit32 data[32]        Register file's registers initialize
 *     bit32 commands[64]    The commands of our program
 *     int run               Program's commands to run
 *     int rest              Cycles for the cpu to rest
 */
void test_Issue(bit32 results[1], bit32 data[32], bit32 commands[64], int run, int rest) {
	// Prepare issue
	Issue issue;
	issue.init();

	// Load the given data 
	// on the register file's registers
	// BOOM! Content switch!
	for (int i = 1; i < 32; ++i) { // Ignore R0
		issue.rf.registers[i].value = data[i];
	}

	// Decoded command variables
	bit2 type;
	bit2 func;
	bit5 Rd;
	bit5 Rs;
	bit5 Rt;

	// Simulate the program counter
	int pc = 0;
	// Count cpu cycles
	int cycles = 0;


	while (pc < run) {
		// Decode my command
		decodeCommand(commands[pc], &type, &func, &Rd, &Rs, &Rt);
		// Try to issue command
		if(issue.issue(type, func, Rd, Rs, Rt)){
			if(_TESTBENCH_PRINTS_)
				printf("  [%d] Command %d issued [%d %d %d %d %d]\n", cycles + 1, pc + 1, type, func, Rd, Rs, Rt);
			// Yeah! Command is running
			pc++;
		} else {
			if(_TESTBENCH_PRINTS_)
				printf("  [%d] Stall\n", cycles + 1);
		}
		cycles++;

		// Print the reorder buffer's data
		//printReorderBuffer(&issue);

		// If it stuck
		if(cycles > run*100){
			// Kill it with fire
			break;
		}
	}

	// Rest the cpu
	// last command should be nop
	for (int i = 0; i < rest; ++i) {
		// Decode last command
		decodeCommand(commands[run], &type, &func, &Rd, &Rs, &Rt);
		// Run last command
		issue.issue(type, func, Rd, Rs, Rt);
		cycles++;

		// Print the reorder buffer's data
		//printReorderBuffer(&issue);
	}

	// Save register data
	// AGAIN! Save Content 4 switch!
	for (int i = 0; i < 32; ++i) {
		data[i] = issue.rf.registers[i].value;
	}

	// Return cycles
	results[0] = cycles;
}

// Decode the given command
void decodeCommand(bit32 command, bit2* type, bit2* func, bit5* Rd, bit5* Rs, bit5* Rt) {
	// Yeah, yeah I know this is not the right format
	// ... but this is what I want now
	// TODO: Convert the command format on a Mips-Like format
	*type = 0b11 & (command >> 30);
	*func = 0b11 & (command >> 28);
	*Rd = 0b11111 & (command >> 23);
	*Rs = 0b11111 & (command >> 18);
	*Rt = 0b11111 & (command >> 13);
}

// Print the reorder buffer's data
void printReorderBuffer(Issue* issue) {
	if(!_TESTBENCH_PRINTS_)
		return;

	// Separator
	printf("  ~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	// For each stage of the reorder buffer
	for (int i = 0; i < _REORDER_BUFFER_SIZE_; ++i){
		// Print stage data
		printf(
			"  [%s] Tag_%d R%d V_%d %s%s\n",
			(issue->rb.buffer[i].active ? (issue->rb.buffer[i].done ? "DONE" : "WAIT") : "OFF"),
			issue->rb.buffer[i].tag,
			issue->rb.buffer[i].destination,
			issue->rb.buffer[i].result,
			(issue->rb.bufferTop == i?"START ":""),
			(issue->rb.bufferBottom == i?"END+1 ":"")
		);
	}
	// Separator
	printf("  ~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

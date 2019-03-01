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
 *     Function of the cpu
 */

// Libraries
#include "global_vars.h"
#include "Issue.h"

// Debug Libraries
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

// Debug Definitions
#define _CPU_PRINT_ false

// TODO: Things to imporve/fix
// - Change command format to original
// - Define options for max cycles and end cases

// Help functions
// Decode the given command
void decodeCpuCommand(bit32 command, bit2* type, bit2* func, bit5* Rd, bit5* Rs, bit5* Rt) {
	// This is not the original MIPS command format ... I simlified it for testing
	// TODO: Convert the command format to a original Mips-Like format
	*type = 0b11 & (command >> 30);
	*func = 0b11 & (command >> 28);
	*Rd = 0b11111 & (command >> 23);
	*Rs = 0b11111 & (command >> 18);
	*Rt = 0b11111 & (command >> 13);
}

/*
 * Top level function
 * Run the cpu
 *
 * Parameters
 *     bit32 results[1]      CPU executed cycles
 *     bit32 data[32]        Register file's registers initialize
 *     bit32 commands[64]    The commands of our program
 *     int run               Program's commands to run
 *
 * CPU will stop when R31 has the value of 0b1.
 * If we run out of commands for execution, the CPU will keep running the last given command.
 * So it is adviced to give a NOP as the last command of the program.
 */
void cpu(bit32 results[1], bit32 data[32], bit32 commands[64], int run) {
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
		decodeCpuCommand(commands[pc], &type, &func, &Rd, &Rs, &Rt);
		// Try to issue command
		if(issue.issue(type, func, Rd, Rs, Rt)){
			if(_CPU_PRINT_)
				printf("  [%d] Command %d issued [%d %d %d %d %d]\n", cycles + 1, pc + 1, type, func, Rd, Rs, Rt);
			// Yeah! Command is running
			pc++;
		} else {
			if(_CPU_PRINT_)
				printf("  [%d] Stall\n", cycles + 1);
		}
		cycles++;

		// If it stuck
		if(cycles > run*100){
			// Kill it with fire
			break;
		}
	}

	// Run untill end case
	while (issue.rf.registers[31].value != 0b1) {
		// Decode last command
		decodeCpuCommand(commands[run], &type, &func, &Rd, &Rs, &Rt);
		// Run last command
		issue.issue(type, func, Rd, Rs, Rt);
		cycles++;
	}

	// Save register data
	// AGAIN! Save Content 4 switch!
	for (int i = 0; i < 32; ++i) {
		data[i] = issue.rf.registers[i].value;
	}

	// Return cycles
	results[0] = cycles;
}

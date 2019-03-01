/*
 * Project:
 *     Simple Mips-like CPU on Xilinx Vivado Cpp
 *     (with Out-of-Order execution and Tomasulo's algorithm implementation)
 * Author:
 *     Grammatopoulos Athanasios Vasileios (agrammatopoulos@isc.tuc.gr)
 * Purpose:
 *     Project for the "Computer architecture Course" on Technical University of Crete
 *
 * Copyright (c) Grammatopoulos Athanasios Vasileios. All rights reserved.
 * Licensed under the MIT License. For more info see the LICENSE file.
 *
 * File:
 *     Top level function for the Register File testbench
 */

// Libraries
#include "global_vars.h"
#include "RegisterFile.h"
// Debug Libraries
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
// Debug Variables
#define _TESTBENCH_PRINTS_ false

/*
 * Top level testbench function
 * Test the Register File
 *
 * Parameters
 *     bit32 data[32]        Register file's registers initialize
 *     bool action[32]       Read R[i] if action[i] is true or write if false
 *     bit32 R[32]           Register list
 *     bit32 value[32]       Value to read or write
 *     int length            Number of register file accesses
 */
void test_RegisterFile(bit32 data[32], bool action[32], bit5 R[32], bit32 value[32], int length) {
	// Prepare Register File
	RegisterFile rf;
	rf.init();

	// Load the given data 
	// on the register file's registers
	for (int i = 1; i < 32; ++i) { // Ignore R0
		rf.registers[i].value = data[i];
	}

	// Access register file
	for (int i = 0; i < length; ++i) {
		// Read register
		if (action[i]) {
			value[i] = rf.read(R[i]);
		}
		// Write register
		else {
			rf.write(R[i], value[i]);
		}
	}

	// Save register data
	for (int i = 0; i < 32; ++i) {
		data[i] = rf.registers[i].value;
	}
}

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
 *     Class of the Register File
 */

// Libraries
#include "global_vars.h"
#include "RegisterFile.h"

// Init Register File
void RegisterFile::init () {
	// Init registers
	for (int i = 0; i < 32; ++i){
		this->registers[i].value = 0b0;
	}
};

// Read a register
bit32 RegisterFile::read (bit5 reg) {
	// Return value
	return this->registers[reg].value;
};

// Write a register
void RegisterFile::write (bit5 reg, bit32 value) {
	// If not R0
	if (reg != 0b0) {
		// Save
		this->registers[reg].value = value;
	}
};

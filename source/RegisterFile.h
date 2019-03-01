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
 *     Header file of the Register File
 */

#ifndef _REGISTER_FILE_H_
#define _REGISTER_FILE_H_

// Libraries
#include "global_vars.h"

// Register File class
class RegisterFile {

	public:

		// Register
		struct Register {
			bit32 value;
		};

		// List of registers
		Register registers[32];
		
		// Init Register File
		void init ();

		// Read a register
		bit32 read (bit5 reg);

		// Write a register
		void write (bit5 reg, bit32 value);
};


#endif // _REGISTER_FILE_H_

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
 *     Testbench functions file
 */

// Libraries
#include "testbench.h"
// Debug Libraries
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>


/*
 * Define testbench helper functions
 * for ease of use in the testbenches
 */


/*
 * Print bits function
 *
 * Parameters
 *     bit32 bits      Bits variable
 *     int size        Number of bits to print
 */
void printBits(bit32 bits, int size) {
	// For each bit to print
	for (int i = size - 1; i >= 0; --i) {
		// Print bit
		printf("%d", 0b1 & (bits >> i));
	}
}

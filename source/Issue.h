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
 *     Header file of the command Issue unit
 */

#ifndef _ISSUE_H_
#define _ISSUE_H_

// Libraries
#include "global_vars.h"
#include "FunctionalUnit.h"
#include "CommonDataBus.h"
#include "RegisterFile.h"
#include "ReorderBuffer.h"

// Define command codes
#define _ISSUE_AU_CODE_ 0b01
#define _ISSUE_LU_CODE_ 0b00

// Issue class
class Issue {

	public:

		// Register file variable
		RegisterFile rf;

		// Reorder buffer variable
		ReorderBuffer rb;

		// Functional Units variables
		FunctionalArithmeticUnit fau;
		FunctionalLogicUnit flu;

		// Common Data Bus variable
		CommonDataBus cdb;

		
		// Init issue unit
		void init ();

		// Command issue
		bool issue (bit2 type, bit2 func, bit5 Rd, bit5 Rs, bit5 Rt);

};


#endif // _ISSUE_H_

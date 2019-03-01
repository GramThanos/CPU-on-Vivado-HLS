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
 *     Header file of the Common Data Bus
 */

#ifndef _COMMONDATABUS_H_
#define _COMMONDATABUS_H_

// Libraries
#include "global_vars.h"

#define _COMMONDATABUS_UNITS_ 4

// Just a common data bus
class CommonDataBus {

	public:

		// Number of units
		char units;
		// Access Token
		char token;
		bool active;


		// CDB values for debugging
		bit5 Q;
		bit32 V;


		// Bind cdb with functional unit
		struct busBind {
			bit5 Q;
			bit32 V;
			bit5 write_Q;
			bit32 write_V;
			bool request;
			bool access;
		};

		// List of binds
		busBind unit_list[_COMMONDATABUS_UNITS_];
		
		// Init bus
		void init ();

		// Bind a unit
		busBind* bind ();

		// Broadcast data to the bus
		void broadcast ();

		// Bind Bus
		void grandAccess ();

};

#endif // _COMMONDATABUS_H_

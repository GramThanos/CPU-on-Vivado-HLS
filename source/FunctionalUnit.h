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
 *     Header file of the Functional units
 */

#ifndef _FUNCTIONAL_UNIT_H_
#define _FUNCTIONAL_UNIT_H_

// Libraries
#include "global_vars.h"
#include "ReservationStation.h"
#include "CommonDataBus.h"

#define _FUNCTIONAL_ARITHMETIC_UNIT_RS_ 3
#define _FUNCTIONAL_ARITHMETIC_UNIT_LATENCY_ 3
#define _FUNCTIONAL_LOGIC_UNIT_RS_ 2
#define _FUNCTIONAL_LOGIC_UNIT_LATENCY_ 2

// Functional unit class
class FunctionalUnit {

	public:

		// Functional unit name
		bit2 tag;

		// Common data bus bind
		CommonDataBus::busBind* cdb;

		// Latency Stage
		struct pipelineStage {
			bool active;
			bit5 Q;
			bit2 func;
			bit32 Vs;
			bit32 Vt;
			bit32 R;
		};

		// Init
		void init (bit2 tag);

		// Listen on cdb
		void subscribe (CommonDataBus::busBind* cdb);

};


// Arithmetic functional unit class
class FunctionalArithmeticUnit : public FunctionalUnit {

	public:

		// Define super
		typedef FunctionalUnit super;

		// Rs units
		ReservationStation rs[_FUNCTIONAL_ARITHMETIC_UNIT_RS_];

		// Calculate unit
		pipelineStage calculateStages[_FUNCTIONAL_ARITHMETIC_UNIT_LATENCY_];



		// Init
		void init (bit2 tag);

		// Get availiable rs (if any)
		bit5 isAvailiable ();

		// Issue command (save on an rs)
		void issue (bit2 func, bit5 Qs, bit32 Vs, bit5 Qt, bit32 Vt);

		// Calculate
		void calculate ();
		
		// Load job
		void loadJob ();

		// Send cdb values to rs
		void checkBroadcast ();

		// Prepare data for cdb
		void checkAccess ();

};


// Logic functional unit class
class FunctionalLogicUnit : public FunctionalUnit {

	public:

		// Define super
		typedef FunctionalUnit super;

		// Rs units
		ReservationStation rs[_FUNCTIONAL_LOGIC_UNIT_RS_];

		// Calculate unit
		pipelineStage calculateStages[_FUNCTIONAL_LOGIC_UNIT_LATENCY_];



		// Init
		void init (bit2 tag);

		// Get availiable rs (if any)
		bit5 isAvailiable ();

		// Issue command (save on an rs)
		void issue (bit2 func, bit5 Qs, bit32 Vs, bit5 Qt, bit32 Vt);

		// Calculate
		void calculate ();
		
		// Load job
		void loadJob ();

		// Send cdb values to rs
		void checkBroadcast ();

		// Prepare data for cdb
		void checkAccess ();

};

#endif // _FUNCTIONAL_UNIT_H_

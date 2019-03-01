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
 *     Top level function for the Reservation Station testbench
 */

// Libraries
#include "global_vars.h"
#include "ReservationStation.h"

/*
 * Top level testbench function
 * Test the Reservation Station
 *
 * Parameters
 *     bit32 results[6]      Results data in order : {ready busy, Vs, Vt, Func, Name}
 *     bit5 name             The name of the RS
 *     bit2 func             The func of the RS
 *     bit5 Qs               The Qs of the RS
 *     bit32 Vs              The Vs of the RS
 *     bit5 Qt               The Qt of the RS
 *     bit32 Vt              The Vt of the RS
 *     bit5 Qb               The cdb Q to broadcast
 *     bit32 Vb              The cdb V to broadcast
 */
void test_ReservationStation(bit32 results[6], bit5 name, bit2 func, bit5 Qs, bit32 Vs, bit5 Qt, bit32 Vt, bit5 Qb, bit32 Vb) {

	// Create a reservation station
	ReservationStation rs;
	// Init
	rs.init(
		(bit2)(0b11 & (name >> 3)),		// First 2 bits
		(bit3)(0b111 & name)			// Last 3 bits
	);

	// Set a Qs or a Vs
	if (Qs != 0) {
		rs.setQs(Qs);
	}
	else {
		rs.setVs(Vs);
	}

	// Set a Qt or a Vt
	if (Qt != 0) {
		rs.setQt(Qt);
	}
	else {
		rs.setVt(Vt);
	}

	// Set func
	rs.setFunc(func);


	// Broadcast if given
	if (Qb != 0) {
		rs.checkBroadcast(Qb, Vb);
	}

	// Save ready state
	results[0] = (rs.isReady()) ? 1 : 0;
	// Save busy state
	results[1] = (rs.isBusy()) ? 1 : 0;
	// Save V of Rs
	results[2] = ((bit32)0b0) + rs.getVs();
	// Save V of Rt
	results[3] = ((bit32)0b0) + rs.getVt();
	// Save func
	results[4] = ((bit32)0b0) + rs.getFunc();
	// Save name
	results[5] = ((bit32)0b0) + rs.getName();
}
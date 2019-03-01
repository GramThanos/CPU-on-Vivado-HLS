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
 *     Testbench for the Register File
 */

// Libraries
#include "global_vars.h"
#include "testbench.h"
// Debug Libraries
using namespace std;

// Check
int check(bit32 ready, bit32 busy, bit32 Vs, bit1 VsDontCare, bit32 Vt, bit1 VtDontCare, bit32 func, bit32 name, bit32 results[6]);

/*
 * Testbench main code
 */
int main(int argc, char** argv) {
	// Test info
	printf("\n");
	printf("\n");
	printf("\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("  Test ReservationStation module\n");
	printf("\n");

	// Test variables
	int errors = 0;
	int test_no = 0;
	bit32* results = (bit32*) malloc(6 * sizeof(bit32));
	// Rs Name
	bit5 name = 0b0;
	// Rs func
	bit2 func = 0b0;
	// Rs
	bit3 Qs = 0b0;
	bit32 Vs = 0b0;
	// Rt
	bit3 Qt = 0b0;
	bit32 Vt = 0b0;
	// Broadcast
	bit3 Qb = 0b0;
	bit32 Vb = 0b0;


	// ------------------------------------------------------------------------
	// Test - RS with Qs and Qt
	// ------------------------------------------------------------------------
	test_no++;
	printf("  Test %d (RS with Qs and Qt) ... ", test_no);
	// Rs Name
	name = 0b01010;
	// Rs func
	func = 0b1;
	// Rs
	Qs = 0b1;
	Vs = 0b0;
	// Rt
	Qt = 0b10;
	Vt = 0b0;
	// Broadcast
	Qb = 0b0;
	Vb = 0b0;
	test_ReservationStation(results, name, func, Qs, Vs, Qt, Vt, Qb, Vb);
	// Check data
	if(check(
		0b0, // ready
		0b1, // busy
		0b0, // Vs
		0b1, // VsDontCare
		0b0, // Vt
		0b1, // VtDontCare
		0b1, // func
		0b010, // name
		results // results
	) < 0) {
		errors++;
	};
	printf("\n");



	// Test with values
	test_no++;
	printf("  Test %d (RS with Vs and Vt) ... ", test_no);
	// Rs Name
	name = 0b01011;
	// Rs func
	func = 0b11;
	// Rs
	Qs = 0b0;
	Vs = 0b1;
	// Rt
	Qt = 0b0;
	Vt = 0b1;
	// Broadcast
	Qb = 0b0;
	Vb = 0b0;
	test_ReservationStation(results, name, func, Qs, Vs, Qt, Vt, Qb, Vb);
	// Check data
	if(check(
		0b1, // ready
		0b1, // busy
		0b1, // Vs
		0b0, // VsDontCare
		0b1, // Vt
		0b0, // VtDontCare
		0b11, // func
		0b011, // name
		results // results
	) < 0) {
		errors++;
	};
	printf("\n");



	// Test with broadcast 1
	test_no++;
	printf("  Test %d (RS with Vs and Qt and broadcast Vt) ... ", test_no);
	// Rs Name
	name = 0b01110;
	// Rs func
	func = 0b1;
	// Rs
	Qs = 0b0;
	Vs = 0b1;
	// Rt
	Qt = 0b110;
	Vt = 0b0;
	// Broadcast
	Qb = 0b110;
	Vb = 0b110;
	test_ReservationStation(results, name, func, Qs, Vs, Qt, Vt, Qb, Vb);
	// Check data
	if(check(
		0b1, // ready
		0b1, // busy
		0b1, // Vs
		0b0, // VsDontCare
		0b110, // Vt
		0b0, // VtDontCare
		0b1, // func
		0b110, // name
		results // results
	) < 0) {
		errors++;
	};
	printf("\n");



	// Test with broadcast 2
	test_no++;
	printf("  Test %d (RS with Qs and Vt and broadcast Vs) ... ", test_no);
	// Rs Name
	name = 0b01010;
	// Rs func
	func = 0b1;
	// Rs
	Qs = 0b110;
	Vs = 0b0;
	// Rt
	Qt = 0b0;
	Vt = 0b1;
	// Broadcast
	Qb = 0b110;
	Vb = 0b110;
	test_ReservationStation(results, name, func, Qs, Vs, Qt, Vt, Qb, Vb);
	// Check data
	if(check(
		0b1, // ready
		0b1, // busy
		0b110, // Vs
		0b0, // VsDontCare
		0b1, // Vt
		0b0, // VtDontCare
		0b1, // func
		0b010, // name
		results // results
	) < 0) {
		errors++;
	};
	printf("\n");



	// Test with broadcast 2
	test_no++;
	printf("  Test %d (RS with Qs same as Qt and broadcast Vs which is also Vt) ... ", test_no);
	// Rs Name
	name = 0b01010;
	// Rs func
	func = 0b1;
	// Rs
	Qs = 0b110;
	Vs = 0b0;
	// Rt
	Qt = 0b110;
	Vt = 0b1;
	// Broadcast
	Qb = 0b110;
	Vb = 0b110;
	test_ReservationStation(results, name, func, Qs, Vs, Qt, Vt, Qb, Vb);
	// Check data
	if(check(
		0b1, // ready
		0b1, // busy
		0b110, // Vs
		0b0, // VsDontCare
		0b110, // Vt
		0b0, // VtDontCare
		0b1, // func
		0b010, // name
		results // results
	) < 0) {
		errors++;
	};
	printf("\n");




	// Results
	printf("\n");
	printf("  Passed %d/%d tests\n", test_no - errors, test_no);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n");
	printf("\n");

	// Return errors
	return (errors > 0) ? 1 : 0;
}


int check(bit32 ready, bit32 busy, bit32 Vs, bit1 VsDontCare, bit32 Vt, bit1 VtDontCare, bit32 func, bit32 name, bit32 results[6]) {
	// Check isReady
	if(results[0] != ready){
		printf("failed (isReady is %d instead of %d)", results[0], ready);
		return -1;
	}

	// Check isBusy
	else if(results[1] != busy){
		printf("failed (isBusy is %d instead of %d)", results[1], busy);
		return -1;
	}

	// Check Vs
	else if(VsDontCare != 0b1 && results[2] != Vs){
		printf("failed (Vs is %d instead of %d)", results[2], Vs);
		return -1;
	}

	// Check Vt
	else if(VtDontCare != 0b1 && results[3] != Vt){
		printf("failed (Vt is %d instead of %d)", results[3], Vt);
		return -1;
	}
	
	// Check func
	else if(results[4] != func){
		printf("failed (func is %d instead of %d)", results[4], func);
		return -1;
	}
	
	// Check name
	else if(results[5] != name){
		printf("failed (name is %d instead of %d)", results[5], name);
		return -1;
	}

	// No error
	printf("passed");
	return 1;
}
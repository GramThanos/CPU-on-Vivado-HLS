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

/*
 * Testbench main code
 */
int main(int argc, char** argv) {
	// Test info
	printf("\n");
	printf("\n");
	printf("\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("  Test Register File\n");
	printf("\n");

	// Test variables
	int errors = 0;
	int test_no = 0;

	// Test data variables
	bit32* data = (bit32*) malloc(32 * sizeof(bit32));
	bool* action = (bool*) malloc(32 * sizeof(bool));
	bit5* R = (bit5*) malloc(32 * sizeof(bit5));
	bit32* value = (bit32*) malloc(32 * sizeof(bit32));
	int l = 0;
	
	// Init data
	for (int i = 0; i < 32; ++i){
		data[i] = 0b0;
		action[i] = true;
		R[i] = 0b0;
		value[i] = 0b0;
	}


	// ------------------------------------------------------------------------
	// Test - Run sample program 1
	// ------------------------------------------------------------------------
	test_no++;
	printf("  Test %d (Run sample program 1) ... \n", test_no);
	printf("  Make unrelated accesses.\n");
	// Register data
	data[1] = 0b1;
	data[2] = 0b10;
	data[3] = 0b11;
	data[4] = 0b100;
	// Make accesses
	l = 0;
	// 0. value = read(R=1)
	action[l] = true;  R[l] = 0b001; value[l] = 0b00; l++;
	// 1. value = read(R=2)
	action[l] = true;  R[l] = 0b010; value[l] = 0b00; l++;
	// 2. write(R=6, value=3)
	action[l] = false; R[l] = 0b110; value[l] = 0b11; l++;
	l = 3;
	// Run it!
	test_RegisterFile(data, action, R, value, l);
	// Check results
	if (value[0] != 0b1) {
		printf("  Test failed (access 1 returned %d instead of %d)", value[0], 0b1);
		errors++;
	}
	else if (value[1] != 0b10) {
		printf("  Test failed (access 2 returned %d instead of %d)", value[1], 0b10);
		errors++;
	}
	else if (data[6] != 0b11) {
		printf("  Test failed (access 3 returned %d instead of %d)", data[6], 0b11);
		errors++;
	}
	else {
		printf("  Test passed");
	}
	printf("\n");

	// Clear data
	for (int i = 0; i < 32; ++i){
		data[i] = 0b0;
		action[i] = true;
		R[i] = 0b0;
		value[i] = 0b0;
	}
	l = 0;


	// ------------------------------------------------------------------------
	// Test - Run sample program 2
	// ------------------------------------------------------------------------
	test_no++;
	printf("  Test %d (Run sample program 2) ... \n", test_no);
	printf("  Make related accesses.\n");
	// Register data
	data[1] = 0b1;
	data[2] = 0b10;
	data[3] = 0b11;
	data[4] = 0b100;
	// Make accesses
	l = 0;
	// 0. value = read(R=1)
	action[l] = true;  R[l] = 0b01; value[l] = 0b000; l++;
	// 1. write(R=1, value=4)
	action[l] = false; R[l] = 0b01; value[l] = 0b100; l++;
	// 2. value = read(R=2)
	action[l] = true;  R[l] = 0b10; value[l] = 0b000; l++;
	// 3. write(R=2, value=5)
	action[l] = false; R[l] = 0b10; value[l] = 0b101; l++;
	// Run it!
	test_RegisterFile(data, action, R, value, l);
	// Check results
	if (value[0] != 0b1) {
		printf("  Test failed (access 1 returned %d instead of %d)", value[0], 0b1);
		errors++;
	}
	else if (data[1] != 0b100) {
		printf("  Test failed (access 2 returned %d instead of %d)", data[1], 0b100);
		errors++;
	}
	else if (value[2] != 0b10) {
		printf("  Test failed (access 3 returned %d instead of %d)", value[2], 0b10);
		errors++;
	}
	else if (data[2] != 0b101) {
		printf("  Test failed (access 4 returned %d instead of %d)", data[2], 0b101);
		errors++;
	}
	else {
		printf("  Test passed");
	}
	printf("\n");

	// Clear data
	for (int i = 0; i < 32; ++i){
		data[i] = 0b0;
		action[i] = true;
		R[i] = 0b0;
		value[i] = 0b0;
	}
	l = 0;


	// ------------------------------------------------------------------------
	// Test - Run sample program 3
	// ------------------------------------------------------------------------
	test_no++;
	printf("  Test %d (Run sample program 3) ... \n", test_no);
	printf("  Make related accesses.\n");
	// Register data
	data[1] = 0b1;
	data[2] = 0b10;
	data[3] = 0b11;
	data[4] = 0b100;
	// Make accesses
	l = 0;
	// 0. write(R=1, value=2)
	action[l] = false; R[l] = 0b01; value[l] = 0b010; l++;
	// 1. write(R=1, value=4)
	action[l] = false; R[l] = 0b01; value[l] = 0b100; l++;
	// 2. value = read(R=1)
	action[l] = true;  R[l] = 0b01; value[l] = 0b000; l++;
	// Run it!
	test_RegisterFile(data, action, R, value, l);
	// Check results
	if (data[1] != 0b100) {
		printf("  Test failed (access 1 returned %d instead of %d)", data[1], 0b100);
		errors++;
	}
	else if (value[2] != 0b100) {
		printf("  Test failed (access 2 returned %d instead of %d)", value[2], 0b100);
		errors++;
	}
	else {
		printf("  Test passed");
	}
	printf("\n");

	// Clear data
	for (int i = 0; i < 32; ++i){
		data[i] = 0b0;
		action[i] = true;
		R[i] = 0b0;
		value[i] = 0b0;
	}
	l = 0;


	// ------------------------------------------------------------------------
	// Results
	// ------------------------------------------------------------------------
	printf("\n");
	printf("  Passed %d/%d tests\n", test_no - errors, test_no);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n");
	printf("\n");

	// Return errors
	return (errors > 0) ? 1 : 0;
}

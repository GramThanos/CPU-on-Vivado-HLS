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
 *     Testbench Header file
 */

#ifndef _TESTBENCH_LINK_H_
#define _TESTBENCH_LINK_H_

// Libraries
#include "global_vars.h"
// Debug Libraries
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>


/*
 * Define top level testbench functions
 * for ease of use in the testbenches
 */

/*
 * Top level function
 * Run the cpu
 * (Parsed from the Issue.test.cpp file)
 *
 * Parameters
 *     bit32 results[1]      CPU executed cycles
 *     bit32 data[32]        Register file's registers initialize
 *     bit32 commands[64]    The commands of our program
 *     int run               Program's commands to run
 *
 * CPU will stop when R31 has the value of 0b1.
 * If commands to run end, it will keep running the last given command.
 * So it is advices a NOP to be the last command of the program.
 */
void cpu(bit32 results[1], bit32 data[32], bit32 commands[64], int run);

/*
 * Top level testbench function
 * Test the command Issue unit
 *
 * Parameters
 *     bit32 results[1]      CPU executed cycles
 *     bit32 data[32]        Register file's registers initialize
 *     bit32 commands[64]    The commands of our program
 *     int run               Program's commands to run
 *     int rest              Cycles for the cpu to rest
 */
void test_Issue(bit32 results[1], bit32 data[32], bit32 commands[64], int run, int rest);

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
void test_RegisterFile(bit32 data[32], bool action[32], bit5 R[32], bit32 value[32], int length);

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
void test_ReservationStation(bit32 results[6], bit5 name, bit2 func, bit5 Qs, bit32 Vs, bit5 Qt, bit32 Vt, bit5 Qb, bit32 Vb);

#endif // _TESTBENCH_LINK_H_

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
 *     Header file for global project defines
 */

#ifndef _GLOBAL_VARS_H_
#define _GLOBAL_VARS_H_

/*
 * Define custom bit types
 *
 * I found no bit data types on Xilinx's Vivado Cpp
 * documentations files, so I tried to create custom
 * ones, as close as possible in bit size.
 *
 * More info:
 *     Cpp Type         Size in bits
 *     unsigned char     8 bits
 *     unsigned short   16 bits
 *     unsigned long    32 bits
 *
 */
// Under 8 bits size define as
// unsigned char
typedef unsigned char bit1;
typedef unsigned char bit2;
typedef unsigned char bit3;
typedef unsigned char bit4;
typedef unsigned char bit5;
typedef unsigned char bit6;
typedef unsigned char bit7;
typedef unsigned char bit8;
// Next bit-types under 16 bits size
// define as unsigned char
typedef unsigned short bit9;
typedef unsigned short bit10;
typedef unsigned short bit11;
typedef unsigned short bit12;
typedef unsigned short bit13;
typedef unsigned short bit14;
typedef unsigned short bit15;
typedef unsigned short bit16;
// Next bit-types under 32 bits size
// define as unsigned char
typedef unsigned long bit17;
typedef unsigned long bit18;
typedef unsigned long bit19;
typedef unsigned long bit20;
typedef unsigned long bit21;
typedef unsigned long bit22;
typedef unsigned long bit23;
typedef unsigned long bit24;
typedef unsigned long bit25;
typedef unsigned long bit26;
typedef unsigned long bit27;
typedef unsigned long bit28;
typedef unsigned long bit29;
typedef unsigned long bit30;
typedef unsigned long bit31;
typedef unsigned long bit32;
// Bigger bit-types were not defined
// due to that they were not used on
// this project

#endif // _GLOBAL_VARS_H_

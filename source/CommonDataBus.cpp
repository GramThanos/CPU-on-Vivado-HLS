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
 *     Class of the Common Data Bus
 */

// Libraries
#include "global_vars.h"
#include "CommonDataBus.h"

// Init CDB
void CommonDataBus::init () {
	// Init units number
	this->units = 0;
	// Init Access token
	this->token = -1;
	this->active = false;

	this->Q = 0b0;
	this->V = 0b0;

	// For each unit
	for (int i = 0; i < _COMMONDATABUS_UNITS_; i++){
		// Init data
		this->unit_list[i].write_Q = 0;
		this->unit_list[i].write_V = 0;
		this->unit_list[i].request = false;
		this->unit_list[i].access = false;
	}
};

// Bind Bus
CommonDataBus::busBind* CommonDataBus::bind () {
	// One additional unit
	this->units++;
	// Return
	return &(this->unit_list[this->units - 1]);
};

// Broadcast data to the bus
void CommonDataBus::broadcast () {
	bit5 Q = 0b0;
	bit32 V = 0b0;

	// If broadcasting
	if(this->active){
		Q = this->unit_list[this->token].write_Q;
		V = this->unit_list[this->token].write_V;
	}

	// For each unit
	for (int i = 0; i < _COMMONDATABUS_UNITS_; i++){
		// Send data
		this->unit_list[i].Q = Q;
		this->unit_list[i].V = V;
	}

	// Set local values
	this->Q = Q;
	this->V = V;
}

// Bind Bus
void CommonDataBus::grandAccess () {
	bool granted = false;
	char token = this->token;
	char index = 0;

	// For each unit
	for (int i = 1; i <= _COMMONDATABUS_UNITS_; i++){
		// Don't get out of range
		index = (token + i) % _COMMONDATABUS_UNITS_;

		// If access not given and asked for access
		if (!granted && this->unit_list[index].request) {
			granted = true;
			this->unit_list[index].access = true;
			this->unit_list[index].request = false;
			this->token = index;
		}
		else {
			this->unit_list[index].access = false;
		}
	}

	// CDB state
	if (granted) {
		this->active = true;
	}
	else {
		this->active = false;
	}

};

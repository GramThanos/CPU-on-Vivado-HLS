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
 *     Class of the command Issue unit
 */

// Libraries
#include "global_vars.h"
#include "Issue.h"

// Init Issue
void Issue::init () {
	// Init Register File
	this->rf.init();
	// Init Reorder Buffer
	this->rb.init(&(this->rf));
	// Init Arithmetic Unit
	this->fau.init(_ISSUE_AU_CODE_);
	// Init Logic Unit
	this->flu.init(_ISSUE_LU_CODE_);
	// Init CDB
	this->cdb.init();

	// Bind units with cdb
	this->rb.subscribe(this->cdb.bind());
	this->fau.subscribe(this->cdb.bind());
	this->flu.subscribe(this->cdb.bind());
};

// Issue
bool Issue::issue (bit2 type, bit2 func, bit5 Rd, bit5 Rs, bit5 Rt) {
	// Common data bus broadcast data
	this->cdb.broadcast();
	// Get data from common data bus
	this->rb.checkBroadcast();
	this->fau.checkBroadcast();
	this->flu.checkBroadcast();
	// Reorder buffer result write
	this->rb.checkBuffer();

	// Init command issued flag
	bool issued = false;

	// Init command's reservation station tag variable
	bit5 tag = 0b00;

	// Init command's registers' data variables
	bool Rs_data_dirty = false;
	bit5 Rs_data_Q = 0b0;
	bit32 Rs_data_V = 0b0;
	bool Rt_data_dirty = false;
	bit5 Rt_data_Q = 0b0;
	bit32 Rt_data_V = 0b0;


	// If arithmetic command
	if (type == _ISSUE_AU_CODE_) {

		// Get avaliable rs
		tag = this->fau.isAvailiable();

		// If a reservation station is availiable
		// and if reorder buffer is not full
		if (tag != 0b0 && !this->rb.isFull()) {

			// Get Rs register data
			if (this->rb.hasReference(Rs)) {
				// Reference data
				Rs_data_dirty = true;
				Rs_data_Q = this->rb.readReference(Rs);
			} else {
				// Value data
				Rs_data_V = this->rf.read(Rs);
			}

			// Get Rt register data
			if (this->rb.hasReference(Rt)) {
				// Reference data
				Rt_data_dirty = true;
				Rt_data_Q = this->rb.readReference(Rt);
			} else {
				// Value data
				Rt_data_V = this->rf.read(Rt);
			}

			// Issue the command
			this->fau.issue(
				func,
				( Rs_data_dirty ? Rs_data_Q : 0b0),
				(!Rs_data_dirty ? Rs_data_V : 0b0),
				( Rt_data_dirty ? Rt_data_Q : 0b0),
				(!Rt_data_dirty ? Rt_data_V : 0b0)
			);

			// Add command on Reorder buffer
			this->rb.load(tag, Rd, 0b0, 0b0);
			// TODO: Add support for the command and pc data

			// Set command issued flag
			issued = true;
		}
	}

	// If logic command
	else if (type == _ISSUE_LU_CODE_) {

		// Get avaliable rs
		tag = this->flu.isAvailiable();

		// If a reservation station is availiable
		// and if reorder buffer is not full
		if (tag != 0b0 && !this->rb.isFull()) {

			// Get Rs register data
			if (this->rb.hasReference(Rs)) {
				// Reference data
				Rs_data_dirty = true;
				Rs_data_Q = this->rb.readReference(Rs);
			} else {
				// Value data
				Rs_data_V = this->rf.read(Rs);
			}

			// Get Rt register data
			if (this->rb.hasReference(Rt)) {
				// Reference data
				Rt_data_dirty = true;
				Rt_data_Q = this->rb.readReference(Rt);
			} else {
				// Value data
				Rt_data_V = this->rf.read(Rt);
			}

			// Issue the command
			this->flu.issue(
				func,
				( Rs_data_dirty ?Rs_data_Q : 0b0),
				(!Rs_data_dirty ?Rs_data_V : 0b0),
				( Rt_data_dirty ?Rt_data_Q : 0b0),
				(!Rt_data_dirty ?Rt_data_V : 0b0)
			);

			// Add command on Reorder buffer
			this->rb.load(tag, Rd, 0b0, 0b0);
			// TODO: Add support for the command and pc data

			// Set command issued flag
			issued = true;
		}
	}

	// Unknown command
	else {
		// On unknown commands do nothing
		// TODO: In the future maybe raise a cpu exception

		// Set command issued flag
		issued = true;
	}

	// Make calculations on the functional units
	this->fau.calculate();
	this->flu.calculate();

	// Common data bus grand access
	this->cdb.grandAccess();
	// Functional units check common data bus accesses
	this->fau.checkAccess();
	this->flu.checkAccess();

	// Return issued flag
	return issued;
};
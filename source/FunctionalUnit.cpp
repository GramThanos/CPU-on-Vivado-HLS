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
 *     Class of the Functional units
 */

// Libraries
#include "global_vars.h"
#include "ReservationStation.h"
#include "FunctionalUnit.h"
#include "CommonDataBus.h"

// General FunctionalUnit

	// Init FunctionalUnit
	void FunctionalUnit::init (bit2 tag) {
		// Set name
		this->tag = tag;
	};

	// Subscribe on cdb
	void FunctionalUnit::subscribe (CommonDataBus::busBind* cdb) {
		// Set cdb
		this->cdb = cdb;
	};




// Arithmetic FunctionalUnit

	// Init
	void FunctionalArithmeticUnit::init (bit2 tag) {
		// Init super
		this->super::init(tag);

		// Init each rs
		for (int i = 0; i < _FUNCTIONAL_ARITHMETIC_UNIT_RS_; ++i){
			// Set tag name
			this->rs[i].init(tag, i + 1);
		}

		// Init calculate stages
		for (int i = 0; i < _FUNCTIONAL_ARITHMETIC_UNIT_LATENCY_; ++i){
			// Set tag name
			this->calculateStages[i].active = false;
			this->calculateStages[i].Q = 0b0;
			this->calculateStages[i].func = 0b0;
			this->calculateStages[i].Vs = 0b0;
			this->calculateStages[i].Vt = 0b0;
			this->calculateStages[i].R = 0b0;
		}
	};

	// Get availiable rs (if any)
	bit5 FunctionalArithmeticUnit::isAvailiable () {
		// For each rs
		for (int i = 0; i < _FUNCTIONAL_ARITHMETIC_UNIT_RS_; ++i){
			// If not busy
			if (!(this->rs[i].isBusy())) {
				// Return full tag
				return ((this->tag << 3) | this->rs[i].getName());
			}
		}

		// No rs availiable
		return 0b0;
	};

	// Issue a command
	void FunctionalArithmeticUnit::issue (bit2 func, bit5 Qs, bit32 Vs, bit5 Qt, bit32 Vt) {
		int index = -1;

		// For each rs
		for (int i = 0; i < _FUNCTIONAL_ARITHMETIC_UNIT_RS_; ++i){
			// If not busy
			if (!(this->rs[i].isBusy())) {
				// Return full tag
				index = i;
				break;
			}
		}

		// Set func
		this->rs[index].setFunc(func);

		// Set a Qs or a Vs
		if (Qs != 0) {
			this->rs[index].setQs(Qs);
		}
		else {
			this->rs[index].setVs(Vs);
		}

		// Set a Qt or a Vt
		if (Qt != 0) {
			this->rs[index].setQt(Qt);
		}
		else {
			this->rs[index].setVt(Vt);
		}
	}

	// Make calculations
	void FunctionalArithmeticUnit::calculate () {
		// Check if we need to request access
		if (
			// If we will have a result the next round
			this->calculateStages[_FUNCTIONAL_ARITHMETIC_UNIT_LATENCY_ - 2].active ||
			// If we have the result but no access
			this->calculateStages[_FUNCTIONAL_ARITHMETIC_UNIT_LATENCY_ - 1].active && !this->cdb->access
		) {
			this->cdb->request = true;
		} else {
			this->cdb->request = false;
		}

		bool noStall = 0;
		// If last data broadcasted or trash
		if (this->cdb->access || !(this->calculateStages[_FUNCTIONAL_ARITHMETIC_UNIT_LATENCY_ - 1].active)){
			// No stall
			noStall = 1;
		}

		// Loop from bottom
		for (int i = _FUNCTIONAL_ARITHMETIC_UNIT_LATENCY_ - 2; i >= 0; i--){
			// If no stall
			if (noStall) {
				// Send to next stage
				this->calculateStages[i + 1].active = this->calculateStages[i].active;
				this->calculateStages[i].active = false;
				this->calculateStages[i + 1].Q = this->calculateStages[i].Q;
				this->calculateStages[i].Q = 0b0;
				this->calculateStages[i + 1].func = this->calculateStages[i].func;
				this->calculateStages[i].func = 0b0;
				this->calculateStages[i + 1].Vs = this->calculateStages[i].Vs;
				this->calculateStages[i].Vs = 0b0;
				this->calculateStages[i + 1].Vt = this->calculateStages[i].Vt;
				this->calculateStages[i].Vt = 0b0;
				this->calculateStages[i + 1].R = this->calculateStages[i].R;
				this->calculateStages[i].R = 0b0;
			}

			// Stall next stage?
			noStall = (noStall || !(this->calculateStages[i].active));
		}

		// Check if load new job
		if (noStall) {
			this->loadJob();
		}
	};

	// Load job
	void FunctionalArithmeticUnit::loadJob () {
		int index = -1;
		bool found = false;

		// For each rs
		for (int i = 0; i < _FUNCTIONAL_ARITHMETIC_UNIT_RS_; ++i){
			if (this->rs[i].isReady() && !this->rs[i].isRunning()) {
				found = true;
				index = i;
				break;
			}
		}

		// If ready rs found
		if (found) {

			// Insert
			this->calculateStages[0].active = true;
			this->calculateStages[0].Q = ((this->tag << 3) | this->rs[index].getName());
			this->calculateStages[0].func = this->rs[index].getFunc();
			this->calculateStages[0].Vs = this->rs[index].getVs();
			this->calculateStages[0].Vt = this->rs[index].getVt();

			// ADD 00
			if (this->calculateStages[0].func == 0b0) {
				this->calculateStages[0].R = this->calculateStages[0].Vs + this->calculateStages[0].Vt;
			}
			// SUB 01
			else if (this->calculateStages[0].func == 0b1) {
				this->calculateStages[0].R = this->calculateStages[0].Vs - this->calculateStages[0].Vt;
			}
			// OTHER
			else {
				this->calculateStages[0].R = 0b0;
			}
			
			// Set as running
			this->rs[index].setAsRunning();
		}
	};

	// Send cdb values to rs
	void FunctionalArithmeticUnit::checkBroadcast () {
		// For each rs
		for (int i = 0; i < _FUNCTIONAL_ARITHMETIC_UNIT_RS_; ++i){
			// Send data
			this->rs[i].checkBroadcast(this->cdb->Q, this->cdb->V);
		}
	};

	// Prepare data for cdb
	void FunctionalArithmeticUnit::checkAccess () {
		// Check if we have access
		if (this->cdb->access) {
			// Write to cdb
			this->cdb->write_Q = this->calculateStages[_FUNCTIONAL_ARITHMETIC_UNIT_LATENCY_ - 1].Q;
			this->cdb->write_V = this->calculateStages[_FUNCTIONAL_ARITHMETIC_UNIT_LATENCY_ - 1].R;
		} else {
			this->cdb->write_Q = 0b0;
			this->cdb->write_V = 0b0;
		}
	};




// Logic FunctionalUnit

	// Init
	void FunctionalLogicUnit::init (bit2 tag) {
		// Init super
		this->super::init(tag);

		// Init each rs
		for (int i = 0; i < _FUNCTIONAL_LOGIC_UNIT_RS_; ++i){
			// Set tag name
			this->rs[i].init(tag, i + 1);
		}

		// Init calculate stages
		for (int i = 0; i < _FUNCTIONAL_LOGIC_UNIT_LATENCY_; ++i){
			// Set tag name
			this->calculateStages[i].active = false;
			this->calculateStages[i].Q = 0b0;
			this->calculateStages[i].func = 0b0;
			this->calculateStages[i].Vs = 0b0;
			this->calculateStages[i].Vt = 0b0;
			this->calculateStages[i].R = 0b0;
		}
	};

	// Get availiable rs (if any)
	bit5 FunctionalLogicUnit::isAvailiable () {
		// For each rs
		for (int i = 0; i < _FUNCTIONAL_LOGIC_UNIT_RS_; ++i){
			// If not busy
			if (!(this->rs[i].isBusy())) {
				// Return full tag
				return ((this->tag << 3) | this->rs[i].getName());
			}
		}

		// No rs availiable
		return 0b0;
	};

	// Issue a command
	void FunctionalLogicUnit::issue (bit2 func, bit5 Qs, bit32 Vs, bit5 Qt, bit32 Vt) {
		int index = -1;

		// For each rs
		for (int i = 0; i < _FUNCTIONAL_LOGIC_UNIT_RS_; ++i){
			// If not busy
			if (!(this->rs[i].isBusy())) {
				// Return full tag
				index = i;
				break;
			}
		}

		// Set func
		this->rs[index].setFunc(func);

		// Set a Qs or a Vs
		if (Qs != 0) {
			this->rs[index].setQs(Qs);
		}
		else {
			this->rs[index].setVs(Vs);
		}

		// Set a Qt or a Vt
		if (Qt != 0) {
			this->rs[index].setQt(Qt);
		}
		else {
			this->rs[index].setVt(Vt);
		}
	}

	// Make calculations
	void FunctionalLogicUnit::calculate () {
		// Check if we need to request access
		if (
			// If we will have a result the next round
			this->calculateStages[_FUNCTIONAL_LOGIC_UNIT_LATENCY_ - 2].active ||
			// If we have the result but no access
			this->calculateStages[_FUNCTIONAL_LOGIC_UNIT_LATENCY_ - 1].active && !this->cdb->access
		) {
			this->cdb->request = true;
		}
		else {
			this->cdb->request = false;
		}

		bool noStall = 0;
		// If last data broadcasted or trash
		if (this->cdb->access || !(this->calculateStages[_FUNCTIONAL_LOGIC_UNIT_LATENCY_ - 1].active)){
			// No stall
			noStall = 1;
		}

		// Loop from bottom
		for (int i = _FUNCTIONAL_LOGIC_UNIT_LATENCY_ - 2; i >= 0; i--){
			// If no stall
			if (noStall) {
				// Send to next stage
				this->calculateStages[i + 1].active = this->calculateStages[i].active;
				this->calculateStages[i].active = false;
				this->calculateStages[i + 1].Q = this->calculateStages[i].Q;
				this->calculateStages[i].Q = 0b0;
				this->calculateStages[i + 1].func = this->calculateStages[i].func;
				this->calculateStages[i].func = 0b0;
				this->calculateStages[i + 1].Vs = this->calculateStages[i].Vs;
				this->calculateStages[i].Vs = 0b0;
				this->calculateStages[i + 1].Vt = this->calculateStages[i].Vt;
				this->calculateStages[i].Vt = 0b0;
				this->calculateStages[i + 1].R = this->calculateStages[i].R;
				this->calculateStages[i].R = 0b0;
			}

			// Stall next stage?
			noStall = (noStall || !(this->calculateStages[i].active));
		}

		// Check if load new job
		if (noStall) {
			this->loadJob();
		}
	};

	// Load job
	void FunctionalLogicUnit::loadJob () {
		int index = -1;
		bool found = false;

		// For each rs
		for (int i = 0; i < _FUNCTIONAL_LOGIC_UNIT_RS_; ++i){
			if (this->rs[i].isReady() && !this->rs[i].isRunning()) {
				found = true;
				index = i;
				break;
			}
		}

		// If ready rs found
		if (found) {

			// Insert
			this->calculateStages[0].active = true;
			this->calculateStages[0].Q = ((this->tag << 3) | this->rs[index].getName());
			this->calculateStages[0].func = this->rs[index].getFunc();
			this->calculateStages[0].Vs = this->rs[index].getVs();
			this->calculateStages[0].Vt = this->rs[index].getVt();

			// AND 00
			if (this->calculateStages[0].func == 0b0) {
				this->calculateStages[0].R = this->calculateStages[0].Vs & this->calculateStages[0].Vt;
			}
			// OR  01
			else if (this->calculateStages[0].func == 0b1) {
				this->calculateStages[0].R = this->calculateStages[0].Vs | this->calculateStages[0].Vt;
			}
			// NOT 10
			else if (this->calculateStages[0].func == 0b10) {
				this->calculateStages[0].R = ~this->calculateStages[0].Vs;
			}
			// OTHER
			else {
				this->calculateStages[0].R = 0b0;
			}
			
			// Set as running
			this->rs[index].setAsRunning();
		}
	};

	// Send cdb values to rs
	void FunctionalLogicUnit::checkBroadcast () {
		// For each rs
		for (int i = 0; i < _FUNCTIONAL_LOGIC_UNIT_RS_; ++i){
			// Send data
			this->rs[i].checkBroadcast(this->cdb->Q, this->cdb->V);
		}
	};

	// Prepare data for cdb
	void FunctionalLogicUnit::checkAccess () {
		// Check if we have access
		if (this->cdb->access) {
			// Write to cdb
			this->cdb->write_Q = this->calculateStages[_FUNCTIONAL_LOGIC_UNIT_LATENCY_ - 1].Q;
			this->cdb->write_V = this->calculateStages[_FUNCTIONAL_LOGIC_UNIT_LATENCY_ - 1].R;
		} else {
			this->cdb->write_Q = 0b0;
			this->cdb->write_V = 0b0;
		}
	};

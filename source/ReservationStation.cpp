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
 *     Class of the Reservation Station
 */

// Libraries
#include "global_vars.h"
#include "ReservationStation.h"


// Init
void ReservationStation::init (bit2 parentTag, bit3 tag) {
	// Set name
	this->tag = tag;
	// Set parent name
	this->parentTag = parentTag;
	// Clear rs
	this->clear();
};

// Clear
void ReservationStation::clear () {
	// Set not busy
	this->busy = false;
	// Set not running
	this->running = false;
	// Init registers
	this->s.V = 0b0;
	this->t.V = 0b0;
	this->s.Q = 0b0;
	this->t.Q = 0b0;
	// Set no values
	this->s_value = false;
	this->t_value = false;
	// Reset func
	this->func = 0b0;
};

// Check if busy
bool ReservationStation::isBusy () {
	return this->busy;
};

// Check if ready
bool ReservationStation::isReady () {
	return (this->s_value && this->t_value);
};

// Check if running
bool ReservationStation::isRunning () {
	return this->running;
};



// Set func
void ReservationStation::setFunc (bit2 func) {
	// Set func
	this->func = func;
}

// Set Q of Rs
void ReservationStation::setQs (bit5 Q) {
	// Set Q
	this->s.Q = Q;
	// Set not loaded
	this->s_value = false;
	// Set as busy
	this->busy = true;
}

// Set Q of Rt
void ReservationStation::setQt (bit5 Q) {
	// Set Q
	this->t.Q = Q;
	// Set not loaded
	this->t_value = false;
	// Set as busy
	this->busy = true;
}

// Set V of Rs
void ReservationStation::setVs (bit32 V) {
	// Set V
	this->s.V = V;
	// Set loaded
	this->s_value = true;
	// Set as busy
	this->busy = true;
}

// Set V of Rt
void ReservationStation::setVt (bit32 V) {
	// Set V
	this->t.V = V;
	// Set loaded
	this->t_value = true;
	// Set as busy
	this->busy = true;
}

// Set running
void ReservationStation::setAsRunning () {
	// Set running to true
	this->running = true;
}

// Check broadcast
void ReservationStation::checkBroadcast (bit5 Q, bit32 V) {
	// Don't check if not busy
	if (!this->busy) {
		return;
	}
	// Check for Rs
	if (!this->s_value && Q == this->s.Q) {
		// Save value
		this->setVs(V);
	}
	// Check for Rt
	if (!this->t_value && Q == this->t.Q) {
		// Save value
		this->setVt(V);
	}

	// If broadcast this reservation station
	// Clear reservation
	if (Q == ((this->parentTag << 3) | this->tag)) {
		this->clear();
	}
}

// Get V of Rs
bit32 ReservationStation::getVs () {
	return this->s.V;
}

// Get V of Rt
bit32 ReservationStation::getVt () {
	return this->t.V;
}

// Get name
bit3 ReservationStation::getName () {
	return this->tag;
}

// Get func
bit5 ReservationStation::getFunc () {
	return this->func;
}

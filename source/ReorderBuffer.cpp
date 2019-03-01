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
 *     Class of the Reorder Buffer
 */

// Libraries
#include "global_vars.h"
#include "ReorderBuffer.h"
#include "RegisterFile.h"
#include "CommonDataBus.h"

// Init buffer
void ReorderBuffer::init (RegisterFile* rf) {
	// Init buffer indexes
	this->bufferTop = 0;
	this->bufferBottom = 0;

	this->rf = rf;

	// Init command stages
	for (int i = 0; i < _REORDER_BUFFER_SIZE_; ++i){
		this->buffer[i].active = false;
		this->buffer[i].done = false;
		this->buffer[i].tag = 0b0;
		this->buffer[i].destination = 0b0;
		this->buffer[i].result = 0b0;
		this->buffer[i].command = 0b0;
		this->buffer[i].exception_status = 0b0;
		this->buffer[i].PC = 0b0;
	}

	// Init register status
	for (int i = 0; i < 32; ++i){
		this->registers[i].reference = false;
		this->registers[i].tag = 0b0;
	}
};

// Check if register has reference
bool ReorderBuffer::hasReference (bit5 reg) {
	// Return value
	return this->registers[reg].reference;
};
// Get register's reference
bit5 ReorderBuffer::readReference (bit5 reg) {
	// Return value
	return this->registers[reg].tag;
};

// Check if it is full
bool ReorderBuffer::isFull () {
	return this->buffer[this->bufferBottom].active;
};

// Load Command
void ReorderBuffer::load (bit5 tag, bit5 Rd, bit32 command, bit32 pc) {
	// Load command
	this->buffer[this->bufferBottom].active = true;
	this->buffer[this->bufferBottom].done = false;
	this->buffer[this->bufferBottom].tag = tag;
	this->buffer[this->bufferBottom].destination = Rd;
	this->buffer[this->bufferBottom].result = 0b0;
	this->buffer[this->bufferBottom].command = command;
	this->buffer[this->bufferBottom].exception_status = 0b0;
	this->buffer[this->bufferBottom].PC = pc;

	// Save reference
	this->registers[Rd].reference = true;
	this->registers[Rd].tag = tag;

	// Set the bottom to the next stage
	this->bufferBottom++;
	if (this->bufferBottom == _REORDER_BUFFER_SIZE_) {
		this->bufferBottom = 0;
	}
};

// Subscribe on cdb
void ReorderBuffer::subscribe (CommonDataBus::busBind* cdb) {
	// Set cdb
	this->cdb = cdb;
};

// Send cdb values to rs
void ReorderBuffer::checkBroadcast () {
	// For each stage 
	for (int i = 0; i < _REORDER_BUFFER_SIZE_; ++i){
		// If rename match
		if (this->buffer[i].active && this->buffer[i].tag == this->cdb->Q) {
			// Set value
			this->buffer[i].done = true;
			this->buffer[i].result = this->cdb->V;
		}
	}
};

// Save command on register file
void ReorderBuffer::checkBuffer () {
	// If top command ready
	if (this->buffer[this->bufferTop].active && this->buffer[this->bufferTop].done) {
		// Write
		this->rf->write(
			this->buffer[this->bufferTop].destination,
			this->buffer[this->bufferTop].result
		);
		// Reset stage
		this->buffer[this->bufferTop].active = false;
		this->buffer[this->bufferTop].done = false;
		// Clear reference
		this->registers[this->buffer[this->bufferTop].destination].reference = false;

		// Move the queue up
		this->bufferTop++;
		if (this->bufferTop == _REORDER_BUFFER_SIZE_) {
			this->bufferTop = 0;
		}
	}
};

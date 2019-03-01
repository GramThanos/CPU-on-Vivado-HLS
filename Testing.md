# Testing the CPU

## Test programs executed

To test the CPU I created 3 simple programs that I executed and check their results.

Before the execution of the test programs, I initialized some CPU Registers, since our CPU has no access to any cache with data.

Register file initialization before program execution.
```text
R1  00000000000000000000000000000001
R2  00000000000000000000000000000010
R3  00000000000000000000000000000011
R4  00000000000000000000000000000100
```

Test program 1 (unrelated commands with NOPs between them)
```Assebly
#func rd   rt   rt
ADD   R5   R1   R2
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
ADD   R6   R3   R4
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
ADD   R7   R1   R3
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
AND   R7   R1   R3
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
NOP   R0   R0   R0
```

Test program 2 (unrelated commands)
```Assebly
#func rd   rt   rt
ADD   R8   R1   R2
ADD   R9   R3   R4
ADD   R10  R1   R3
NOP   R0   R0   R0
```

Test program 3 (commands with relations)
```Assebly
#func rd   rt   rt
ADD   R11  R1   R2
ADD   R12  R11  R3
ADD   R13  R12  R4
SUB   R14  R11  R1
OR    R14  R3   R2
NOP   R0   R0   R0
```

## Executing a program

You can execute a program by `cpu` as top level function (the function that will run on the FPGA) and creating a test bench file to call it.

An example testbench file can can be found below.

```C
/*
 * Exaple Testbench for CPU execution
 */

// Libraries
#include "global_vars.h"
#include "testbench.h"

int main(int argc, char** argv) {
	// Print info
	printf("\n");
	printf("  Sample program execution ...\n");

	// Variables
	int pc = 0;
	bit32* info = (bit32*) malloc(1 * sizeof(bit32));
	
	// Init register file data
	bit32* registers = (bit32*) malloc(32 * sizeof(bit32));
	for (int i = 0; i < 32; ++i) registers[i] = 0b0;

	// Init program's commands
	bit32* commands = (bit32*) malloc(32 * sizeof(bit32));
	for (int i = 0; i < 32; ++i) commands[i] = 0b0;

	// Data for the initialization of the registers
	registers[1] = 0b1;
	registers[2] = 0b10;
	registers[3] = 0b11;
	registers[4] = 0b100;

	// Program's code
	// Command         ADD R11  R1   R2   
	commands[0] = ((0b0100010110000100010) << 13);
	// Command         ADD R12  R11  R3   
	commands[1] = ((0b0100011000101100011) << 13);
	// Command         ADD R13  R12  R4   
	commands[2] = ((0b0100011010110000100) << 13);
	// Command         SUB R14  R11  R1   
	commands[3] = ((0b0101011100101100001) << 13);
	// Command         OR  R14  R3   R2   
	commands[4] = ((0b0001011100001100010) << 13);
	// Command         NOP R0   R0   R0   
	commands[5] = ((0b1100000000000000000) << 13);

	// End Command (Write 0b1 on R31)
	// Command         ADD R31  R0   R30  
	commands[6] = ((0b0001111110000011110) << 13);
	// Command         NOP R0   R0   R0   
	commands[7] = ((0b1100000000000000000) << 13);

	// Run the sample program
	cpu(info, registers, commands, 7);
	printf("  Program was executed in %d CPU cycles\n", info[0]);

	// Return
	return 0;
}
```

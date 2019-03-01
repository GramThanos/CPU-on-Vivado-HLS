
# CPU on Vivado HLS
### A simple MIPS-like CPU demo in C++ for Xilinx Vivado HLS

Nowadays, tools like Xilinx’s Vivado HLS let us synthesize hardware code from high level languages. Such tools were designed to speed up the development on FPGA projects and to enable porting codes form languages like C++ to the hardware.

In this project I developed the main parts of a MIPS-like CPU in a C++ for use with the Vivado HLS tool. The end result looks like a CPU simulator. This project was developed as an assignment of the Computer architecture Course on Technical University of Crete.

This demo CPU features an Out-of-Order command execution by implementing the Tomasulo's algorithm. I tested the CPU by running simple custom programs which were executed with correct results.



___

## Documentation

[Project's Files](Files.md)

[Testion the CPU](Testing.md)

___


### License

This project is under [The MIT license](https://opensource.org/licenses/MIT).
I do although appreciate attribute.

Copyright (c) 2019 Grammatopoulos Athanasios-Vasileios

___

[![GramThanos](https://avatars2.githubusercontent.com/u/14858959?s=42&v=4)](https://github.com/GramThanos)

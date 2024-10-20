# Chip8

The Chip 8 is an interpreted language created by RCA engineer Joe Weisbecker in 1977.

It's Machine Specifications are as listed below:

- Memory: CHIP-8 has direct access to up to 4 kilobytes of RAM
- Display: 64 x 32 pixels (or 128 x 64 for SUPER-CHIP) monochrome, ie. black or white
- A program counter, often called just “PC”, which points at the current instruction in memory
- One 16-bit index register called “I” which is used to point at locations in memory
- A stack for 16-bit addresses, which is used to call subroutines/functions and return from them
- An 8-bit delay timer which is decremented at a rate of 60 Hz (60 times per second) until it reaches 0
- An 8-bit sound timer which functions like the delay timer, but which also gives off a beeping sound as long as it’s not 0
- 16 8-bit (one byte) general-purpose variable registers numbered 0 through F hexadecimal, ie. 0 through 15 in decimal, called V0 through VF
- VF is also used as a flag register; many instructions will set it to either 1 or 0 based on some rule, for example using it as a carry flag

The Following Project was therefore created in attempt to gain an understanding over low level concepts such as Opcodes (similar to syscalls), stacks, dealing with memory directly, registers, etc...

4-flags ROM provided by Timendus (integral for testing of mathematical operations)
![Screenshot_20241020_184000](https://github.com/user-attachments/assets/00344a29-fca4-4a5a-8c31-241ee9a31800)
3-corax+ ROM provided by Timendus (integral for testing of opcodes)
![Screenshot_20241020_183935](https://github.com/user-attachments/assets/09e9e30f-16fb-4e14-88a7-9e79cca33ac4)
Breakout:
![Screenshot_20241020_183902](https://github.com/user-attachments/assets/92514e91-189d-42c1-b74b-025f260c41c9)

Dependencies To Build:
  SDL2 (note currently this program only builds on linux)

Build Instuctions:
  #####
    make clean & make

How to Run Program:
  #####
    ./main [path_to_rom][width_of_window][height_of_window]

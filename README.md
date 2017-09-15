### CS430: Project 1 ###

Developer: Itreau Bigsby 
Email: ib233@nau.edu

## Purpose ##

The purpose of this project is to create a PPM file read and writer. The program
is written in C and was developed on a Unix based machine. The reader/writer is
meant to convert between P3 and P6 PPM file formats.

## Contents ##

The contents of the project repository are as follows:
- Source code written in C programming language
- A Makefile used to build the project
- A sample program build
- Sample input/output files to be used with the sample build

## Usage ##

This project converts between P3 and P6 format for .ppm files. Steps to use: 

1. Using a command line interface, navigate to the project directory containing the project code
2. If pre-existing build exists, type "make clean" in order to remove the previous build
3. Type "make" to build a new executable file
4. Use following format to run program: "./ppmrw (output format: 3 or 6) (input file name) (output file name)"

# NOTE #

A working example exists in the project direcory. the input files are named "p3example.ppm" and "p6example.ppm"

## Known Issues ##

The one main issue I have been unable to fix in this project is converting large P3 color values. For example, a P3
rgb value of "255" converts to some strange output in the P6 file. However, this does not occur for every color input. 
Other than that, the project should execute fine. The only other requirement that might be missing is error catching that 
I may have not have thought of. 

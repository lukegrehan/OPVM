//
//  main.cpp
//  Virtual Machine
//
//  Created by Seán Hargadon on 04/04/2014.
//  Copyright (c) 2014 Seán Hargadon. All rights reserved.
//

#include <iostream>
#include "Assembler.h"
#include "Intepreter.h"

using namespace std;


//immidiate value
//1000
//0x100
//0b1111


// Options
//AL    0x0
//EQ    0x1
//NE    0x2
//GT    0x3
//LT    0x4
//GE    0x5
//LE    0x6

//0x1

//Instructions
//11111111111111111111111
//    4        4    4  4    4  4   4
//[OPCODE][Option][S I][RD][RA][RB][LINK]

//mov   RD <- RS ^ Val          0x00            0x000000
//add   RD <- RS1 + RS2 ^ Val   0x01
//sub   RD <- RS1 - RS2 ^ Val   0x02
//mul   RD <- RS1 * RS2 ^ Val   0x03
//div   RD <- RS1 / RS2 ^ Val   0x04
//and   RD <- RS1 & RS2 ^ Val   0x05
//or    RD <- RS1 | RS2 ^ Val   0x06
//not   RD <- !RS1 ^ !Val       0x07
//xor   RD <- RS1 ^ RS2 ^ Val   0x08
//sr    RD <- RS1 >> 1          0x09
//sl    RD <- RS1 << 1          0x0A
//cmp   RS1 == RS2 ^ Val        0x0B
//b     B label                 0x0C
//ld    RD <- [RS] ^ Val        0x0D
//str   [RD] <- RS ^ Val        0x0E
//push  [SP] <- RS1, RS2...RSN  str for sources
//pop   RD1, RD2...RDN <- [SP]  ld for destinations
//mem   "ascii", 10000, 0x100, 0b100  PC+=2

//flags
//N
//Z
//C
//V

//registers
//R0
//R1
//R2
//R3
//R4
//R5
//R6
//R7
//R8
//R9
//R10
//R11
//R12
//R13 (SP)
//R14 (LR)
//R15 (PC)

//empty ascending stack

//[SP] <- R0, R1, R2
//[SP] <- R0
//SP <- SP + 1
//[SP] <- R1
//SP <- SP + 1
//[SP] <- R2
//SP <- SP + 1

//R0, R1, R2 <- [SP]
//R2 <- [SP]
//SP <- SP - 1
//R1 <- [SP]
//SP <- SP - 1
//R0 <- [SP]
//SP <- SP - 1

//          000011110000111100001111
//PC ++     0x101FF1

//  0x0000000
//  1111 1111 1111

//R0 <- [R0]


//while
//R0 == 0
//B endWhile : EQ
//R0 <- R0 + 1
//[SP] <- R0, R1, R2
//B while
//endWhile
             

void stepThroughAndPrint(Intepreter &intepreter)
{
    intepreter.step();
    intepreter.print();
}

int main(int argc, const char * argv[])
{
    vector<string> code;
    code.push_back("SP <- 0xF"); //set stack
    code.push_back("R0 <- 0 : AL");
    code.push_back("R1 <- 7");
    code.push_back("while");
    code.push_back("R0 == 100");
    code.push_back("R0 <- R0 + R1");
    code.push_back("[SP] <- R0, R1");
    code.push_back("R0, R1 <- [SP]");
    code.push_back("B while");
    
    Assembler assembler = Assembler(code);
    vector<int> byte_code = assembler.assemble();

    Intepreter intepreter = Intepreter(byte_code, 1000);
    //stepThroughAndPrint(intepreter);
    //stepThroughAndPrint(intepreter);
    //stepThroughAndPrint(intepreter);

    intepreter.evaluate();
    
    
    return 0;
}


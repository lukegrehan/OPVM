//
//  Intepreter.h
//  Virtual Machine
//
//  Created by Seán Hargadon on 04/04/2014.
//  Copyright (c) 2014 Seán Hargadon. All rights reserved.
//

#ifndef __Virtual_Machine__Intepreter__
#define __Virtual_Machine__Intepreter__

#include <iostream>
#include <vector>
#include <iomanip>
#include <unistd.h>

using namespace std;

class Intepreter {
private:
    int register_0;
    int register_1;
    int register_2;
    int register_3;
    int register_4;
    int register_5;
    int register_6;
    int register_7;
    int register_8;
    int register_9;
    int register_10;
    int register_11;
    int register_12;
    int SP;
    int LR;
    int PC;
    
    char NZCV;
    
    vector<int> memory;
    
    enum opcodes {
        OPCODE_MOV = 0x0, OPCODE_ADD = 0x1, OPCODE_SUB = 0x2, OPCODE_MUL = 0x3, OPCODE_DIV = 0x4, OPCODE_AND = 0x5, OPCODE_OR = 0x6, OPCODE_NOT = 0x7, OPCODE_XOR = 0x8, OPCODE_RSHIFT = 0x9, OPCODE_LSHIFT = 0xA, OPCODE_CMP = 0xB, OPCODE_BREAK = 0xC, OPCODE_LOAD = 0xD, OPCODE_STORE = 0xE
    };
    
    enum conditions {
        CONDITION_AL = 0x0, CONDITION_EQ = 0x1, CONDITION_NE = 0x2, CONDITION_GT = 0x3, CONDITION_LT = 0x4, CONDITION_GE = 0x5, CONDITION_LE = 0x6
    };
    
    struct Instruction {
        int opcode;
        int option;
        int I;
        int destination;
        int source1;
        int source2;
        int link;
    };

    void op_mov(int destination, int source1, int source2, bool immidiate);
    void op_add(int destination, int source1, int source2, bool immidiate);
    void op_sub(int destination, int source1, int source2, bool immidiate);
    void op_mul(int destination, int source1, int source2, bool immidiate);
    void op_div(int destination, int source1, int source2, bool immidiate);
    void op_and(int destination, int source1, int source2, bool immidiate);
    void op_or(int destination, int source1, int source2, bool immidiate);
    void op_not(int destination, int source, bool immidiate);
    void op_xor(int destination, int source1, int source2, bool immidiate);
    void op_rshift(int destination, int source1, int source2, bool immidiate);
    void op_lshift(int destination, int source1, int source2, bool immidiate);
    void op_cmp(int destination, int source1, int source2, bool immidiate);
    void op_break(int destination, int source1, int source2, bool immidiate);
    void op_load(int destination, int source1, int source2, bool immidiate);
    void op_store(int destination, int source1, int source2, bool immidiate);

    int& get_register(char reg);
    
public:
    Intepreter(vector<int> byte_code, int memory_size);
    Intepreter(vector<int> byte_code, int PC_init, int memory_size);
    void evaluate();
    void step();
    void print();
    
};

#endif /* defined(__Virtual_Machine__Intepreter__) */

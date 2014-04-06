//
//  Assembler.h
//  Virtual Machine
//
//  Created by Seán Hargadon on 04/04/2014.
//  Copyright (c) 2014 Seán Hargadon. All rights reserved.
//

#ifndef __Virtual_Machine__Assembler__
#define __Virtual_Machine__Assembler__

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Assembler {
private:
    vector<string> assembly;
    
    struct Instruction {
        int opcode;
        int option;
        int I;
        int destination;
        int source1;
        int source2;
        int link;
    };
    
    struct token {
        enum tokens {
            TOKENS_LBRACK, TOKENS_RBRACK, TOKENS_REG, TOKENS_MOVE, TOKENS_CMP, TOKENS_COMMA, TOKENS_ADD, TOKENS_MUL, TOKENS_SUB, TOKENS_DIV, TOKENS_AND, TOKENS_OR, TOKENS_NOT, TOKENS_XOR, TOKENS_BREAK, TOKENS_CONDITION, TOKENS_AL, TOKENS_EQ, TOKENS_NE, TOKENS_GT, TOKENS_LT, TOKENS_GE, TOKENS_LE, TOKENS_LSHIFT, TOKENS_RSHIFT, TOKENS_LQUOTE, TOKENS_RQUOTE, TOKENS_ASCII, TOKENS_DEC, TOKENS_HEX, TOKENS_BIN, TOKENS_LABEL, TOKENS_LINK
        };
        string ascii;
        int value;
        int reg;
        tokens type;
    };
    
public:
    
    Assembler(vector<string> assembly);
    vector<string> readFile(string file);
    vector<string> readString(string str);
    vector<int> assemble();
    vector<vector<token>> tokonise();
    
};

#endif /* defined(__Virtual_Machine__Assembler__) */

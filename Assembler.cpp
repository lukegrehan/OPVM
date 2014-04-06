//
//  Assembler.cpp
//  Virtual Machine
//
//  Created by Seán Hargadon on 04/04/2014.
//  Copyright (c) 2014 Seán Hargadon. All rights reserved.
//

#include "Assembler.h"



Assembler::Assembler(vector<string> assembly)
{
    this->assembly = assembly;
}


vector<string> Assembler::readFile(string file)
{
    vector<string> result;
    
    return result;
}

vector<string> Assembler::readString(string str)
{
    vector<string> result;
    
    return result;
}

vector<vector<Assembler::token>> Assembler::tokonise()
{
    vector<vector<Assembler::token>> tokens;
    
    bool quote_opened = false;
    
    for (int j = 0; j < this->assembly.size(); j++) {
        string instruction = this->assembly[j];
        
        vector<Assembler::token> toks;
        
        for (int i = 0; i < instruction.length(); i++) {
            token tok;
            if (instruction[i] == ' ') {
                continue;
            }
            if (instruction[i] == '[') {
                tok.type = token::TOKENS_LBRACK;
                toks.push_back(tok);
            }
            else if (instruction[i] == ']') {
                tok.type = token::TOKENS_RBRACK;
                toks.push_back(tok);
            }
            else if (instruction[i] == 'R') {
                tok.type = token::TOKENS_REG;
                string num;
                i++;
                for (int k = 0; instruction[i] != ' ' && i < instruction.length() && isnumber(instruction[i]); i++, k++) {
                    num.insert(k, 1, instruction[i]);
                }
                i--;
                tok.reg = atoi(num.c_str());
                toks.push_back(tok);
            }
            else if (instruction[i] == 'S') {
                tok.type = token::TOKENS_REG;
                tok.reg = 13;
                toks.push_back(tok);
                i++;
            }
            else if (instruction[i] == 'L') {
                tok.type = token::TOKENS_REG;
                tok.reg = 14;
                toks.push_back(tok);
                i++;
            }
            else if (instruction[i] == 'P') {
                tok.type = token::TOKENS_REG;
                tok.reg = 15;
                toks.push_back(tok);
                i++;
            }
            else if (instruction[i] == '<') {
                tok.type = token::TOKENS_MOVE;
                toks.push_back(tok);
                i++;
            }
            else if (instruction[i] == '=') {
                tok.type = token::TOKENS_CMP;
                toks.push_back(tok);
                i++;
            }
            else if (instruction[i] == ',') {
                tok.type = token::TOKENS_COMMA;
                toks.push_back(tok);
            }
            else if (instruction[i] == '+') {
                tok.type = token::TOKENS_ADD;
                toks.push_back(tok);
            }
            else if (instruction[i] == '*') {
                tok.type = token::TOKENS_MUL;
                toks.push_back(tok);
            }
            else if (instruction[i] == '-') {
                tok.type = token::TOKENS_SUB;
                toks.push_back(tok);
            }
            else if (instruction[i] == '/') {
                tok.type = token::TOKENS_DIV;
                toks.push_back(tok);
            }
            else if (instruction[i] == '&') {
                tok.type = token::TOKENS_AND;
                toks.push_back(tok);
            }
            else if (instruction[i] == '|') {
                tok.type = token::TOKENS_OR;
                toks.push_back(tok);
            }
            else if (instruction[i] == '!') {
                tok.type = token::TOKENS_NOT;
                toks.push_back(tok);
            }
            else if (instruction[i] == '^') {
                tok.type = token::TOKENS_XOR;
                toks.push_back(tok);
            }
            else if (instruction[i] == '<') {
                tok.type = token::TOKENS_LSHIFT;
                toks.push_back(tok);
                i++;
            }
            else if (instruction[i] == '>') {
                tok.type = token::TOKENS_RSHIFT;
                toks.push_back(tok);
                i++;
            }
            else if (instruction[i] == 'B') {
                tok.type = token::TOKENS_BREAK;
                toks.push_back(tok);
            }
            else if (instruction[i] == ':') {
                tok.type = token::TOKENS_CONDITION;
                toks.push_back(tok);
            }
            else if (instruction[i] == 'A' && instruction[i+1] == 'L') {
                tok.type = token::TOKENS_AL;
                toks.push_back(tok);
                i++;
            }
            else if (instruction[i] == 'E' && instruction[i+1] == 'Q') {
                tok.type = token::TOKENS_EQ;
                toks.push_back(tok);
                i++;
            }
            else if (instruction[i] == 'N' && instruction[i+1] == 'E') {
                tok.type = token::TOKENS_NE;
                toks.push_back(tok);
                i++;
            }
            else if (instruction[i] == 'G' && instruction[i+1] == 'T') {
                tok.type = token::TOKENS_GT;
                toks.push_back(tok);
                i++;
            }
            else if (instruction[i] == 'L' && instruction[i+1] == 'T') {
                tok.type = token::TOKENS_LT;
                toks.push_back(tok);
                i++;
            }
            else if (instruction[i] == 'G' && instruction[i+1] == 'E') {
                tok.type = token::TOKENS_GE;
                toks.push_back(tok);
                i++;
            }
            else if (instruction[i] == 'L' && instruction[i+1] == 'E') {
                tok.type = token::TOKENS_LT;
                toks.push_back(tok);
                i++;
            }
            else if (instruction[i] == '"') {
                if (quote_opened) {
                    tok.type = token::TOKENS_RQUOTE;
                }
                else {
                    tok.type = token::TOKENS_LQUOTE;
                    quote_opened = true;
                }
                toks.push_back(tok);
            }
            else if (quote_opened) {
                for (int k = 0; i != '"' && i < instruction.length(); i++, k++) {
                    tok.type = token::TOKENS_ASCII;
                    tok.ascii.insert(j, 1, instruction[i]);
                }
                toks.push_back(tok);
            }
            else if (isnumber(instruction[i])) {
                if (i+1 < instruction.length() - 1) {
                    if (instruction[i+1] == 'x') {
                        string num;
                        i += 2;
                        for (int k = 0; i != ' ' && i < instruction.length() && isalnum(instruction[i]); i++, k++) {
                            tok.type = token::TOKENS_HEX;
                            num.insert(k, 1, instruction[i]);
                        }
                        tok.value = (int)strtoull(num.c_str(), NULL, 16);
                        toks.push_back(tok);
                    }
                    else if (instruction[i+1] == 'b') {
                        string num;
                        i += 2;
                        for (int k = 0; i != ' ' && i < instruction.length() && isnumber(instruction[i]); i++, k++) {
                            tok.type = token::TOKENS_BIN;
                            num.insert(k, 1, instruction[i]);
                        }
                        tok.value = (int)strtoull(num.c_str(), NULL, 2);
                        toks.push_back(tok);
                    }
                    else {
                        string num;
                        for (int k = 0; i != ' ' && i < instruction.length() && isnumber(instruction[i]); i++, k++) {
                            tok.type = token::TOKENS_DEC;
                            num.insert(k, 1, instruction[i]);
                        }
                        tok.value = (int)atoi(num.c_str());
                        toks.push_back(tok);
                    }

                }
                else {
                    string num;
                    for (int k = 0; i != ' ' && i < instruction.length() && isnumber(instruction[i]); i++, k++) {
                        tok.type = token::TOKENS_DEC;
                        num.insert(k, 1, instruction[i]);
                    }
                    tok.value = (int)atoi(num.c_str());
                    toks.push_back(tok);
                }
            }
            else if (isalpha(instruction[i])) {
                for (int k = 0; isalnum(instruction[i]); i++, k++) {
                    tok.ascii.insert(k, 1, instruction[i]);
                }
                tok.type = token::TOKENS_LABEL;
                toks.push_back(tok);
            }
        }
        tokens.push_back(toks);
    }
    
    return tokens;
}


vector<int> Assembler::assemble()
{
    vector<int> byte_code;
    
    vector<vector<token>> tokens = tokonise();

    int local_address = 0;
    
    map<string, int> labels; //labels that exist
    map<string, bool> existing_labels;  //bool to check whether label exists
    map<int, string> marked_address; //not yet defined label location
    
    for (int i = 0; i < tokens.size(); i++) {
        
        bool dests_filled = false;
        
        bool bracket_opened = false;
        
        bool load = false;
        bool store = false;
        
        char condtion = 0x0;
        char op_code = 0x0;
        bool immidiate = false;
        bool link = false;
        bool label = false;
        bool br = false; //break;
        
        vector<token> instruction_in = tokens[i];
        
        
        vector<int> destination_regs;
        vector<int> source_regs;
        
        
        for (int j = 0; j < instruction_in.size(); j++) {
            switch (instruction_in[j].type) {
                case token::TOKENS_LBRACK:
                    if (dests_filled) {
                        load = true;
                    }
                    else {
                        store = true;
                    }
                    bracket_opened = true;
                    break;
                case token::TOKENS_RBRACK:
                    bracket_opened = false;
                    break;
                case token::TOKENS_REG:
                    if (!dests_filled) {
                        destination_regs.push_back(instruction_in[j].reg);
                    }
                    else if (dests_filled) {
                        source_regs.push_back(instruction_in[j].reg);
                    }
                    break;
                case token::TOKENS_MOVE:
                    dests_filled = true;
                    if (load) {
                        op_code = 0xD;
                    }
                    else if (store) {
                        op_code = 0xE;
                    }
                    else {
                        op_code = 0x0;
                    }
                    break;
                case token::TOKENS_CMP:
                    dests_filled = true;
                    op_code = 0xB;
                    break;
                case token::TOKENS_COMMA:
                    break;
                case token::TOKENS_ADD:
                    op_code = 0x1;
                    break;
                case token::TOKENS_MUL:
                    op_code = 0x3;
                    break;
                case token::TOKENS_SUB:
                    op_code = 0x2;
                    break;
                case token::TOKENS_DIV:
                    op_code = 0x4;
                    break;
                case token::TOKENS_AND:
                    op_code = 0x5;
                    break;
                case token::TOKENS_OR:
                    op_code = 0x6;
                    break;
                case token::TOKENS_NOT:
                    op_code = 0x7;
                    break;
                case token::TOKENS_XOR:
                    op_code = 0x8;
                    break;
                case token::TOKENS_LSHIFT:
                    op_code = 0xA;
                    break;
                case token::TOKENS_RSHIFT:
                    op_code = 0x9;
                    break;
                case token::TOKENS_BREAK:
                    br = true;
                    op_code = 0xC;
                    break;
                case token::TOKENS_CONDITION:
                    break;
                case token::TOKENS_AL:
                    condtion = 0x0;
                    break;
                case token::TOKENS_EQ:
                    condtion = 0x1;
                    break;
                case token::TOKENS_NE:
                    condtion = 0x2;
                    break;
                case token::TOKENS_GT:
                    condtion = 0x3;
                    break;
                case token::TOKENS_LT:
                    condtion = 0x4;
                    break;
                case token::TOKENS_GE:
                    condtion = 0x5;
                    break;
                case token::TOKENS_LE:
                    condtion = 0x6;
                    break;
                case token::TOKENS_LQUOTE:
                    break;
                case token::TOKENS_RQUOTE:
                    break;
                case token::TOKENS_ASCII:
                    
                    break;
                case token::TOKENS_DEC:
                    if (dests_filled) {
                        immidiate = true;
                        if (instruction_in[j].value < 256 && instruction_in[j].value >= 0) {

                            source_regs.push_back((instruction_in[j].value & (0xF << 4)) >> 4);
                            source_regs.push_back(instruction_in[j].value & 0xF);
                        }
                        else if (op_code == 0x0) {
                            byte_code.push_back(0x101FF10);      //PC+2
                            byte_code.push_back(instruction_in[j].value);
                            //0xD01XFF //PC-1
                            source_regs.push_back(0xF);
                            source_regs.push_back(0xF);
                            op_code = 0xD;
                            local_address+=2;
                        }
                    }
                    else {
                        byte_code.push_back(0x101FF20);      //PC+1
                        byte_code.push_back(instruction_in[j].value);
                        continue;
                    }
                    break;
                case token::TOKENS_HEX:
                    if (dests_filled) {
                        immidiate = true;
                        if (instruction_in[j].value < 256 && instruction_in[j].value >= 0) {
                            source_regs.push_back((instruction_in[j].value & (0xF << 4)) >> 4);
                            source_regs.push_back(instruction_in[j].value & 0xF);
                        }
                        else if (op_code == 0x0) {
                            byte_code.push_back(0x101FF10);      //PC+1
                            byte_code.push_back(instruction_in[j].value);
                            //0xD01XFF //PC-1
                            source_regs.push_back(0xF);
                            source_regs.push_back(0xF);
                            op_code = 0xD;
                            local_address+=2;
                        }
                    }
                    else {
                        byte_code.push_back(0x101FF10);      //PC+1
                        byte_code.push_back(instruction_in[j].value);
                        continue;
                    }
                    break;
                case token::TOKENS_BIN:
                    if (dests_filled) {
                        immidiate = true;
                        if (instruction_in[j].value < 256 && instruction_in[j].value >= 0) {
                            source_regs.push_back((instruction_in[j].value & (0xF << 4)) >> 4);
                            source_regs.push_back(instruction_in[j].value & 0xF);
                        }
                        else if (op_code == 0x0) {
                            byte_code.push_back(0x101FF10);      //PC+1
                            byte_code.push_back(instruction_in[j].value);
                            //0xD01XFF //PC-1
                            source_regs.push_back(0xF);
                            source_regs.push_back(0xF);
                            op_code = 0xD;
                            local_address+=2;
                        }
                    }
                    else {
                        byte_code.push_back(0x101FF10);      //PC+1
                        byte_code.push_back(instruction_in[j].value);
                        continue;
                    }
                    break;
                case token::TOKENS_LABEL:
                    if (br) {
                        int branch_to = 0;
                        if (existing_labels[instruction_in[j].ascii] == true) {
                            branch_to = labels[instruction_in[j].ascii];
                            int branch_offset = branch_to - local_address;
                            if (branch_offset < 2047 && branch_offset > -2048) {
                                immidiate = true;
                                if (branch_offset < 0) {
                                    branch_offset = 4096 + branch_offset;
                                }
                                destination_regs.push_back((branch_offset & 0xF << 8) >> 8);
                                source_regs.push_back((branch_offset & 0xF << 4) >> 4);
                                source_regs.push_back(branch_offset & 0xF);
                            }
                            else {
                                byte_code.push_back(0x101FF10);      //PC+1
                                if (branch_offset < 0) {
                                    branch_offset = 4096 + branch_offset;
                                }
                                byte_code.push_back(branch_offset);
                                //0xD01XFF //PC-1
                                destination_regs.push_back(0);
                                source_regs.push_back(0);
                                source_regs.push_back(0);
                                local_address+=2;
                            }
                        }
                        else {
                            byte_code.push_back(0x101FF10);      //PC+1
                            marked_address[local_address] = instruction_in[j].ascii;
                        }
                    }
                    else {
                        labels[instruction_in[j].ascii] = local_address;
                        existing_labels[instruction_in[j].ascii] = true;
                        
                        //loop through marked addresses, if address has been marked with the new label put local address at that marked location
                        for(auto iterator = marked_address.begin(); iterator != marked_address.end(); iterator++) {
                            if (iterator->second == instruction_in[j].ascii) {
                                byte_code[iterator->first] = labels[instruction_in[j].ascii];
                            }
                        }
                        label = true;
                    }
                    break;
                case token::TOKENS_LINK:
                    link = true;
                default:
                    break;
            }
        }
        if (label) {
            label = false;
            continue;
        }
        vector<Instruction> instructions;
        if (destination_regs.size() > 1) {
            for (int k = 0; k < destination_regs.size(); k++) {
                Instruction instruction;
                instruction.opcode = 0xD;
                instruction.option = condtion;
                instruction.I = immidiate;
                instruction.destination = destination_regs[k];
                instruction.source1 = source_regs[0];
                instruction.source2 = 0;
                if (instruction.source1 == 0xD) {
                    Instruction SP_decrement;
                    SP_decrement.opcode = 0x2;
                    SP_decrement.option = 0x0;
                    SP_decrement.I = 0x1;
                    SP_decrement.destination = 0xD;
                    SP_decrement.source1 = 0xD;
                    SP_decrement.source2 = 0x1;
                    instructions.push_back(SP_decrement);
                }
                instructions.push_back(instruction);
            }
        }
        else if (source_regs.size() > 2 && op_code != 0xE) {
            for (int k = 0; k < source_regs.size(); k++) {
                Instruction instruction;
                instruction.opcode = op_code;
                instruction.option = condtion;
                instruction.I = immidiate;
                instruction.destination = destination_regs[0];
                instruction.source1 = source_regs[k];
                instructions.push_back(instruction);
            }
        }
        else if (op_code == 0xE) {
            for (int k = 0; k < source_regs.size(); k++) {
                Instruction instruction;
                instruction.opcode = op_code;
                instruction.option = condtion;
                instruction.I = immidiate;
                instruction.destination = destination_regs[0];
                instruction.source1 = source_regs[k];
                instruction.source2 = 0;
                instructions.push_back(instruction);
                if (instruction.destination == 0xD) {
                    Instruction SP_increment;
                    SP_increment.opcode = 0x1;
                    SP_increment.option = 0x0;
                    SP_increment.I = 0x1;
                    SP_increment.destination = 0xD;
                    SP_increment.source1 = 0xD;
                    SP_increment.source2 = 1;
                    instructions.push_back(SP_increment);
                }
            }
        }
        else {
            Instruction instruction;
            instruction.opcode = op_code;
            instruction.option = condtion;
            instruction.I = immidiate;
            instruction.destination = destination_regs[0];
            instruction.source1 = source_regs[0];
            if (source_regs.size() == 1) {
                instruction.source2 = 0;
            }
            else {
                instruction.source2 = source_regs[1];
            }
            instructions.push_back(instruction);
        }
        for (int k = 0; k < instructions.size(); k++) {
            int instruct = 0;
            instruct = instructions[k].opcode;
            instruct = (instruct << 4) + instructions[k].option;
            instruct = (instruct << 4) + instructions[k].I;
            instruct = (instruct << 4) + instructions[k].destination;
            instruct = (instruct << 4) + instructions[k].source1;
            instruct = (instruct << 4) + instructions[k].source2;
            instruct = (instruct << 4) + link;
            
            byte_code.push_back(instruct);
            local_address++;
        }
        
    }
    
    
    
    return byte_code;
}
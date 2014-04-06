//
//  Intepreter.cpp
//  Virtual Machine
//
//  Created by Seán Hargadon on 04/04/2014.
//  Copyright (c) 2014 Seán Hargadon. All rights reserved.
//

#include "Intepreter.h"

Intepreter::Intepreter(vector<int> byte_code, int memory_size)
{
    this->memory = vector<int>(memory_size);
    for (int i = 0; i < byte_code.size(); i++) {
        this->memory[i] = byte_code[i];
    }
    this->PC = 0;
}
Intepreter::Intepreter(vector<int> byte_code, int PC_init, int memory_size)
{
    this->memory = vector<int>(memory_size);
    for (int i = 0; i < byte_code.size(); i++) {
        this->memory[i] = byte_code[i];
    }
    this->PC = PC_init;
}

void Intepreter::evaluate()
{
    int previous_PC1 = PC-2;
    int previous_PC2 = PC-1;
    while (abs(PC-previous_PC1) > 1) {
        previous_PC1 = previous_PC2;
        previous_PC2 = PC;
        step();
        print();
        sleep(1);
    }
}

int& Intepreter::get_register(char reg)
{
    switch (reg) {
        case 0:
            return register_0;
            break;
        case 1:
            return register_1;
            break;
        case 2:
            return register_2;
            break;
        case 3:
            return register_3;
            break;
        case 4:
            return register_4;
            break;
        case 5:
            return register_5;
            break;
        case 6:
            return register_6;
            break;
        case 7:
            return register_7;
            break;
        case 8:
            return register_8;
            break;
        case 9:
            return register_9;
            break;
        case 10:
            return register_10;
            break;
        case 11:
            return register_11;
            break;
        case 12:
            return register_12;
            break;
        case 13:
            return SP;
            break;
        case 14:
            return LR;
            break;
        case 15:
            return PC;
            break;
        default:
            return register_0;
            break;
    }
}


void Intepreter::op_mov(int destination, int source1, int source2, bool immidiate)
{
    if (immidiate) {
        int value = source1 & 0xF << 4;
        value += source2;
        get_register(destination) = value;
    }
    else {
        get_register(destination) = get_register(source1);
    }
    if (get_register(destination) == 0) {
        this->NZCV = this->NZCV | 0x4;
    }
    if (get_register(destination) > 7) {
        this->NZCV = this->NZCV | 0x8;
    }
}

void Intepreter::op_add(int destination, int source1, int source2, bool immidiate)
{
    int temp = 0;
    if (immidiate) {
        temp = source2;
    }
    else {
        temp = get_register(source2);
    }
    get_register(destination) = get_register(source1) + temp;

    if (get_register(destination) == 0) {
        this->NZCV = this->NZCV | 0x4;
    }
    if (get_register(destination) > 7) {
        this->NZCV = this->NZCV | 0x8;
    }
    if (get_register(source1) > INT_MAX - temp) {
        this->NZCV = this->NZCV | 0x2;
    }
    if ( (get_register(source1) > 0 && temp > 0 && get_register(destination) < 0 ) || (get_register(source1) < 0 && temp < 0 && get_register(destination) > 0 )) {
        this->NZCV = this->NZCV | 0x1;
    }

}
void Intepreter::op_sub(int destination, int source1, int source2, bool immidiate)
{
    int temp = 0;
    if (immidiate) {
        temp = source2;
    }
    else {
        temp = get_register(source2);
    }
    get_register(destination) = get_register(source1) - temp;
    
    if (get_register(destination) == 0) {
        this->NZCV = this->NZCV | 0x4;
    }
    if (get_register(destination) > 7) {
        this->NZCV = this->NZCV | 0x8;
    }
    if (get_register(source1) > INT_MAX - temp) {
        this->NZCV = this->NZCV | 0x2;
    }
    if ( (get_register(source1) > 0 && temp > 0 && get_register(destination) < 0 ) || (get_register(source1) < 0 && temp < 0 && get_register(destination) > 0 )) {
        this->NZCV = this->NZCV | 0x1;
    }
}
void Intepreter::op_mul(int destination, int source1, int source2, bool immidiate)
{
    int temp = 0;
    if (immidiate) {
        temp = source2;
    }
    else {
        temp = get_register(source2);
    }
    get_register(destination) = get_register(source1) * temp;
    
    if (get_register(destination) == 0) {
        this->NZCV = this->NZCV | 0x4;
    }
    if (get_register(destination) > 7) {
        this->NZCV = this->NZCV | 0x8;
    }
    if (get_register(source1) > INT_MAX - temp) {
        this->NZCV = this->NZCV | 0x2;
    }
    if ( (get_register(source1) > 0 && temp > 0 && get_register(destination) < 0 ) || (get_register(source1) < 0 && temp < 0 && get_register(destination) > 0 )) {
        this->NZCV = this->NZCV | 0x1;
    }
}
void Intepreter::op_div(int destination, int source1, int source2, bool immidiate)
{
    int temp = 0;
    if (immidiate) {
        temp = source2;
    }
    else {
        temp = get_register(source2);
    }
    get_register(destination) = get_register(source1) / temp;
    
    if (get_register(destination) == 0) {
        this->NZCV = this->NZCV | 0x4;
    }
    if (get_register(destination) > 7) {
        this->NZCV = this->NZCV | 0x8;
    }
    if (get_register(source1) > INT_MAX - temp) {
        this->NZCV = this->NZCV | 0x2;
    }
    if ( (get_register(source1) > 0 && temp > 0 && get_register(destination) < 0 ) || (get_register(source1) < 0 && temp < 0 && get_register(destination) > 0 )) {
        this->NZCV = this->NZCV | 0x1;
    }

}
void Intepreter::op_and(int destination, int source1, int source2, bool immidiate)
{
    int temp = 0;
    if (immidiate) {
        temp = source2;
    }
    else {
        temp = get_register(source2);
    }
    get_register(destination) = get_register(source1) & temp;
    
    if (get_register(destination) == 0) {
        this->NZCV = this->NZCV | 0x4;
    }
    if (get_register(destination) > 7) {
        this->NZCV = this->NZCV | 0x8;
    }
    if (get_register(source1) > INT_MAX - temp) {
        this->NZCV = this->NZCV | 0x2;
    }
    if ( (get_register(source1) > 0 && temp > 0 && get_register(destination) < 0 ) || (get_register(source1) < 0 && temp < 0 && get_register(destination) > 0 )) {
        this->NZCV = this->NZCV | 0x1;
    }
}
void Intepreter::op_or(int destination, int source1, int source2, bool immidiate)
{
    int temp = 0;
    if (immidiate) {
        temp = source2;
    }
    else {
        temp = get_register(source2);
    }
    get_register(destination) = get_register(source1) | temp;
    
    if (get_register(destination) == 0) {
        this->NZCV = this->NZCV | 0x4;
    }
    if (get_register(destination) > 7) {
        this->NZCV = this->NZCV | 0x8;
    }
    if (get_register(source1) > INT_MAX - temp) {
        this->NZCV = this->NZCV | 0x2;
    }
    if ( (get_register(source1) > 0 && temp > 0 && get_register(destination) < 0 ) || (get_register(source1) < 0 && temp < 0 && get_register(destination) > 0 )) {
        this->NZCV = this->NZCV | 0x1;
    }
}
void Intepreter::op_not(int destination, int source, bool immidiate)
{
    int temp = 0;
    if (immidiate) {
        temp = source;
    }
    else {
        temp = get_register(source);
    }
    get_register(destination) =  ~temp;
    
    if (get_register(destination) == 0) {
        this->NZCV = this->NZCV | 0x4;
    }
    if (get_register(destination) > 7) {
        this->NZCV = this->NZCV | 0x8;
    }
}
void Intepreter::op_xor(int destination, int source1, int source2, bool immidiate)
{
    int temp = 0;
    if (immidiate) {
        temp = source2;
    }
    else {
        temp = get_register(source2);
    }
    get_register(destination) = get_register(source1) ^ temp;
    
    if (get_register(destination) == 0) {
        this->NZCV = this->NZCV | 0x4;
    }
    if (get_register(destination) > 7) {
        this->NZCV = this->NZCV | 0x8;
    }
    if (get_register(source1) > INT_MAX - temp) {
        this->NZCV = this->NZCV | 0x2;
    }
    if ( (get_register(source1) > 0 && temp > 0 && get_register(destination) < 0 ) || (get_register(source1) < 0 && temp < 0 && get_register(destination) > 0 )) {
        this->NZCV = this->NZCV | 0x1;
    }
}
void Intepreter::op_rshift(int destination, int source1, int source2, bool immidiate)
{
    int temp = 0;
    if (immidiate) {
        temp = source2;
    }
    else {
        temp = get_register(source2);
    }
    get_register(destination) = get_register(source1) >> temp;
    
    if (get_register(destination) == 0) {
        this->NZCV = this->NZCV | 0x4;
    }
    if (get_register(destination) > 7) {
        this->NZCV = this->NZCV | 0x8;
    }
    if (get_register(source1) > INT_MAX - temp) {
        this->NZCV = this->NZCV | 0x2;
    }
    if ( (get_register(source1) > 0 && temp > 0 && get_register(destination) < 0 ) || (get_register(source1) < 0 && temp < 0 && get_register(destination) > 0 )) {
        this->NZCV = this->NZCV | 0x1;
    }
}
void Intepreter::op_lshift(int destination, int source1, int source2, bool immidiate)
{
    int temp = 0;
    if (immidiate) {
        temp = source2;
    }
    else {
        temp = get_register(source2);
    }
    get_register(destination) = get_register(source1) << temp;
    
    if (get_register(destination) == 0) {
        this->NZCV = this->NZCV | 0x4;
    }
    if (get_register(destination) > 7) {
        this->NZCV = this->NZCV | 0x8;
    }
    if (get_register(source1) > INT_MAX - temp) {
        this->NZCV = this->NZCV | 0x2;
    }
    if ( (get_register(source1) > 0 && temp > 0 && get_register(destination) < 0 ) || (get_register(source1) < 0 && temp < 0 && get_register(destination) > 0 )) {
        this->NZCV = this->NZCV | 0x1;
    }
}
void Intepreter::op_cmp(int destination, int source1, int source2, bool immidiate)
{
    int r = 0;
    int temp = 0;
    if (immidiate) {
        temp += source1 << 4;
        temp += source2;
    }
    else {
        temp = get_register(source2);
    }
    r = get_register(destination) - temp;
    if (r == 0) {
        this->NZCV = this->NZCV | 0x4;
    }
    if (r < 0) {
        this->NZCV = this->NZCV | 0x8;
    }
    if (get_register(destination) < temp) {
        this->NZCV = this->NZCV | 0x2;
    }
    if ( (get_register(destination) > 0 && temp > 0 && r < 0 ) || (get_register(destination) < 0 && temp < 0 && r > 0 )) {
        this->NZCV = this->NZCV | 0x1;
    }
}
void Intepreter::op_break(int destination, int source1, int source2, bool immidiate)
{
    if (immidiate) {
        int branch_offset = destination << 8;
        branch_offset += source1 << 4;
        branch_offset += source2;
        if (branch_offset > 2047) {
            branch_offset = -4096 + branch_offset;
        }
        this->PC += branch_offset - 1;
    }
    else {
        this->PC += this->memory[this->PC-1] - 1;
    }
}
void Intepreter::op_load(int destination, int source1, int source2, bool immidiate)
{
    if (immidiate) {
        get_register(destination) = this->memory[this->PC-1];
    }
    else {
        get_register(destination) = this->memory[get_register(source1)];
    }
 
}
void Intepreter::op_store(int destination, int source1, int source2, bool immidiate)
{
    if (immidiate) {
        if (source1 > 7) {
            source1 = (-16 + source1);
        }
        this->memory[get_register(destination)] = source1;
    }
    else {
        this->memory[get_register(destination)] = get_register(source1);
    }
}

void Intepreter::step()
{
    int instruction = this->memory[PC];
    
    Instruction instruction_register;
    int mask = 0xF;
    instruction_register.link = instruction & mask;
    instruction = instruction >> 4;
    instruction_register.source2 = instruction & mask;
    instruction = instruction >> 4;
    instruction_register.source1 = instruction & mask;
    instruction = instruction >> 4;
    instruction_register.destination = instruction & mask;
    instruction = instruction >> 4;
    instruction_register.I = instruction & mask;
    instruction = instruction >> 4;
    instruction_register.option = instruction & mask;
    instruction = instruction >> 4;
    instruction_register.opcode = instruction & mask;

    
    switch (instruction_register.opcode) {
        case OPCODE_MOV:
            switch (instruction_register.option) {
                case CONDITION_AL:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                case CONDITION_EQ:
                    if (this->NZCV & 0x4) {
                        op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    }
                    break;
                case CONDITION_NE:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                default:
                    break;
            }
            break;
        case OPCODE_ADD:
            switch (instruction_register.option) {
                case CONDITION_AL:
                    op_add(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                case CONDITION_EQ:
                    if (this->NZCV & 0x4) {
                        op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    }
                    break;
                case CONDITION_NE:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                default:
                    break;
            }
            break;
        case OPCODE_SUB:
            switch (instruction_register.option) {
                case CONDITION_AL:
                    op_sub(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                case CONDITION_EQ:
                    if (this->NZCV & 0x4) {
                        op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    }
                    break;
                case CONDITION_NE:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                default:
                    break;
            }
            break;
        case OPCODE_MUL:
            switch (instruction_register.option) {
                case CONDITION_AL:
                    op_mul(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                case CONDITION_EQ:
                    if (this->NZCV & 0x4) {
                        op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    }
                    break;
                case CONDITION_NE:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                default:
                    break;
            }
            break;
        case OPCODE_DIV:
            switch (instruction_register.option) {
                case CONDITION_AL:
                    op_div(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                case CONDITION_EQ:
                    if (this->NZCV & 0x4) {
                        op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    }
                    break;
                case CONDITION_NE:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                default:
                    break;
            }
            break;
        case OPCODE_AND:
            switch (instruction_register.option) {
                case CONDITION_AL:
                    op_and(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                case CONDITION_EQ:
                    if (this->NZCV & 0x4) {
                        op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    }
                    break;
                case CONDITION_NE:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                default:
                    break;
            }
            break;
        case OPCODE_OR:
            switch (instruction_register.option) {
                case CONDITION_AL:
                    op_or(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                case CONDITION_EQ:
                    if (this->NZCV & 0x4) {
                        op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    }
                    break;
                case CONDITION_NE:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                default:
                    break;
            }
            break;
        case OPCODE_NOT:
            switch (instruction_register.option) {
                case CONDITION_AL:
                    op_not(instruction_register.destination, instruction_register.source1, instruction_register.I);
                    break;
                case CONDITION_EQ:
                    if (this->NZCV & 0x4) {
                        op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    }
                    break;
                case CONDITION_NE:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                default:
                    break;
            }
            break;
        case OPCODE_XOR:
            switch (instruction_register.option) {
                case CONDITION_AL:
                    op_xor(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                case CONDITION_EQ:
                    if (this->NZCV & 0x4) {
                        op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    }
                    break;
                case CONDITION_NE:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                default:
                    break;
            }
            break;
        case OPCODE_RSHIFT:
            switch (instruction_register.option) {
                case CONDITION_AL:
                    op_rshift(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                case CONDITION_EQ:
                    if (this->NZCV & 0x4) {
                        op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    }
                    break;
                case CONDITION_NE:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                default:
                    break;
            }
            break;
        case OPCODE_LSHIFT:
            switch (instruction_register.option) {
                case CONDITION_AL:
                    op_lshift(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                case CONDITION_EQ:
                    if (this->NZCV & 0x4) {
                        op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    }
                    break;
                case CONDITION_NE:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                default:
                    break;
            }
            break;
        case OPCODE_CMP:
            switch (instruction_register.option) {
                case CONDITION_AL:
                    op_cmp(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                case CONDITION_EQ:
                    if (this->NZCV & 0x4) {
                        op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    }
                    break;
                case CONDITION_NE:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                default:
                    break;
            }
            break;
        case OPCODE_BREAK:
            switch (instruction_register.option) {
                case CONDITION_AL:
                    op_break(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                case CONDITION_EQ:
                    if (this->NZCV & 0x4) {
                        op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    }
                    break;
                case CONDITION_NE:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                default:
                    break;
            }
            break;
        case OPCODE_LOAD:
            switch (instruction_register.option) {
                case CONDITION_AL:
                    op_load(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                case CONDITION_EQ:
                    if (this->NZCV & 0x4) {
                        op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    }
                    break;
                case CONDITION_NE:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                default:
                    break;
            }
            break;
        case OPCODE_STORE:
            switch (instruction_register.option) {
                case CONDITION_AL:
                    op_store(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                case CONDITION_EQ:
                    if (this->NZCV & 0x4) {
                        op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    }
                    break;
                case CONDITION_NE:
                    op_mov(instruction_register.destination, instruction_register.source1, instruction_register.source2, instruction_register.I);
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }
    this->PC++;
}

void Intepreter::print()
{
    cout << "Registers" << "           " << "Address" << "         " << "Memory" << endl;
    for (int i = (PC-8 < 0 ? 0 : PC - 8), j = 0; i < (PC-8 < 0 ? PC+8 - (PC-8) : PC+8); i++, j++) {
        if (j == 13) {
            cout << "SP" << " :" << "0x"<< setfill('0') << setw(8) << std::hex << get_register(j);
        }
        else if (j == 14) {
            cout << "LR" << " :" << "0x"<< setfill('0') << setw(8) << std::hex << get_register(j);
        }
        else if (j == 15) {
            cout << "PC" << " :" << "0x"<< setfill('0') << setw(8) << std::hex << get_register(j);
        }
        else if (j < 10){
            cout << "R" << std::dec << j << " :" << "0x"<< setfill('0') << setw(8) << std::hex << get_register(j);
        }
        else {
            cout << "R" << std::dec << j << ":" << "0x"<< setfill('0') << setw(8) << std::hex << get_register(j);
        }
        
        if (i == this->PC) {
            cout << "  PC->" << "0x"<< setfill('0') << setw(8) << std::hex << i;
        }
        else {
            cout << "      " << "0x"<< setfill('0') << setw(8) << std::hex << i;
        }
        cout << "      " << "0x"<< setfill('0') << setw(8) << this->memory[i] << endl;
    }
    cout << endl;
    
}








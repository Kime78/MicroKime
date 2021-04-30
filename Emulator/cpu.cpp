#include "cpu.h"
#include <iostream>

void CPU::emulate_cycle()
{
    uint32_t opcode = mem->read(pc);
    uint8_t instr = opcode & 0b1111'1111;
    //std::cout << std::hex << pc << ": " << opcode << "\n";
    switch (instr)
    {
    case 0x1: //jmp
    {
        int32_t target = opcode >> 8;
        if (target >> 23)
            target = target | 0xFF000000;
        pc += target - 4;
        break;
    }
    case 0x2: //jmp to reg
    {
        uint32_t target = opcode >> 12;
        uint8_t reg = (opcode >> 8) & 0b1111;
        pc += target + reg - 4;
        break;
    }
    case 0x3: //mov to imm
    {
        uint32_t imm = opcode >> 12;
        uint8_t reg = (opcode >> 8) & 0b1111;
        regs[reg] = imm;
        break;
    }
    case 0x5:
    {
        uint8_t reg1 = (opcode >> 8) & 0b1111;
        uint8_t reg2 = (opcode >> 12) & 0b1111;
        regs[reg1] += regs[reg2];
        break;
    }
    case 0xA: //wrt reg
    {
        uint8_t reg2 = (opcode >> 8) & 0b1111;
        uint8_t reg1 = (opcode >> 12) & 0b1111;
        uint8_t imm = (opcode >> 16);
        //std::cout << std::hex << "[" << regs[reg1] << "] = " << regs[reg2] << '\n';
        mem->write(regs[reg1], regs[reg2]);
        break;
    }
    case 0xC: //add imm
    {
        uint32_t imm = opcode >> 12;
        uint8_t reg = (opcode >> 8) & 0b1111;
        regs[reg] += imm;
        break;
    }
    case 0x11: //lsh imm
    {
        uint32_t imm = opcode >> 12;
        uint8_t reg = (opcode >> 8) & 0b1111;
        regs[reg] <<= imm;
        break;
    }
    case 0x1E: //cond
    {
        uint8_t reg2 = (opcode >> 8) & 0b1111;
        uint8_t reg1 = (opcode >> 12) & 0b1111;
        uint8_t cond = (opcode >> 16) & 0b1111;
        switch (cond)
        {
        case 0:
            if (regs[reg1] == regs[reg2])
                pc += 4;
            break;
        case 1:
            if (regs[reg1] != regs[reg2])
                pc += 4;
            break;
        case 2:
            if (regs[reg1] < regs[reg2])
                pc += 4;
            break;
        case 3:
            if (regs[reg1] > regs[reg2])
                pc += 4;
            break;
        case 4:
            if (regs[reg1] <= regs[reg2])
                pc += 4;
            break;
        case 5:
            if (regs[reg1] >= regs[reg2])
                pc += 4;
            break;
        case 6:
            if (regs[reg1] == 0)
                pc += 4;
            break;
        case 7:
            if (regs[reg1] != 0)
                pc += 4;
            break;
        case 8:
            break;
        default:
            pc += 4;
            break;
        }
        break;
    }

    default:
        std::cout << "Intruction: " << std::hex << (int)instr;
        exit(0);
        break;
    }
}

CPU::CPU()
{
    mem = std::make_unique<Memory>();
    pc = 0x602000;
    for (int i = 0; i < 16; i++)
        regs[i] = 0;
}
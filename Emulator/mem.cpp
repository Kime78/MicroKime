#include "mem.h"
#include <fstream>

void Memory::write(uint32_t addr, uint32_t val)
{
    uint8_t nibble1, nibble2, nibble3, nibble4;
    nibble4 = (val >> 24) & 0b1111'1111;
    nibble3 = (val >> 16) & 0b1111'1111;
    nibble2 = (val >> 8) & 0b1111'1111;
    nibble1 = val & 0b1111'1111;

    if (addr >= 0x000000 && addr <= 0x3FFFF)
    {
        ram[addr] = nibble4;
        ram[addr + 1] = nibble3;
        ram[addr + 2] = nibble2;
        ram[addr + 3] = nibble1;
    }

    if (addr >= 0x40000 && addr <= 0x5FFFFF)
    {
        vram[addr - 0x40000 + 1] = nibble4;
        vram[addr - 0x40000 + 2] = nibble3;
        vram[addr - 0x40000 + 3] = nibble2;
        vram[addr - 0x40000] = nibble1;
    }

    if (addr >= 0x600000 && addr <= 0x600FFF)
    {
        sprite[addr - 0x600000 + 1] = nibble4;
        sprite[addr - 0x600000 + 2] = nibble3;
        sprite[addr - 0x600000 + 3] = nibble2;
        sprite[addr - 0x600000] = nibble1;
    }

    if (addr >= 0x601000 && addr <= 0x601FFF)
    {
        io_regs[addr - 0x601000 + 3] = nibble4;
        io_regs[addr - 0x601000 + 2] = nibble3;
        io_regs[addr - 0x601000 + 1] = nibble2;
        io_regs[addr - 0x601000] = nibble1;
    }
}

uint32_t Memory::read(uint32_t addr)
{
    if (addr >= 0x000000 && addr <= 0x3FFFFF)
    {
        return (uint32_t)(ram[addr]) << 24 | (uint32_t)(ram[addr + 1]) << 16 |
               (uint32_t)(ram[addr + 2]) << 8 | (uint32_t)(ram[addr + 3]);
    }

    if (addr >= 0x400000 && addr <= 0x5FFFFF)
    {
        return (uint32_t)(vram[addr - 0x0400000]) << 24 | (uint32_t)(vram[addr - 0x0400000 + 1]) << 16 |
               (uint32_t)(vram[addr - 0x0400000 + 2]) << 8 | (uint32_t)(vram[addr - 0x0400000 + 3]);
    }

    if (addr >= 0x600000 && addr <= 0x600FFF)
    {
        return (uint32_t)(sprite[addr - 0x600000]) << 24 | (uint32_t)(sprite[addr - 0x600000 + 1]) << 16 |
               (uint32_t)(sprite[addr - 0x600000 + 2]) << 8 | (uint32_t)(sprite[addr - 0x600000 + 3]);
    }

    if (addr >= 0x601000 && addr <= 0x601FFF)
    {
        return (uint32_t)(io_regs[addr - 0x601000]) << 24 | (uint32_t)(io_regs[addr - 0x601000 + 1]) << 16 |
               (uint32_t)(io_regs[addr - 0x601000 + 2]) << 8 | (uint32_t)(io_regs[addr - 0x601000 + 3]);
    }
    else
    {
        return (uint32_t)(rom[addr - 0x602000]) << 24 | (uint32_t)(rom[addr - 0x602000 + 1]) << 16 |
               (uint32_t)(rom[addr - 0x602000 + 2]) << 8 | (uint32_t)(rom[addr - 0x602000 + 3]);
    }
}

Memory::Memory()
{
    std::string path = "/home/kime/Documents/coding/MicroKime/Emulator/build/test.bin";
    FILE *file = fopen(path.c_str(), "rb");
    int pos = 0;

    while (fread(&rom[pos], 1, 1, file))
    {
        //std::cout << std::hex << (int)Memory.rom[pos] << " ";
        pos++;
    }
}
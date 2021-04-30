#include <stdint.h>
#include <array>

class Memory
{
    std::array<uint8_t, 0x3FFFFF> ram;
    std::array<uint8_t, 0xFFF> sprite;
    std::array<uint8_t, 0xFFF> io_regs;
    std::array<uint8_t, 0x3FFFFF> rom;

public:
    Memory();
    ~Memory() = default;
    uint32_t read(uint32_t addr);
    void write(uint32_t addr, uint32_t val);
    std::array<uint8_t, 0x1FFFFF> vram;
};
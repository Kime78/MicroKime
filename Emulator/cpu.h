#include <memory>
#include "mem.h"
class CPU
{
    std::array<uint32_t, 16> regs;

public:
    std::unique_ptr<Memory> mem;
    uint32_t pc;
    void emulate_cycle();
    CPU();
    ~CPU() = default;
};
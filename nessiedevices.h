#include "nessiedefs.h"
#include "nessiemappers.h"
#include <vector>

namespace nessie
{
    template <int size_kb>
    class RAM
    {
        std::vector<nessie::Data> store;

    public:
        const nessie::Address MAX_ADDRESS = size_kb * 1024;
        void reset()
        {
            fill(store.begin(), store.end(), 0);
        }
        void write(nessie::Data udata, nessie::Address uaddr)
        {
            store[uaddr] = udata;
        }
        nessie::Data read(nessie::Address uaddr)
        {
            return store[uaddr];
        }
    };

    class System
    {
        RAM<2> wram;

    public:
        System(nessie::ConsoleType uctype)
        {
        }

        void load()
        {
        }
    };

    class CART
    {
    };

    class CPUBUS
    {
    public:
        CPUBUS(CART ucart)
        {
        }

        nessie::Data read(nessie::Address uaddr)
        {
            if (uaddr <= 0x1FFF)
            {
                // return wram.read(uaddr % 0x800);
            }
            else if (uaddr >= 0x2000 && uaddr <= 0x3FFF)
            {
                // return ppu.read(0x2000 + (uaddr % 0x0008));
            }
            else if (uaddr >= 0x4000 && uaddr <= 0x4017)
            {
                // read from controller
            }
            else if (uaddr >= 0x6000 && uaddr <= 0x7FFF)
            {
                // prg ram
            }
            else if (uaddr >= 0x8000 && uaddr <= 0xFFFF)
            {
                // connected to mapper
            }
        }

        void write(nessie::Data udata, nessie::Address uaddr)
        {
            if (uaddr <= 0x1FFF)
            {
                // return wram.read(uaddr % 0x800);
            }
            else if (uaddr >= 0x2000 && uaddr <= 0x3FFF)
            {
                // return ppu.read(0x2000 + (uaddr % 0x0008));
            }
            else if (uaddr >= 0x4000 && uaddr <= 0x4017)
            {
                // read from controller
            }
            else if (uaddr >= 0x6000 && uaddr <= 0x7FFF)
            {
                // prg ram
            }
            else if (uaddr >= 0x8000 && uaddr <= 0xFFFF)
            {
                // connected to mapper
            }
        }
    };

    class CPU
    {
        // Registers
        nessie::Byte A, X, Y, SP, PSR;
        nessie::Word PC;

        // Flag modifiers
        enum STATUSFLAG
        {
            C = 0b00000001,
            Z = 0b00000010,
            I = 0b00000100,
            D = 0b00001000,
            B = 0b00010000,
            U = 0b00100000,
            V = 0b01000000,
            N = 0b10000000
        };

        //
        const int lookup[4] = { 1,2,3,4 };// = {{0x00,"BRK",ADDRESSINGMODE::IMP,0,3}};

        // Operands
        nessie::Byte immopd;  // Used in imm addressing
        nessie::Byte relvec;  // Used in rel addressing
        nessie::Byte zpgaddr; // Used in zpg, zpx and zpy addressing
        nessie::Word absaddr; // Used in abs abx aby ind addressing
        nessie::Byte indaddr; // Used in xin and iny addressing

        //
        CPUBUS* bus;

        CPU(CPUBUS& ubus)
        {
            bus = &ubus;
        }

        Instruction currentinstruction;

        void step()
        {
            currentinstruction = lookup[readcycle(PC)]; // Cycle 1
            // Execute addressing;
        }

        void IMP(Instruction uins)
        {

        }

        nessie::Data readcycle(nessie::Address uaddr)
        {
            return bus->read(uaddr);
        }

        void writecycle(nessie::Data udata, nessie::Address uaddr)
        {
            bus->write(udata, uaddr);
        }

        // Instructions
        void setflag(CPU::STATUSFLAG flag)
        {
            PSR |= flag;
        }

        void clearflag(CPU::STATUSFLAG flag)
        {
            PSR = ~PSR;
            PSR |= flag;
            PSR = ~PSR;
        }

        // Flag instructions
        void sec()
        {
            setflag(STATUSFLAG::C);
        }
    };

    class APU
    {
        std::vector<nessie::HardwareRegister> registers = {
            {} };
    };

    class Controller
    {
        std::vector<nessie::Key> keystate = {
            {KEY::A, 0},
            {KEY::B, 0},
            {KEY::SELECT, 0},
            {KEY::START, 0},
            {KEY::UP, 0},
            {KEY::DOWN, 0},
            {KEY::LEFT, 0},
            {KEY::RIGHT, 0} };

    public:
        void setkeystate(nessie::Byte ukey, bool pressed)
        {
            keystate[ukey].state = pressed;
        }
    };

    class PPUBUS
    {
    };

    class PPU
    {
    public:
        std::vector<nessie::HardwareRegister> registers = {
            {"PPUCTRL", 0, 0x2000},
            {"PPUMASK", 0, 0x2001},
            {"PPUSTATUS", 0, 0x2002},
            {"OAMADDR", 0, 0x2003},
            {"OAMDATA", 0, 0x2004},
            {"PPUSCROLL", 0, 0x2005},
            {"PPUADDR", 0, 0x2006},
            {"PPUDATA", 0, 0x2007},
            {"OAMDMA", 0, 0x4014} };
    };

};
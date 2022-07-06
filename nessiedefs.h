#ifndef _NESSIEDEFS_
#define _NESSIEDEFS_
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
namespace nessie
{

    const uint8_t PRG_ROM_UNIT_KB = 16;
    const uint8_t CHR_ROM_UNIT_KB = 8;

    typedef uint8_t Data;
    typedef uint16_t Address;
    typedef uint8_t Byte;
    typedef uint16_t Word;

    typedef std::vector<nessie::Byte> Prgrom;
    typedef std::vector<nessie::Byte> Chrrom;

    enum REGION
    {
        NTSC,
        PAL,
        DENDY
    };

    enum SYSTEM
    {
        NES,
        FAMICOM
    };

    enum FORMAT
    {
        archiNES,
        iNES,
        NES2_0,
        FDS,
        NSF,
        NSF2_0
    };

    enum MIRRORINGTYPE
    {
        HORIZONTAL,
        VERTICAL,
        FOURSCREEN
    };

    typedef struct
    {
        Byte region;
        double clockrate;
    } ConsoleType;

    typedef struct
    {
        const std::string signature = "NES\x1A";
        Byte prgrombanks;
        Byte chrrombanks;
        Byte mirroringtype;
        bool hasprgram;
        bool hastrainer;
        bool mappernumber;
    } archiNESHeader;

    typedef struct
    {
        const std::string signature = "NES\x1A";
        Byte prgrombanks;
        Byte chrrombanks;
        Byte mirroringtype;
        bool hasprgram;
        bool hastrainer;
        bool mappernumber;
        bool isvsunisytem;
        bool isplaychoice10;
        Byte prgramsize;
        Byte tvsystem;
        bool hasbusconflicts;
    } iNESHeader;

    typedef struct
    {
        const std::string signature = "NES\x1A";
    } NES2_0Header;

    typedef struct
    {
        const std::string signature = "FDS\x1A";
    } FDSHeader;

    typedef struct
    {
        std::string name;
        Data value;
        Address address;
    } HardwareRegister;

    enum ADDRESSINGMODE
    {
        IMP,
        ACC,
        IMM,
        REL,
        ZPG,
        ZPX,
        ZPY,
        ABS,
        ABX,
        ABY,
        XIN,
        INY
    };

    typedef struct
    {
        std::string name;
        Byte addressingmode;
        Byte cyclecount;
        bool isillegal;
    } Instruction;

    nessie::Instruction cpuinsts[7] = {
        {"BRK",IMP,7,false},{"ORA",XIN,6,false},{"JAM",IMP,0,true},{"SLO",XIN,8,true},{"NOP",ZPG,3,true},{"ORA",ZPG,3,false},{"ASL",ZPG,5,false}
    };

    enum KEY
    {
        A,
        B,
        SELECT,
        START,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    typedef struct
    {
        Byte key;
        bool state;
    } Key;

    typedef struct
    {

    } Tile;

    typedef struct
    {
        Byte Y;
        Byte index;
        Byte attribute;
        Byte X;
    } Sprite;

}
#endif

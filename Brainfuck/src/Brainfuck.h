//
// Created by erikd on 27.06.2024.
//

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

typedef int8_t   i8;
typedef uint8_t  u8;
typedef int32_t  i32;
typedef uint32_t u32;

typedef i8 byte;
typedef u8 ubyte;

enum BrainfuckSymbol: byte {
    None       = 0, // Default Value
    PointerInc = 1,
    PointerDec = 2,
    CellInc    = 3,
    CellDec    = 4,
    PutChar    = 5,
    GetChar    = 6,
    Begin      = 7,
    End        = 8,
    Debug      = 9,
};

class Brainfuck {
public:
    explicit Brainfuck(const std::string& source);

    bool Compile();
    void Run();

    std::string GetSource();
    std::string GetCompiledSource();
    std::string GetIUseArchBTWCode();

private:
    std::string m_source;

    bool m_compiled = false;
    std::vector<BrainfuckSymbol> m_code;
    std::unordered_map<u32, u32> m_loops;

    bool m_running = false;
    i32 m_cellPtr;
    u32 m_codePtr;

    u32 m_cellCount = 100;
    ubyte* m_cells;

    bool Step();
    std::string GetSourceWithTable(const char* table);
};
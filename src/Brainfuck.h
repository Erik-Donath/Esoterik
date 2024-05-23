//
// Created by erikd on 23.05.2024.
//

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

typedef uint8_t byte;
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
};

class Brainfuck {
public:
    explicit Brainfuck(const std::string& path);
    bool Compile();
    void Run();
private:
    std::string m_source;
    std::vector<BrainfuckSymbol> m_code;
    std::unordered_map<uint32_t, uint32_t> m_loop;

    bool m_compiled = false;
};

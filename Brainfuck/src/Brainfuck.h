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

    // You could use this to use it in other applications
    inline void SetOutStream(std::basic_ostream<char>* out) {
        m_out = out;
    }
    inline void SetErrStream(std::basic_ostream<char>* err) {
        m_err = err;
    }
    inline void SetInStream(std::basic_istream<char>* in) {
        m_in = in;
    }
private:
    std::string m_source;
    std::vector<BrainfuckSymbol> m_code;
    std::unordered_map<uint32_t, uint32_t> m_loop;

    bool m_compiled = false;

    std::basic_ostream<char>* m_out;
    std::basic_ostream<char>* m_err;
    std::basic_istream<char>* m_in;
};

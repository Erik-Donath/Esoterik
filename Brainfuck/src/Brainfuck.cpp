//
// Created by erikd on 23.05.2024.
//

#include <fstream>
#include <iostream>
#include <sstream>

#include "Brainfuck.h"

Brainfuck::Brainfuck(const std::string& path) {
    m_source = path;
    m_out = &std::cout;
    m_err = &std::cerr;
    m_in  = &std::cin;
}

bool Brainfuck::Compile() {
    if(m_compiled) return true;
    m_compiled = false;

    // Open File
    std::ifstream file(m_source);
    if(!file.good() || !file.is_open()) {
        file.close();

        *m_err << "Could not open the file '" << m_source << "'" << std::endl;
        return false;
    }

    // Clear Vectors
    m_code.clear();
    m_loop.clear();

    // Read File
    char c = '\0';
    bool failedLoopEnd = false;
    bool notSupported  = false;
    std::vector<uint32_t> begins;

    while(file.get(c) && !failedLoopEnd) {
        switch (c) {
            case '>':
                m_code.push_back(BrainfuckSymbol::PointerInc);
                break;
            case '<':
                m_code.push_back(BrainfuckSymbol::PointerDec);
                break;
            case '+':
                m_code.push_back(BrainfuckSymbol::CellInc);
                break;
            case '-':
                m_code.push_back(BrainfuckSymbol::CellDec);
                break;
            case '.':
                m_code.push_back(BrainfuckSymbol::PutChar);
                break;
            case ',':
                m_code.push_back(BrainfuckSymbol::GetChar);
                break;
            case '[':
                begins.push_back(m_code.size());
                m_code.push_back(BrainfuckSymbol::Begin);
                break;
            case ']': {
                if(begins.empty()) {
                    failedLoopEnd = true;
                    break;
                }
                uint32_t begin = begins.back();
                uint32_t end   = m_code.size();
                begins.pop_back();

                m_loop[end]   = begin;
                m_loop[begin] = end;
                m_code.push_back(BrainfuckSymbol::End);
            } break;

            // Debug symbol which some Interpreters use
            case '!':
            case '#':
                notSupported = true;
                break;

            default:
                break;
        }
    }
    file.close();

    if(!begins.empty()) {
        *m_err << "Error: One or more Loops have not been closed!" << std::endl;
        return false;
    }
    if(failedLoopEnd) {
        *m_err << "Error: One or more Loops have not been opened!" << std::endl;
        return false;
    }
    if(notSupported) {
        *m_out << "Warning: The Symbols ! and # are not Supported by this Interpreter!" << std::endl;
    }

    m_compiled = true;
    return true;
}

void Brainfuck::Run() {
    if(!m_compiled) {
        if(!Compile()) {
            *m_err << "Failed: Can not run program" << std::endl;
            return;
        }
    }

    int32_t  cellPtr =  0;
    uint32_t codePtr =  0;

    int32_t cellCount = 100;
    auto* cells = new byte[cellCount];
    for(int i = 0; i < cellCount; i++) cells[i] = 0;

    // Execute
    while(codePtr < m_code.size()) {
        switch(m_code[codePtr]) {
            case None:
            case Debug:
                break;
            case PointerInc:
                cellPtr++;
                if(cellPtr >= cellCount) cellPtr = 0;
                break;
            case PointerDec:
                cellPtr--;
                if(cellPtr < 0) cellPtr = cellCount - 1;
                break;
            case CellInc:
                cells[cellPtr]++;
                break;
            case CellDec:
                cells[cellPtr]--;
                break;
            case PutChar:
                *m_out << cells[cellPtr];
                break;
            case GetChar:
                *m_in  >> cells[cellPtr];
                break;
            case Begin:
                if(cells[cellPtr] == 0) codePtr = m_loop[codePtr];
                break;
            case End:
                if(cells[cellPtr] != 0) codePtr = m_loop[codePtr];
                break;
        }
        codePtr++;
    }
    delete[] cells;
}
std::string Brainfuck::GetBrainfuck() {
    if(!m_compiled) {
        if(!Compile()) {
            *m_err << "Failed: Can not generate Brainfuck code." << std::endl;
            return "";
        }
    }

    std::stringstream ss;
    static const char* table[] = {
            " ", ">", "<", "+", "-", ".", ",", "[", "]", "#"
    };

    for(BrainfuckSymbol symbol : m_code) {
        ss << table[symbol];
    }
    return ss.str();
}
std::string Brainfuck::GetIUseArchBTW() {
    if(!m_compiled) {
        if(!Compile()) {
            *m_err << "Failed: Can not generate I-Use-Arch-BTW code." << std::endl;
            return "";
        }
    }

    std::stringstream ss;
    static const char* table[] = {
            " ", "i", "use", "arch", "linux", "btw", "by", "the", "way", "gentoo"
    };

    for(BrainfuckSymbol symbol : m_code) {
        ss << table[symbol] << ' ';
    }
    return ss.str();
}

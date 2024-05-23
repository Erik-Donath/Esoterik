//
// Created by erikd on 23.05.2024.
//

#include <fstream>
#include <iostream>

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

    file.close();
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
    int32_t  m_cellPtr =  0;
    uint32_t m_codePtr =  0;

    int32_t cellCount = 100;
    auto* cells = new byte[cellCount];
    for(int i = 0; i < cellCount; i++) cells[i] = 0;

    // Execute
    while(m_codePtr < m_code.size()) {
        switch(m_code[m_codePtr]) {
            case None:
                break;
            case PointerInc:
                m_cellPtr++;
                if(m_cellPtr >= cellCount) m_cellPtr = 0;
                break;
            case PointerDec:
                m_cellPtr--;
                if(m_cellPtr < 0) m_cellPtr = cellCount - 1;
                break;
            case CellInc:
                cells[m_cellPtr]++;
                break;
            case CellDec:
                cells[m_cellPtr]--;
                break;
            case PutChar:
                *m_out << cells[m_cellPtr];
                break;
            case GetChar:
                *m_in  >> cells[m_cellPtr];
                break;
            case Begin:
                if(cells[m_cellPtr] == 0) m_codePtr = m_loop[m_codePtr];
                break;
            case End:
                if(cells[m_cellPtr] != 0) m_codePtr = m_loop[m_codePtr];
                break;
        }
        m_codePtr++;
    }
    delete[] cells;
}

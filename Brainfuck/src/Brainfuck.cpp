//
// Created by erikd on 27.06.2024.
//

#include <iostream>
#include <sstream>
#include <utility>
#include "Brainfuck.h"

Brainfuck::Brainfuck(std::string  source) : m_source(std::move(source)) { }
Brainfuck::Brainfuck(const BrainfuckSource &source) {
    m_source = source.source;
    m_code = source.code;
    m_loops = source.loops;
    m_compiled = true;
}

bool Brainfuck::Compile() {
    if(m_compiled) return true;
    m_code.clear();
    m_loops.clear();

    m_compiled = false;
    std::vector<u32> loop_begin;
    for(char c : m_source) {
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
            case '[': {
                u32 curIndex = m_code.size();
                m_code.push_back(BrainfuckSymbol::Begin);
                loop_begin.push_back(curIndex);
            } break;
            case ']': {
                if(loop_begin.empty()) {
                    std::cerr << "Error: One or more Loops have not been opened!" << std::endl;
                    return false;
                }
                u32 begin = loop_begin.back();
                u32 end   = m_code.size();

                loop_begin.pop_back();
                m_code.push_back(BrainfuckSymbol::End);

                m_loops[end] = begin;
                m_loops[begin] = end;
            } break;
            case '#':
                m_code.push_back(BrainfuckSymbol::Debug);
            case '!':
                std::cout << "Warning: Symbols '#' and '!' are not supported!" << std::endl;
            default:
                break;
        }
    }

    if(!loop_begin.empty()) {
        std::cerr << "Error: One or more Loops have not been closed!" << std::endl;
        return false;
    }

    m_compiled = true;
    return m_compiled;
}

void Brainfuck::Run() {
    if(!Compile()) {
        std::cerr << "Failed: Can not run Program." << std::endl;
        return;
    }

    m_cellPtr = 0;
    m_codePtr = 0;

    m_cells = new ubyte[m_cellCount];
    for(int i = 0; i < m_cellCount; i++) m_cells[i] = 0;

    m_running = true;
    while(Step());

    delete[] m_cells;
    m_running = false;
}

bool Brainfuck::Step() {
    if(m_codePtr >= m_code.size()) return false;
    switch(m_code[m_codePtr]) {
        case PointerInc:
            m_cellPtr++;
            if(m_cellPtr >= m_cellCount) m_cellPtr = 0;
            break;
        case PointerDec:
            m_cellPtr--;
            if(m_cellPtr < 0) m_cellPtr = (i32)m_cellCount - 1;
            break;
        case CellInc:
            m_cells[m_cellPtr]++;
            break;
        case CellDec:
            m_cells[m_cellPtr]--;
            break;
        case PutChar:
            std::cout << m_cells[m_cellPtr];
            break;
        case GetChar:
            std::cin  >> m_cells[m_cellPtr];
            break;
        case Begin:
            if(m_cells[m_cellPtr] == 0) m_codePtr = m_loops[m_codePtr];
            break;
        case End:
            if(m_cells[m_cellPtr] != 0) m_codePtr = m_loops[m_codePtr];
            break;
        case None:
        case Debug:
            break;
    }
    m_codePtr++;
    return true;
}

std::string Brainfuck::GetSource() {
    return m_source;
}

std::string Brainfuck::GetCompiledSource() {
    static const char* conversion_table[] = {
            " ", ">", "<", "+", "-", ".", ",", "[", "]", "#"
    };

    if(!Compile()) {
        std::cerr << "Failed: Can not retrieve compiled source." << std::endl;
        return "";
    }

    std::stringstream ss;
    for(BrainfuckSymbol symbol : m_code)
        ss << conversion_table[symbol];
    return ss.str();
}

Brainfuck::~Brainfuck() {
    delete[] m_cells;
}



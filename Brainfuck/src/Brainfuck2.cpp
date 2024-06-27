//
// Created by erikd on 23.05.2024.
//

#include <fstream>
#include <iostream>
#include <sstream>

#include "Brainfuck2.h"

Brainfuck2::Brainfuck2(const BrainfuckSource &source) {
    m_source = source;
    m_out = &std::cout;
    m_err = &std::cerr;
    m_in  = &std::cin;
}

bool Brainfuck2::Compile() {
    if(m_compiled) return true;
    m_compiled = false;

    switch (m_source.Type) {
        case BrainfuckFile:
            return CompileBrainfuck();
        case IUseArchBTW:
            return CompileIUseArchBTW();
    }
    *m_err << "Can not Compile Source Type: " << m_source.Type << std::endl;
    return false;
}

bool Brainfuck2::CompileBrainfuck() {
    if(m_compiled) return true;
    m_compiled = false;

    // Open File
    std::ifstream file(m_source.Path);
    if(!file.good() || !file.is_open()) {
        file.close();

        *m_err << "Could not open bf file '" << m_source.Path << "'" << std::endl;
        return false;
    }

    // Clear Vectors
    m_code.clear();
    m_loop.clear();

    // Read File
    char c;
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

bool Brainfuck2::CompileIUseArchBTW(){
    if(m_compiled) return true;
    m_compiled = false;

    // Open File
    std::ifstream file(m_source.Path);
    if(!file.good() || !file.is_open()) {
        file.close();

        *m_err << "Could not open iusearchbtw file '" << m_source.Path << "'" << std::endl;
        return false;
    }

    // Clear Vectors
    m_code.clear();
    m_loop.clear();

    // Read File
    std::string symbol;
    std::stringstream buffer;
    bool failedLoopEnd = false;
    bool notSupported  = false;
    std::vector<uint32_t> begins;

    buffer << file.rdbuf();
    while(std::getline(buffer, symbol, ' ') && !failedLoopEnd) {
        if(     symbol == "i")     m_code.push_back(BrainfuckSymbol::PointerInc);
        else if(symbol == "use")   m_code.push_back(BrainfuckSymbol::PointerDec);
        else if(symbol == "arch")  m_code.push_back(BrainfuckSymbol::CellInc);
        else if(symbol == "linux") m_code.push_back(BrainfuckSymbol::CellDec);
        else if(symbol == "btw")   m_code.push_back(BrainfuckSymbol::PutChar);
        else if(symbol == "by")   m_code.push_back(BrainfuckSymbol::GetChar);
        else if(symbol == "the") {
            begins.push_back(m_code.size());
            m_code.push_back(BrainfuckSymbol::Begin);
        }
        else if(symbol == "way") {
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
        }
        else if(symbol == "gentoo") notSupported = true;
    }
    file.close();

    if(!begins.empty()) {
        *m_err << "Error: One or more Loops have not been closed!" << std::endl;

        m_compiled = true;
        *m_err << GetIUseArchBTW() << std::endl;
        m_compiled = false;

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

void Brainfuck2::Run() {
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
std::string Brainfuck2::GetBrainfuck() {
    if(!m_compiled) {
        if(!Compile()) {
            *m_err << "Failed: Can not generate I-Use-Arch-BTW code." << std::endl;
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
std::string Brainfuck2::GetIUseArchBTW() {
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

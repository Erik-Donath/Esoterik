//
// Created by erikd on 12.10.2024.
//

#include "Interpreter.h"

#include <iostream>
#include <utility>

BF_Interpreter::BF_Interpreter(std::vector<BF_Symbol> symbols): symbols(std::move(symbols)) {}

bool BF_Interpreter::run(uint32_t cell_size) {
    auto* cells = new uint8_t[cell_size];
    for(uint32_t i = 0; i < cell_size; i++) cells[i] = 0;

    int32_t cellPtr = 0, codePtr = 0;
    while (codePtr < symbols.size()) {
        switch (symbols[codePtr]) {
            case PtrInc:
                cellPtr++;
                if(cellPtr >= cell_size) cellPtr = 0;
                break;
            case PtrDec:
                cellPtr--;
                if(cellPtr < 0) cellPtr = (int32_t)cell_size - 1;
                break;
            case CellInc:
                cells[cellPtr]++;
                break;
            case CellDec:
                cells[cellPtr]--;
                break;
            case PutChr:
                std::cout << cells[cellPtr];
                break;
            case GetChr:
                std::cin  >> cells[cellPtr];
                break;
            case OpenBlock:
                if(cells[cellPtr] == 0) codePtr = blocks[codePtr];
                break;
            case CloseBlock:
                if(cells[cellPtr] != 0) codePtr = blocks[codePtr];
                break;
            case Error:
                std::cout << codePtr << ": error: ran into error symbol." << std::endl;
                return false;
            case Ignore:
                break;
            default:
                std::cout << codePtr << ": error: unknown symbol: " << symbols[codePtr] << "." << std::endl;
                return false;
        }
        codePtr++;
    }

    delete[] cells;
    return true;
}

void BF_Interpreter::findBlocks() {
    std::vector<uint32_t> begins;
    uint32_t index = 0;

    for(BF_Symbol symbol : symbols) {
        switch (symbol) {
            case BF_Symbol::OpenBlock:
                begins.push_back(index);
                break;
            case BF_Symbol::CloseBlock: {
                uint32_t end = index;
                uint32_t begin = -1;

                if (!begins.empty()) {
                    begin = begins.back();
                    begins.pop_back();
                }

                blocks[end] = begin;
                blocks[begin] = end;
            } break;
            default:
                break;
        }
        index++;
    }
}

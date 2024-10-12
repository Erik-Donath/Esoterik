//
// Created by erikd on 12.10.2024.
//

#ifndef ESOTERIC_INTERPRETER_H
#define ESOTERIC_INTERPRETER_H

#include <vector>
#include <unordered_map>
#include "Symbols.h"

class BF_Interpreter {
public:
    explicit BF_Interpreter(BF_Symbols symbols);
    bool run(uint32_t cell_size = 100);
private:
    void findBlocks();

    BF_Symbols symbols;

    std::unordered_map<int32_t , int32_t> blocks;
};


#endif //ESOTERIC_INTERPRETER_H

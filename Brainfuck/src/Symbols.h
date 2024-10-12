//
// Created by erikd on 12.10.2024.
//

#ifndef ESOTERIC_SYMBOLS_H
#define ESOTERIC_SYMBOLS_H
#include <cstdint>

enum BF_Symbol: uint8_t {
    Error       = 0,
    PtrInc      = 1,
    PtrDec      = 2,
    CellInc     = 3,
    CellDec     = 4,
    PutChr      = 5,
    GetChr      = 6,
    OpenBlock   = 7,
    CloseBlock  = 8,
    Ignore      = 9, // (Used for Comments in BF)
};

#define BF_Symbols std::vector<BF_Symbol>

#endif //ESOTERIC_SYMBOLS_H

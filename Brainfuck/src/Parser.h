//
// Created by erikd on 12.10.2024.
//

#ifndef ESOTERIC_PARSER_H
#define ESOTERIC_PARSER_H
#include <string>
#include <vector>
#include "Symbols.h"

class BF_Parser {
public:
    explicit BF_Parser(std::string path);
    bool parse();

    BF_Symbols GetSymbols();
    std::vector<std::string> GetErrors();
private:
    BF_Symbol next(char ch);

    std::string path;
    uint32_t line = 0, pos = 0;

    BF_Symbols symbols;
    std::vector<std::string> errors;
    uint32_t blockCheck = 0;
};

#endif //ESOTERIC_PARSER_H

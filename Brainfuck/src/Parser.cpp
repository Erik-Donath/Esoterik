//
// Created by erikd on 12.10.2024.
//

#include "Parser.h"

#include <utility>
#include <fstream>

BF_Parser::BF_Parser(std::string path): path(std::move(path)) {}

bool BF_Parser::parse() {
    errors.clear();
    symbols.clear();

    std::ifstream file(path);
    if(!file) {
        errors.push_back("Can not read file: '" + path + "'");
        return false;
    }

    char ch;
    line = 1;
    pos  = 1;

    while(file.get(ch)) {
        if(ch == '\n') {
            line++;
            pos = 0;
        }
        else {
            BF_Symbol symbol = next(ch);
            if(symbol != BF_Symbol::Ignore) symbols.push_back(symbol);
            pos++;
        }
    }

    if(blockCheck != 0) {
        symbols.push_back(BF_Symbol::Error);
        errors.push_back(path + ":" + std::to_string(line) + ":" + std::to_string(pos) + ": error: not all blocks have been closed.");
    }

    file.close();
    return errors.empty();
}

std::vector<BF_Symbol> BF_Parser::GetSymbols() {
    return symbols;
}

std::vector<std::string> BF_Parser::GetErrors() {
    return errors;
}

BF_Symbol BF_Parser::next(char ch) {
    switch(ch) {
        case '>':
            return BF_Symbol::PtrInc;
        case '<':
            return BF_Symbol::PtrDec;
        case '+':
            return BF_Symbol::CellInc;
        case '-':
            return BF_Symbol::CellDec;
        case '.':
            return BF_Symbol::PutChr;
        case ',':
            return BF_Symbol::GetChr;
        case '[':
            blockCheck++;
            return BF_Symbol::OpenBlock;
        case ']':
            if(blockCheck == 0) {
                errors.push_back(path + ":" + std::to_string(line) + ":" + std::to_string(pos) + ": error: to many blocks closed.");
                return BF_Symbol::Error;
            }
            else {
                blockCheck--;
                return BF_Symbol::CloseBlock;
            }
        default:
            return BF_Symbol::Ignore;
    }
}

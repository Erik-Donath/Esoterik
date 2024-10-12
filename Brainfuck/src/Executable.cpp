//
// Created by erikd on 27.06.2024.
//

#include <iostream>
#include <fstream>

#include "Parser.h"
#include "Interpreter.h"

int32_t main(int32_t argc, char *argv[]) {
    BF_Symbols symbols;
    symbols.push_back(BF_Symbol::OpenBlock);
    symbols.push_back(BF_Symbol::GetChr);
    symbols.push_back(BF_Symbol::PutChr);
    symbols.push_back(BF_Symbol::CloseBlock);
    BF_Interpreter interpreter(symbols);
    interpreter.run(100);

    /*
    if(argc < 2) {
        std::cout << "The first Argument has to be an Brainfuck File!" << std::endl;
        return 1;
    }

    for(int i = 1; i < argc; i++) {
        std::cout << '\'' << argv[i] << "': " << std::endl;

        std::ifstream file(argv[i]);
        if(!file.is_open() || !file.good()) {
            std::cout << "Error: Can't read file" << std::endl;
            continue;
        }

        std::string source = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        BrainfuckA bf(source);
        if(!bf.Compile()) {
            std::cout << "Skipping the file do to compilation error" << std::endl;
            continue;
        }
        bf.Run();
        std::cout << std::endl << "Execution has stopped!" << std::endl;
    }*/
}
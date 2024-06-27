//
// Created by erikd on 27.06.2024.
//

#include <iostream>
#include <fstream>

#include "Brainfuck.h"
i32 main(i32 argc, char *argv[]) {
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
        Brainfuck bf(source);
        if(!bf.Compile()) {
            std::cout << "Skipping the file do to compilation error" << std::endl;
            continue;
        }
        bf.Run();
        std::cout << std::endl << "Execution has stopped!" << std::endl;
    }
}
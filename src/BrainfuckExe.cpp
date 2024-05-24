#include <iostream>
#include "../Brainfuck/src/Brainfuck.h"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cerr << "The first Argument has to be an BF File!" << std::endl;
        return 1;
    }

    for(int i = 1; i < argc; i++) {
        std::cout << argv[i] << std::endl;

        Brainfuck bf(argv[i]);
        if(!bf.Compile()) {
            std::cout << std::endl;
            continue;
        }
        bf.Run();

        std::cout << "BF Code: " << std::endl << bf.GetBrainfuck() << std::endl;
        std::cout << "I-Use-Arch-BTW Code: " << std::endl << bf.GetIUseArchBTW() << std::endl;
    }
    return 0;
}

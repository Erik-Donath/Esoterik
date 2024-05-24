#include <iostream>
#include <Brainfuck.h>

BrainfuckSourceType GetTypeFromPath(const std::string& path) {
    size_t i = path.rfind('.');
    if (i != std::string::npos) {
        std::string ending = path.substr(i + 1);
        if(ending == "bf")               return BrainfuckSourceType::BrainfuckFile;
        else if(ending == "iusearchbtw") return BrainfuckSourceType::IUseArchBTW;
    }
    return BrainfuckSourceType::NoneType;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cerr << "The first Argument has to be an BF or iusearchbtw File!" << std::endl;
        return 1;
    }

    for(int i = 1; i < argc; i++) {
        std::cout << argv[i] << std::endl;

        std::string path = argv[i];
        Brainfuck bf(BrainfuckSource(path, GetTypeFromPath(path)));
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

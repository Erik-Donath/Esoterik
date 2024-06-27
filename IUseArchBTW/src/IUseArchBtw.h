//
// Created by erikd on 27.06.2024.
//

#pragma once
#include <string>
#include <cstdint>

typedef int8_t   i8;
typedef uint8_t  u8;
typedef int32_t  i32;
typedef uint32_t u32;

typedef i8 byte;
typedef u8 ubyte;

class Brainfuck;

class IUseArchBtw {
    explicit IUseArchBtw(std::string  source);
    ~IUseArchBtw();

    bool Compile();
    void Run();

    std::string GetSource();
    std::string GetCompiledSource();

    [[nodiscard]] inline Brainfuck& GetBrainfuck() {
        return *m_bf;
    }
private:
    std::string m_source;
    Brainfuck* m_bf = nullptr;
};

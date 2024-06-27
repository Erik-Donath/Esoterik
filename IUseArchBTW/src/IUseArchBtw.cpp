//
// Created by erikd on 27.06.2024.
//

#include <iostream>
#include <utility>
#include "Brainfuck.h"
#include "IUseArchBtw.h"

IUseArchBtw::IUseArchBtw(std::string source): m_source(std::move(source)) {

}

bool IUseArchBtw::Compile() {
    std::cout << "Failed: I Use Arch Btw is not implemented yet." << std::endl;
    return false;
}

void IUseArchBtw::Run() {
    if(!m_bf) {
        if(!Compile()) {
            std::cout << "Failed: Can not execute IUseArchBTW code." << std::endl;
            return;
        }
    }
    m_bf->Run();
}

std::string IUseArchBtw::GetSource() {
    return m_source;
}

std::string IUseArchBtw::GetCompiledSource() {
    return m_source;
}

IUseArchBtw::~IUseArchBtw() {
    delete m_bf;
}

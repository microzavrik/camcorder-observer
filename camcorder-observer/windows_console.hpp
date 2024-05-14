#pragma once

#include <string>
#include <Windows.h>

class Console
{
public:
    Console();
    ~Console();
private:
    FILE* consoleOutputStream;
    FILE* consoleInputStream;
};
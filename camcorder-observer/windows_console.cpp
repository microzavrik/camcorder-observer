#include "windows_console.hpp"

Console::Console()
{
    AllocConsole();
    freopen_s(&consoleOutputStream, "CONOUT$", "w", stdout);
    freopen_s(&consoleInputStream, "CONIN$", "r", stdin);
}

Console::~Console()
{
    fclose(consoleOutputStream);
    fclose(consoleInputStream);
    FreeConsole();
}
#include <windows.h>
#include "Console.h"

Console::Console() {
}

Console::~Console() {
}

void Console::gotoxy(int x, int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){--y,--x});
}
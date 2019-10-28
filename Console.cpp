#include <windows.h>
#include "Console.h"

Console::Console() {
}

Console::~Console() {
}

void Console::gotoxy(int x, int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){ (SHORT)--y, (SHORT)--x});
}

void Console::colorTex(int COLOR) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR);
}

void Console::windows(int y, int x) {
    system("title Jogo Campo Minado - Genilton");
    system("color 71");

    COORD outbuff;
    outbuff.X = x;
    outbuff.Y = y;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(hConsole, outbuff);
    Sleep(130);
    SMALL_RECT windowSize = {(short) 0, (short) 0, (short) --x, (short) --y};
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

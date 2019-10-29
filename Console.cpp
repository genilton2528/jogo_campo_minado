#include <windows.h>
#include <string.h>
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
    Console::colorTex(113);
    COORD outbuff;
    outbuff.X = x;
    outbuff.Y = y;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(hConsole, outbuff);
    Sleep(130);
    SMALL_RECT windowSize = {(short) 0, (short) 0, (short) --x, (short) --y};
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

void Console::clip(char *str, int n){
    for(int i = 0; i < n; i++){
        if(str[i] == '\n'){
            str[i] = '\0';
            break;
        }
    }
}

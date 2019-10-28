#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include "Panel.h"
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13
#define ESC 27
#define ESPACO 32

Panel::Panel() {
    this->windows( 60, 20);
}

Panel::~Panel() {
}

int Panel::menu() {
    int arrow = 49;
    int opc;
    char menu[] = "\t\t1  MENU           \n\n"
                  "\t\t2  JOGAR           \n"
                  "\t\t3  NOVO TABULEIRO  \n"
                  "\t\t4  RECORDES        \n"
                  "\t\t5  SAIR            \n";
    while(true){
        system("cls");
        printf("\n\n\n");
        for(int i = 0 ; i < 110; i++){
            if(menu[i] == arrow){
                printf(">");
                continue;
            }
            if(menu[i] == 49 || menu[i] == 50 ||menu[i] == 51 ||menu[i] == 52 ||menu[i] == 53){
                printf(" ");
                continue;
            }
            printf("%c", menu[i]);
        }
        setbuf( stdin, NULL);
        opc = getch();
        switch(opc){
            case UP:
                arrow--;
            break;
            case DOWN:
                arrow++;
            break;
            default:
            break;
        }
    }
    return 0;
}

void Panel::colorTex(int COLOR) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR);
}

void Panel::windows(int x, int y) {
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

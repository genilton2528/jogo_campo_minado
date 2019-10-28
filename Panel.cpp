#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include "Panel.h"
#include "Console.h"
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13
#define ESC 27
#define ESPACO 32

Panel::Panel() {
    Console::windows( 20, 80);
}

Panel::~Panel() {
}

int Panel::menu() {
    int x = 8;
    int opc;
    
    system("cls");
    Console::gotoxy( 5, 10);
    printf("MENU");
    Console::gotoxy( 8, 10);
    printf("JOGAR");
    Console::gotoxy( 9, 10);
    printf("PERSONALIZADO");
    Console::gotoxy( 10, 10);
    printf("RECORDES");
    Console::gotoxy( 11, 10);
    printf("SAIR");
    Console::gotoxy( x, 8);
    printf(">");
    Console::gotoxy( 20, 50);
                
    while(true){
        setbuf( stdin, NULL);
        opc = getch();
        switch(opc){
            case UP:
                Console::gotoxy( x, 8);
                printf(" ");
                if(x == 8){
                    x = 12;
                }
                x--;
                Console::gotoxy( x, 8);
                printf(">");   
                Console::gotoxy( 20, 50);
            break;
            case DOWN:
                Console::gotoxy( x, 8);
                printf(" ");
                if(x == 11){
                    x = 7;
                }
                x++;
                Console::gotoxy( x, 8);
                printf(">");        
                Console::gotoxy( 20, 50);
            break;
            case ENTER:
                return  x-7;               
            break;
            default:
            break;
        }
    }
    return 0;
}
#include "Panel.h"
#include "Field.h"
#include "Player.h"
#include "Console.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

int main() {
    int opc, x, y, bomb;
    Field field;
    Panel panel;

    while (true) {
        opc = panel.menu();
        switch (opc) {
            case 1:
                field.setField(9, 9, 10);
                if (field.getField() != NULL && field.getHidden() != NULL) {
                    field.fillField();
                    field.play(); 
                } else {
                    system("cls");
                    printf("\n\n\tFalhou");
                    setbuf(stdin, NULL);
                    getch();
                }
                break;
            case 2:
                system("cls");
                Console::gotoxy(3, 5);
                printf("Digite [Altura][Largura][Bombas]: ");
                scanf("%d %d %d", &x, &y, &bomb);
                if (x > 4 && y > 4 && bomb < (int) (x * y)*0.75 && bomb > 4) {
                    field.setField(x, y, bomb);
                    if (field.getField() != NULL && field.getHidden() != NULL) {
                        field.fillField();
                        field.play();
                        setbuf(stdin, NULL);
                        getch();
                    } else {
                        system("cls");
                        printf("\n\n\tFalhou!");
                        setbuf(stdin, NULL);
                        getch();
                    }
                } else {
                    system("cls");
                    Console::gotoxy(3, 3);
                    printf("Valores Invalidos\n\n"
                            "\t- Digite a altura, largura e numero de bombas\n"
                            "\t  respectivamente separado por espaco.\n\n"
                            "\t- As dimensoes devem ser maior ou ingual a 5.\n\n"
                            "\t- O numero de bombas nao pode ocupar mais do que 75\n"
                            "\t  por cento do campo, e devem ter no minimo 4 bombas.");
                    setbuf(stdin, NULL);
                    getch();
                }
                break;
            case 3:
                break;
            case 4:
                field.~Field();
                exit(0);
                break;
        }
    }
    return 0;
}


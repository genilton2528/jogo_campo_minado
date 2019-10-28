#include "Panel.h"
#include "Field.h"
#include "Console.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

int main() {
    int opc, x, y, bomb;
    Panel panel;
    Field field;

    while (true) {
        opc = panel.menu();
        switch (opc) {
            case 1:
                field.setField( 9, 9, 10);
                if (field.getField() != NULL && field.getHidden() != NULL) {
                    system("cls");
                    field.fillField();
                    field.printField();
                    setbuf(stdin, NULL);
                    getch();
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
                if (x > 9 && y > 9 && bomb < (int) (x * y)*0.75) {
                    field.setField(x, y, bomb);
                    if (field.getField() != NULL && field.getHidden() != NULL) {
                        system("cls");
                        field.fillField();
                        field.printField();
                        setbuf(stdin, NULL);
                        getch();
                    } else {
                        system("cls");
                        printf("\n\n\tFalhou");
                        setbuf(stdin, NULL);
                        getch();
                    }
                } else {
                    system("cls");
                    Console::gotoxy(3, 3);
                    printf("Valores Invalidos\n\n"
                            "\t- Digite a altura largura e numero de bombas\n"
                            "\t  respectivamente separado por espaco.\n\n"
                            "\t- As dimensoes devem ser maior que 9.\n\n"
                            "\t- O numero de bombas nao pode ocupar mais\n"
                            "\t  do que 75 por cento do campo.");
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


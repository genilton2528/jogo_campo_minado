#include "Panel.h"
#include "Field.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

int main() {
    int opc;
    Panel panel;
    Field field;
    opc = panel.menu();
    
    switch(opc){
        case 1:         
            if(field.getField() != NULL && field.getHidden() != NULL){
                system("cls");
                field.fillField();
                field.printField();
                getch();
            }else{
                system("cls");
                printf("\n\n\tFalhou");
                getch();
            }
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
    }
    return 0;
}


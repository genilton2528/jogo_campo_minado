#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "Panel.h"
#include "Console.h"
#include "Field.h"
#include "Player.h"

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13
#define ESC 27
#define ESPACO 32
#define BLUE 113
#define GREEN 122

Field::Field() {
    this->field = NULL;
    this->hidden = NULL;
}

Field::Field(int x, int y, int bomb) {
    this->row = x;
    this->column = y;
    this->bomb = bomb;
    this->allocField();
}

Field::~Field() {
    this->freeField();
}

void Field::allocField() {
    this->field = (int **) calloc(this->row, sizeof (int *));
    this->hidden = (int **) calloc(this->row, sizeof (int *));

    if (this->field == NULL || this->hidden == NULL) {
        return;
    }

    for (int i = 0; i < column; i++) {
        this->field[i] = (int*) calloc(this->column, sizeof (int));
        this->hidden[i] = (int*) calloc(this->column, sizeof (int));
        if (this->field[i] == NULL || this->hidden[i] == NULL) {
            this->field = NULL;
            this->hidden = NULL;
            return;
        }
    }
}

void Field::freeField() {
    if (this->field != NULL) {
        for (int i = 0; i < this->row; i++) {
            free(this->field[i]);
        }
        free(this->field);
    }
    this->field = NULL;
    if (this->hidden != NULL) {
        for (int i = 0; i < this->row; i++) {
            free(this->hidden[i]);
        }
        free(this->hidden);
    }
    this->hidden = NULL;
}

int** Field::getField() {
    return this->field;
}

int** Field::getHidden() {
    return this->hidden;
}

void Field::printField() {
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->column; j++) {
            if (this->field[i][j] > 9) {
                printf(" %d", this->field[i][j]);
                continue;
            }
            printf("  %d", this->field[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n\n");
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->column; j++) {
            printf("%d", this->hidden[i][j]);
        }
        printf("\n");
    }
}

void Field::setField(int x, int y, int bomb) {
    this->row = x;
    this->column = y;
    this->bomb = bomb;
    this->freeField();
    this->allocField();
}

void Field::fillField() {
    int count = 0;
    int x, y;
    srand(time(NULL));
    while (count < this->bomb) {
        x = rand() % (this->row - 1);
        y = rand() % (this->column - 1);
        if (this->field[x][y] > 8) {
            srand(time(NULL) * count);
            continue;
        }
        this->field[x][y] = 9;

        if (y != 0 && x != 0) {
            this->field[x - 1][y - 1]++;
        }
        if (y != 0) {
            this->field[x][y - 1]++;
            this->field[x + 1][y - 1]++;
        }
        if (x != 0) {
            this->field[x - 1][y + 1]++;
            this->field[x - 1][y]++;
        }
        this->field[x][y + 1]++;
        this->field[x + 1][y + 1]++;
        this->field[x + 1][y]++;

        count++;
    }
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->column; j++) {
            this->hidden[i][j] = 1;
        }
    }
}

int Field::getX() {
    return this->row;
}

int Field::getY() {
    return this->column;
}

void Field::drawField() {
    Panel::header();
    int x = 6, y = 10;

    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->column; j++) {
            Console::gotoxy(x, y);
            this->printBlock(i, j, BLUE);
            y += 2;
        }
        x++;
        y = 10;
    }
    Console::gotoxy(x + 2, 1);
    printf("\t[ESPACO] Marca Bandeira\n\t[ENTER] Descobre\n\t[ESC] Sair");
}

void Field::printBlock(int x, int y, int color) {
    Console::colorTex(color);
    if (this->hidden[x][y] == 1) {
        printf("%c%c", 219, 219);
        return;
    }
    if (this->hidden[x][y] == 2) {
        printf(" !");
        return;
    }
    if (this->field[x][y] == 0) {
        printf(" ~");
        return;
    }
    if (this->field[x][y] > 8) {
        printf(" B");
        return;
    }
    printf(" %d", this->field[x][y]);
}

void Field::play() {
    this->player.setLose(0);
    this->player.setWin(0);
    clock_t timer;
    int opc, x = 6, y = 10, xSelect = 0, ySelect = 0;
    
    printf("\n\n\tDigite seu nome: ");
    setbuf(stdin, NULL);
    fgets(player.getNome(), 50, stdin);
    Console::clip( player.getNome(), 51);

    this->drawField();
    timer = clock();
    while (this->player.isWin() == 0 && this->player.isLose() == 0) {
        setbuf(stdin, NULL);
        opc = getch();
        switch (opc) {
            case UP:
                Console::gotoxy(x, y);
                this->printBlock(xSelect, ySelect, BLUE);
                if (xSelect == 0) {
                    x = this->row + 5;
                    xSelect = this->row - 1;
                    Console::gotoxy(x, y);
                    this->printBlock(xSelect, ySelect, GREEN);
                } else {
                    x--;
                    xSelect--;
                    Console::gotoxy(x, y);
                    this->printBlock(xSelect, ySelect, GREEN);
                }
                Console::gotoxy(20, 50);
                break;
            case DOWN:
                Console::gotoxy(x, y);
                this->printBlock(xSelect, ySelect, BLUE);
                if (xSelect == this->row - 1) {
                    x = 6;
                    xSelect = 0;
                    Console::gotoxy(x, y);
                    this->printBlock(xSelect, ySelect, GREEN);
                } else {
                    x++;
                    xSelect++;
                    Console::gotoxy(x, y);
                    this->printBlock(xSelect, ySelect, GREEN);
                }
                Console::gotoxy(20, 50);
                break;
            case LEFT:
                Console::gotoxy(x, y);
                this->printBlock(xSelect, ySelect, BLUE);
                if (ySelect == 0) {
                    y = (this->column * 2 + 9) - 1;
                    ySelect = this->column - 1;
                    Console::gotoxy(x, y);
                    this->printBlock(xSelect, ySelect, GREEN);
                } else {
                    y -= 2;
                    ySelect--;
                    Console::gotoxy(x, y);
                    this->printBlock(xSelect, ySelect, GREEN);
                }
                Console::gotoxy(20, 50);
                break;
            case RIGHT:
                Console::gotoxy(x, y);
                this->printBlock(xSelect, ySelect, BLUE);
                if (ySelect == this->column - 1) {
                    y = 10;
                    ySelect = 0;
                    Console::gotoxy(x, y);
                    this->printBlock(xSelect, ySelect, GREEN);
                } else {
                    y += 2;
                    ySelect++;
                    Console::gotoxy(x, y);
                    this->printBlock(xSelect, ySelect, GREEN);
                }
                Console::gotoxy(20, 50);
                break;
            case ENTER:
                this->discoverLine(xSelect, ySelect);
                this->drawField();
                this->youWin();
                break;
            case ESC:
                if (Panel::dialogBox() == 1) {
                    return;
                }
                this->drawField();
                break;
            case ESPACO:
                this->hidden[xSelect][ySelect] = 2;
                Console::gotoxy(x, y);
                this->printBlock(xSelect, ySelect, GREEN);
                this->youWin();
                break;
            default:
                break;
        }
    }
    Console::colorTex(BLUE);
    timer = clock() - timer;
    this->player.setTimer((float)timer/CLOCKS_PER_SEC);
    if(this->player.isWin() == 1){
        system("cls");
        printf("\n\n\t _____________________________________ ");    
        printf("\n\t %c                                   %c ", 219, 219);
        printf("\n\t %c        Voce Ganhou                %c ", 219, 219);
        printf("\n\t %c___________________________________%c ", 219, 219);
        printf("\n\n\t - %s %.2f", player.getNome(), player.getTimer());
        setbuf(stdin, NULL);
        getch();        
    }else{
        system("cls");
        printf("\n\n\t _____________________________________ ");    
        printf("\n\t %c                                   %c ", 219, 219);
        printf("\n\t %c        Voce Perdeu                %c ", 219, 219);
        printf("\n\t %c___________________________________%c ", 219, 219);
        printf("\n\n\t - %s %.2f", player.getNome(), player.getTimer());
        setbuf(stdin, NULL);
        getch();    
    }
}

void Field::discoverLine(int x, int y) {
    if (x >= this->row || y >= this->column || x < 0 || y < 0) {
        return;
    }
    if (this->field[x][y] > 8) {
        this->hidden[x][y] = 0;
        this->player.setLose(1);
        return;
    }
    if (this->hidden[x][y] != 1) {
        return;
    }
    //pra esquerda
    for (int i = y; i >= 0; i--) {
        if (this->field[x][i] > 8) {
            break;
        }
        if (this->field[x][i] > 0) {
            this->discoverColumn(x, i);
            break;
        }
        this->discoverColumn(x, i);
    }
    //Pra direita
    for (int i = y; i < this->column; i++) {
        if (this->field[x][i] > 8) {
            break;
        }
        if (this->field[x][i] > 0) {
            this->discoverColumn(x, i);
            break;
        }
        this->discoverColumn(x, i);
    }
}

void Field::discoverColumn(int x, int y) {
    if (x >= this->row || y >= this->column || x < 0 || y < 0) {
        return;
    }
    if (this->field[x][y] > 8) {
        this->hidden[x][y] = 0;
        this->player.setLose(1);
        return;
    }
    if (this->hidden[x][y] != 1) {
        return;
    }
    //pra cima
    for (int i = x; i >= 0; i--) {
        if (this->field[i][y] > 8) {
            break;
        }
        if (this->field[i][y] > 0) {
            this->hidden[i][y] = 0;
            break;
        }
        this->hidden[i][y] = 0;
        if (y - 1 >= 0) {
            if (this->hidden[i][y - 1] == 1 && this->field[i][y - 1] < 9) {
                this->discoverLine(i, y - 1);
            }
        }
        if (y + 1 < this->column) {
            if (this->hidden[i][y + 1] == 1 && this->field[i][y + 1] < 9) {
                this->discoverLine(i, y + 1);
            }
        }
    }
    //Pra baixo
    for (int i = x; i < this->row; i++) {
        if (this->field[i][y] > 8) {
            break;
        }
        if (this->field[i][y] > 0) {
            this->hidden[i][y] = 0;
            break;
        }
        this->hidden[i][y] = 0;
        if (y - 1 >= 0) {
            if (this->hidden[i][y - 1] == 1 && this->field[i][y - 1] < 9) {
                this->discoverLine(i, y - 1);
            }
        }
        if (y + 1 < this->column) {
            if (this->hidden[i][y + 1] == 1 && this->field[i][y + 1] < 9) {
                this->discoverLine(i, y + 1);
            }
        }
    }
}

void Field::youWin() {
    int count = 0;
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->column; j++) {
            if(this->hidden[i][j] != 0){
                count++;
            }
        }
    }
    if(count == this->bomb){
        this->player.setWin(1);
    }
}
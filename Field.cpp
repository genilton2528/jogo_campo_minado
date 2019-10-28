#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

Field::Field() {
    this->field = NULL;
    this->hidden = NULL;
}

Field::Field(int x, int y, int bomb) {
    this->x = x;
    this->y = y;
    this->bomb = bomb;
    this->allocField();
}

Field::~Field() {
    this->freeField();
}

void Field::allocField() {
//    try {
        this->field = (int **) calloc(this->x, sizeof (int *));
        this->hidden = (int **) calloc(this->x, sizeof (int *));

        if (this->field == NULL || this->hidden == NULL) {
            return;
        }

        for (int i = 0; i < y; i++) {
            this->field[i] = (int*) calloc(this->y, sizeof (int));
            this->hidden[i] = (int*) calloc(this->y, sizeof (int));
            if (this->field[i] == NULL || this->hidden[i] == NULL) {
                this->field = NULL;
                this->hidden = NULL;
                return;
            }
        }
//    } catch (std::bad_alloc& ba) {
//        system("cls");
//        printf("\n\n\tFalha na criacao do campo: Nao foi possivel alocar memoria!");
//        setbuf(stdin, NULL);
//        getch();
//    } catch (...) {
//        system("cls");
//        printf("\n\n\tFalha na criacao do campo");
//        setbuf(stdin, NULL);
//        getch();
//    }
}

void Field::freeField() {
    if (this->field != NULL) {
        for (int i = 0; i < this->x; i++) {
            free(this->field[i]);
        }
        free(this->field);
    }
    this->field = NULL;
    if (this->hidden != NULL) {
        for (int i = 0; i < this->x; i++) {
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
    for (int i = 0; i < this->x; i++) {
        for (int j = 0; j < this->y; j++) {
            if (this->field[i][j] > 9) {
                printf(" %d", this->field[i][j]);
                continue;
            }
            printf("  %d", this->field[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n\n");
    for (int i = 0; i < this->x; i++) {
        for (int j = 0; j < this->y; j++) {
            printf("%d", this->hidden[i][j]);
        }
        printf("\n");
    }
}

void Field::setField(int x, int y, int bomb) {
    this->x = x;
    this->y = y;
    this->bomb = bomb;
    this->freeField();
    this->allocField();
}

void Field::fillField() {
    int count = 0;
    int x, y;
    srand(time(NULL));
    while (count < this->bomb) {
        x = rand() % (this->x - 1);
        y = rand() % (this->y - 1);
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
    for (int i = 0; i < this->x; i++) {
        for (int j = 0; j < this->y; j++) {
            this->hidden[i][j] = 1;
        }
    }
}

int Field::getX() {
    return this->x;
}

int Field::getY() {
    return this->y;
}

int Field::play() {
    Panel panel;
    panel.header();
    int x = 6, y = 10;

    for (int i = 0; i < this->x; i++) {
        for (int j = 0; j < this->y; j++) {
            if (i == 0 && j == 0) {
                Console::colorTex(90);
                Console::gotoxy(x, y);
                printf("%c%c", 219, 219);
                Console::colorTex(113);
                y += 2;
                continue;
            }
            if (this->hidden[i][j] == 1) {
                Console::gotoxy(x, y);
                printf("%c%c", 219, 219);
                y += 2;
                continue;
            }
            if (this->field[i][j] == 0) {
                printf(" ~");
                y += 2;
                continue;
            }
            printf(" %d", this->field[i][j]);
            y += 2;
        }
        x++;
        y = 10;
    }
    Console::gotoxy(x, 50);
    return 1;
}

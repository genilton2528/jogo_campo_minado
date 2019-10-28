#include "Field.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Field::Field() {
    this->field  = NULL;
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
}

void Field::freeField() {
    if (this->field != NULL) {
        for (int i = 0; i < this->x; i++) {
            free(this->field[i]);
        }
        free(this->field);
    }
    if (this->hidden != NULL) {
        for (int i = 0; i < this->x; i++) {
            free(this->hidden[i]);
        }
        free(this->hidden);
    }
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
            if(this->field[i][j]>9){
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
        
        if(y != 0 && x != 0){ 
            this->field[x-1][y-1]++;
        }
        if(y != 0){ 
            this->field[x][y-1]++; 
            this->field[x+1][y-1]++;
        }
        if(x != 0){ 
            this->field[x-1][y+1]++;        
            this->field[x-1][y]++;
        }          
        this->field[x][y+1]++; 
        this->field[x+1][y+1]++;
        this->field[x+1][y]++;
        
        count++;
    }
    for (int i = 0; i < this->x; i++) {
        for (int j = 0; j < this->y; j++) {
            this->hidden[i][j] = 1;
        }
    }
}
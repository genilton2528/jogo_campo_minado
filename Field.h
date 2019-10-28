#ifndef FIELD_H
#define FIELD_H

class Field {
public:
    Field();
    Field(int x, int y, int bomb);
    ~Field();
    void allocField();
    void freeField();
    void printField();
    void setField(int x, int y, int bomb);
    void fillField();
    int** getField();
    int** getHidden();
    int getX();
    int getY();
    int play();
private:
    int **field;
    int **hidden;
    int x;
    int y;
    int bomb;
};

#endif


#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player();
    ~Player();
    
    void setLose(int lose);
    void setWin(int win);
    void setNome(char nome[]);
    int isLose();
    int isWin();
    char* getNome();    

private:
    char nome[50];
    int win;
    int lose;
};

#endif


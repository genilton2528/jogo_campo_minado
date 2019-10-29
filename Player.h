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
    float getTimer();
    void setTimer(float timer);

private:
    char nome[51];
    float timer;
    int win;
    int lose;
};

#endif


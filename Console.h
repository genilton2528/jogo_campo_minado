#ifndef CONSOLE_H
#define CONSOLE_H

class Console {
public:
    Console();
    ~Console();
    void static gotoxy(int x, int y);
    void static colorTex(int COLOR);
    void static windows(int x, int y);
    void static clip(char *str, int n);
private:
};

#endif


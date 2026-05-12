#ifndef PAD_H //se NON è ancora stato definito (if not defined) un simbolo/identificatore chiamato SNAKE_H
#define PAD_H //allora definiscilo ora

#include <raylib.h>
#include <deque>
using namespace std;

class Pad {
private:
    int larghezza;
    int altezza;
    Color colore;
    Vector2 pos;

public:
    Pad(int larghezza, int altezza, Color colore) {
        this->larghezza = larghezza;
        this->altezza = altezza;
        this->colore = colore;
        this->pos = {0,0};
    }

    void Disegna() {
        Rectangle rettangolo = {pos.x, pos.y, (float)larghezza, (float)altezza};
        DrawRectangleRounded(rettangolo, 0.8, 16, colore);
    }

    //altezza
    int getAltezza() {
        return altezza;
    }

    void setAltezza(int altezza) {
        this->altezza = altezza;
    }

    //larghezza
    int getLarghezza() {
        return larghezza;
    }

    void setLarghezza(int larghezza) {
        this->larghezza = larghezza;
    }

    //colore
    Color getColore() {
        return colore;
    }

    void setColore(Color colore) {
        this->colore = colore;
    }

    //x, y
    Vector2 getPos() {
        return Vector2{pos.x, pos.y};
    }

    void setPos(float x, float y) {
        pos = {x, y};
    }
    
};

#endif
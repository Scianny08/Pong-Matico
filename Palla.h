#ifndef PALLA_H //se NON è ancora stato definito (if not defined) un simbolo/identificatore chiamato SNAKE_H
#define PALLA_H //allora definiscilo ora

#include <functional>
#include <raylib.h>
using namespace std;

class Palla {
private:
    int raggio;
    Color colore;
    Vector2 pos;

public:
    Palla(int raggio, Color colore) {
        this->raggio = raggio;
        this->colore = colore;
    }

    void Disegna() {
        DrawCircle(pos.x, pos.y, raggio, colore);
    }
    
    //raggio
    int getRaggio() {
        return raggio;
    }

    void setRaggio(int raggio) {
        this->raggio = raggio;
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
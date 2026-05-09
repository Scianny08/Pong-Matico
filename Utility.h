#ifndef UTILITY_H //se NON è ancora stato definito (if not defined) un simbolo/identificatore chiamato SNAKE_H
#define UTILITY_H //allora definiscilo ora

#include <raylib.h>
using namespace std;

class Utility {
public:
    double ultimoAggiornamentoTempo = 0;

    bool EventTriggered(double intervallo) {
        double tempoAttuale = GetTime();
        double tempoTrascorso = tempoAttuale - ultimoAggiornamentoTempo;
        
        if (tempoTrascorso >= intervallo) {
            ultimoAggiornamentoTempo = tempoAttuale;
            return true; //intervallo superato
        }
        return false; //intervallo non superato
    }
};

#endif
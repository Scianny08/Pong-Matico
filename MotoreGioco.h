#ifndef MOTOREGIOCO_H //se NON è ancora stato definito (if not defined) un simbolo/identificatore chiamato SNAKE_H
#define MOTOREGIOCO_H //allora definiscilo ora

#include <raylib.h>
#include "Pad.h"
#include "Palla.h"
#include <cmath>
using namespace std;

class MotoreGioco {
private:
    int larghezzaCampo;
    int altezzaCampo;
    Color coloreCampo;

    int larghezzaPad;
    int altezzaPad;
    Pad padDX;
    Pad padSX;

    Palla palla;
    int angolo;

public:
    // Costruttore con "Initialization List" (la parte dopo i due punti ':')
    MotoreGioco(int larghezzaCampo, int altezzaCampo, Color coloreCampo):
        // Assegno i parametri. 
        // Anche se i nomi sono uguali (es. larghezzaCampo), 
        // il compilatore capisce che quello a sinistra dei ( ) è la variabile della classe.
        larghezzaCampo(larghezzaCampo),
        altezzaCampo(altezzaCampo),
        coloreCampo(coloreCampo),
        larghezzaPad(30),
        altezzaPad(100),

        // Inizializzo gli oggetti complessi direttamente.
        // NOTA: Se non lo facessi qui, il compilatore cercherebbe un 
        // costruttore vuoto Pad() o Palla() che non ho definito.
        padDX(larghezzaPad, altezzaPad, RED),
        padSX(larghezzaPad, altezzaPad, BLUE),
        palla(15, WHITE)

        // Il corpo { } può essere usato per inizializzare attributi
        // dopo la creazione dal costruttore
        {   
            //centro campo
            palla.setPos((float)larghezzaCampo/2, (float)altezzaCampo/2);
            
            //direzione x random a destra o a sinistra
            //0: sinistra, 1: destra
            if (GetRandomValue(0, 1)) {
                //1
                angolo = 0;
            } else {
                //0
                angolo = 180;
            }

            //pads
            int centroYPad = (float)altezzaCampo/2-(float)altezzaPad/2;
            padSX.setPos(0, centroYPad);
            padDX.setPos(larghezzaCampo-larghezzaPad, centroYPad);
        };
    

    void Disegna() {
        palla.Disegna();
        padDX.Disegna();
        padSX.Disegna();

    }

    void AggiornaPalla() {
        int velocita = 300; //pixel al secondo

        //restuisce un valore float che rappresenta il tempo, espresso in secondi, 
        //trascorso tra la fine del frame precedente e l'inizio di quello attuale
        float deltaTempo = GetFrameTime();

        float nuovaX = cos(angolo*DEG2RAD) * velocita * deltaTempo + palla.getPos().x;
        float nuovaY = sin(angolo*DEG2RAD) * velocita * deltaTempo + palla.getPos().y;
        palla.setPos(nuovaX, nuovaY);
    }

    void CollisioneBordi() {
        //sopra e sotto: ribalzo
        if (palla.getPos().y - palla.getRaggio() >= altezzaCampo || palla.getPos().y - palla.getRaggio() <= 0) {
            // ...
        }
    }
    
};

#endif
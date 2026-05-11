#ifndef MOTOREGIOCO_H //se NON è ancora stato definito (if not defined) un simbolo/identificatore chiamato SNAKE_H
#define MOTOREGIOCO_H //allora definiscilo ora

#include <raylib.h>
#include "Pad.h"
#include "Palla.h"
#include <cmath>
#include <iostream>
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

    int ultimoTocco;
    int puntiDX;
    int puntiSX;
    int offsetPad;

    int velocitaPad; //pixel al secondo

    Palla palla;
    int angolo;
    int velocitaPalla; //pixel al secondo


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

        // Inizializzo gli oggetti direttamente.
        // NOTA: Se non lo facessi qui, il compilatore cercherebbe un 
        // il costruttore di Pad() o Palla() che non avevo ancora definito.
        padDX(larghezzaPad, altezzaPad, RED),
        padSX(larghezzaPad, altezzaPad, BLUE),

        //0: destra, 1: sinistra
        ultimoTocco(-1),

        puntiDX(0),
        puntiSX(0),
        offsetPad(10), //pixel
        velocitaPad(500),

        palla(15, WHITE),
        velocitaPalla(300)

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
            padSX.setPos(offsetPad, centroYPad);
            padDX.setPos(larghezzaCampo-larghezzaPad-offsetPad, centroYPad);
        };
    

    void Disegna() {
        palla.Disegna();
        padDX.Disegna();
        padSX.Disegna();
    }

    void AggiornaPalla() {//GetFrameTime restuisce un valore float che rappresenta il tempo, espresso in secondi, 
        //trascorso tra la fine del frame precedente e l'inizio di quello attuale
        //per assicurare che la palla si muova di 300 pixel in un secondo reale
        //indipendentemente dagli fps o dalla velocità del processore
        float deltaTempo = GetFrameTime();

        float nuovaX = cos(angolo*DEG2RAD) * velocitaPalla * deltaTempo + palla.getPos().x;
        float nuovaY = sin(angolo*DEG2RAD) * velocitaPalla * deltaTempo + palla.getPos().y;
        palla.setPos(nuovaX, nuovaY);
    }

    int PallaInPad() {
        //la funzione restuisce:
        //0 se la palla tocca il pad sinistro
        //1 se la palla tocca il pad destro
        //-1 se non tocca nulla

        //pad sinistro
        if (palla.getPos().x - palla.getRaggio() <= padSX.getPos().x + larghezzaPad && //asse x
            palla.getPos().y + palla.getRaggio() >= padSX.getPos().y &&                //fondo della palla, parte sup del pad
            palla.getPos().y - palla.getRaggio() <= padSX.getPos().y + altezzaPad)     //cima della palla, parte inf del pad
        {
            return 0; 
        }

        //pad destro
        if (palla.getPos().x + palla.getRaggio() >= padDX.getPos().x &&                //asse x
            palla.getPos().y + palla.getRaggio() >= padDX.getPos().y &&                //fondo della palla, parte sup del pad
            palla.getPos().y - palla.getRaggio() <= padDX.getPos().y + altezzaPad)     //cima della palla, parte inf del pad
        {
            return 1;
        }

        return -1;
    }

    void CollisionePads() {
        int ris = PallaInPad();

        if (ris != -1) {
            angolo = 180 - angolo; //cambio direzione
            ultimoTocco = ris;
        }
    }

    void CollisioneBordi() {
        //sopra e sotto: ribalzo
        if (palla.getPos().y + palla.getRaggio() >= altezzaCampo || palla.getPos().y - palla.getRaggio() <= 0) {
            angolo = -angolo; //inverto direzione
        }

        //destra e sinistra: assegno punti
        if (palla.getPos().x >= larghezzaCampo || palla.getPos().x <= 0) {
            if (ultimoTocco == 0) puntiSX++;    //sinistra
            if (ultimoTocco == 1) puntiDX++;    //destra
        }
    }

    //comandi
    bool PadFuoriBordo(Pad pad) {
        return pad.getPos().y + offsetPad >= altezzaCampo || pad.getPos().y - offsetPad <= 0;
    }

    void muoviDX() {
        bool sopra = IsKeyDown(KEY_UP);
        bool sotto = IsKeyDown(KEY_DOWN);
        float deltaTempo;

        if (sopra) {
            deltaTempo = GetFrameTime();
            float nuovaY = padDX.getPos().y - velocitaPad * deltaTempo;
            padDX.setPos(padDX.getPos().x, nuovaY);
        }
        
        if (sotto) {
            deltaTempo = GetFrameTime();
            float nuovaY = padDX.getPos().y + velocitaPad * deltaTempo;
            padDX.setPos(padDX.getPos().x, nuovaY);
        }

        if (PadFuoriBordo(padDX)) {
            padDX.setPos(padDX.getPos().x, padDX.getPos().y);
        }
    }

    void muoviSX() {
        bool sopra = IsKeyDown(KEY_W);
        bool sotto = IsKeyDown(KEY_S);
        float deltaTempo;

        if (sopra) {
            deltaTempo = GetFrameTime();
            float nuovaY = padSX.getPos().y - velocitaPad * deltaTempo;
            padSX.setPos(padSX.getPos().x, nuovaY);
        }
        
        if (sotto) {
            deltaTempo = GetFrameTime();
            float nuovaY = padSX.getPos().y + velocitaPad * deltaTempo;
            padSX.setPos(padSX.getPos().x, nuovaY);
        }

        if (PadFuoriBordo(padSX)) {
            padSX.setPos(padSX.getPos().x, padSX.getPos().y);
        }
    }

    void ControllaComandi() {
        muoviDX();
        muoviSX();
    }
    
};

#endif
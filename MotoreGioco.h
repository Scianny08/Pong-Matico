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

    bool running;

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
        angolo(0),
        velocitaPalla(600),

        running(false)

        // Il corpo { } può essere usato per inizializzare attributi
        // dopo la creazione dal costruttore
        { };
    

    void NuovaPartita() {
        if (!running) {
            //palla a centro campo
            palla.setPos((float)larghezzaCampo/2, (float)altezzaCampo/2);
            
            //posizionamento pads
            int centroYPad = (float)altezzaCampo/2-(float)altezzaPad/2;
            padSX.setPos(offsetPad, centroYPad);
            padDX.setPos(larghezzaCampo-larghezzaPad-offsetPad, centroYPad);

            //direzione x random a destra o a sinistra
            //0: verso sinistra, 1: verso destra
            if (IsKeyPressed(KEY_SPACE)) {
                if (GetRandomValue(0, 1)) {
                    //1:
                    angolo = 0;
                } else {
                    //0
                    angolo = 180;
                }

                running = true;
            }
        }
    }

    void Disegna() {
        palla.Disegna();
        padDX.Disegna();
        padSX.Disegna();
    }

    float CalcolaSpostamento(float velocita) {
        //GetFrameTime restuisce un valore float che rappresenta il tempo, espresso in secondi, 
        //trascorso tra la fine del frame precedente e l'inizio di quello attuale
        //per assicurare che la palla si muova di 300 pixel in un secondo reale
        //indipendentemente dagli fps o dalla velocità del processore
        return velocita * GetFrameTime();
    }

    void AggiornaPalla() {
        float nuovaX = cos(angolo*DEG2RAD) * CalcolaSpostamento(velocitaPalla) + palla.getPos().x;
        float nuovaY = sin(angolo*DEG2RAD) * CalcolaSpostamento(velocitaPalla) + palla.getPos().y;
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

    //Ogni pad è suddiviso in 2 parti uguali:
    // - più la palla colpisce in alto o in basso più andrà verso l'alto
    // - la palla non deve arrivare a 90 o 270 gradi
    // - più il punto in cui la palla colpisce il pad si avvicina verso il centro del pad
    // - l'angolo della palla deve avvicinarsi a 0 o 180 gradi
    void CambioDirezione(Pad &pad) {

    }

    void CollisionePads() {
        int ris = PallaInPad();

        if (ris != -1) {
            ultimoTocco = ris;
            
            //risoluzione al collision glue
            //per cui la palla può rimanere incastrata nel pad
            //ogni volta che la palla colpisce un pad la rimetto
            //al margine del pad
            float hitX;

            if (ris == 0) {
                hitX = padSX.getPos().x + larghezzaPad + palla.getRaggio() + 1;

                //cambio direzione
                CambioDirezione(padSX);

            } else {
                hitX = padDX.getPos().x - palla.getRaggio() - 1;

                //cambio direzione
                CambioDirezione(padDX);
            }

            palla.setPos(hitX, palla.getPos().y);
        }
    }

    void CollisioneBordi() {
        //sopra e sotto: ribalzo
        if (palla.getPos().y + palla.getRaggio() >= altezzaCampo || palla.getPos().y - palla.getRaggio() <= 0) {
            angolo = -angolo; //inverto direzione
        }

        //destra e sinistra: assegno punti
        //faccio uscire un poco la palla dal campo per dare l'impressione che sia stata mancata
        if (palla.getPos().x >= larghezzaCampo || palla.getPos().x <= 0) {
            if (ultimoTocco == 0) puntiSX++;    //sinistra
            if (ultimoTocco == 1) puntiDX++;    //destra

            running = false;
        }
    }

    //comandi
    bool PadFuoriBordo(Pad pad) {
        return pad.getPos().y + offsetPad >= altezzaCampo || pad.getPos().y - offsetPad <= 0;
    }

    //con la & pad diventa un riferimento
    void muoviPad(Pad &pad, KeyboardKey sopra, KeyboardKey sotto) {
        if (IsKeyDown(sopra)) {
            float nuovaY = pad.getPos().y - CalcolaSpostamento(velocitaPad);
            pad.setPos(pad.getPos().x, nuovaY);
        }
        
        if (IsKeyDown(sotto)) {
            float nuovaY = pad.getPos().y + CalcolaSpostamento(velocitaPad);
            pad.setPos(pad.getPos().x, nuovaY);
        }

        if (PadFuoriBordo(pad)) {
            pad.setPos(pad.getPos().x, pad.getPos().y);
        }
    }

    void ControllaComandi() {
        if (running) {
            muoviPad(padDX, KEY_UP, KEY_DOWN);
            muoviPad(padSX, KEY_W, KEY_S);
        }
    }
    
};

#endif
#include <raylib.h>
#include <time.h>
#include <iostream>
#include "MotoreGioco.h"
#include "Utility.h"
using namespace std;

int main () {
    int larghezzaCampo = 800;
    int altezzaCampo = 600;
    
    SetRandomSeed(time(NULL));

    MotoreGioco engine = MotoreGioco(larghezzaCampo, altezzaCampo, BLACK);

    InitWindow(larghezzaCampo, altezzaCampo, "Pong Matico");
        SetTargetFPS(60);

        while (WindowShouldClose() == false) {
            BeginDrawing();
            
            // 1. gestione eventi
            engine.CollisioneBordi();
            engine.CollisionePads();
            engine.ControllaComandi();

            // 2. aggiornare posizioni
            engine.AggiornaPalla();

            // 3. disegnare
            BeginDrawing();
                ClearBackground(BLACK);

                engine.Disegna();
                
            EndDrawing();   
        }

    CloseWindow();
    return 0;
}
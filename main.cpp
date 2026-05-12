#include <raylib.h>
#include <time.h>
#include "MotoreGioco.h"
#include <iostream>
using namespace std;

int main () {
    float larghezzaCampo = 800;
    float altezzaCampo = 600;

    const char* nomeGioco = "Pong Matico";
    float larghezzaNomeGioco;
    float nomeGiocoFontSize = 40;

    SetRandomSeed(time(NULL));

    MotoreGioco engine = MotoreGioco(larghezzaCampo, altezzaCampo, BLACK);
    
    InitWindow(larghezzaCampo, altezzaCampo, nomeGioco);
        SetTargetFPS(60);

        while (WindowShouldClose() == false) {
            engine.NuovaPartita();

            // 1. gestione eventi
            engine.ControllaComandi();
            engine.AggiornaPalla();     // prima sposta la palla...
            engine.CollisioneBordi();   // ...poi controlla dove si trova
            engine.CollisionePads();

            // 2. aggiornare posizioni
            // engine.AggiornaPalla();

            // 3. disegnare
            BeginDrawing();
                ClearBackground(BLACK);
                
                DrawLineBezier({larghezzaCampo/2, 0}, {larghezzaCampo/2, altezzaCampo}, 10, {30, 30, 30, 255});
                
                engine.Disegna();
                
                larghezzaNomeGioco = MeasureText(nomeGioco, nomeGiocoFontSize);
                DrawText(nomeGioco, larghezzaCampo/2-larghezzaNomeGioco/2, altezzaCampo*0.05, nomeGiocoFontSize, WHITE);

                
            EndDrawing();
        }

    CloseWindow();
    return 0;
}
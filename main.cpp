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
    float nomeGiocoFontSize;

    char testoPunti[10];
    float larghezzaTestoPunti;
    float testoPuntiFontSize;

    const Color GRIGIO = {30, 30, 30, 255};

    SetRandomSeed(time(NULL));

    MotoreGioco engine = MotoreGioco(larghezzaCampo, altezzaCampo, BLACK);
    
    InitWindow(larghezzaCampo, altezzaCampo, nomeGioco);
        SetTargetFPS(60);

        while (WindowShouldClose() == false) {
            engine.NuovaPartita();

            // 1. gestione eventi
            engine.ControllaComandi();

            // 2. aggiornare posizioni
            engine.AggiornaPalla();
            engine.CollisioneBordi();
            engine.CollisionePads();

            // 3. disegnare
            BeginDrawing();
                ClearBackground(BLACK);
                
                DrawLineBezier({larghezzaCampo/2, 0}, {larghezzaCampo/2, altezzaCampo}, 10, GRIGIO);
                
                DrawCircleV({larghezzaCampo/2, altezzaCampo/2}, 60 + 5, GRIGIO);
                DrawCircleV({larghezzaCampo/2, altezzaCampo/2}, 60, BLACK);
                
                DrawCircle(larghezzaCampo/2, altezzaCampo/2, engine.getRaggio()*0.9, GRIGIO);
                
                engine.Disegna();
                
                //nome gioco
                nomeGiocoFontSize = 40;
                larghezzaNomeGioco = MeasureText(nomeGioco, nomeGiocoFontSize);
                DrawText(nomeGioco, larghezzaCampo/2-larghezzaNomeGioco/2, altezzaCampo*0.05, nomeGiocoFontSize, WHITE);

                //punti sinistra
                sprintf(testoPunti, "%d", engine.getPuntiSX());
                testoPuntiFontSize = 30;
                larghezzaTestoPunti = MeasureText(testoPunti, testoPuntiFontSize);
                DrawText(testoPunti, larghezzaCampo/4-larghezzaTestoPunti, altezzaCampo*0.10, testoPuntiFontSize, engine.getPadSX().getColore());

                //punti destra
                sprintf(testoPunti, "%d", engine.getPuntiDX());
                testoPuntiFontSize = 30;
                larghezzaTestoPunti = MeasureText(testoPunti, testoPuntiFontSize);
                DrawText(testoPunti, larghezzaCampo*3/4-larghezzaTestoPunti, altezzaCampo*0.10, testoPuntiFontSize, engine.getPadDX().getColore());
                

            EndDrawing();
        }

    CloseWindow();
    return 0;
}
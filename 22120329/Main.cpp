#include "SetUp.h"
#include "Player.h"
#include "LogicGame.h"
#include "Game.h"

int main() {
    InitWindow(screenWidth, screenHeight, "2048");
    SetTargetFPS(60);

    loadFont();
    loadImage();
    LoadSound();

    initPlayer(player);

    readFileList();
    readFileResume();

    initStack(undoStack);
    initStack(redoStack);

    if (music % 2 == 1) {
        PlaySound(Music);
    }
  
    while (!WindowShouldClose())
    {

        BeginDrawing();
        drawBackGround();

        int res;
        if (inMenu) {
            if (inSetting == false && top20list == false) {
                drawMenu();

                res = HandleMenuInput();
                if (res == 2) inSetting = true;
                if (res == 3) top20list = true;
                if (res == 0) {

                    inMenu = false;
                }
            }

            if (inSetting == true) {
                solveSetting();
            }

            if (top20list == true) {
                solveTop20List();
            }

        }
        else {
            solveGamePlay();
            update();

        }

        EndDrawing();
    }

    freeTable(player.t);
    UnLoadImage();
    CloseWindow();
    CloseAudioDevice();

    return 0;
}
#include "Game.h"

void drawMenu() {
    DrawTexture(setting, 720, 10, WHITE);
    DrawTexture(highScore, 0, 140, WHITE);

    DrawRectangleRounded({ 175, 945, 450, 100 }, 0.3, 0, WHITE);
    Vector2 textSize2 = MeasureTextEx(font2, "Enter your name", 35, 0);
    Vector2 textPosition2 = { 150 + (500 - textSize2.x) / 2, 910 + (125 - textSize2.y) / 2 };
    DrawTextEx(font2, "Enter your name", textPosition2, 35, 0, purple);

    DrawRectangleRounded({ 250, 1100, 300, 70 }, 0.4, 0, purple3);
    Vector2 textSize = MeasureTextEx(font2, "PLAY", 60, 0);
    Vector2 textPosition = { 250 + (300 - textSize.x) / 2, 1100 + (70 - textSize.y) / 2 };
    DrawTextEx(font2, "PLAY", textPosition, 60, 0, WHITE);

    if (!isTypingName) {
        Vector2 textSize2 = MeasureTextEx(font2, player.name.c_str(), 35, 0);
        Vector2 textPosition2 = { 150 + (500 - textSize2.x) / 2, 945 + (125 - textSize2.y) / 2 };
        DrawTextEx(font2, player.name.c_str(), textPosition2, 35, 0, WHITE);
    }
    else {
        string displayName = player.name + "_";
        Vector2 textSize2 = MeasureTextEx(font2, displayName.c_str(), 40, 0);
        Vector2 textPosition2 = { 150 + (500 - textSize2.x) / 2, 945 + (125 - textSize2.y) / 2 };
        DrawTextEx(font2, displayName.c_str(), textPosition2, 40, 0, purple);
    }

    if (isTypingName) {
        if (IsKeyPressed(KEY_BACKSPACE) && player.name.size() > 0) {
            player.name.pop_back();
        }
        else {
            int t = 'a' - 'A';
            if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))  t = 0;
            for (int i = 'A'; i <= 'Z'; i++) if (IsKeyPressed(i)) player.name.push_back(i + t);
            for (int i = '0'; i <= '9'; i++) if (IsKeyPressed(i) && t != 0) player.name.push_back(i);
            if (IsKeyPressed(KEY_BACKSPACE)) if (!player.name.empty()) player.name.pop_back();
            if (player.name.size() > 15) player.name.pop_back();
        }
    }

    Vector2 v1 = { 400, 860 };
    Vector2 v2 = { 330, 820 };
    Vector2 v3 = { 470, 820 };
    DrawTriangle(v2, v1, v3, WHITE);

    float posY = 395, posX = 113;
    for (int i = 0; i < 5; i++) {
        DrawTextEx(font2, list[i].name.c_str(), { posX, posY }, 45, 2, WHITE);

        posY += 7;
        posX += 325;

        DrawTextEx(font2, to_string(list[i].score).c_str(), { posX, posY }, 37, 2, WHITE);
        // time
        string hour, min, sec;
        changeTime(list[i], hour, min, sec);
        string time = hour + min + sec;
        DrawTextEx(font2, time.c_str(), { 600, posY }, 37, 2, WHITE);

        posY += 81 - 7;
        posX = 113;
    }

    if (isExsistName) {
        string tmpAn = "This name is already taken, please re-enter a new name!";
        DrawTextEx(font2, tmpAn.c_str(), { 150,900 }, 30, 0, WHITE);
    }
}

void solveTop20List() {
    DrawRectangleRounded({ 100, 175, 600, 1100 }, 0.1, 0, purple3);

    float posX = 105, posY = 190;
    for (int i = 0; i < numHighScore; i++) {
        DrawRectangleRounded({ posX, posY, 295, 45 }, 0.1, 0, purple2);
        //DrawTextEx(font2, list[i].name)
        string num = to_string(i + 1) + ". ";
        DrawTextEx(font2, num.c_str(), { posX + 5, posY + 5 }, 35, 0, WHITE);
        DrawTextEx(font2, list[i].name.c_str(), { posX + 45, posY + 5 }, 35, 0, WHITE);

        DrawRectangleRounded({ posX + 300, posY, 115, 45 }, 0.1, 0, purple2);
        DrawTextEx(font2, to_string(list[i].score).c_str(), { posX + 305, posY + 5 }, 35, 0, WHITE);

        DrawRectangleRounded({ posX + 420, posY, 170, 45 }, 0.1, 0, purple2);
        string hour, min, sec;
        changeTime(list[i], hour, min, sec);
        string time = hour + min + sec;
        DrawTextEx(font2, time.c_str(), { posX + 425, posY }, 35, 0, WHITE);

        posX = 105, posY += 50;
    }

    if (CheckCollisionPointRec(GetMousePosition(), { 700, 120, 60, 60 })) {
        DrawTexture(exitSetting, 700, 120, purple2);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            top20list = false;
        }
    }
    else {
        DrawTexture(exitSetting, 700, 120, WHITE);
    }

}

int HandleMenuInput() // bổ sung tính năng sổ 20 thằng 20 list
{
    if (CheckCollisionPointRec(GetMousePosition(), { 175, 945, 450, 100 })) { // nut nhap ten
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            isTypingName = true;
            return 1;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), Rec)) { // nut setting
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return 2;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), { 250, 1100, 300, 70 })) { // nut play
        DrawRectangleRounded({ 250, 1100, 300, 70 }, 0.4, 0, WHITE);
        Vector2 textSize = MeasureTextEx(font2, "PLAY", 60, 0);
        Vector2 textPosition = { 250 + (300 - textSize.x) / 2, 1100 + (70 - textSize.y) / 2 };
        DrawTextEx(font2, "PLAY", textPosition, 60, 0, purple3);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (!belongList()) { // khong thuoc list
                for (int i = 0; i < numResume; i++) {
                    if (resume[i].name == player.name) { // thuoc resume
                        player = resume[i];
                        //initPlayer(resume[i]);
                        isPlayerResume = true;
                        deletePlayer(resume, numResume, i);
                        return 0;
                    }
                }
                player.score = 0;
                initTable(player.t, player.t.size);
                return 0; // khong thuoc resume
            }
            else { // thuoc list
                for (int i = 0; i < numResume; i++) {
                    if (resume[i].name == player.name) { // thuoc resume
                        player = resume[i];
                        isPlayerResume = true;
                        //deletePlayer(resume, numResume, i);
                        //initPlayer(resume[i]);
                        deletePlayer(list, numHighScore, i);

                        for (int j = 0; j < numHighScore; j++) {
                            if (list[j].name == player.name) {
                                deletePlayer(list, numHighScore, j);
                                return 0;
                            }
                        }
                        return 0;
                    }
                }
                player.name = "";
                isExsistName = true;
                return 1;

            }
        }
    }

    Vector2 v1 = { 400, 860 };
    Vector2 v2 = { 330, 820 };
    Vector2 v3 = { 470, 820 };

    if (CheckCollisionPointTriangle(GetMousePosition(), v1, v2, v3)) {
        DrawTriangle(v2, v1, v3, purple2);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return 3;
        }
    }

    return 1;
}

void solveSetting() {
    Vector2 d1 = { 125, 625 };
    Vector2 d2 = { 165, 550 };
    Vector2 d3 = { 165, 700 };
    Vector2 d4 = { 675, 625 };
    Vector2 d5 = { 635, 550 };
    Vector2 d6 = { 635, 700 };

    DrawRectangleRounded({ 100, 275, 600, 800 }, 0.1, 0, purple3);

    DrawTexture(exitSetting, 630, 280, WHITE);

    DrawTriangle(d2, d1, d3, WHITE);
    DrawTriangle(d4, d5, d6, WHITE);

    float posX = 215, posY = 440;
    float space = 15 - (player.t.size - 3) * 1;
    float cellSize = 1.0 * (370 - (player.t.size - 1) * space) / player.t.size;
    for (int i = 0; i < player.t.size; i++)
    {
        for (int j = 0; j < player.t.size; j++)
        {
            DrawRectangle(posX, posY, cellSize, cellSize, WHITE);
            posX += (cellSize + space);
        }
        posY += (cellSize + space);
        posX = 215;
    }

    DrawTextEx(font2, "UNDO, REDO", { 290,875 }, 70, 0, WHITE);
    DrawRectangleRounded({ 200, 875, 60, 60 }, 0.1, 0, WHITE);

    DrawTextEx(font2, "MUSIC", { 290,965 }, 70, 0, WHITE);
    DrawRectangleRounded({ 200, 965, 60, 60 }, 0.1, 0, WHITE);

    if (CheckCollisionPointTriangle(GetMousePosition(), d1, d2, d3)) {
        DrawTriangle(d2, d1, d3, purple2);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && player.t.size > 3)
        {
            player.t.size--;
        }
    }

    if (CheckCollisionPointTriangle(GetMousePosition(), d4, d5, d6)) {
        DrawTriangle(d4, d5, d6, purple2);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && player.t.size < 16)
        {
            player.t.size++;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), { 630, 280, 60, 60 })) {
        DrawTexture(exitSetting, 630, 280, purple);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            inSetting = false;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), { 200, 965, 60, 60 })) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            music++;
            if (music % 2 == 0) {
                SetSoundVolume(Music, 0.0f);
            }
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), { 200, 875, 60, 60 })) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            undoRedo++;
        }
    }

    if (music % 2 == 1) {
        DrawTexture(tich, 202, 965, WHITE);
    }
    if (undoRedo % 2 == 1) {
        DrawTexture(tich, 202, 875, WHITE);
    }
}

void drawResumeDelete() {
    DrawRectangleRounded({ 150, 300, 500, 600 }, 0.1, 0, purple3);

    float posX = 200, posY = 410;
    for (int i = 0; i < numResume; i++) {
        DrawRectangleRounded({ posX, posY, 400, 80 }, 0.2, 0, purple2);

        if (CheckCollisionPointRec(GetMousePosition(), { posX, posY, 400, 80 })) {
            DrawTextEx(font2, resume[i].name.c_str(), { posX + 30, posY + 10 }, 60, 0, purple3);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                replaceResume(i);
                resumeSave = false;
                inMenu = true;
            }
        }
        else {
            DrawTextEx(font2, resume[i].name.c_str(), { posX + 30, posY + 10 }, 60, 0, WHITE);
        }

        posY += 100;
    }
}

void drawResumeYesNo() {
    DrawRectangle(0, 0, 800, 1200, { 106,45,112,200 });
    DrawRectangleRounded({ 150, 400, 500, 400 }, 0.1, 0, purple3);

    DrawTextEx(font2, "Save the game ?", { 235,530 }, 70, 0, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), { 200, 650, 150, 80 })) { // ve menu + luu 
        DrawRectangleRounded({ 200, 650, 150, 80 }, 0.3, 0, purple);
        DrawTextEx(font2, "YES", { 240,665 }, 50, 0, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (player.score > list[19].score) {
                addPlayer();
            }
            writeFileList();

            if (!isFullResume()) {
                for (int i = 0; i < numResume; i++) {
                    if (resume[i].name == "" && resume[i].score == 0) {
                        resume[i] = player;
                        inMenu = true;
                        resumeSave = false;
                        return;
                    }
                }
            }
            else {
                drawResumeDelete();
            }

            writeFileResume();
        }
    }
    else {
        DrawRectangleRounded({ 200, 650, 150, 80 }, 0.3, 0, WHITE);
        DrawTextEx(font2, "YES", { 240,665 }, 50, 0, purple);
    }


    if (CheckCollisionPointRec(GetMousePosition(), { 450, 650, 150, 80 })) {
        DrawRectangleRounded({ 450, 650, 150, 80 }, 0.3, 0, purple);
        DrawTextEx(font2, "NO", { 500,665 }, 50, 0, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (player.score > list[19].score) {
                addPlayer();
            }
            
            for (int i = 0; i < numResume; i++) {
                if (resume[i].name == player.name) {
                    deletePlayer(resume, numResume, i);
                }
            }
            writeFileList();
            resumeSave = false;
            inMenu = true;
        }
    }
    else {
        DrawRectangleRounded({ 450, 650, 150, 80 }, 0.3, 0, WHITE);
        DrawTextEx(font2, "NO", { 500,665 }, 50, 0, purple);
    }


    if (CheckCollisionPointRec(GetMousePosition(), { 590, 410, 60, 60 }))
    {
        DrawTexture(exitSetting, 590, 410, purple);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            resumeSave = false;
        }
    }
    else {
        DrawTexture(exitSetting, 590, 410, WHITE);
    }
}

void drawResumeContinue() {
    DrawRectangle(0, 0, 800, 1200, { 106,45,112,200 });
    DrawRectangleRounded({ 150, 400, 500, 400 }, 0.1, 0, purple3);
   
    DrawTextEx(font2, "Continue your last game ?", { 165,530 }, 60, 0, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), { 200, 650, 150, 80 })) {
        DrawRectangleRounded({ 200, 650, 150, 80 }, 0.3, 0, purple);
        DrawTextEx(font2, "YES", { 240,665 }, 50, 0, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // xac nhan choi cua resume
        {
            isPlayerResume = false;
        }
    }
    else {
        DrawRectangleRounded({ 200, 650, 150, 80 }, 0.3, 0, WHITE);
        DrawTextEx(font2, "YES", { 240,665 }, 50, 0, purple);
    }

    if (CheckCollisionPointRec(GetMousePosition(), { 450, 650, 150, 80 })) {
        DrawRectangleRounded({ 450, 650, 150, 80 }, 0.3, 0, purple);
        DrawTextEx(font2, "NO", { 500,665 }, 50, 0, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // xac nhan init lai ng choi resume
        {
            initPlayer(player);
            isPlayerResume = false;
        }
    }
    else {
        DrawRectangleRounded({ 450, 650, 150, 80 }, 0.3, 0, WHITE);
        DrawTextEx(font2, "NO", { 500,665 }, 50, 0, purple);
    }
}

void solveGamePlay()
{
    if (!isPlayerResume) {

        start = GetTime();

        if (!resumeSave) {

            Rectangle tmp = { 35, 345, 730, 730 };

            float startX = 70; // Vị trí bắt đầu vẽ theo trục x
            float startY = 380; // Vị trí bắt đầu vẽ theo trục y

            player.sec = -endTime + start + tmpTime;

            string hour, min, sec;
            changeTime(player, hour, min, sec);
            string time = hour + min + sec;
            DrawTextEx(font2, time.c_str(), { 20, 50 }, 30, 0, WHITE);

            float spacing = 30 - (player.t.size - 3) * 2;
            double cellSize = (double)(660 - (player.t.size - 1) * spacing) / player.t.size;

            for (int i = 0; i < player.t.size; i++)
            {
                for (int j = 0; j < player.t.size; j++)
                {
                    int posX = startX + j * (cellSize + spacing);
                    int posY = startY + i * (cellSize + spacing);

                    if (player.t.map[i][j] != 0) {
                        int mu = log2(player.t.map[i][j]);
                        while (mu > 11) mu -= 11;

                        Rectangle tmp2 = { posX, posY, cellSize, cellSize };
                        DrawRectangleRounded(tmp2, 0.05, 0, num[mu - 1]);

                        string a = to_string(player.t.map[i][j]);
                        float fontSize = 100;
                        Vector2 textSize = MeasureTextEx(font2, a.c_str(), fontSize, 0);

                        // Điều chỉnh kích thước phông chữ cho phù hợp với ô
                        while ((textSize.x > cellSize || textSize.y > cellSize) && fontSize > 0)
                        {
                            fontSize -= 1;
                            textSize = MeasureTextEx(font2, a.c_str(), fontSize, 0);
                        }

                        Vector2 textPosition = { posX + (cellSize - textSize.x) / 2, posY + (cellSize - textSize.y) / 2 };
                        DrawTextEx(font2, a.c_str(), textPosition, fontSize, 0, WHITE);
                    }
                    else {
                        Rectangle tmp2 = { posX, posY, cellSize, cellSize };
                        DrawRectangleRounded(tmp2, 0.05, 0, purple2);
                    }
                }
            }

            // Home + undo redo
            if (validPress) {
                DrawRectangleRounded({ 70, 1080, 80, 80 }, 0.3, 0, WHITE); // bam nut home => xuwr ly RESUME here
                if (CheckCollisionPointRec(GetMousePosition(), { 70, 1080, 80, 80 })) {
                    DrawRectangleRounded({ 70, 1080, 80, 80 }, 0.3, 0, purple2);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        /*if (player.score > list[19].score) {
                            addPlayer();
                        }
                        writeFileList();*/

                        // ve bang xem co muon luu resume thang player

                        //DrawRectangleRounded({ 100, 200, 500, 500 }, 0.1, 0, purple2);

                        endTime = GetTime();
                        resumeSave = true;

                        //endTime = GetTime();
                        //inMenu = true;
                    }
                }

                DrawTexture(home, 70, 1080, WHITE);
                if (undoRedo % 2 == 1) {
                    if (CheckCollisionPointRec(GetMousePosition(), { 650, 1080, 80, 80 })) { // REDO
                        DrawRectangleRounded({ 650, 1080, 80, 80 }, 0.3, 0, purple2);
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        {
                            redo(player.t, undoStack, redoStack);
                        }
                    }
                    else {
                        DrawRectangleRounded({ 650, 1080, 80, 80 }, 0.3, 0, WHITE);
                    }
                    DrawTexture(re, 650, 1080, WHITE);

                    if (CheckCollisionPointRec(GetMousePosition(), { 550, 1080, 80, 80 })) { // UNDO
                        DrawRectangleRounded({ 550, 1080, 80, 80 }, 0.3, 0, purple2);
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        {
                            undo(player.t, undoStack, redoStack);
                        }
                    }
                    else {
                        DrawRectangleRounded({ 550, 1080, 80, 80 }, 0.3, 0, WHITE);
                    }
                    DrawTexture(un, 550, 1080, WHITE);
                }
            }
            


            // ve diem thoi gian o day
            DrawTextEx(font2, "SCORE", { 300, 150 }, 100, 0, WHITE);

            string score = to_string(player.score);

            // 0, 170, 800, 100
            Vector2 textSize = MeasureTextEx(font2, score.c_str(), 60, 0);
            Vector2 textPosition = { 0 + (800 - textSize.x) / 2, 220 + (100 - textSize.y) / 2 };
            DrawTextEx(font2, score.c_str(), textPosition, 60, 0, WHITE);

            // Do here
            if (check == false) {
                if (winGame(player.t)) {
                    check2 = true;
                    validPress = false;
                }
            }
            if (check2) {
                DrawRectangle(0, 0, 800, 1200, { 106,45,112,200 });
                DrawRectangleRounded({ 100, 300, 600, 600 }, 0.1, 0, purple3);
                DrawTexture(win, 70, 300, WHITE);

                if (CheckCollisionPointRec(GetMousePosition(), { 150, 800, 150, 80 })) {
                    DrawRectangleRounded({ 150, 800, 150, 80 }, 0.3, 0, purple);
                    DrawTextEx(font2, "YES", { 190,815 }, 50, 0, WHITE);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        validPress = true;
                        check = true;
                        check2 = false;
                    }
                }
                else {
                    DrawRectangleRounded({ 150, 800, 150, 80 }, 0.3, 0, WHITE);
                    DrawTextEx(font2, "YES", { 190,815 }, 50, 0, purple);
                }


                if (CheckCollisionPointRec(GetMousePosition(), { 500, 800, 150, 80 })) {
                    DrawRectangleRounded({ 500, 800, 150, 80 }, 0.3, 0, purple);
                    DrawTextEx(font2, "NO", { 550,815 }, 50, 0, WHITE);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        addPlayer();
                        writeFileList();
                        validPress = true;
                        inMenu = true;
                    }
                }
                else {
                    DrawRectangleRounded({ 500, 800, 150, 80 }, 0.3, 0, WHITE);
                    DrawTextEx(font2, "NO", { 550,815 }, 50, 0, purple);
                }
            }

            if (gameOver(player.t)) {
                validPress = false;
                DrawRectangle(0, 0, 800, 1200, { 106,45,112,200 });
                DrawRectangleRounded({ 100, 300, 600, 600 }, 0.1, 0, purple3);
                DrawTexture(loss, 70, 300, WHITE);

                if (CheckCollisionPointRec(GetMousePosition(), { 500, 800, 150, 80 })) {
                    DrawRectangleRounded({ 500, 800, 150, 80 }, 0.3, 0, purple);
                    DrawTextEx(font2, "YES", { 545,815 }, 50, 0, WHITE);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        validPress = true;
                        if (player.score > list[19].score) {
                            addPlayer();
                        }
                        for (int i = 0; i < numResume; i++) {
                            if (resume[i].name == player.name) {
                                deletePlayer(resume, numResume, i);
                            }
                        }

                        writeFileList();
                        inMenu = true;
                    }
                }
                else {
                    DrawRectangleRounded({ 500, 800, 150, 80 }, 0.3, 0, WHITE);
                    DrawTextEx(font2, "YES", { 545,815 }, 50, 0, purple);
                }


            }
        }

        else { // bam nut home


            /*if (!isFullResumeCheck) {
                drawResumeYesNo();
            }

            if (isFullResumeCheck) {
                drawResumeDelete();
            }*/



            //bool check = isFullResume();
            //if (!check) { // chuwa day 
            //    drawResumeYesNo();
            //}
            //else { // day
            //    drawResumeYesNo();
            //}
            drawResumeYesNo();
            //resumeSave = true;
        }
    }
    else {
        drawResumeContinue();
        tmpTime = player.sec;
    }


}

void update()
{
    Table previousTable;
    copyTable(player.t, previousTable);

    if (validPress) {
        if (IsKeyPressed(KEY_UP))
        {
            if (music % 2 == 1) {
                PlaySound(Press);
            }
            goUp(player.t, undoStack, redoStack);
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            if (music % 2 == 1) {
                PlaySound(Press);
            }
            goDown(player.t, undoStack, redoStack);
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            if (music % 2 == 1) {
                PlaySound(Press);
            }
            goLeft(player.t, undoStack, redoStack);
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            if (music % 2 == 1) {
                PlaySound(Press);
            }
            goRight(player.t, undoStack, redoStack);
        }
    }
    
    if (!tablesEqual(player.t, previousTable)) {
        randomNumber(player.t);

        player.score = 0;
        calScore();
    }

    freeTable(previousTable);
}
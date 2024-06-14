#include "SetUp.h"

// Định nghĩa các hằng số và biến
const int screenWidth = 800;
const int screenHeight = 1200;

time_t start;
time_t endTime;
int tmpTime = 0;

Font font2, font;
Sound Music, Press;

const int last = 120;
int color_top2[] = { 110,231,221,255 };
int color_bot2[] = { 230,249,247,255 };
int color_top[] = { 62,14,74,255 };
int color_bot[] = { 23,11,26,255 };

long double sin_start, sin_start2;

Rectangle sourceRec;
Rectangle destRec;
Vector2 origin;
float rotation = 0;
float Width, Height, frameWidth, frameHeight;
int deltaship = 0;

float roundness = 0.5f;
float segments = 0.3f;
Rectangle Rec = { (float)720 ,(float)10,(float)70,(float)70 };
unsigned char g[4];

Texture ship, setting, tich, exitSetting, un, re, home, highScore, win, loss;

Color purple3 = { 103,57,166,255 };
Color purple = { 62,14,74,255 };
Color purple2 = { 106,45,112,100 };

Color cl1 = { 238 ,238, 0,205 };
Color cl2 = { 118 ,238, 0,205 };
Color cl3 = { 0 ,238, 118,205 };
Color cl4 = { 0, 229 ,238,205 };
Color cl5 = { 0 ,191, 255,205 };
Color cl6 = { 28, 134 ,238,205 };
Color cl7 = { 132 ,112, 255,205 };
Color cl8 = { 205, 0 ,205,205 };
Color cl9 = { 238, 58, 140,205 };
Color cl10 = { 238, 0 ,0,205 };
Color cl11 = { 255, 127, 0,205 };

Color num[] = { cl1, cl2,cl3,cl4,cl5,cl6,cl7,cl8,cl9,cl10,cl11 };

bool isTypingName = false;
bool isExsistName = false;
bool inMenu = true;
bool inSetting = false;
bool top20list = false;
bool resumeSave = false;
bool check = false;
bool check2 = false;
bool isPlayerResume = false;
int undoRedo = 0, music = 1;
int numResume = 5;
int numHighScore = 20;
const int maxNameLength = 20;
bool validPress = true;

Stack undoStack;
Stack redoStack;

Player player;
Player* list;
Player* resume;

// Định nghĩa hàm
long double get_sin(long double x) {
    return 106.0 + (10.0 * sin(((x) / (55.0))));
}

long double get_sin2(long double x) {
    return 103.0 + (13.0 * sin(((x) / (45.0))));
}

void loadFont() {
    font = LoadFontEx("./SetUp/SNAP____.ttf", 96, 0, 0);
    GenTextureMipmaps(&font.texture);
    font2 = LoadFontEx("./SetUp/CabinCondensed-SemiBold.ttf", 96, 0, 0);
    GenTextureMipmaps(&font2.texture);
}

void loadImage() {
    Image image;
    image = LoadImage("./SetUp/Ship.png");
    ship = LoadTextureFromImage(image);

    image = LoadImage("./SetUp/Setting.png");
    setting = LoadTextureFromImage(image);

    image = LoadImage("./SetUp/Tich.png");
    tich = LoadTextureFromImage(image);

    image = LoadImage("./SetUp/ExitSetting.png");
    exitSetting = LoadTextureFromImage(image);

    image = LoadImage("./SetUp/Undo.png");
    un = LoadTextureFromImage(image);

    image = LoadImage("./SetUp/Redo.png");
    re = LoadTextureFromImage(image);

    image = LoadImage("./SetUp/Home.png");
    home = LoadTextureFromImage(image);

    image = LoadImage("./SetUp/HighScore.png");
    highScore = LoadTextureFromImage(image);

    image = LoadImage("./SetUp/win.png");
    win = LoadTextureFromImage(image);

    image = LoadImage("./SetUp/loss.png");
    loss = LoadTextureFromImage(image);

    ship.width /= 3;
    ship.height /= 3;
    Width = 800;
    Height = 120;
    frameWidth = ship.width;
    frameHeight = ship.height;
    sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
    destRec = { Width / 2.0f, Height / 2.0f, frameWidth * 2.0f, frameHeight * 2.0f };
    origin = { (float)frameWidth, (float)frameHeight };

    UnloadImage(image);
}

void LoadSound()
{
    InitAudioDevice();
    Music = LoadSound("./SetUp/Music.mp3");
    Press = LoadSound("./SetUp/Press.mp3");
}

void UnLoadImage() {
    UnloadTexture(ship);
    UnloadTexture(setting);
    UnloadTexture(tich);
    UnloadTexture(exitSetting);
    UnloadTexture(un);
    UnloadTexture(re);
    UnloadTexture(home);
    UnloadTexture(highScore);
    UnloadTexture(win);
    UnloadTexture(loss);

}

void drawBackGround() {
    for (int i = 1; i <= 130; i++) {
        for (int j = 0; j < 4; j++) g[j] = color_top2[j] - (1.0 * i * ((1.0 * color_top2[j] - color_bot2[j]) / (last * 1.0)));
        DrawRectangle(0, i, 800, 1, { g[0],g[1],g[2],g[3] });
    }

    int ok = 0;
    for (int i = 85; i <= 115; i++) {
        for (int j = 0; j < 4; j++) g[j] = color_top[j] - (1.0 * i * ((1.0 * color_top[j] - color_bot[j]) / 1200.0));
        int d = 0;
        for (int j = 0; j < 800; j++) {
            if (i > get_sin2(sin_start2 * 1.0 + j)) {
                d++;
                DrawRectangle(j, i, 1, 1, { 134,85,140,255 });
            }
        }
        if (ok == 1) {
            DrawRectangle(0, i, 800, 1, { 134,85,140,255 });
        }
        if (d == 601) ok = 1;
    }

    rotation = -(1.0 * (get_sin(sin_start * 1.0 + 255 - deltaship) - 93)) / ((112 - 93) * 1.0) * 10.0 + 5.0;
    DrawTexturePro(ship, sourceRec, destRec, origin, (float)rotation, WHITE);
    ok = 0;

    for (int i = 90; i <= 115; i++) {
        for (int j = 0; j < 4; j++) g[j] = color_top[j] - (1.0 * i * ((1.0 * color_top[j] - color_bot[j]) / 1200.0));
        int d = 0;
        for (int j = 0; j < 800; j++) {
            if (i > get_sin(sin_start * 1.0 + j)) {
                d++;
                DrawRectangle(j, i, 1, 1, { g[0],g[1],g[2],g[3] });
            }
        }
        if (ok == 1) {
            DrawRectangle(0, i, 800, 1, { g[0],g[1],g[2],g[3] });
        }
        if (d == 801) ok = 1;
    }

    for (int i = 116; i <= 116; i++) {
        for (int j = 0; j < 4; j++) g[j] = color_top[j] - (1.0 * i * ((1.0 * color_top[j] - color_bot[j]) / 1200.0));
        DrawRectangle(0, i, 800, 1200 - 112, { g[0],g[1],g[2],g[3] });
    }

    sin_start -= 1 * 6;
    sin_start2 -= 0.7 * 6;
    if (fabs(get_sin(0) - get_sin(sin_start)) <= 0.1 && fabs(get_sin(50) - get_sin(sin_start + 50)) <= 0.1) {
        sin_start = 0;
    }

    if (fabs(get_sin2(0) - get_sin2(sin_start2)) < 0.1 && fabs(get_sin2(50) - get_sin2(sin_start2 + 50)) < 0.1) {
        sin_start2 = 0;
    }
}

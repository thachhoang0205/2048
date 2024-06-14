#pragma once
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// Khai báo các hằng số, biến và hàm
extern const int screenWidth;
extern const int screenHeight;

// Các biến liên quan đến thời gian
extern time_t start;
extern time_t endTime;
extern int tmpTime;

// Phông chữ và âm thanh
extern Font font2, font;
extern Sound Music, Press;

// Màu sắc và các biến liên quan đến tàu
extern const int last;
extern int color_top2[];
extern int color_bot2[];
extern int color_top[];
extern int color_bot[];
extern long double sin_start, sin_start2;
extern Rectangle sourceRec, destRec;
extern Vector2 origin;
extern float rotation, Width, Height, frameWidth, frameHeight;
extern int deltaship;

// Các biến liên quan đến giao diện người dùng
extern float roundness, segments;
extern Rectangle Rec;
extern unsigned char g[4];

// Các texture
extern Texture ship, setting, tich, exitSetting, un, re, home, highScore, win, loss;

// Màu sắc
extern Color purple3, purple, purple2;
extern Color cl1, cl2, cl3, cl4, cl5, cl6, cl7, cl8, cl9, cl10, cl11;
extern Color num[];

// Biến boolean
extern bool isTypingName, isExsistName, inMenu, inSetting, top20list;
extern bool resumeSave, check, check2, isPlayerResume, validPress;
extern int undoRedo, music;
extern int numResume, numHighScore;
extern const int maxNameLength;

// Khai báo hàm
long double get_sin(long double x);
long double get_sin2(long double x);
void loadFont();
void loadImage();
void LoadSound();
void UnLoadImage();
void drawBackGround();

// Khai báo struct và biến liên quan
struct Table {
    int** map;
    int size;
};

struct Node {
    Table table;
    Node* next;
};

struct Stack {
    Node* top;
};

extern Stack undoStack;
extern Stack redoStack;

struct Player {
    string name;
    Table t;
    int score;
    int sec;
};

extern Player player;
extern Player* list;
extern Player* resume;

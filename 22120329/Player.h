#pragma once
#include "SetUp.h"
#include "LogicGame.h"

void calScore();
void initPlayer(Player& a);
void deletePlayer(Player*& arr, int n, int pos);
void changeTime(Player a, string& hour, string& min, string& sec);

void initPlayers(Player*& arr, const int n);
void readFileList();
void writeFileList();
bool belongList();
bool isHigherRanking(Player a, Player b);
void addPlayer();

bool belongResume();
bool isFullResume();
void pushInResume();
void replaceResume(int pos);
void writeFileResume();
void readFileResume();


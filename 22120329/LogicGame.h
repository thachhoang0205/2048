#pragma once
#include "SetUp.h"

int getRandomNumber();
void initTable(Table& t, int sizeT);
void randomNumber(Table& t);
void copyTable(const Table& src, Table& dest);
void freeTable(Table& t);
bool tablesEqual(const Table& t1, const Table& t2);
void initStack(Stack& s);
bool isEmpty(Stack s);
void push(Stack& s, Table t);
Table pop(Stack& s);
Table peek(Stack& s);
void saveState(Table& t, Stack& s);
void clearStack(Stack& s);
void goUp(Table& t, Stack& undoStack, Stack& redoStack);
void goDown(Table& t, Stack& undoStack, Stack& redoStack);
void goLeft(Table& t, Stack& undoStack, Stack& redoStack);
void goRight(Table& t, Stack& undoStack, Stack& redoStack);
void undo(Table& t, Stack& undoStack, Stack& redoStack);
void redo(Table& t, Stack& undoStack, Stack& redoStack);
bool gameOver(Table t);
bool winGame(Table t);

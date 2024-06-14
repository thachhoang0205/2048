#include "LogicGame.h"

int getRandomNumber() {
    int randomValue = rand() % 100; // Lấy số ngẫu nhiên từ 0 đến 99
    return (randomValue < 90) ? 2 : 4; // 90% khả năng là 2, 10% khả năng là 4
}

void initTable(Table& t, int sizeT)
{
    t.size = sizeT;

    t.map = new int* [t.size];
    for (int i = 0; i < t.size; i++)
    {
        t.map[i] = new int[t.size];
        for (int j = 0; j < t.size; j++)
        {
            t.map[i][j] = 0;
        }
    }

    srand(time(0));
    int a = rand() % t.size, b = rand() % t.size;
    t.map[a][b] = getRandomNumber();

    int c, d;
    do {
        c = rand() % t.size;
        d = rand() % t.size;
    } while (c == a && d == b);

    t.map[c][d] = getRandomNumber();
}

void randomNumber(Table& t)
{
    int pos1, pos2;
    srand(time(0));
    do
    {
        pos1 = rand() % t.size;
        pos2 = rand() % t.size;
    } while (t.map[pos1][pos2] != 0);

    t.map[pos1][pos2] = getRandomNumber();
}

void copyTable(const Table& src, Table& dest) {
    dest.size = src.size;
    dest.map = new int* [src.size];
    for (int i = 0; i < src.size; i++) {
        dest.map[i] = new int[src.size];
        for (int j = 0; j < src.size; j++) {
            dest.map[i][j] = src.map[i][j];
        }
    }
}

void freeTable(Table& t) {
    for (int i = 0; i < t.size; i++) {
        delete[] t.map[i];
    }
    delete[] t.map;
}

bool tablesEqual(const Table& t1, const Table& t2) {
    if (t1.size != t2.size) return false;
    for (int i = 0; i < t1.size; i++) {
        for (int j = 0; j < t1.size; j++) {
            if (t1.map[i][j] != t2.map[i][j]) return false;
        }
    }
    return true;
}

void initStack(Stack& s) {
    s.top = nullptr;
}

bool isEmpty(Stack s) {
    return s.top == nullptr;
}

void push(Stack& s, Table t) {
    Node* newNode = new Node();
    copyTable(t, newNode->table);
    newNode->next = s.top;
    s.top = newNode;
}

Table pop(Stack& s) {
    if (isEmpty(s)) {
        Table emptyTable;
        emptyTable.size = 0;
        emptyTable.map = nullptr;
        return emptyTable;
    }
    Node* temp = s.top;
    s.top = s.top->next;
    Table poppedTable = temp->table;
    delete temp;
    return poppedTable;
}

Table peek(Stack& s) {
    if (isEmpty(s)) {
        Table emptyTable;
        emptyTable.size = 0;
        emptyTable.map = nullptr;
        return emptyTable;
    }
    return s.top->table;
}

void saveState(Table& t, Stack& s) {
    push(s, t);
}

void clearStack(Stack& s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}

void goUp(Table& t, Stack& undoStack, Stack& redoStack)
{
    saveState(t, undoStack);
    clearStack(redoStack);

    for (int x = 0; x < t.size; x++)
    {
        for (int y = 1; y < t.size; y++)
        {
            if (t.map[y][x] != 0)
            {
                int ty = y;
                while (ty > 0 && t.map[ty - 1][x] == 0)
                {
                    swap(t.map[ty][x], t.map[ty - 1][x]);
                    ty--;
                }
                if (ty > 0 && t.map[ty - 1][x] == t.map[ty][x])
                {
                    t.map[ty - 1][x] *= 2;
                    t.map[ty][x] = 0;
                }
            }
        }
    }
}

void goDown(Table& t, Stack& undoStack, Stack& redoStack)
{
    saveState(t, undoStack);
    clearStack(redoStack);

    for (int x = 0; x < t.size; x++)
    {
        for (int y = t.size - 2; y >= 0; y--)
        {
            if (t.map[y][x] != 0)
            {
                int ty = y;
                while (ty < t.size - 1 && t.map[ty + 1][x] == 0)
                {
                    swap(t.map[ty][x], t.map[ty + 1][x]);
                    ty++;
                }
                if (ty < t.size - 1 && t.map[ty + 1][x] == t.map[ty][x])
                {
                    t.map[ty + 1][x] *= 2;
                    t.map[ty][x] = 0;
                }
            }
        }
    }
}

void goLeft(Table& t, Stack& undoStack, Stack& redoStack)
{
    saveState(t, undoStack);
    clearStack(redoStack);

    for (int y = 0; y < t.size; y++)
    {
        for (int x = 1; x < t.size; x++)
        {
            if (t.map[y][x] != 0)
            {
                int tx = x;
                while (tx > 0 && t.map[y][tx - 1] == 0)
                {
                    swap(t.map[y][tx], t.map[y][tx - 1]);
                    tx--;
                }
                if (tx > 0 && t.map[y][tx - 1] == t.map[y][tx])
                {
                    t.map[y][tx - 1] *= 2;
                    t.map[y][tx] = 0;
                }
            }
        }
    }
}

void goRight(Table& t, Stack& undoStack, Stack& redoStack)
{
    saveState(t, undoStack);
    clearStack(redoStack);

    for (int y = 0; y < t.size; y++)
    {
        for (int x = t.size - 2; x >= 0; x--)
        {
            if (t.map[y][x] != 0)
            {
                int tx = x;
                while (tx < t.size - 1 && t.map[y][tx + 1] == 0)
                {
                    swap(t.map[y][tx], t.map[y][tx + 1]);
                    tx++;
                }
                if (tx < t.size - 1 && t.map[y][tx + 1] == t.map[y][tx])
                {
                    t.map[y][tx + 1] *= 2;
                    t.map[y][tx] = 0;
                }
            }
        }
    }
}

void undo(Table& t, Stack& undoStack, Stack& redoStack) {
    if (!isEmpty(undoStack)) {
        saveState(t, redoStack);
        t = pop(undoStack);
    }
}

void redo(Table& t, Stack& undoStack, Stack& redoStack) {
    if (!isEmpty(redoStack)) {
        saveState(t, undoStack);
        t = pop(redoStack);
    }
}

bool gameOver(Table t) {
    for (int i = 0; i < t.size; ++i) {
        for (int j = 0; j < t.size; ++j) {
            if (t.map[i][j] == 0) {
                return false;
            }
        }
    }

    for (int i = 0; i < t.size; ++i) {
        for (int j = 0; j < t.size; ++j) {
            if ((i < t.size - 1 && t.map[i][j] == t.map[i + 1][j]) ||
                (j < t.size - 1 && t.map[i][j] == t.map[i][j + 1])) {
                return false;
            }
        }
    }

    return true;
}

bool winGame(Table t) {
    for (int i = 0; i < t.size; ++i) {
        for (int j = 0; j < t.size; ++j) {
            if (t.map[i][j] == 2048) {
                return true;
            }
        }
    }
    return false;
}

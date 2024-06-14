#include "Player.h"

void calScore() {
    for (int i = 0; i < player.t.size; i++) {
        for (int j = 0; j < player.t.size; j++) {
            player.score += player.t.map[i][j];
        }
    }
}

void initPlayer(Player& a) {
    a.name = "";
    a.score = 0;
    a.sec = 0;
    a.t.size = 4;
    initTable(a.t, a.t.size);
}

void deletePlayer(Player*& arr, int n, int pos) {
    for (int i = pos; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    initPlayer(arr[n - 1]);
}

void changeTime(Player a, string& hour, string& min, string& sec) {
    int h = a.sec / 3600;
    int m = (a.sec - 3600 * h) / 60;
    int s = a.sec - 3600 * h - 60 * m;

    if (m < 10) min = '0' + to_string(m) + ':';
    else min = to_string(m) + ':';

    if (s < 10) sec = '0' + to_string(s);
    else sec = to_string(s);

    hour = to_string(h) + ':';
}

void initPlayers(Player*& arr, const int n) {
    arr = new Player[n];
    for (int i = 0; i < n; i++) {
        initPlayer(arr[i]);
    }
}

void readFileList() {
    ifstream inFile("Top20List.bin", ios::binary);

    if (!inFile) {
        cerr << "Error opening file for reading" << endl;
        return;
    }

    // Đọc số lượng người chơi từ file
    inFile.read(reinterpret_cast<char*>(&numHighScore), sizeof(numHighScore));
    list = new Player[numHighScore];

    for (int i = 0; i < numHighScore; ++i) {
        Player& player = list[i];

        // Đọc độ dài tên và tên
        int nameLength;
        inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        player.name.resize(nameLength);
        inFile.read(&player.name[0], nameLength);

        // Đọc điểm số và thời gian
        inFile.read(reinterpret_cast<char*>(&player.score), sizeof(player.score));
        inFile.read(reinterpret_cast<char*>(&player.sec), sizeof(player.sec));
    }

    inFile.close();
}

void writeFileList() {
    ofstream outFile("Top20List.bin", ios::binary);

    if (!outFile) {
        cerr << "Error opening file for writing" << endl;
        return;
    }

    // Ghi số lượng người chơi vào file
    outFile.write(reinterpret_cast<char*>(&numHighScore), sizeof(numHighScore));

    for (int i = 0; i < numHighScore; ++i) {
        Player& player = list[i];

        // Ghi độ dài tên và tên
        int nameLength = player.name.size();
        outFile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        outFile.write(player.name.c_str(), nameLength);

        // Ghi điểm số và thời gian
        outFile.write(reinterpret_cast<char*>(&player.score), sizeof(player.score));
        outFile.write(reinterpret_cast<char*>(&player.sec), sizeof(player.sec));
    }

    outFile.close();
}

bool belongList() {
    for (int i = 0; i < numHighScore; i++) {
        if (list[i].name == player.name) return true;
    }
    return false;
}

bool isHigherRanking(Player a, Player b) {
    if (a.score > b.score) return true;

    if (a.score == b.score) {
        if (a.sec < b.sec) return true;
    }

    return false;
}

void addPlayer() {
    if (list[0].name == "" && list[0].score == 0) {
        list[0] = player;
        return;
    }

    if (isHigherRanking(player, list[0])) {
        for (int j = numHighScore - 2; j >= 0; j--) {
            list[j + 1] = list[j];
        }
        list[0] = player;
        return;
    }

    for (int i = numHighScore - 1; i >= 1; i--) {
        if (isHigherRanking(player, list[i]) && isHigherRanking(list[i - 1], player)) {
            for (int j = numHighScore - 2; j >= i; j--) {
                list[j + 1] = list[j];
            }
            list[i] = player;
            return;
        }
    }

}

bool belongResume() {
    for (int i = 0; i < numResume; i++) {
        if (resume[i].name == player.name) return true;
    }
    return false;
}

bool isFullResume() {
    return resume[numResume - 1].name != "" && resume[numResume - 1].score != 0;
}

void pushInResume() {
    for (int i = 0; i < numResume; i++) {
        if (resume[i].name == "" && resume[i].score == 0) {
            resume[i] = player;
            return;
        }
    }
}

void replaceResume(int pos) {
    resume[pos] = player;
}

void writeFileResume() {
    ofstream outFile("Resume.bin", ios::binary);
    if (!outFile) {
        cerr << "Cannot open file for writing: input.bin" << endl;
        return;
    }

    outFile.write(reinterpret_cast<char*>(&numResume), sizeof(numResume));

    for (int i = 0; i < numResume; i++) {
        int nameLength = resume[i].name.size();
        outFile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        outFile.write(resume[i].name.c_str(), nameLength);

        outFile.write(reinterpret_cast<char*>(&resume[i].score), sizeof(resume[i].score));
        outFile.write(reinterpret_cast<char*>(&resume[i].sec), sizeof(resume[i].sec));

        outFile.write(reinterpret_cast<char*>(&resume[i].t.size), sizeof(resume[i].t.size));
        for (int j = 0; j < resume[i].t.size; j++) {
            for (int k = 0; k < resume[i].t.size; k++) {
                outFile.write(reinterpret_cast<char*>(&resume[i].t.map[j][k]), sizeof(resume[i].t.map[j][k]));
            }
        }
    }

    outFile.close();
}

void readFileResume() {
    ifstream inFile("Resume.bin", ios::binary);

    if (!inFile) {
        cerr << "Cannot open file for reading: input.bin" << endl;
        return;
    }

    inFile.read(reinterpret_cast<char*>(&numResume), sizeof(numResume));
    resume = new Player[numResume];

    for (int i = 0; i < numResume; ++i) {
        // Đọc độ dài tên và tên
        int nameLength;
        inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        resume[i].name.resize(nameLength);
        inFile.read(&resume[i].name[0], nameLength);

        // Đọc điểm số và thời gian
        inFile.read(reinterpret_cast<char*>(&resume[i].score), sizeof(resume[i].score));
        inFile.read(reinterpret_cast<char*>(&resume[i].sec), sizeof(resume[i].sec));
        inFile.read(reinterpret_cast<char*>(&resume[i].t.size), sizeof(resume[i].t.size));

        // Khởi tạo bảng cho người chơi
        initTable(resume[i].t, resume[i].t.size);

        // Đọc dữ liệu của bảng từ tệp
        for (int j = 0; j < resume[i].t.size; j++) {
            for (int k = 0; k < resume[i].t.size; k++) {
                inFile.read(reinterpret_cast<char*>(&resume[i].t.map[j][k]), sizeof(resume[i].t.map[j][k]));
            }
        }
    }

    inFile.close();
}




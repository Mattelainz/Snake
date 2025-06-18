#ifndef SCORE_BOARD_HPP
#define SCORE_BOARD_HPP

#include <fstream>
#include <vector>


using namespace std;

struct DataPlayer{
    char name[4];
    int score;
};

struct Scoreboard {
    DataPlayer levelScores[30][5];
};

void serialize(Scoreboard scoreboard);
void deserialize(Scoreboard*scoreboard);
void saveScore(int level, DataPlayer score, Scoreboard*scoreboard);

vector<DataPlayer> readFile(const string& filename);
void appendFile(const string& filename, DataPlayer data);
bool deleteData(const string& filename, DataPlayer data);
void sortData(vector<DataPlayer> arr);

#endif
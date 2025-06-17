#ifndef SCORE_BOARD_HPP
#define SCORE_BOARD_HPP

#include <fstream>
#include <vector>


using namespace std;

struct dataPlayer{
    std::string name;
    int score;
    short int lvl;
};

vector<dataPlayer> readFile(const string& filename);
void appendFile(const string& filename, dataPlayer data);
bool deleteData(const string& filename, dataPlayer data);
void sortData(vector<dataPlayer> arr);

#endif
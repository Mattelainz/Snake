#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include <fstream>
#include <vector>
#include <string>

using namespace std;

class PlayerScore {
public:
    char name[4];
    int score;
    
    PlayerScore();
    PlayerScore(const string& playerName, int playerScore);
};

class ScoreBoard {
private:
    static const int MAX_LEVELS = 30;
    static const int SCORES_PER_LEVEL = 5;
    PlayerScore levelScores[MAX_LEVELS][SCORES_PER_LEVEL];
    
public:
    ScoreBoard();
    
    bool loadFromFile(const string& filename = "scoreboard");
    bool saveToFile(const string& filename = "scoreboard");
    
    void addScore(int level, const PlayerScore& newScore);
    void addScore(int level, const string& name, int score);
    
    vector<PlayerScore> getLevelScores(int level);
    void printLevelScores(int level);
    void printAllScores();
    
    void clear();
};

#endif
#include "ScoreBoard.hpp"
#include <cstring>
#include <iostream>
#include <algorithm>

PlayerScore::PlayerScore() : score(0) {
    memset(name, 0, 4);
}

PlayerScore::PlayerScore(const string& playerName, int playerScore) : score(playerScore) {
    memset(name, 0, 4);
    strncpy(name, playerName.c_str(), 3);
    name[3] = '\0';
}

ScoreBoard::ScoreBoard() {
    clear();
}

bool ScoreBoard::loadFromFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    file.read(reinterpret_cast<char*>(levelScores), sizeof(levelScores));
    file.close();
    return true;
}

bool ScoreBoard::saveToFile(const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    file.write(reinterpret_cast<const char*>(levelScores), sizeof(levelScores));
    file.close();
    return true;
}

void ScoreBoard::addScore(int level, const PlayerScore& newScore) {
    if (level < 0 || level >= MAX_LEVELS) {
        return;
    }
    
    // Crea un array temporaneo con il nuovo punteggio
    PlayerScore temp[SCORES_PER_LEVEL + 1];
    
    // Copia i punteggi esistenti
    for (int i = 0; i < SCORES_PER_LEVEL; i++) {
        temp[i + 1] = levelScores[level][i];
    }
    
    // Inserisce il nuovo punteggio nella posizione corretta
    bool inserted = false;
    for (int i = 0; i < SCORES_PER_LEVEL; i++) {
        if (!inserted && newScore.score > temp[i + 1].score) {
            temp[i] = newScore;
            inserted = true;
        } else {
            int sourceIndex = inserted ? i : i + 1;
            temp[i] = temp[sourceIndex];
        }
    }
    
    // Se non è stato inserito, lo mette all'ultimo posto se c'è spazio
    if (!inserted) {
        temp[SCORES_PER_LEVEL - 1] = newScore;
    }
    
    // Copia i primi 5 punteggi nell'array originale
    for (int i = 0; i < SCORES_PER_LEVEL; i++) {
        levelScores[level][i] = temp[i];
    }
}

void ScoreBoard::addScore(int level, const string& name, int score) {
    PlayerScore newScore(name, score);
    addScore(level, newScore);
}

vector<PlayerScore> ScoreBoard::getLevelScores(int level) {
    vector<PlayerScore> scores;
    if (level >= 0 && level < MAX_LEVELS) {
        for (int i = 0; i < SCORES_PER_LEVEL; i++) {
            if (levelScores[level][i].score > 0) {
                scores.push_back(levelScores[level][i]);
            }
        }
    }
    return scores;
}

void ScoreBoard::printLevelScores(int level) {
    if (level < 0 || level >= MAX_LEVELS) {
        return;
    }
    
    cout << "Level " << level << " Scores:" << endl;
    for (int i = 0; i < SCORES_PER_LEVEL; i++) {
        if (levelScores[level][i].score > 0) {
            cout << "\t" << levelScores[level][i].name << ": " 
                 << levelScores[level][i].score << endl;
        }
    }
}

void ScoreBoard::printAllScores() {
    for (int i = 0; i < MAX_LEVELS; i++) {
        bool hasScores = false;
        for (int j = 0; j < SCORES_PER_LEVEL; j++) {
            if (levelScores[i][j].score > 0) {
                hasScores = true;
                break;
            }
        }
        
        if (hasScores) {
            printLevelScores(i);
        }
    }
}

void ScoreBoard::clear() {
    memset(levelScores, 0, sizeof(levelScores));
}
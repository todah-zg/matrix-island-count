#include "Matrix.h"
#include <queue>

bool matrix::Matrix::isValid(int x, int y) {
    return (x >= 0 && x < this->data.size() &&
            y >= 0 && y < this->data[0].size());
}

void matrix::Matrix::markAsProcessed(int x, int y) {
    // variant using special value '2' to mark processed elements
    this->data[x][y]=2;
}

bool matrix::Matrix::isProcessed(int x, int y) {
    // variant using special values
    return this->data[x][y] == 2; 
}

void matrix::Matrix::findAllNeighbours(int x, int y) {
    // uses BFS to find all connected elements (for now)

    // taken 2 by 2, these values cover all neighbouring position offsets
    int offset[] = {0, 1, 0, -1, 0};
    
    std::queue<std::pair<int, int>> searchQueue;
    searchQueue.push(std::make_pair(x, y));

    this->markAsProcessed(x, y);

    while (!searchQueue.empty()) {
        int row = searchQueue.front().first;
        int col = searchQueue.front().second;
        searchQueue.pop();

        for (int i = 0; i < 4; ++i) {
            if( isValid(x + offset[i], y + offset[i+1]) && !isProcessed(x, y)) {
                markAsProcessed(x, y);
                searchQueue.push(std::make_pair(x + offset[i], y + offset[i+1]));
            }
        }
    }
}

int matrix::Matrix::countFigures() {

    if (this->data.size() == 0) {
        return 0;
    }

    int count = 0;
    for (int x = 0; x < this->data.size(); ++x) {
        for (int y = 0; y < this->data[0].size(); ++y) {
            if (this->data[x][y] == 1 && !isProcessed(x, y)) {
                ++count;
                findAllNeighbours(x, y);
            }
        }
    }
    
    return count;
}


#include <iostream>
#include <iomanip>
#include <stack>
#include <algorithm>
#include "Node.h"
#include "fileReader.h"
using namespace std;


bool dfs(Node startNode, int limit) {
    if (startNode.checkComplete()) {
        cout << "The task is completed, the depth is:" << startNode.Depth << endl;
        startNode.makeSolution();
        return true;
    }
    else {
        while (startNode.Depth <= limit && count(startNode.acceptableActions.begin(), startNode.acceptableActions.end(), 1)) {
            for (int i = 0; i < 4; i++) {
                if (startNode.acceptableActions[i] != 0) {
                    startNode.acceptableActions[i] = 0;
                    if ((i == 0 && startNode.parentNode == nullptr) || (i == 0 && startNode.parentNode->action != 0)) {
                        if(dfs(startNode.left(), limit))return true;
                    }
                    else if ((i == 1 && startNode.parentNode == nullptr) || (i == 1 && startNode.parentNode->action != 1)) {
                        if(dfs(startNode.top(), limit))return true;
                    }
                    else if ((i == 2 && startNode.parentNode == nullptr) || (i == 2 && startNode.parentNode->action != 2)) {
                        if(dfs(startNode.right(), limit))return true;
                    }
                    else if ((i == 3 && startNode.parentNode == nullptr) || (i == 3 && startNode.parentNode->action != 3)) {
                        if(dfs(startNode.bottom(), limit))return true;
                    }
                }
            }
        }
        return false;
    }
}
int main()
{
    vector<vector<int>> testMatr = readFile();
    print(testMatr);
    Node test(testMatr);
    if (test.isCorrect()) {
        for (int limit = 1; limit < 100000; limit++) {
            cout << "CHECK LIMIT -----------------------------" << limit << endl;
            if (dfs(test, limit))break;
        }
    }
    else {
        cout << "The puzzle can not be solved( " << endl;
    }
    
}


#include <iostream>
#include <iomanip>
#include <stack>
#include <list>
#include <algorithm>
#include "Node.h"
#include "fileReader.h"
using namespace std;
Node getNode(vector<Node> vec) {
    Node tempNode = vec[vec.size() - 1];
    tempNode.parentNode = vec[vec.size() - 1].parentNode;
    return tempNode;
}
bool funcSort(const Node& a, const Node& b) {
    return(a.h2 > b.h2);
}
bool dfs(Node startNode, int limit) {
    if (startNode.checkComplete()) {
        cout << "The task is completed, the depth is:" << startNode.Depth << endl;
        startNode.makeSolution();
        return true;
    }
    else {
        while (startNode.Depth < limit && count(startNode.acceptableActions.begin(), startNode.acceptableActions.end(), 1)) {
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
void AStar(Node startNode) {
    vector<Node> q;
    q.push_back(startNode);
    while (!q.empty()) {
        sort(q.begin(),q.end(),funcSort);
        Node tempNode = getNode(q);
        q.pop_back();
        if (tempNode.checkComplete()) {
            cout << "The task is completed, the depth is:" << tempNode.Depth << endl;
            cout << "Check" << tempNode.Depth << endl;
            tempNode.makeSolution();
            break;
        }
        for (int i = 0; i < 4; i++) {
            if (tempNode.acceptableActions[i] != 0) {                                                                                                                                                                                                                                                              
                tempNode.acceptableActions[i] == 0;
                if (i == 0) {
                    q.push_back(tempNode.left());
                }
                else if (i == 1) {
                    q.push_back(tempNode.top());
                }
                else if (i == 2) {
                    q.push_back(tempNode.right());
                }
                else if (i == 3) {
                    q.push_back(tempNode.bottom());
                }
            }
        }
    }
}
int main()
{
    vector<vector<int>> testMatr = readFile();
    print(testMatr);
    Node test(testMatr);
    list<Node> q;
    
    if (test.isCorrect()) {
        AStar(test);
    }
    else {
        cout << "The puzzle can not be solved( " << endl;
    }
}


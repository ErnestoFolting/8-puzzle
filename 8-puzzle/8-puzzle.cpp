#include <iostream>
#include <iomanip>
#include <stack>
#include <list>
#include <algorithm>
#include "Node.h"
#include <time.h>
#include "fileReader.h"
using namespace std;
int Node::AllExpandedNodes = 0;
int Node::ExpandedNodes = 0;
int numberOfIterations = 0;
clock_t start = clock();
int nodesInMemory = 0;

bool funcSort(const Node& a, const Node& b) {
    return(a.h2 > b.h2);
}
bool IDS(Node startNode, int limit) {
    numberOfIterations++;
    nodesInMemory++;
    if (numberOfIterations >= 716340 || ((int(clock()) - start) / 1000 / 60) >= 30) {
        cout << "Error, overflow." << endl;
        exit(1);
    }
    if (startNode.checkComplete()) {
        startNode.makeSolution(numberOfIterations, nodesInMemory);
        return true;
    }
    else {
        while (startNode.Depth < limit && count(startNode.acceptableActions.begin(), startNode.acceptableActions.end(), 1)) {
            for (int i = 0; i < 4; i++) {
                if (startNode.acceptableActions[i] != 0) {
                    startNode.acceptableActions[i] = 0;
                    if ((i == 0 )) {
                        if(IDS(startNode.left(), limit))return true;
                    }
                    else if ((i == 1 )) {
                        if(IDS(startNode.top(), limit))return true;
                    }
                    else if ((i == 2)) {
                        if(IDS(startNode.right(), limit))return true;
                    }
                    else if ((i == 3 )) {
                        if(IDS(startNode.bottom(), limit))return true;
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
        numberOfIterations++;
        if (q.size() >= 716340 || ((int(clock()) - start)/1000/60) >= 30) {
            cout << "Error, overflow." << endl;
            exit(1);
        }
        sort(q.begin(),q.end(),funcSort);
        Node tempNode = q[q.size() - 1];;
        q.pop_back();
        if (tempNode.checkComplete()) {
            cout << "Nodes in queue remain to be expand - " << q.size() << endl;
            tempNode.makeSolutionAStar(numberOfIterations);
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
        Node::ExpandedNodes++;
    }
}
int main()
{
    vector<vector<int>> testMatr = readFile();
    print(testMatr);
    Node test(testMatr);
    if (!test.isCorrect()) {
        cout << "What method do you want to use?   1 - IDS   2 - A*" << endl;
        int n;
        cin >> n;
        if (n == 1) {
            for (int i = 1; i < 100000; i++) {
                if (IDS(test, i)) {
                    break;
                }
                nodesInMemory = 0;
            }
        }
        else {
            AStar(test);
        }
    }
    else {
        cout << "The puzzle can not be solved( " << endl;
    }
}


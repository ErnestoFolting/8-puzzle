#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include "Node.h"
using namespace std;

void expand(Node tempNode) {
    int m = 0, n = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tempNode.state[i][j] == 0) {
                m = i;
                n = j;
            }
        }
    }
    stack<Node> nodesToOpen;

}

int main()
{
    vector<vector<int>> testMatr;
    ifstream inFile("test.txt");
    int a = 0, i = 0;
    while (!inFile.eof()) {
        vector<int> tempVec;
        while (i != 3) {
            inFile >> a;
            tempVec.push_back(a);
            i++;
        }     
        testMatr.push_back(tempVec);
        i = 0;
    }
    for(int i = 0;i<3;i++){
        for (int j = 0; j < 3; j++) {
            cout << testMatr[i][j] << " ";
        }
        cout << endl;
    }
    
    Node test(testMatr);
    cout << test.action;
    cout << "check" << test.Check();
    test.bottom();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << test.state[i][j] << " ";
        }
        cout << endl;
    }
}


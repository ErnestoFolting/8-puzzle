#include <iostream>
#include <iomanip>
#include <stack>
#include "Node.h"
#include "fileReader.h"
using namespace std;

Node expand(Node tempNode) {
    int m = 0, n = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tempNode.state[i][j] == 0) {
                m = i;
                n = j;
            }
        }
    }
    if (n >= 1)return tempNode.left();
    if (m >= 1)return tempNode.top();
    if (n <= 1)return tempNode.right();
    if (m <= 1)return tempNode.bottom();
}

void print(vector<vector<int>> vec) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
}
void dfs(Node startNode) {
    
}
int main()
{
    vector<vector<int>> testMatr = readFile();
    print(testMatr);
    Node test(testMatr);
    print(expand(test).state);
}


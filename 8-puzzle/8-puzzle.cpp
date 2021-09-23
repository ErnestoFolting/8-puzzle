#include <iostream>
#include <iomanip>
#include <stack>
#include "Node.h"
#include "fileReader.h"
using namespace std;

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
    for (int i = 0; i < 4; i++) {
        cout << test.acceptableActions[i] << " ";
    }
        
}


#include "fileReader.h"
vector<vector<int>> readFile()
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
    return testMatr;
}

#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "fileReader.h"
using namespace std;

struct Node {
	vector<vector<int>> state;
	Node *parentNode;
	int action; // -1 - none 0 - left 1 - top 2- right 3 - bottom
	int pathCost;
	int Depth;
	vector<bool> acceptableActions = { 0,0,0,0 };
	

	Node(vector<vector<int>>matr) { 
		state = matr;
		action = -1;
		pathCost = 1;
		Depth = 0;
		parentNode = nullptr;
		int m = 0, n = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (matr[i][j] == 0) {
					m = i;
					n = j;
				}
			}
		}
		if (n >= 1)acceptableActions[0] = 1;
		if (m >= 1)acceptableActions[1] = 1;
		if (n <= 1)acceptableActions[2] = 1;
		if (m <= 1)acceptableActions[3] = 1;
	};
	bool checkComplete() {  // check if the game is completed
		vector<vector<int>> resultVec{ {1,2,3},{4,5,6},{7,8,0} };
		bool flag = true;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (state[i][j] != resultVec[i][j])flag = false;
			}
		}
		return flag;
	}
	void makeSolution() {
		Node tempNode = *this;
		while (tempNode.parentNode != nullptr) {
			print(tempNode.state);
			cout << endl;
			tempNode = *tempNode.parentNode;
		}
		print(tempNode.state);
	}
	Node left() {
		int k = 0;
		vector<vector<int>> tempState = this->state;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (tempState[i][j] == 0 && k == 0) {
					int temp = tempState[i][j - 1];
					tempState[i][j - 1] = 0;
					tempState[i][j] = temp;
					k++;
				}
			}
		}
		Node tempNode(tempState);
		tempNode.action = 0;
		tempNode.parentNode = this;
		tempNode.Depth = (this->Depth + 1 );
		tempNode.pathCost = (this->pathCost + 1);
		return  tempNode;
	}
	Node right() {
		int k = 0;
		vector<vector<int>> tempState = state;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (tempState[i][j] == 0 && k == 0) {
					int temp = tempState[i][j + 1];
					tempState[i][j + 1] = 0;
					tempState[i][j] = temp;
					k++;
				}
			}
		}
		Node tempNode(tempState);
		tempNode.action = 2;
		tempNode.parentNode = this;
		tempNode.Depth = (this->Depth + 1);
		tempNode.pathCost = (this->pathCost + 1);
		return  tempNode;
	}
	Node top() {
		int k = 0;
		vector<vector<int>> tempState = state;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (tempState[i][j] == 0 && k == 0) {
					int temp = tempState[i - 1][j];
					tempState[i - 1][j] = 0;
					tempState[i][j] = temp;
					k++;
				}
			}
		}
		Node tempNode(tempState);
		tempNode.action = 1;
		tempNode.parentNode = this;
		tempNode.Depth = (this->Depth + 1);
		tempNode.pathCost = (this->pathCost + 1);
		return  tempNode;
	}
	Node bottom() {
		int k = 0;
		vector<vector<int>> tempState = state;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (tempState[i][j] == 0 && k == 0) {
					int temp = tempState[i + 1][j];
					tempState[i + 1][j] = 0;
					tempState[i][j] = temp;
					k++;
				}
			}
		}
		Node tempNode(tempState);
		tempNode.action = 3;
		tempNode.parentNode = this;
		tempNode.Depth = (this->Depth + 1);
		tempNode.pathCost = (this->pathCost + 1);
		return  tempNode;
	}
};
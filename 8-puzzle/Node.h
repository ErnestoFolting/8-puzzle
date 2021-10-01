#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include "fileReader.h"
using namespace std;

struct Node {
	vector<vector<int>> state;
	static int AllExpandedNodes;
	static int ExpandedNodes;
	Node *parentNode;
	int action; // -1 - none 0 - left 1 - top 2- right 3 - bottom
	int pathCost;
	int Depth;
	int h2;
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
		h2 = 0;
		for (int i = 0; i < 3 ; i++) {
			for (int j = 0; j < 3; j++) {
				if (state[i][j] == 1 || state[i][j] == 4 || state[i][j] == 7) {
					h2 += j;
				}
				else if (state[i][j] == 2 || state[i][j] == 5 || state[i][j] == 8) {
					h2 += abs(j - 1);
				}
				else if (state[i][j] == 3 || state[i][j] == 6 ) {
					h2 += abs(j - 2);
				}
				if (state[i][j] == 1 || state[i][j] == 2 || state[i][j] == 3) {
					h2 += i;
				}
				else if (state[i][j] == 4 || state[i][j] == 5 || state[i][j] == 6) {
					h2 += abs(i - 1);
				}
				else if (state[i][j] == 7 || state[i][j] == 8 ) {
					h2 += abs(i - 2);
				}
			}
		}
		AllExpandedNodes++;
	};
	bool isCorrect()
	{
		vector<int> tempVec;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				tempVec.push_back(state[i][j]);
			}
		}
		int inv_count = 0;
		for (int i = 0; i < 9 - 1; i++)
			for (int j = i + 1; j < 9; j++)
				if (tempVec[j] && tempVec[i] && tempVec[i] > tempVec[j])
					inv_count++;
		return !(inv_count%2);
	}
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
	void makeSolution(int numberOfIteratins, int nodesInMemory) {
		cout << "The task is completed, the depth is:" << Depth << endl;
		cout << "The number of iterations: " << numberOfIteratins << endl;
		cout << "The number of all expanded nodes: " << AllExpandedNodes << endl;
		cout << "The number of nodes in memory: " << nodesInMemory << endl;
		Node tempNode = *this;
		while (tempNode.parentNode != nullptr) {
			print(tempNode.state);
			cout << endl;
			tempNode = *tempNode.parentNode;
		}
		print(tempNode.state);
	}
	void makeSolutionAStar(int numberOfIterations) {
		cout << "The task is completed" << endl << endl;
		cout << "Iterations: " << numberOfIterations << endl;
		print(state);
		cout << endl;
		cout << "The depth is: " << Depth << endl;
		cout << "The number of all expanded nodes: " << AllExpandedNodes << endl;
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
		tempNode.h2 += tempNode.Depth;
		ExpandedNodes+=2;
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
		tempNode.h2 += tempNode.Depth;
		ExpandedNodes += 2;
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
		tempNode.h2 += tempNode.Depth;
		ExpandedNodes += 2;
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
		tempNode.h2 += tempNode.Depth;
		ExpandedNodes += 2;
		return  tempNode;
	}
};
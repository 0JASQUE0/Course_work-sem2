#include "EdmondsKarp.h"
#include <string>
#include <fstream>
#include "queue.h"

void vertexesSearch(LinkedList<char>* listOfCities, ifstream& fin) 
{
	string str;
	char tempChar;
	int counter, index;
	while (!fin.eof()) {
		getline(fin, str);
		counter = 0;
		for (size_t i = 0; i < str.size(); i++) {
			tempChar = str[i++];
			index = listOfCities->find(tempChar);
			if (index == -1) {
				listOfCities->push_back(tempChar);
			}
			counter++;
			if (counter == 2) {
				break;
			}
		}
	}
}

void matrixFilling(LinkedList<char>* listOfVertexes, ifstream& fin, int** capacityMatrix)
{
	string str;
	char tempChar;
	int indexI, indexJ;
	int counter;
	while (!fin.eof()) {
		getline(fin, str);
		counter = 0;
		for (size_t i = 0; i < str.size(); i++) {
			tempChar = str[i++];
			if (counter == 0) {
				indexI = listOfVertexes->find(tempChar);
			}
			if (counter == 1) {
				indexJ = listOfVertexes->find(tempChar);
			}
			if (counter == 2) {
				capacityMatrix[indexI][indexJ] = int(tempChar) - int('0');
			}
			counter++;
		}
	}
}

bool breadthFirstSearch(int** graph, int s, int t, int* parent, size_t size)
{
	bool* visited = new bool[size];
	for (size_t i = 0; i < size; i++) {
		visited[i] = false;
	}

	Queue<int> queue;
	queue.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!queue.empty()) {
		int cur = queue.first();
		queue.pop();
		for (size_t i = 0; i < size; i++) {
			if (visited[i] == false && graph[cur][i] > 0) {
				queue.push(i);
				parent[i] = cur;
				visited[i] = true;
			}
		}
	}

	return visited[t];
}

int EdmondsKarpAlgorithm(int** capacityMatrix, int s, int t, size_t size)
{
	int cur;
	int** graph = new int* [size];
	for (size_t i = 0; i < size; i++) {
		graph[i] = new int[size];
	}
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			graph[i][j] = capacityMatrix[i][j];
		}
	}

	int* parent = new int[size];
	int maxFlow = 0;

	while (breadthFirstSearch(graph, s, t, parent, size)) {
		int pathFlow = 1e9;

		for (int i = t; i != s; i = parent[i]) {
			cur = parent[i];
			if (pathFlow > graph[cur][i]) {
				pathFlow = graph[cur][i];
			}
		}
		for (int i = t; i != s; i = parent[i]) {
			cur = parent[i];
			graph[cur][i] -= pathFlow;
			graph[i][cur] += pathFlow;
		}

		maxFlow += pathFlow;
	}
	
	return maxFlow;
}
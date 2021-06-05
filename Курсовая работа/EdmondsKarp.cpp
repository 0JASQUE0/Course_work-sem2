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
			if (str[i] != ' ') {
				throw("Incorrect input");
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
				if (int(tempChar) < int('0') || int(tempChar) > int('9')) {
					throw("Incorrect input");
				}
				else {
					capacityMatrix[indexI][indexJ] = int(tempChar) - int('0');
				}
			}
			counter++;
		}
	}
}

bool breadthFirstSearch(int** flowMatrix, int source, int target, int* parent, size_t size)
{
	bool* visitedVertexes = new bool[size];
	for (size_t i = 0; i < size; i++) {
		visitedVertexes[i] = false;
	}

	Queue<int> queue;
	queue.push(source);
	visitedVertexes[source] = true;
	parent[source] = -1;

	while (!queue.empty()) {
		int currentVertex = queue.first();
		queue.pop();
		for (size_t i = 0; i < size; i++) {
			if (visitedVertexes[i] == false && flowMatrix[currentVertex][i] > 0) {
				queue.push(i);
				parent[i] = currentVertex;
				visitedVertexes[i] = true;
			}
		}
	}

	return visitedVertexes[target];
}

int EdmondsKarpAlgorithm(int** capacityMatrix, int source, int target, size_t size)
{
	int currentVertex;
	int** flowMatrix = new int* [size];
	for (size_t i = 0; i < size; i++) {
		flowMatrix[i] = new int[size];
	}
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			flowMatrix[i][j] = capacityMatrix[i][j];
		}
	}

	int* parent = new int[size];
	int maxFlow = 0;
	int pathFlow;

	while (breadthFirstSearch(flowMatrix, source, target, parent, size)) {
		pathFlow = 1e9;

		for (int i = target; i != source; i = parent[i]) {
			currentVertex = parent[i];
			if (pathFlow > flowMatrix[currentVertex][i]) {
				pathFlow = flowMatrix[currentVertex][i];
			}
		}
		for (int i = target; i != source; i = parent[i]) {
			currentVertex = parent[i];
			flowMatrix[currentVertex][i] -= pathFlow;
			flowMatrix[i][currentVertex] += pathFlow;
		}

		maxFlow += pathFlow;
	}
	return maxFlow;
}
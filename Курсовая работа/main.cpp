#include <iostream>
#include <fstream>
#include <string>
#include "list.h"
#include "EdmondsKarp.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	ifstream fin("input.txt", ios::in);

	LinkedList<char>* vertexes = new LinkedList<char>;

	vertexesSearch(vertexes, fin);

	size_t n = vertexes->get_size();

	int** capacityMatrix = new int* [n];
	for (size_t i = 0; i < n; i++) {
		capacityMatrix[i] = new int[n];
	}
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			capacityMatrix[i][j] = 0;
		}
	}

	fin.clear();
	fin.seekg(0);

	matrixFilling(vertexes, fin, capacityMatrix);

	int maxFlow = EdmondsKarpAlgorithm(capacityMatrix, 0, n - 1, n);

	fin.clear();
	fin.seekg(0);

	string str;

	cout << "Входные данные:\n";
	while (!fin.eof()) {
		getline(fin, str);
		cout << str << endl;
	}
	cout << "Максимальный поток графа равен: " << maxFlow;

	return 0;
}
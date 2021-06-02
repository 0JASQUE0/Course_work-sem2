#pragma once
#include "list.h"

void vertexesSearch(LinkedList<char>* listOfCities, ifstream& fin);
void matrixFilling(LinkedList<char>* listOfVertexes, ifstream& fin, int** capacityMatrix);
bool breadthFirstSearch(int** graph, int s, int t, int* parent, size_t size);
int EdmondsKarpAlgorithm(int** capacityMatrix, int s, int t, size_t size);
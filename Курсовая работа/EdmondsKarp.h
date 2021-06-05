#pragma once
#include "list.h"

void vertexesSearch(LinkedList<char>* listOfCities, ifstream& fin);
void matrixFilling(LinkedList<char>* listOfVertexes, ifstream& fin, int** capacityMatrix);
bool breadthFirstSearch(int** flowMatrix, int source, int target, int* parent, size_t size);
int EdmondsKarpAlgorithm(int** capacityMatrix, int source, int target, size_t size);
#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <iostream>
#include <string>
#include "D:\Прога 4 сем лабы\Курсовая работа\Курсовая работа\EdmondsKarp.cpp"
#include "D:\Прога 4 сем лабы\Курсовая работа\Курсовая работа\EdmondsKarp.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(vertexesSearchTest)
		{
			ifstream fin;
			fin.open("D:\\Прога 4 сем лабы\\Курсовая работа\\UnitTest1\\test.txt", ios::in);
			LinkedList<char>* list = new LinkedList<char>;
			list->push_back('S');
			list->push_back('O');
			list->push_back('P');
			list->push_back('Q');
			LinkedList<char>* test = new LinkedList<char>;
			vertexesSearch(test, fin);
			for (size_t i = 0; i < list->get_size(); i++) {
				Assert::IsTrue(list->at(i)->data == test->at(i)->data);
			}
			fin.close();
		}

		TEST_METHOD(matrixFillingTest)
		{
			ifstream fin;
			fin.open("D:\\Прога 4 сем лабы\\Курсовая работа\\UnitTest1\\test.txt", ios::in);
			LinkedList<char>* test = new LinkedList<char>;
			vertexesSearch(test, fin);
			size_t n = test->get_size();

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

			matrixFilling(test, fin, capacityMatrix);

			int testMatrix[4][4] = { {0, 3, 3, 0}, {0, 0, 0, 3}, {0, 0, 0, 2}, {0, 0, 0, 0} };

			for (size_t i = 0; i < n; i++) {
				for (size_t j = 0; j < n; j++) {
					Assert::IsTrue(capacityMatrix[i][j] == testMatrix[i][j]);
				}
			}
		}

		TEST_METHOD(EdmondsKarpAlgorithmTest)
		{
			ifstream fin;
			fin.open("D:\\Прога 4 сем лабы\\Курсовая работа\\UnitTest1\\test.txt", ios::in);
			LinkedList<char>* test = new LinkedList<char>;
			vertexesSearch(test, fin);
			size_t n = test->get_size();

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

			matrixFilling(test, fin, capacityMatrix);
			int maxFlow = EdmondsKarpAlgorithm(capacityMatrix, 0, n - 1, n);

			Assert::IsTrue(maxFlow == 5);
		}
	};
}

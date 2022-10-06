/**
 * FloydsAlgorithm.cpp - программа для обнаружения цикла отрицательного веса методом Флойда
 * 
 * Copyright (c) 2021, Vladislav Shkut <shkut@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <iostream>
#include <fstream>

using namespace std;

void ApplyFloydsAlgorithm(int n, const int Inf, int** A)
{
    for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
	    for (int k = 0; k < n; k++) {
		if ((A[j][i] > Inf) && (A[i][k] > Inf)) {
		    A[j][k] = min(A[j][k], A[j][i] + A[i][k]);
		}
	    }
	}
    }
}

bool NegativeWeightCycleExists(int n, const int Inf, int** A)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
	    for (int k = 0; k < n; k++) {
		if ((A[i][k] <= Inf) && (A[k][j] <= Inf) && (A[k][k] < 0)) {
		    A[i][j] = Inf;
		    return true;
		}
	    }
	}
    }

    return false;
}

int main()
{
    const int Inf = -1001;
    
    ifstream fin("input.txt");
    int n;
    fin >> n;
    int** A = new int*[n];
    for (int i = 0; i < n; i++) {
	A[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
	    fin >> A[i][j];
	}
    }
    fin.close();

    ApplyFloydsAlgorithm(n, Inf, A);
    
    ofstream fout("output.txt");
    if (NegativeWeightCycleExists(n, Inf, A)) fout << "YES";
    else fout << "NO";
    fout.close();

    for (int i = 0; i < n; i++) {
	delete[] A[i];
    }

    return 0;
}
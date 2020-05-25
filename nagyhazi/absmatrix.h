#ifndef ABSMATRIX_H
#define ABSMATRIX_H
#include <iostream>
#include <fstream>
#include <exception>
using namespace std;

template<class type>
class absmatrix {
protected:
	type **arr;
	int m;
	int n;
public:
	absmatrix(int m1 = 3,int n1=3,type zahl=0);
	absmatrix(ifstream &file);
	absmatrix(const absmatrix<type>& a);
	virtual ~absmatrix()=0 {
		for (int i = 0; i < m; ++i) {
			delete[] arr[i];
		}
		delete[] arr;
	}
	virtual void print()= 0;
};
//Deklaration: 
template<class type>
absmatrix<type>::absmatrix(int m1, int n1, type zahl) {
	if (m1 <= 0 || n1 <= 0) {
		throw "Error: Falsche Indexierung";
	}
	m = m1;
	n = n1;
	arr = new type*[m]; //m: Anzahl der Zeile
	for (int i = 0; i < m; ++i) {
		arr[i] = new type[n]; // n: Anzahl der Spalte
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = zahl;
		}
	}
}
template<class type>
absmatrix<type>::absmatrix(ifstream &myfile) {
	int sum = 0;
	if (!myfile.is_open()) {
		throw exception("Nicht valid File");
	}
	myfile >> m;
	myfile >> n;
	arr = new type*[m];
	for (int i = 0; i < m; ++i) {
		arr[i] = new type[n];
	}
	while (!myfile.eof()) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				myfile >> arr[i][j];
				if (myfile.eof()) {
					break;
				}
				sum++;
				if (sum > m*n) {
					throw "Error: Falsche Indexierung";
				}
			}
		}
	}
	sum++;
	if (sum != m*n) {
		throw "Error: Falsche Indexierung";
	}
	myfile.close();
}
template<class type>
absmatrix<type>::absmatrix(const absmatrix& a) {
	m = a.m;
	n = a.n;
	arr = new type*[m];
	for (int i = 0; i < m; ++i) {
		arr[i] = new type[n];
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = a.arr[i][j];
		}
	}
}
#endif
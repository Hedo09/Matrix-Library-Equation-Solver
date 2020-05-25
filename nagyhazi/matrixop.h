#ifndef MATRIXOP_H
#define MATRIXOP_H
#include "absmatrix.h"
#include <iostream>
#include <cmath>
using namespace std;
template<class type>
class matrixop :public absmatrix<type> {
private:
	type determinante;
public:
	matrixop(int m1 = 3, int n1 = 3, type zahl = 0) : absmatrix<type>(m1, n1, zahl) {
		this->determinante = this->det(this->arr, this->n);
	}
	matrixop(ifstream &file) : absmatrix<type>(file) { this->determinante = this->det(this->arr, this->n); }
	matrixop(const matrixop& m) : absmatrix<type>(m) {
		this->determinante = m.determinante;
	}
	matrixop<type>& operator+=(const matrixop<type>& m);
	matrixop<type>& operator*=(type n);
	matrixop<type>& operator+=(type n);
	matrixop<type>& operator-=(const matrixop<type>& m);
	matrixop<type>& operator-=(type n);
	matrixop<type>& operator=(const matrixop<type>& m);
	bool operator==(const matrixop<type>& m);
	type det(type **a,int n);
	type getdet() {
		return this->determinante;
	}
	template <class type> friend matrixop<type> operator+(const matrixop<type>& m, int n);
	template <class type> friend matrixop<type> operator+(int n, const matrixop<type>& m);
	template <class type> friend matrixop<type> operator+(const matrixop<type>& m1, const matrixop<type>& m2);
	template <class type> friend ostream & operator<<(ostream &os, matrixop<type> & m);
	template <class type> friend matrixop<type> operator*(const matrixop<type>& m, int n);
	template <class type> friend matrixop<type> operator*(int n, const matrixop<type>& m);
	template <class type> friend matrixop<type> operator*(const matrixop<type>& m1, const matrixop<type>& m2);
	virtual ~matrixop() {}
	int getm() { return this->m; } // Anzahl der Zeile
	int getn() { return this->n; } // Anzahl der Spalte
	void print() {
		for (int i = 0; i < this->m; i++) {
			for (int j = 0; j < this->n; j++) {
				cout << this->arr[i][j] << " ";
			}
			cout << endl;
		}
	}
};
//Deklaration:
template<class type>
matrixop<type>& matrixop<type>::operator+=(const matrixop<type>& m) {
	if (this->m != m.m || this->n != m.n) {
		throw exception("Die Bedingungen der Matrix Addierung(Groeﬂe) werden nicht erfuellt!");
	}
	for (int i = 0; i < m.m; i++) {
		for (int j = 0; j < m.n; j++) {
		this->arr[i][j] += m.arr[i][j];
		}
	}
	return *this;
}
template<class type>
matrixop<type>& matrixop<type>::operator-=(const matrixop<type>& m) {
	if (this->m != m.m || this->n != m.n) {
		throw exception("Die Bedingungen der Matrix Substrahierung (Groeﬂe) werden nicht erfuellt!");
	}
	for (int i = 0; i < m.m; i++) {
		for (int j = 0; j < m.n; j++) {
			this->arr[i][j] -= m.arr[i][j];
		}
	}
	return *this;
}
template<class type>
matrixop<type>& matrixop<type>::operator-=(type n) {
	for (int i = 0; i < this->m; i++) {
		for (int j = 0; j < this->n; j++) {
			this->arr[i][j] -= n;
		}
	}
	return *this;
}
template<class type>
matrixop<type>& matrixop<type>::operator=(const matrixop<type>& m) {
	for (int i = 0; i < this->m; ++i) {
		delete[] this->arr[i];
	}
	delete[] this->arr;
	this->m = m.m;
	this->n = m.n;
	this->arr = new type*[this->m];
	for (int i = 0; i < this->m; ++i) {
		this->arr[i] = new type[this->n];
	}
	for (int i = 0; i < this->m; i++) {
		for (int j = 0; j < this->n; j++) {
			this->arr[i][j] = m.arr[i][j];
		}
	}
	return *this;
}
template<class type>
bool matrixop<type>::operator==(const matrixop<type>& m) {
	if (this->m != m.m || this->n != m.n) {
		return false;
	}
	for (int i = 0; i < m.m; i++) {
		for (int j = 0; j < m.n; j++) {
			if (this->arr[i][j] != m.arr[i][j]) {
				return false;
			}
		}
	}
	return true;
}
template<class type>
matrixop<type> operator+(const matrixop<type>& m, int n) {
	matrixop<type> t(m.m, m.n);
	for (int i = 0; i < m.m; i++) {
		for (int j = 0; j < m.n; j++) {
			t.arr[i][j] = m.arr[i][j] + n;
		}
	}
	return t;
}
template<class type>
matrixop<type>& matrixop<type>::operator+=(type n) {
	for (int i = 0; i < this->m; i++) {
		for (int j = 0; j < this->n; j++) {
			this->arr[i][j] += n;
		}
	}
	return *this;
}
template <class type> 
matrixop<type> operator+(int n, const matrixop<type>& m) {
	matrixop<type> t(m.m, m.n);
	for (int i = 0; i < m.m; i++) {
		for (int j = 0; j < m.n; j++) {
			t.arr[i][j] = m.arr[i][j] + n;
		}
	}
	return t;
}
template <class type>
matrixop<type> operator+(const matrixop<type>& m1, const matrixop<type>& m2) {
	if (m1.m != m2.m || m1.n != m2.n) {
		throw exception("Die Bedingungen der Matrix Addierung(Groeﬂe) werden nicht erfuellt!");
		
	}
	matrixop<type> t(m1.m, m2.n);
	for (int i = 0; i < t.m; i++) {
		for (int j = 0; j < t.n; j++) {
			t.arr[i][j] = m1.arr[i][j] + m2.arr[i][j];
		}
	}
	return t;
}
template <class type>
ostream & operator<<(ostream &os, matrixop<type> & m) {
	for (int i = 0; i < m.m; i++) {
		for (int j = 0; j < m.n; j++) {
			os << m.arr[i][j] << " ";
		}
		os << endl;
	}
	return os;
}
template<class type>
matrixop<type>& matrixop<type>::operator*=(type n) {
	for (int i = 0; i < this->m; i++) {
		for (int j = 0; j < this->n; j++) {
			this->arr[i][j] *= n;
		}
	}
	return *this;
}
template<class type>
matrixop<type> operator*(const matrixop<type>& m, int n) {
	matrixop<type> t(m.m, m.n);
	for (int i = 0; i < m.m; i++) {
		for (int j = 0; j < m.n; j++) {
			t.arr[i][j] = m.arr[i][j] * n;
		}
	}
	return t;
}
template <class type>
matrixop<type> operator*(int n, const matrixop<type>& m) {
	matrixop<type> t(m.m, m.n);
	for (int i = 0; i < m.m; i++) {
		for (int j = 0; j < m.n; j++) {
			t.arr[i][j] = m.arr[i][j] * n;
		}
	}
	return t;
}
template <class type>
matrixop<type> operator*(const matrixop<type>& m1, const matrixop<type>& m2) {
	if (m1.n != m2.m) {
		throw exception("Die Bedingungen der Matrix Multiplizierung werden nicht erfuellt!");
	}
	matrixop<type> t(m1.m, m1.m);
	for (int i = 0; i < m1.m; i++) {
		for (int j = 0; j < m1.m; j++) {
			for (int k = 0; k < m1.n; k++) {
				t.arr[i][j] += m1.arr[i][k] * m2.arr[k][j];
			}
		}
	}
	return t;
}
template <class type>
type matrixop<type>::det(type **a, int n) {
	if (this->n != this->m) {
		return 0;
	}
	type det1 = 0;
	type **temp;
	temp = new type*[n]; //m: Anzahl der Zeile
	for (int i = 0; i < n; ++i) {
		temp[i] = new type[n]; // n: Anzahl der Spalte
	}
	int p, h, k, i, j;
	if (n == 1) {
		return a[0][0];
	}
	else if (n == 2) {
		det1 = (a[0][0] * a[1][1] - a[0][1] * a[1][0]);
		return det1;
	}
	else {
		for (p = 0; p < n; p++) {
			h = 0;
			k = 0;
			for (i = 1; i < n; i++) {
				for (j = 0; j < n; j++) {
					if (j == p) {
						continue;
					}
					temp[h][k] = a[i][j];
					k++;
					if (k == n - 1) {
						h++;
						k = 0;
					}
				}
			}
			det1 = det1 + a[0][p] * pow(-1, p)*det(temp, n - 1);
		}
		return det1;
	}
}
#endif
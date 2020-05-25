#ifndef VECTOR_H
#define VECTOR_H
#include "absmatrix.h"
#include "absvektor.h"
#include <iostream>
#include <cmath>
// arr*arr2=arr3
using namespace std;
const double rad = 3.14 / 180;
template<class type>
class Vector :public absmatrix<type>, public absvector<type> {
private:
	type **arr2;
	type **arr3;
public:
	Vector(type i=0, type j=0, type k=0) : absvector<type>(i, j, k) {
		this->arr = new type*[3];
		for (int i = 0; i < 3; ++i) {
			this->arr[i] = new type[3];
		}
		this->arr2 = new type*[3];
		for (int i = 0; i < 3; ++i) {
			this->arr2[i] = new type[3];
		}
		this->arr3 = new type*[3];
		for (int i = 0; i < 3; ++i) {
			this->arr3[i] = new type[3];
		}
		this->m = 3;
		this->n = 3;
	}
	virtual ~Vector() {
		for (int i = 0; i < 3; ++i) {
			delete[] this->arr2[i];
			delete[] this->arr3[i];
		}
		delete[] this->arr2;
		delete[] this->arr3;
	}
	void print();
	void lösen();
	//void lösenforditva();
	void Rotx(double x);
	void Roty(double x);
	void Rotz(double x);
	void Projxy();
	void Projxz();
	void Projyz();
	void Spiegxy();
	void Spiegxz();
	void Spiegyz();
	void Streckungx(double x);
	void Streckungy(double x);
	void Streckungz(double x);
private:
	void arr3löschen();
	void initarr1();
	void initarr21();
	void Rotyinit(double x);
	void Rotxinit(double x);
	void Rotzinit(double x);
	void Projxyinit();
	void Projxzinit();
	void Projyzinit();
	void Spiegxyinit();
	void Spiegxzinit();
	void Spiegyzinit();
	
	template <class type> friend ostream & operator<<(ostream &os, Vector<type> & v);
};
template<class type>
void Vector<type>::print() {
	cout << "Originelle Vector: " << endl;
	cout << " (" << this->v[0] << "," << this->v[1] << "," << this->v[2] << ")" << endl;
	cout << "Abgebildete Vector: " << endl;
	cout << " (" << this->x[0] << "," << this->x[1] << "," << this->x[2] << ")" << endl;
}
template <class type>
ostream & operator<<(ostream &os, Vector<type> & v) {
	os << "Originelle Vector: " << endl;
	os << " (" << v.x[0] << "," << v.x[1] << "," << v.x[2] << ")" << endl;
	os << "Abgebildete Vector: " << endl;
	os << " (" << v.v[0] << "," << v.v[1] << "," << v.v[2] << ")" << endl;
	return os;
}
template<class type>
void Vector<type>::lösen() {
	type tmp;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				this->arr3[i][j] += this->arr[i][k] * this->arr2[k][j];
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		this->x[i] = 0;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->x[i] += this->v[j] * this->arr3[i][j];
		}
	}
	for (int i = 0; i < 3; i++) {
		tmp = this->v[i];
		this->v[i] = this->x[i];
		this->x[i] = tmp;
	}
}
/*template<class type>
void Vector<type>::lösenforditva() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				this->arr3[i][j] += this->arr2[i][k] * this->arr[k][j];
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->x[i] += this->v[j] * this->arr3[i][j];
		}
	}
	for (int i = 0; i < 3; i++) {
		this->v[i] = this->x[i];
		this->x[i] = 0;
	}
}*/
template<class type>
void Vector<type>::arr3löschen() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->arr3[i][j] = 0;
		}
	}
}
template <class type>
void Vector<type>::Rotxinit(double x) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->arr2[i][j] = 0;
			this->arr3[i][j] = 0;
		}
	}
	this->arr2[0][0] = 1;
	this->arr2[1][1] = cos(x*rad);
	this->arr2[1][2] = -sin(x*rad);
	this->arr2[2][1] = sin(x*rad);
	this->arr2[2][2] = cos(x*rad);
}
template <class type>
void Vector<type>::Rotx(double x) {
	this->Rotxinit(x);
	this->initarr1();
	this->lösen();
}
template <class type>
void Vector<type>::Rotyinit(double x) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->arr2[i][j] = 0;
			this->arr3[i][j] = 0;
		}
	}
	this->arr2[1][1] = 1;
	this->arr2[0][0] = cos(x*rad);
	this->arr2[0][2] = sin(x*rad);
	this->arr2[2][0] = -sin(x*rad);
	this->arr2[2][2] = cos(x*rad);
}
template <class type>
void Vector<type>::Roty(double x) {
	this->Rotyinit(x);
	this->initarr1();
	this->lösen();
}
template <class type>
void Vector<type>::Rotzinit(double x) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->arr2[i][j] = 0;
			this->arr3[i][j] = 0;
		}
	}
	this->arr2[2][2] = 1;
	this->arr2[0][0] = cos(x*rad);
	this->arr2[0][1] = -sin(x*rad);
	this->arr2[1][0] = sin(x*rad);
	this->arr2[1][1] = cos(x*rad);
}
template <class type>
void Vector<type>::Rotz(double x) {
	this->Rotzinit(x);
	this->initarr1();
	this->lösen();
}
template<class type>
void Vector<type>::Projxy() {
	this->Projxyinit();
	this->initarr1();
	this->arr3löschen();
	this->lösen();
}
template<class type>
void Vector<type>::Projxz() {
	this->Projxzinit();
	this->initarr1();
	this->arr3löschen();
	this->lösen();
}
template<class type>
void Vector<type>::Projyz() {
	this->Projyzinit();
	this->initarr1();
	this->arr3löschen();
	this->lösen();
}
template<class type>
void Vector<type>::Spiegyz() {
	this->Spiegyzinit();
	this->initarr1();
	this->arr3löschen();
	this->lösen();
}
template<class type>
void Vector<type>::Spiegxz() {
	this->Spiegxzinit();
	this->initarr1();
	this->arr3löschen();
	this->lösen();
}
template<class type>
void Vector<type>::Spiegxy() {
	this->Spiegxyinit();
	this->initarr1();
	this->arr3löschen();
	this->lösen();
}
template<class type>
void Vector<type>::initarr1() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) {
				this->arr[i][j] = 1;
			}
			else {
				this->arr[i][j] = 0;
			}
		}
	}
}
template<class type>
void Vector<type>::initarr21() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) {
				this->arr2[i][j] = 1;
			}
			else {
				this->arr2[i][j] = 0;
			}
		}
	}
}
template<class type>
void Vector<type>::Projxyinit() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->arr2[i][j] = 0;
		}
	}
	this->arr2[0][0] = 1;
	this->arr2[1][1] = 1;
}
template<class type>
void Vector<type>::Projxzinit() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->arr2[i][j] = 0;
		}
	}
	this->arr2[0][0] = 1;
	this->arr2[2][2] = 1;
}
template<class type>
void Vector<type>::Projyzinit() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->arr2[i][j] = 0;
		}
	}
	this->arr2[2][2] = 1;
	this->arr2[1][1] = 1;
}
template<class type>
void Vector<type>::Spiegyzinit() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->arr2[i][j] = 0;
		}
	}
	this->arr2[2][2] = 1;
	this->arr2[1][1] = 1;
	this->arr2[0][0] = -1;
}
template<class type>
void Vector<type>::Spiegxyinit() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->arr2[i][j] = 0;
		}
	}
	this->arr2[2][2] = -1;
	this->arr2[1][1] = 1;
	this->arr2[0][0] = 1;
}
template<class type>
void Vector<type>::Spiegxzinit() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->arr2[i][j] = 0;
		}
	}
	this->arr2[2][2] = 1;
	this->arr2[1][1] = -1;
	this->arr2[0][0] = 1;
}
template<class type>
void Vector<type>::Streckungx(double x) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) {
				this->arr2[i][j] = 1;
			}
			else {
				this->arr2[i][j] = 0;
			}
		}
	}
	this->arr2[0][0] = x;
	this->initarr1();
	this->arr3löschen();
	this->lösen();
}
template<class type>
void Vector<type>::Streckungy(double x) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) {
				this->arr2[i][j] = 1;
			}
			else {
				this->arr2[i][j] = 0;
			}
		}
	}
	this->arr2[1][1] = x;
	this->initarr1();
	this->arr3löschen();
	this->lösen();
}
template<class type>
void Vector<type>::Streckungz(double x) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) {
				this->arr2[i][j] = 1;
			}
			else {
				this->arr2[i][j] = 0;
			}
		}
	}
	this->arr2[2][2] = x;
	this->initarr1();
	this->arr3löschen();
	this->lösen();
}
#endif

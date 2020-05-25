#ifndef GLEICHUNG_H
#define GLEICHUNG_H
#include "absmatrix.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <exception>

const double EPS = 10E-4;
using namespace std;
template<class type>
class gleichung :public absmatrix<type> {
private:
	double *x;
	bool lösung;
public:
	gleichung(ifstream &myfile);
	template <class type> friend ostream & operator<<(ostream &os, gleichung<type> & g);
	template <class type> friend istream & operator>>(ostream &is, gleichung<type> & g);
	virtual ~gleichung() {
		delete[] x;
	}
	void print();
	void losen(); //Grundfunktion
private: // außer nicht sichtbare Funktions
	void gauss1(); //für n> m
	void gauss2(); // fur n<=m
	void prüfen(); // prüfen vor der dividierung ( um mit 0 dividieren zu vermeiden)
};
//Deklaration:
template<class type>
gleichung<type>::gleichung(ifstream &myfile) {
	int sum = 0;
	if (!myfile.is_open()) {
		throw exception("Nicht valid File");
	}
	myfile >> this->m;
	myfile >> this->n;
	this->arr = new type*[this->m];
	for (int i = 0; i < this->m; ++i) {
		this->arr[i] = new type[this->n+1];
	}
	while (!myfile.eof()) {
		for (int i = 0; i < this->m; i++) {
			for (int j = 0; j <= this->n; j++) {
				myfile >> this->arr[i][j];
				if (myfile.eof()) {
					break;
				}
				sum++;
				if (sum > this->m*(this->n + 1)) {
					throw "Error: Falsche Indexierung";
				}
			}
		}
	}
	if (sum != this->m*(this->n + 1)) {
		throw "Error: Falsche Indexierung";
	}
	myfile.close();
	x = new double[this->n];
	lösung = true;
}
template <class type>
ostream & operator<<(ostream &os, gleichung<type> & g) {
	for (int i = 0; i < g.m; i++) {
		for (int j = 0; j <= g.n; j++) {
			os << g.arr[i][j] << " ";
		}
		os << endl;
	}
	if (g.lösung) {
		cout << "Die Loesungen: " << endl;
		for (int i = 0; i < g.n; i++) {
			cout << "x[" << i + 1 << "]: " << g.x[i] << endl;
		}
	}
	else{
		cout << "Es gibt keine Loesung." << endl;
	}
	return os;
}
template <class type>
istream & operator>>(ostream &is, gleichung<type> & g) {
	for (int i = 0; i < g.m; i++) {
		for (int j = 0; j < g.n; j++) {
			is >> g.arr[i][j];
		}
	}
	return is;
}
template <class type>
void gleichung<type>::print() {
	for (int i = 0; i < this->m; i++) {
		for (int j = 0; j <= this->n; j++) {
			cout << this->arr[i][j] << " ";
		}
		cout << endl;
	}
}
template <class type>
void gleichung<type>::losen() {
	this->print();
	cout << endl;
	this->prüfen();
	if (this->n > this->m) {
		gauss1();
	}
	else {
		gauss2();
	}
}
template<class type>
void gleichung<type>::prüfen() {
	if (this->arr[0][0] == 0) {
		int i;
		type tmp;
		for (i = 1; this->arr[i][0] == 0; i++);
		for (int j = 0; j <= this->n; j++) {
			tmp = this->arr[0][j];
			this->arr[0][j] = this->arr[i][j];
			this->arr[i][j] = tmp;
		}
	}
}
template<class type>
void gleichung<type>::gauss1() {
	int o, i, j, k;
	double sum = 0, c;
	cout << "Es gibt mehr Unbekannte als Gleichung,deshalb ist die Loesung der Gleichungssystem nicht eindeutig!" << endl;
	o = this->n - this->m; // so viel Unbekannten müssen wir eingeben für die Lösbarkeit
	for (i = 0; i < o; i++) {
		cout << "Damit das Gleichungssystem loesbar sein, geben Sie die Werte den einzelnen Unbekannten!" << endl;
		cout << "x[" << i + 1 << "]: ";
		cin>>this->x[i]; // die eingegebene Unbekannten in die LösungArray einschreiben
	}
	// Die eingegebte Unbekannten beinflüssen die Ergebnisse den Gleichungen, wir müssen es modifizieren(Die Ergebnisse):
	for (i = 0; i < this->m; i++) {
		for (j = 0; j < o; j++) {
			this->arr[i][this->n] = this->arr[i][this->n] - (this->x[j] * this->arr[i][j]);
		}
	}
	// Unter der führende eins Position die Werte auf 0 bringen:
	for (j = o; j < this->n; j++)
	{
		for (i = 0; i < this->m; i++)
		{
			if (i > j - o) // das Element liegt unter der führende eins Position
			{
				c = this->arr[i][j] / this->arr[j - o][j];
				for (k = o; k <= this->n; k++)
				{
					this->arr[i][k] = this->arr[i][k] - c * this->arr[j - o][k]; //Die Zeile werden subtrahiert
				}
			}
		}
	}
	this->x[this->n - 1] = this->arr[this->m - 1][this->n] / this->arr[this->m - 1][this->n - 1]; // Der Wert der letzte Unbekannte bestimmen
	for (i = this->m - 2; i >= 0; i--)
	{
		sum = 0;
		for (j = i + 1 + o; j < this->n; j++)
		{
			sum = sum + this->arr[i][j] * this->x[j];
		}
		this->x[i + o] = (this->arr[i][this->n] - sum) / this->arr[i][i + o]; //Andere Lösungen bestimmen
	}
}
template<class type>
void gleichung<type>::gauss2() {
	int help = 0;
	double tmp;
	bool zeile = true;
	int l, j, k, p, i;
	double sum = 0; double sum3 = 0; double sum4 = 0;
	double sum2 = 0;
	double c = 0;
	for (j = 0; j < this->n; j++)
	{
		zeile = true;
		for (i = 0; i < this->n; i++)
		{
			sum4 = 0;
			if (i > j)
			{
				c = this->arr[i][j] / this->arr[j][j];
				for (k = 0; k <= this->n; k++)
				{
					this->arr[i][k] = this->arr[i][k] - c * this->arr[j][k];
				}
				if (this->arr[i][i] == 0) {
					for (p = 0; p < this->n; p++) {
						sum4 += abs(this->arr[i][p]);
					}
					if (sum4 == 0 && this->m<=this->n) {
						//Program findet eine triviale Zeile(besteht aus nur 0)
						cout << "Die " << i + 1 << " Zeile ist eine triviale Zeile deshalb das Gleichungssystem nicht eindeutig loesbar!" << endl;
						this->lösung = false;
						return;
					}
					if (sum4 == 0 && this->m > this->n) {
						cout << this->m << endl;
						for (int j = 0; j <= this->n; j++) {
							tmp = this->arr[i][j];
							this->arr[i][j] = this->arr[this->m-1][j];
							this->arr[this->m-1][j] = tmp;
						}
					}
					if(zeile) { // ein bisschen logic, wenn es mehr arr[i][i]( hauptdiagonale) ==0 gliedern gibt.
						help = i;
						zeile = false;
					}
				}
			}
		}
		if (help != 0) {
			l = help + 1;
			if (this->arr[l][help] != 0) {
				// Zeile-Tauschung!
				for (j = 0; j <= this->n; j++) {
					tmp = this->arr[help][j];
					this->arr[help][j] = this->arr[l][j];
					this->arr[l][j] = tmp;
				}
			}
			else {
				l++;
			}
		}
		if (help != 0 && this->arr[l][l] == 0) {
			l = help + 2;
			if (this->arr[l][help + 1] != 0) {
				// Zeile-Tauschung!
				for (j = 0; j <= this->n; j++) {
					tmp = this->arr[help + 1][j];
					this->arr[help + 1][j] = this->arr[l][j];
					this->arr[l][j] = tmp;
				}
			}
			else {
				l++;
			}
		}
		else {
			help = 0;
		}
	}
	for (i = 0; i < this->n; i++) { //triviale Zeile testen
		sum3 = 0;
		for (j = 0; j <= this->n; j++) {
			if (this->arr[i][j] == 0) {
				sum3++; // es hilft mir
			}
			else {
				break; //keine triviale Zeile
			}
		}
		if (sum3 == this->n + 1) {   //es gibt n+1 Spalte, und alle Glieder sind 0 (sum3 == 1+1+1...+1(n+1 mal)
			cout << "Die verbotene Zeile: " << i + 1 << ".Zeile" << endl;
			cout << "\nEs gibt mindestens eine verbotene Zeile, deshalb wird diese verbotene Zeile rausfallen(keine eindeutige Loesung)\n" << endl;
			this->lösung = false;
			return;
		}
	}
	this->x[this->n - 1] = this->arr[this->n - 1][this->n] / this->arr[this->n - 1][this->n - 1]; //erste Lösung
	for (int i = this->n - 2; i >= 0; i--)
	{
		sum = 0;
		for (int j = i + 1; j < this->n; j++)
		{
			sum = sum + this->arr[i][j] * this->x[j];
		}
		this->x[i] = (this->arr[i][this->n] - sum) / this->arr[i][i];
	}
	if (this->m > this->n) {
		for (i = this->n; i < this->m; i++) {
			for (j = 0; j < this->n; j++) {
				sum2 += (this->x[j] * this->arr[i][j]);
			}
			//Jetzt sum2 ist das Ergebnis den einzelnen Gleichungen
			if (this->arr[i][this->n] - EPS < sum2 && sum2 < this->arr[i][this->n] + EPS) { // wegen unpünktlichkeit
				sum2 = 0;
			}
			else {
				cout<<"Die Gleichunssystem ist nicht loesbar, weil es mindestens eine Gleichung gibt, die nicht wahr ist."<<endl;
				this->lösung = false;
				return;
			}
		}
	}
}
#endif
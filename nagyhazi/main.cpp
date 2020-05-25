#include <iostream>
#include <fstream>
#include "absmatrix.h"
#include "matrixop.h"
#include "gleichung.h"
#include "Vector.h"
#include "absvektor.h"
#include  <cmath>
#include <exception>
using namespace std;

int main() {
	try {
		ifstream file;
		ifstream file2;
		ifstream file3;
		file.open("matrix1.txt");
		file2.open("matrix2.txt");
		file3.open("gleichung.txt");
		matrixop<double> m1(file);
		matrixop<double> m2(file2);
		gleichung<double> g(file3);
		Vector<double> v(4.5, 3.3, 1.2);
		v.Rotx(15);
		v.Spiegxy();
		v.Spiegxy();
		v.Rotx(345);
		cout << v << endl;
		g.losen();
		cout << g;
		m2 = m2 * m1;
		m2 += 4;
		cout << m2;
	}
	catch (const exception &e) {
		cerr << "Error: " << e.what() << endl;
	}
	catch (const char* v) {
		cerr << v << endl;
	}
	cin.get(); cin.get();
	return 0;
}
#ifndef ABSVEKTOR_H
#define ABSVEKTOR_H
#include <iostream>
using namespace std;
template<class type>
class absvector {
protected:
	type* v;
	type* x;
public:
	absvector(type i=0, type j=0, type k=0);
	virtual ~absvector ()=0 {
		delete[] v;
		delete[] x;
	}
	virtual void print() = 0;
};
template<class type>
absvector<type>::absvector(type i, type j, type k) {
	v = new type[3];
	v[0] = i;
	v[1] = j;
	v[2] = k;
	x = new type[3];
	for (int i = 0; i < 3; i++) {
		x[i] = 0;
	}
}
#endif
//#include <iostream>
//#pragma once
//using namespace std;
//
//template<class T>
//class Array {
//	int Len;
//	T* mas;
//public:
//	Array(int l)
//	{
//		Len = l;
//		try {
//			mas = new T[Len];
//		}
//		catch (bad_alloc& e) {
//			cout << "Standard exception: " << e.what() << endl;
//		}
//	}
//
//	~Array();
//	Array& operator= (Array *&x);
//	bool operator== (Array &x);
//	bool operator!= (Array &x);
//	T& operator[] (int i);
//	friend ostream& operator<< (ostream &os, Array &x);
//	friend istream& operator>> (istream &is, Array &x);
//};
//
//

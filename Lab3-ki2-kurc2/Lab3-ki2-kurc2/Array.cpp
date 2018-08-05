//#include "Array.h"
//#include <iostream>
//#include <exception>
///*
//template<class T>Array<T>::Array(int l=20000)
//{
//	Len = l;
//	try {
//		mas = new T[Len];
//	}
//	catch (bad_alloc& e) {
//		cout << "Standard exception: " << e.what() << endl;
//	}
//}
//*/
//template<class T>Array<T>::~Array()
//{
//	delete[]mas;
//	Len = 0;
//}
//
//template<class T>Array<T>& Array<T>::operator= (Array<T> *&x)
//{
//	Len = x.Len;
//	for (int i = 0; i < Len; i++)
//		mas[i] = x.mas[i];
//	return x;
//}
//
//template<class T>bool Array<T>::operator== (Array<T> &x)
//{
//	if (x.Len != this->Len) return false;
//	for (int i = 0; i < Len; i++) {
//		if (x.mas[i] != this->mas[i]) return false;
//	}
//	return true;
//}
//
//template<class T>bool Array<T>::operator!= (Array<T> &x)
//{
//	if (x.Len != this->Len) return true;
//	for (int i = 0; i < Len; i++) {
//		if (x.mas[i] != this->mas[i]) return true;
//	}
//	return false;
//}
//
//template<class T>T& Array<T>::operator[] (int i)
//{
//	if (i >= this->Len) throw "Index out of range";
//	else return mas[i];
//	return 0;
//}
//
//template<class T>ostream& operator<< <T>(ostream &os, Array<T> &x)
//{
//	os << x.Len << " ";
//	for (int i = 0; i < x.Len; i++) {
//		os << x.mas[i] << " ";
//	}
//	return os;
//}
//
//template<class T>istream& operator>> <T>(istream &is, Array<T> &x)
//{
//	cout << "Len = ";
//	is >> x.Len;
//	cout << "mas = ";
//	for (int i = 0; i < x.Len; i++)
//		is >> x.mas[i];
//	is.get();
//	return is;
//}

#include <iostream>
#include <exception>
using namespace std;

template<class T>
class Array {
	int Len;
	T* mas;
public:
	Array(int l = 20000) {
		if (l > 20000)
			throw "_Oops! It's too long. Again, please!\n";
		if (l <= 0)
			throw "_Oops! Len of array is negative? Again, please!\n";
		Len = l; mas = new T[Len];
	};
	~Array();
	Array<T>& operator= (Array<T> &x);
	bool operator== (Array &x);
	bool operator!= (Array &x);
	T& operator[] (int i);
	friend ostream& operator<< <T>(ostream &os, Array &x);
	friend istream& operator>> <T>(istream &is, Array &x);
};

template<class T>
Array<T>::~Array() {
	delete []mas;
	Len = 0;
}

template<class T>
Array<T>& Array<T>::operator= (Array<T> &x)
{
	if (this == &x) return *this;
	delete[]mas;
	Len = x.Len;
	mas = new T[Len];
	for (int i = 0; i < this->Len; i++)
		mas[i] = x.mas[i];
	return *this;
}

template<class T>
bool Array<T>::operator== (Array<T> &x)
{
	if (x.Len != this->Len) return false;
	for (int i = 0; i < Len; i++) {
		if (x.mas[i] != this->mas[i]) return false;
	}
	return true;
}

template<class T>
bool Array<T>::operator!= (Array<T> &x)
{
	if (x.Len != this->Len) return true;
	for (int i = 0; i < Len; i++) {
		if (x.mas[i] != this->mas[i]) 
			return true;
	}
	return false;
}

template<class T>
T& Array<T>::operator[] (int i)
{
	if (i >= this->Len || i <0) 
		throw "Index out of range. Again, please!\n";
	return mas[i];
}

template<class T>
ostream& operator<< (ostream &os, Array<T> &x)
{
	os << "Len = " << x.Len << "\t" << "mas = ";
	for (int i = 0; i < x.Len; i++) {
		os << x.mas[i] << " ";
	}
	return os;
}

template<class T>
istream& operator>> (istream &is, Array<T> &x)
{
	for (int i = 0; i < x.Len; i++)
		is >> x.mas[i];
	is.get();
	return is;
}

template<typename T>
void Use()
{
	int len = 0, i; bool success;
	do {
		success = 1;
		cout << "Input length for array a1: "; 
		cin >> len; fflush(stdin);  //cai nay cho C, giao bao phai dung cho C++ cin.flush() or cin >> flush...
		try {
			Array<T> a1(len),a2;
			cout << "a1 = "; cin >> a1; fflush(stdin);
			a2 = a1;
			cout << "Assignment: a2 = a1 \n";
			cout << "Output a2: " << a2 << endl;
			cout << "Comparison - equal: a2 == a1 is " << (a2 == a1) << endl;
			cout << "Comparison - not equal: a2 != a1 is " << (a2 != a1) << endl;
			do {
				success = 1;
				cout << "Input index: "; cin >> i;
				try {
					cout << "a1[" << i << "] = " << a1[i] << endl;
				}
				catch (const char *e) { cerr << e; success = 0; }
			} while (!success);
		}
		catch (const char *e) { cerr << e; success = 0; }
		catch (bad_alloc& e) {
			cout << "Standard exception: " << e.what() << endl;
		}
	} while (!success);
}

int main()
{
	cout << "INT\n";
	Use<int>();
	cout << "\nCHAR\n";
	Use<char>();
	system("pause");
	return 0;
}

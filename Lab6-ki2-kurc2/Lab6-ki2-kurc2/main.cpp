#include <iostream>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <algorithm>
#include <iomanip>
using namespace std;
#define len 100000

typedef struct {
	LARGE_INTEGER start;
	LARGE_INTEGER stop;
} stopWatch;

void startTimer(stopWatch *timer) {
	QueryPerformanceCounter(&timer->start);
}

void stopTimer(stopWatch *timer) {
	QueryPerformanceCounter(&timer->stop);
}

double LIToSecs(LARGE_INTEGER * L) {
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return ((double)L->QuadPart / (double)frequency.QuadPart);
}

double getElapsedTime(stopWatch *timer) {
	LARGE_INTEGER time;
	time.QuadPart = timer->stop.QuadPart - timer->start.QuadPart;
	return LIToSecs(&time);
}

void Swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

//void SortdecA(int *a, int i, int size, bool boolback){
//	if (a[i] < a[i + 1]) {
//		swap(&a[i], &a[i + 1]);
//		if (i) SortdecA(a, i - 1, size, 1);
//	}
//	if (!boolback && (i < (size - 2))) SortdecA(a, i + 1, size, 0);
//}

void SortdecA(int *a, int size)
{ 
	int min = 0;
	for (int i = 1; i < size - 1; min = 0, i++) {
		for (int j = 0; j < size - i; j++){
			if (a[j] < a[min]) {
				min = j;
			}
		}
		if (min != (size - i)) Swap(a[min], a[size - i]);
	}
}

void SortdecV(vector<int> v, int size)
{
	int min = 0;
	for (int i = 1; i < size - 1; min = 0, i++) {
		for (int j = 0; j < size - i; j++){
			if (v[j] < v[min]) {
				min = j;
			}
		}
		if (min != (size-i)) swap(v[min], v[size - i]);
	}
}

//void SortdecV(vector<int>::iterator a, int i, int size, bool boolback){
//	vector<int>::iterator b = a + 1;
//	if (*a < *b) {
//		swap(*a, *b);
//		if (i) SortdecV(a - 1, i - 1, size, 1);
//	}
//	if (!boolback && (i < size - 2)) SortdecV(b, i + 1, size, 0);
//}

bool mod2(int value){
	return value % 2;
}

bool compare(const int& a, const int& b) {
	return a < b || (a == b && a < b);
}

void GenArray(int a[len + 1]) {
	for (int i = 0; i < len; i++) {
		a[i] = rand();
	} a[len] = len;
}

void GenVector(vector<int> &v) {
	v.reserve(len);
	for (int i = 0; i < len;i++) v.push_back(rand());
}

double TimeArray(int a[len], int x) {
	stopWatch timer;
	startTimer(&timer);
	switch (x) {
	case 1: {
				for (int i = 4; i < len; a[i] = 0, i += 5); break;
	}
	case 2: {
				for (int i = len - 1; i >= 0;){
					if (a[i] % 2) {
						a[len]--;
						for (int j = i; j < a[len]; j++) a[j] = a[j + 1];
					}
					else  i--;
				} break;
	}
	case 3:	{
				//SortdecA(a, 0, a[len], 0); break;
				SortdecA(a, a[len]); break;
	}
	}
	stopTimer(&timer);
	return getElapsedTime(&timer)*1000;
}


double TimeVector(vector<int> v, int x)
{
	stopWatch timer;
	startTimer(&timer);
	switch (x) {
	case 1: {
				for (int i = 4; i < len; v.at(i) = 0, i += 5); break;
	}
	case 2: {
				for (int i = 0; i < v.size();) {
					if (v[i] % 2) v.erase(v.begin() + i);
					else i++;
				} break;
	}
	case 3:	{
				//SortdecV(v.begin(), 0, v.size(), 0);
				SortdecV(v, v.size()); break;
	}
	}
	stopTimer(&timer);
	return getElapsedTime(&timer)*1000;
}

double TimeVector_alg(vector<int> v_alg, int x)
{
	stopWatch timer;
	startTimer(&timer);
	switch (x) {
	case 1: {
				for (int i = 4; i < len; v_alg.at(i) = 0, i += 5); break;
	}
	case 2: {
				v_alg.erase(remove_if(v_alg.begin(), v_alg.end(), mod2), v_alg.end());
				break;
	}
	case 3:	{
				sort(v_alg.begin(), v_alg.end()); 
				for (int i = 0; i < (v_alg.size() / 2); i++)
					 swap(v_alg[i], v_alg[v_alg.size() - i - 1]);
				break;
	}
	}
	stopTimer(&timer);
	return getElapsedTime(&timer)*1000;
}

int main()
{
	srand(time(0));
	int a[len+1]; vector<int> v, v_alg;
	GenArray(a);
	GenVector(v);
	GenVector(v_alg);
	double ta, tv, tv_alg; 
	
	//printf("\tArray\t\tVector\t\tVector_alg\n"); 
	/*cout << setw(15) << "Array" << setw(15) << "Vector" << setw(15) << "Vector_alg" << endl;
	for (int i = 1; i < 4; i++) {
		ta = TimeArray(a, i);
		tv = TimeVector(v, i); 
		tv_alg = TimeVector_alg(v_alg, i); 
		cout << i << setw(15) << ta << setw(15) << tv << setw(15) << tv_alg << endl;
	}*/

	
	/*printf("Trans2:\t%.5f |\t%.5f |\t%.5f\n", TimeArray(a, 2), TimeVector(v, 2), TimeVector_alg(v_alg, 2));
	printf("Trans2:\t%.5f |\t%.5f |\t%.5f\n", TimeArray(a, 2), TimeVector(v, 2), TimeVector_alg(v_alg, 2));
	printf("Trans3:\t%.5f |\t%.5f |\t%.5f\n", TimeArray(a, 3), TimeVector(v, 3), TimeVector_alg(v_alg, 3));*/
	TimeVector_alg(v_alg, 3);
	system("pause");
	return 0;
}
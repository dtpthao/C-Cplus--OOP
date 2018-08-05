#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
using namespace std;

#define LINE printf("--------------------------------------\n");
#define sLINE printf("\t-----------------\n");
#define END { LINE system("PAUSE"); LINE break; }
#define CHOOSE(x) {\
printf("\t1. Add\t\t2. Delete\t3. Find\n\t4. Show all\t5. Sort\t\t");\
printf("6. Save\n\t7. Upload\t8. Go out\n");\
printf("Choose to continue... ");\
x = getchar(); fflush(stdin); sLINE\
}
#define MAXF 11
#define MAXL 21
#define MAXT 13

struct Directory {
	char fstname_[MAXF];
	char lstname_[MAXL];
	char telnum_[MAXT];
	Directory *next_, *prev_;
} *Head, *Tail;

typedef Directory Dir;
typedef Directory *pDir;

void Input(char s[], char m[], int maxs); //Input a member
void Puts(pDir p);						  //show a variable of pDir
int Check_numTel(char telNum[]);		  //check input is number or not
int find_lname(char s[]);				  //find with lastname, use in Find
pDir find_tel(char s[]);				  //find with phone number, use in add_Tel, Delete, Find, ReadF	
int add_Tel(pDir p);					  //
void Delete(pDir p);					  //delete an entry
void Add(pDir &Head, pDir &Tail);	      //add an entry
void Delete();							  //delete or add_Tel
void Find();							  //
void Showall();							  
void Sort(int back, pDir p);
void SaveF(pDir p);
void ReadF();


int main()
{
	char x;
	do {
		CHOOSE(x)
			switch (x) {
			case '1': {Add(Head, Tail); END}
			case '2': {Delete(); END}
			case '3': {Find(); END}
			case '4': {Showall(); END }
			case '5': {Sort(0, Head); END}
			case '6': {SaveF(Head); END}
			case '7': {ReadF(); END}
			case '8': return 0;
			default: printf("-> Input is invalid! Please, try again:\n\n");
		}
	} while (x != '8');
}

void Puts(pDir p) {
	printf("   %s %s - %s\n", p->lstname_, p->fstname_, p->telnum_);
}

void Input(char s[], char m[], int maxs)
{
	printf("%s", s);
	do {
		fgets(m, maxs, stdin); fflush(stdin);
		if (strlen(m) == 1) {
			printf("-> You can't leave this empty!\n%s", s);
		}
	} while (strlen(m) == 1);
	if (strlen(m) < maxs - 1) m = strtok(m, "\n");
}

int Check_numTel(char telNum[])
{
	int i = 0;
	if (!strcmp(telNum, "0")) {
		printf("-> You can't leave this empty!\n");
		return 1;
	}
	while (telNum[i] != '\0') {
		if (telNum[i]<'0' || telNum[i]>'9') {
			printf("-> Input only numbers!\n");
			return 1;
		} i++;
	}
	return 0;
}

int find_lname(char s[])
{
	pDir p = Head; int count = 0;
	while (p) {
		if (!strcmp(p->lstname_, s)) { Puts(p); count++; }
		p = p->next_;
	}
	//free(p);     giao bao k dk dung cai nay
	if (count) return 1;
	return 0;
}

pDir find_tel(char s[])
{
	pDir p = Head; 
	while (p) {
		if (!strcmp(p->telnum_, s)) return p;
		p = p->next_;
	}
	//free(p);    // giao bao k dk xoa, (k dung)
	return 0;
}

int add_Tel(pDir p)
{
	char s[MAXT];
	do {
		Input("Phone number\t: ", s, MAXT);
		if (!Check_numTel(s)) {
			if (find_tel(s)) {
				printf("-> This number is already using! Try another.\n");
			}
			else {strcpy(p->telnum_, s); return 0;}
		}
	} while (s);
}

void Add(pDir &Head, pDir &Tail)
{
	pDir p = (pDir)malloc(sizeof(Dir));
	Input("First name\t: ", p->fstname_, MAXF);
	Input("Last name\t: ", p->lstname_, MAXL);
	add_Tel(p); sLINE
	cout << "->"; Puts(p);
	if (Head == 0) {
		Head = p; Head->prev_ = 0;
		Tail = Head; Tail->next_ = 0;
	}
	else {
		p->prev_ = Tail; Tail->next_ = p;
		Tail = p; Tail->next_ = 0;
	}
}

void Delete(pDir p)
{
	if (!p->prev_) {
		if (!p->next_) { Head = 0; Tail = 0; }
		else { Head = p->next_; Head->prev_ = 0; }
	}
	else {
		if (!p->next_) { Tail = p->prev_; Tail->next_ = 0; }
		else  {
			p->prev_->next_ = p->next_;
			p->next_->prev_ = p->prev_;
		}
	} free(p); cout << "-> Deleted.\n";
}

void Delete()
{
	char telNum[MAXT]; char x;
	do {
		Input("Enter phone number: ", telNum, MAXT);
	} while (Check_numTel(telNum));
	pDir p = find_tel(telNum);
	if (p) {
		Puts(p); sLINE
		printf("Press 1 to Add info or other key to Delete... ");
		cin >> x; fflush(stdin); sLINE
		if (x == '1') add_Tel(p);
		else Delete(p);
	}
	else cout << "\n-> Not found!\n";
}

void Find()
{
	char s[MAXL]; char x;
	printf("\tFind with...\n");
	printf("Press 1 - last name or other key - phone number... "); 
	cin >> x; fflush(stdin); sLINE
	if (x == '1') {
		Input("Enter last name: ", s, MAXL);
		if (!find_lname(s)) printf("-> Not found!\n");
	}
	else {
		do {
			Input("Enter phone number: ", s, MAXT);
		} while (Check_numTel(s));
		if (find_tel(s)) Puts(find_tel(s));
		else printf("-> Not found!\n");
	}
}

void Showall()
{
	pDir p = Head;
	while (p) {
		Puts(p);
		p = p->next_;
	} free(p);
}

void tmp(pDir p)
{
	if (p->prev_) p->prev_->next_ = p->next_;
	else Head = p->next_;
	p->next_->prev_ = p->prev_; 
	p->prev_ = p->next_;
	p->next_ = p->next_->next_;
	if(p->next_) p->next_->prev_ = p;
	else Tail = p;
	p->prev_->next_ = p;
}

void Sort(int back, pDir p)
{
	if (p && (p!=Tail)) {
		if (strcmp(p->lstname_, p->next_->lstname_) > 0) {
			tmp(p); back++;
			Sort(back, p->prev_->prev_);
			if (back == 1) Sort(0, p);
		}
		else if (!strcmp(p->lstname_, p->next_->lstname_)) {
			if (strcmp(p->fstname_, p->next_->fstname_) > 0) {
				tmp(p); back++;
				Sort(back, p->prev_->prev_);
				if (back == 1) Sort(0, p);
			}
		}
		if (!back) Sort(0, p->next_);
	}
	if (p == Tail) printf("-> Sort completed.\n");
}

void SaveF(pDir p)
{
	//ReadF();   giao bao k can
	FILE *f = fopen("phone.dat","wt");
	while (p) {
		fprintf(f, "%s %s - %s\n", p->lstname_, p->fstname_, p->telnum_);
		p = p->next_;
	}
	fclose(f);
	printf("-> Saved.\n");
}

void ReadF()
{
	pDir p; FILE *f = fopen("phone.dat", "rt");
	while (!feof(f)) {
		p = (pDir)malloc(sizeof(Dir));
		fscanf(f, "%[^ ] %[^ ] - %[^\n]\n", p->lstname_, p->fstname_, p->telnum_);
		if (!find_tel(p->telnum_)) {
			if (!Head) {
				Head = p; Head->prev_ = 0;
				Tail = Head; Tail->next_ = 0;
			}
			else {
				Tail->next_ = p; p->prev_ = Tail;
				Tail = p; Tail->next_ = 0;
			}
		}
		else free(p);   // giao bao phai them
	} printf("-> Upload completed.\n");
	fclose(f);
}
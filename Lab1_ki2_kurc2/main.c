#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
using namespace std;

#define LINE printf("------------------\n");
#define sLINE printf("\t-----------\n")
#define END { LINE system("PAUSE"); break; }

struct Directory {
	char fstname_[11];
	char lstname_[21];
	char telnum_[13];
	Directory *next_;
};

//void Input(char s[], char m[], int maxs);
//void Puts(Directory m, int i);
//int Check_numTel(char telNum[]);
//int Check_useTel(Directory m[], char telNum[]);
//int Check_Tel(Directory m[], char telnum[]);
//void Add(int &i, Directory m[]);
//void Delete(Directory m[]);
//void Find(Directory m[]);
//void Showall(Directory m[]);

void Input(char s[], char m[], int maxs)
{
	int a;
	printf("%s", s);
	do {
		fgets(m); a = strlen(m);
		fflush(stdin);
		if (a < 1) {
			printf("--> You can't leave this empty!\n%s", s);
		}
		else if (a > maxs) {
			printf("--> The number of characters is less than %d!\n%s", maxs, s);
		}
	} while ((a < 1) || (a > maxs));
}

void Puts(Directory m, int i) {
	printf("%d.  %s %s - %s\n", i + 1, m.fstname_, m.lstname_, m.telnum_);
}

int Check_numTel(char telNum[])
{
	int i = 0;
	if (!strcmp(telNum, "0")) {
		printf("--> You can't leave this empty!\n");
		return 1;
	}
	while (telNum[i] != '\0') {
		if (telNum[i]<'0' || telNum[i]>'9') {
			printf("--> Input only numbers!\n");
			return 1;
		} i++;
	}
	return 0;
}

int Check_useTel(Directory m[], int n, char telNum[])
{
	for (int i = 0; i < 20; i++) {
		if ((i != n) && (strcmp(m[i].telnum_, telNum) == 0)) {
			printf("--> This number is already using. Try another!\n");
			return 1;
		}
	}
	return 0;
}

int Check_Tel(Directory m[], int i, char telnum[])
{
	if (Check_numTel(telnum) || Check_useTel(m, i, telnum)) {
		return 1;
	}
	return 0;
}

void Add(int &i, Directory m[])
{
	if (i < 20) {
		Input("First name\t: ", m[i].fstname_, 10);
		Input("Last name\t: ", m[i].lstname_, 20);
		do {
			Input("Phone number\t: ", m[i].telnum_, 12);
		} while (Check_Tel(m, i, m[i].telnum_));
		cout << "\n"; Puts(m[i], i); i++;
	}
	else printf("--> The number of entries is less than 20!\n");
}

void Delete(Directory m[])
{
	char telNum[13]; int i = 0, x;
	do {
		Input("Enter the phone number: ", telNum, 12);
	} while (Check_numTel(telNum));

	for (; i<20; i++) {
		if (strcmp(m[i].telnum_, telNum) == 0) {
			Puts(m[i], i); sLINE;
			strcpy(m[i].telnum_, "0");
			cout << "   Deleted!\n"; sLINE;
			printf("   Do you want to add inf?\n\t1. Yes\tOther. No\t");
			cin >> x; fflush(stdin);
			if (x == 1) {
				do {
					Input("\ntel: ", m[i].telnum_, 12);
				} while (Check_Tel(m, i, m[i].telnum_));
				Puts(m[i], i);
			} break;
		}
	} if (i == 20) cout << "\nNot found!\n";
}

void Find(Directory m[])
{
	char lname[20];
	int count = 0;
	Input("Enter the last name: ", lname, 20);
	for (int i = 0; i<20; i++) {
		if (strcmp(m[i].lstname_, lname) == 0) {
			Puts(m[i], i);
			count++;
		}
	} if (!count) printf("   Not found!\n");
}

void Showall(Directory m[])
{
	for (int i = 0; i<20; i++)
	if (strcmp(m[i].telnum_, "0") != 0) {
		Puts(m[i], i);
	}
}


int main()
{
	Directory m[20];
	for (int i = 0; i < 20; i++) {
		strcpy(m[i].telnum_, "0");
	}
	char x; int n = 0;
	do {
		printf("1. Add\n2. Delete\n3. Find\n4. Show all\n5. Go out\n");
		printf("Choose to continue... ");
		x = getchar();
		fflush(stdin); LINE
			switch (x) {
			case '1':{
						 cout << "Add\n";
						 Add(n, m);
						 END;
			}
			case '2': {
						  cout << "Delete\n";
						  Delete(m);
						  END;
			}
			case '3': {
						  cout << "Find\n";
						  Find(m);
						  END;
			}
			case '4': {
						  cout << "Show all\n";
						  Showall(m);
						  END;
			}
			case '5': return 0;
			default: printf("--> Input is invalid! Please, try again:\n");
		}
	} while (x != '5');
}


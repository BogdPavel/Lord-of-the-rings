#ifndef CSTRING_H
#define CSTRING_H

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>

using namespace std;

class cString {
	char* string;
	int size;
public:
	cString() {										//конструктор по умолчанию
		size = 80;
		string = new char[size];
		strcpy(string, "");
	}
	cString(char *str) {				
		size = strlen(str) + 1;
		string = new char[size];
		strcpy(string, str);
	}
	cString(const char str[]) {	
		size = strlen(str) + 1;
		string = new char[size];
		strcpy(string, str);
	}
	cString(const cString& str) {		
		size = str.size + 1;						//конструктор копирования
		string = new char[size];
		strcpy(string, str.string);
	}

	cString& operator= (cString& );					//функции пергрузки операторв
	cString& operator= (char* );
	cString& operator+= (const cString& );
	cString operator+ (const cString& );
	cString operator+ (const char* );

	char& operator[] (const int& );
	char* operator() (int , int );

	bool operator== (const cString& );
	bool operator== (const char* );
	bool operator!= (const cString& );
	
	void operator++ ();
	void operator++ (int);
	void operator-- (int);

	friend cString operator+ (char *, cString&); 
	friend ostream& operator<< (ostream&, const cString&);
    friend istream& operator>> (istream&, cString&);
	//friend istream& getline(istream& , cString& );

	int empty( );
	int strlen( );
	int strlen(const char* );
	const char* str();

	~cString() {										//деструктор объектов
		delete [] string;
	}
};

#endif
